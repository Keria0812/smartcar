/*
 * Copyright 2018-2019 Autoware Foundation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <naive_motion_predict/naive_motion_predict.h>

NaiveMotionPredict::NaiveMotionPredict() :
  nh_(),
  private_nh_("~"),
  MAX_PREDICTION_SCORE_(1.0)
{
  private_nh_.param<double>("interval_sec", interval_sec_, 0.1);
  private_nh_.param<int>("num_prediction", num_prediction_, 80);
  private_nh_.param<double>("sensor_height_", sensor_height_, 0);
  private_nh_.param<double>("filter_out_close_object_threshold", filter_out_close_object_threshold_, 1.5);
  private_nh_.param<bool>("predictionByrecorded_trajectories", predictionByrecorded_trajectories_, false);
  private_nh_.param<std::string>("waypoints_file", waypoints_file_, "/home/erro");

  ROS_INFO_STREAM("predictionByrecorded_trajectories: " << predictionByrecorded_trajectories_);

  predicted_objects_pub_ = nh_.advertise<smartcar_msgs::DetectedObjectArray>("/prediction/motion_predictor/objects", 1);
  predicted_paths_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("/prediction/motion_predictor/path_markers", 10);
  detected_objects_sub_ = nh_.subscribe("/ITS/DetectObjects", 1, &NaiveMotionPredict::objectsCallback, this);

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

    //4.打印测试，不要录制太长的轨迹，不然屏幕看不清
    // for(int i=0; i < g_lanes.lanes.size(); i++) {
    //   ROS_INFO_STREAM("car id: " << g_lanes.lanes[i].lane_id);
    //   for (int j=0; j < g_lanes.lanes[i].trajectory_points.size(); j++) {
    //     std::cout << std::fixed << std::setprecision(3) 
    //               << g_lanes.lanes[i].trajectory_points[j].relative_time << ","
    //               << g_lanes.lanes[i].trajectory_points[j].x << ","
    //               << g_lanes.lanes[i].trajectory_points[j].y << ","
    //               << g_lanes.lanes[i].trajectory_points[j].z << ","
    //               << g_lanes.lanes[i].trajectory_points[j].theta << ","
    //               << g_lanes.lanes[i].trajectory_points[j].v << "\n";
    //   }
    // }

  }
}

NaiveMotionPredict::~NaiveMotionPredict()
{
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

/*
This package is a template package for more sopisticated prediction packages.
Feel free to change/modify generatePredictedObject function
and send pull request to Autoware
 */

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
  // tf::Quaternion q = tf::createQuaternionFromRPY(0, 0, prediction_yaw);
  // predicted_object.pose.orientation.x = q[0];
  // predicted_object.pose.orientation.y = q[1];
  // predicted_object.pose.orientation.z = q[2];
  // predicted_object.pose.orientation.w = q[3];
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
  // output = input;
  int iddd = 1;
  for (const auto &object : input.objects)
  {
    std::vector<smartcar_msgs::DetectedObject> predicted_objects_vec;
    visualization_msgs::Marker predicted_line;
    // if (isObjectValid(object))
    {
      if (object.speed < 0.1) {
        //静止障碍物，不预测轨迹
        output.objects.push_back(object);
        continue;
      }
      
      if (predictionByrecorded_trajectories_) {
        ROS_INFO("predictionByrecorded_trajectories_");

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
        makePrediction(object, predicted_objects_vec, predicted_line);
      }

      // concate to output object array
      // output.objects.insert(output.objects.end(), predicted_objects_vec.begin(), predicted_objects_vec.end());

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
      // std::cout << iddd <<" " << tmp_object << std::endl;
      output.objects.push_back(tmp_object);
      predicted_line.id =  iddd * 100;
      iddd++;
      predicted_lines.markers.push_back(predicted_line);
    }
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
      // std::isnan(in_object.pose.orientation.x) ||
      // std::isnan(in_object.pose.orientation.y) ||
      // std::isnan(in_object.pose.orientation.z) ||
      // std::isnan(in_object.pose.orientation.w) ||
      // std::isnan(in_object.pose.position.x) ||
      // std::isnan(in_object.pose.position.y) ||
      // std::isnan(in_object.pose.position.z) ||
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
