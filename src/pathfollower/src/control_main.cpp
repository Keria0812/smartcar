/*整个节点的主程序
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-05-24 20:53:17
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-09 05:02:25
 * @FilePath: /miniEV/src/pathfollower/src/control_main.cpp
 */
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include<ros/ros.h>
// #include <smartcar_msgs/VehicleStatus.h>
// #include <smartcar_msgs/VehicleLocation.h>
#include <smartcar_msgs/VehicleCmd.h>
#include <smartcar_msgs/Lane.h>
#include <smartcar_msgs/ControlCommandStamped.h>
#include <smartcar_msgs/Location.h>
#include <smartcar_msgs/VehicleChassis.h>


#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Joy.h>


#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <tf/tf.h> 

#include "pathfollower/controller.h"
#include "pathfollower/common.h"
#include "pathfollower/stanley.h"
#include "pathfollower/pure_pursuit.h"
#include "pathfollower/lat_lqr.h"
#include "pathfollower/lat_mpc.h"
#include "pathfollower/lon_mpc.h"


#include "pathfollower/manual_control.h"




std::mutex  follow_path_mutex;
std::mutex  cur_status_mutex;
std::mutex  cur_chassis_mutex;
std::mutex  cur_acc_mutex;



geometry_msgs::PoseArray follow_path;
geometry_msgs::Pose cur_pos;



double cur_velocity = 0.0;//m/s
double target_vel = 0.0;
bool path_update = false;
bool curpos_update = false;
bool curvel_update = false;
bool location_update = false;
bool chassis_update = false;
bool acc_update = false;

smartcar_msgs::ACCTarget cur_acc_target;


smartcar_msgs::Location cur_location;
smartcar_msgs::VehicleChassis cur_chassis;


void FollowPathCallback(const smartcar_msgs::Lane &follow)
{
    std::lock_guard<std::mutex> _guard(follow_path_mutex);
    follow_path.poses.clear();
    follow_path.poses.reserve(follow.waypoints.size());
    for (const smartcar_msgs::Waypoint &pt :follow.waypoints) {
        geometry_msgs::Pose p;
        p.position.x = pt.pose.pose.position.x;
        p.position.y = pt.pose.pose.position.y;
        p.position.z = 0;
        follow_path.poses.emplace_back(p);
    }
    // target_vel = follow.waypoints.begin()->twist.twist.linear.x;
    // target_vel = follow.waypoints.back().twist.twist.linear.x;
    target_vel = follow.waypoints[size_t(follow.waypoints.size()/2.0)].twist.twist.linear.x;



    path_update = true;
};
void LocationCallback(const smartcar_msgs::Location &msg) {
    std::lock_guard<std::mutex> _guard(cur_status_mutex);
    cur_location = msg;
    location_update = true;//一种自动加解锁的方式，C++11，只在作用域内会加锁，出域解锁
};

void CurrentPoseCallback(const geometry_msgs::PoseStamped &msg) {
    cur_pos = msg.pose;
    curpos_update = true;
    return;
};
// void CurrentVelocityCallback(const geometry_msgs::TwistStampedConstPtr &msg)
// {
//     cur_velocity = msg->twist.linear.x;
//     curvel_update = true;
// };
void VehicleChassisCallback(const smartcar_msgs::VehicleChassis &msg) {
    std::lock_guard<std::mutex> _guard(cur_chassis_mutex);
    cur_chassis = msg;
    chassis_update = true;
};

void ACCTargetCallback(const smartcar_msgs::ACCTarget &msg) {
    std::lock_guard<std::mutex> _guard(cur_acc_mutex);//时间上不受影响但共享了全局变量，所以要加锁保证同一时刻只能由一个程序修改变量
    cur_acc_target = msg;
    acc_update = true;
};
void mainback(ros::NodeHandle nh)
{
    ros::Subscriber sub1_ = nh.subscribe("/local_trajectory", 1, &FollowPathCallback);
    ros::Subscriber sub2_ = nh.subscribe("/current_pose", 1, &CurrentPoseCallback);
    ros::Subscriber sub_location_ = nh.subscribe("smartcar/location", 1, &LocationCallback);
    ros::Subscriber sub_vehicle_chassis_ = nh.subscribe("smartcar/chassis", 1, &VehicleChassisCallback);
    ros::Subscriber sub_acc_target = nh.subscribe("/ACC_Target", 1, &ACCTargetCallback);


    ros::MultiThreadedSpinner spinner(5);//在这个函数里面开了五个线程处理回调函数，时间上互不影响
    spinner.spin();
}


