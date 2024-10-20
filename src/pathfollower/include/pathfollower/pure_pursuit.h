/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-12 22:39:38
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-01-14 22:44:55
 * @FilePath: /miniEV/src/pathfollower/include/pathfollower/pure_pursuit.h
 */
#ifndef PATHFOLLOWER_PUREPURSUIT_H_
#define PATHFOLLOWER_PUREPURSUIT_H_

#include <iostream>

#include "pathfollower/common.h"
#include "pathfollower/controller.h"

namespace PathFollower {

class PurePursuit : public Controller
{
    private: 

        double lookahead_dis_base_ = 4.0;
        double Max_lookahead_dis_ = 10.0;
        double Min_lookahead_dis_ = 4.0;

        double k_vel_4lookahead_ = 0.0;
        double k_kappa_4lookahead_ = 0.0;

        double getLookaheadDistance(const double cur_linear_vel_, const double cur_path_kappa) const;

        size_t QueryLookaheadPoseFromXY(const Trajectory &path, size_t nearest_index, double lookahead_distance) const;

    public:
        PurePursuit(const std::string &vehicle_physical_config) : Controller(vehicle_physical_config) {};
        ~PurePursuit() = default;


        bool FollowMethod(ControlCommand &cur_cmd) override;
};

}//PathFollower
#endif //PATHFOLLOWER_PUREPURSUIT_H_