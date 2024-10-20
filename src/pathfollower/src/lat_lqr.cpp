/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-14 18:57:40
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-22 22:40:09
 * @FilePath: /miniEV_grad/src/pathfollower/src/lat_lqr.cpp
 */
#include "pathfollower/lat_lqr.h"

#include <assert.h>

namespace PathFollower {

LatLQR::LatLQR(const std::string &vehicle_physical_config_path, const std::string &lqr_param_config_path) : Controller(vehicle_physical_config_path) {
    assert(this->initConfigParameters(lqr_param_config_path));
    
    constexpr double lat = 0.1;
    constexpr double phi = 1.0;


    Interpolation1D::DataType xy1, xy2;
    // xy1.push_back(std::make_pair(4, 0.4 / lat));
    // xy1.push_back(std::make_pair(8, 0.3 / lat));
    // xy1.push_back(std::make_pair(13.8, 0.25 / lat));
    // xy1.push_back(std::make_pair(20, 0.1 / lat));
    // xy1.push_back(std::make_pair(25, 0.08 / lat));
    xy1.push_back(std::make_pair(4, 1));
    xy1.push_back(std::make_pair(8, 0.6));
    xy1.push_back(std::make_pair(12, 0.2));
    xy1.push_back(std::make_pair(20, 0.1));
    xy1.push_back(std::make_pair(25, 0.05));

    xy2.push_back(std::make_pair(4, 0.8 / phi));
    xy2.push_back(std::make_pair(8, 0.4 / phi));
    xy2.push_back(std::make_pair(12, 0.2 / phi));
    xy2.push_back(std::make_pair(20, 0.1 / phi));
    xy2.push_back(std::make_pair(25, 0.05 / phi));

    this->lat_err_interpolation_.reset(new Interpolation1D);
    this->lat_err_interpolation_->Init(xy1);
    this->heading_err_interpolation_.reset(new Interpolation1D);
    this->heading_err_interpolation_->Init(xy2);
};

bool LatLQR::FollowMethod(ControlCommand &cur_cmd)  {

    //VehicleParameters
    double wheelbase = physical_.wheel_base_; 
    double steer_ratio = physical_.steer_ratio_;
    double max_frontwheel_angle = physical_.max_steering_angle_ / physical_.steer_ratio_; //%前轮最大转角, 单位rad /apollo 53, old 30
    double max_frontwheel_speed = physical_.max_steering_speed_ / physical_.steer_ratio_;               //%前轮最大角速度, 单位rad/s
    double max_lon_acc = physical_.max_lon_acceleration_;                                                          //%车辆最大加速度,m/s^2
    double max_lat_acceleration = 3.0;
    //设置LQR的参数，参数不对方向盘抖动会比较厉害
    double cf = physical_.cf_;      //%前轮侧偏刚度(cornering stiffness)  ，两个轮的侧偏刚度合并为一个
    double cr = physical_.cr_;      //%后轮侧偏刚度
    // double mass_front = 890; //估算：整备1570 + 人员：60*2 + 设备： 50 = 1740 1740/2 = 870
    // double mass_rear = 850;  //tesla 1064 1043
    // double mass = mass_front + mass_rear;
    // double lf = wheelbase * (1.0 - mass_front / mass);     //%前悬长度
    // double lr = wheelbase * (1.0 - mass_rear / mass);      //%后悬长度
    double mass = physical_.mass_;
    double lf = physical_.lf_;
    double lr = physical_.lr_;
    double mass_front = physical_.front_mass_;
    double mass_rear = physical_.rear_mass_;
    double iz = physical_.iz_;
    Pose lqr_pos(cur_status_.cur_pos);//重心点

    lqr_pos.point_.x = lqr_pos.point_.x + physical_.lr_ * std::cos(lqr_pos.heading_);
    lqr_pos.point_.y = lqr_pos.point_.y + physical_.lr_ * std::sin(lqr_pos.heading_);

    double cur_frontwheel_angle = cur_chassis_.feedback_steering_angle / physical_.steer_ratio_;

    double cur_speed = cur_status_.speed;
    // double cur_speed = cur_chassis_.speed;

    double cur_heading = cur_status_.cur_pos.rpy_.z;
    double cur_heading_rate = cur_status_.rpy_rate.z;
    double cur_vx = cur_status_.linear_vel.x;
    double cur_vy = cur_status_.linear_vel.y;

    double tolerance = 0.01;
    //predict_module
    double pred_ts = 0.02;
    Pose pred_pos(lqr_pos);
    pred_pos.point_.x = lqr_pos.point_.x + cur_vx * pred_ts * std::cos(cur_heading) - cur_vy * pred_ts * std::sin(cur_heading);
    pred_pos.point_.y = lqr_pos.point_.y + cur_vy * pred_ts * std::cos(cur_heading) + cur_vx * pred_ts * std::sin(cur_heading);
    double pred_phi = cur_heading + cur_heading_rate * pred_ts;
    double pred_vx = cur_vx;
    double pred_vy = cur_vy;
    double pred_phi_dot = cur_heading_rate;

    

    //update——matrix_ad
    matrix_a_(1, 1) = matrix_a_coeff_(1, 1) / (cur_speed + 1.0e-10);
    matrix_a_(1, 3) = matrix_a_coeff_(1, 3) / (cur_speed + 1.0e-10);
    matrix_a_(3, 1) = matrix_a_coeff_(3, 1) / (cur_speed + 1.0e-10);
    matrix_a_(3, 3) = matrix_a_coeff_(3, 3) / (cur_speed + 1.0e-10);

    MatrixXd matrix_i = MatrixXd::Identity(basic_state_size_, basic_state_size_);
    matrix_ad_ = (matrix_i - Ts_ * 0.5 * matrix_a_).inverse() * (matrix_i + Ts_ * 0.5 * matrix_a_);//可考虑三种方法，前向欧拉。中点欧拉，后向欧拉

    Eigen::MatrixXd matrix_k = MatrixXd::Zero(1, basic_state_size_);

    matrix_q_updated_(0, 0) =
            matrix_q_(0, 0) * lat_err_interpolation_->Interpolate(
                                 std::fabs(cur_speed));
    matrix_q_updated_(2, 2) =
        matrix_q_(2, 2) * heading_err_interpolation_->Interpolate(
                                std::fabs(cur_speed));
    // if (cur_speed < 12.0) {
    //     matrix_q_updated_(0, 0) = 0.05;
    // } else if (cur_speed < 14.0) {
    //     matrix_q_updated_(0, 0) = 0.02;
    // } else {
    //     matrix_q_updated_(0, 0) = 0.01;
    // }
    std::cout << matrix_q_updated_ << std::endl;
    // printf("%f\n", cur_speed);
    // this->SolveLQRProblem(matrix_ad_, matrix_bd_, matrix_q_, matrix_r_, tolerance, max_iteration_, &matrix_k);
    this->SolveLQRProblem(matrix_ad_, matrix_bd_, matrix_q_updated_, matrix_r_, tolerance, max_iteration_, &matrix_k);

    //update_state
    //min_pos
    size_t nearest_index = this->QueryNearestPoseFromXY(this->follow_path_, pred_pos);
    // size_t nearest_index = this->QueryNearestPoseFromXY(this->follow_path_, cur_status_.cur_pos);

    const Pose nearest_pos = this->follow_path_.poses_[nearest_index];

    double ed = this->calcLateralError(pred_pos, nearest_pos);
    double ephi = NormalizeAngle(nearest_pos.heading_ - pred_phi);
    double ed_dot = cur_vx * std::sin(ephi);
    double ephi_dot = pred_phi_dot - nearest_pos.kappa_ * cur_vx;
    ROS_INFO("The ed is %f , ephi is %f \n", ed, ephi);

    ed = lateral_error_filter_.Update(ed);
    ephi = heading_error_filter_.Update(ephi);
    ed_dot = lateralRate_error_filter_.Update(ed_dot);
    ephi_dot = headingRate_error_filter_.Update(ephi_dot);
    
    matrix_state_(0, 0) = ed;
    matrix_state_(1, 0) = ed_dot;
    matrix_state_(2, 0) = ephi;
    matrix_state_(3, 0) = ephi_dot;

    // ROS_INFO("The ed is %f , ephi is %f \n", ed, ephi);

    const double kv =
    lr * mass / 2 / cf / wheelbase - lf * mass / 2 / cr / wheelbase;
    double cur_max_kappa = 0.0;
    for (auto &pos : this->follow_path_.poses_) {
        cur_max_kappa = std::max(cur_max_kappa, pos.kappa_);
    }
    cur_max_kappa = this->curvature_filter_.Update(cur_max_kappa);
    target_velocity_ = std::min(std::fabs(0.03 / cur_max_kappa / 3.6) , target_velocity_);

    ROS_INFO("The nearest_pos.kappa_ is %f , target_velocity_ is %f \n", nearest_pos.kappa_, target_velocity_);

    double forword_angle =
        wheelbase * nearest_pos.kappa_ + kv * cur_speed * cur_speed * nearest_pos.kappa_ -
         matrix_k(0, 2) *
             (lr * nearest_pos.kappa_ -
              lf * mass * cur_speed * cur_speed * nearest_pos.kappa_ / 2 / cr / wheelbase);
    double steer_angle = (matrix_k * matrix_state_)(0, 0) + forword_angle ;
    
    double steering_angle = steer_angle * physical_.steer_ratio_;
    steering_angle = std::max(steering_angle, -physical_.max_steering_angle_);
    steering_angle = std::min(steering_angle, physical_.max_steering_angle_);
    // steering_angle = this->steeringcmd_mean_filter_->Update(steering_angle);
    steering_angle = 0.8 * steering_angle + 0.2 * pre_steer_;
    // steering_angle = steeringcmd_losspass_filter_->Filter(steering_angle);
    pre_steer_ = steering_angle;
    cur_cmd.setCommand(steering_angle, target_velocity_, this->VelocityError2Accelerate(target_velocity_ - cur_status_.cur_pos.linear_velocity_, 0.02));
    return true;
};

bool LatLQR::SolveLQRProblem (const MatrixXd &A, const MatrixXd &B, const MatrixXd &Q,
                     const MatrixXd &R, const double tolerance,
                     const uint max_num_iteration, MatrixXd *ptr_K) {
    if (A.rows() != A.cols() || B.rows() != A.rows() || Q.rows() != Q.cols() ||
      Q.rows() != A.rows() || R.rows() != R.cols() || R.rows() != B.cols()) {
        std::cout << "LQR solver: one or more matrices have incompatible dimensions.";
        return false;
    }

    MatrixXd AT = A.transpose();
    MatrixXd BT = B.transpose();

    // Solves a discrete-time Algebraic Riccati equation (DARE)
    // Calculate Matrix Difference Riccati Equation, initialize P and Q
    MatrixXd P = Q;
    uint num_iteration = 0;
    double diff = std::numeric_limits<double>::max();
    while (num_iteration++ < max_num_iteration && diff > tolerance) {
        MatrixXd P_next =
            AT * P * A - AT * P * B * (R + BT * P * B).inverse() * BT * P * A + Q;
        // check the difference between P and P_next
        diff = fabs((P_next - P).maxCoeff());
        P = P_next;
    }

    if (num_iteration >= max_num_iteration) {
         std::cout << "LQR solver cannot converge to a solution, "
                 "last consecutive result diff. is:"
              << diff << std::endl; 
        *ptr_K = (R + BT * P * B).inverse() * BT * P * A;
        return false;
    } else {
        std::cout << "LQR solver converged at iteration: " << num_iteration
               << ", max consecutive result diff.: " << diff << std::endl;
    }
    *ptr_K = (R + BT * P * B).inverse() * BT * P * A;
    return true;
};

bool LatLQR::initConfigParameters(const std::string &lqr_param_config_path) {
    YAML::Node config = YAML::LoadFile(lqr_param_config_path);
    bool init = true;
    //缺少关键词，则赋值为-1.0，便于后面检查
    this->matrix_q0_ = config["matrix_q0"] ? config["matrix_q0"].as<double>() : -1.0;
    this->matrix_q1_ = config["matrix_q1"] ? config["matrix_q1"].as<double>() : -1.0;
    this->matrix_q2_ = config["matrix_q2"] ? config["matrix_q2"].as<double>() : -1.0;
    this->matrix_q3_ = config["matrix_q3"] ? config["matrix_q3"].as<double>() : -1.0;
    this->max_iteration_ = config["max_iteration"] ? config["max_iteration"].as<int>() : -1.0;

    this->Ts_ = config["Ts"] ? config["Ts"].as<double>() : -1.0;

    if (this->matrix_q0_ < -0.01 || this->matrix_q1_ < -0.01 || this->matrix_q2_ < -0.01 || this->matrix_q3_ < -0.01 || this->Ts_ < -0.01) {
        fprintf(stderr, "The LQR init unsuccessfully! \n");
        init = false;
        return false;
    }
    //转动惯量
    
    double matrix_size = this->basic_state_size_ + this->preview_window_;
    this->matrix_q_ = MatrixXd::Zero(matrix_size, matrix_size);
    this->matrix_q_(0,0)= this->matrix_q0_;
    this->matrix_q_(1,1)= this->matrix_q1_;
    this->matrix_q_(2,2)= this->matrix_q2_;
    this->matrix_q_(3,3)= this->matrix_q3_;
    this->matrix_q_updated_ = this->matrix_q_;

    this->matrix_r_ = MatrixXd::Identity(1, 1);
    // this->matrix_r_(0, 0) = 10;

    this->matrix_a_ = MatrixXd::Zero(basic_state_size_, basic_state_size_);
    this->matrix_a_coeff_ = MatrixXd::Zero(basic_state_size_, basic_state_size_);
    this->matrix_ad_ = MatrixXd::Zero(basic_state_size_, basic_state_size_);

    this->matrix_state_ = MatrixXd::Zero(basic_state_size_, 1);
    double mass = physical_.mass_;
    double cf = physical_.cf_;
    double cr = physical_.cr_;
    double lf = physical_.lf_;
    double lr = physical_.lr_;
    double iz = physical_.iz_;
    //初始化常数项
    this->matrix_a_(0, 1) = 1.0;
    this->matrix_a_(1, 2) = (2*cf + 2*cr) / mass;
    this->matrix_a_(2, 3) = 1.0;
    this->matrix_a_(3, 2) = (2 * cf * lf - 2 * cr * lr) / iz;

    //复制需要速度
    this->matrix_a_(1, 1) = -(2*cf + 2*cr) / mass ;
    this->matrix_a_(1, 3) = -(2*cf*lf  - 2*cr*lr) / mass ;
    this->matrix_a_(3, 1) = -(2*cf*lf  - 2*cr*lr) / iz ;
    this->matrix_a_(3, 3) = -(2*cf*lf*lf  + 2*cr*lr*lr ) / iz;
    
    //matrix_a_coeff_
    this->matrix_a_coeff_ = this->matrix_a_;
    this->matrix_b_ = MatrixXd::Zero(basic_state_size_, 1);
    this->matrix_bd_ = MatrixXd::Zero(basic_state_size_, 1);

    this->matrix_b_(1, 0) = 2*cf / mass;
    this->matrix_b_(3, 0) = 2*cf*lf / iz;

    this->matrix_bd_ = this->matrix_b_ * this->Ts_;

    return true;
};


}//PathFollower