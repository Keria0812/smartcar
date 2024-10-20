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
#ifndef MAPHANDLE_H
#define MAPHANDLE_H

#include <ros/ros.h>
#include <naive_motion_predict/common.h>
#include <smartcar_msgs/My_Trajectory.h>
#include <smartcar_msgs/My_TrajectoryArray.h>
#include <visualization_msgs/Marker.h>


namespace smartcar {
namespace prediction {

class MapHandle
{
private:
    /* data */
    ros::NodeHandle nh;
    ros::Publisher pub_refernece_line;
    double lane_width_ = 3.75;
public:
    MapHandle(const double lane_width);
    ~MapHandle();

    int get_nearst_point(const smartcar_msgs::My_Trajectory &path, const double &x, const double &y);

    void get_reference_line(const smartcar_msgs::My_Trajectory &path, const int nearst_index, smartcar_msgs::My_Trajectory &output_path);

    void send_reference_line(smartcar_msgs::My_TrajectoryArray &path);

    void get_left_boundary(const smartcar_msgs::My_Trajectory &path, smartcar_msgs::My_Trajectory &output_path);

    void get_right_boundary(const smartcar_msgs::My_Trajectory &path, smartcar_msgs::My_Trajectory &output_path);

    void DistanceResample(const smartcar_msgs::My_Trajectory &gWaypoints, smartcar_msgs::My_Trajectory &gWaypoints_fix_dis);

    void TimeResample(const smartcar_msgs::My_Trajectory &gWaypoints, smartcar_msgs::My_Trajectory &gWaypoints_fix_dis);

    int get_lane_id(const std::string path);

    void lanes_sort(smartcar_msgs::My_TrajectoryArray &trajs);
};


}   //namespace prediction
}   //namespace smartcar

#endif