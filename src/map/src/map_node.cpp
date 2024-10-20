#include "ros/ros.h"
#include <nav_msgs/Path.h>
#include <smartcar_msgs/Lane.h>
#include <tf/tf.h>
#include <fstream>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/TwistStamped.h>
#include <smartcar_msgs/My_Trajectory.h>
#include <smartcar_msgs/My_Trajectory_Point.h>
#include <smartcar_msgs/My_TrajectoryArray.h>
#include <cmath>
#include <algorithm>
#include <visualization_msgs/Marker.h>
#include <thread>
#include <map/path_read.h>
#include <map/vis_marker.h>
#include <smartcar_msgs/Location.h>
#include <map/MapHandle.h>
#include <chrono>

// #include <opendrive_parser/parser.h>
// #include <lanelet2_io/Io.h>
// #include <lanelet2_core/LaneletMap.h>
// #include <lanelet2_traffic_rules/TrafficRulesFactory.h>
// #include <lanelet2_routing/RoutingGraph.h>
// #include <rviz_visual_tools/marker_array_publisher.h>


using namespace smartcar::map;

smartcar_msgs::My_TrajectoryArray g_lanes;
smartcar_msgs::My_TrajectoryArray g_lanes_refernece;
smartcar_msgs::My_Trajectory gWaypoints, gWaypoints_fix_dis;
nav_msgs::Path gPath;
smartcar_msgs::Location gpos;
smartcar_msgs::Location gpos_msg;
bool is_pose_get_ = false;
bool is_pose_init = false;
int no_pos_count = 0;

double target_speed = 0;


void callbackFromCurrentPose(const smartcar_msgs::LocationConstPtr &msg){
    gpos_msg = *msg;
    is_pose_get_ = true;
    is_pose_init = true;
    // ROS_INFO("recv pos");
}

