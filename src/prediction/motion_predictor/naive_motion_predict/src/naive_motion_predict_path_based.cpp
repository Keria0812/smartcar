/*
 * @Copyright: 2018-2019 Autoware Foundation. All rights reserved.
 * @Author: jinxiaoxin235
 * @Date: 2023-04-23 19:56:39
 * @LastEditors: xining095@whut.edu.cn
 * @LastEditTime: 2025-03-23
 * @FilePath: src/prediction/motion_predictor/naive_motion_predict/src/naive_motion_predict.cpp
 * @NOTE: This version adds path-based unimodal trajectory prediction and multimodal trajectory prediction.
 */

#include <naive_motion_predict/naive_motion_predict.h>

NaiveMotionPredict::NaiveMotionPredict() :
  nh_(),
  private_nh_("~"),
  MAX_PREDICTION_SCORE_(1.0),
  map_handle_(3.75)  // 初始化地图处理对象，默认车道宽度3.75米
{
  private_nh_.param<double>("interval_sec", interval_sec_, 0.1);
  private_nh_.param<int>("num_prediction", num_prediction_, 80);
  private_nh_.param<double>("sensor_height_", sensor_height_, 0);
  private_nh_.param<double>("filter_out_close_object_threshold", filter_out_close_object_threshold_, 1.5);
  private_nh_.param<bool>("predictionByrecorded_trajectories", predictionByrecorded_trajectories_, false);
  private_nh_.param<std::string>("waypoints_file", waypoints_file_, "/home/erro");
  
  // 添加中心线预测的参数
  private_nh_.param<bool>("predictionByCenterline", predictionByCenterline_, false);

  ROS_INFO_STREAM("predictionByrecorded_trajectories: " << predictionByrecorded_trajectories_);
  ROS_INFO_STREAM("predictionByCenterline: " << predictionByCenterline_);

  predicted_objects_pub_ = nh_.advertise<smartcar_msgs::DetectedObjectArray>("/prediction/motion_predictor/objects", 1);
  predicted_paths_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("/prediction/motion_predictor/path_markers", 10);
  detected_objects_sub_ = nh_.subscribe("/ITS/DetectObjects", 1, &NaiveMotionPredict::objectsCallback, this);

  // 如果启用基于中心线的预测，加载中心线文件
  if (predictionByCenterline_) {
    std::vector<std::string> centerline_files;
    private_nh_.param<std::vector<std::string>>("centerline_files", centerline_files, std::vector<std::string>());
    
    if (centerline_files.empty()) {
      ROS_WARN("predictionByCenterline is enabled but no centerline files specified.");
    } else {
      loadCenterlineFiles(centerline_files);
    }
  }
  
  // 已有的基于录制轨迹的预测初始化
  if (predictionByrecorded_trajectories_) {
    double road_width = 3.75;
    MapHandle map_handle(road_width);
    
    //1.得到全部轨迹文件名
    std::vector<std::string> files;
    get_all_files(waypoints_file_, files);
    for (auto &file : files) {
        std::cout << "file path: " << file << std::endl;
    }

    //2.提取有效的轨迹文件名
    std::vector<std::string> vaild_files;
    vaild_files = remove_erro_files(files, ".csv");
    for (auto &file : vaild_files) {
        std::cout << "vaild_files path: " << file << std::endl;
    }

    //3.读取轨迹，并根据轨迹名字获得object id
    for (long unsigned int i=0; i < vaild_files.size(); i++) {
        read_csv(vaild_files[i], gWaypoints);
        map_handle.TimeResample(gWaypoints, gWaypoints_fix_time);
        gWaypoints_fix_time.lane_id = map_handle.get_lane_id(vaild_files[i]);
        if (gWaypoints_fix_time.lane_id == -1) {
          ROS_WARN("no find car id");
          continue;
        }
        g_lanes.lanes.push_back(gWaypoints_fix_time);

        std::cout << "car id " << gWaypoints_fix_time.lane_id << std::endl;
    }
  }
}

NaiveMotionPredict::~NaiveMotionPredict()
{
}

