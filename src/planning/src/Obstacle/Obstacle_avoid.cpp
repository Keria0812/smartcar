#include "Obstacle_avoid.h"
#include "path_matcher.h"

lanelet::LaneletMapPtr map_;

Obstacle_avoid::Obstacle_avoid()
{
  ros::NodeHandle nh_;
  Pinnacle_Visualization = nh_.advertise<visualization_msgs::Marker>("efficient_area", 10);
  referenceline_pub = nh_.advertise<nav_msgs::Path>("ReferenceLine_Remove", 10);
  Points_Visualization = nh_.advertise<visualization_msgs::MarkerArray>("pinnacle_points", 10);
}
Obstacle_avoid::Obstacle_avoid(Eigen::Vector3d &origin_mgrs_point)
{
  origin_mgrs_point_ = origin_mgrs_point;
}

Obstacle_avoid::~Obstacle_avoid()
{
}

//求有效范围内障碍物与车的角度

//已知载具（矩形）的中心点坐标、长、宽和倾斜角度，求载具（矩形）四个边界点
//************************************
// Method:    GenerateCarBoundaryPoint
// FullName:  GenerateCarBoundaryPoint
// Access:    public
// Returns:   void
// Qualifier:根据载具中心坐标生成载具四个边界点的坐标
// Parameter: double car_length		载具长
// Parameter: double car_width		载具宽
// Parameter: PPoint & center 		中心点
// Parameter: double angle			倾斜角度 非弧度角 [0,360) x轴正方向为0度
// Parameter: PPoint & front_left	左前点
// Parameter: PPoint & back_left	左后点
// Parameter: PPoint & back_right	右后点
// Parameter: PPoint & front_right	右前点
//************************************
void Obstacle_avoid::CalculateCarBoundaryPoint(double car_length, double car_width, PPoint &center, double angle,
                                               PPoint &front_left, PPoint &back_left, PPoint &back_right,
                                               PPoint &front_right)
{
  //角度为负值，错误输入，返回
  // if (angle < 0)
  //   return;
  double X1, Y1, X2, Y2, X3, Y3, X4, Y4;
  //以(x,y)为中心点，不旋转的情况下四个顶点的坐标
  back_right.x = (center.x - car_length / 2);
  back_right.y = (center.y - car_width / 2);
  back_left.x = (center.x - car_length / 2);
  back_left.y = (center.y + car_width / 2);
  front_left.x = (center.x + car_length / 2);
  front_left.y = (center.y + car_width / 2);
  front_right.x = (center.x + car_length / 2);
  front_right.y = (center.y - car_width / 2);
  if (angle <= 0.00001)
    return;
  else
  {
    //按逆时针旋转角度center.x后的四个点坐标
    X1 = (back_right.x - center.x) * cos(angle) - (back_right.y - center.y) * sin(angle) + center.x;
    Y1 = (back_right.y - center.y) * cos(angle) + (back_right.x - center.x) * sin(angle) + center.y;
    X2 = (back_left.x - center.x) * cos(angle) - (back_left.y - center.y) * sin(angle) + center.x;
    Y2 = (back_left.y - center.y) * cos(angle) + (back_left.x - center.x) * sin(angle) + center.y;
    X3 = (front_left.x - center.x) * cos(angle) - (front_left.y - center.y) * sin(angle) + center.x;
    Y3 = (front_left.y - center.y) * cos(angle) + (front_left.x - center.x) * sin(angle) + center.y;
    X4 = (front_right.x - center.x) * cos(angle) - (front_right.y - center.y) * sin(angle) + center.x;
    Y4 = (front_right.y - center.y) * cos(angle) + (front_right.x - center.x) * sin(angle) + center.y;
    back_right.x = X1;
    back_right.y = Y1;
    back_left.x = X2;
    back_left.y = Y2;
    front_left.x = X3;
    front_left.y = Y3;
    front_right.x = X4;
    front_right.y = Y4;
  }
}

double Obstacle_avoid::getCross(PPoint p1, PPoint p2, PPoint p)
{
  return (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);
}

bool Obstacle_avoid::Inside_rectangle(PPoint p1, PPoint p2, PPoint p3, PPoint p4, PPoint p)
{
  if (getCross(p1, p2, p) * getCross(p3, p4, p) >= 0 && getCross(p2, p3, p) * getCross(p4, p1, p) >= 0)
  {
    return true;
  }
  return false;
}

