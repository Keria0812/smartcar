
#pragma once

#include <memory>
#include <vector>

#include "qp_solver.h"
#include "spline_1d_solver.h"
#include <qpOASES.hpp>

class ActiveSetSpline1dSolver : public Spline1dSolver
{
public:
  ActiveSetSpline1dSolver(const std::vector<double>& x_knots, const uint32_t order) : Spline1dSolver(x_knots, order)
  {
  }

  bool Solve() override;

private:
  std::unique_ptr<::qpOASES::SQProblem> sqp_solver_;
};