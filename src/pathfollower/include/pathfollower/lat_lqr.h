/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-14 18:58:01
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-07 22:51:02
 * @FilePath: /miniEV/src/pathfollower/include/pathfollower/lat_lqr.h
 */

#ifndef PATHFOLLOWER_LATLQR_H_
#define PATHFOLLOWER_LATLQR_H_

#include "pathfollower/controller.h"
#include "filters/interpolation_1d.h"
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>
#include <eigen3/Eigen/Core>

using namespace Eigen;

namespace PathFollower {

class LatLQR : public Controller
{
private:
    /* data */

    double Ts_ = 0.01;//simple_time/s
    double pre_steer_ = 0.0;
    

    int max_iteration_ = 0;
    int basic_state_size_ = 4;
    int preview_window_ = 0;

    double matrix_q0_ = 0.0;
    double matrix_q1_ = 0.0;
    double matrix_q2_ = 0.0;
    double matrix_q3_ = 0.0;

    MatrixXd matrix_a_;
    MatrixXd matrix_a_coeff_;
    MatrixXd matrix_ad_;

    MatrixXd matrix_state_;
    MatrixXd matrix_b_;
    MatrixXd matrix_bd_;

    MatrixXd matrix_r_;
    MatrixXd matrix_q_;

    MatrixXd matrix_q_updated_;


    std::unique_ptr<Interpolation1D> lat_err_interpolation_;
    std::unique_ptr<Interpolation1D> heading_err_interpolation_;
    // std::unique_ptr<Interpolation1D> heading_err_interpolation_;


    bool initConfigParameters(const std::string &lqr_param_config_path);
    bool SolveLQRProblem (const MatrixXd &A, const MatrixXd &B, const MatrixXd &Q,
                     const MatrixXd &R, const double tolerance,
                     const uint max_num_iteration, MatrixXd *ptr_K);
public:
    LatLQR(const std::string &vehicle_physical_config_path, const std::string &lqr_param_config_path);
    ~LatLQR() = default;

    
    bool FollowMethod(ControlCommand &cur_cmd)  override;

};

    
} //PathFollower



#endif //PATHFOLLOWER_LATLQR_H_