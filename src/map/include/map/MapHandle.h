/**
 * @file MapHandle.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <ros/ros.h>
#include <map/common.h>
#include <smartcar_msgs/My_Trajectory.h>
#include <smartcar_msgs/My_TrajectoryArray.h>
#include <visualization_msgs/Marker.h>


namespace smartcar {
namespace map {

class MapHandle
{
private:
    /* data */
    ros::NodeHandle nh;
    ros::Publisher pub_refernece_line;
    // double lane_width_ = 3.75;
    double lane_width_ = 3.5;
    // double lane_width_ = 12.0/3.281;
    
public:
    MapHandle(const double lane_width);
    ~MapHandle();
    ros::Publisher pub_mid_line;
    int get_nearst_point(const smartcar_msgs::My_Trajectory &path, const double &x, const double &y);

    void get_reference_line(const smartcar_msgs::My_Trajectory &path, const int nearst_index, smartcar_msgs::My_Trajectory &output_path);


    void send_reference_line(smartcar_msgs::My_TrajectoryArray &path);

    void get_left_boundary(const smartcar_msgs::My_Trajectory &path, smartcar_msgs::My_Trajectory &output_path);

    void get_right_boundary(const smartcar_msgs::My_Trajectory &path, smartcar_msgs::My_Trajectory &output_path);

    void DistanceResample(const smartcar_msgs::My_Trajectory &gWaypoints, smartcar_msgs::My_Trajectory &gWaypoints_fix_dis);

    int get_lane_id(const std::string path);

    void lanes_sort(smartcar_msgs::My_TrajectoryArray &trajs);
};

MapHandle::MapHandle(const double lane_width)
{
    lane_width_ = lane_width;
    pub_refernece_line = nh.advertise<smartcar_msgs::My_TrajectoryArray>("ReferenceLine_CenterPoint", 10);
    pub_mid_line = nh.advertise<smartcar_msgs::My_Trajectory>("global_lane", 10);

}

MapHandle::~MapHandle()
{
}

int MapHandle::get_nearst_point(const smartcar_msgs::My_Trajectory &path, const double &x, const double &y) {
    const int n = static_cast<int>(path.trajectory_points.size());
    ROS_INFO("path size %d", n);
    
    // 3、找当前位置距离全局地图的最近点
    ROS_INFO("cur x %.3f\tcur y %.3f", x, y);
    double distance = pow(x - path.trajectory_points.front().x, 2) 
                        + pow(y - path.trajectory_points.front().y, 2);
    int min = 0;
    for (int i = 0; i < n; i++)
    {
        double d = pow(x - path.trajectory_points[i].x, 2) 
                    + pow(y - path.trajectory_points[i].y, 2);
        if (d < distance)
        {
            distance = d;
            min = i;
        }
    }
    return min;
    // ROS_INFO("match_index %d", match_index);
    // ROS_INFO("cur1 x %.3f\tcur1 y %.3f", gPath.poses[match_index].pose.position.x, gPath.poses[match_index].pose.position.y);
}

void MapHandle::get_reference_line(const smartcar_msgs::My_Trajectory &path, const int nearst_index, smartcar_msgs::My_Trajectory &output_path) {
    
    output_path.trajectory_points.resize(0);
    output_path.lane_id = path.lane_id;

    // 4、设置参考线发送的长度
    int start_index = 0;
    int end_index = static_cast<int> (path.trajectory_points.size());

    if((end_index - nearst_index) > 100){
        end_index = 100 + nearst_index;
    }
    if ((nearst_index - 20) >  0) {
        start_index = nearst_index - 20;
    }
    start_index = std::max(0, start_index);
    // ROS_INFO("start_index %ld", start_index);
    // ROS_INFO("end_index %ld", end_index);
    
    // 5、填充要发送的msg
    for(int i= start_index; i < end_index; i++){
        output_path.trajectory_points.push_back(path.trajectory_points[i]);
    }

    ROS_INFO("reference_line size: %ld %f m", output_path.trajectory_points.size(), output_path.trajectory_points.back().x - output_path.trajectory_points.begin()->x);
}



