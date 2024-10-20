/*
对参考曲线的插值
*/
#include "Adjacent.h"
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>

//正在使用：加权平均
void Adjacent::average_interpolation(std::vector<double>& Wx, std::vector<double>& Wy, double interval_dis,
                                     double distance)
{
  // 1.定义一个容器，类型为Point3d_s,即（x,y,z）
  std::vector<Point3d_s> vec_3d;
  std::vector<Point3d_s> n_vec;
  Point3d_s p;
  // 2.遍历
  // std::cout << " input.rows()" << input.rows() << std::endl;
  for (int i = 0; i < Wx.size() - 1; i++)
  {
    double dis = sqrt(pow(Wx[i + 1] - Wx[i], 2) + pow(Wy[i + 1] - Wy[i], 2));  //求两点的距离
    //两点距离太长的话就进行插点
    if (dis >= distance)
    {
      //计算(x,y)两点的距离
      double sqrt_val = sqrt(pow(Wx[i + 1] - Wx[i], 2) + pow(Wy[i + 1] - Wy[i], 2));  //求两点的距离
      //计算角度
      double sin_a = (Wy[i + 1] - Wy[i]) / sqrt_val;
      double cos_a = (Wx[i + 1] - Wx[i]) / sqrt_val;
      //两点之间要插值的插值点的数量
      int num = dis / interval_dis;  //分割了一下
      //插入点
      for (int j = 0; j < num; j++)
      {
        // i=0,j=0的时候其实是插入起点
        p.x = Wx[i] + j * interval_dis * cos_a;
        p.y = Wy[i] + j * interval_dis * sin_a;
        p.z = 0;
        vec_3d.push_back(p);
      }
    }
    // 3.有些点原本比较近，不需要插点，但是也要补进去，不然会缺失,dis >= 1防止点太密集
    else if (dis < distance)
    {
      p.x = Wx[i];
      p.y = Wy[i];
      p.z = 0;
      vec_3d.push_back(p);
    }
  }
  // 4.漏了终点，需要加上
  p.x = Wx[Wx.size() - 1];
  p.y = Wy[Wx.size() - 1];
  p.z = 0;
  vec_3d.push_back(p);

  //再转为Wx和Wy
  for (std::vector<Point3d_s>::iterator it = vec_3d.begin(); it != vec_3d.end(); it++)
  {
    Wx.push_back((*it).x);
    Wy.push_back((*it).y);
  }
}