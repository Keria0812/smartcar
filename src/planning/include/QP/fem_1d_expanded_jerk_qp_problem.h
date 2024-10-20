#pragma once

#include <vector>

#include "fem_1d_qp_problem.h"

/*
 * @brief:
 * the idea is to balance the time consumption and accuracy compared to the
 * original problem. We construct a matrix by concatinate x, x''', and use x'''
 * to represent x' and x'':
 * TODO(all): In principle, x' and x'' can be represented by x''', but need to
 * verify the fomular below
 * --- x(i)'' = sum[0, i-1](x''') + x(0)''
 * --- x(i)' = 0.5 * ds^2 * sum[0, i-1](x''') + ds * (i - 1) + x(0)'
 * + sum[0, i-2](sum[0, j](x(k)''' * ds))
 */

class Fem1dExpandedJerkQpProblem : public Fem1dQpProblem
{
public:
    Fem1dExpandedJerkQpProblem() = default;

    virtual ~Fem1dExpandedJerkQpProblem() = default;

    // this verison is used as a base line. Will be upgraded according to brief.
    bool Optimize() override;

private:
    // naming convention follows osqp solver.
    void CalculateKernel(std::vector<c_float> *P_data,
                         std::vector<c_int> *P_indices,
                         std::vector<c_int> *P_indptr) override;

    void CalculateOffset(std::vector<c_float> *q) override;

    void CalculateAffineConstraint(std::vector<c_float> *A_data,
                                   std::vector<c_int> *A_indices,
                                   std::vector<c_int> *A_indptr,
                                   std::vector<c_float> *lower_bounds,
                                   std::vector<c_float> *upper_bounds) override;

    void CalculateAffineConstraintUsingDenseMatrix(
        std::vector<c_float> *A_data, std::vector<c_int> *A_indices,
        std::vector<c_int> *A_indptr, std::vector<c_float> *lower_bounds,
        std::vector<c_float> *upper_bounds);
};