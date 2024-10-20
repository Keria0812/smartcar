/*
一些辅助函数
给生成ST和SL障碍物图等使用
*/
#include "auxiliary_function.h"

Auxiliary::Auxiliary()
{
}

//返回：最近的点
//这里的reference_path_最好是先识别出障碍物是否在道路内，在的话计算出相应的Lanelet,再减少计算量。
std::pair<double, double>
Auxiliary::Find_nearest_piont(std::pair<double, double> ObastaclePoint,
                              std::pair<std::vector<double>, std::vector<double>> reference_path_, int& index_ob)
{
  std::pair<double, double> nearest;
  int index = 0;
  double min_val = 1000;
  double distance;
  for (size_t i = 0; i < reference_path_.first.size(); i++)
  {
    distance = sqrt(pow(ObastaclePoint.first - reference_path_.first[i], 2) +
                    pow(ObastaclePoint.second - reference_path_.second[i], 2));
    if (distance < min_val)
    {
      min_val = distance;  //更新
      index = i;
    }
  }
  index_ob = index;
  nearest.first = reference_path_.first[index];
  nearest.second = reference_path_.second[index];
  return nearest;
}

//判断是否通过Lanelet获得了最近车道lane，传入：障碍物的4个顶点坐标， lanelet地图，最近车道，距离阈值
//如果障碍物的顶点坐标有在车道内的，返回true，否则false。
bool Auxiliary::getClosestLanelet(const geometry_msgs::PoseArray& ObastaclePoint,
                                  const lanelet::LaneletMapPtr& lanelet_map_ptr_, lanelet::Lanelet* closest_lanelet,
                                  const Eigen::Vector3d origin_mgrs_point, double distance_thresh)
{
  // std::cout << "This obstacle is effective " << std::endl;
  bool result = false;
  //遍历障碍物4个顶点
  if (ObastaclePoint.poses.size() > 0)
  {
    for (size_t i = 0; i < ObastaclePoint.poses.size(); i++)
    {
      search_pose.position.x = ObastaclePoint.poses[i].position.x + origin_mgrs_point(0);
      search_pose.position.y = ObastaclePoint.poses[i].position.y + origin_mgrs_point(1);
      lanelet::BasicPoint2d search_point(search_pose.position.x, search_pose.position.y);
      std::vector<std::pair<double, lanelet::Lanelet>> nearest_lanelet =
          lanelet::geometry::findNearest(lanelet_map_ptr_->laneletLayer, search_point, 1);
      if (!nearest_lanelet.empty())  //如果有一个点在车道内，就return
      {
        if (nearest_lanelet.front().first < distance_thresh)
        {
          // std::cout << "This obstacle is effective " << std::endl;
          *closest_lanelet = nearest_lanelet.front().second;
          result = true;
          break;
        }
      }
    }
  }
  return result;
}
//根据x,y求s
double Auxiliary::find_s(CubicSpline2D* csp, double x, double y, double s0, std::vector<double> s)
{
  double s_closest = s0;
  double closest = INFINITY;
  double si = s.front();
  do
  {
    double px = csp->calc_x(si);
    double py = csp->calc_y(si);
    double dist = sqrt(pow((x - px), 2) + pow((y - py), 2));
    if (dist < closest)
    {
      closest = dist;
      s_closest = si;
    }
    si += 0.1;
  } while (si < s.back());
  return s_closest;
}

//传入：障碍物中心点ObastaclePoint， 最近的参考点rxy
//输出：横向偏移
double Auxiliary::cartesian_to_frenet(std::pair<double, double> ObastaclePoint, std::pair<double, double> rxy,
                                      double rtheta)
{
  const double dx = ObastaclePoint.first - rxy.first;
  const double dy = ObastaclePoint.second - rxy.second;

  const double cos_theta_r = std::cos(rtheta);
  const double sin_theta_r = std::sin(rtheta);

  const double cross_rd_nd = cos_theta_r * dy - sin_theta_r * dx;

  double ptr_d = std::copysign(std::sqrt(dx * dx + dy * dy), cross_rd_nd);

  return ptr_d;
}