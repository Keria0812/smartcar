#ifndef LATTICE_RECORD_H
#define LATTICE_RECORD_H

#include "CubicSpline2D.h"
#include "lattice_planner.h"
#include "ThreadPool.h"
// #include "em_planner.h"
#include "PlanningTarget.h"
#include "plot_data.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include <string>
#include <vector>
#include "FrenetOptimalTrajectory.h"
#include "XmlDomDocument.h"
#include "reference_line.h"
#include "Obstacle_test.h"
#include <nav_msgs/OccupancyGrid.h>
// #include "dynamicvoronoi.h"
// #include "hybrid_a_star.h"
#include <mutex>
#include <smartcar_msgs/My_TrajectoryArray.h>
#include <smartcar_msgs/ACCTarget.h>
#include <smartcar_msgs/Location.h>
#include <atomic>
#include <thread>
#include "planning_conf.h"
#include <smartcar_msgs/Lane.h>
#include <smartcar_msgs/DetectedObjectArray.h>
#include <smartcar_msgs/ACCTarget.h>
#include <smartcar_msgs/ControlCommandStamped.h>


#include <memory>

using std::string;
using namespace std;
using namespace lanelet;

struct Point3D_ss
{
  double x;
  double y;
  double z;
};
struct State_ss
{
  double x;
  double y;
  double z;
  double pitch;
  double roll;
  double yaw;
};

typedef struct Car_Info {
    double Time_frame;
    double s;
    double x;  
    double y;
    double z;
    double roll;
    double pitch;
    double yaw;
    double length;
    double width;
    double height;
    double speed;
    double ax;
    double kappa;
    double dkappa;

    Car_Info(){
      s = 0.0;
      x = 0.0;
      y = 0.0;
      z = 0.0;
      roll = 0.0;
      pitch = 0.0;
      yaw = 0.0;
      length = 0.0;
      width = 0.0;
      height = 0.0;
      speed = 0.0;
      ax = 0.0;
      kappa = 0.0;
      dkappa = 0.0;
    }
}Car_Info;

class PlanningRecord
{
public:
  PlanningRecord(void);
  ~PlanningRecord(void);
  void thread_routing(void);
  void odom_call_back(const smartcar_msgs::Location& odom);
  // void start_pose_call_backs(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg);
  void goal_pose_call_backs(const smartcar_msgs::My_Trajectory &msg);
  // void setHybridMap(const nav_msgs::OccupancyGrid::Ptr map);
  void path_pose_call_backs(const smartcar_msgs::My_TrajectoryArray &path_point_);
  void update_path(const smartcar_msgs::My_Trajectory& msg);
  bool is_update_dynamic(nav_msgs::Path &trj_point_array, Car_Info &odom, int size);
  bool Approaching_Obstacles(vector<Point2D> Obstacles, nav_msgs::Odometry &odom, double distances);
  DiscretizedTrajectory FindDriveReferenceLineInfo();
  void ObstacleCallBack(const smartcar_msgs::DetectedObjectArray &msg);
  void egoSLPathCallback(const nav_msgs::Path &ego_SL_path);
  void samplePointsCallback(const nav_msgs::Path::ConstPtr& msg);


private:
  int cout;
  int use_lattice_planner; //选择规划方案
  double COLLISION_CHECK_THRESHOLD;
  double MaxT;
  double MinT;
  int go_sizes;
  int set_sizes;
  double Approaching_obstacles;
  int cross_Sizes;
  int setcross_Sizes;
  bool has_stop = false;           //是否需要停车,先默认不需要
  bool FLAGS_lateral_optimization; //选择二次规划

  // ROS
  // visual publish
  ros::Publisher pub_plot;
  ros::Publisher waypoints_pub_;
  ros::Publisher waypoints_vis_pub_;
  ros::Publisher local_paths_v;
  ros::Publisher local_paths_t;
  ros::Publisher local_paths_k;
  ros::Publisher Start_Dynamic;
  ros::Publisher waypoints_center_;
  ros::Publisher pub_sl_graph_;
  // visual sub
  ros::Subscriber odom_sub_;
  ros::Subscriber start_pose_subscriber_;
  ros::Subscriber goal_pose_subscriber_;
  ros::Subscriber path_pose_subscriber_;
  ros::Subscriber global_lane_subscriber_;