void MapHandle::send_reference_line(smartcar_msgs::My_TrajectoryArray &refernece_line) {

    refernece_line.header.frame_id = "map";
    refernece_line.header.stamp = ros::Time::now();
    pub_refernece_line.publish(refernece_line);
   
    ROS_INFO("send_reference_line success, The lines has %ld ", refernece_line.lanes.size());
}

void MapHandle::get_left_boundary(const smartcar_msgs::My_Trajectory &path, smartcar_msgs::My_Trajectory &output_path) {
    
    output_path.trajectory_points.resize(0);
    for(auto &point : path.trajectory_points){

        // 6、转为局部坐标可视化参考线及边界
        smartcar_msgs::My_Trajectory_Point tmp_pose;

        local2global(0, lane_width_ / 2,
                    point.x, point.y, point.theta,
                    tmp_pose.x, tmp_pose.y);
        
        output_path.trajectory_points.push_back(tmp_pose);
    }
}

void MapHandle::get_right_boundary(const smartcar_msgs::My_Trajectory &path, smartcar_msgs::My_Trajectory &output_path) {
    
    output_path.trajectory_points.resize(0);
    for(auto &point : path.trajectory_points){

        // 6、转为局部坐标可视化参考线及边界
        smartcar_msgs::My_Trajectory_Point tmp_pose;

        local2global(0, lane_width_ / (-2),
                    point.x, point.y, point.theta,
                    tmp_pose.x, tmp_pose.y);
        
        output_path.trajectory_points.push_back(tmp_pose);
    }
}

void MapHandle::DistanceResample(const smartcar_msgs::My_Trajectory &gWaypoints, smartcar_msgs::My_Trajectory &gWaypoints_fix_dis) {
    //2.改变gPath的点距，存入gWaypoints_fix_dis
    gWaypoints_fix_dis.trajectory_points.resize(0);
    gWaypoints_fix_dis.num = 0;
    double s = 100;
    for (const auto& ref_point : gWaypoints.trajectory_points) {
        // geometry_msgs::PoseStamped path_point;
        smartcar_msgs::My_Trajectory_Point path_point;
        path_point = ref_point;

        if (!gWaypoints_fix_dis.trajectory_points.empty()) {
            double dx = path_point.x - gWaypoints_fix_dis.trajectory_points.back().x;
            double dy = path_point.y - gWaypoints_fix_dis.trajectory_points.back().y;
            s = std::sqrt(dx * dx + dy * dy);
        }
        if (s < 0.9) {
            continue;
        }
        gWaypoints_fix_dis.trajectory_points.push_back(path_point);
        gWaypoints_fix_dis.num += 1;

        //打印检查
        // ROS_INFO_STREAM("Discretized X: " << path_point.pose.position.x);
        // ROS_INFO_STREAM("Discretized Y: " << path_point.pose.position.y);
        // ROS_INFO_STREAM("Discretized S: " << path_point.s);
        // ROS_INFO_STREAM("Discretized kappa: " << path_point.kappa);
    }    
}

int MapHandle::get_lane_id(const std::string path) {

    std::vector<std::string> routes;
    routes.push_back("route_0");
    routes.push_back("route_1");
    routes.push_back("route_2");
    for (size_t i = 0; i < routes.size(); i++) {
        if (path.find(routes[i]) != std::string::npos) {
            return  static_cast<int>(i);
        }
    }
    return -1;
}

void MapHandle::lanes_sort(smartcar_msgs::My_TrajectoryArray &trajs) {
    smartcar_msgs::My_TrajectoryArray tmp_lanes;
    tmp_lanes.lanes.resize(trajs.lanes.size());
    for (size_t i = 0; i < trajs.lanes.size(); i++) {
        std::swap(trajs.lanes[i], tmp_lanes.lanes[trajs.lanes[i].lane_id]);
    }

    trajs.lanes.resize(0);
    for (auto &tmp_lane : tmp_lanes.lanes) {
        trajs.lanes.push_back(tmp_lane);
    }


}

}   //namespace map
}   //namespace smartcar