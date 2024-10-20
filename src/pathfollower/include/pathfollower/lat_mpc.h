/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-07-22 15:36:05
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-01-14 22:45:23
 * @FilePath: /miniEV/src/pathfollower/include/pathfollower/lat_mpc.h
 */
#ifndef PATHFOLLOWER_LATMPC_H_
#define PATHFOLLOWER_LATMPC_H_

#include "pathfollower/controller.h"
#include "filters/interpolation_1d.h"

#include "math/math_utils.h"
#include "math/mpc_osqp.h"
#include "math/osqp_interface.h"

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>
#include <eigen3/Eigen/Core>


using namespace Eigen;

namespace PathFollower {

class LatMPC : public Controller {
private:
    /* data */

    double Ts_ = 0.01;//simple_time/s
    
    double pre_steer_ = 0.0;

    int max_iteration_ = 0;
    // int basic_state_size_ = 4;
    int preview_window_ = 0;

    double matrix_q0_ = 0.0;
    double matrix_q1_ = 0.0;
    double matrix_q2_ = 0.0;
    double matrix_q3_ = 0.0;
    double matrix_q4_ = 0.0;
    double matrix_q5_ = 0.0;
    double matrix_r0_ = 0.0;
    double matrix_r1_ = 0.0;

    MatrixXd matrix_a_;
    MatrixXd matrix_a_coeff_;
    MatrixXd matrix_ad_;

    MatrixXd matrix_state_;
    MatrixXd matrix_b_;
    MatrixXd matrix_bd_;

    MatrixXd matrix_r_;
    MatrixXd matrix_q_;

    MatrixXd matrix_q_updated_;
    MatrixXd matrix_r_updated_;

    bool enable_gain_mpc_theta_ = true;
    const int basic_state_size_ = 6;
    const int controls_ = 2;
    const int horizon_ = 10;
    const int mpc_max_iteration_ = 150;
    const double mpc_eps_ = 0.01;

    std::unique_ptr<Interpolation1D> lat_err_interpolation_;
    std::unique_ptr<Interpolation1D> heading_err_interpolation_;

    bool initConfigParameters(const std::string &mpc_param_config_path);
    // bool SolveLQRProblem (const MatrixXd &A, const MatrixXd &B, const MatrixXd &Q,
    //                  const MatrixXd &R, const double tolerance,
    //                  const uint max_num_iteration, MatrixXd *ptr_K);
public:
    LatMPC(const std::string &vehicle_physical_config_path, const std::string &mpc_param_config_path);
    ~LatMPC() = default;


    
    bool FollowMethod(ControlCommand &cur_cmd)  override;
};
}//PathFollower
#endif //PATHFOLLOWER_LATMPC_H_