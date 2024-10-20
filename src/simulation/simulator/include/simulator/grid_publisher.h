/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2024-03-21 13:38:55
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-21 14:05:10
 * @FilePath: /miniEV_grad/src/simulation/simulator/include/simulator/grid_publisher.h
 */
#ifndef _GRID_PUBLISHER_H
#define _GRID_PUBLISHER_H

#include <ros/ros.h>
#include <cstdint>
#include <algorithm>
#include <simulator/sim_info.hpp>
#include <vector>
#include <eigen3/Eigen/Core>
#include <smartcar_msgs/Grid.h>
#include <visualization_msgs/Marker.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <smartcar_msgs/DetectedObjectArray.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <string>

namespace ITS
{
    class Grid
    {
    public:
        Grid();
        ~Grid();

        void process_data(std::vector<struct object_info> &object_info_);
        void publish_3Dbox_marker(Eigen::MatrixXd &corners_3d_, int id_);
        void publish_3DboxId_marker(double x, double y, double z, std::string id_, double height);
        void object2grid(std::vector<struct Rect_point> &RectArray_);
        bool isPointInRect(cv::Point2d P, struct Rect_point rect);
        void local2global(const double &local_x, const double &local_y, const double &local_heading,
                          const double &ref_x, const double &ref_y, const double &ref_heading,
                          double &out_x, double &out_y, double &out_heading);
        void local2global(const double &local_x, const double &local_y,
                            const double &ref_x, const double &ref_y, const double &ref_heading,
                            double &out_x, double &out_y); 

        //vehicle pose
        geometry_msgs::PoseStamped egocar;


    private:
        // grid variables
        ros::Time timestamp;
        float grid_step = 0.2;
        int grid_cloum = 400; //列数
        int grid_row = 150; //行数
        int grid_nums = grid_cloum * grid_row; //栅格左下角在后轴中心，从左至右，从下到上计数

        //vehicle variables
        double length;
        double width;
        double heigth;
        double wheel_base;
        double rear_overhang;
        double front_overhang;
        double tire_radius;



        //发布3D box
        ros::NodeHandle nh;
        ros::Publisher box_pub = nh.advertise<visualization_msgs::Marker>("detect_box3d", 10);
        ros::Publisher box_id_pub = nh.advertise<visualization_msgs::Marker>("detect_boxid", 10);
        ros::Publisher grid_pub = nh.advertise<smartcar_msgs::Grid>("ITS/Grid", 10);
        ros::Publisher occupancygrid_pub = nh.advertise<nav_msgs::OccupancyGrid>("ITS/OccupancyGrid",10);
        ros::Publisher objects_pub = nh.advertise<smartcar_msgs::DetectedObjectArray>("ITS/DetectObjects", 10);

        // ros::Publisher box_pub ;
        // ros::Publisher box_id_pub ;
        // ros::Publisher grid_pub ;
        // ros::Publisher occupancygrid_pub ;
        // ros::Publisher objects_pub ;

    };
} // Grid

#endif // _GRID_PUBLISHER_H
