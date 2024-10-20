/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-11 16:20:08
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-09 03:46:41
 * @FilePath: /miniEV/src/simulation/simulator/src/pid.cpp
 */
#include "simulator/pid.h"

// class PID  {

// PID::PID(const double kp, const double ki, const double kd) {
//     kp_ = kp;
//     ki_ = ki;
//     kd_ = kd;
//     previous_error_ = 0.0;
//     previous_output_ = 0.0;
//     integral_ = 0.0;
//     first_hit_ = true;
// }

// double PID::Control(const double error, const double dt) {
//     if (dt <= 0) {
//         return previous_output_;
//     }
//     double diff = 0;
//     double output = 0;

//     if (first_hit_)    // first_hit_: 用来选择是否计算diff
//     {
//         first_hit_ = false;
//     } else {
//         diff = (error - previous_error_) / dt;
//     }

//     integral_ += ki_ * error * dt;    // 积分环节

//     output = kp_ * error + integral_ + diff * kd_;
//     if (output > limMax_) output = limMax_;
//     if (output < limMin_) output = limMin_;

//     previous_output_ = output;
//     previous_error_ = error;
//     return output;
// }

// void PID::Reset() {
//     previous_error_ = 0.0;
//     previous_output_ = 0.0;
//     integral_ = 0.0;
//     first_hit_ = true;
// }

// }//PathFollower