// 新增：加载中心线文件
void NaiveMotionPredict::loadCenterlineFiles(const std::vector<std::string>& centerline_files) {
    centerlines_.clear();
    setlocale(LC_ALL,"");
    
    for (int i = 0; i < centerline_files.size(); i++) {
        smartcar_msgs::My_Trajectory centerline;
        centerline.lane_id = i;  // 为每条中心线分配一个ID
        
        // 读取中心线文件
        std::ifstream file(centerline_files[i]);
        if (!file.is_open()) {
            ROS_ERROR_STREAM("无法打开中心线文件: " << centerline_files[i]);
            continue;
        }
        
        std::string line;
        double relative_time = 0.0;
        
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            double x, y, heading;
            
            if (!(iss >> x >> y >> heading)) {
                continue;  // 跳过无效行
            }
            
            smartcar_msgs::My_Trajectory_Point point;
            point.x = x;
            point.y = y;
            point.theta = heading;
            point.relative_time = relative_time;
            relative_time += 0.1;  // 任意时间增量
            
            centerline.trajectory_points.push_back(point);
        }
        
        centerline.num = centerline.trajectory_points.size();
        
        if (centerline.num > 0) {
            centerlines_.push_back(centerline);
            ROS_INFO_STREAM("加载中心线 " << i << " 包含 " << centerline.num << " 个点");
        }
    }
    
    ROS_INFO_STREAM("总共加载了 " << centerlines_.size() << " 条中心线");
}

// 新增：查找最近的中心线点
CenterlineMatch NaiveMotionPredict::findClosestCenterlinePoint(double x, double y) {
    CenterlineMatch match;
    match.centerline_idx = -1;
    match.point_idx = -1;
    match.distance = std::numeric_limits<double>::max();
    
    for (int i = 0; i < centerlines_.size(); i++) {
        // 只有当中心线包含足够的点时才进行比较
        if (centerlines_[i].trajectory_points.size() < 2) {
            continue;
        }
        
        int nearest_point_idx = map_handle_.get_nearst_point(centerlines_[i], x, y);
        double dx = x - centerlines_[i].trajectory_points[nearest_point_idx].x;
        double dy = y - centerlines_[i].trajectory_points[nearest_point_idx].y;
        double distance = std::sqrt(dx*dx + dy*dy);
        
        if (distance < match.distance) {
            match.centerline_idx = i;
            match.point_idx = nearest_point_idx;
            match.distance = distance;
        }
    }
    
    return match;
}

void NaiveMotionPredict::initializeROSmarker(const std_msgs::Header& header, const geometry_msgs::Point& position,
                                             const std::string object_id, visualization_msgs::Marker& predicted_line)
{
  predicted_line.lifetime = ros::Duration(0.2);
  predicted_line.header.frame_id = "map";//header.frame_id;
  predicted_line.header.stamp = header.stamp;
  predicted_line.ns = "predicted_line";
  predicted_line.action = visualization_msgs::Marker::ADD;
  predicted_line.pose.orientation.w = 1.0;
  predicted_line.id =  std::stoi(object_id);
  predicted_line.type = visualization_msgs::Marker::POINTS;
  predicted_line.scale.x = 0.25;
  predicted_line.scale.y = 0.25;

  // Points are green
  predicted_line.color.b = 1.0f;
  predicted_line.color.a = 1.0;

  geometry_msgs::Point p;
  p.x = position.x;
  p.y = position.y;
  p.z = position.z;
  predicted_line.points.push_back(p);
}