int main(int argc, char *argv[]) {
    ros::init(argc, argv, "pathfollower");



    ros::NodeHandle nh_, nh_param_("~");
    std::string vehicle_config;
    std::string follow_method;
    std::string lqr_config;
    std::string mpc_config;
    std::string lon_mpc_config;
    bool calivration;
    // std::cout << vehicle_config <<
    nh_param_.param<std::string>("vehicle_physical_config", vehicle_config, "/home/xining095/Carmaker/smartcar/miniEV_grad/src/pathfollower/config/vehicle_physical_miniEV.yaml");
    nh_param_.param<std::string>("follow_method", follow_method, "PurePursuit");
    nh_param_.param<std::string>("lqr_config", lqr_config, "/home/xining095/Carmaker/smartcar/miniEV_grad/src/pathfollower/config/lqr_parameters.yaml");
    nh_param_.param<std::string>("mpc_config", mpc_config, "/home/xining095/Carmaker/smartcar/miniEV_grad/src/pathfollower/config/mpc_parameters.yaml");
    nh_param_.param<std::string>("lon_mpc_config", lon_mpc_config, "/home/xining095/Carmaker/smartcar/miniEV_grad/src/pathfollower/config/lon_mpc_parameters.yaml");

    ros::Publisher pub_cmd = nh_.advertise<smartcar_msgs::ControlCommandStamped>("ctrl_cmd", 10);

    // std::string vehicle_config = "/home/jinxiaoxin/master_graduation/miniEV/src/pathfollower/config/vehicle_physical_miniEV.yaml";
    // std::string vehicle_config = "/home/jinxiaoxin/master_graduation/miniEV/src/pathfollower/config/vehicle_physical_Tesla.yaml";
    

    std::unique_ptr<PathFollower::Controller> vehicle_ctrl;

   PathFollower::LonMPC vehicle_ctrl_lon(vehicle_config, lon_mpc_config); 

//follow的方法是在launch文件中传过来的
    if (follow_method == "PurePursuit") {
        vehicle_ctrl = std::make_unique<PathFollower::PurePursuit> (vehicle_config) ;
    } else if (follow_method == "Staneley") {
        vehicle_ctrl = std::make_unique<PathFollower::Stanley> (vehicle_config) ;
    } else if (follow_method == "LQR") {//轨迹跟踪
        vehicle_ctrl = std::make_unique<PathFollower::LatLQR> (vehicle_config, lqr_config); 
    } else if (follow_method == "MPC") {//暂时不用
        vehicle_ctrl = std::make_unique<PathFollower::LatMPC> (vehicle_config, mpc_config); 
    } else if (follow_method == "Manual") {//发加速度信号的,地图选calc
        vehicle_ctrl = std::make_unique<PathFollower::ManualControl> (vehicle_config); 
    }//做哪个实验就把字符串改成相应的
    else {
        ROS_ERROR("There is not the FollowMethod which is %s......\n", follow_method.c_str());
        exit(1);
    }
    
//  
    std::thread t(mainback, nh_);//单独开了一个线程，处理所有回调
    ros::Rate loop(50);//20ms
    while (ros::ok()) {
        // printf(". ");
        // std::cout << location_update << chassis_update << std::endl;
        if (/*path_update &&*/ location_update && chassis_update) {
            //此处写算法
            path_update = false;
            curpos_update = false;
            curvel_update =false;
            location_update = false;
            chassis_update = false;
            PathFollower::ControlCommand calc_cmd;
            PathFollower::ControlCommand calc_cmd4lon;
            //传入的参数，也加锁保证数据安全
            if (vehicle_ctrl->Follow(cur_location, cur_status_mutex, 
                                        follow_path,follow_path_mutex,
                                        cur_chassis, cur_chassis_mutex,
                                        target_vel, calc_cmd)) {
                target_vel = calc_cmd.LinearVelocity();//速度实验打开这个和下面两行                          
                vehicle_ctrl_lon.updateAccTarget(cur_acc_target, cur_acc_mutex);
                vehicle_ctrl_lon.Follow(cur_location, cur_status_mutex, 
                                follow_path,follow_path_mutex,
                                cur_chassis, cur_chassis_mutex,
                                target_vel, calc_cmd4lon);   //follow是pid命令                

                smartcar_msgs::ControlCommandStamped cur_cmd;
                cur_cmd.header.stamp = ros::Time::now();

                
                cur_cmd.cmd.linear_velocity = calc_cmd.LinearVelocity();
                cur_cmd.cmd.steering_angle = calc_cmd.SteeringAngle();

                if (calc_cmd.Enable_linear_acceleration_) {
                    cur_cmd.cmd.linear_acceleration = calc_cmd.Linearacceleration();
                }
                if (calc_cmd.Enable_steering_speed_) {
                    cur_cmd.cmd.steering_speed = calc_cmd.SteeringSpeed();
                }
                cur_cmd.cmd.linear_acceleration = calc_cmd4lon.Linearacceleration();//加速度实验屏蔽这两行
                cur_cmd.cmd.linear_velocity = calc_cmd4lon.LinearVelocity();

                cur_cmd.cmd.steering_angle = cur_cmd.cmd.steering_angle;

                ROS_INFO("The SteeringAngle is %f, acc is %f m/s2 \n",cur_cmd.cmd.steering_angle / M_PI * 180.0, cur_cmd.cmd.linear_acceleration);

                // ROS_INFO("wheel_base %f   kappa %f", wheel_base_, kappa);
                // ROS_INFO("steering_angle %f", ccs.cmd.steering_angle);
                pub_cmd.publish(cur_cmd);


            }
        

            // while (!(location_update && chassis_update));
            
        }

        loop.sleep();
    }
    

    //TODO1: 订阅位姿信息、轨迹信息、发布控制命令


    //TODO2: 设计全局变量，用于控制分层,利用C++的多态特性重定义各种控制器，标准化控制器输入输出

    //TODO3: 设计一个简单的横纵向分离的控制算法，用于功能性验证

    //TODO4: 完成车辆油门刹车标定工作
    t.join();
    return 0;
    //TODO5: 设计合适的横纵向控制算法
}