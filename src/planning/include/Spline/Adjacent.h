#ifndef ADJACENT_H
#define ADJACENT_H
#include <lanelet2_extension/utility/utilities.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>
#include <vector>
using namespace Eigen;

struct Point3d_s
{
  double x;
  double y;
  double z;
};
class Adjacent
{
public:
  void average_interpolation(std::vector<double>& Wx, std::vector<double>& Wy, double interval_dis, double distance);
};
#endif  // ADJACENT_H