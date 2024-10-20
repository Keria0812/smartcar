#pragma once

#include <string>
#include <vector>

#include "Obstacle.h"
#include "path_data.h"
#include "speed_limit.h"
#include "reference_line.h"
#include "indexed_list.h"

class SpeedLimitDecider
{
public:
    SpeedLimitDecider(const SL_Boundary &adc_sl_boundary,
                      const ReferenceLine &reference_line,
                      const PathData &path_data);

    virtual ~SpeedLimitDecider() = default;

    virtual void GetSpeedLimits(
        const std::vector<const Obstacle *> &obstacles,
        planning::SpeedLimit *const speed_limit_data) const;

private:
    double GetCentricAccLimit(const double kappa) const;

    void GetAvgKappa(const std::vector<PathPoint> &path_points,
                     std::vector<double> *kappa) const;

private:
    const SL_Boundary &adc_sl_boundary_;
    const ReferenceLine &reference_line_;
    const PathData &path_data_;
};
