/*
 * @Copyright: jinxiaoxin@whut.edu.cn
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
   map_handle_(3.75)  // Initialize map handler with default lane width 3.75m
 {
   private_nh_.param<double>("interval_sec", interval_sec_, 0.1);
   private_nh_.param<int>("num_prediction", num_prediction_, 80);
   private_nh_.param<double>("sensor_height_", sensor_height_, 0);
   private_nh_.param<double>("filter_out_close_object_threshold", filter_out_close_object_threshold_, 1.5);
   private_nh_.param<bool>("predictionByrecorded_trajectories", predictionByrecorded_trajectories_, false);
   private_nh_.param<std::string>("waypoints_file", waypoints_file_, "/home/erro");
   
   // Add centerline prediction parameters
   private_nh_.param<bool>("predictionByCenterline", predictionByCenterline_, false);
   
   // Add multi-modal prediction parameters
   private_nh_.param<bool>("predictionMultiModal", predictionMultiModal_, false);
   private_nh_.param<double>("lane_change_probability", lane_change_probability_, 0.3);
   private_nh_.param<double>("lane_follow_probability", lane_follow_probability_, 0.7);
 
   ROS_INFO_STREAM("predictionByrecorded_trajectories: " << predictionByrecorded_trajectories_);
   ROS_INFO_STREAM("predictionByCenterline: " << predictionByCenterline_);
   ROS_INFO_STREAM("predictionMultiModal: " << predictionMultiModal_);
 
   predicted_objects_pub_ = nh_.advertise<smartcar_msgs::DetectedObjectArray>("/prediction/motion_predictor/objects", 1);
   predicted_paths_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("/prediction/motion_predictor/path_markers", 10);
   detected_objects_sub_ = nh_.subscribe("/ITS/DetectObjects", 1, &NaiveMotionPredict::objectsCallback, this);
 
   // Load centerline files if centerline prediction is enabled
   if (predictionByCenterline_ || predictionMultiModal_) {
     std::vector<std::string> centerline_files;
     private_nh_.param<std::vector<std::string>>("centerline_files", centerline_files, std::vector<std::string>());
     
     if (centerline_files.empty()) {
       ROS_WARN("Centerline-based prediction is enabled but no centerline files specified.");
     } else {
       loadCenterlineFiles(centerline_files);
     }
   }
   
   // Initialize recorded trajectory prediction
   if (predictionByrecorded_trajectories_) {
     double road_width = 3.75;
     MapHandle map_handle(road_width);
     
     // Get all trajectory files
     std::vector<std::string> files;
     get_all_files(waypoints_file_, files);
     for (auto &file : files) {
         std::cout << "file path: " << file << std::endl;
     }
 
     // Extract valid trajectory files
     std::vector<std::string> vaild_files;
     vaild_files = remove_erro_files(files, ".csv");
     for (auto &file : vaild_files) {
         std::cout << "vaild_files path: " << file << std::endl;
     }
 
     // Read trajectories and get object ID from filename
     for (long unsigned int i=0; i < vaild_files.size(); i++) {
         read_csv(vaild_files[i], gWaypoints);
         map_handle.TimeResample(gWaypoints, gWaypoints_fix_time);
         gWaypoints_fix_time.lane_id = map_handle.get_lane_id(vaild_files[i]);
         if (gWaypoints_fix_time.lane_id == -1) {
           ROS_WARN("No find car id");
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
 
 // Load centerline files
 void NaiveMotionPredict::loadCenterlineFiles(const std::vector<std::string>& centerline_files) {
     centerlines_.clear();
     
     for (int i = 0; i < centerline_files.size(); i++) {
         smartcar_msgs::My_Trajectory centerline;
         centerline.lane_id = i;  // Assign ID to each centerline
         
         // Read centerline file
         std::ifstream file(centerline_files[i]);
         if (!file.is_open()) {
             ROS_ERROR_STREAM("Failed to open centerline file: " << centerline_files[i]);
             continue;
         }
         
         std::string line;
         double relative_time = 0.0;
         
         while (std::getline(file, line)) {
             std::istringstream iss(line);
             double x, y, heading;
             
             if (!(iss >> x >> y >> heading)) {
                 continue;  // Skip invalid lines
             }
             
             smartcar_msgs::My_Trajectory_Point point;
             point.x = x;
             point.y = y;
             point.theta = heading;
             point.relative_time = relative_time;
             relative_time += 0.1;  // Arbitrary time increment
             
             centerline.trajectory_points.push_back(point);
         }
         
         centerline.num = centerline.trajectory_points.size();
         
         if (centerline.num > 0) {
             centerlines_.push_back(centerline);
             ROS_INFO_STREAM("Loaded centerline " << i << " with " << centerline.num << " points");
         }
     }
     
     ROS_INFO_STREAM("Loaded a total of " << centerlines_.size() << " centerlines");
 }
 
 // Find closest centerline point
 CenterlineMatch NaiveMotionPredict::findClosestCenterlinePoint(double x, double y) {
     CenterlineMatch match;
     match.centerline_idx = -1;
     match.point_idx = -1;
     match.distance = std::numeric_limits<double>::max();
     
     for (int i = 0; i < centerlines_.size(); i++) {
         // Only compare if centerline has enough points
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
 
 // Find adjacent centerlines for multi-modal prediction
 std::vector<CenterlineMatch> NaiveMotionPredict::findAdjacentCenterlines(const smartcar_msgs::DetectedObject& object,
                                                             const CenterlineMatch& current_match) {
     std::vector<CenterlineMatch> adjacent_centerlines;
     
     if (current_match.centerline_idx == -1) {
         return adjacent_centerlines;  // No valid current centerline
     }
     
     // Get current centerline
     const smartcar_msgs::My_Trajectory& current_centerline = centerlines_[current_match.centerline_idx];
     
     // Current position
     double current_x = object.utm_x;
     double current_y = object.utm_y;
     
     // Current heading direction
     double current_heading = current_centerline.trajectory_points[current_match.point_idx].theta;
     
     // Calculate perpendicular direction (left and right of the centerline)
     double perp_x_left = cos(current_heading + M_PI/2);
     double perp_y_left = sin(current_heading + M_PI/2);
     double perp_x_right = cos(current_heading - M_PI/2);
     double perp_y_right = sin(current_heading - M_PI/2);
     
     // Standard lane width (can be a parameter)
     double lane_width = 3.75;  
     
     // Search points at one lane width distance in perpendicular directions
     double left_search_x = current_x + perp_x_left * lane_width;
     double left_search_y = current_y + perp_y_left * lane_width;
     double right_search_x = current_x + perp_x_right * lane_width;
     double right_search_y = current_y + perp_y_right * lane_width;
     
     // Find closest centerlines to these points
     CenterlineMatch left_match = findClosestCenterlinePoint(left_search_x, left_search_y);
     CenterlineMatch right_match = findClosestCenterlinePoint(right_search_x, right_search_y);
     
     // Add valid matches (if they are different from current centerline)
     if (left_match.centerline_idx != -1 && 
         left_match.centerline_idx != current_match.centerline_idx && 
         left_match.distance < lane_width * 1.5) {
         adjacent_centerlines.push_back(left_match);
     }
     
     if (right_match.centerline_idx != -1 && 
         right_match.centerline_idx != current_match.centerline_idx && 
         right_match.distance < lane_width * 1.5) {
         adjacent_centerlines.push_back(right_match);
     }
     
     return adjacent_centerlines;
 }
 
 void NaiveMotionPredict::initializeROSmarker(const std_msgs::Header& header, const geometry_msgs::Point& position,
                                              const std::string object_id, visualization_msgs::Marker& predicted_line,
                                              const std::string& mode_type)
 {
   predicted_line.lifetime = ros::Duration(0.2);
   predicted_line.header.frame_id = "map";  // header.frame_id;
   predicted_line.header.stamp = header.stamp;
   predicted_line.ns = "predicted_line_" + mode_type;
   predicted_line.action = visualization_msgs::Marker::ADD;
   predicted_line.pose.orientation.w = 1.0;
   predicted_line.id = std::stoi(object_id);
   predicted_line.type = visualization_msgs::Marker::POINTS;
   predicted_line.scale.x = 0.25;
   predicted_line.scale.y = 0.25;
 
   // Color based on trajectory mode
   if (mode_type == "lane_follow") {
     // Blue for lane following
     predicted_line.color.r = 0.0f;
     predicted_line.color.g = 0.0f;
     predicted_line.color.b = 1.0f;
     predicted_line.color.a = 1.0;
   } else if (mode_type == "lane_change_left") {
     // Green for left lane change
     predicted_line.color.r = 0.0f;
     predicted_line.color.g = 1.0f;
     predicted_line.color.b = 0.0f;
     predicted_line.color.a = 1.0;
   } else if (mode_type == "lane_change_right") {
     // Red for right lane change
     predicted_line.color.r = 1.0f;
     predicted_line.color.g = 0.0f;
     predicted_line.color.b = 0.0f;
     predicted_line.color.a = 1.0;
   } else {
     // Default: purple for other modes
     predicted_line.color.r = 0.8f;
     predicted_line.color.g = 0.0f;
     predicted_line.color.b = 0.8f;
     predicted_line.color.a = 1.0;
   }
 
   geometry_msgs::Point p;
   p.x = position.x;
   p.y = position.y;
   p.z = position.z;
   predicted_line.points.push_back(p);
 }
 
 // Centerline-based prediction method
 void NaiveMotionPredict::makePredictionByCenterline(
     const smartcar_msgs::DetectedObject& object,
     std::vector<smartcar_msgs::DetectedObject>& predicted_objects_vec,
     visualization_msgs::Marker& predicted_line) {
     
     // Find closest centerline point
     CenterlineMatch match = findClosestCenterlinePoint(object.utm_x, object.utm_y);
     
     // Fall back to model-based prediction if no close centerline found
     if (match.centerline_idx == -1 || match.distance > 5.0) {  // 5m threshold
         ROS_WARN_STREAM("Object " << object.id << " is too far from all centerlines, using model-based prediction");
         makePrediction(object, predicted_objects_vec, predicted_line);
         return;
     }
     
     ROS_INFO_STREAM("Using centerline " << match.centerline_idx << " for prediction, distance is " << match.distance << "m");
     
     // Get reference to matched centerline for easier access
     const smartcar_msgs::My_Trajectory& centerline = centerlines_[match.centerline_idx];
     
     // Initialize current position
     smartcar_msgs::DetectedObject current_object = object;
     current_object.score = MAX_PREDICTION_SCORE_;
     
     // Add current position to prediction vector
     predicted_objects_vec.push_back(current_object);
     
     // Set up visualization
     geometry_msgs::Point start_pose;
     start_pose.x = object.utm_x;
     start_pose.y = object.utm_y;
     start_pose.z = object.utm_z;
     initializeROSmarker(object.header, start_pose, object.id, predicted_line, "lane_follow");
     
     // Calculate distance per time step based on vehicle speed
     double distance_per_step = object.speed * interval_sec_;
     
     // Variables to track progress along centerline
     int current_point_idx = match.point_idx;
     double accumulated_distance = 0.0;
     
     // Generate future positions
     for (int i = 0; i < num_prediction_; i++) {
         smartcar_msgs::DetectedObject predicted_object = current_object;
         
         // Find position along centerline
         double total_distance_to_travel = distance_per_step;
         
         while (total_distance_to_travel > 0 && current_point_idx < centerline.trajectory_points.size() - 1) {
             int next_point_idx = current_point_idx + 1;
             
             // Calculate distance between current and next point
             double dx = centerline.trajectory_points[next_point_idx].x - 
                         centerline.trajectory_points[current_point_idx].x;
             double dy = centerline.trajectory_points[next_point_idx].y - 
                         centerline.trajectory_points[current_point_idx].y;
             double segment_distance = std::sqrt(dx*dx + dy*dy);
             
             if (total_distance_to_travel >= segment_distance) {
                 // Move to next point
                 total_distance_to_travel -= segment_distance;
                 current_point_idx = next_point_idx;
             } else {
                 // Interpolate between points
                 double ratio = total_distance_to_travel / segment_distance;
                 predicted_object.utm_x = centerline.trajectory_points[current_point_idx].x + 
                                        ratio * dx;
                 predicted_object.utm_y = centerline.trajectory_points[current_point_idx].y + 
                                        ratio * dy;
                 
                 // Interpolate heading
                 double heading_diff = centerline.trajectory_points[next_point_idx].theta - 
                                      centerline.trajectory_points[current_point_idx].theta;
                 // Normalize heading difference
                 while (heading_diff > M_PI) heading_diff -= 2 * M_PI;
                 while (heading_diff < -M_PI) heading_diff += 2 * M_PI;
                 
                 predicted_object.utm_heading = centerline.trajectory_points[current_point_idx].theta + 
                                             ratio * heading_diff;
                 
                 // Reset accumulated distance for next iteration
                 total_distance_to_travel = 0;
             }
         }
         
         // If reached end of centerline, stay at last point
         if (current_point_idx >= centerline.trajectory_points.size() - 1) {
             predicted_object.utm_x = centerline.trajectory_points.back().x;
             predicted_object.utm_y = centerline.trajectory_points.back().y;
             predicted_object.utm_heading = centerline.trajectory_points.back().theta;
         }
         
         // Set confidence score and maintain speed
         predicted_object.score = (-1.0/(interval_sec_*num_prediction_))*i*interval_sec_ + MAX_PREDICTION_SCORE_;
         predicted_object.speed = object.speed;
         
         // Add to prediction vector
         predicted_objects_vec.push_back(predicted_object);
         current_object = predicted_object;
         
         // Add to visualization marker
         geometry_msgs::Point viz_point;
         viz_point.x = predicted_object.utm_x;
         viz_point.y = predicted_object.utm_y;
         viz_point.z = object.utm_z;
         predicted_line.points.push_back(viz_point);
     }
 }
 
 // Generate lane following trajectory for multi-modal prediction
 void NaiveMotionPredict::generateLaneFollowTrajectory(
     const smartcar_msgs::DetectedObject& object,
     const CenterlineMatch& match,
     TrajectoryMode& trajectory_mode,
     visualization_msgs::Marker& predicted_line) {
     
     // Get reference to matched centerline for easier access
     const smartcar_msgs::My_Trajectory& centerline = centerlines_[match.centerline_idx];
     
     // Initialize trajectory properties
     trajectory_mode.mode_type = "lane_follow";
     trajectory_mode.probability = lane_follow_probability_;
     trajectory_mode.trajectory_points.clear();
     
     // Initialize current position
     smartcar_msgs::DetectedObject current_object = object;
     current_object.score = MAX_PREDICTION_SCORE_;
     
     // Add current position to trajectory
     trajectory_mode.trajectory_points.push_back(current_object);
     
     // Set up visualization
     geometry_msgs::Point start_pose;
     start_pose.x = object.utm_x;
     start_pose.y = object.utm_y;
     start_pose.z = object.utm_z;
     initializeROSmarker(object.header, start_pose, object.id, predicted_line, "lane_follow");
     
     // Calculate distance per time step based on vehicle speed
     double distance_per_step = object.speed * interval_sec_;
     
     // Variables to track progress along centerline
     int current_point_idx = match.point_idx;
     
     // Generate future positions
     for (int i = 0; i < num_prediction_; i++) {
         smartcar_msgs::DetectedObject predicted_object = current_object;
         
         // Find position along centerline
         double total_distance_to_travel = distance_per_step;
         
         while (total_distance_to_travel > 0 && current_point_idx < centerline.trajectory_points.size() - 1) {
             int next_point_idx = current_point_idx + 1;
             
             // Calculate distance between current and next point
             double dx = centerline.trajectory_points[next_point_idx].x - 
                         centerline.trajectory_points[current_point_idx].x;
             double dy = centerline.trajectory_points[next_point_idx].y - 
                         centerline.trajectory_points[current_point_idx].y;
             double segment_distance = std::sqrt(dx*dx + dy*dy);
             
             if (total_distance_to_travel >= segment_distance) {
                 // Move to next point
                 total_distance_to_travel -= segment_distance;
                 current_point_idx = next_point_idx;
             } else {
                 // Interpolate between points
                 double ratio = total_distance_to_travel / segment_distance;
                 predicted_object.utm_x = centerline.trajectory_points[current_point_idx].x + 
                                        ratio * dx;
                 predicted_object.utm_y = centerline.trajectory_points[current_point_idx].y + 
                                        ratio * dy;
                 
                 // Interpolate heading
                 double heading_diff = centerline.trajectory_points[next_point_idx].theta - 
                                      centerline.trajectory_points[current_point_idx].theta;
                 // Normalize heading difference
                 while (heading_diff > M_PI) heading_diff -= 2 * M_PI;
                 while (heading_diff < -M_PI) heading_diff += 2 * M_PI;
                 
                 predicted_object.utm_heading = centerline.trajectory_points[current_point_idx].theta + 
                                             ratio * heading_diff;
                 
                 // Reset accumulated distance for next iteration
                 total_distance_to_travel = 0;
             }
         }
         
         // If reached end of centerline, stay at last point
         if (current_point_idx >= centerline.trajectory_points.size() - 1) {
             predicted_object.utm_x = centerline.trajectory_points.back().x;
             predicted_object.utm_y = centerline.trajectory_points.back().y;
             predicted_object.utm_heading = centerline.trajectory_points.back().theta;
         }
         
         // Set confidence score and maintain speed
         predicted_object.score = (-1.0/(interval_sec_*num_prediction_))*i*interval_sec_ + MAX_PREDICTION_SCORE_;
         predicted_object.speed = object.speed;
         
         // Add to trajectory mode vector
         trajectory_mode.trajectory_points.push_back(predicted_object);
         current_object = predicted_object;
         
         // Add to visualization marker
         geometry_msgs::Point viz_point;
         viz_point.x = predicted_object.utm_x;
         viz_point.y = predicted_object.utm_y;
         viz_point.z = object.utm_z;
         predicted_line.points.push_back(viz_point);
     }
 }
 
 // Generate lane change trajectory for multi-modal prediction
 void NaiveMotionPredict::generateLaneChangeTrajectory(
     const smartcar_msgs::DetectedObject& object,
     const CenterlineMatch& source_match,
     const CenterlineMatch& target_match,
     const std::string& direction,
     TrajectoryMode& trajectory_mode,
     visualization_msgs::Marker& predicted_line) {
     
     // Set trajectory properties
     trajectory_mode.mode_type = "lane_change_" + direction;
     trajectory_mode.probability = lane_change_probability_;
     trajectory_mode.trajectory_points.clear();
     
     // Parameters for lane change
     double lane_change_duration = 3.0;  // Seconds to complete lane change
     int lane_change_steps = static_cast<int>(lane_change_duration / interval_sec_);
     
     // Source and target centerlines
     const smartcar_msgs::My_Trajectory& source_centerline = centerlines_[source_match.centerline_idx];
     const smartcar_msgs::My_Trajectory& target_centerline = centerlines_[target_match.centerline_idx];
     
     // Initialize current position
     smartcar_msgs::DetectedObject current_object = object;
     current_object.score = MAX_PREDICTION_SCORE_;
     
     // Add current position to trajectory
     trajectory_mode.trajectory_points.push_back(current_object);
     
     // Set up visualization
     geometry_msgs::Point start_pose;
     start_pose.x = object.utm_x;
     start_pose.y = object.utm_y;
     start_pose.z = object.utm_z;
     initializeROSmarker(object.header, start_pose, object.id, predicted_line, trajectory_mode.mode_type);
     
     // Calculate distance per time step based on vehicle speed
     double distance_per_step = object.speed * interval_sec_;
     
     // Variables to track progress along centerlines
     int source_point_idx = source_match.point_idx;
     int target_point_idx = target_match.point_idx;
     
     // Generate future positions
     for (int i = 0; i < num_prediction_; i++) {
         smartcar_msgs::DetectedObject predicted_object = current_object;
         
         // Determine blend factor for lane change (ranges from 0 to 1)
         double blend_factor = 0.0;
         if (i < lane_change_steps) {
             // Smooth transition using sigmoid function
             blend_factor = 1.0 / (1.0 + exp(-12.0 * (static_cast<double>(i) / lane_change_steps - 0.5)));
         } else {
             blend_factor = 1.0;  // Fully on target lane
         }
         
         // Progress along source centerline
         double source_total_distance = distance_per_step;
         int next_source_point_idx = source_point_idx;
         double source_x = 0.0, source_y = 0.0, source_heading = 0.0;
         
         if (source_point_idx < source_centerline.trajectory_points.size() - 1) {
             // Navigate along source centerline
             while (source_total_distance > 0 && next_source_point_idx < source_centerline.trajectory_points.size() - 1) {
                 int next_idx = next_source_point_idx + 1;
                 
                 double dx = source_centerline.trajectory_points[next_idx].x - 
                             source_centerline.trajectory_points[next_source_point_idx].x;
                 double dy = source_centerline.trajectory_points[next_idx].y - 
                             source_centerline.trajectory_points[next_source_point_idx].y;
                 double segment_distance = std::sqrt(dx*dx + dy*dy);
                 
                 if (source_total_distance >= segment_distance) {
                     source_total_distance -= segment_distance;
                     next_source_point_idx = next_idx;
                 } else {
                     double ratio = source_total_distance / segment_distance;
                     source_x = source_centerline.trajectory_points[next_source_point_idx].x + ratio * dx;
                     source_y = source_centerline.trajectory_points[next_source_point_idx].y + ratio * dy;
                     
                     double heading_diff = source_centerline.trajectory_points[next_idx].theta - 
                                          source_centerline.trajectory_points[next_source_point_idx].theta;
                     // Normalize heading difference
                     while (heading_diff > M_PI) heading_diff -= 2 * M_PI;
                     while (heading_diff < -M_PI) heading_diff += 2 * M_PI;
                     
                     source_heading = source_centerline.trajectory_points[next_source_point_idx].theta + ratio * heading_diff;
                     source_total_distance = 0;
                 }
             }
             
             // If reached end of centerline
             if (next_source_point_idx >= source_centerline.trajectory_points.size() - 1) {
                 source_x = source_centerline.trajectory_points.back().x;
                 source_y = source_centerline.trajectory_points.back().y;
                 source_heading = source_centerline.trajectory_points.back().theta;
             }
         } else {
             // Already at end of source centerline
             source_x = source_centerline.trajectory_points.back().x;
             source_y = source_centerline.trajectory_points.back().y;
             source_heading = source_centerline.trajectory_points.back().theta;
         }
         
         // Progress along target centerline
         double target_total_distance = distance_per_step;
         int next_target_point_idx = target_point_idx;
         double target_x = 0.0, target_y = 0.0, target_heading = 0.0;
         
         if (target_point_idx < target_centerline.trajectory_points.size() - 1) {
             // Navigate along target centerline
             while (target_total_distance > 0 && next_target_point_idx < target_centerline.trajectory_points.size() - 1) {
                 int next_idx = next_target_point_idx + 1;
                 
                 double dx = target_centerline.trajectory_points[next_idx].x - 
                             target_centerline.trajectory_points[next_target_point_idx].x;
                 double dy = target_centerline.trajectory_points[next_idx].y - 
                             target_centerline.trajectory_points[next_target_point_idx].y;
                 double segment_distance = std::sqrt(dx*dx + dy*dy);
                 
                 if (target_total_distance >= segment_distance) {
                     target_total_distance -= segment_distance;
                     next_target_point_idx = next_idx;
                 } else {
                     double ratio = target_total_distance / segment_distance;
                     target_x = target_centerline.trajectory_points[next_target_point_idx].x + ratio * dx;
                     target_y = target_centerline.trajectory_points[next_target_point_idx].y + ratio * dy;
                     
                     double heading_diff = target_centerline.trajectory_points[next_idx].theta - 
                                          target_centerline.trajectory_points[next_target_point_idx].theta;
                     // Normalize heading difference
                     while (heading_diff > M_PI) heading_diff -= 2 * M_PI;
                     while (heading_diff < -M_PI) heading_diff += 2 * M_PI;
                     
                     target_heading = target_centerline.trajectory_points[next_target_point_idx].theta + ratio * heading_diff;
                     target_total_distance = 0;
                 }
             }
             
             // If reached end of centerline
             if (next_target_point_idx >= target_centerline.trajectory_points.size() - 1) {
                 target_x = target_centerline.trajectory_points.back().x;
                 target_y = target_centerline.trajectory_points.back().y;
                 target_heading = target_centerline.trajectory_points.back().theta;
             }
         } else {
             // Already at end of target centerline
             target_x = target_centerline.trajectory_points.back().x;
             target_y = target_centerline.trajectory_points.back().y;
             target_heading = target_centerline.trajectory_points.back().theta;
         }
         
         // Blend between source and target positions
         predicted_object.utm_x = (1.0 - blend_factor) * source_x + blend_factor * target_x;
         predicted_object.utm_y = (1.0 - blend_factor) * source_y + blend_factor * target_y;
         
         // Blend between source and target headings
         double heading_diff = target_heading - source_heading;
         // Normalize heading difference
         while (heading_diff > M_PI) heading_diff -= 2 * M_PI;
         while (heading_diff < -M_PI) heading_diff += 2 * M_PI;
         
         predicted_object.utm_heading = source_heading + blend_factor * heading_diff;
         
         // Set confidence score and maintain speed
         predicted_object.score = (-1.0/(interval_sec_*num_prediction_))*i*interval_sec_ + MAX_PREDICTION_SCORE_;
         predicted_object.speed = object.speed;
         
         // Add to trajectory mode vector
         trajectory_mode.trajectory_points.push_back(predicted_object);
         current_object = predicted_object;
         
         // Add to visualization marker
         geometry_msgs::Point viz_point;
         viz_point.x = predicted_object.utm_x;
         viz_point.y = predicted_object.utm_y;
         viz_point.z = object.utm_z;
         predicted_line.points.push_back(viz_point);
         
         // Update indices for next iteration
         source_point_idx = next_source_point_idx;
         target_point_idx = next_target_point_idx;
     }
 }
 
 // Multi-modal prediction method
 void NaiveMotionPredict::makePredictionMultiModal(
     const smartcar_msgs::DetectedObject& object,
     std::vector<TrajectoryMode>& trajectory_modes,
     visualization_msgs::MarkerArray& predicted_lines) {
     
     // Find closest centerline point
     CenterlineMatch current_match = findClosestCenterlinePoint(object.utm_x, object.utm_y);
     
     // Fall back to model-based prediction if no close centerline found
     if (current_match.centerline_idx == -1 || current_match.distance > 5.0) {  // 5m threshold
         ROS_WARN_STREAM("Object " << object.id << " is too far from all centerlines, using model-based prediction");
         
         // Create a fallback trajectory using model-based prediction
         TrajectoryMode fallback_mode;
         fallback_mode.mode_type = "model_based";
         fallback_mode.probability = 1.0;  // Only one mode
         
         visualization_msgs::Marker fallback_line;
         std::vector<smartcar_msgs::DetectedObject> fallback_trajectory;
         
         makePrediction(object, fallback_trajectory, fallback_line);
         
         fallback_mode.trajectory_points = fallback_trajectory;
         trajectory_modes.push_back(fallback_mode);
         
         predicted_lines.markers.push_back(fallback_line);
         return;
     }
     
     ROS_INFO_STREAM("Using multi-modal prediction with base centerline " << current_match.centerline_idx);
     
     // Find adjacent centerlines for potential lane changes
     std::vector<CenterlineMatch> adjacent_centerlines = findAdjacentCenterlines(object, current_match);
     
     // 1. Generate lane following trajectory
     {
         TrajectoryMode lane_follow_mode;
         visualization_msgs::Marker lane_follow_marker;
         
         // Base ID for lane follow visualization
         int id_base = std::stoi(object.id) * 10;
         lane_follow_marker.id = id_base;
         
         generateLaneFollowTrajectory(object, current_match, lane_follow_mode, lane_follow_marker);
         trajectory_modes.push_back(lane_follow_mode);
         predicted_lines.markers.push_back(lane_follow_marker);
     }
     
     // 2. Generate lane change trajectories for each adjacent lane
     for (size_t i = 0; i < adjacent_centerlines.size(); i++) {
         TrajectoryMode lane_change_mode;
         visualization_msgs::Marker lane_change_marker;
         
         // Generate unique ID for each lane change visualization
         int id_base = std::stoi(object.id) * 10;
         lane_change_marker.id = id_base + i + 1;
         
         // Determine if this is a left or right lane change
         std::string direction;
         
         // Get centerline headings
         double current_heading = centerlines_[current_match.centerline_idx].trajectory_points[current_match.point_idx].theta;
         double target_heading = centerlines_[adjacent_centerlines[i].centerline_idx].trajectory_points[adjacent_centerlines[i].point_idx].theta;
         
         // Get vector from current to adjacent centerline
         double dx = centerlines_[adjacent_centerlines[i].centerline_idx].trajectory_points[adjacent_centerlines[i].point_idx].x - 
                     centerlines_[current_match.centerline_idx].trajectory_points[current_match.point_idx].x;
         double dy = centerlines_[adjacent_centerlines[i].centerline_idx].trajectory_points[adjacent_centerlines[i].point_idx].y - 
                     centerlines_[current_match.centerline_idx].trajectory_points[current_match.point_idx].y;
         
         // Cross product to determine left or right
         double cross_product = cos(current_heading) * dy - sin(current_heading) * dx;
         
         if (cross_product > 0) {
             direction = "left";
         } else {
             direction = "right";
         }
         
         generateLaneChangeTrajectory(object, current_match, adjacent_centerlines[i], direction, lane_change_mode, lane_change_marker);
         trajectory_modes.push_back(lane_change_mode);
         predicted_lines.markers.push_back(lane_change_marker);
     }
     
     // Normalize probabilities
     double total_probability = 0.0;
     for (const auto& mode : trajectory_modes) {
         total_probability += mode.probability;
     }
     
     if (total_probability > 0.0) {
         for (auto& mode : trajectory_modes) {
             mode.probability /= total_probability;
         }
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
 
   // First add the starting point (t=0) to prediction trajectory
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
   // 1. Find trajectory for this object in loaded trajectories
   int target_index;
   for (int i=0; i < g_lanes.lanes.size(); i++) {
     if (g_lanes.lanes[i].lane_id == std::stoi(object.id)) {
       target_index = i;
       break;
     }
   }
 
   ROS_INFO("target_lane_id: %d", g_lanes.lanes[target_index].lane_id);
 
   // 2. Find closest point in trajectory to current object position
   int target_point_id;
   double distance = 100000;
   for (int i =0; i < g_lanes.lanes[target_index].trajectory_points.size(); i++) {
     double dx = object.utm_x - g_lanes.lanes[target_index].trajectory_points[i].x;
     double dy = object.utm_y - g_lanes.lanes[target_index].trajectory_points[i].y;
     double ds = std::sqrt(dx * dx + dy * dy);
 
     if (distance < 0.1 && ds > distance) {
       // Found the closest point
       break;
     }
 
     if (ds < distance) {
       target_point_id = i;
       distance = ds;
     }
   }
 
   // Consider algorithm-based prediction if object is far from recorded trajectory
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
 
     // First add starting point (t=0) to prediction trajectory
     predicted_objects_vec.push_back(target_object);
 
     initializeROSmarker(object.header, tmp_pose, object.id, predicted_line);
 
     for (int ith_prediction = 1; ith_prediction <= num_prediction_; ith_prediction++) {
       smartcar_msgs::DetectedObject predicted_object;
       if (target_point_id + ith_prediction >= g_lanes.lanes[target_index].trajectory_points.size()) {
         // If object is approaching the end of recorded trajectory, use algorithm for remaining points
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
 
       // First add starting point (t=0) to prediction trajectory
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
     if (object.speed < 0.1) {
       // Stationary object, no trajectory prediction
       output.objects.push_back(object);
       continue;
     }
     
     // Choose prediction method: multi-modal, centerline, recorded trajectory, or model-based
     if (predictionMultiModal_) {
       ROS_INFO("Using multi-modal prediction");
       
       std::vector<TrajectoryMode> trajectory_modes;
       visualization_msgs::MarkerArray object_predicted_lines;
       
       makePredictionMultiModal(object, trajectory_modes, object_predicted_lines);
       
       // Select the most likely trajectory for output
       if (!trajectory_modes.empty()) {
         // Find the trajectory mode with highest probability
         int best_mode_idx = 0;
         double best_probability = trajectory_modes[0].probability;
         
         for (size_t i = 1; i < trajectory_modes.size(); i++) {
           if (trajectory_modes[i].probability > best_probability) {
             best_probability = trajectory_modes[i].probability;
             best_mode_idx = i;
           }
         }
         
         // Construct object with predicted trajectory
         smartcar_msgs::DetectedObject tmp_object = object;
         tmp_object.trajectory_.trajectory_points.clear();
         
         for (const auto &predicted_object : trajectory_modes[best_mode_idx].trajectory_points) {
           smartcar_msgs::My_Trajectory_Point predicted_point;
           predicted_point.x = predicted_object.utm_x;
           predicted_point.y = predicted_object.utm_y;
           predicted_point.v = predicted_object.speed;
           tmp_object.trajectory_.trajectory_points.push_back(predicted_point);
         }
         
         // Add mode probability information (could be used by planning)
         // This could be extended with a custom message type in the future
         tmp_object.behavior_state = best_mode_idx;  // Use behavior_state to store mode index
         
         // Visualize only stably tracked objects
         if (object.pose_reliable) {
           output.objects.push_back(tmp_object);
           
           // Add all prediction markers
           for (const auto &marker : object_predicted_lines.markers) {
             predicted_lines.markers.push_back(marker);
           }
         }
       }
     } else if (predictionByCenterline_) {
       ROS_INFO("Using centerline-based prediction");
       
       std::vector<smartcar_msgs::DetectedObject> predicted_objects_vec;
       visualization_msgs::Marker predicted_line;
       
       makePredictionByCenterline(object, predicted_objects_vec, predicted_line);
       
       // Construct object with predicted trajectory
       smartcar_msgs::DetectedObject tmp_object = object;
       smartcar_msgs::My_Trajectory_Point predicted_point;
       
       for (const auto &predicted_object : predicted_objects_vec) {
         predicted_point.x = predicted_object.utm_x;
         predicted_point.y = predicted_object.utm_y;
         predicted_point.v = predicted_object.speed;
         tmp_object.trajectory_.trajectory_points.push_back(predicted_point);
       }
       
       // Visualize only stably tracked objects
       if (object.pose_reliable) {
         output.objects.push_back(tmp_object);
         predicted_line.id = iddd * 100;
         iddd++;
         predicted_lines.markers.push_back(predicted_line);
       }
     } else if (predictionByrecorded_trajectories_) {
       ROS_INFO("Using recorded trajectory-based prediction");
 
       std::vector<smartcar_msgs::DetectedObject> predicted_objects_vec;
       visualization_msgs::Marker predicted_line;
       
       // Find trajectory for this object in loaded trajectories
       int target_index = -1;
       for (int i=0; i < g_lanes.lanes.size(); i++) {
         if (g_lanes.lanes[i].lane_id == std::stoi(object.id)) {
           target_index = i;
           break;
         }
       }
       
       if (target_index == -1) {
         ROS_WARN_STREAM("Object " << object.id << " is not found in recorded paths");
         makePrediction(object, predicted_objects_vec, predicted_line);
       } else {
         makePredictionByRecord(object, predicted_objects_vec, predicted_line);
       }
       
       // Construct object with predicted trajectory
       smartcar_msgs::DetectedObject tmp_object = object;
       smartcar_msgs::My_Trajectory_Point predicted_point;
       
       for (const auto &predicted_object : predicted_objects_vec) {
         predicted_point.x = predicted_object.utm_x;
         predicted_point.y = predicted_object.utm_y;
         predicted_point.v = predicted_object.speed;
         tmp_object.trajectory_.trajectory_points.push_back(predicted_point);
       }
       
       // Visualize only stably tracked objects
       if (object.pose_reliable) {
         output.objects.push_back(tmp_object);
         predicted_line.id = iddd * 100;
         iddd++;
         predicted_lines.markers.push_back(predicted_line);
       }
     } else {
       ROS_INFO("Using model-based prediction");
       
       std::vector<smartcar_msgs::DetectedObject> predicted_objects_vec;
       visualization_msgs::Marker predicted_line;
       
       makePrediction(object, predicted_objects_vec, predicted_line);
       
       // Construct object with predicted trajectory
       smartcar_msgs::DetectedObject tmp_object = object;
       smartcar_msgs::My_Trajectory_Point predicted_point;
       
       for (const auto &predicted_object : predicted_objects_vec) {
         predicted_point.x = predicted_object.utm_x;
         predicted_point.y = predicted_object.utm_y;
         predicted_point.v = predicted_object.speed;
         tmp_object.trajectory_.trajectory_points.push_back(predicted_point);
       }
       
       // Visualize only stably tracked objects
       if (object.pose_reliable) {
         output.objects.push_back(tmp_object);
         predicted_line.id = iddd * 100;
         iddd++;
         predicted_lines.markers.push_back(predicted_line);
       }
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
   // Calculate distance from object to vehicle rear axle center in vehicle coordinates
   double distance = std::sqrt(std::pow(in_object.x,2)+
                               std::pow(in_object.y,2));
   if (!in_object.valid ||
       std::isnan(in_object.heading) ||
       (distance <= filter_out_close_object_threshold_) ||
       (in_object.length <= 0) ||
       (in_object.width <= 0) ||
       (in_object.height <= 0)
     )
   {
     return false;
   }
   return true;
 }//end IsObjectValid














// /*
//  * @Copyright: jinxiaoxin@whut.edu.cn
//  * @Author: jinxiaoxin235
//  * @Date: 2023-04-23 19:56:39
//  * @LastEditors: xining095@whut.edu.cn
//  * @LastEditTime: 2025-03-23
//  * @FilePath: src/prediction/motion_predictor/naive_motion_predict/src/naive_motion_predict.cpp
//  */

