/*
 * @Date: 2021-11-05 10:47:27
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2023-07-05 21:55:19
 * @FilePath: /miniEV/src/visualization/show_trajectory/src/marker_list.cpp
 */

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <smartcar_msgs/Lane.h>
#include <geometry_msgs/PoseArray.h>
#include <mutex>
#include <cmath>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <tf/tf.h>
#include <smartcar_msgs/Waypoint.h>
#include <geometry_msgs/PoseStamped.h>

geometry_msgs::PoseArray g_plan;
std::mutex g_plan_mutex;
geometry_msgs::Pose gpos;

// calculation relative coordinate of point from current_pose frame
geometry_msgs::Point calcRelativeCoordinate(geometry_msgs::Point point_msg, geometry_msgs::Pose current_pose)
{
  tf::Transform inverse;
  tf::poseMsgToTF(current_pose, inverse);
  tf::Transform transform = inverse.inverse();

  tf::Point p;
  pointMsgToTF(point_msg, p);
  tf::Point tf_p = transform * p;
  geometry_msgs::Point tf_point_msg;
  pointTFToMsg(tf_p, tf_point_msg);

  return tf_point_msg;
}

void follow_callback(const smartcar_msgs::Lane &follow)
{
    std::lock_guard<std::mutex> _guard(g_plan_mutex);
    // g_plan_marker.points.clear();
    // g_plan_marker.colors.clear();
    g_plan.poses.clear();
    for (const smartcar_msgs::Waypoint &pt :follow.waypoints) {
        geometry_msgs::Pose p;
        p.position.x = pt.pose.pose.position.x;
        p.position.y = pt.pose.pose.position.y;
        p.position.z = 0;
        g_plan.poses.push_back(p);
    }
}

void callbackFromCurrentPose(const geometry_msgs::PoseStampedConstPtr &msg){
    gpos = msg->pose;
     tf::Quaternion quat;
        double roll, pitch, yaw;

    tf::quaternionMsgToTF(gpos.orientation, quat);
    // std::cout << curpos.pose.orientation.x << " " << curpos.pose.orientation.y  << " " << curpos.pose.orientation.z<< " " << curpos.pose.orientation.w<< " " << std::endl;
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);//进行转换
    // is_pose_set_ = true;
    std::cout << yaw << " " << roll << pitch <<std::endl;
}   


int main( int argc, char** argv )
{
  ros::init(argc, argv, "points_and_lines");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Subscriber plan_sub = n.subscribe("/local_trajectory", 1000, follow_callback);
  ros::Subscriber carpos_sub = n.subscribe<geometry_msgs::PoseStamped>("/current_pose", 100, &callbackFromCurrentPose);

  ros::Rate r(50);

  while (ros::ok())
  {
    ros::spinOnce();
// %Tag(MARKER_INIT)%
    visualization_msgs::Marker points, line_strip, line_list;
    points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = "base_link";
    points.header.stamp = line_strip.header.stamp = line_list.header.stamp = ros::Time::now();
    points.ns = line_strip.ns = line_list.ns = "points_and_lines";
    points.action = line_strip.action = line_list.action = visualization_msgs::Marker::ADD;
    points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = 1.0;
// %EndTag(MARKER_INIT)%

// %Tag(ID)%
    points.id = 0;
    line_strip.id = 1;
    line_list.id = 2;
// %EndTag(ID)%

// %Tag(TYPE)%
    points.type = visualization_msgs::Marker::POINTS;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    line_list.type = visualization_msgs::Marker::LINE_LIST;
// %EndTag(TYPE)%

// %Tag(SCALE)%
    // POINTS markers use x and y scale for width/height respectively
    points.scale.x = 0.2;
    points.scale.y = 0.2;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    line_strip.scale.x = 0.1;
    line_list.scale.x = 0.1;
// %EndTag(SCALE)%

// %Tag(COLOR)%
    // Points are green
    points.color.g = 1.0f;
    points.color.a = 1.0;

    // Line strip is blue
    line_strip.color.b = 1.0;
    line_strip.color.a = 1.0;

    // Line list is red
    line_list.color.r = 1.0;
    line_list.color.a = 1.0;
// %EndTag(COLOR)%

// %Tag(HELIX)%
    // Create the vertices for the points and lines
    {
        std::lock_guard<std::mutex> _guard(g_plan_mutex);
        // ROS_INFO("size %d", g_plan.poses.size());
        for (uint32_t i = 0; i < g_plan.poses.size(); ++i)
        {
        // float x = g_plan.poses[i].position.x;
        // float y = g_plan.poses[i].position.y; 
        // float z = g_plan.poses[i].position.z;
        geometry_msgs::Point p = calcRelativeCoordinate(g_plan.poses[i].position, gpos);
        if(p.x < 0) continue;

        points.points.push_back(p);
        line_strip.points.push_back(p);

        // The line list needs two points for each line
        line_list.points.push_back(p);
        p.z += 0.1;
        line_list.points.push_back(p);
        }
    }
// %EndTag(HELIX)%

    marker_pub.publish(points);
    marker_pub.publish(line_strip);
    marker_pub.publish(line_list);

    r.sleep();

  }
  return 0;
}
// %EndTag(FULLTEXT)%
