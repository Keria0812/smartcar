#include "active_set_spline_1d_solver.h"
#include <algorithm>
#include <iostream>
#include "active_set_qp_solver.h"
#include "path_struct.h"
#include <chrono>

namespace
{
  constexpr double kMaxBound = 1e3;
}

using Eigen::MatrixXd;

bool ActiveSetSpline1dSolver::Solve()
{
  const MatrixXd &kernel_matrix = kernel_.kernel_matrix();
  const MatrixXd &offset = kernel_.offset();
  const MatrixXd &inequality_constraint_matrix = constraint_.inequality_constraint().constraint_matrix();
  const MatrixXd &inequality_constraint_boundary = constraint_.inequality_constraint().constraint_boundary();
  const MatrixXd &equality_constraint_matrix = constraint_.equality_constraint().constraint_matrix();
  const MatrixXd &equality_constraint_boundary = constraint_.equality_constraint().constraint_boundary();

  if (kernel_matrix.rows() != kernel_matrix.cols())
  {
    // std::cout << "kernel_matrix.rows() [" << kernel_matrix.rows() << "] and kernel_matrix.cols() [" <<
    // kernel_matrix.cols() << "] should be identical.";
    return false;
  }

  int num_param = static_cast<int>(kernel_matrix.rows());
  int num_constraint = static_cast<int>(equality_constraint_matrix.rows() + inequality_constraint_matrix.rows());

  bool use_hotstart = last_problem_success_ && (Config_.FLAGS_enable_sqp_solver && sqp_solver_ != nullptr &&
                                                num_param == last_num_param_ && num_constraint == last_num_constraint_);

  if (!use_hotstart)
  {
    sqp_solver_.reset(new ::qpOASES::SQProblem(num_param, num_constraint, ::qpOASES::HST_UNKNOWN));
    ::qpOASES::Options my_options;
    my_options.enableCholeskyRefactorisation = 1;
    my_options.epsNum = Config_.default_active_set_eps_num;
    my_options.epsDen = Config_.default_active_set_eps_den;
    my_options.epsIterRef = Config_.default_active_set_eps_iter_ref;
    sqp_solver_->setOptions(my_options);
    if (!Config_.default_enable_active_set_debug_info)
    {
      sqp_solver_->setPrintLevel(qpOASES::PL_NONE);
    }
  }

  // definition of qpOASESproblem
  const auto kNumOfMatrixElements = kernel_matrix.rows() * kernel_matrix.cols();
  double h_matrix[kNumOfMatrixElements]; // NOLINT

  const auto kNumOfOffsetRows = offset.rows();
  double g_matrix[kNumOfOffsetRows]; // NOLINT
  int index = 0;

  for (int r = 0; r < kernel_matrix.rows(); ++r)
  {
    g_matrix[r] = offset(r, 0);
    for (int c = 0; c < kernel_matrix.cols(); ++c)
    {
      h_matrix[index++] = kernel_matrix(r, c);
    }
  }
  // DCHECK_EQ(index, kernel_matrix.rows() * kernel_matrix.cols());

  // search space lower bound and uppper bound
  double lower_bound[num_param]; // NOLINT
  double upper_bound[num_param]; // NOLINT

  const double l_lower_bound_ = -kMaxBound;
  const double l_upper_bound_ = kMaxBound;
  for (int i = 0; i < num_param; ++i)
  {
    lower_bound[i] = l_lower_bound_;
    upper_bound[i] = l_upper_bound_;
  }

  // constraint matrix construction
  double affine_constraint_matrix[num_param * num_constraint]; // NOLINT
  double constraint_lower_bound[num_constraint];               // NOLINT
  double constraint_upper_bound[num_constraint];               // NOLINT

  index = 0;
  for (int r = 0; r < equality_constraint_matrix.rows(); ++r)
  {
    constraint_lower_bound[r] = equality_constraint_boundary(r, 0);
    constraint_upper_bound[r] = equality_constraint_boundary(r, 0);

    for (int c = 0; c < num_param; ++c)
    {
      affine_constraint_matrix[index++] = equality_constraint_matrix(r, c);
    }
  }

  // DCHECK_EQ(index, equality_constraint_matrix.rows() * num_param);

  const double constraint_upper_bound_ = kMaxBound;
  for (int r = 0; r < inequality_constraint_matrix.rows(); ++r)
  {
    constraint_lower_bound[r + equality_constraint_boundary.rows()] = inequality_constraint_boundary(r, 0);
    constraint_upper_bound[r + equality_constraint_boundary.rows()] = constraint_upper_bound_;

    for (int c = 0; c < num_param; ++c)
    {
      affine_constraint_matrix[index++] = inequality_constraint_matrix(r, c);
    }
  }
  // DCHECK_EQ(index, equality_constraint_matrix.rows() * num_param + inequality_constraint_boundary.rows() *
  // num_param);

  // initialize problem
  int max_iteration_ = 1000;
  int max_iter = std::max(max_iteration_, num_constraint);

  ::qpOASES::returnValue ret;
  auto start_timestamp = std::chrono::system_clock::now();

  if (use_hotstart)
  {
    // std::cout << "using SQP hotstart.";
    ret = sqp_solver_->hotstart(h_matrix, g_matrix, affine_constraint_matrix, lower_bound, upper_bound,
                                constraint_lower_bound, constraint_upper_bound, max_iter);
    if (ret != qpOASES::SUCCESSFUL_RETURN)
    {
      // std::cout << "Fail to hotstart spline 1d, will use re-init instead.";
      ret = sqp_solver_->init(h_matrix, g_matrix, affine_constraint_matrix, lower_bound, upper_bound,
                              constraint_lower_bound, constraint_upper_bound, max_iter);
    }
  }
  else
  {
    // std::cout << "no using SQP hotstart.";
    ret = sqp_solver_->init(h_matrix, g_matrix, affine_constraint_matrix, lower_bound, upper_bound,
                            constraint_lower_bound, constraint_upper_bound, max_iter);
  }
  auto end_timestamp = std::chrono::system_clock::now();

  // std::cout << "ActiveSetSpline1dSolver QP solve time: " << (end_timestamp - start_timestamp) * 1000 << " ms.";

  if (ret != qpOASES::SUCCESSFUL_RETURN)
  {
    if (ret == qpOASES::RET_MAX_NWSR_REACHED)
    {
      // std::cout << "qpOASES solver failed due to reached max iteration";
    }
    else
    {
      // std::cout << "qpOASES solver failed due to infeasibility or other internal " "reasons:" << ret;
    }
    last_problem_success_ = false;
    return false;
  }

  last_problem_success_ = true;
  double result[num_param]; // NOLINT
  memset(result, 0, sizeof result);

  sqp_solver_->getPrimalSolution(result);

  MatrixXd solved_params = MatrixXd::Zero(num_param, 1);
  for (int i = 0; i < num_param; ++i)
  {
    solved_params(i, 0) = result[i];
    // std::cout  << "spline 1d solved param[" << i << "]: " << result[i];
  }

  last_num_param_ = num_param;
  last_num_constraint_ = num_constraint;

  return spline_.SetSplineSegs(solved_params, spline_.spline_order());
}