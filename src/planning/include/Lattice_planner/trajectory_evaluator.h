/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-04-23 19:56:39
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-01-11 20:07:44
 * @FilePath: /miniEV/src/planning/include/Lattice_planner/trajectory_evaluator.h
 */
#ifndef TRAJECTORY_EVALUATOR_H
#define TRAJECTORY_EVALUATOR_H
#include "CubicSpline2D.h"
#include "path_struct.h"
#include "piecewise_braking_trajectory_generator.h"
#include "PlanningTarget.h"
#include "curve1d.h"
#include "quintic_polynomial_curve1d.h"
#include "quartic_polynomial_curve1d.h"
#include "lattice_trajectory1d.h"
#include "path_time_graph.h"
#include "path_matcher.h"
#include "ThreadPool.h"

#include <vector>
#include <cmath>
#include <chrono>
#include <queue>
#include <string>
#include <mutex>
#include <future>
using Trajectory1d = Curve1d;
using Trajectory1dPair = std::pair<std::shared_ptr<Curve1d>, std::shared_ptr<Curve1d>>;
using PtrTrajectory1d = std::shared_ptr<Trajectory1d>;

class TrajFeature {
  public:
    double lat_offset_cost = 0.0;
    double lat_comfort_cost = 0.0;
    double lon_objective_cost = 0.0;
    double lon_comfort_cost = 0.0;
    double lon_collision_cost = 0.0;
    double centripetal_acc_cost = 0.0;

    double speed_cost = 0.0;
    double dist_travelled_cost = 0.0;

    double human_likeness = 0.0;
    bool is_collision = false;

    double lat_offset = 0.0;
    double target_speed = 0.0;
    double length_s = 0.0;
    double length_time = 0.0;
  
};
class TrajectoryEvaluator
{
public:
  TrajectoryEvaluator() = default;
  ~TrajectoryEvaluator() = default;
  explicit TrajectoryEvaluator(const PlanningTarget &planning_target,
                               const std::vector<PtrTrajectory1d> &lon_trajectories,
                               const std::vector<PtrTrajectory1d> &lat_trajectories,
                               const std::array<double, 3> &init_s,
                               const std::shared_ptr<PathTimeGraph> &ptr_path_time_graph,
                               const std::vector<ReferencePoint> &reference_points,
                               const std::shared_ptr<ThreadPool> calc_pool);
  TrajectoryEvaluator(const PlanningTarget &planning_target,
                              const std::vector<std::pair<PtrTrajectory1d, PtrTrajectory1d>> &pair_trajectories,
                              const std::array<double, 3> &init_s,
                              const std::shared_ptr<PathTimeGraph> &ptr_path_time_graph,
                              const std::vector<ReferencePoint> &reference_points,
                              const std::shared_ptr<ThreadPool> calc_pool);
  double Evaluate(const PlanningTarget &planning_target, const PtrTrajectory1d &lon_trajectory,
                  const PtrTrajectory1d &lat_trajectory);
  void Evaluate(const PlanningTarget &planning_target, const PtrTrajectory1d &lon_trajectory,
  const PtrTrajectory1d &lat_trajectory, const std::shared_ptr<ThreadPool> calc_pool);

  double LatOffsetCost(const PtrTrajectory1d &lat_trajectory, const std::vector<double> &s_values, TrajFeature& cur_feature) const;

  double LatComfortCost(const std::shared_ptr<Curve1d> &lon_trajectory, const std::shared_ptr<Curve1d> &lat_trajectory) const;

  double LonObjectiveCost(const std::shared_ptr<Curve1d> &lon_trajectory, const std::vector<double> ref_s_dots, TrajFeature& cur_feature) const;

  double LonComfortCost(const std::shared_ptr<Curve1d> &lon_trajectory) const;

  double LonCollisionCost(const std::shared_ptr<Curve1d> &lon_trajectory) const;

  double CentripetalAccelerationCost(const std::shared_ptr<Curve1d> &lon_trajectory) const;

  bool fuzzy_within(const double v, const double lower, const double upper) const;

  bool IsValidLongitudinalTrajectory(const Curve1d &lon_trajectory) const;

  std::vector<double> ComputeLongitudinalGuideVelocity(const PlanningTarget &planning_target) const;

  std::pair<PtrTrajectory1d, PtrTrajectory1d> next_top_trajectory_pair();
  bool has_more_trajectory_pairs() const;
  size_t num_of_trajectory_pairs() const;
  double top_trajectory_pair_cost() const;

  std::mutex features_mutex_;
  std::vector<TrajFeature> traj_features;

private:
  //代价
  std::mutex cost_queue_mutex_;
  std::priority_queue<PairCost, std::vector<PairCost>, CostComparator> cost_queue_;
  std::vector<std::vector<std::pair<double, double>>> path_time_intervals_;
  std::shared_ptr<PathTimeGraph> path_time_graph_;
  std::vector<ReferencePoint> reference_points_;
  std::vector<double> reference_s_dot_;
  std::array<double, 3> init_s_;
  std::shared_ptr<ThreadPool> calc_pool_;
};

#endif