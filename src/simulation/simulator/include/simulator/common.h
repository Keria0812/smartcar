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
namespace simulator {


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


}   //namespace simulator
}   //namespace smartcar