// #include <naive_motion_predict/naive_motion_predict.h>

// NaiveMotionPredict::NaiveMotionPredict() :
//   nh_(),
//   private_nh_("~"),
//   MAX_PREDICTION_SCORE_(1.0),
//   map_handle_(3.75)  // 初始化地图处理对象，默认车道宽度3.75米
// {
//   private_nh_.param<double>("interval_sec", interval_sec_, 0.1);
//   private_nh_.param<int>("num_prediction", num_prediction_, 80);
//   private_nh_.param<double>("sensor_height_", sensor_height_, 0);
//   private_nh_.param<double>("filter_out_close_object_threshold", filter_out_close_object_threshold_, 1.5);
//   private_nh_.param<bool>("predictionByrecorded_trajectories", predictionByrecorded_trajectories_, false);
//   private_nh_.param<std::string>("waypoints_file", waypoints_file_, "/home/erro");
  
//   // 添加中心线预测的参数
//   private_nh_.param<bool>("predictionByCenterline", predictionByCenterline_, false);

//   ROS_INFO_STREAM("predictionByrecorded_trajectories: " << predictionByrecorded_trajectories_);
//   ROS_INFO_STREAM("predictionByCenterline: " << predictionByCenterline_);

//   predicted_objects_pub_ = nh_.advertise<smartcar_msgs::DetectedObjectArray>("/prediction/motion_predictor/objects", 1);
//   predicted_paths_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("/prediction/motion_predictor/path_markers", 10);
//   detected_objects_sub_ = nh_.subscribe("/ITS/DetectObjects", 1, &NaiveMotionPredict::objectsCallback, this);

