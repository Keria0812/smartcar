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

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <nav_msgs/Path.h>
#include <map/common.h>

namespace smartcar {
namespace map {


/**
 * @brief Get the all files object
 * 
 * @param dir_in 
 * @param files 
 * @return true 
 * @return false 
 */
bool get_all_files(const std::string& dir_in, std::vector<std::string>& files) {
    if (dir_in.empty()) {
        return false;
    }
    struct stat s;
    stat(dir_in.c_str(), &s);
    if (!S_ISDIR(s.st_mode)) {
        return false;
    }
    DIR* open_dir = opendir(dir_in.c_str());
    if (NULL == open_dir) {
        std::exit(EXIT_FAILURE);
    }
    dirent* p = nullptr;
    while( (p = readdir(open_dir)) != nullptr) {
        struct stat st;
        if (p->d_name[0] != '.') {
            //因为是使用devC++ 获取windows下的文件，所以使用了 "\" ,linux下要换成"/"
            std::string name = dir_in + std::string("/") + std::string(p->d_name);
            stat(name.c_str(), &st);
            if (S_ISDIR(st.st_mode)) {
                get_all_files(name, files);
            }
            else if (S_ISREG(st.st_mode)) {
                files.push_back(name);
            }
        }
    }
    closedir(open_dir);
    return true;
}

/**
 * @brief 
 * 
 * @param files 
 */
std::vector<std::string> 
remove_erro_files(const std::vector<std::string>& files, const std::string& target_type) {
    std::vector<std::string> tmp_files;
    for (auto &file : files) {
        if (file.find(target_type) != std::string::npos) {
            tmp_files.push_back(file);
        }
    }

    return tmp_files;
}

/**
 * @brief 
 * 
 * @param filename 
 * @param scale 
 * @param waypoints 
 */
void loadWaypoints(const std::string filename, smartcar_msgs::My_Trajectory &waypoints) {

    waypoints.trajectory_points.resize(0);
    // double x, y, yaw;

    /*读取逗号分割，中间无空格
    20,30
    19,20.0这个格式*/
    // FILE *file = fopen(filename.c_str(), "rt");
    // if(file == nullptr){
    //     ROS_ERROR("no found waypoints");
    //     exit(0);
    // }
    // while(fscanf(file, "%lf,%lf", &x, &y) != EOF) {
    //     geometry_msgs::Point point;
    //     point.x = scale * x;
    //     point.y = scale * y;
    //     point.z = 0;
    //     ROS_INFO("X  %lf   Y   %lf",  point.x,  point.y);
    //     waypoints->push_back(point);
    // }
    // fclose(file);

    //读取tab分割
    // std::string input;
    // double temp1, temp2, temp3;
    // std::ifstream fin;
    // bool error = false;
    // fin.open(filename.c_str());
    // if (fin.fail()) {
    //     ROS_ERROR("no found waypoints");
    //     exit(0);
    // }
    // while(true){
    //     getline(fin,input);
    //     if (!fin) break; //check for eof
 
    //     std::istringstream buffer(input);
    //     buffer >> temp1 >> temp2 >> temp3;
 
    //     //check for non numerical input
    //     //and less/more input than needed
    //     if (!buffer || !buffer.eof())
    //     {
    //         error=true;
    //         break;
    //     }
    //     geometry_msgs::Point point;
    //     point.x = scale * temp1;
    //     point.y = scale * temp2;
    //     point.z = 0;
    //     waypoints->push_back(point);
 
    //     //do what you want with temp1 and temp2
    //     // printf("X %.3lf\tY %.3lf\tYaw %.3lf\n", temp1, temp2, temp3);
    // }
    // if (error)
    //     std::cout << "file is corrupted..." << std::endl;
    // fin.close();

    //自动获取Tab分割数据，不用指定行列
    std::ifstream fin;
    fin.open(filename);
    if (fin.fail()) {
        ROS_ERROR("no found reference line");
        exit(0);
    }
    std::string test = "";
    std::vector<std::vector<double>> tmpMyData;
    while (std::getline(fin, test))  //全局函数，隶属于<string>头文件，空行也会被读入，但流数据为空
    {
        if (test == "") continue;  //排除空行
        std::stringstream os_data(test);
        double tmp;
        std::vector<double> mydata;
        while (os_data >> tmp) {
            // ROS_INFO("into");
            // ROS_INFO("tmp: %.3f", tmp);
            mydata.push_back(tmp);
        }
        tmpMyData.push_back(mydata);
    }
    // std::cout << "MyData-row " << tmpMyData.size() << std::endl;
    // if (tmpMyData.size() > 0) {
    //     std::cout << "MyData-column " << tmpMyData[0].size() << std::endl;
    // }

    // for (int i = 0; i < tmpMyData.size(); i++) {
    //     for (int j = 0; j < tmpMyData[0].size(); j++) {
    //         std::cout << tmpMyData[i][j] << "    ";
    //     }
    //     std::cout << std::endl;
    // }

    //将读取的数据赋值给轨迹
    for (size_t i = 0; i < tmpMyData.size(); i++) {
        smartcar_msgs::My_Trajectory_Point tmp_point;
        // tmp_point.theta = tmpMyData[i][2] - tmpMyData[0][2];
        // // if (i == 0) {
        // //     tmp_point.x = tmpMyData[i][0] - tmpMyData[0][0];
        // //     tmp_point.y = tmpMyData[i][1] - tmpMyData[0][1];

        // // } else {
        // //     tmp_point.x = tmpMyData[i][0] - tmpMyData[0][0];
        // //     tmp_point.y = tmpMyData[i][1] - tmpMyData[0][1];
        // // }
        // double theta_x = tmpMyData[i][0] - tmpMyData[0][0];
        // double theta_y = tmpMyData[i][1] - tmpMyData[0][1];
        // double theta = std::atan2(theta_y, theta_x) - tmpMyData[0][2];
        // double ll = std::sqrt(theta_x * theta_x + theta_y * theta_y);
        // tmp_point.x = ll * std::cos(theta);
        // tmp_point.y = ll * std::sin(theta);

        tmp_point.x = tmpMyData[i][0];
        tmp_point.y = tmpMyData[i][1];
        tmp_point.theta = tmpMyData[i][2];
        waypoints.trajectory_points.push_back(tmp_point);
    }
    waypoints.num = static_cast<int>(tmpMyData.size()) ;

}


/**
 * @brief 
 * 
 * @param waypoints 
 * @param path 
 */
void interpolatePathNaive(const smartcar_msgs::My_Trajectory &waypoints, nav_msgs::Path &path) {
    path.poses.clear();
    path.header.frame_id = "map";
    path.header.stamp = ros::Time::now();

    for(size_t i = 0; i < waypoints.trajectory_points.size(); i++) {
        geometry_msgs::PoseStamped pose;

        pose.pose.position.x = waypoints.trajectory_points[i].x;
        pose.pose.position.y = waypoints.trajectory_points[i].y;
        
        geometry_msgs::Quaternion quat_tmp;
        quat_tmp = tf::createQuaternionMsgFromRollPitchYaw(0.0, 0.0, NormalizeAngle(waypoints.trajectory_points[i].theta));
        pose.pose.orientation = quat_tmp;

        path.poses.push_back(pose);
    }
}


}   //namespace smartcar
}   //namespace map