// 新增：基于中心线的预测方法
void NaiveMotionPredict::makePredictionByCenterline(
    const smartcar_msgs::DetectedObject& object,
    std::vector<smartcar_msgs::DetectedObject>& predicted_objects_vec,
    visualization_msgs::Marker& predicted_line) {
    
    // 找到最近的中心线点
    CenterlineMatch match = findClosestCenterlinePoint(object.utm_x, object.utm_y);
    
    // 如果没有找到足够近的中心线，回退到基于模型的预测
    if (match.centerline_idx == -1 || match.distance > 5.0) {  // 5米阈值
        ROS_WARN_STREAM("对象 " << object.id << " 距离所有中心线太远，使用基于模型的预测");
        makePrediction(object, predicted_objects_vec, predicted_line);
        return;
    }
    
    ROS_INFO_STREAM("使用中心线 " << match.centerline_idx << " 进行预测，距离为 " << match.distance << "米");
    
    // 为了更容易访问，获取匹配的中心线引用
    const smartcar_msgs::My_Trajectory& centerline = centerlines_[match.centerline_idx];
    
    // 初始化当前位置
    smartcar_msgs::DetectedObject current_object = object;
    current_object.score = MAX_PREDICTION_SCORE_;
    
    // 将当前位置添加到预测向量
    predicted_objects_vec.push_back(current_object);
    
    // 设置可视化
    geometry_msgs::Point start_pose;
    start_pose.x = object.utm_x;
    start_pose.y = object.utm_y;
    start_pose.z = object.utm_z;
    initializeROSmarker(object.header, start_pose, object.id, predicted_line);
    
    // 根据车辆速度计算每个时间步的距离
    double distance_per_step = object.speed * interval_sec_;
    
    // 变量跟踪沿中心线的进度
    int current_point_idx = match.point_idx;
    double accumulated_distance = 0.0;
    
    // 生成未来位置
    for (int i = 0; i < num_prediction_; i++) {
        smartcar_msgs::DetectedObject predicted_object = current_object;
        
        // 沿中心线找位置
        double total_distance_to_travel = distance_per_step;
        
        while (total_distance_to_travel > 0 && current_point_idx < centerline.trajectory_points.size() - 1) {
            int next_point_idx = current_point_idx + 1;
            
            // 计算当前点和下一个点之间的距离
            double dx = centerline.trajectory_points[next_point_idx].x - 
                        centerline.trajectory_points[current_point_idx].x;
            double dy = centerline.trajectory_points[next_point_idx].y - 
                        centerline.trajectory_points[current_point_idx].y;
            double segment_distance = std::sqrt(dx*dx + dy*dy);
            
            if (total_distance_to_travel >= segment_distance) {
                // 移动到下一个点
                total_distance_to_travel -= segment_distance;
                current_point_idx = next_point_idx;
            } else {
                // 在点之间插值
                double ratio = total_distance_to_travel / segment_distance;
                predicted_object.utm_x = centerline.trajectory_points[current_point_idx].x + 
                                       ratio * dx;
                predicted_object.utm_y = centerline.trajectory_points[current_point_idx].y + 
                                       ratio * dy;
                
                // 插值航向角
                double heading_diff = centerline.trajectory_points[next_point_idx].theta - 
                                     centerline.trajectory_points[current_point_idx].theta;
                // 归一化航向角差异
                while (heading_diff > M_PI) heading_diff -= 2 * M_PI;
                while (heading_diff < -M_PI) heading_diff += 2 * M_PI;
                
                predicted_object.utm_heading = centerline.trajectory_points[current_point_idx].theta + 
                                            ratio * heading_diff;
                
                // 重置累积距离，为下一次迭代准备
                total_distance_to_travel = 0;
            }
        }
        
        // 如果到达中心线末端，停留在最后一个点
        if (current_point_idx >= centerline.trajectory_points.size() - 1) {
            predicted_object.utm_x = centerline.trajectory_points.back().x;
            predicted_object.utm_y = centerline.trajectory_points.back().y;
            predicted_object.utm_heading = centerline.trajectory_points.back().theta;
        }
        
        // 设置置信度分数并保持速度
        predicted_object.score = (-1.0/(interval_sec_*num_prediction_))*i*interval_sec_ + MAX_PREDICTION_SCORE_;
        predicted_object.speed = object.speed;
        
        // 添加到预测向量
        predicted_objects_vec.push_back(predicted_object);
        current_object = predicted_object;
        
        // 添加到可视化标记
        geometry_msgs::Point viz_point;
        viz_point.x = predicted_object.utm_x;
        viz_point.y = predicted_object.utm_y;
        viz_point.z = object.utm_z;
        predicted_line.points.push_back(viz_point);
    }
}

