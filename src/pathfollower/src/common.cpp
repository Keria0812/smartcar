/*rpy_.x 这个文件定义了轨迹跟踪需要的类，比如说pose等
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-11 14:05:12
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2023-06-13 13:14:22
 * @FilePath: /miniEV/src/pathfollower/src/common.cpp
 */
#include "pathfollower/common.h"

namespace PathFollower {

bool Pose::operator==(const Pose& pose) const {
    if (point_.x != pose.point_.x || point_.y != pose.point_.y) return false;
    return true;
};

double Pose::getDistanceFromXY(const Pose & next_pos) const {
    return  std::hypot(this->point_.x - next_pos.point_.x, this->point_.y - next_pos.point_.y);
};
void Pose::Quaternion2EulerAgnle(const geometry_msgs::Quaternion& orientation) {
    tf::Quaternion q;
    tf::quaternionMsgToTF(orientation, q);// 将朝向转换为四元数类型
    tf::Matrix3x3(q).getRPY(rpy_.x, rpy_.y, rpy_.z);// 将四元数转换为欧拉角，并存储到 Pose 对象的 rpy_ 向量中
};

bool Trajectory::updateTrajectory(const geometry_msgs::PoseArray &follow_path,  std::mutex &path_mutex) {
    poses_.clear(); // 清空之前的轨迹
    poses_.reserve(follow_path.poses.size());
    {
        std::lock_guard<std::mutex> _guard(path_mutex);
        if (follow_path.poses.empty()) // 如果输入为空，则返回 false
        {
            std::cerr << "The Path is empty............" << std::endl;
            return false;
        }    

        for (const auto &pose_msg : follow_path.poses) {
            Pose pose;
            pose.point_.x = pose_msg.position.x; // 将 x 坐标赋值给 Pose 对象的 point_ 的第一个元素
            pose.point_.y = pose_msg.position.y; // 将 y 坐标赋值给 Pose 对象的 point_ 的第二个元素
            pose.point_.z = pose_msg.position.z; // 将 z 坐标赋值给 Pose 对象的 point_ 的第三个元素
            // pose.Quaternion2EulerAgnle(pose_msg.orientation);
            poses_.push_back(pose); // 将 Pose 对象存储到 poses_ 向量中
        }
    }

    this->calcTrajectoryYawFromXY();
    this->calcTrajectoryCurvature(15);

    return true; // 轨迹更新成功，返回 true
};

bool Trajectory::calcTrajectoryYawFromXY() {
    if (poses_.size() < 3) // 如果轨迹为空，则返回
    {
        std::cerr << "The Path is too short............" << std::endl;
        return false;
    }    

    for (int i = 0; i < poses_.size(); ++i) {
        auto &cur_pose = poses_[i];
        if (i == 0) { // 当前位姿是第一个位姿点
            double dx = poses_[1].point_.x - cur_pose.point_.x;
            double dy = poses_[1].point_.y - cur_pose.point_.y;
            cur_pose.heading_ = std::atan2(dy, dx); // 使用相邻两个位姿点的坐标信息计算偏航角
        } else if (i == poses_.size() - 1) { // 当前位姿是最后一个位姿点
            double dx = cur_pose.point_.x - poses_[poses_.size() - 2].point_.x;
            double dy = cur_pose.point_.y - poses_[poses_.size() - 2].point_.y;
            cur_pose.heading_ = std::atan2(dy, dx); // 使用相邻两个位姿点的坐标信息计算偏航角
        } else { // 当前位姿是中间的位姿点
            double dx = poses_[i + 1].point_.x - poses_[i - 1].point_.x;
            double dy = poses_[i + 1].point_.y - poses_[i - 1].point_.y;
            cur_pose.heading_ = std::atan2(dy, dx); // 使用相邻两个位姿点的坐标信息计算偏航角
        }
    }
    return true;
};

bool Trajectory::calcTrajectoryCurvature(int smooth_num) {
    if (poses_.size() < 2*smooth_num)
      return false;

    // 计算第一个和最后一个位姿点的曲率
    poses_.front().kappa_ = calcPoseCurvature(poses_[0], poses_[1], poses_[2]);
    poses_.back().kappa_ =
        calcPoseCurvature(poses_[poses_.size() - 3], poses_[poses_.size() - 2],
                          poses_[poses_.size() - 1]);

    // 计算中间的位姿点的曲率
    for (size_t i = smooth_num; i < poses_.size() - smooth_num; ++i) {
      poses_[i].kappa_ = calcPoseCurvature(poses_[i - smooth_num], poses_[i], poses_[i + smooth_num]);
    }

    for (size_t i = 0; i < smooth_num; ++i) {
        poses_[i].kappa_ = poses_[smooth_num].kappa_;
        poses_[i+poses_.size() - smooth_num].kappa_ = poses_[poses_.size() - smooth_num-1].kappa_;
    }
    return true;
};

double Trajectory::calcPoseCurvature(const Pose& prev_pose, const Pose& curr_pose,
                            const Pose& next_pose) {
    // 计算当前位姿点的前进方向和后退方向
    double kappa = 0.0;
    double den = std::max(prev_pose.getDistanceFromXY(curr_pose) * curr_pose.getDistanceFromXY(next_pose) * next_pose.getDistanceFromXY(prev_pose), 1e-10);
    kappa = 2.0 * ((curr_pose.point_.x - prev_pose.point_.x) * (next_pose.point_.y - prev_pose.point_.y)
                     - (curr_pose.point_.y - prev_pose.point_.y) *( next_pose.point_.x - prev_pose.point_.x)) / den;
    // 计算当前位姿点的曲率
    // kappa = 1.0 / radius;

    return kappa;
}

}//PathFollower