//   // 如果启用基于中心线的预测，加载中心线文件
//   if (predictionByCenterline_) {
//     std::vector<std::string> centerline_files;
//     private_nh_.param<std::vector<std::string>>("centerline_files", centerline_files, std::vector<std::string>());
    
//     if (centerline_files.empty()) {
//       ROS_WARN("predictionByCenterline is enabled but no centerline files specified.");
//     } else {
//       loadCenterlineFiles(centerline_files);
//     }
//   }
  
//   // 已有的基于录制轨迹的预测初始化
//   if (predictionByrecorded_trajectories_) {
//     double road_width = 3.75;
//     MapHandle map_handle(road_width);
    
//     //1.得到全部轨迹文件名
//     std::vector<std::string> files;
//     get_all_files(waypoints_file_, files);
//     for (auto &file : files) {
//         std::cout << "file path: " << file << std::endl;
//     }

//     //2.提取有效的轨迹文件名
//     std::vector<std::string> vaild_files;
//     vaild_files = remove_erro_files(files, ".csv");
//     for (auto &file : vaild_files) {
//         std::cout << "vaild_files path: " << file << std::endl;
//     }

//     //3.读取轨迹，并根据轨迹名字获得object id
//     for (long unsigned int i=0; i < vaild_files.size(); i++) {
//         read_csv(vaild_files[i], gWaypoints);
//         map_handle.TimeResample(gWaypoints, gWaypoints_fix_time);
//         gWaypoints_fix_time.lane_id = map_handle.get_lane_id(vaild_files[i]);
//         if (gWaypoints_fix_time.lane_id == -1) {
//           ROS_WARN("no find car id");
//           continue;
//         }
//         g_lanes.lanes.push_back(gWaypoints_fix_time);

