/**
 * @file common.h
 * @author your name (you@domain.com)
 * @brief 常用的工具函数
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <cmath>

namespace smartcar {
namespace map {


/**
 * @brief limit rad [-pi, pi)
 * 
 * @param theta 
 * @return double 
 */
inline double NormalizeAngle(double theta)
{
  //限制在-pi~pi
  auto n = (int)(theta / (2 * M_PI));
  theta -= n * (2 * M_PI);
  if (theta > M_PI)
  {
    theta -= 2 * M_PI;
  }
  if (theta <= -M_PI)
  {
    theta += 2 * M_PI;
  }
  return theta;
}

void global2local(const double &global_x, const double &global_y, const double &global_yaw,
                    const double &ref_x, const double &ref_y, const double &ref_heading,
                    double &out_x, double &out_y, double &yaw) {
                    
                    //将全局轨迹转为车辆坐标系下的轨迹
                    double dx = global_x - ref_x;
                    double dy = global_y - ref_y;
                    out_x = dx * cos(ref_heading) + dy * sin(ref_heading);
                    out_y = dx * (-sin(ref_heading)) + dy * cos(ref_heading);
                    yaw = NormalizeAngle(global_yaw - ref_heading);
                    // ROS_INFO_STREAM("global2local  X  Y  :" << out_x <<" " << out_y << " " << "\n");
                    
                    }


void local2global(const double &local_x, const double &local_y,
                    const double &ref_x, const double &ref_y, const double &ref_heading,
                    double &out_x, double &out_y) {
                    
                    //将局部坐标系下的障碍物转为全局坐标系
                    double tmp_x = local_x * std::cos(ref_heading) + local_y * (-std::sin(ref_heading));;
                    double tmp_y = local_x * std::sin(ref_heading) + local_y * std::cos(ref_heading);
                    out_x = tmp_x + ref_x;
                    out_y = tmp_y + ref_y;
                    // ROS_INFO_STREAM("local2global  X  Y  :" << out_x <<" " << out_y << " " << "\n");
                    
                    }


}   //namespace map
}   //namespace smartcar