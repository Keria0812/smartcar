/**
 * @file vis_maker.h
 * @author your name (you@domain.com)
 * @brief vis reference line and boundary
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <ros/ros.h>
#include <smartcar_msgs/My_Trajectory.h>
#include <smartcar_msgs/My_TrajectoryArray.h>
#include <visualization_msgs/Marker.h>
#include <map/common.h>
#include <vector>

namespace smartcar {
namespace map {

class vis_maker
{
private:
    /* data */
    ros::NodeHandle vis_node;

    ros::Publisher vis_ref_line;
    ros::Publisher vis_left_line;
    ros::Publisher vis_right_line;
    ros::Publisher vis_boundary_line;

    visualization_msgs::Marker ref_points, l_ref_points, r_ref_points; //可视化使用

    

public:



    vis_maker(/* args */);
    ~vis_maker() = default;


    
    void vis_reference_line(const smartcar_msgs::My_TrajectoryArray &gpath, const double x, const double y, const double yaw, const double z) {

        std::vector<visualization_msgs::Marker> tmp_ref_markers;
        int marker_id = 0;
        for (auto &g_line : gpath.lanes) {
            ref_points.points.resize(0);
            for(size_t i= 0; i < g_line.trajectory_points.size(); i++){
                geometry_msgs::Pose tmp_pose;
                double tmp_yaw;
                // std::cout << "path_x:   " << ref_line.poses.back().pose.position.x << " ";
                // std::cout << "path_y:   " << ref_line.poses.back().pose.position.y << " ";
                // std::cout << "path_yaw:   " << ref_yaw << std::endl;            
                global2local(g_line.trajectory_points[i].x, g_line.trajectory_points[i].y, g_line.trajectory_points[i].theta,
                            x, y, yaw,
                            tmp_pose.position.x, tmp_pose.position.y, tmp_yaw);
                tmp_pose.position.z = z;
                ref_points.points.push_back(tmp_pose.position);

            }
            marker_id++;
            ref_points.id = marker_id;
            tmp_ref_markers.push_back(ref_points);
            
        }
        for (auto &tmp_ref_marker : tmp_ref_markers) {
            vis_ref_line.publish(tmp_ref_marker);
        }


    }

    void get_left_boundary_Marker(const smartcar_msgs::My_Trajectory &gpath, const double x, const double y, const double yaw, const double z, int marker_id, std::vector<visualization_msgs::Marker> &boundary) {
        l_ref_points.points.resize(0);
        for(size_t i= 0; i < gpath.trajectory_points.size(); i++){
            geometry_msgs::Pose tmp_pose;
            double tmp_yaw;
            // std::cout << "path_x:   " << ref_line.poses.back().pose.position.x << " ";
            // std::cout << "path_y:   " << ref_line.poses.back().pose.position.y << " ";
            // std::cout << "path_yaw:   " << ref_yaw << std::endl;            
            global2local(gpath.trajectory_points[i].x, gpath.trajectory_points[i].y, gpath.trajectory_points[i].theta,
                        x, y, yaw,
                        tmp_pose.position.x, tmp_pose.position.y, tmp_yaw);
            tmp_pose.position.z  = z;
            l_ref_points.points.push_back(tmp_pose.position);



        }
        l_ref_points.id = marker_id;
        // vis_left_line.publish(l_ref_points);   
        // return l_ref_points;  
        boundary.push_back(l_ref_points);
    }

    void get_right_boundary_Marker(const smartcar_msgs::My_Trajectory &gpath, const double x, const double y, const double yaw, const double z, int marker_id, std::vector<visualization_msgs::Marker> &boundary) {
        r_ref_points.points.resize(0);
        for(size_t i= 0; i < gpath.trajectory_points.size(); i++){
            geometry_msgs::Pose tmp_pose;
            double tmp_yaw;
            // std::cout << "path_x:   " << ref_line.poses.back().pose.position.x << " ";
            // std::cout << "path_y:   " << ref_line.poses.back().pose.position.y << " ";
            // std::cout << "path_yaw:   " << ref_yaw << std::endl;            
            global2local(gpath.trajectory_points[i].x, gpath.trajectory_points[i].y, gpath.trajectory_points[i].theta,
                        x, y, yaw,
                        tmp_pose.position.x, tmp_pose.position.y, tmp_yaw);
            tmp_pose.position.z  = z;
            r_ref_points.points.push_back(tmp_pose.position);

        }
        r_ref_points.id = marker_id;
        // vis_right_line.publish(r_ref_points);      
        // return r_ref_points;
        boundary.push_back(r_ref_points);
    }

    void vis_boundary_marker(const std::vector<visualization_msgs::Marker> boundaries) {
       for (auto &tmp_ref_marker : boundaries) {
            vis_boundary_line.publish(tmp_ref_marker);
        }        
    }


    
};

vis_maker::vis_maker(/* args */)
{

    //发布转换到局部坐标系下的参考轨迹及其边界线
    vis_ref_line = vis_node.advertise<visualization_msgs::Marker>("vis_ref_line", 10);
    // vis_left_line = vis_node.advertise<visualization_msgs::Marker>("vis_left_line", 10);
    // vis_right_line = vis_node.advertise<visualization_msgs::Marker>("vis_right_line", 10);
    vis_boundary_line = vis_node.advertise<visualization_msgs::Marker>("vis_boundary_line", 10);

    ref_points.header.frame_id = l_ref_points.header.frame_id = r_ref_points.header.frame_id = "base_link";
    ref_points.header.stamp = l_ref_points.header.stamp = r_ref_points.header.stamp = ros::Time::now();
    ref_points.ns = l_ref_points.ns = r_ref_points.ns = "smartcar/map";
    ref_points.action = l_ref_points.action = r_ref_points.action = visualization_msgs::Marker::ADD;


    ref_points.id = 0;
    l_ref_points.id = 1;
    r_ref_points.id = 2;

    ref_points.type = visualization_msgs::Marker::POINTS;
    l_ref_points.type = visualization_msgs::Marker::POINTS;
    r_ref_points.type = visualization_msgs::Marker::POINTS;

    //设置点的粗细
    ref_points.scale.x = 0.05;
    ref_points.scale.y = 0.05;

    l_ref_points.scale.x = 0.1;
    l_ref_points.scale.y = 0.1;

    r_ref_points.scale.x = 0.1;
    r_ref_points.scale.y = 0.1;

    //设置线的颜色
    ref_points.color.r = 0.0f;
    ref_points.color.g = 1.0;
    ref_points.color.b = 0.0f;
    ref_points.color.a = 1.0f;

    // Line strip is blue
    l_ref_points.color.r = 1.0f;
    l_ref_points.color.g = 0.0;
    l_ref_points.color.b = 1.0f;
    l_ref_points.color.a = 1.0f;

    // Line list is red
    r_ref_points.color.r = 1.0f;
    r_ref_points.color.g = 0.0;
    r_ref_points.color.b = 1.0f;
    r_ref_points.color.a = 1.0f;

    ref_points.lifetime = ros::Duration(0.1);
    l_ref_points.lifetime = ros::Duration(0.1);
    r_ref_points.lifetime = ros::Duration(0.1);
}







}   //namespace smartcar
}   //namespace map