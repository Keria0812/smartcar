#ifndef NAIVE_MOTION_PREDICT_H
#define NAIVE_MOTION_PREDICT_H

#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <visualization_msgs/MarkerArray.h>
#include <smartcar_msgs/DetectedObject.h>
#include <smartcar_msgs/DetectedObjectArray.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <naive_motion_predict/common.h>
#include <naive_motion_predict/MapHandle.h>
#include <naive_motion_predict/path_read.h>

using namespace smartcar::prediction;

enum MotionModel : int
{
  CV = 0,    // constant velocity
  CTRV = 1,  // constant turn rate and velocity
  RM = 2,    // random motion
};

// 用于存储中心线匹配结果的结构体
struct CenterlineMatch {
    int centerline_idx;  // 中心线的索引
    int point_idx;       // 中心线上点的索引
    double distance;     // 到该点的距离
};

// 新增：多模态轨迹的结构体
struct TrajectoryMode {
    std::vector<smartcar_msgs::DetectedObject> trajectory_points;
    double probability;  // 该轨迹模式的概率
    std::string mode_type;  // "lane_follow", "lane_change_left", "lane_change_right" 等
};

class NaiveMotionPredict
{
private:
  // nodehandle
  ros::NodeHandle nh_;
  ros::NodeHandle private_nh_;

  // max prediction score
  const double MAX_PREDICTION_SCORE_;

  // ros publisher
  ros::Publisher predicted_objects_pub_;
  ros::Publisher predicted_paths_pub_;

  // ros Subscriber
  ros::Subscriber detected_objects_sub_;

  // prediction param
  double interval_sec_;
  int num_prediction_;
  double sensor_height_;
  double filter_out_close_object_threshold_;
  bool predictionByrecorded_trajectories_;
  std::string waypoints_file_;
  smartcar_msgs::My_TrajectoryArray g_lanes;
  smartcar_msgs::My_Trajectory gWaypoints, gWaypoints_fix_time;
  
  // 中心线预测相关变量
  bool predictionByCenterline_;
  std::vector<smartcar_msgs::My_Trajectory> centerlines_;
  smartcar::prediction::MapHandle map_handle_;
  
  // 新增：多模态预测相关变量
  bool predictionMultiModal_;
  double lane_change_probability_;  // 车道变换的基础概率
  double lane_follow_probability_;  // 沿车道行驶的基础概率

  void objectsCallback(const smartcar_msgs::DetectedObjectArray& input);

  void initializeROSmarker(const std_msgs::Header& header, const geometry_msgs::Point& position, 
                           const std::string object_id, visualization_msgs::Marker& predicted_line,
                           const std::string& mode_type = "lane_follow");

  void makePrediction(const smartcar_msgs::DetectedObject& object,
                      std::vector<smartcar_msgs::DetectedObject>& predicted_objects,
                      visualization_msgs::Marker& predicted_line);

  void makePredictionByRecord(const smartcar_msgs::DetectedObject& object,
                      std::vector<smartcar_msgs::DetectedObject>& predicted_objects,
                      visualization_msgs::Marker& predicted_line); 
                      
  // 基于中心线的预测方法
  void makePredictionByCenterline(const smartcar_msgs::DetectedObject& object,
                      std::vector<smartcar_msgs::DetectedObject>& predicted_objects,
                      visualization_msgs::Marker& predicted_line);

  // 新增：多模态预测方法
  void makePredictionMultiModal(const smartcar_msgs::DetectedObject& object,
                      std::vector<TrajectoryMode>& trajectory_modes,
                      visualization_msgs::MarkerArray& predicted_lines);
                      
  // 生成沿车道行驶的轨迹
  void generateLaneFollowTrajectory(const smartcar_msgs::DetectedObject& object,
                      const CenterlineMatch& match,
                      TrajectoryMode& trajectory_mode,
                      visualization_msgs::Marker& predicted_line);
                      
  // 生成车道变换轨迹
  void generateLaneChangeTrajectory(const smartcar_msgs::DetectedObject& object,
                      const CenterlineMatch& source_match,
                      const CenterlineMatch& target_match,
                      const std::string& direction,
                      TrajectoryMode& trajectory_mode,
                      visualization_msgs::Marker& predicted_line);

  // 查找相邻车道/中心线
  std::vector<CenterlineMatch> findAdjacentCenterlines(const smartcar_msgs::DetectedObject& object,
                                            const CenterlineMatch& current_match);

  // 加载中心线文件
  void loadCenterlineFiles(const std::vector<std::string>& centerline_files);

  // 查找最近的中心线点
  CenterlineMatch findClosestCenterlinePoint(double x, double y);

  smartcar_msgs::DetectedObject generatePredictedObject(const smartcar_msgs::DetectedObject& object);

  smartcar_msgs::DetectedObject moveConstantVelocity(const smartcar_msgs::DetectedObject& object);

  smartcar_msgs::DetectedObject moveConstantTurnRateVelocity(const smartcar_msgs::DetectedObject& object);

