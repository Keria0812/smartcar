#pragma once
#include <ros/ros.h>
#include <string>
#include <vector>
#include <cmath>
#include <tf/tf.h>
#include <tf2/utils.h>
#include <boost/thread.hpp>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Vector3.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <eigen3/Eigen/Dense>

#include <lanelet2_core/primitives/Lanelet.h>
#include <lanelet2_io/Io.h>
#include <lanelet2_projection/UTM.h>
#include <lanelet2_routing/Route.h>
#include <lanelet2_routing/RoutingCost.h>
#include <lanelet2_routing/RoutingGraph.h>
#include <lanelet2_routing/RoutingGraphContainer.h>
#include <lanelet2_traffic_rules/TrafficRulesFactory.h>
#include <lanelet2_extension/projection/mgrs_projector.h>

#include "CubicSpline2D.h"
#include "path_struct.h"
#include "trajectoryPoint.h"
#include "Ob_prediction_trajectory.h"
#include <smartcar_msgs/DetectedObject.h>

//坐标点
struct PPoint
{
  double x; //坐标点x坐标
  double y; //坐标点y坐标
  PPoint(double _x, double _y) : x(_x), y(_y){};
  PPoint() : x(0), y(0){};
  PPoint(const PPoint &other) : x(other.x), y(other.y){};
  const PPoint operator=(const PPoint &p)
  {
    x = p.x;
    y = p.y;
    return *this;
  }
  bool operator==(const PPoint &p)
  {
    return (abs(x - p.x) < 0.0001 && abs(y - p.y) < 0.0001);
  }
};

class Obstacle_avoid
{
private:
  Eigen::Vector3d origin_mgrs_point_;
  ros::Publisher Pinnacle_Visualization;
  PPoint p1, p2, p3, p4;
  PPoint p;
  nav_msgs::Path referenceline;
  ros::Publisher referenceline_pub;
  ros::Publisher Points_Visualization;

public:
  Obstacle_avoid();
  Obstacle_avoid(Eigen::Vector3d &origin_mgrs_point);
  ~Obstacle_avoid();
  void CalculateCarBoundaryPoint(double car_length, double car_width, PPoint &center, double angle, PPoint &front_left,
                                 PPoint &back_left, PPoint &back_right, PPoint &front_right);
  void visualization(PPoint center, double ego_heading, double length, double width);
  void visualization_points(PPoint ob_left_front, PPoint ob_left_buttom, PPoint ob_right_front, PPoint ob_right_buttom);
  void Publish(std::pair<std::vector<double>, std::vector<double>> &path_point_after_interpolation_);
  double getCross(PPoint p1, PPoint p2, PPoint p);
  bool Inside_rectangle(PPoint p1, PPoint p2, PPoint p3, PPoint p4, PPoint p);

  bool GetClosestLanelet(geometry_msgs::Pose &search_pose, lanelet::LaneletMapPtr &lanelet_map_ptr_,
                         lanelet::Lanelet *closest_lanelet, double distance_thresh);

  struct Point3d_s
  {
    double x;
    double y;
    double z;
  };

  //用此函数模拟动态障碍物的预测轨迹，即：前探距离=当前位置*预测距离，然后线性插值，来得到预测轨迹点
  prediction::Ob_Trajectory Generater_Trajectory(geometry_msgs::Pose ob_pos, double pre_time, double obstacle_theta, double obstacle_velocity);
  prediction::Ob_Trajectory Generater_Trajectory(const smartcar_msgs::DetectedObject &object);
  void average_interpolation(Eigen::MatrixXd &input, Eigen::MatrixXd &output, double pre_time);
};
