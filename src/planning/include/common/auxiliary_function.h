#ifndef AUXILIARY_FUNCTION_H
#define AUXILIARY_FUNCTION_H

#include <ros/ros.h>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <string>
#include <iostream>
#include <lanelet2_core/primitives/Lanelet.h>
#include <lanelet2_io/Io.h>
#include <lanelet2_projection/UTM.h>
#include <lanelet2_routing/Route.h>
#include <lanelet2_routing/RoutingCost.h>
#include <lanelet2_routing/RoutingGraph.h>
#include <lanelet2_routing/RoutingGraphContainer.h>
#include <lanelet2_traffic_rules/TrafficRulesFactory.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Path.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <visualization_msgs/MarkerArray.h>
#include <boost/thread.hpp>
// msg
#include <lanelet2_extension/io/autoware_osm_parser.h>
#include <lanelet2_extension/projection/mgrs_projector.h>
#include <lanelet2_extension/utility/message_conversion.h>
#include <lanelet2_extension/utility/utilities.h>
#include <lanelet2_extension/regulatory_elements/autoware_traffic_light.h>
#include <lanelet2_extension/utility/query.h>
#include <lanelet2_extension/visualization/visualization.h>
#include <autoware_lanelet2_msgs/MapBin.h>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include "reference_point.h"
#include "CubicSpline2D.h"

using namespace lanelet;
class Auxiliary
{
public:
  Auxiliary();
  std::pair<double, double> Find_nearest_piont(std::pair<double, double> ObastaclePoint,
                                               std::pair<std::vector<double>, std::vector<double>> reference_path_,
                                               int& index_ob);
  bool getClosestLanelet(const geometry_msgs::PoseArray& ObastaclePoint, const lanelet::LaneletMapPtr& lanelet_map_ptr_,
                         lanelet::Lanelet* closest_lanelet, const Eigen::Vector3d origin_mgrs_point,
                         double distance_thresh);
  double find_s(CubicSpline2D* csp, double x, double y, double s0, std::vector<double> s);
  double cartesian_to_frenet(std::pair<double, double> ObastaclePoint, std::pair<double, double> rxy, double rtheta);
  geometry_msgs::Pose search_pose;
};
#endif  // AUXILIARY_FUNCTION_H
