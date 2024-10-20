/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-12 22:42:11
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-27 18:52:50
 * @FilePath: /miniEV_grad/src/pathfollower/src/pure_pursuit.cpp
 */
#include "pathfollower/pure_pursuit.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

namespace PathFollower {


double PurePursuit::getLookaheadDistance(const double cur_linear_vel_, const double cur_path_kappa) const {
    return std::max (lookahead_dis_base_ , cur_status_.cur_pos.linear_velocity_);
    // return std::max (lookahead_dis_base_ , this->cur_chassis_.speed/3.6);

    // return 1.0/36.0 * this->cur_status_.speed* this->cur_status_.speed + 1.0/30.0 * this->cur_status_.speed + this->physical_.min_radius_turn_;
    // return lookahead_dis_base_ + k_vel_4lookahead_ * cur_linear_vel_ + k_kappa_4lookahead_ * (1.0 / (std::fabs(cur_path_kappa) + 1.0e-10));
};

size_t PurePursuit::QueryLookaheadPoseFromXY(const Trajectory &path, size_t nearest_index, double lookahead_distance) const {
    size_t lookahead_index = nearest_index + 1;
    while (lookahead_index < path.poses_.size() && cur_status_.cur_pos.getDistanceFromXY(path.poses_[lookahead_index++]) < lookahead_distance);
    return lookahead_index;
};

bool PurePursuit::FollowMethod(ControlCommand &cur_cmd)  {




    std::cout << cur_status_.cur_pos.point_.x << " " << cur_status_.cur_pos.point_.y  << std::endl;
    size_t nearest_index  = this->QueryNearestPoseFromXY(follow_path_,cur_status_.cur_pos);
    const Pose& nearest_pos = follow_path_.poses_[nearest_index];
    double lookahead_distance = this->getLookaheadDistance(cur_status_.cur_pos.linear_velocity_, nearest_pos.kappa_);
    size_t lookahead_index = this->QueryLookaheadPoseFromXY(follow_path_, nearest_index, lookahead_distance);

    double ed = this->calcLateralError(cur_status_.cur_pos, nearest_pos);
    double ephi = NormalizeAngle(nearest_pos.heading_ - cur_status_.cur_pos.heading_);
    // double ed_dot = cur_status_.cur_pos.linear_velocity_ * std::sin(ephi);
    // double ephi_dot = cur_status_.rpy_rate.z - nearest_pos.kappa_ * cur_vx;
    ROS_INFO("The ed is %f , ephi is %f \n", ed, ephi);

    
    const Pose& lookahead_pos = follow_path_.poses_[lookahead_index];
    if (lookahead_pos == follow_path_.poses_.back() && lookahead_pos.getDistanceFromXY(follow_path_.poses_.back()) < lookahead_dis_base_) {
        cur_cmd.setVehicleStop();
        return true;
    } 

    double ld = cur_status_.cur_pos.getDistanceFromXY(lookahead_pos);

    double tmpx = (lookahead_pos.point_.x - cur_status_.cur_pos.point_.x) * std::cos(cur_status_.cur_pos.heading_) 
            + (lookahead_pos.point_.y - cur_status_.cur_pos.point_.y) * std::sin(cur_status_.cur_pos.heading_);
    double tmpy = (lookahead_pos.point_.x - cur_status_.cur_pos.point_.x) * std::sin(cur_status_.cur_pos.heading_) 
            - (lookahead_pos.point_.y - cur_status_.cur_pos.point_.y) * std::cos(cur_status_.cur_pos.heading_);
    double alpha = -std::atan2(tmpy, tmpx);//车身坐标系的原因

    double kappa = 2 * std::sin(alpha) / ld;
    printf("The VehicleWheelbase is %f m, the path kappa is %f , lookahead_distance is %f ,\n", physical_.wheel_base_, kappa, ld);
    printf("The VehicleVel is %f m/s, the targetheading is %f , heading is %f ,\n", cur_status_.cur_pos.linear_velocity_, target_velocity_, cur_status_.cur_pos.heading_ * 57.3);

    double front_wheel_angle = std::atan(kappa * physical_.wheel_base_);
    double steering_angle = front_wheel_angle * physical_.steer_ratio_;
    
    

    steering_angle = std::max(steering_angle, -physical_.max_steering_angle_);
        steering_angle = std::min(steering_angle, physical_.max_steering_angle_);
    // std::ofstream outputFile("/home/jinxiaoxin/master_graduation/grad/miniEV_grad/pathfollower.txt",std::ios_base::app); // 打开一个名为 output.txt 的文件用于写入

    // if (outputFile.is_open()) {
    // // 获取当前时间
    //      // 获取当前时间的毫秒级表示
    //     auto now = std::chrono::system_clock::now();
    //     auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    //     auto since_epoch = ms.time_since_epoch();
    //     auto current_ms = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch).count();

    //     // 将值和时间写入文件
    //     outputFile << current_ms << '\t' <<   cur_status_.cur_pos.point_.x <<  '\t' <<   cur_status_.cur_pos.point_.y ;
    //     outputFile << '\t' <<   ed << "\t" << ephi << '\t'
    //      << steering_angle << '\t' << cur_chassis_.feedback_steering_angle 
    //      << '\t' << cur_status_.speed  << '\t' << cur_status_.linear_acc.x << std::endl;

    //     // 关闭文件
    //     outputFile.close();
    // } else {
    //     std::cerr << "Failed to open the file." << std::endl;
    // }
    cur_cmd.setCommand(steering_angle, target_velocity_, this->VelocityError2Accelerate(target_velocity_ - cur_status_.cur_pos.linear_velocity_, 0.02));

    return true;
};

}//PathFollower