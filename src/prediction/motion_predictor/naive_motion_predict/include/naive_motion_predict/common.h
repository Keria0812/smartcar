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
#ifndef COMMON_H
#define COMMON_H

#include <cmath>

namespace smartcar {
namespace prediction {


/**
 * @brief limit rad [-pi, pi)
 * 
 * @param theta 
 * @return double 
 */
double NormalizeAngle(double theta);


void global2local(const double &global_x, const double &global_y, const double &global_yaw,
                    const double &ref_x, const double &ref_y, const double &ref_heading,
                    double &out_x, double &out_y, double &yaw);


void local2global(const double &local_x, const double &local_y,
                    const double &ref_x, const double &ref_y, const double &ref_heading,
                    double &out_x, double &out_y);


}   //namespace prediction
}   //namespace smartcar

#endif