void mainCallBack() {
  
    ros::MultiThreadedSpinner spinnsend_reference_lineer(1);
// ros::AsyncSpinner spinner(1); // 在合适的位置声明spinner变量

    spinnsend_reference_lineer.spin();

    ros::waitForShutdown();

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "track_publisher");
    ros::NodeHandle nh;
    ros::NodeHandle npriv("~");


    ros::Subscriber curpos_sub = nh.subscribe<smartcar_msgs::Location>("smartcar/location", 10, &callbackFromCurrentPose);

    // vis_maker map_vis;
    // MapHandle map_handle;

    std::string param_waypoints_filename;
    double road_width = 3.75;

    npriv.param<std::string>("waypoints_file", param_waypoints_filename, "");
    npriv.param<double>("road_width", road_width, 3.75);
    npriv.param("speed", target_speed, double(0));

    vis_maker map_vis;
    MapHandle map_handle(road_width);

    //1.加载轨迹文件，存入gWaypoints
    std::vector<std::string> files;
    get_all_files(param_waypoints_filename, files);
    for (auto &file : files) {
        std::cout << "file path: " << file << std::endl;
    }
    std::vector<std::string> vaild_files;
    vaild_files = remove_erro_files(files, ".txt");
    for (auto &file : vaild_files) {
        std::cout << "vaild_files path: " << file << std::endl;
    }

    for (size_t i=0; i < vaild_files.size(); i++) {
        loadWaypoints(vaild_files[i], gWaypoints);
        map_handle.DistanceResample(gWaypoints, gWaypoints_fix_dis);
        //先根据轨迹名字排序获得lane id
        gWaypoints_fix_dis.lane_id = map_handle.get_lane_id(vaild_files[i]);
        g_lanes.lanes.push_back(gWaypoints_fix_dis);
        std::cout << "route id " << gWaypoints_fix_dis.lane_id << std::endl;
    }

    //按照route id 重新按顺序压入
    map_handle.lanes_sort(g_lanes);
    for (auto &tmp : g_lanes.lanes) {
        std::cout << "sort route id " << tmp.lane_id << std::endl;
        std::cout << "first point Y " << tmp.trajectory_points[0].y << std::endl;
    }
    
    ROS_INFO("map start after sleeping for 1000ms...");
    ros::Duration(1).sleep();

    std::thread th1;
    th1 = std::thread(&mainCallBack);

    //尝试抓取定位
    std::cout << "try get first position\n";
    while (!is_pose_init) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (!ros::ok()) return 0;
    }
    std::cout << "has got position\n";

    ros::Rate loop_rate(10);  //Hz
    tf::TransformBroadcaster broadcaster;
    geometry_msgs::Pose co_simulation_transformation;
    co_simulation_transformation.position.x = g_lanes.lanes.begin()->trajectory_points.begin()->x;
    co_simulation_transformation.position.y = g_lanes.lanes.begin()->trajectory_points.begin()->y;
    co_simulation_transformation.orientation = tf::createQuaternionMsgFromYaw(NormalizeAngle(g_lanes.lanes.begin()->trajectory_points.begin()->theta));
    tf::Pose tfPose_map2odometry(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0));
    tf::poseMsgToTF(co_simulation_transformation, tfPose_map2odometry);
    broadcaster.sendTransform(tf::StampedTransform(tfPose_map2odometry, ros::Time::now(), "map", "co_simulation"));
    // curpose.header.frame_id = "map";
    // curpose.pose.position.x = easting;
    // curpose.pose.position.y = northing;
    // curpose.pose.position.z = ins_altitude;

    // geometry_msgs::Quaternion quat;
    // // quat = tf::createQuaternionMsgFromYaw(NormalizeAngle(ins_yaw / 180.0 * M_PI));
    // quat = tf::createQuaternionMsgFromYaw(NormalizeAngle(ins_yaw / 180.0 * M_PI));
    int mid_line_time = 0;
    
    while (ros::ok()) {

        auto control_start = std::chrono::system_clock::now();
        // 1、判断定位是否更新
        if (!is_pose_get_)
        {
            no_pos_count++;
        } else {
            no_pos_count = 0;
            // 2、更新定位
            gpos = gpos_msg;
            gpos.global_pos.z = 0;
        }

        if (no_pos_count >= 20) {
            ROS_WARN("Necessary topics are not subscribed yet ... ");
            mid_line_time = 0;
            loop_rate.sleep();
            continue;
        }
        
        g_lanes_refernece.lanes.resize(0);
        for (auto &g_lane : g_lanes.lanes) {
            int match_index = 0; //充分利用上一次的匹配结果
            smartcar_msgs::My_Trajectory ref_line;

            match_index = map_handle.get_nearst_point(g_lane, gpos.global_pos.x, gpos.global_pos.y);
            map_handle.get_reference_line(g_lane, match_index, ref_line);
            g_lanes_refernece.lanes.push_back(ref_line);
        }
        if (mid_line_time % 100 == 0) {
            size_t index_line = 0;
            if (g_lanes.lanes.size() > 1) {
                index_line = 1;
            }
            auto g_lane = g_lanes.lanes[index_line];
            // smartcar_msgs::My_Trajectory ref_line;
            // map_handle.get_mid_line(g_lane, ref_line);
            map_handle.pub_mid_line.publish(g_lane);
            mid_line_time = 0;
        }
        

        map_handle.send_reference_line(g_lanes_refernece);

        map_vis.vis_reference_line(g_lanes_refernece, gpos.global_pos.x, gpos.global_pos.y, gpos.orientation[2], gpos.global_pos.z);

        // 5、填充要发送的msg
        smartcar_msgs::My_Trajectory left_line;
        smartcar_msgs::My_Trajectory right_line;
        std::vector<visualization_msgs::Marker> all_boundary_marker;

         for (int i=0; i < g_lanes_refernece.lanes.size(); i++) {
            map_handle.get_left_boundary(g_lanes_refernece.lanes[i], left_line);
            map_handle.get_right_boundary(g_lanes_refernece.lanes[i], right_line);
            map_vis.get_left_boundary_Marker(left_line, gpos.global_pos.x, gpos.global_pos.y, gpos.orientation[2], gpos.global_pos.z, i+100, all_boundary_marker);
            map_vis.get_right_boundary_Marker(right_line, gpos.global_pos.x, gpos.global_pos.y, gpos.orientation[2], gpos.global_pos.z, i+200, all_boundary_marker);  
        }
        //   for (size_t i=0; i < g_lanes_refernece.lanes.size(); i++) {
        //     map_handle.get_left_boundary(g_lanes_refernece.lanes[i], left_line);
        //     map_handle.get_right_boundary(g_lanes_refernece.lanes[i], right_line);
        //     map_vis.get_left_boundary_Marker(left_line, gpos.global_pos.x, gpos.global_pos.y, gpos.orientation[2], static_cast<int>(i+100), all_boundary_marker);
        //     map_vis.get_right_boundary_Marker(right_line, gpos.global_pos.x, gpos.global_pos.y, gpos.orientation[2], static_cast<int>(i+100), all_boundary_marker);  
        // }
        map_vis.vis_boundary_marker(all_boundary_marker);

        auto control_end = std::chrono::system_clock::now();
        std::chrono::duration<double> cost_time = control_end - control_start;
        std::cout << "cost_time: " << cost_time.count() * 1000 << " ms." <<std::endl;
        


        //sleep and spin
        is_pose_get_ = false;
        mid_line_time++;
    
        loop_rate.sleep();

    }
    if (th1.joinable()) {
        th1.join();
    }

    return 0;
}

