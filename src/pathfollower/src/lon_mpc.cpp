/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-14 18:57:40
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-27 04:03:41
 * @FilePath: /miniEV_grad/src/pathfollower/src/lon_mpc.cpp
 */
#include "pathfollower/lon_mpc.h"

#include <assert.h>

double prev_acc = 0.0;
double prev_acc_cmd = 0.0;

namespace PathFollower {

LonMPC::LonMPC(const std::string &vehicle_physical_config_path, const std::string &lqr_param_config_path) : Controller(vehicle_physical_config_path) {
    assert(this->initConfigParameters(lqr_param_config_path));
    

    Interpolation1D::DataType xy1, xy2;
    xy1.push_back(std::make_pair(4, 1));
    xy1.push_back(std::make_pair(8, 0.6));
    xy1.push_back(std::make_pair(12, 0.2));
    xy1.push_back(std::make_pair(20, 0.1));
    xy1.push_back(std::make_pair(25, 0.05));

    xy2.push_back(std::make_pair(4, 1));
    xy2.push_back(std::make_pair(8, 0.6));
    xy2.push_back(std::make_pair(12, 0.4));
    xy2.push_back(std::make_pair(20, 0.2));
    xy2.push_back(std::make_pair(25, 0.1));

    this->lat_err_interpolation_.reset(new Interpolation1D);
    this->lat_err_interpolation_->Init(xy1);
    this->heading_err_interpolation_.reset(new Interpolation1D);
    this->heading_err_interpolation_->Init(xy2);
};

bool LonMPC::FollowMethod(ControlCommand &cur_cmd)  {

    // //VehicleParameters
    double wheelbase = physical_.wheel_base_; 
    double steer_ratio = physical_.steer_ratio_;
    double max_frontwheel_angle = physical_.max_steering_angle_ / physical_.steer_ratio_; //%前轮最大转角, 单位rad /apollo 53, old 30
    double max_frontwheel_speed = physical_.max_steering_speed_ / physical_.steer_ratio_;               //%前轮最大角速度, 单位rad/s
    double max_lon_acc = physical_.max_lon_acceleration_;                                                          //%车辆最大加速度,m/s^2
    double max_lat_acceleration = 3.0;
    // //设置LQR的参数，参数不对方向盘抖动会比较厉害
    double cf = physical_.cf_;      //%前轮侧偏刚度(cornering stiffness)  ，两个轮的侧偏刚度合并为一个
    double cr = physical_.cr_;      //%后轮侧偏刚度

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
    // cur_speed += pred_ts*cur_status_.linear_acc.y;
    

 

    MatrixXd matrix_i = MatrixXd::Identity(basic_state_size_, basic_state_size_);
    // matrix_ad_ = (matrix_i - Ts_ * 0.5 * matrix_a_).inverse() * (matrix_i + Ts_ * 0.5 * matrix_a_);//可考虑三种方法，前向欧拉。中点欧拉，后向欧拉
    matrix_ad_ = matrix_a_;//可考虑三种方法，前向欧拉。中点欧拉，后向欧拉

    

    // Eigen::MatrixXd matrix_k = MatrixXd::Zero(1, basic_state_size_);
    // if (enable_gain_mpc_theta_)40.29823303222656
    // {
    //     matrix_q_updated_(0, 0) =
    //         matrix_q_(0, 0) * lat_err_interpolation_->Interpolate(
    //                              std::fabs(cur_speed));
    //     matrix_q_updated_(2, 2) =
    //         matrix_q_(2, 2) * heading_err_interpolation_->Interpolate(
    //                              std::fabs(cur_speed));
    // }
    // std::cout<<"matrix_q_updated_: "<<std::endl;
    // std::cout<<matrix_q_updated_<<std::endl;


    // // this->SolveLQRProblem(matrix_ad_, matrix_bd_, matrix_q_, matrix_r_, tolerance, max_iteration_, &matrix_k);
    // this->SolveLQRProblem(matrix_ad_, matrix_bd_, matrix_q_updated_, matrix_r_, tolerance, max_iteration_, &matrix_k);

    // //update_state
    // //min_pos
    size_t nearest_index = this->QueryNearestPoseFromXY(this->follow_path_, pred_pos);
    // // size_t nearest_index = this->QueryNearestPoseFromXY(this->follow_path_, cur_status_.cur_pos);

    const Pose nearest_pos = this->follow_path_.poses_[nearest_index];

    double ed = this->calcLateralError(pred_pos, nearest_pos);
    double ephi = nearest_pos.heading_ - pred_phi;
    double ed_dot = cur_vx * std::sin(ephi);
    double ephi_dot = pred_phi_dot - nearest_pos.kappa_ * cur_vx;
    // ROS_INFO("The ed is %f , ephi is %f \n", ed, ephi);
    double ref_curvature = nearest_pos.kappa_;
    ed = lateral_error_filter_.Update(ed);
    ephi = heading_error_filter_.Update(ephi);
    ed_dot = lateralRate_error_filter_.Update(ed_dot);
    ephi_dot = headingRate_error_filter_.Update(ephi_dot);   
    double cur_max_kappa = 0.0;
    // for (auto &pos : this->follow_path_.poses_) {
    //     cur_max_kappa = std::max(cur_max_kappa, pos.kappa_);
    // }
    // // cur_max_kappa = this->curvature_filter_.Update(cur_max_kappa);
    // target_velocity_ = std::min(std::fabs(0.03 / cur_max_kappa / 3.6) , target_velocity_);
    // // target_velocity_ = this->curvature_filter_.Update(target_velocity_);

    //  printf("The Target Vel %f, obj vel %f, obj_dis %f\n", target_velocity_, ACC_cur_obj_vel_, ACC_relative_dis_);
    // ACC_cur_obj_vel_ = 1000.0;
    // target_velocity_ = this->direction_filter_.Update(target_velocity_);
    ACC_target_dis_ = cur_speed * 3 + 15;
    // ACC_relative_dis_ = 1000.0;
    // target_velocity_ = 20.0;
    if (ACC_cur_obj_vel_ == 1000.0 || ACC_cur_obj_vel_ == 0.00 || ACC_relative_dis_ == 1000.0) {
        ACC_cur_obj_vel_ = target_velocity_;
        ACC_relative_dis_ = ACC_target_dis_;
    } 
    // if (ACC_relative_dis_ - ACC_target_dis_ > 50.0) {
    //     ACC_relative_dis_ = ACC_target_dis_;
    //     // ACC_cur_obj_vel_ = target_velocity_;

    // } 
    // matrix_state_(0, 0) = ACC_target_dis_ - ACC_relative_dis_ ;
    
    if (ACC_relative_dis_ - ACC_target_dis_ > 5.0) {
        ACC_cur_obj_vel_ = target_velocity_;
        ACC_relative_dis_ = ACC_target_dis_;
    }
    matrix_state_(0, 0) = ACC_relative_dis_ - ACC_target_dis_;

    matrix_state_(1, 0) = (ACC_cur_obj_vel_ - cur_speed) ;
    // matrix_state_(2, 0) = cur_speed ;
    // matrix_state_(3, 0) = cur_status_.linear_acc.x;
    matrix_state_(2, 0) = cur_status_.linear_acc.x ;
    // matrix_state_(3, 0) = cur_status_.linear_acc.x - prev_acc;
    matrix_state_(3, 0) = 0.0;
    // std::cout << matrix_ad_ << std::endl;
    prev_acc = cur_status_.linear_acc.x;
    // matrix_state_(0, 0) = 0.0;
    // // matrix_state_(1, 0) = ed_dot;
    // matrix_state_(2, 0) = 0.0;
    // matrix_state_(3, 0) =  0;
    // std::cout << "State  " << std::endl;
    std::cout << matrix_state_ << std::endl;
    // matrix_state_(3, 0) = target_velocity_ - cur_speed * cos(ephi)/(1-ref_curvature);

    // matrix_state_(4, 0) = 0;
    // matrix_state_(5, 0) = target_velocity_ - cur_speed * cos(ephi)/(1-ref_curvature);
    


    MatrixXd control_matrix = MatrixXd::Zero(controls_, 1);
    std::vector<MatrixXd> control(horizon_, control_matrix);

    MatrixXd reference_state = MatrixXd::Zero(basic_state_size_, 1);
    std::vector<MatrixXd> reference(horizon_, reference_state);

    MatrixXd reference_control = MatrixXd::Zero(controls_, 1);
    ControlCommand refCMD;
    // reference_control(0, 0) = 1.0;
    std::cout<<"################# "<<ACC_cur_obj_vel_ - cur_speed <<std::endl;
    reference_control(0, 0) = this->VelocityError2Accelerate(ACC_cur_obj_vel_ - cur_speed, 0.02);
    // std::cout << "ref_u: " << reference_control(0, 0) << std::endl; 
    
    MatrixXd lower_bound(controls_, 1);
    lower_bound << -max_lon_acc;
    
    MatrixXd upper_bound(controls_, 1);
    upper_bound << max_lon_acc;

    // const double max = std::numeric_limits<double>::max();
    const double max = 100.0;
    // printf("MAX : %f \n", max);
    MatrixXd lower_state_bound(basic_state_size_, 1);
    MatrixXd upper_state_bound(basic_state_size_, 1);
    // max = 100.0;
    // lateral_error, lateral_error_rate, heading_error, heading_error_rate
    // station_error, station_error_rate
    lower_state_bound << -1.0 * max, -30.0,-5.0, -1.0;
    upper_state_bound << max, 30, 5.0, 1.0;

    std::vector<double> control_cmd(controls_, 0);

    common::math::MpcOsqp mpc_osqp(
        matrix_ad_, matrix_bd_, matrix_cd_, matrix_q_updated_, matrix_r_updated_,
        matrix_state_, lower_bound, upper_bound, lower_state_bound,
        upper_state_bound, reference_state, reference_control, 
        mpc_max_iteration_, horizon_, mpc_eps_);

    auto start_time_osqp = std::chrono::system_clock::now();
    if (mpc_osqp.Solve(&control_cmd))
    {
        std::cout << "MPC OSQP solver success" << std::endl;
        control[0](0, 0) = control_cmd.at(0);
        // control[0](1, 0) = control_cmd.at(1);
    }
    else
    {
        std::cout << "MPC OSQP solver failed! " << std::endl;

    }
    auto end_time_osqp = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_OSQP = end_time_osqp - start_time_osqp;
    std::cout << "OSQP used time: " << diff_OSQP.count() * 1000 << " ms." <<std::endl;
    double steer_angle_feedback = control[0](0, 0);


    const double kv =
    lr * mass / 2 / cf / wheelbase - lf * mass / 2 / cr / wheelbase;

    double forword_angle =
        wheelbase * ref_curvature + kv * cur_speed * cur_speed * ref_curvature;
    // double steer_angle = (matrix_k * matrix_state_)(0, 0) + forword_angle;
    double steer_angle = steer_angle_feedback;
    
    double steering_angle = steer_angle * physical_.steer_ratio_;
    steering_angle = std::max(steering_angle, -physical_.max_steering_angle_);
    steering_angle = std::min(steering_angle, physical_.max_steering_angle_);
    // // steering_angle = this->steeringcmd_mean_filter_->Update(steering_angle);
    steering_angle = 0.8 * steering_angle + 0.2 * pre_steer_;
    // steering_angle = steeringcmd_losspass_filter_->Filter(steering_angle);
    // pre_steer_ = steering_angle;
    // double  acc_cmd = this->VelocityError2Accelerate(target_velocity_ - cur_status_.cur_pos.linear_velocity_, 0.02) 
    // + longitudinaldispid_->Control(ACC_relative_dis_ - ACC_target_dis_, 0.02);
    
    double  acc_cmd  = control[0](0, 0);
    // acc_cmd = std::min(acc_cmd, reference_control(0, 0));

    acc_cmd = std::max(acc_cmd, -3.5);
    acc_cmd = std::min(acc_cmd, 2.5);
    // if(cur_speed > target_velocity_ + 0.5) acc_cmd = 0.0;
    // acc_cmd = curvature_filter_.Update(acc_cmd);
    // // double  acc_cmd  =  reference_control(0, 0);
    // if (std::fabs(acc_cmd) < 0.00000000001) acc_cmd = prev_acc_cmd;
    // prev_acc_cmd = acc_cmd;
    // cur_cmd.setCommand(-steering_angle, ACC_cur_obj_vel_, this->VelocityError2Accelerate(ACC_cur_obj_vel_ - cur_status_.cur_pos.linear_velocity_, 0.02));
    printf("MPC Acc : %f %f %f\n", control[0](0, 0), reference_control(0, 0), cur_status_.linear_acc.x);
    cur_cmd.setCommand(-steering_angle, target_velocity_, acc_cmd);
    
    return true;
};

bool LonMPC::initConfigParameters(const std::string &mpc_param_config_path) {
    YAML::Node config = YAML::LoadFile(mpc_param_config_path);
    bool init = true;
    //缺少关键词，则赋值为-1.0，便于后面检查
    this->matrix_q0_ = config["matrix_q0"] ? config["matrix_q0"].as<double>() : -1.0;
    this->matrix_q1_ = config["matrix_q1"] ? config["matrix_q1"].as<double>() : -1.0;
    this->matrix_q2_ = config["matrix_q2"] ? config["matrix_q2"].as<double>() : -1.0;
    this->matrix_q3_ = config["matrix_q3"] ? config["matrix_q3"].as<double>() : -1.0;
    this->matrix_r0_ = config["matrix_r0"] ? config["matrix_r0"].as<double>() : -1.0;

    this->Tau_ = config["Tau"] ? config["Tau"].as<double>() : -1.0;
    this->max_iteration_ = config["max_iteration"] ? config["max_iteration"].as<int>() : -1.0;

    this->Ts_ = config["Ts"] ? config["Ts"].as<double>() : -1.0;
    printf("The Sample time : %f\n", Ts_);
    // printf("The Weight  q0 : %f, q1 : %f, q2 : %f, q3 : %f \n q4 : %f, q5 : %f, r0 : %f, r1 : %f \n"
    // , matrix_q0_, matrix_q1_, matrix_q2_, matrix_q3_, matrix_q4_, matrix_q5_,matrix_r0_, matrix_r1_);

    if (this->matrix_q0_ < -0.01 || this->matrix_q1_ < -0.01 || this->matrix_q2_ < -0.01 || this->matrix_q3_ < -0.01 || this->Ts_ < -0.01) {
        fprintf(stderr, "The MPC init unsuccessfully! \n");
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

    this->matrix_r_ = MatrixXd::Zero(controls_, controls_);
    this->matrix_r_(0,0)= this->matrix_r0_;
    this->matrix_r_updated_ = this->matrix_r_;

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
    this->matrix_a_(0, 0) = 1.0;
    this->matrix_a_(1, 1) = 1.0;
    this->matrix_a_(2, 2) = 1.0;


    this->matrix_a_(0, 1) = Ts_;
    // this->matrix_a_(0, 2) = -0.5 * Ts_ * Ts_;
    // this->matrix_a_(1, 3) = -0.5 * Ts_ * Ts_;
    // this->matrix_a_(1, 2) = -Ts_;

    this->matrix_a_(1, 3) = -0.5 * Ts_ * Ts_;
    this->matrix_a_(2, 3) = Ts_;
    this->matrix_a_(3, 3) = 1 - Ts_ / Tau_;
    // this->matrix_a_(0, 1) = Ts_;
    // this->matrix_a_(0, 3) = -0.5 * Ts_ * Ts_;


    // this->matrix_a_(1, 3) = -Ts_;
    // this->matrix_a_(2, 3) = Ts_;
    // this->matrix_a_(3, 3) = 1 - Ts_ / Tau_;
    
    //matrix_a_coeff_
    this->matrix_a_coeff_ = this->matrix_a_;
    // this->matrix_a_coeff_ = this->matrix_a_;


    //matrix_b_
    this->matrix_b_ = MatrixXd::Zero(basic_state_size_, controls_);
    this->matrix_bd_ = MatrixXd::Zero(basic_state_size_, controls_);

    this->matrix_b_(1, 0) = -0.5 * Ts_ * Ts_;

    this->matrix_b_(1, 0) = -Ts_;

    this->matrix_b_(2, 0) = 1.0;
    
    this->matrix_b_(3, 0) = Ts_ / Tau_;
    // this->matrix_bd_ = this->matrix_b_ * this->Ts_;
    this->matrix_bd_ = this->matrix_b_;


    this->matrix_c_ = MatrixXd::Zero(basic_state_size_, 1);;
    this->matrix_cd_ = MatrixXd::Zero(basic_state_size_, 1);;
    //   this->matrix_c_ = MatrixXd::Zero(3, 4);;
    // this->matrix_cd_ = MatrixXd::Zero(3, 4);;
    // this->matrix_c_(0, 0) = 1.0;
    // this->matrix_c_(1, 1) = 1.0;
    // this->matrix_c_(2, 2) = 1.0;

    // this->matrix_cd_ = this->matrix_c_ * this->Ts_;
    this->matrix_cd_ = this->matrix_c_;



    printf( "The MPC init successfully! \n");

    return true;
};
bool LonMPC::updateAccTarget(const smartcar_msgs::ACCTarget& cur_acc_target, std::mutex &cur_acc_mutex) {
    ACC_pre_obj_vel_ = ACC_cur_obj_vel_;
    {
        std::lock_guard<std::mutex> _guard(cur_acc_mutex);
        ACC_obj_id_ = cur_acc_target.object_id;
        ACC_relative_dis_ = cur_acc_target.relative_dis;
        ACC_cur_obj_vel_ = cur_acc_target.velocity;
    }
    printf("%s %f %f ACCTARGET\n",ACC_obj_id_.c_str(), ACC_relative_dis_, ACC_cur_obj_vel_ );
    // ACC_cur_obj_acc_ = (ACC_cur_obj_vel_ - ACC_pre_obj_vel_)/0.02;
    ACC_cur_obj_acc_ = 0.0;

    return true;
};

}//PathFollower