//         std::cout << "car id " << gWaypoints_fix_time.lane_id << std::endl;
//     }
//   }
// }

// NaiveMotionPredict::~NaiveMotionPredict()
// {
// }

// // 新增：加载中心线文件
// void NaiveMotionPredict::loadCenterlineFiles(const std::vector<std::string>& centerline_files) {
//     centerlines_.clear();
//     setlocale(LC_ALL,"");
    
//     for (int i = 0; i < centerline_files.size(); i++) {
//         smartcar_msgs::My_Trajectory centerline;
//         centerline.lane_id = i;  // 为每条中心线分配一个ID
        
//         // 读取中心线文件
//         std::ifstream file(centerline_files[i]);
//         if (!file.is_open()) {
//             ROS_ERROR_STREAM("无法打开中心线文件: " << centerline_files[i]);
//             continue;
//         }
        
//         std::string line;
//         double relative_time = 0.0;
        
//         while (std::getline(file, line)) {
//             std::istringstream iss(line);
//             double x, y, heading;
            
//             if (!(iss >> x >> y >> heading)) {
//                 continue;  // 跳过无效行
//             }
            
//             smartcar_msgs::My_Trajectory_Point point;
//             point.x = x;
//             point.y = y;
//             point.theta = heading;
//             point.relative_time = relative_time;
//             relative_time += 0.1;  // 任意时间增量
            
