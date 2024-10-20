/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-10 15:46:51
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2023-07-22 15:48:58
 * @FilePath: /miniEV/src/pathfollower/src/stanley.cpp
 */
#include "pathfollower/stanley.h"
    double pre_steer_ = 0.0;
namespace PathFollower {

bool Stanley::FollowMethod(ControlCommand &cur_cmd)  {
    Pose cur_fwhell_pos(cur_status_.cur_pos);
    double steer_cmd = 0.0;
    // if (cur_status_.cur_pos.linear_velocity_  > 0.00001) {
        cur_fwhell_pos.point_.x = cur_status_.cur_pos.point_.x + physical_.wheel_base_ * std::cos(cur_status_.cur_pos.heading_);
        cur_fwhell_pos.point_.y = cur_status_.cur_pos.point_.y + physical_.wheel_base_ * std::sin(cur_status_.cur_pos.heading_);
        cur_fwhell_pos.point_.z = cur_status_.cur_pos.point_.z;

        const Pose& target_pos = follow_path_.poses_[this->QueryNearestPoseFromXY(follow_path_, cur_fwhell_pos)];

        if (target_pos == follow_path_.poses_.back()) {
            cur_cmd.setVehicleStop();
            return true;
        } 
        double later_err = this->calcLateralError(cur_fwhell_pos, target_pos);
        double heading_err = target_pos.heading_  - cur_fwhell_pos.heading_;
        double ed_theta = std::atan2(ky_ * later_err, cur_status_.cur_pos.linear_velocity_ + k_);
        double e_theta =  heading_err_pid_->Control(NormalizeAngle(heading_err) , 0.02);
        steer_cmd = e_theta + 0.5 * ed_theta;

        printf("The laterError is %f, Heading Error is %f ,etheta %f ed %f \n",later_err, heading_err, e_theta, ed_theta) ;
        steer_cmd = steer_cmd * physical_.steer_ratio_;
        steer_cmd = std::max(steer_cmd, -physical_.max_steering_angle_);
        steer_cmd = std::min(steer_cmd, physical_.max_steering_angle_);

        steer_cmd = steeringcmd_losspass_filter_->Filter(steer_cmd);
        // steer_cmd = steeringcmd_mean_filter_->Update(steer_cmd);
        // steer_cmd = 0.1 * steer_cmd + 0.9 * pre_steer_;
        // steer_cmd = this->steeringcmd_mean_filter_->Update(steer_cmd);
        pre_steer_ = steer_cmd;
    // }
    cur_cmd.setCommand(steer_cmd,target_velocity_, this->VelocityError2Accelerate(target_velocity_ - cur_status_.cur_pos.linear_velocity_, 0.02));


    std::cout << "The cur_vel is " << cur_status_.cur_pos.linear_velocity_ << " m/s, The target_vel is " << target_velocity_ << std::endl;

    return true;
};

}//PathFollower