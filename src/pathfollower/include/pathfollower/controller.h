/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-09 21:24:57
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-26 10:25:11
 * @FilePath: /miniEV_grad/src/pathfollower/include/pathfollower/controller.h
 */
#pragma once 
#ifndef PATHFOLLOWER_CONTROLLER_H_
#define PATHFOLLOWER_CONTROLLER_H_



#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>
#include <chrono>
#include <mutex>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>

#include <smartcar_msgs/Location.h>
#include <smartcar_msgs/VehicleChassis.h>
#include <smartcar_msgs/ACCTarget.h>



#include "pathfollower/common.h"
#include "pathfollower/pid.h"

#include "filters/digital_filter.h"
#include "filters/digital_filter_coefficients.h"
#include "filters/mean_filter.h"


//此处为控制的基类，定义各种变量
/***************************************************************************
 * 1、控制算法的输入为cur_pos, followpath, target_velocity ，cur_velocity
 * 2、控制算法的输出为steering_angle、steering_angle_vel、纵向acceleration。
 * 3、控制类需要读取车身配置文件、获取车辆参数
 * 4、控制算法需要读取算法配置文件、获取控制算法参数（在派生类中实现）
 * 5、控制类提供以下几个接口：
 *    ctrl_cmd follow(cur_pos, follow_path, target_velocity, cur_velocity);//用于发送控制命令
 *    一个用于读取车辆参数的函数
 *    一个用于读取算法配置文件的函数（在子类中实现）
 * 6、其他思路，各个算法相同都需要的文件定义为physical类，在基类中实现
 * 算法单独需要的，在派生类中实现
 * 设计模式：工厂模式
 **************************************************************************/
namespace PathFollower {

class ControlCommand {
    private:
        double steering_angle_ = 0.0;// rad
        double linear_velocity_ = 0.0;// m/s

        double steering_speed_ = 0.0;// rad/s
        double linear_acceleration_ = 0.0;// m/s^2
        
    public: 
        bool setCommand(double steering_angle, double linear_velocity);//enable_steer_vel
        bool setCommand(double steering_angle, double linear_velocity, double linear_acceleration);//enable_steer_acc
        bool setCommand(double steering_angle, double linear_velocity, double linear_acceleration, double steering_speed);//enable_steer_rotate_acc

        bool setVehicleStop();
        bool Enable_linear_acceleration_ = false;
        bool Enable_steering_speed_ = false;

        double SteeringAngle() {return steering_angle_ ;};
        double Linearacceleration() {return linear_acceleration_;};
        double LinearVelocity() {return linear_velocity_ ;}; 
        double SteeringSpeed() {return steering_speed_ ;}; 


};

class VehiclePhysical {
    public: 

    double steer_ratio_ = 0.0;
    double length_ = 0.0;
    double width_ = 0.0;
    double height_ = 0.0;
    double wheel_base_ = 0.0;
    double rear_overhang_ = 0.0;//后悬
    double front_overhang_ = 0.0;//前悬
    double mass_ = 0.0;//kg

    double cf_ = 0.0;//
    double cr_ = 0.0;//侧偏刚度

    double lf_mass_ = 0.0;
    double rf_mass_ = 0.0;
    double lr_mass_ = 0.0;
    double rr_mass_ = 0.0;

    double lf_ = 0.0;//前轮到重心
    double lr_ = 0.0; //后轮到重心

    double iz_ = 0.0;

    double max_steering_angle_ = 0.0;//rad
    double max_steering_speed_ = 0.0;//rad/s
    double min_radius_turn_ = 0.0;//m

    double max_lon_acceleration_ = 0.0;
    double max_lon_deceleration_ = 0.0;//为正值

    double front_mass_ = 0.0;
    double rear_mass_ = 0.0;//这个计算可能有问题

    bool initPhysical(const std::string &vehicle_physical_config);
};

class VehicleStatus 
{
    public:
        Pose cur_pos;
        Vector3 utm_vel;//utm,m/s
        Vector3 utm_acc;//utm m/s2
        Vector3 rpy_rate;//baselink, rad/s
        Vector3 linear_vel;//base_link, m/s
        Vector3 linear_acc;//base_link, m/s2
        double speed;//absolute_speed
};

class VehicleChassis {
    public:
        ControlCommand cur_cmd;
        double feedback_steering_angle = 0.0;
        double feedback_gas = 0.0;//-1.0-1.0;
        double feedback_brake = 0.0;//-1.0-1.0;
        double feedback_torque = 0.0;
        double feedback_brake_pressure = 0.0;//mpa
        double speed; //km/h

        bool gas_pedal_press = false;
        bool brake_pedal_press = false;
        double wheel_speed_lf = 0.0;//km/h 左前轮
        double wheel_speed_lr = 0.0;//km/h 左后轮
        double wheel_speed_rf = 0.0;//km/h 右前轮
        double wheel_speed_rr = 0.0;//km/h 右后轮

        char gear = 'N';//这应该是个枚举类，后面再说吧

};
class Controller
{
private:
    /* data */
    std::unique_ptr<PID>  longitudinalvelocitypid_ = std::make_unique<PID>(0.50,0.0,0.0, 1.5, -2.5, 1.5, -2.5);

    bool updateVehicleStatus(const smartcar_msgs::Location &cur_status, std::mutex &status_mutex);
    bool updateVehicleChassis(const smartcar_msgs::VehicleChassis &cur_chassis, std::mutex &chassis_mutex);
    bool updateTarget(const geometry_msgs::PoseArray &follow_path, double target_velocity, std::mutex &path_mutex);
protected:

    VehiclePhysical physical_;
    Trajectory follow_path_;
    VehicleStatus cur_status_;
    VehicleChassis cur_chassis_;
    double target_velocity_;
    std::unique_ptr<Filter::DigitalFilter> steeringcmd_losspass_filter_ = std::make_unique<Filter::DigitalFilter>();
    std::unique_ptr<Filter::MeanFilter> steeringcmd_mean_filter_ = std::make_unique<Filter::MeanFilter>(4);


    Filter::MeanFilter lateral_error_filter_;
    Filter::MeanFilter lateralRate_error_filter_;
    Filter::MeanFilter heading_error_filter_;
    Filter::MeanFilter headingRate_error_filter_;
    Filter::MeanFilter curvature_filter_;
    Filter::MeanFilter direction_filter_;

    
    virtual bool FollowMethod(ControlCommand &cur_cmd) = 0;
    virtual size_t QueryNearestPoseFromXY(const Trajectory &path, const Pose &pose) const;//其中找到最近点后会提前break，对于有交叉或掉头的路可能存在问题

    double calcLateralError(const Pose &loca_pos, const Pose &nearest_pos) const;
    double VelocityError2Accelerate(double vel_error, double sim_dt) const;

    Controller(const std::string &vehicle_physical_config);

public:

    
    bool Follow(const smartcar_msgs::Location &cur_status,  std::mutex &status_mutex, 
                const geometry_msgs::PoseArray &follow_path,  std::mutex &path_mutex,
                const smartcar_msgs::VehicleChassis &cur_chassis, std::mutex &chassis_mutex,
                double target_velocity, ControlCommand &cur_cmd);
    virtual ~Controller() = default;

    
};


}//PathFollower

#endif  // PATHFOLLOWER_CONTROLLER_H_