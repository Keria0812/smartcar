#pragma once

#include <Eigen/Core>
#include <Eigen/LU>

class QpSolver
{
public:
  QpSolver(const Eigen::MatrixXd& kernel_matrix, const Eigen::MatrixXd& offset,
           const Eigen::MatrixXd& affine_inequality_matrix, const Eigen::MatrixXd& affine_inequality_boundary,
           const Eigen::MatrixXd& affine_equality_matrix, const Eigen::MatrixXd& affine_equality_boundary);
  virtual ~QpSolver() = default;

  virtual void set_pos_semi_definite_hessian()
  {
  }
  virtual void set_pos_definite_hessian()
  {
  }
  virtual void EnableCholeskyRefactorisation(const int)
  {
  }
  virtual void SetTerminationTolerance(const double)
  {
  }
  virtual bool Solve() = 0;

  const Eigen::MatrixXd& params() const;
  const Eigen::MatrixXd& kernel_matrix() const;
  const Eigen::MatrixXd& offset() const;
  const Eigen::MatrixXd& affine_equality_matrix() const;
  const Eigen::MatrixXd& affine_equality_boundary() const;
  const Eigen::MatrixXd& affine_inequality_matrix() const;
  const Eigen::MatrixXd& affine_inequality_boundary() const;

protected:
  virtual bool sanity_check() = 0;
  Eigen::MatrixXd params_;
  Eigen::MatrixXd kernel_matrix_;
  Eigen::MatrixXd offset_;
  Eigen::MatrixXd affine_inequality_matrix_;
  Eigen::MatrixXd affine_inequality_boundary_;
  Eigen::MatrixXd affine_equality_matrix_;
  Eigen::MatrixXd affine_equality_boundary_;
};