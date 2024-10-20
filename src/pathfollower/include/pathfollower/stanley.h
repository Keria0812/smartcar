/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-10 15:37:51
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-01-14 22:44:47
 * @FilePath: /miniEV/src/pathfollower/include/pathfollower/stanley.h
 */
#pragma once 
#ifndef PATHFOLLOWER_STANELY_H_
#define PATHFOLLOWER_STANELY_H_

#include "pathfollower/controller.h"
#include "pathfollower/pid.h"

namespace PathFollower {

class Stanley : public Controller
{
private:
    /* data */
    double ky_ = 1.0;
    double k_ = 0.0;
    std::unique_ptr<PID>  heading_err_pid_ = std::make_unique<PID>(1.0, 0.005, 0.01, 0.57, -0.57, 0.57, -0.57);
    // std::unique_ptr<PID>  heading_err_pid_ = std::make_unique<PID>(1.0, 0.05, 0.002, 0.57, -0.57, 0.57, -0.57);
    // std::unique_ptr<PID>  heading_err_pid_ = std::make_unique<PID>(1.0, 0.1, 0.0, 0.53, -0.53, 0.53, -0.53);

public:
    Stanley(const std::string &vehicle_physical_config) : Controller(vehicle_physical_config) {};
    ~Stanley()  = default;


    bool FollowMethod(ControlCommand &cur_cmd)  override;
};

}//PathFollower
#endif //PATHFOLLOWER_STANELY_H_
