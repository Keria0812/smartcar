cmake_minimum_required(VERSION 3.0.2)
project(planning)

# 在这里如果不设置，出现无法调试，直接执行结束
set(CMAKE_BUILD_TYPE "Debug")


## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

set(SRC_FILE
    src/Frenet/FrenetOptimalTrajectory.cpp
    src/Frenet/cartesian_frenet_conversion.cpp

    src/Polynomial/QuinticPolynomial.cpp
    src/Polynomial/QuarticPolynomial.cpp
    src/Polynomial/quartic_polynomial_curve1d.cpp
    src/Polynomial/quintic_polynomial_curve1d.cpp
    src/Polynomial/polynomial_xd.cpp

    src/Spline/CubicSpline1D.cpp
    src/Spline/CubicSpline2D.cpp
    src/Spline/Adjacent.cpp
    src/Spline/affine_constraint.cpp
    src/Spline/spline_1d_constraint.cpp
    src/Spline/spline_1d_kernel.cpp
    src/Spline/spline_seg_kernel.cpp
    src/Spline/spline_1d_seg.cpp
    src/Spline/spline_1d_solver.cpp
    src/Spline/spline_1d.cpp
    src/Spline/active_set_spline_1d_solver.cpp
    src/Spline/active_set_qp_solver.cpp
 
    src/Obstacle/Obstacle.cpp
    src/Obstacle/Obstacle_test.cpp
    src/Obstacle/Obstacle_avoid.cpp
    src/Obstacle/boundarys.cpp
    src/Obstacle/Ob_prediction_trajectory.cpp

    src/Lattice_planner/lattice_planner.cpp
    src/Lattice_planner/trajectory_evaluator.cpp
    src/Lattice_planner/piecewise_acceleration_trajectory1d.cpp
    src/Lattice_planner/lattice_trajectory1d.cpp
    src/Lattice_planner/trajectory_combiner.cpp
    src/Lattice_planner/trajectory1d_generator.cpp
    src/Lattice_planner/end_condition_sampler.cpp
    src/Lattice_planner/feasible_region.cpp
    src/Lattice_planner/path_time_graph.cpp
    src/Lattice_planner/collision_checker.cpp
    src/Lattice_planner/constraint_checker.cpp
    src/Lattice_planner/piecewise_braking_trajectory_generator.cpp
    src/Lattice_planner/prediction_querier.cpp

    src/common/Config.cpp
    src/common/planning_conf.cpp
    src/common/angle.cpp
    src/common/auxiliary_function.cpp
    src/common/box2d.cpp
    src/common/line_segment2d.cpp
    src/common/math_utils.cpp
    src/common/plot_data.cpp
    src/common/polygon2d.cpp
    src/common/sin_table.cpp
    src/common/vec2d.cpp
    src/common/XmlDomDocument.cpp
    src/common/PlanningTarget.cpp
    src/common/speed_limit.cpp
    src/common/speed_data.cpp
    src/common/speed_limit_decider.cpp

    src/path/path_matcher.cpp
    src/path/path_data.cpp
    src/path/path_boundary.cpp
    src/path/path_bounds_decider.cpp
    src/path/path_matcher.cpp
    src/path/FrenetPath.cpp
    src/path/trajectoryPoint.cpp
    src/path/path_points.cpp

    src/ReferenceLine/reference_point.cpp
    src/ReferenceLine/reference_line.cpp
    src/ReferenceLine/reference_line_info.cpp

    src/QP/constant_jerk_trajectory1d.cpp
    src/QP/lateral_osqp_optimizer.cpp
    src/QP/lateral_qp_optimizer.cpp
    src/QP/piecewise_jerk_trajectory1d.cpp
    src/QP/piecewise_jerk_path_problem.cpp
    src/QP/piecewise_jerk_problem.cpp
    src/QP/piecewise_jerk_speed_problem.cpp
    src/QP/osqp_spline_1d_solver.cpp
    src/QP/piecewise_linear_constraint.cpp
    src/QP/piecewise_linear_generator.cpp
    src/QP/piecewise_linear_kernel.cpp
    src/QP/qp_solver.cpp
    src/QP/fem_1d_qp_problem.cpp
    src/QP/fem_1d_expanded_jerk_qp_problem.cpp

    src/dynamic_node.cpp
    src/dynamic_routing.cpp
)

