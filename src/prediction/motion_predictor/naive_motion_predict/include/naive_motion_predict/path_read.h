/**
 * @file path_read.h
 * @author your name (you@domain.com)
 * @brief 读取轨迹文件
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef PATH_READ_H
#define PATH_READ_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <nav_msgs/Path.h>
#include <naive_motion_predict/common.h>
#include <smartcar_msgs/My_Trajectory.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ros/ros.h>
#include <tf/tf.h>

namespace smartcar {
namespace prediction {


/**
 * @brief Get the all files object
 * 
 * @param dir_in 
 * @param files 
 * @return true 
 * @return false 
 */
bool get_all_files(const std::string& dir_in, std::vector<std::string>& files);

/**
 * @brief 
 * 
 * @param files 
 */
std::vector<std::string> 
remove_erro_files(const std::vector<std::string>& files, const std::string& target_type);

/**
 * @brief 
 * 
 * @param filename 
 * @param scale 
 * @param waypoints 
 */
void loadWaypoints(const std::string filename, smartcar_msgs::My_Trajectory &waypoints);

void read_csv(const std::string filename, smartcar_msgs::My_Trajectory &waypoints);

/**
 * @brief 
 * 
 * @param waypoints 
 * @param path 
 */
void interpolatePathNaive(const smartcar_msgs::My_Trajectory &waypoints, nav_msgs::Path &path);


}   //namespace prediction
}   //namespace smartcar

#endif