//###################################################
//                        TF MODULE FOR THE HYBRID A*
//###################################################
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <mutex>
#include <memory>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>

// mutex
std::mutex mutex_;


// map pointer
nav_msgs::OccupancyGrid grid_;

// odometry instance
nav_msgs::Odometry odometry_;

// map callback
void setMap(const nav_msgs::OccupancyGrid::ConstPtr map) {
    std::cout << "Creating transform for map..." << std::endl;
    grid_ = *map;
    grid_.info.origin.position.z = 0.0;

}

// odometry callback
void setOdometry(const nav_msgs::OdometryConstPtr odometry) {
    ROS_DEBUG("rec odometry msgs");
    std::lock_guard<std::mutex> lock(mutex_);
    odometry_= *odometry;
    //  tf::Quaternion quat;
    //     double roll, pitch, yaw;

    // tf::quaternionMsgToTF(odometry_.pose.pose.orientation, quat);
    // // std::cout << curpos.pose.orientation.x << " " << curpos.pose.orientation.y  << " " << curpos.pose.orientation.z<< " " << curpos.pose.orientation.w<< " " << std::endl;
    // tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);//进行转换
    // is_pose_set_ = true;
}

int main(int argc, char** argv) {
    // initiate the broadcaster
    ros::init(argc, argv, "tf_broadcaster");
    ros::NodeHandle n;

    // subscribe to map updates
    ros::Subscriber sub_map = n.subscribe("/occ_map", 1, setMap);

    // subscribe to odometry updates
    ros::Subscriber sub_odometry = n.subscribe("base_pose_ground_truth", 10, &setOdometry);
    nav_msgs::Odometry tmp_odometry;

    // create tfPose
    tf::Pose tfPose(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0));
    tf::Pose tfPose_map2odometry(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0));


    ros::AsyncSpinner spin(2);
    spin.start();

    // ros::Rate r(100);
    ros::Rate loop(100);

    tf::TransformBroadcaster broadcaster;


    while (ros::ok()) {
        //处理回调
        // ros::spinOnce();

        {
            std::lock_guard<std::mutex> lock(mutex_);
            tmp_odometry = odometry_;
            tmp_odometry.pose.pose.position.z = 0.0;
        }

        // transform from geometry msg to TF
        if (grid_.header.seq != 0) {
            tf::poseMsgToTF(grid_.info.origin, tfPose);
            ROS_DEBUG(".....");
        }

        if (tmp_odometry.header.seq != 0) {
            tf::poseMsgToTF(tmp_odometry.pose.pose, tfPose_map2odometry);
        }        

        //发布tf变换树的类型，一个变换树包含：变换(子坐标系在父坐标系中的位置)、时间戳、父坐标系frame_id、子坐标系frame_id
        // map to odom（这里设置统一）
        broadcaster.sendTransform(tf::StampedTransform(
            tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0)), ros::Time::now(), "map", "odom"));

        // map to path
        broadcaster.sendTransform(tf::StampedTransform(
            tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0)), ros::Time::now(), "map", "path"));
        
        // map to base_link
        broadcaster.sendTransform(tf::StampedTransform(tfPose_map2odometry, ros::Time::now(), "map", "base_link"));

        // base_link to ego_vehicle
        broadcaster.sendTransform(tf::StampedTransform(
            tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0)), ros::Time::now(), "base_link", "ego_vehicle"));


        //休眠
        loop.sleep();
    }

    spin.stop();
}
