#pragma once
#include <vector>
#include <osqp/osqp.h>
#include "qp_solver.h"
#include "spline_1d_solver.h"
#include "path_struct.h"

class OsqpSpline1dSolver : public Spline1dSolver
{
public: 
    OsqpSpline1dSolver(const std::vector<double> &x_knots, const uint32_t order);
    virtual ~OsqpSpline1dSolver();

    bool Solve() override;

    void CleanUp();

    void ResetOsqp();

private:
    OSQPSettings *settings_ = nullptr;
    OSQPWorkspace *work_ = nullptr; // Workspace
    OSQPData *data_ = nullptr;      // OSQPData
};