bool Obstacle_avoid::GetClosestLanelet(geometry_msgs::Pose &search_pose, lanelet::LaneletMapPtr &lanelet_map_ptr_,
                                       lanelet::Lanelet *closest_lanelet, double distance_thresh)
{
  lanelet::BasicPoint2d search_point(search_pose.position.x, search_pose.position.y);
  std::vector<std::pair<double, lanelet::Lanelet>> nearest_lanelet =
      lanelet::geometry::findNearest(lanelet_map_ptr_->laneletLayer, search_point, 1);

  if (nearest_lanelet.empty() || nearest_lanelet.front().first > distance_thresh)
  {
    return false;
  }

  *closest_lanelet = nearest_lanelet.front().second;
  return true;
}

//障碍物有效区域显示
void Obstacle_avoid::visualization(PPoint center, double ego_heading, double length, double width)
{
  visualization_msgs::Marker marker;
  marker.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, ego_heading - M_PI / 2);
  marker.header.frame_id = "planning";
  marker.header.stamp = ros::Time::now();
  marker.ns = "basic_shapes";
  marker.id = 0; //注意了
  marker.type = visualization_msgs::Marker::CUBE;
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = center.x;
  marker.pose.position.y = center.y;
  marker.pose.position.z = 0;
  marker.scale.x = width;
  marker.scale.y = length;
  marker.scale.z = 0.0;
  marker.color.r = 1.0f;
  marker.color.g = 0.0f;
  marker.color.g = 0.0f;
  marker.color.g = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 0.0f;
  marker.color.a = 0.2;
  marker.lifetime = ros::Duration();
  Pinnacle_Visualization.publish(marker);
}

//显示障碍物顶点
void Obstacle_avoid::visualization_points(PPoint ob_left_front, PPoint ob_left_buttom, PPoint ob_right_front,
                                          PPoint ob_right_buttom)
{
  std::vector<PPoint> ob_vector;
  ob_vector.emplace_back(ob_left_front);
  ob_vector.emplace_back(ob_left_buttom);
  ob_vector.emplace_back(ob_right_front);
  ob_vector.emplace_back(ob_right_buttom);

  visualization_msgs::MarkerArray markerarray1;
  for (size_t i = 0; i < ob_vector.size(); i++)
  {
    visualization_msgs::Marker marker;
    marker.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 0);
    marker.header.frame_id = "planning";
    marker.header.stamp = ros::Time::now();
    marker.ns = "basic_shapes";
    marker.id = i; //注意了
    marker.type = visualization_msgs::Marker::CYLINDER;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = ob_vector[i].x;
    marker.pose.position.y = ob_vector[i].y;
    marker.pose.position.z = 0;
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.0;
    if (i == 0)
    {
      marker.color.r = 1.0f;
      marker.color.g = 0.0f;
      marker.color.b = 0.0f;
    }
    else if (i == 1)
    {
      marker.color.r = 0.0f;
      marker.color.g = 1.0f;
      marker.color.b = 0.0f;
    }
    else if (i == 2)
    {
      marker.color.r = 1.0f;
      marker.color.g = 0.0f;
      marker.color.b = 1.0f;
    }
    else if (i == 3)
    {
      marker.color.r = 0.0f;
      marker.color.g = 0.0f;
      marker.color.b = 1.0f;
    }

    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();
    markerarray1.markers.push_back(marker);
  }
  Points_Visualization.publish(markerarray1);
}

//发布移动的参考线并显示
void Obstacle_avoid::Publish(std::pair<std::vector<double>, std::vector<double>> &move_referenceline)
{
  referenceline.poses.clear();
  referenceline.header.frame_id = Frame_id;
  referenceline.header.stamp = ros::Time::now();
  geometry_msgs::PoseStamped pose_stamp;
  pose_stamp.header.frame_id = Frame_id;
  pose_stamp.header.stamp = ros::Time::now();

  for (int i = 0; i < move_referenceline.first.size(); i++)
  {
    pose_stamp.pose.position.x = move_referenceline.first[i];
    pose_stamp.pose.position.y = move_referenceline.second[i];
    pose_stamp.pose.position.z = 0;
    referenceline.poses.push_back(pose_stamp);
  }
  referenceline_pub.publish(referenceline); //只能发布一次
}

