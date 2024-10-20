
#pragma once

#include <algorithm>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

#include "OsqpEigen/OsqpEigen.h"
#include <iostream>

namespace IAU {
namespace common {
namespace math {
class MpcOsqp {
 public:
  /**
   * @brief Solver for discrete-time model predictive control problem.
   * @param matrix_a The system dynamic matrix
   * @param matrix_b The control matrix
   * @param matrix_q The cost matrix for control state
   * @param matrix_r The cost matrix for control cmd
   * @param matrix_lower The lower bound control constrain matrix
   * @param matrix_upper The upper bound control constrain matrix
   * @param matrix_initial_state The initial state matrix
   * @param max_iter The maximum iterations
   */
  MpcOsqp(const Eigen::MatrixXd &matrix_a, const Eigen::MatrixXd &matrix_b,
          const Eigen::MatrixXd &matrix_c,
          const Eigen::MatrixXd &matrix_q, const Eigen::MatrixXd &matrix_r,
          const Eigen::MatrixXd &matrix_initial_x,
          const Eigen::MatrixXd &matrix_u_lower,
          const Eigen::MatrixXd &matrix_u_upper,
          const Eigen::MatrixXd &matrix_x_lower,
          const Eigen::MatrixXd &matrix_x_upper,
          const Eigen::MatrixXd &matrix_x_ref, 
          const int max_iter,
          const int horizon, const double eps_abs);

  // control vector
  bool Solve(std::vector<double> *control_cmd);

 private:
  void castMPCToQPHessian();
  void castMPCToQPGradient();
  void castMPCToQPConstraintMatrix();
  void castMPCToQPConstraintVectors();

 private:
  Eigen::MatrixXd matrix_a_;
  Eigen::MatrixXd matrix_b_;
  Eigen::MatrixXd matrix_c_;
  Eigen::MatrixXd matrix_q_;
  Eigen::MatrixXd matrix_r_;

  Eigen::MatrixXd matrix_initial_x_;
  const Eigen::MatrixXd matrix_u_lower_;
  const Eigen::MatrixXd matrix_u_upper_;
  const Eigen::MatrixXd matrix_x_lower_;
  const Eigen::MatrixXd matrix_x_upper_;
  const Eigen::MatrixXd matrix_x_ref_;
  int max_iteration_;
  size_t horizon_;
  double eps_abs_;
  size_t state_dim_ = 4;
  size_t control_dim_ = 1;
  size_t num_param_;
  int num_constraint_;

  // allocate QP problem matrices and vectores
  Eigen::SparseMatrix<double> hessian_;
  Eigen::VectorXd gradient_;
  Eigen::SparseMatrix<double> constraintMatrix_;
  Eigen::VectorXd lowerBound_;
  Eigen::VectorXd upperBound_;

};
}  // namespace math
}  // namespace common
}  // namespace apollo