//             centerline.trajectory_points.push_back(point);
//         }
        
//         centerline.num = centerline.trajectory_points.size();
        
//         if (centerline.num > 0) {
//             centerlines_.push_back(centerline);
//             ROS_INFO_STREAM("加载中心线 " << i << " 包含 " << centerline.num << " 个点");
//         }
//     }
    
//     ROS_INFO_STREAM("总共加载了 " << centerlines_.size() << " 条中心线");
// }

// // 新增：查找最近的中心线点
// CenterlineMatch NaiveMotionPredict::findClosestCenterlinePoint(double x, double y) {
//     CenterlineMatch match;
//     match.centerline_idx = -1;
//     match.point_idx = -1;
//     match.distance = std::numeric_limits<double>::max();
    
//     for (int i = 0; i < centerlines_.size(); i++) {
//         // 只有当中心线包含足够的点时才进行比较
//         if (centerlines_[i].trajectory_points.size() < 2) {
//             continue;
//         }
        
//         int nearest_point_idx = map_handle_.get_nearst_point(centerlines_[i], x, y);
//         double dx = x - centerlines_[i].trajectory_points[nearest_point_idx].x;
//         double dy = y - centerlines_[i].trajectory_points[nearest_point_idx].y;
//         double distance = std::sqrt(dx*dx + dy*dy);
        