//产生pre_timepre_time秒的预测
prediction::Ob_Trajectory Obstacle_avoid::Generater_Trajectory(geometry_msgs::Pose ob_pos, double pre_time, double obstacle_theta, double obstacle_velocity)
{
  prediction::Ob_Trajectory result;
  std::vector<TrajectoryPoint> Trajectories;
  Eigen::MatrixXd ob_points;
  ob_points = Eigen::MatrixXd::Zero(2, 3); //初始化零矩阵
  ob_points(0, 0) = ob_pos.position.x;
  ob_points(0, 1) = ob_pos.position.y;
  ob_points(0, 2) = 0;

  ob_points(1, 0) = ob_pos.position.x + pre_time * obstacle_velocity * cos(obstacle_theta);
  ob_points(1, 1) = ob_pos.position.y + pre_time * obstacle_velocity * sin(obstacle_theta);
  ob_points(1, 2) = 0;

  Eigen::MatrixXd path_point_after_interpolation;
  average_interpolation(ob_points, path_point_after_interpolation, pre_time); //线性插值

  double s = 0.0;
  double prev_x = 0.0;
  double prev_y = 0.0;
  double relative_time = 0.0;
  bool empty_path = true;
  std::vector<double> headings;
  std::vector<double> kappas;
  std::vector<double> dkappas;
  std::vector<double> accumulated_s;
  std::vector<std::pair<double, double>> xy_points;

  for (size_t i = 0; i < path_point_after_interpolation.rows(); i++)
  {
    xy_points.emplace_back(path_point_after_interpolation(i, 0), path_point_after_interpolation(i, 1));
  }

  if (!PathMatcher::ComputePathProfile(xy_points, &headings, &accumulated_s, &kappas, &dkappas))
  {
    ROS_WARN("obstacle prediction trajectory generate failed!");
  }
  // std::cout << "path_point_after_interpolation.rows():" << path_point_after_interpolation.rows() << "\n";

  for (int i = 0; i < path_point_after_interpolation.rows(); i++)//遍历每个预测轨迹点
  {
    TrajectoryPoint tra_;
    tra_.set_x(path_point_after_interpolation(i, 0)); // x
    tra_.set_y(path_point_after_interpolation(i, 1)); // y
    tra_.set_theta(headings[i]);
    tra_.set_v(obstacle_velocity); //假设未来匀速
    tra_.set_a(0);                 //匀速，那么a=0
    tra_.set_kappa(kappas[i]);
    tra_.set_dkappa(dkappas[i]);
    tra_.set_s(accumulated_s[i]);

    tra_.set_relative_time(relative_time);

    Trajectories.push_back(tra_);

    relative_time += Config_.FLAGS_trajectory_time_resolution;
  }

  result.Set_Trajectory(Trajectories);
  return result;
}

