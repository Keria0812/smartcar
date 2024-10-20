#pragma once

#include <memory>
#include "qp_solver.h"
#include "piecewise_linear_constraint.h"
#include "piecewise_linear_kernel.h"

class PiecewiseLinearGenerator
{
public:
    // x = f(t)
    PiecewiseLinearGenerator(const uint32_t num_of_segments,
                             const double unit_segment);
    virtual ~PiecewiseLinearGenerator() = default;

    PiecewiseLinearConstraint *mutable_constraint();

    PiecewiseLinearKernel *mutable_kernel();

    // solve
    bool Solve();

    // results
    Eigen::MatrixXd params() const { return qp_solver_->params(); }

private:
    const uint32_t num_of_segments_;
    const double unit_segment_;
    const double total_t_;

    PiecewiseLinearConstraint constraint_;
    PiecewiseLinearKernel kernel_;

    std::unique_ptr<QpSolver> qp_solver_;
};