void NaiveMotionPredict::makePrediction(const smartcar_msgs::DetectedObject& object,
                                        std::vector<smartcar_msgs::DetectedObject>& predicted_objects_vec,
                                        visualization_msgs::Marker& predicted_line)
{
  smartcar_msgs::DetectedObject target_object = object;
  target_object.score = MAX_PREDICTION_SCORE_;
  geometry_msgs::Point tmp_pose;
  tmp_pose.x = object.utm_x;
  tmp_pose.y = object.utm_y;
  tmp_pose.z = object.utm_z;

  //先将起点，即t=0塞进预测轨迹
  predicted_objects_vec.push_back(target_object);

  initializeROSmarker(object.header, tmp_pose, object.id, predicted_line);
  for (int ith_prediction = 0; ith_prediction < num_prediction_; ith_prediction++)
  {
    smartcar_msgs::DetectedObject predicted_object = generatePredictedObject(target_object);
    predicted_object.score = (-1/(interval_sec_*num_prediction_))*ith_prediction*interval_sec_ + MAX_PREDICTION_SCORE_;
    predicted_objects_vec.push_back(predicted_object);
    target_object = predicted_object;

    geometry_msgs::Point p;
    p.x = predicted_object.utm_x;
    p.y = predicted_object.utm_y;
    p.z = object.z;
    predicted_line.points.push_back(p);
  }
}

void NaiveMotionPredict::makePredictionByRecord(const smartcar_msgs::DetectedObject& object,
                                        std::vector<smartcar_msgs::DetectedObject>& predicted_objects_vec,
                                        visualization_msgs::Marker& predicted_line)
{
  ROS_INFO_STREAM("object_id: " << object.id);
  ROS_INFO("object_ x: %f   y: %f", object.utm_x, object.utm_y);
  //1.在读取的轨迹文件中，找出该object的轨迹
  int target_index;
  for (int i=0; i < g_lanes.lanes.size(); i++) {
    if (g_lanes.lanes[i].lane_id == std::stoi(object.id)) {
      target_index = i;
      break;
    }
  }

  ROS_INFO("target_lane_id: %d", g_lanes.lanes[target_index].lane_id);

  //2.找出轨迹中距离目前object最近的点
  int target_point_id;
  double distance = 100000;
  for (int i =0; i < g_lanes.lanes[target_index].trajectory_points.size(); i++) {
    double dx = object.utm_x - g_lanes.lanes[target_index].trajectory_points[i].x;
    double dy = object.utm_y - g_lanes.lanes[target_index].trajectory_points[i].y;
    double ds = std::sqrt(dx * dx + dy * dy);

    if (distance < 0.1 && ds > distance) {
      //找到了最近点
      break;
    }

    if (ds < distance) {
      target_point_id = i;
      distance = ds;
    }
  }

  //考虑障碍物已经远离录制的轨迹，改用算法预测
  if (distance < 1) {
    ROS_INFO("target_point_id: %d", target_point_id);
    ROS_INFO("target_point x: %f   y: %f", g_lanes.lanes[target_index].trajectory_points[target_point_id].x,
                                          g_lanes.lanes[target_index].trajectory_points[target_point_id].y);
    
    smartcar_msgs::DetectedObject target_object = object;
    target_object.score = MAX_PREDICTION_SCORE_;
    
    geometry_msgs::Point tmp_pose;
    tmp_pose.x = object.utm_x;
    tmp_pose.y = object.utm_y;
    tmp_pose.z = object.utm_z;

    //先将起点，即t=0塞进预测轨迹
    predicted_objects_vec.push_back(target_object);

    initializeROSmarker(object.header, tmp_pose, object.id, predicted_line);

    for (int ith_prediction = 1; ith_prediction <= num_prediction_; ith_prediction++) {
      smartcar_msgs::DetectedObject predicted_object;// = generatePredictedObject(target_object);
      if (target_point_id + ith_prediction >= g_lanes.lanes[target_index].trajectory_points.size()) {
        //如果object快远离了录制的轨迹，不足80个时间点，剩余的用算法预测
        predicted_object = generatePredictedObject(target_object);
      } else {
        predicted_object.score = (-1/(interval_sec_*num_prediction_))*ith_prediction*interval_sec_ + MAX_PREDICTION_SCORE_;
        predicted_object.utm_x = g_lanes.lanes[target_index].trajectory_points[target_point_id + ith_prediction].x;
        predicted_object.utm_y = g_lanes.lanes[target_index].trajectory_points[target_point_id + ith_prediction].y;
        predicted_object.speed = g_lanes.lanes[target_index].trajectory_points[target_point_id + ith_prediction].v;
      }

      predicted_objects_vec.push_back(predicted_object);
      target_object = predicted_object;

      geometry_msgs::Point p;
      p.x = predicted_object.utm_x;
      p.y = predicted_object.utm_y;
      p.z = object.z;
      predicted_line.points.push_back(p);
    }
  } else {
      smartcar_msgs::DetectedObject target_object = object;
      target_object.score = MAX_PREDICTION_SCORE_;
      geometry_msgs::Point tmp_pose;
      tmp_pose.x = object.utm_x;
      tmp_pose.y = object.utm_y;
      tmp_pose.z = object.utm_z;

      //先将起点，即t=0塞进预测轨迹
      predicted_objects_vec.push_back(target_object);

      initializeROSmarker(object.header, tmp_pose, object.id, predicted_line);
      for (int ith_prediction = 0; ith_prediction < num_prediction_; ith_prediction++) {
        smartcar_msgs::DetectedObject predicted_object = generatePredictedObject(target_object);
        predicted_object.score = (-1/(interval_sec_*num_prediction_))*ith_prediction*interval_sec_ + MAX_PREDICTION_SCORE_;
        predicted_objects_vec.push_back(predicted_object);
        target_object = predicted_object;

        geometry_msgs::Point p;
        p.x = predicted_object.utm_x;
        p.y = predicted_object.utm_y;
        p.z = object.z;
        predicted_line.points.push_back(p);
      }    
  }
}