prediction::Ob_Trajectory Obstacle_avoid::Generater_Trajectory(const smartcar_msgs::DetectedObject &object)
{
  prediction::Ob_Trajectory result;
  std::vector<TrajectoryPoint> Trajectories;
  Eigen::MatrixXd ob_points;
  // ob_points = Eigen::MatrixXd::Zero(2, 3); //初始化零矩阵
  // ob_points(0, 0) = ob_pos.position.x;
  // ob_points(0, 1) = ob_pos.position.y;
  // ob_points(0, 2) = 0;

  // ob_points(1, 0) = ob_pos.position.x + pre_time * obstacle_velocity * cos(obstacle_theta);
  // ob_points(1, 1) = ob_pos.position.y + pre_time * obstacle_velocity * sin(obstacle_theta);
  // ob_points(1, 2) = 0;

  int num = object.trajectory_.trajectory_points.size();
  Eigen::MatrixXd path_point_after_interpolation = Eigen::MatrixXd::Zero(num, 5); //x, y, z, theat, v
  for (int i = 0; i < num; i++) {
    path_point_after_interpolation(i, 0) = object.trajectory_.trajectory_points[i].x;
    path_point_after_interpolation(i, 1) = object.trajectory_.trajectory_points[i].y;
    path_point_after_interpolation(i, 2) = object.trajectory_.trajectory_points[i].z;
    path_point_after_interpolation(i, 3) = object.trajectory_.trajectory_points[i].theta;
    path_point_after_interpolation(i, 4) = object.trajectory_.trajectory_points[i].v;
  }
  // average_interpolation(ob_points, path_point_after_interpolation, pre_time); //线性插值

  double s = 0.0;
  double prev_x = 0.0;
  double prev_y = 0.0;
  double relative_time = 0.0;
  bool empty_path = true;
  std::vector<double> headings;
  std::vector<double> kappas;
  std::vector<double> dkappas;
  std::vector<double> accumulated_s;
  std::vector<std::pair<double, double>> xy_points;

  for (size_t i = 0; i < path_point_after_interpolation.rows(); i++)
  {
    xy_points.emplace_back(path_point_after_interpolation(i, 0), path_point_after_interpolation(i, 1));
  }

  if (!PathMatcher::ComputePathProfile(xy_points, &headings, &accumulated_s, &kappas, &dkappas))
  {
    ROS_WARN("obstacle prediction trajectory generate failed!");
  }
  // std::cout << "path_point_after_interpolation.rows():" << path_point_after_interpolation.rows() << "\n";

  for (int i = 0; i < path_point_after_interpolation.rows(); i++)//遍历每个预测轨迹点
  {
    TrajectoryPoint tra_;
    tra_.set_x(path_point_after_interpolation(i, 0)); // x
    tra_.set_y(path_point_after_interpolation(i, 1)); // y
    // tra_.set_theta(headings[i]);
    tra_.set_theta(path_point_after_interpolation(i, 3));
    // tra_.set_v(obstacle_velocity); //假设未来匀速
    tra_.set_v(path_point_after_interpolation(i, 4));
    tra_.set_a(0);                 //匀速，那么a=0
    tra_.set_kappa(kappas[i]);
    tra_.set_dkappa(dkappas[i]);
    tra_.set_s(accumulated_s[i]);

    tra_.set_relative_time(relative_time);

    Trajectories.push_back(tra_);

    relative_time += Config_.FLAGS_trajectory_time_resolution;
  }

  result.Set_Trajectory(Trajectories);
  return result;
}

void Obstacle_avoid::average_interpolation(Eigen::MatrixXd &input, Eigen::MatrixXd &output, double pre_time)
{
  // 1.定义
  std::vector<Point3d_s> vec_3d;
  std::vector<Point3d_s> n_vec;
  Point3d_s p;
  const int INSERTPOINTNUMBER = pre_time / Config_.FLAGS_trajectory_time_resolution;

  //第一个点
  double start_x = input(0, 0);
  double start_y = input(0, 1);
  //最后一个点
  double end_x = input(1, 0);
  double end_y = input(1, 1);

  //在两点间插入INSERTPOINTNUMBER个点
  for (int i = 0; i < INSERTPOINTNUMBER; ++i)
  {
    //计算(x,y)两点的距离
    double sqrt_val = sqrt((end_x - start_x) * (end_x - start_x) + (end_y - start_y) * (end_y - start_y));
    //计算角度
    double sin_a = (end_y - start_y) / sqrt_val;
    double cos_a = (end_x - start_x) / sqrt_val;

    p.x = (start_x * (INSERTPOINTNUMBER - i) + end_x * i) / float(INSERTPOINTNUMBER);
    p.y = (start_y * (INSERTPOINTNUMBER - i) + end_y * i) / float(INSERTPOINTNUMBER);
    p.z = 0;
    vec_3d.push_back(p);
  }

  // 4.漏了终点，需要加上
  p.x = input(input.rows() - 1, 0);
  p.y = input(input.rows() - 1, 1);
  p.z = input(input.rows() - 1, 2);
  vec_3d.push_back(p);

  //传给输出矩阵output
  output = Eigen::MatrixXd::Zero(vec_3d.size(), 3);
  int j = 0;
  for (std::vector<Point3d_s>::iterator it = vec_3d.begin(); it != vec_3d.end(); it++)
  {
    output(j, 0) = (*it).x;
    output(j, 1) = (*it).y;
    output(j, 2) = (*it).z;
    j++;
  }
}
