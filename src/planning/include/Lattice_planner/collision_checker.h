/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-04-23 19:56:39
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-01 22:33:57
 * @FilePath: /miniEV_copy/src/planning/include/Lattice_planner/collision_checker.h
 */
#pragma once
#include <memory>
#include <vector>
#include <map>
#include <limits>
#include <string>
#include <utility>
#include <iostream>
#include "reference_point.h"
#include "Obstacle.h"

#include "box2d.h"
#include "FrenetPath.h"
#include "path_time_graph.h"
#include <mutex>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
class CollisionChecker
{
public:
  CollisionChecker();

  CollisionChecker(const std::vector<const Obstacle *> &obstacles, const double ego_vehicle_s, const double ego_vehicle_d,
                   const std::vector<ReferencePoint> &discretized_reference_line,
                   const std::shared_ptr<PathTimeGraph> &ptr_path_time_graph);
  ~CollisionChecker();
  bool InCollision(const DiscretizedTrajectory &discretized_trajectory);

private:
  void BuildPredictedEnvironment(const std::vector<const Obstacle *> &obstacles, const double ego_vehicle_s,
                                 const double ego_vehicle_d,
                                 const std::vector<ReferencePoint> &discretized_reference_line);

  bool IsEgoVehicleInLane(const double ego_vehicle_s, const double ego_vehicle_d);

  bool IsObstacleBehindEgoVehicle(const Obstacle *obstacle, const double ego_vehicle_s,
                                  const std::vector<ReferencePoint> &discretized_reference_line);

private:
  boost::shared_mutex predicted_bounding_rectangles_mutex_;
  std::vector<std::vector<Box2d>> predicted_bounding_rectangles_;
  std::shared_ptr<PathTimeGraph> ptr_path_time_graph_;
};