smartcar_msgs::DetectedObject NaiveMotionPredict::generatePredictedObject(const smartcar_msgs::DetectedObject& object)
{
  smartcar_msgs::DetectedObject predicted_object;
  if (object.behavior_state == MotionModel::CV)
  {
    predicted_object = moveConstantVelocity(object);
  }
  else if (object.behavior_state == MotionModel::CTRV)
  {
    predicted_object = moveConstantTurnRateVelocity(object);
  }
  else
  {
    // This is because random motion's velocity is 0
    predicted_object = object;
  }

  return predicted_object;
}

smartcar_msgs::DetectedObject NaiveMotionPredict::moveConstantVelocity(const smartcar_msgs::DetectedObject& object)
{
  smartcar_msgs::DetectedObject predicted_object;
  predicted_object = object;
  double px = object.utm_x;
  double py = object.utm_y;
  double velocity = object.speed;
  // double yaw = object.utm_heading;
  double yaw = 0.0;

  // predicted state values
  double prediction_px = px + velocity * cos(yaw) * interval_sec_;
  double prediction_py = py + velocity * sin(yaw) * interval_sec_;

  predicted_object.utm_x = prediction_px;
  predicted_object.utm_y = prediction_py;
  predicted_object.speed = velocity;

  return predicted_object;
}

smartcar_msgs::DetectedObject
NaiveMotionPredict::moveConstantTurnRateVelocity(const smartcar_msgs::DetectedObject& object)
{
  smartcar_msgs::DetectedObject predicted_object;
  predicted_object = object;
  double px = object.utm_x;
  double py = object.utm_y;
  double velocity = object.speed;
  // double yaw = object.utm_heading;
  double yaw = 0.0;

  double yawd = 0;//object.acceleration.linear.y;

  // predicted state values
  double prediction_px, prediction_py;

  // avoid division by zero
  if (fabs(yawd) > 0.001)
  {
    prediction_px = px + velocity / yawd * (sin(yaw + yawd * interval_sec_) - sin(yaw));
    prediction_py = py + velocity / yawd * (cos(yaw) - cos(yaw + yawd * interval_sec_));
  }
  else
  {
    prediction_px = px + velocity * interval_sec_ * cos(yaw);
    prediction_py = py + velocity * interval_sec_ * sin(yaw);
  }
  double prediction_yaw = yaw + yawd * interval_sec_;

  while (prediction_yaw > M_PI)
    prediction_yaw -= 2. * M_PI;
  while (prediction_yaw < -M_PI)
    prediction_yaw += 2. * M_PI;

  predicted_object.utm_x = prediction_px;
  predicted_object.utm_y = prediction_py;
  predicted_object.utm_heading = prediction_yaw;
  
  return predicted_object;
}

