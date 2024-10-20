/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-12 22:39:38
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-22 19:41:15
 * @FilePath: /miniEV_grad/src/pathfollower/include/pathfollower/manual_control.h
 */
#ifndef PATHFOLLOWER_MANUALCONTROL_H_
#define PATHFOLLOWER_MANUALCONTROL_H_

#include <iostream>
#include <chrono>

#include "pathfollower/common.h"
#include "pathfollower/controller.h"

namespace PathFollower {


class ControlSignal {
    private:
        double amplitude_ = 0.0;//振幅
        double period_ = 0.0;//周期
        double phase_ = 0.0;//相位差
        double offset_ = 0.0;//振幅偏移
        bool first_hit_ = true;
        // int cur_step = 0;
        // double sample_time = 0.02;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_signal_;
        std::chrono::time_point<std::chrono::high_resolution_clock> end_signal_;
        double getCurSampleTime();//s
          
    public:
        //振幅、周期、相位差、振幅偏移量,调整2，最终目标是三个周期，实验速度0-100km/h，中途不能超过100，最后要接近100,加速度不超过2.5，减速度不超过3.0
        //只调周期现在
        //有坡度时加速度最大2.0，减速度最大2.0，基值由2.25改到1.75
        ControlSignal(double _amplitude, double _period, double _phase = 0.0, double _offset = 0.0) 
        : amplitude_(_amplitude),  period_(_period), phase_(_phase), offset_(_offset) {};
        double SinusoidalSignal();
        double SquareSignal();
        double SlopeSignal();
};


class ManualControl : public Controller
{
    private: 

        // ControlSignal* manual_acc = new ControlSignal(1.0, 1.85 * M_PI, 0.0, 0.5);//设置这个调整上面的四个值，调波形，几种波型都能用
        //ControlSignal* manual_acc = new ControlSignal(1.75, 4.21 * M_PI, 0.0, 0.25);//设置这个调整上面的四个值，调波形，几种波型都能用

        //速度实验时是m/s
        // ControlSignal* manual_acc = new ControlSignal(22.778/2.0, 20.0 * M_PI, 0.0, 22.778/2.0 + 5.0);//目标是两个周期30s以内，拟合很好
        //假设匀加速度2.5,目标速度27.778， 算法最小上升时间为11.11秒，周期最小44.44s，所以速度跟踪的实验时间不做过分限制，调整周期以包含两个周期即可
        // 在跟踪良好的情况下尽量缩短周期，目前20Pi跟踪良好，在15-20间简单调几下即可
        // ControlSignal* manual_acc = new ControlSignal(22.778/2.0, 15 * M_PI, -M_PI / 2.0, 22.778/2.0 + 5.0);//目标是两个周期30s以内，拟合很好
        ControlSignal* manual_acc = new ControlSignal(15.0/3.6, 18 * M_PI, -M_PI / 2.0, 25.0/3.6 );//目标是两个周期30s以内，拟合很好


    public:
        ManualControl(const std::string &vehicle_physical_config) : Controller(vehicle_physical_config) {};
        ~ManualControl() = default;

        bool FollowMethod(ControlCommand &cur_cmd) override;
};

}//PathFollower
#endif //PATHFOLLOWER_MANUALCONTROL_H_