//         if (distance < match.distance) {
//             match.centerline_idx = i;
//             match.point_idx = nearest_point_idx;
//             match.distance = distance;
//         }
//     }
    
//     return match;
// }

// void NaiveMotionPredict::initializeROSmarker(const std_msgs::Header& header, const geometry_msgs::Point& position,
//                                              const std::string object_id, visualization_msgs::Marker& predicted_line)
// {
//   predicted_line.lifetime = ros::Duration(0.2);
//   predicted_line.header.frame_id = "map";//header.frame_id;
//   predicted_line.header.stamp = header.stamp;
//   predicted_line.ns = "predicted_line";
//   predicted_line.action = visualization_msgs::Marker::ADD;
//   predicted_line.pose.orientation.w = 1.0;
//   predicted_line.id =  std::stoi(object_id);
//   predicted_line.type = visualization_msgs::Marker::POINTS;
//   predicted_line.scale.x = 0.25;
//   predicted_line.scale.y = 0.25;

//   // Points are green
//   predicted_line.color.b = 1.0f;
//   predicted_line.color.a = 1.0;

//   geometry_msgs::Point p;
//   p.x = position.x;
//   p.y = position.y;
//   p.z = position.z;
//   predicted_line.points.push_back(p);
// }

// // 新增：基于中心线的预测方法
// void NaiveMotionPredict::makePredictionByCenterline(
//     const smartcar_msgs::DetectedObject& object,
//     std::vector<smartcar_msgs::DetectedObject>& predicted_objects_vec,
//     visualization_msgs::Marker& predicted_line) {
    
//     // 找到最近的中心线点
//     CenterlineMatch match = findClosestCenterlinePoint(object.utm_x, object.utm_y);
    
//     // 如果没有找到足够近的中心线，回退到基于模型的预测
//     if (match.centerline_idx == -1 || match.distance > 5.0) {  // 5米阈值
//         ROS_WARN_STREAM("对象 " << object.id << " 距离所有中心线太远，使用基于模型的预测");
//         makePrediction(object, predicted_objects_vec, predicted_line);
//         return;
//     }
    
//     ROS_INFO_STREAM("使用中心线 " << match.centerline_idx << " 进行预测，距离为 " << match.distance << "米");
    
//     // 为了更容易访问，获取匹配的中心线引用
//     const smartcar_msgs::My_Trajectory& centerline = centerlines_[match.centerline_idx];
    
//     // 初始化当前位置
//     smartcar_msgs::DetectedObject current_object = object;
//     current_object.score = MAX_PREDICTION_SCORE_;
    
//     // 将当前位置添加到预测向量
//     predicted_objects_vec.push_back(current_object);
    
//     // 设置可视化
//     geometry_msgs::Point start_pose;
//     start_pose.x = object.utm_x;
//     start_pose.y = object.utm_y;
//     start_pose.z = object.utm_z;
//     initializeROSmarker(object.header, start_pose, object.id, predicted_line);
    
//     // 根据车辆速度计算每个时间步的距离
//     double distance_per_step = object.speed * interval_sec_;
    
//     // 变量跟踪沿中心线的进度
//     int current_point_idx = match.point_idx;
//     double accumulated_distance = 0.0;
    
