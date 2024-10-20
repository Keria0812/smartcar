#ifndef _SIM_INFO_H
#define _SIM_INFO_H

#include <cstdint>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>

// namespace Sim {

struct object_info {
    uint8_t ID;
    uint8_t Type;
    double Time_frame;
    double x;   //sensor frame x-forward y-left, z-up
    double y;
    double z;
    double heading;
    double length;
    double width;
    double height;
    double speed;
};

struct CarStatus
{
    /* data */
    double Time;    //s
    double steering_ang ;      /* rad */
    double steer_vel;   // rad/s
    double speed ;        /* m/s */
    int gear ;
    double acceleration_x ;      /* m/s^2, utm坐标系 */
    double acceleration_y ;       
    double acceleration_z ;
    
    double FL_speed ;         /* 左前轮，m/s */
    double FR_speed ;
    double RL_speed ;
    double RR_speed ;
    double latitude ;    //rad
    double longitude;   //rad
    double height ;     //m
    double utm_x ;      //m
    double utm_y ;
    double utm_z ;
    double roll ;     //rad
    double rate_roll ;     //rad/s
    double pitch ;       //rad
    double rate_pitch ;      //rad/s
    double yaw ;       //rad
    double rate_yaw ;      //rad/s
    double accel_x ;         //base_link坐标系
    double accel_y ;
    double accel_z ;
    double v_x ;             //base_link坐标系
    double v_y ;
    double v_z ;
    double east_speed ;             //地图坐标系
    double north_speed ;
    double up_speed ;
    struct object_info object_info_[64];
    
    double feedback_gas_pedal;
    double feedback_brake_pedal;
    double feedback_torque;
};

struct VehicleCMD
{
    /* data */
    double steeringAng;
    double acceleration;
    double gas;
    double brake;
    int drivemode; //0 人工；1 自动 2 ipgdrive
    int gear;
};

struct manulCMD
{
    /* data */
    double steeringAng;
    double gas;
    double brake;
    int gear;
};

struct autoCMD
{
  /* data */
    double steeringAng;
    double acceleration;
    int gear;
};

struct Rect_point{
    cv::Point2d A;  //左下，逆时针方向
    cv::Point2d B;
    cv::Point2d C;
    cv::Point2d D;
    cv::Point2d center;
    float radius;
};

// }  // namespace Sim

#endif  // _SIM_INFO_H