  ros::Subscriber location_pose_subscriber_;
  ros::Subscriber ego_SL_path_sub_;
  ros::Subscriber sub_sample_points_;

  ros::Subscriber subMap;

  // visualmsgs
  visualization_msgs::MarkerArray ObstacleArray;
  visualization_msgs::Marker marker;
  geometry_msgs::PoseArray pubLocalPath_v;
  geometry_msgs::PoseArray pubLocalPath_t;
  geometry_msgs::PoseArray pubLocalPath_k;

  //变量
  nav_msgs::Path traj_points_; //局部规划的轨迹,nav_msgs类型

  nav_msgs::Path ego_SL_human_path_; //局部规划的轨迹,nav_msgs类型
  nav_msgs::Path learning_sample_points_; //局部规划的轨迹,nav_msgs类型

  bool update_human_path_ = false;
  bool update_sample_points_ = false;

  double d0;                   //初始的横向偏移值 [m]
  double dd0;                  //初始的横向速度 [m/s]
  double ddd0;                 //初始的横向加速度 [m/s^2]
  double init_lon_state;       //初始的纵向值[m]
  double ds0;                  //初始的纵向速度[m/s]
  double dds0;                 //初始的纵向加速度[m/ss]
  double init_relative_time;   //规划起始点的时间
  double x_init;
  double y_init;
  double z_init;
  double v_init;
  double a_init;
  double theta_init;
  double theta_end;
  double kappa_init;
  double dkappa_init;

  std_msgs::String start_dynamic;  //判断局部规划是否开始
  DiscretizedTrajectory best_path; //最佳路径
  FrenetPath *best_frenet_path;    //最佳路径,要析构
  // DynamicVoronoi voronoiDiagram;   // The voronoi diagram

  //地图
  lanelet::projection::MGRSProjector projector;
  lanelet::GPSPoint origin_gps_pt_; //地图GPS的原点
  std::string file_path_;
  lanelet::LaneletMapPtr maps;
  routing::RoutingGraphUPtr routingGraph_;
  traffic_rules::TrafficRulesPtr trafficRules;
  nav_msgs::OccupancyGrid::Ptr grid;
  // visual sub
  ros::Subscriber odom_sub;
  ros::Subscriber start_pose_subscriber;
  ros::Subscriber goal_pose_subscriber;
  ros::Subscriber path_pose_subscriber;
  // thread
  boost::thread *routing_thread_;
  //对象
  LatticePlanner LP;
  // std::shared_ptr<LatticePlanner> LP;
  // EMPlanner EM;
  // HybridAStar hybrid_test;

  std::mutex mutex_;
 
  //接收的ros消息暂存在这，保证线程安全
  nav_msgs::Odometry pos_msg;
  nav_msgs::Path reference_line_msg;
  bool planning_by_learning_ = false;

  std::atomic_bool pos_msg_update = ATOMIC_FLAG_INIT;
  std::atomic_bool reference_line_msg_update = ATOMIC_FLAG_INIT;
  std::atomic_bool objects_msg_update = ATOMIC_FLAG_INIT;

  std::atomic_bool pos_msg_init = ATOMIC_FLAG_INIT;
  std::atomic_bool reference_line_msg_init = ATOMIC_FLAG_INIT;
  std::atomic_bool objects_msg_init = ATOMIC_FLAG_INIT;

  Car_Info car_info;
  Car_Info match_status;

  int no_pos_count = 0;
  int no_chassis_count = 0;
  int no_reference_line_count = 0;

  ros::Publisher vis_feasible_paths;
  std::vector<DiscretizedTrajectory> multiple_best_path;
  std::vector<DiscretizedTrajectory> feasible_paths_;
  DiscretizedTrajectory final_best_path;
  ros::Publisher local_path_pub;
  ros::Publisher ACC_Target_;
  ros::Subscriber sub_obstacle;
  bool debug_pathfollow_ = false;
  bool enable_forecast_ = false;
  int reference_line_id = 1;
  int number_of_cpu_cores_ = 8;
  std::shared_ptr<ThreadPool> calc_pool_;

};

#endif
