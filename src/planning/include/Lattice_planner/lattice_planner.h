/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-04-23 19:56:39
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-04 23:02:34
 * @FilePath: /miniEV_copy/src/planning/include/Lattice_planner/lattice_planner.h
 */
#ifndef LATTICE_PLANNER_H
#define LATTICE_PLANNER_H

#include "lattice_trajectory1d.h"
#include "trajectory_evaluator.h"
#include "trajectory1d_generator.h"
#include "PlanningTarget.h"
#include "path_time_graph.h"
#include "collision_checker.h"
#include "constraint_checker.h"
#include "trajectory_combiner.h"

class LatticePlanner
{
public:
  LatticePlanner() = default;
  ~LatticePlanner() = default;
  DiscretizedTrajectory LatticePlan(
      const TrajectoryPoint &planning_init_point,
      const PlanningTarget &planning_target,
      const std::vector<const Obstacle *> &obstacles,
      const std::vector<double> &accumulated_s,
      const std::vector<ReferencePoint> &reference_points, const bool &lateral_optimization,
      const double &init_relative_time, const double lon_decision_horizon,
      std::vector<DiscretizedTrajectory> &feasible_paths,
      DiscretizedTrajectory &ego_human_path,
      std::vector<TrajFeature> &features,
      std::shared_ptr<ThreadPool> calc_pool,
      std::vector<DiscretizedTrajectory> &cur_sl_graph,
      std::vector<size_t> &analysis_data
      );
  DiscretizedTrajectory LatticePlanbyMySampleModel(
      const TrajectoryPoint &planning_init_point,
      const PlanningTarget &planning_target,
      const std::vector<const Obstacle *> &obstacles,
      const std::vector<double> &accumulated_s,
      const std::vector<ReferencePoint> &reference_points, const bool &lateral_optimization,
      const double &init_relative_time, const double lon_decision_horizon,
      std::vector<DiscretizedTrajectory> &feasible_paths,
      DiscretizedTrajectory &learning_sample_points,

      std::vector<TrajFeature> &features,
      std::shared_ptr<ThreadPool> calc_pool,
      std::vector<DiscretizedTrajectory> &cur_sl_graph,
      std::vector<size_t> &analysis_data
      );

  void ComputeInitFrenetState(const ReferencePoint &matched_point,
                            const TrajectoryPoint &cartesian_state,
                            std::array<double, 3> *ptr_s,
                            std::array<double, 3> *ptr_d);
  void SamplepointsFilter(DiscretizedTrajectory &learning_sample_points);
private:
  TrajectoryCombiner trajectorycombiner;
  DiscretizedTrajectory sample_pointsbylearing_;
  ConstraintChecker constraintchecker_;
};

#endif