set(SRC_FILE_RECORD
    src/Frenet/FrenetOptimalTrajectory.cpp
    src/Frenet/cartesian_frenet_conversion.cpp

    src/Polynomial/QuinticPolynomial.cpp
    src/Polynomial/QuarticPolynomial.cpp
    src/Polynomial/quartic_polynomial_curve1d.cpp
    src/Polynomial/quintic_polynomial_curve1d.cpp
    src/Polynomial/polynomial_xd.cpp

    src/Spline/CubicSpline1D.cpp
    src/Spline/CubicSpline2D.cpp
    src/Spline/Adjacent.cpp
    src/Spline/affine_constraint.cpp
    src/Spline/spline_1d_constraint.cpp
    src/Spline/spline_1d_kernel.cpp
    src/Spline/spline_seg_kernel.cpp
    src/Spline/spline_1d_seg.cpp
    src/Spline/spline_1d_solver.cpp
    src/Spline/spline_1d.cpp
    src/Spline/active_set_spline_1d_solver.cpp
    src/Spline/active_set_qp_solver.cpp
 
    src/Obstacle/Obstacle.cpp
    src/Obstacle/Obstacle_test.cpp
    src/Obstacle/Obstacle_avoid.cpp
    src/Obstacle/boundarys.cpp
    src/Obstacle/Ob_prediction_trajectory.cpp

    src/Lattice_planner/lattice_planner.cpp
    src/Lattice_planner/trajectory_evaluator.cpp
    src/Lattice_planner/piecewise_acceleration_trajectory1d.cpp
    src/Lattice_planner/lattice_trajectory1d.cpp
    src/Lattice_planner/trajectory_combiner.cpp
    src/Lattice_planner/trajectory1d_generator.cpp
    src/Lattice_planner/end_condition_sampler.cpp
    src/Lattice_planner/feasible_region.cpp
    src/Lattice_planner/path_time_graph.cpp
    src/Lattice_planner/collision_checker.cpp
    src/Lattice_planner/constraint_checker.cpp
    src/Lattice_planner/piecewise_braking_trajectory_generator.cpp
    src/Lattice_planner/prediction_querier.cpp

    src/common/Config.cpp
    src/common/planning_conf.cpp
    src/common/angle.cpp
    src/common/auxiliary_function.cpp
    src/common/box2d.cpp
    src/common/line_segment2d.cpp
    src/common/math_utils.cpp
    src/common/plot_data.cpp
    src/common/polygon2d.cpp
    src/common/sin_table.cpp
    src/common/vec2d.cpp
    src/common/XmlDomDocument.cpp
    src/common/PlanningTarget.cpp
    src/common/speed_limit.cpp
    src/common/speed_data.cpp
    src/common/speed_limit_decider.cpp

    src/path/path_matcher.cpp
    src/path/path_data.cpp
    src/path/path_boundary.cpp
    src/path/path_bounds_decider.cpp
    src/path/path_matcher.cpp
    src/path/FrenetPath.cpp
    src/path/trajectoryPoint.cpp
    src/path/path_points.cpp

    src/ReferenceLine/reference_point.cpp
    src/ReferenceLine/reference_line.cpp
    src/ReferenceLine/reference_line_info.cpp

    src/QP/constant_jerk_trajectory1d.cpp
    src/QP/lateral_osqp_optimizer.cpp
    src/QP/lateral_qp_optimizer.cpp
    src/QP/piecewise_jerk_trajectory1d.cpp
    src/QP/piecewise_jerk_path_problem.cpp
    src/QP/piecewise_jerk_problem.cpp
    src/QP/piecewise_jerk_speed_problem.cpp
    src/QP/osqp_spline_1d_solver.cpp
    src/QP/piecewise_linear_constraint.cpp
    src/QP/piecewise_linear_generator.cpp
    src/QP/piecewise_linear_kernel.cpp
    src/QP/qp_solver.cpp
    src/QP/fem_1d_qp_problem.cpp
    src/QP/fem_1d_expanded_jerk_qp_problem.cpp

    src/planning_record.cpp
    src/planning_record_node.cpp
)

find_package(catkin REQUIRED  COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  nav_msgs
  tf2_ros
  tf2_geometry_msgs

  lanelet2_core
  lanelet2_io
  lanelet2_maps
  lanelet2_projection
  lanelet2_routing
  lanelet2_traffic_rules
  lanelet2_validation
  lanelet2_extension

  object_msgs
  smartcar_msgs

)
find_package(Eigen3 QUIET)
find_package(OsqpEigen QUIET)
find_package(qpOASES QUIET)
find_package(yaml-cpp REQUIRED)


catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
   geometry_msgs
   lanelet2_core
   lanelet2_io
   lanelet2_maps
   lanelet2_projection
   lanelet2_routing
   lanelet2_traffic_rules
  DEPENDS
    Boost
)

include_directories(
  include/dynamic_routing
  include/Frenet
  include/Lattice_planner
  include/Obstacle
  include/Polynomial
  include/QP
  include/Spline
  include/Kalman

  include/ReferenceLine
  include/common
  include/path
  include/ReferenceLine

  ${EIGEN3_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
)


#planning node
add_executable(${PROJECT_NAME}_node ${SRC_FILE})
target_link_libraries(${PROJECT_NAME}_node  
  ${catkin_LIBRARIES} 
  osqp 
  -lxerces-c 
  qpOASES 
  yaml-cpp
)
#record node
add_executable(${PROJECT_NAME}_record_node ${SRC_FILE_RECORD})
target_link_libraries(${PROJECT_NAME}_record_node  
  ${catkin_LIBRARIES} 
  osqp 
  -lxerces-c 
  qpOASES 
  yaml-cpp
)
