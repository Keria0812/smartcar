/*
由于调试画图,传给qt上位机
*/
#include "plot_data.h"
plot_data::plot_data()
{
  //   ros::param::get("FLAGS_trajectory_time_length", FLAGS_trajectory_time_length);
}

plot_data::~plot_data()
{
}

// 1.画障碍物的SL图
void plot_data::Plot_Obstacle_SL(ros::Publisher &pub_plot, std::vector<SL_Boundary> SL_Obstacle)
{
  geometry_msgs::PoseArray SL_Graphy;
  if (SL_Obstacle.size() > 0)
  {
    for (size_t i = 0; i < SL_Obstacle.size(); i++)
    {
      //打印
      // std::cout << "obstacle_id:" << SL_Obstacle[i].obstacle_id << std::endl;
      // map<string, double>::iterator it = SL_Obstacle[i].SL_Max_Min.begin();
      // while (it != SL_Obstacle[i].SL_Max_Min.end())
      // {
      //   std::cout << it->first << ":";
      //   std::cout << it->second << std::endl;
      //   it++;
      // }
      //画图SL
      geometry_msgs::Pose posess1, posess2, posess3, posess4;
      posess1.position.x = SL_Obstacle[i].start_s_;
      posess1.position.y = SL_Obstacle[i].start_l_;
      posess2.position.x = SL_Obstacle[i].start_s_;
      posess2.position.y = SL_Obstacle[i].end_l_;
      posess3.position.x = SL_Obstacle[i].end_s_;
      posess3.position.y = SL_Obstacle[i].end_l_;
      posess4.position.x = SL_Obstacle[i].end_s_;
      posess4.position.y = SL_Obstacle[i].start_l_;
      SL_Graphy.poses.push_back(posess1);
      SL_Graphy.poses.push_back(posess2);
      SL_Graphy.poses.push_back(posess3);
      SL_Graphy.poses.push_back(posess4);
    }
    pub_plot.publish(SL_Graphy);
  }
}

// 2.画障碍物的ST图
void plot_data::Plot_Obstacle_ST(ros::Publisher &pub_plot, std::vector<ST_Boundary> ST_Obstacle)
{
  geometry_msgs::PoseArray ST_Graphy;
  if (ST_Obstacle.size() > 0)
  {
    for (size_t i = 0; i < ST_Obstacle.size(); i++)
    {
      //打印
      // std::cout << "obstacle_id:" << ST_Obstacle[i].obstacle_id << std::endl;
      // std::cout << "(" << ST_Obstacle[i].bottom_left_point.first << "," <<
      // ST_Obstacle[i].bottom_left_point.second << ")" << std::endl; std::cout << "(" <<
      // ST_Obstacle[i].upper_left_point.first << "," << ST_Obstacle[i].upper_left_point.second << ")" <<
      // std::endl; std::cout << "(" << ST_Obstacle[i].upper_right_point.first << "," <<
      // ST_Obstacle[i].upper_right_point.second << ")" << std::endl; std::cout << "(" <<
      // ST_Obstacle[i].bottom_right_point.first << "," << ST_Obstacle[i].bottom_right_point.second << ")" <<
      // std::endl; std::cout << "/////////////////////////////////////" << std::endl;
      //画图SL
      geometry_msgs::Pose posess1, posess2, posess3, posess4;
      posess1.position.x = ST_Obstacle[i].bottom_left_point_.t();
      posess1.position.y = ST_Obstacle[i].bottom_left_point_.s();
      posess2.position.x = ST_Obstacle[i].upper_left_point_.t();
      posess2.position.y = ST_Obstacle[i].upper_left_point_.s();
      posess3.position.x = ST_Obstacle[i].upper_right_point_.t();
      posess3.position.y = ST_Obstacle[i].upper_right_point_.s();
      posess4.position.x = ST_Obstacle[i].bottom_right_point_.t();
      posess4.position.y = ST_Obstacle[i].bottom_right_point_.s();
      ST_Graphy.poses.push_back(posess1);
      ST_Graphy.poses.push_back(posess2);
      ST_Graphy.poses.push_back(posess3);
      ST_Graphy.poses.push_back(posess4);
    }
    pub_plot.publish(ST_Graphy);
  }
}