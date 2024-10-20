#include <naive_motion_predict/MapHandle.h>


namespace smartcar {
namespace prediction {


MapHandle::MapHandle(const double lane_width)
{
    lane_width_ = lane_width;
    pub_refernece_line = nh.advertise<smartcar_msgs::My_TrajectoryArray>("ReferenceLine_CenterPoint", 10);
}

MapHandle::~MapHandle()
{
}

int MapHandle::get_nearst_point(const smartcar_msgs::My_Trajectory &path, const double &x, const double &y) {
    const int n = path.trajectory_points.size();
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
    int end_index = path.trajectory_points.size();

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

    ROS_INFO("reference_line size: %ld", output_path.trajectory_points.size());
}

void MapHandle::send_reference_line(smartcar_msgs::My_TrajectoryArray &refernece_line) {

    refernece_line.header.frame_id = "map";
    refernece_line.header.stamp = ros::Time::now();
    pub_refernece_line.publish(refernece_line);
   
    ROS_INFO("send_reference_line success");
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

void MapHandle::TimeResample(const smartcar_msgs::My_Trajectory &gWaypoints, smartcar_msgs::My_Trajectory &gWaypoints_fix_dis) {
    //2.改变gPath的点距，存入gWaypoints_fix_dis
    gWaypoints_fix_dis.trajectory_points.resize(0);
    gWaypoints_fix_dis.num = 0;
    double dt = 100;
    for (const auto& ref_point : gWaypoints.trajectory_points) {
        // geometry_msgs::PoseStamped path_point;
        smartcar_msgs::My_Trajectory_Point path_point;
        path_point = ref_point;

        if (!gWaypoints_fix_dis.trajectory_points.empty()) {
            dt = path_point.relative_time - gWaypoints_fix_dis.trajectory_points.back().relative_time;   
        }
        if (dt < 0.1) {
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
    for (int i=0; i< 64; i++) {
        routes.push_back("car_" + std::to_string(i * 100));
    }
    for (long unsigned int i = 0; i < routes.size(); i++) {
        if (path.find(routes[i]) != std::string::npos) {
            return i * 100;
        }
    }

    return -1; //-1代表没有找到对应的ID
}

void MapHandle::lanes_sort(smartcar_msgs::My_TrajectoryArray &trajs) {
    smartcar_msgs::My_TrajectoryArray tmp_lanes;
    tmp_lanes.lanes.resize(trajs.lanes.size());
    for (long unsigned int i = 0; i < trajs.lanes.size(); i++) {
        std::swap(trajs.lanes[i], tmp_lanes.lanes[trajs.lanes[i].lane_id]);
    }

    trajs.lanes.resize(0);
    for (auto &tmp_lane : tmp_lanes.lanes) {
        trajs.lanes.push_back(tmp_lane);
    }


}

}   //namespace prediction
}   //namespace smartcar