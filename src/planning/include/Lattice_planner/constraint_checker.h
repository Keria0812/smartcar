/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-04-23 19:56:39
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-01-11 20:25:07
 * @FilePath: /miniEV/src/planning/include/Lattice_planner/constraint_checker.h
 */
#pragma once
#include <memory>
#include <vector>
#include "path_struct.h"
#include "FrenetPath.h"

class ConstraintChecker
{
public:
  enum class Result
  {
    VALID,
    LON_VELOCITY_OUT_OF_BOUND,
    LON_ACCELERATION_OUT_OF_BOUND,
    LON_JERK_OUT_OF_BOUND,
    LAT_VELOCITY_OUT_OF_BOUND,
    LAT_ACCELERATION_OUT_OF_BOUND,
    LAT_JERK_OUT_OF_BOUND,
    CURVATURE_OUT_OF_BOUND,
  };
  ConstraintChecker() = default;
  ~ConstraintChecker() = default;
  Result ValidTrajectory(const DiscretizedTrajectory &trajectory) const;

private:
  ;
};