double NaiveMotionPredict::generateYawFromQuaternion(const geometry_msgs::Quaternion& quaternion)
{
  tf::Quaternion q(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
  tf::Matrix3x3 m(q);
  double roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw);
  return yaw;
}

void NaiveMotionPredict::objectsCallback(const smartcar_msgs::DetectedObjectArray& input)
{
  ROS_INFO("..............................");
  smartcar_msgs::DetectedObjectArray output;
  visualization_msgs::MarkerArray predicted_lines;
  
  int iddd = 1;
  for (const auto &object : input.objects)
  {
    std::vector<smartcar_msgs::DetectedObject> predicted_objects_vec;
    visualization_msgs::Marker predicted_line;
    
    if (object.speed < 0.1) {
      //静止障碍物，不预测轨迹
      output.objects.push_back(object);
      continue;
    }
    
    // 选择预测方法：中心线、录制轨迹或基于模型
    if (predictionByCenterline_) {
      ROS_INFO("使用基于中心线的预测");
      makePredictionByCenterline(object, predicted_objects_vec, predicted_line);
    } else if (predictionByrecorded_trajectories_) {
      ROS_INFO("使用基于录制轨迹的预测");

      //1.在读取的轨迹文件中，找出该object的轨迹
      int target_index = -1;
      for (int i=0; i < g_lanes.lanes.size(); i++) {
        if (g_lanes.lanes[i].lane_id == std::stoi(object.id)) {
          target_index = i;
          break;
        }
      }
      
      if (target_index == -1) {
        ROS_WARN_STREAM("object " << object.id << " is not find record path");
        makePrediction(object, predicted_objects_vec, predicted_line);
      } else {
        makePredictionByRecord(object, predicted_objects_vec, predicted_line);
      }
    } else {
      ROS_INFO("使用基于模型的预测");
      makePrediction(object, predicted_objects_vec, predicted_line);
    }

    //构造包含预测轨迹的障碍物
    smartcar_msgs::DetectedObject tmp_object;
    tmp_object = object;
    smartcar_msgs::My_Trajectory_Point predicted_point;
    for (const auto &predicted_object : predicted_objects_vec) {
      predicted_point.x = predicted_object.utm_x;
      predicted_point.y = predicted_object.utm_y;
      predicted_point.v = predicted_object.speed;
      tmp_object.trajectory_.trajectory_points.push_back(predicted_point);
    }

    // visualize only stably tracked objects
    if (!object.pose_reliable)
    {
      continue;
    }
    
    output.objects.push_back(tmp_object);
    predicted_line.id =  iddd * 100;
    iddd++;
    predicted_lines.markers.push_back(predicted_line);
  }
  
  output.num = output.objects.size();
  output.header = input.header;
  predicted_objects_pub_.publish(output);
  printf("The object Traj %ld %ld \n", output.objects.size(), input.objects.size());
  predicted_paths_pub_.publish(predicted_lines);
}

bool NaiveMotionPredict::isObjectValid(const smartcar_msgs::DetectedObject &in_object)
{
  //在车辆坐标系下，计算障碍物距离自车后轴中心的距离
  double distance = std::sqrt(std::pow(in_object.x,2)+
                              std::pow(in_object.y,2));
  if (!in_object.valid ||
      std::isnan(in_object.heading) ||
      (distance <=  filter_out_close_object_threshold_)||
      (in_object.length <= 0) ||
      (in_object.width <= 0) ||
      (in_object.height <= 0)
    )
  {
    return false;
  }
  return true;
}//end IsObjectValid


