#include "reference_line_info.h"

ReferenceLineInfo::ReferenceLineInfo(const TrajectoryPoint &adc_planning_point, const ReferenceLine &reference_line) : reference_line_(reference_line)
{
}

const std::vector<PathBoundary> &ReferenceLineInfo::GetCandidatePathBoundaries() const
{
  return candidate_path_boundaries_;
}

void ReferenceLineInfo::SetCandidatePathBoundaries(std::vector<PathBoundary> &&path_boundaries)
{
  candidate_path_boundaries_ = std::move(path_boundaries);
}
const SpeedData &ReferenceLineInfo::speed_data() const
{
  return speed_data_;
}

const ReferenceLine &ReferenceLineInfo::reference_line() const
{
  return reference_line_;
}

void ReferenceLineInfo::set_speed_data(SpeedData &speed_)
{
  speed_data_ = speed_;
}