//     // 生成未来位置
//     for (int i = 0; i < num_prediction_; i++) {
//         smartcar_msgs::DetectedObject predicted_object = current_object;
        
//         // 沿中心线找位置
//         double total_distance_to_travel = distance_per_step;
        
//         while (total_distance_to_travel > 0 && current_point_idx < centerline.trajectory_points.size() - 1) {
//             int next_point_idx = current_point_idx + 1;
            
//             // 计算当前点和下一个点之间的距离
//             double dx = centerline.trajectory_points[next_point_idx].x - 
//                         centerline.trajectory_points[current_point_idx].x;
//             double dy = centerline.trajectory_points[next_point_idx].y - 
//                         centerline.trajectory_points[current_point_idx].y;
//             double segment_distance = std::sqrt(dx*dx + dy*dy);
            
//             if (total_distance_to_travel >= segment_distance) {
//                 // 移动到下一个点
//                 total_distance_to_travel -= segment_distance;
//                 current_point_idx = next_point_idx;
//             } else {
//                 // 在点之间插值
//                 double ratio = total_distance_to_travel / segment_distance;
//                 predicted_object.utm_x = centerline.trajectory_points[current_point_idx].x + 
//                                        ratio * dx;
//                 predicted_object.utm_y = centerline.trajectory_points[current_point_idx].y + 
//                                        ratio * dy;
                
//                 // 插值航向角
//                 double heading_diff = centerline.trajectory_points[next_point_idx].theta - 
//                                      centerline.trajectory_points[current_point_idx].theta;
//                 // 归一化航向角差异
//                 while (heading_diff > M_PI) heading_diff -= 2 * M_PI;
//                 while (heading_diff < -M_PI) heading_diff += 2 * M_PI;
                
//                 predicted_object.utm_heading = centerline.trajectory_points[current_point_idx].theta + 
//                                             ratio * heading_diff;
                
//                 // 重置累积距离，为下一次迭代准备
//                 total_distance_to_travel = 0;
//             }
//         }
        
//         // 如果到达中心线末端，停留在最后一个点
//         if (current_point_idx >= centerline.trajectory_points.size() - 1) {
//             predicted_object.utm_x = centerline.trajectory_points.back().x;
//             predicted_object.utm_y = centerline.trajectory_points.back().y;
//             predicted_object.utm_heading = centerline.trajectory_points.back().theta;
//         }
        
//         // 设置置信度分数并保持速度
//         predicted_object.score = (-1.0/(interval_sec_*num_prediction_))*i*interval_sec_ + MAX_PREDICTION_SCORE_;
//         predicted_object.speed = object.speed;
        
//         // 添加到预测向量
//         predicted_objects_vec.push_back(predicted_object);
//         current_object = predicted_object;
        
//         // 添加到可视化标记
//         geometry_msgs::Point viz_point;
//         viz_point.x = predicted_object.utm_x;
//         viz_point.y = predicted_object.utm_y;
//         viz_point.z = object.utm_z;
//         predicted_line.points.push_back(viz_point);
//     }
// }

// void NaiveMotionPredict::makePrediction(const smartcar_msgs::DetectedObject& object,
//                                         std::vector<smartcar_msgs::DetectedObject>& predicted_objects_vec,
//                                         visualization_msgs::Marker& predicted_line)
// {
//   smartcar_msgs::DetectedObject target_object = object;
//   target_object.score = MAX_PREDICTION_SCORE_;
//   geometry_msgs::Point tmp_pose;
//   tmp_pose.x = object.utm_x;
//   tmp_pose.y = object.utm_y;
//   tmp_pose.z = object.utm_z;

//   //先将起点，即t=0塞进预测轨迹
//   predicted_objects_vec.push_back(target_object);

//   initializeROSmarker(object.header, tmp_pose, object.id, predicted_line);
//   for (int ith_prediction = 0; ith_prediction < num_prediction_; ith_prediction++)
//   {
//     smartcar_msgs::DetectedObject predicted_object = generatePredictedObject(target_object);
//     predicted_object.score = (-1/(interval_sec_*num_prediction_))*ith_prediction*interval_sec_ + MAX_PREDICTION_SCORE_;
//     predicted_objects_vec.push_back(predicted_object);
//     target_object = predicted_object;

//     geometry_msgs::Point p;
//     p.x = predicted_object.utm_x;
//     p.y = predicted_object.utm_y;
//     p.z = object.z;
//     predicted_line.points.push_back(p);
//   }
// }

// void NaiveMotionPredict::makePredictionByRecord(const smartcar_msgs::DetectedObject& object,
//                                         std::vector<smartcar_msgs::DetectedObject>& predicted_objects_vec,
//                                         visualization_msgs::Marker& predicted_line)
// {
//   ROS_INFO_STREAM("object_id: " << object.id);
//   ROS_INFO("object_ x: %f   y: %f", object.utm_x, object.utm_y);
//   //1.在读取的轨迹文件中，找出该object的轨迹
//   int target_index;
//   for (int i=0; i < g_lanes.lanes.size(); i++) {
//     if (g_lanes.lanes[i].lane_id == std::stoi(object.id)) {
//       target_index = i;
//       break;
//     }
//   }

//   ROS_INFO("target_lane_id: %d", g_lanes.lanes[target_index].lane_id);

//   //2.找出轨迹中距离目前object最近的点
//   int target_point_id;
//   double distance = 100000;
//   for (int i =0; i < g_lanes.lanes[target_index].trajectory_points.size(); i++) {
//     double dx = object.utm_x - g_lanes.lanes[target_index].trajectory_points[i].x;
//     double dy = object.utm_y - g_lanes.lanes[target_index].trajectory_points[i].y;
//     double ds = std::sqrt(dx * dx + dy * dy);

//     if (distance < 0.1 && ds > distance) {
//       //找到了最近点
//       break;
//     }

//     if (ds < distance) {
//       target_point_id = i;
//       distance = ds;
//     }
//   }

//   //考虑障碍物已经远离录制的轨迹，改用算法预测
//   if (distance < 1) {
//     ROS_INFO("target_point_id: %d", target_point_id);
//     ROS_INFO("target_point x: %f   y: %f", g_lanes.lanes[target_index].trajectory_points[target_point_id].x,
//                                           g_lanes.lanes[target_index].trajectory_points[target_point_id].y);
    
//     smartcar_msgs::DetectedObject target_object = object;
//     target_object.score = MAX_PREDICTION_SCORE_;
    
//     geometry_msgs::Point tmp_pose;
//     tmp_pose.x = object.utm_x;
//     tmp_pose.y = object.utm_y;
//     tmp_pose.z = object.utm_z;

//     //先将起点，即t=0塞进预测轨迹
//     predicted_objects_vec.push_back(target_object);

//     initializeROSmarker(object.header, tmp_pose, object.id, predicted_line);

//     for (int ith_prediction = 1; ith_prediction <= num_prediction_; ith_prediction++) {
//       smartcar_msgs::DetectedObject predicted_object;// = generatePredictedObject(target_object);
//       if (target_point_id + ith_prediction >= g_lanes.lanes[target_index].trajectory_points.size()) {
//         //如果object快远离了录制的轨迹，不足80个时间点，剩余的用算法预测
//         predicted_object = generatePredictedObject(target_object);
//       } else {
//         predicted_object.score = (-1/(interval_sec_*num_prediction_))*ith_prediction*interval_sec_ + MAX_PREDICTION_SCORE_;
//         predicted_object.utm_x = g_lanes.lanes[target_index].trajectory_points[target_point_id + ith_prediction].x;
//         predicted_object.utm_y = g_lanes.lanes[target_index].trajectory_points[target_point_id + ith_prediction].y;
//         predicted_object.speed = g_lanes.lanes[target_index].trajectory_points[target_point_id + ith_prediction].v;
//       }

//       predicted_objects_vec.push_back(predicted_object);
//       target_object = predicted_object;