  double generateYawFromQuaternion(const geometry_msgs::Quaternion& quaternion);

  bool isObjectValid(const smartcar_msgs::DetectedObject &in_object);

public:
  NaiveMotionPredict();
  ~NaiveMotionPredict();
};

#endif  // NAIVE_MOTION_PREDICT_H















// /*
//  * @Copyright: jinxiaoxin@whut.edu.cn
//  * @Author: jinxiaoxin235
//  * @Date: 2023-04-23 19:56:39
//  * @LastEditors: xining095@whut.edu.cn
//  * @LastEditTime: 2025-03-23
//  * @FilePath: /miniEV_grad_xn/src/prediction/motion_predictor/naive_motion_predict/include/naive_motion_predict/naive_motion_predict.h
//  */

//  #ifndef NAIVE_MOTION_PREDICT_H
//  #define NAIVE_MOTION_PREDICT_H
 
//  #include <ros/ros.h>
 
//  #include <tf/transform_datatypes.h>
 
//  #include <visualization_msgs/MarkerArray.h>
 
//  #include <smartcar_msgs/DetectedObject.h>
//  #include <smartcar_msgs/DetectedObjectArray.h>
//  #include <string>
//  #include <iostream>
//  #include <vector>
//  #include <fstream>
//  #include <sstream>
//  #include <naive_motion_predict/common.h>
//  #include <naive_motion_predict/MapHandle.h>
//  #include <naive_motion_predict/path_read.h>
 
//  using namespace smartcar::prediction;
 
//  enum MotionModel : int
//  {
//    CV = 0,    // constant velocity
//    CTRV = 1,  // constant turn rate and velocity
//    RM = 2,    // random motion
//  };
 
//  // 用于存储中心线匹配结果的结构体
//  struct CenterlineMatch {
//      int centerline_idx;  // 中心线的索引
//      int point_idx;       // 中心线上点的索引
//      double distance;     // 到该点的距离
//  };
 
//  class NaiveMotionPredict
//  {
//  private:
//    // nodehandle
//    ros::NodeHandle nh_;
//    ros::NodeHandle private_nh_;
 
//    // max prediction score
//    const double MAX_PREDICTION_SCORE_;
 
//    // ros publisher
//    ros::Publisher predicted_objects_pub_;
//    ros::Publisher predicted_paths_pub_;
 
//    // ros Subscriber
//    ros::Subscriber detected_objects_sub_;
 
//    // prediction param
//    double interval_sec_;
//    int num_prediction_;
//    double sensor_height_;
//    double filter_out_close_object_threshold_;
//    bool predictionByrecorded_trajectories_;
//    std::string waypoints_file_;
//    smartcar_msgs::My_TrajectoryArray g_lanes;
//    smartcar_msgs::My_Trajectory gWaypoints, gWaypoints_fix_time;
   
//    // 中心线预测相关变量
//    bool predictionByCenterline_;
//    std::vector<smartcar_msgs::My_Trajectory> centerlines_;
//    smartcar::prediction::MapHandle map_handle_;
 
//    void objectsCallback(const smartcar_msgs::DetectedObjectArray& input);
 
//    void initializeROSmarker(const std_msgs::Header& header, const geometry_msgs::Point& position, const std::string object_id,
//                             visualization_msgs::Marker& predicted_line);
 
//    void makePrediction(const smartcar_msgs::DetectedObject& object,
//                        std::vector<smartcar_msgs::DetectedObject>& predicted_objects,
//                        visualization_msgs::Marker& predicted_line);
 
//    void makePredictionByRecord(const smartcar_msgs::DetectedObject& object,
//                        std::vector<smartcar_msgs::DetectedObject>& predicted_objects,
//                        visualization_msgs::Marker& predicted_line); 
                       
//    // 基于中心线的预测方法
//    void makePredictionByCenterline(const smartcar_msgs::DetectedObject& object,
//                        std::vector<smartcar_msgs::DetectedObject>& predicted_objects,
//                        visualization_msgs::Marker& predicted_line);
 
//    // 加载中心线文件
//    void loadCenterlineFiles(const std::vector<std::string>& centerline_files);
 
//    // 查找最近的中心线点
//    CenterlineMatch findClosestCenterlinePoint(double x, double y);
 
//    smartcar_msgs::DetectedObject generatePredictedObject(const smartcar_msgs::DetectedObject& object);
 
//    smartcar_msgs::DetectedObject moveConstantVelocity(const smartcar_msgs::DetectedObject& object);
 
//    smartcar_msgs::DetectedObject moveConstantTurnRateVelocity(const smartcar_msgs::DetectedObject& object);
 
//    double generateYawFromQuaternion(const geometry_msgs::Quaternion& quaternion);
 
//    bool isObjectValid(const smartcar_msgs::DetectedObject &in_object);
 
//  public:
//    NaiveMotionPredict();
//    ~NaiveMotionPredict();
//  };
 
//  #endif  // NAIVE_MOTION_PREDICT_H



