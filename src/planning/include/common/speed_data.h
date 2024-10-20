#pragma once
#include "path_points.h"
#include <iostream>
#include <algorithm>
#include <mutex>
#include <utility>

class SpeedData : public std::vector<SpeedPoint>
{
public:
  SpeedData() = default;

  explicit SpeedData(std::vector<SpeedPoint> speed_points);

  void AppendSpeedPoint(const double s, const double time, const double v, const double a, const double da);

  bool EvaluateByTime(const double time, SpeedPoint *const speed_point) const;

  // Assuming spatial traversed distance is monotonous, which is the case for
  // current usage on city driving scenario
  bool EvaluateByS(const double s, SpeedPoint *const speed_point) const;

  double TotalTime() const;

  // Assuming spatial traversed distance is monotonous
  double TotalLength() const;

  bool Empty() const;

  virtual std::string DebugString() const;
};