//       geometry_msgs::Point p;
//       p.x = predicted_object.utm_x;
//       p.y = predicted_object.utm_y;
//       p.z = object.z;
//       predicted_line.points.push_back(p);
//     }
//   } else {
//       smartcar_msgs::DetectedObject target_object = object;
//       target_object.score = MAX_PREDICTION_SCORE_;
//       geometry_msgs::Point tmp_pose;
//       tmp_pose.x = object.utm_x;
//       tmp_pose.y = object.utm_y;
//       tmp_pose.z = object.utm_z;

//       //先将起点，即t=0塞进预测轨迹
//       predicted_objects_vec.push_back(target_object);

//       initializeROSmarker(object.header, tmp_pose, object.id, predicted_line);
//       for (int ith_prediction = 0; ith_prediction < num_prediction_; ith_prediction++) {
//         smartcar_msgs::DetectedObject predicted_object = generatePredictedObject(target_object);
//         predicted_object.score = (-1/(interval_sec_*num_prediction_))*ith_prediction*interval_sec_ + MAX_PREDICTION_SCORE_;
//         predicted_objects_vec.push_back(predicted_object);
//         target_object = predicted_object;

//         geometry_msgs::Point p;
//         p.x = predicted_object.utm_x;
//         p.y = predicted_object.utm_y;
//         p.z = object.z;
//         predicted_line.points.push_back(p);
//       }    
//   }
// }

// smartcar_msgs::DetectedObject NaiveMotionPredict::generatePredictedObject(const smartcar_msgs::DetectedObject& object)
// {
//   smartcar_msgs::DetectedObject predicted_object;
//   if (object.behavior_state == MotionModel::CV)
//   {
//     predicted_object = moveConstantVelocity(object);
//   }
//   else if (object.behavior_state == MotionModel::CTRV)
//   {
//     predicted_object = moveConstantTurnRateVelocity(object);
//   }
//   else
//   {
//     // This is because random motion's velocity is 0
//     predicted_object = object;
//   }

//   return predicted_object;
// }

// smartcar_msgs::DetectedObject NaiveMotionPredict::moveConstantVelocity(const smartcar_msgs::DetectedObject& object)
// {
//   smartcar_msgs::DetectedObject predicted_object;
//   predicted_object = object;
//   double px = object.utm_x;
//   double py = object.utm_y;
//   double velocity = object.speed;
//   // double yaw = object.utm_heading;
//   double yaw = 0.0;

//   // predicted state values
//   double prediction_px = px + velocity * cos(yaw) * interval_sec_;
//   double prediction_py = py + velocity * sin(yaw) * interval_sec_;

//   predicted_object.utm_x = prediction_px;
//   predicted_object.utm_y = prediction_py;
//   predicted_object.speed = velocity;

//   return predicted_object;
// }

// smartcar_msgs::DetectedObject
// NaiveMotionPredict::moveConstantTurnRateVelocity(const smartcar_msgs::DetectedObject& object)
// {
//   smartcar_msgs::DetectedObject predicted_object;
//   predicted_object = object;
//   double px = object.utm_x;
//   double py = object.utm_y;
//   double velocity = object.speed;
//   // double yaw = object.utm_heading;
//   double yaw = 0.0;

//   double yawd = 0;//object.acceleration.linear.y;

//   // predicted state values
//   double prediction_px, prediction_py;

//   // avoid division by zero
//   if (fabs(yawd) > 0.001)
//   {
//     prediction_px = px + velocity / yawd * (sin(yaw + yawd * interval_sec_) - sin(yaw));
//     prediction_py = py + velocity / yawd * (cos(yaw) - cos(yaw + yawd * interval_sec_));
//   }
//   else
//   {
//     prediction_px = px + velocity * interval_sec_ * cos(yaw);
//     prediction_py = py + velocity * interval_sec_ * sin(yaw);
//   }
//   double prediction_yaw = yaw + yawd * interval_sec_;

//   while (prediction_yaw > M_PI)
//     prediction_yaw -= 2. * M_PI;
//   while (prediction_yaw < -M_PI)
//     prediction_yaw += 2. * M_PI;

//   predicted_object.utm_x = prediction_px;
//   predicted_object.utm_y = prediction_py;
//   predicted_object.utm_heading = prediction_yaw;
  
//   return predicted_object;
// }

// double NaiveMotionPredict::generateYawFromQuaternion(const geometry_msgs::Quaternion& quaternion)
// {
//   tf::Quaternion q(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
//   tf::Matrix3x3 m(q);
//   double roll, pitch, yaw;
//   m.getRPY(roll, pitch, yaw);
//   return yaw;
// }

// void NaiveMotionPredict::objectsCallback(const smartcar_msgs::DetectedObjectArray& input)
// {
//   ROS_INFO("..............................");
//   smartcar_msgs::DetectedObjectArray output;
//   visualization_msgs::MarkerArray predicted_lines;
  
//   int iddd = 1;
//   for (const auto &object : input.objects)
//   {
//     std::vector<smartcar_msgs::DetectedObject> predicted_objects_vec;
//     visualization_msgs::Marker predicted_line;
    
//     if (object.speed < 0.1) {
//       //静止障碍物，不预测轨迹
//       output.objects.push_back(object);
//       continue;
//     }
    
//     // 选择预测方法：中心线、录制轨迹或基于模型
//     if (predictionByCenterline_) {
//       ROS_INFO("使用基于中心线的预测");
//       makePredictionByCenterline(object, predicted_objects_vec, predicted_line);
//     } else if (predictionByrecorded_trajectories_) {
//       ROS_INFO("使用基于录制轨迹的预测");

//       //1.在读取的轨迹文件中，找出该object的轨迹
//       int target_index = -1;
//       for (int i=0; i < g_lanes.lanes.size(); i++) {
//         if (g_lanes.lanes[i].lane_id == std::stoi(object.id)) {
//           target_index = i;
//           break;
//         }
//       }
      
//       if (target_index == -1) {
//         ROS_WARN_STREAM("object " << object.id << " is not find record path");
//         makePrediction(object, predicted_objects_vec, predicted_line);
//       } else {
//         makePredictionByRecord(object, predicted_objects_vec, predicted_line);
//       }
//     } else {
//       ROS_INFO("使用基于模型的预测");
//       makePrediction(object, predicted_objects_vec, predicted_line);
//     }

//     //构造包含预测轨迹的障碍物
//     smartcar_msgs::DetectedObject tmp_object;
//     tmp_object = object;
//     smartcar_msgs::My_Trajectory_Point predicted_point;
//     for (const auto &predicted_object : predicted_objects_vec) {
//       predicted_point.x = predicted_object.utm_x;
//       predicted_point.y = predicted_object.utm_y;
//       predicted_point.v = predicted_object.speed;
//       tmp_object.trajectory_.trajectory_points.push_back(predicted_point);
//     }

//     // visualize only stably tracked objects
//     if (!object.pose_reliable)
//     {
//       continue;
//     }
    
//     output.objects.push_back(tmp_object);
//     predicted_line.id =  iddd * 100;
//     iddd++;
//     predicted_lines.markers.push_back(predicted_line);
//   }
  
//   output.num = output.objects.size();
//   output.header = input.header;
//   predicted_objects_pub_.publish(output);
//   printf("The object Traj %ld %ld \n", output.objects.size(), input.objects.size());
//   predicted_paths_pub_.publish(predicted_lines);
// }

// bool NaiveMotionPredict::isObjectValid(const smartcar_msgs::DetectedObject &in_object)
// {
//   //在车辆坐标系下，计算障碍物距离自车后轴中心的距离
//   double distance = std::sqrt(std::pow(in_object.x,2)+
//                               std::pow(in_object.y,2));
//   if (!in_object.valid ||
//       std::isnan(in_object.heading) ||
//       (distance <=  filter_out_close_object_threshold_)||
//       (in_object.length <= 0) ||
//       (in_object.width <= 0) ||
//       (in_object.height <= 0)
//     )
//   {
//     return false;
//   }
//   return true;
// }//end IsObjectValid


