/*sin/loop，窗型信号
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-12 22:42:11
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-09 04:16:04
 * @FilePath: /miniEV/src/pathfollower/src/manual_control.cpp
 */
#include "pathfollower/manual_control.h"

namespace PathFollower {

double ControlSignal::getCurSampleTime() {
    if (first_hit_) {
        start_signal_ = std::chrono::high_resolution_clock::now();
        first_hit_ = false;
        return 0.0;
    }
    end_signal_ = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> cost_time = end_signal_ - start_signal_;//ms
    return cost_time.count() / 1000.0;
    // std::cout << "The ControlMethod cost time is: " << cost_time.count() << " ms" << std::endl;
}

double ControlSignal::SinusoidalSignal() {
    double cur_sample_t = this->getCurSampleTime();
    return amplitude_ * std::sin(2 * M_PI / period_ * cur_sample_t + phase_) + offset_;
}

double ControlSignal::SquareSignal() {
    double cur_sample_t = this->getCurSampleTime();
    double cur_sin = std::sin(2 * M_PI / period_ * cur_sample_t + phase_);
    if (cur_sin > 0.0) cur_sin = 1.0;
    else if (cur_sin < 0.0) cur_sin = -1.0;
    else cur_sin = 0.0;
    return amplitude_ * cur_sin + offset_;
}
double ControlSignal::SlopeSignal() {
    double prev_time = period_ / 6.0;
    double cur_sample_t = this->getCurSampleTime();
    int cur_state = (int)(cur_sample_t / prev_time);
    double ans = 0.0;
    switch (cur_state % 6)
    {
    case 0:
    {
        double cur_time = cur_sample_t - cur_state * prev_time;
        ans = cur_time * amplitude_  / prev_time;
        break;
    }
    case 1:
    {
        ans = amplitude_;
        break;
    }
    case 2:
    {
        double cur_time = cur_sample_t - cur_state * prev_time;
        ans = amplitude_ - cur_time * amplitude_  / prev_time;
        break;
    }
    case 3:
    {
        double cur_time = cur_sample_t - cur_state * prev_time;
        ans = - cur_time * amplitude_  / prev_time;
        break;
    }
    case 4:
    {
        ans = -amplitude_;
        break;
    }
    case 5:
    {
        double cur_time = cur_sample_t - cur_state * prev_time;
        ans = -amplitude_ + cur_time * amplitude_  / prev_time;
        break;
    }
    default:
        break;
    }
    return ans + offset_;
}

bool ManualControl::FollowMethod(ControlCommand &cur_cmd)  {
    double steering_angle = 0.0;
    // double acc = this->manual_acc->SquareSignal();//几种信号，改完要编译，不打开main文件的注释的两行（mpc，lon）的时候能穿过去。
    //起始速度40，周期3.06效果最好，三个周期
    //po 3.46
    //vel 15 yiyangde xianzhitiaojiandoushijiasudu
    // double acc = this->manual_acc->SinusoidalSignal();
    ////起始速度40，周期3.96效果最好，三个周期
    //po 4.30
    //vel 12 round3
    // double acc = this->manual_acc->SlopeSignal();
    //起始速度40，周期3.87效果最好，三个周期
    //po 4.21
    // acc = 0.0;
    //vel 15 dengyihui
    // cur_cmd.setCommand(steering_angle, target_velocity_, acc);//速度实验的时候，tarxxx改成信号中的一个，acc改成0
    cur_cmd.setCommand(steering_angle, this->manual_acc->SlopeSignal(), 0);//速度实验的时候，tarxxx改成信号中的一个，acc改成0
    return true;
};

}//PathFollower