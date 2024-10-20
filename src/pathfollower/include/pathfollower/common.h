/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-09 21:28:59
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2023-06-17 19:25:06
 * @FilePath: /miniEV/src/pathfollower/include/pathfollower/common.h
 */
#pragma once 
#ifndef PATHFOLLOWER_COMMON_H_
#define PATHFOLLOWER_COMMON_H_

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <mutex>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <tf/transform_datatypes.h>
#include <tf/tf.h>

namespace PathFollower {

// typedef std::array<double, 3> Vector3;//xyz,右手系，roll, pitch, yaw
struct Vector3 {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};



class Pose
{
    public:

        Vector3 point_;//xyz,右手系
        Vector3 rpy_;//roll, pitch, yaw,右手系
        // Vector3 velocity_;
        // Vector3 angular_vel_;
        double heading_ = 0.0;//[-pi,pi]，X轴往右为正，Y轴往上为正
        double kappa_ = 0.0;
        double linear_velocity_ = 0.0;
        // double angvel_ = 0.0;
        Pose() = default;
        double getDistanceFromXY(const Pose & next_pos) const;
        void Quaternion2EulerAgnle(const geometry_msgs::Quaternion& oriaternion);

        bool operator==(const Pose& pose) const;
        bool operator!=(const Pose& pose) const {return *this == pose;};

    /* data */
};


class Trajectory 
{
    public:
        std::vector<Pose> poses_;
        bool updateTrajectory(const geometry_msgs::PoseArray &follow_path, std::mutex &path_mutex);
        bool calcTrajectoryYawFromXY();
        bool calcTrajectoryCurvature(int smooth_num);

    private:
        double calcPoseCurvature(const Pose& prev_pose, const Pose& curr_pose,
                                const Pose& next_pose);
};


inline double NormalizeAngle(double theta) {
    auto n = (int)(theta / (2 * M_PI));
    theta -= n * (2 * M_PI);
    if (theta >= M_PI) {
        theta -= 2 * M_PI;
    }
    if (theta < -M_PI) {
        theta += 2 * M_PI;
    }
    
    return theta;
}

}//PathFollower
#endif //PATHFOLLOWER_COMMON_H_