#pragma once
#include <ros/ros.h>
#include "boundarys.h"

class plot_data
{
private:
  /* data */
public:
  plot_data();
  ~plot_data();
  void Plot_Obstacle_SL(ros::Publisher &pub_plot, std::vector<SL_Boundary> SL_Obstacle);
  void Plot_Obstacle_ST(ros::Publisher &pub_plot, std::vector<ST_Boundary> ST_Obstacle);
};
