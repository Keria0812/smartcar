/*
 * @Date: 2021-10-25 13:55:24
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-26 20:43:41
 * @FilePath: /miniEV_grad/src/gps_bridge/src/gps_bridge_node.cpp
 */
#include <ros/ros.h>
#include <can_msgs/Frame.h>
#include <iostream>
#include <stdint.h>
#include <thread>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <string>
#include <time.h>
#include <string.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/NavSatStatus.h>
#include <sensor_msgs/NavSatFix.h>
#include <gps_common/conversions.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <smartcar_msgs/Location.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include "gps_bridge/proj4.h"
// #define MAXLINE 109
// #define bzero(ptr,n) memset(ptr, 0, n)
#include "gps_bridge/filters/digital_filter.h"
#include "gps_bridge/filters/digital_filter_coefficients.h"
#include "gps_bridge/filters/mean_filter.h"
Location::proj LL_gaus;

inline double NormalizeAngle(double theta)
{
  //限制在-pi~pi
  auto n = (int)(theta / (2 * M_PI));
  theta -= n * (2 * M_PI);
  if (theta >= M_PI)
  {
    theta -= 2 * M_PI;
  }
  if (theta < -M_PI)
  {
    theta += 2 * M_PI;
  }
  return theta;
}

inline int32_t int20_t2int32_t(int32_t temp_si20) {
    if (temp_si20 & (1 << 19)) {
        temp_si20 = ~(temp_si20 | 0xfff00000);
        temp_si20 = -temp_si20;
    }
    return temp_si20;
}

enum DAOYUAN
{
    INS_Acc = 0x500,
    INS_GYRO = 0x501,
    INS_HeadingPitchRoll = 0x502,
    INS_HeightAndTime = 0x503,
    INS_LatitudeLongitude = 0x504,
    INS_Speed = 0x505,
    INS_DataInfo = 0x506,
    INS_Std = 0x507,
    INS_UTC = 0x508,
    GPS_LatitudeLongitude = 0x509,
    GPS_HeightAndWeek = 0x50A,
    GPS_HeadingAndPitch = 0x50C,
    GPS_DOP = 0x50B
};

bool b_endFrame = false;

//imu data
float acc_x = 0, acc_y = 0, acc_z = 0;
float gyro_x = 0, gyro_y = 0, gyro_z = 0;

//ins data
float ins_pitch = 0, ins_roll = 0, ins_yaw = 0;
float ins_altitude = 0, ins_time = 0;
double ins_latitude = 0, ins_longtitude = 0;
float ins_northspd = 0, ins_eastspd = 0, ins_togroundspd = 0;

//ins data info
int ins_gpsflag_pos = 0, ins_numsv = 0, ins_gpsflag_heading = 0, ins_gps_age = 0, ins_car_status = 0, ins_status = 0;

//ins std
float ins_std_lat = 0, ins_std_lon = 0, ins_std_alt = 0, ins_std_heading = 0;

//ins utc
int8_t utc_year = 0, utc_month = 0, utc_day = 0, utc_hour = 0, utc_min = 0, utc_sec = 0;
int16_t utc_msec = 0;
int32_t utc_nsec = 0;

//gps data
float gps_latitude = 0, gps_longtitude = 0, gps_altitude = 0, gps_week = 0;
float gps_heading = 0, gps_pitch = 0;
float gps_gdop = 0, gps_pdop = 0, gps_hdop = 0, gps_htdop = 0;
geometry_msgs::PoseStamped curpos;
double VelE = 0, VelN = 0, VelU = 0, Vel = 0;

double AccelX = 0, AccelY = 0, AccelZ = 0;

double AngRateX = 0, AngRateY = 0, AngRateZ = 0;

Filter::MeanFilter speed_mean_filter_(25);
Filter::MeanFilter accx_mean_filter_(25);
Filter::MeanFilter accy_mean_filter_(25);

// Filter::MeanFilter heading_error_filter_;

    
// std::vector<double> den(3, 0.0);
// std::vector<double> num(3, 0.0);
// Filter::LpfCoefficients(0.01, 10, &den, &num);
// // std::vector<double> den(2, 0.0);
// // std::vector<double> num(2, 0.0);
// // Filter::LpfCoefficients(0.02, 5, &den, &num);

// Filter::DigitalFilter speed_losspass_filter_(den, num);
//publish sensor_msgs/NavSat{Fix,Status}
void NavSat_send(const ros::Publisher &pub, const ros::Publisher &pub2, const ros::Publisher &pub3)
{
    geometry_msgs::PoseStamped curpose;
    double easting, northing;
    // ins_yaw = speed_mean_filter_.Update(NormalizeAngle(ins_yaw));

    // ros 的库
    // std::string zone;
    // gps_common::LLtoUTM(ins_latitude, ins_longtitude, northing, easting, zone);
    AccelY = -AccelY;
    AccelY = accx_mean_filter_.Update(AccelY);
    AccelX = accy_mean_filter_.Update(AccelX);
    //proj4
    char sour_EPSG[] = "EPSG:4326";
    char des_EPSG[] = "EPSG:4526";

    LL_gaus.LLtoGaus(sour_EPSG, des_EPSG, ins_longtitude, ins_latitude, easting, northing);
// 38517414.982	3374902.242	2.865
    curpose.header.frame_id = "map";
    // 38509621.442	3368305.271	-0.411
    // curpose.pose.position.x = easting - 38517414.982 ;
    // curpose.pose.position.y = northing - 3374902.242	;
        easting = easting - 38509621.442 ;
    northing = northing - 3368305.271	;
    curpose.pose.position.x = easting  ;
    curpose.pose.position.y = northing ;
    // 38509688.485	3368283.269
    curpose.pose.position.z = ins_altitude;

    geometry_msgs::Quaternion quat;
    // quat = tf::createQuaternionMsgFromYaw(NormalizeAngle(ins_yaw / 180.0 * M_PI));
    quat = tf::createQuaternionMsgFromYaw(NormalizeAngle(ins_yaw / 180.0 * M_PI));

    curpose.pose.orientation = quat;
            ROS_INFO("2222222222222  %f\n", ins_yaw);
    // tf::Quaternion quat123;
    // tf::quaternionMsgToTF(curpose.pose.orientation, quat123);
    // double a,b,c;
    //     // std::cout << curpos.pose.orientation.x << " " << curpos.pose.orientation.y  << " " << curpos.pose.orientation.z<< " " << curpos.pose.orientation.w<< " " << std::endl;
    // tf::Matrix3x3(quat123).getRPY(a, b, c);//进行转换
    //     std::cout << a << " " << b  << " " << c << " " << curpose.pose.orientation.w<< " " << std::endl;

    // if (quat.w < 0.000000000000001 && quat.x < 0.000000000000001 && quat.y < 0.000000000000001 && quat.z < 0.000000000000001) {
    //     ROS_INFO("2222222222222  %f\n", ins_yaw);
    // }
    std::string location_status;
    switch (ins_gpsflag_pos)
    {
    case 0:
        location_status = "STATUS_NO_FIX"; //无解
        break;
    case 2:
        location_status = "STATUS_FIX"; //固定解
        break;
    default:
        break;
    }
    pub.publish(curpose);


    nav_msgs::Odometry real_location;
    real_location.header.stamp = ros::Time::now();

    real_location.pose.pose.position.x = curpose.pose.position.x;
    real_location.pose.pose.position.y = curpose.pose.position.y;
    real_location.pose.pose.position.z = curpose.pose.position.z;

    real_location.pose.pose.orientation = curpose.pose.orientation;
    real_location.twist.twist.linear.x = VelE;
    real_location.twist.twist.linear.y = VelN;
    // real_location.twist.twist.angular.z= AngRateZ / 57.3;
    // real_location.twist.twist.angular.z= AngRateZ / 57.3;
    real_location.twist.twist.angular.z= AngRateZ / 57.3;
    real_location.pose.pose.position.z = std::sqrt(AccelX*AccelX+AccelY*AccelY); //acceleration
    pub3.publish(real_location);
    // real_location.
      //给plan的定位
//   nav_msgs::Odometry odometry_;
//   odometry_.header.stamp = ros::Time::now();
//   odometry_.pose.pose.position.x = gcarstatus.utm_x;
//   odometry_.pose.pose.position.y = gcarstatus.utm_y;
//   odometry_.pose.pose.position.z = gcarstatus.utm_z;

//   geometry_msgs::Quaternion quat_tmp;
//   quat_tmp = tf::createQuaternionMsgFromRollPitchYaw(0.0, 0.0, NormalizeAngle(gcarstatus.yaw));
//   odometry_.pose.pose.orientation = quat_tmp;

//   odometry_.twist.twist.linear.x = gcarstatus.v_x;
//   odometry_.twist.twist.linear.y = gcarstatus.v_y;
//   odometry_.twist.twist.linear.z = gcarstatus.v_z;
  
//   odometry_.twist.twist.angular.x = gcarstatus.rate_roll;
//   odometry_.twist.twist.angular.y = gcarstatus.rate_pitch;
//   odometry_.twist.twist.angular.z = gcarstatus.rate_yaw;
  // pub_Location2->publish(odometry_);
    smartcar_msgs::Location g_location;
    g_location.header.stamp = ros::Time::now();
    g_location.ins_time[1] = 0;
    g_location.global_pos.x = easting;
    g_location.global_pos.y = northing;
    g_location.global_pos.z = ins_altitude;
    g_location.wgs84_pos[0] = ins_longtitude;
    g_location.wgs84_pos[1] = ins_latitude;
    g_location.wgs84_pos[2] = ins_latitude;
    g_location.orientation[0] = ins_roll;
    g_location.orientation[1] = NormalizeAngle(ins_pitch/57.3);
    g_location.orientation[2] = NormalizeAngle(ins_yaw/57.3);
            ROS_INFO("2222222222222  %f\n", g_location.orientation[2] * 57.3);

    g_location.global_speed[0] = VelE;
    g_location.global_speed[1] = VelN;
    g_location.global_speed[2] = VelU;
    g_location.accelerate[0] = 0.0;
    g_location.accelerate[1] = 0.0;
    g_location.accelerate[2] = 0.0;
    g_location.rpy_rate[0] =AngRateX;
    g_location.rpy_rate[1] = AngRateY;
    g_location.rpy_rate[2] =AngRateZ;

    g_location.speed = Vel;
    g_location.v_x = VelE;
    g_location.v_y = VelN;
    g_location.v_z = VelU;
    g_location.accel_x = AccelY ;
    g_location.accel_y = AccelX ;
    g_location.accel_z = AccelZ ;

    g_location.INS_status = "RTK-Fix";
    // std::cout<<"curlocation.orientation[2]"<<curlocation.orientation[2]<<std::endl;
    pub2.publish(g_location);
    // ROS_INFO("lon:    %.7lf       lat:    %.7lf    %s", ins_longtitude, ins_latitude, location_status.c_str());
    // ROS_INFO("UTM X:    %.3lf   UTM Y:  %.3lf   %d%s", easting, northing, ins_gpsflag_pos, location_status.c_str());
}

// void NavSatTCP_recv()
// {
//     int sockfd, n;

//     if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
//     {
//         printf("socket error\n");
//         exit(2);
//     }

//     struct sockaddr_in servaddr;
//     memset(&servaddr, 0, sizeof(servaddr));
//     servaddr.sin_family = AF_INET;
//     servaddr.sin_addr.s_addr = inet_addr("192.168.2.233");
//     servaddr.sin_port = htons(8887); /*访问服务器的8887号端口*/

//     std::cout << "start connect" << std::endl;
//     if ((n = connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
//     {
//         printf("connect error\n");
//         exit(1);
//     }
//     int MAXSIZE = 109;
//     char recvbuf[MAXSIZE] = "";
//     while (ros::ok())
//     {
//         n = recv(sockfd, recvbuf, MAXSIZE, 0);
//         if (n < 0)
//         {
//             printf("read error\n");
//             continue;
//         }
//         if ((n == 109) && (recvbuf[0] == 0xAA) && (recvbuf[1] == 0x55))
//         {
//             int pos_status = *((uint32_t *)(recvbuf + 20)); //2- 固定解
//             double lontitude = *((double *)(recvbuf + 28));
//             double latitude = *((double *)(recvbuf + 36));
//             double heading = *((float *)(recvbuf + 92));
//             std::cout <<"pos_status" << pos_status <<"\t"
//                       << std::fixed << std::setprecision(7)
//                       << "lontitude: " << lontitude << "\t"
//                       << "latitude: " << latitude << "\t"
//                       << std::fixed << std::setprecision(3) << "heading" << heading << std::endl;
//             ins_longtitude = lontitude;
//             ins_latitude = latitude;
//             ins_yaw = heading;
//             ins_gpsflag_pos = pos_status;

//         }
//         memset(recvbuf, 0, 109);
//     }
//     printf("finally n=%d", n);
//     if (n < 0)
//         printf("read error");
//     exit(0);
// }

// void LocationFrameCallBack(const can_msgs::Frame::ConstPtr &msg)
// {
//     // TODO: 解析状态
//     switch (msg->id)
//     {
//     case INS_Acc:
//         acc_x = (((u_int16_t)(msg->data[0]) << 8) + msg->data[1]) * 0.0001220703125 - 4;
//         acc_y = (((u_int16_t)(msg->data[2]) << 8) + msg->data[3]) * 0.0001220703125 - 4;
//         acc_z = (((u_int16_t)(msg->data[4]) << 8) + msg->data[5]) * 0.0001220703125 - 4;
//         break;
//     case INS_GYRO:
//         gyro_x = (((u_int16_t)(msg->data[0]) << 8) + msg->data[1]) * 0.0076293 - 250;
//         gyro_y = (((u_int16_t)(msg->data[2]) << 8) + msg->data[3]) * 0.0076293 - 250;
//         gyro_z = (((u_int16_t)(msg->data[4]) << 8) + msg->data[5]) * 0.0076293 - 250;
//         break;
//     case INS_HeadingPitchRoll:
//         ins_pitch = (((u_int16_t)(msg->data[0]) << 8) + msg->data[1]) * 0.010986 - 360;
//         ins_roll = (((u_int16_t)(msg->data[2]) << 8) + msg->data[3]) * 0.010986 - 360;
//         ins_yaw = (((u_int16_t)(msg->data[4]) << 8) + msg->data[5]) * 0.010986 - 360;
//         if (ins_yaw < 0)
//         {
//             ins_yaw += 360.0;
//         }
//         break;
//     case INS_HeightAndTime:
//         ins_altitude = (((u_int32_t)(msg->data[0]) << 24) + ((u_int32_t)(msg->data[1]) << 16) + ((u_int32_t)(msg->data[2]) << 8) + msg->data[3]) * 0.001 - 10000;
//         ins_time = (((u_int32_t)(msg->data[4]) << 24) + ((u_int32_t)(msg->data[5]) << 16) + ((u_int32_t)(msg->data[6]) << 8) + msg->data[7]);
//         break;
//     case INS_LatitudeLongitude:
//         ins_latitude = (((u_int32_t)(msg->data[0]) << 24) | ((u_int32_t)(msg->data[1]) << 16) | ((u_int32_t)(msg->data[2]) << 8) | msg->data[3]) * 1E-7 - 180;
//         ins_longtitude = (((u_int32_t)(msg->data[4]) << 24) | ((u_int32_t)(msg->data[5]) << 16) | ((u_int32_t)(msg->data[6]) << 8) | msg->data[7]) * 1E-7 - 180;
//         // ROS_INFO("ins_latitude%lf", ins_latitude);
//         break;
//     case INS_Speed:
//         ins_northspd = (((u_int16_t)(msg->data[0]) << 8) + msg->data[1]) * 0.0030517 - 100;
//         ins_eastspd = (((u_int16_t)(msg->data[2]) << 8) + msg->data[3]) * 0.0030517 - 100;
//         ins_togroundspd = (((u_int16_t)(msg->data[4]) << 8) + msg->data[5]) * 0.0030517 - 100;
//         break;
//     case INS_DataInfo:
//         ins_gpsflag_pos = msg->data[0];
//         ins_numsv = msg->data[1];
//         ins_gpsflag_heading = msg->data[2];
//         ins_gps_age = msg->data[3];
//         ins_car_status = msg->data[4];
//         ins_status = msg->data[7];
//         break;
//     case INS_Std:
//         ins_std_alt = (((u_int16_t)(msg->data[0]) << 8) + msg->data[1]) * 0.01;
//         ins_std_lon = (((u_int16_t)(msg->data[2]) << 8) + msg->data[3]) * 0.01;
//         ins_std_alt = (((u_int16_t)(msg->data[4]) << 8) + msg->data[5]) * 0.01;
//         ins_std_alt = (((u_int16_t)(msg->data[6]) << 8) + msg->data[7]) * 0.01;
//         b_endFrame = true;
//         break;
//     case INS_UTC:
//         // d_week   = (((u_int32_t)(msg->msg[4]) << 24) | ((u_int32_t)(msg->msg[5]) << 16) | ((u_int32_t)(msg->msg[6]) << 8) | msg->msg[7]);
//         utc_year = msg->data[0];
//         utc_month = msg->data[1];
//         utc_day = msg->data[2];
//         utc_hour = msg->data[3];
//         utc_min = msg->data[4];
//         utc_sec = msg->data[5];
//         utc_msec = (msg->data[6] << 8) + msg->data[7];
//         utc_nsec = utc_msec * (10 ^ 6);
//         break;
//     case GPS_LatitudeLongitude:
//         gps_latitude = (((u_int32_t)(msg->data[0]) << 24) | ((u_int32_t)(msg->data[1]) << 16) | ((u_int32_t)(msg->data[2]) << 8) | msg->data[3]) * 1E-7 - 180;
//         gps_longtitude = (((u_int32_t)(msg->data[4]) << 24) | ((u_int32_t)(msg->data[5]) << 16) | ((u_int32_t)(msg->data[6]) << 8) | msg->data[7]) * 1E-7 - 180;
//         break;
//     case GPS_HeightAndWeek:
//         gps_altitude = (((u_int32_t)(msg->data[0]) << 24) | ((u_int32_t)(msg->data[1]) << 16) | ((u_int32_t)(msg->data[2]) << 8) | msg->data[3]) * 0.001 - 10000;
//         gps_week = (((u_int32_t)(msg->data[4]) << 24) | ((u_int32_t)(msg->data[5]) << 16) | ((u_int32_t)(msg->data[6]) << 8) | msg->data[7]) * 1;
//         break;
//     case GPS_HeadingAndPitch:
//         gps_heading = (((u_int32_t)(msg->data[0]) << 24) | ((u_int32_t)(msg->data[1]) << 16) | ((u_int32_t)(msg->data[2]) << 8) | msg->data[3]) * 0.010986 - 360;
//         gps_pitch = (((u_int32_t)(msg->data[4]) << 24) | ((u_int32_t)(msg->data[5]) << 16) | ((u_int32_t)(msg->data[6]) << 8) | msg->data[7]) * 0.010986 - 360;
//         break;
//     case GPS_DOP:
//         gps_gdop = (((u_int16_t)(msg->data[0]) << 8) + msg->data[1]) * 0.01;
//         gps_pdop = (((u_int16_t)(msg->data[2]) << 8) + msg->data[3]) * 0.01;
//         gps_hdop = (((u_int16_t)(msg->data[4]) << 8) + msg->data[5]) * 0.01;
//         gps_htdop = (((u_int16_t)(msg->data[6]) << 8) + msg->data[7]) * 0.01;
//         break;
//     default:
//         break;
//     }
// }

void LocationFrameCallBack(const can_msgs::Frame::ConstPtr &msg)
{
    
    double easting, northing;
    // std::cout << "get location" << std::endl;
    // ROS_INFO("get location  %.7lf       lat:    %.7lf    ", ins_longtitude, ins_latitude);

    //proj4
    char sour_EPSG[] = "EPSG:4326";
    char des_EPSG[] = "EPSG:4526";

    // printf("msgid: %04x [",msg->id);
    // for(int i = 0;i<8;i++)
    // {
    //     printf("%02x ",msg->data[i]);
    // }
    // printf("]\n");

    curpos.header.frame_id = "map";

    // TODO: 解析状态
    switch (msg->id)
    {
    case 0x320://Time
    {
        // ins_status = 
        // break;
    }
    case 0x323://Time
    {
        //INS结算状态
        uint16_t INS_state =  (int16_t)(msg->data[0]);

        //INS_RTK解算状态
        uint16_t RTK_state = (int16_t)(msg->data[2]);
        // if (INS_state != 3) {
        //     ROS_WARN("The INS state is %d \n", INS_state);
        // } else 
        // ROS_INFO ("The INS state is OK %d\n", INS_state);

        // ROS_WARN("The RTK state is %d \n", RTK_state);
        // // switch (INS_state)
        // {
        // case /* constant-expression */:
        //     /* code */
        //     break;
        
        // default:
        //     break;
        // }
        break;
    }
    case 0x327://enu velocity
    {
        //VelE ([-327.68,327.67] m/s)
        VelE = (int16_t)(((u_int16_t)(msg->data[0]) << 8) + msg->data[1]) * 0.01;
        
        //VelN ([-327.68,327.67] m/s)
        VelN = (int16_t)(((u_int16_t)(msg->data[2]) << 8) + msg->data[3]) * 0.01;
        VelU = (int16_t)(((u_int16_t)(msg->data[4]) << 8) + msg->data[5]) * 0.01;
        Vel = (int16_t)(((u_int16_t)(msg->data[6]) << 8) + msg->data[7]) * 0.01;
        // std::cout << "Velocity of E,N: " << VelE << ", " << VelN << ". " <<", " << VelU <<", " << Vel << std::endl;
        break;
    }
    case 0x329://xyz acceleration
    {
        //AccelX ([-8,8] g)
        // int32_t temp_si32 = (int32_t)((((u_int32_t)(msg->data[0]) << 12) | ((u_int32_t)(msg->data[1]) << 4)) | ((u_int32_t)(msg->data[2])&0xf));
        // int32_t temp_si32 = (int32_t)(((u_int32_t)(msg->data[0]) << 12) | ((u_int32_t)(msg->data[1]) << 4) | ((u_int32_t)(msg->data[2])&0xf));

        int32_t temp_si20 = (int32_t)(((u_int32_t)(msg->data[0]) << 12) | ((u_int32_t)(msg->data[1]) << 4) | ((u_int32_t)(msg->data[2])) >> 4);
        temp_si20 = int20_t2int32_t(temp_si20);
        AccelX = 0.0001*temp_si20;
        //AccelY ([-8,8] g)
        // temp_si32 = (int32_t)(((u_int32_t)((msg->data[2]) & 0xf) << 16  | ((u_int32_t)(msg->data[3]) << 4) | (u_int32_t)msg->data[4] << 12));
        temp_si20 = (((int32_t)((msg->data[2])&0x0f) << 16) | ((u_int32_t)(msg->data[3]) << 8) | (u_int32_t)msg->data[4]);
        temp_si20 = int20_t2int32_t(temp_si20);
        AccelY = 0.0001*temp_si20;
        //AccelZ ([-8,8] g)
        temp_si20 = (int32_t)(((u_int32_t)(msg->data[5]) << 12) | ((u_int32_t)(msg->data[6]) << 4) | ((u_int32_t)msg->data[7] >> 4));
        temp_si20 = int20_t2int32_t(temp_si20);
        AccelZ = 0.0001*temp_si20;

        // u_int32_t temp_si32 =( (u_int32_t)(((u_int32_t)(msg->data[0]) << 12) | ((u_int32_t)(msg->data[1]) << 4) | ((u_int32_t)(msg->data[2])) >> 4) ) & 0xFFFFF;
        // // std::cout << temp_si32 << std::endl;
        // // if (temp_si32 < 80000.0 && temp_si32 > -80000.0)
        // AccelX = 0.00001*temp_si32 - 8.0;
        // //AccelY ([-8,8] g)
        // // temp_si32 = (int32_t)(((u_int32_t)((msg->data[2]) & 0xf) << 16  | ((u_int32_t)(msg->data[3]) << 4) | (u_int32_t)msg->data[4] << 12));
        // u_int32_t temp_si32Y = (((u_int32_t)((msg->data[2])&0x0f) << 16) | ((u_int32_t)(msg->data[3]) << 8) | (u_int32_t)msg->data[4]) & 0xFFFFF ;
    
        // // if (temp_si32 < 80000.0 && temp_si32 > -80000.0)

        // AccelY = 0.00001*temp_si32Y - 8.0;
        // //AccelZ ([-8,8] g)
        // u_int32_t temp_si32Z = (u_int32_t)(((u_int32_t)(msg->data[5]) << 12) | ((u_int32_t)(msg->data[6]) << 4) | ((u_int32_t)msg->data[7] >> 4)) & 0xFFFFF;
   
        // // if (temp_si32 < 80000.0 && temp_si32 > -80000.0)

        // AccelZ = 0.00001*temp_si32Z - 8.0;

        std::cout << "Accel of x,y,z(g): " << AccelX << ", " << AccelY << ", " << AccelZ << std::endl;
        // printf("\n");
        // for (int i = 0; i < 8; i++) {
        //     printf("%x \n", msg->data[i]);
        // }
        // printf("\n");

        break;
    }
    case 0x32C: //AngRate deg/s
    {
        int32_t temp_si20 = (int32_t)(((u_int32_t)(msg->data[0]) << 12) | ((u_int32_t)(msg->data[1]) << 4) | ((u_int32_t)msg->data[2] >> 4));
        temp_si20 = int20_t2int32_t(temp_si20);
        AngRateX = 0.01*temp_si20;

        temp_si20 = (int32_t)(((u_int32_t)((msg->data[2])&0x0f) << 16) + ((u_int32_t)(msg->data[3]) << 8) + (u_int32_t)msg->data[4]);
        temp_si20 = int20_t2int32_t(temp_si20);
        AngRateY = 0.01*temp_si20;

        temp_si20 = (int32_t)(((u_int32_t)(msg->data[5]) << 12) + ((u_int32_t)(msg->data[6]) << 4) + ((u_int32_t)msg->data[7] >> 4));
        temp_si20 = int20_t2int32_t(temp_si20);
        AngRateZ = 0.01*temp_si20;

        // std::cout << "AngRate of x,y,z(degree): " << AngRateX << ", " << AngRateY << ", " << AngRateZ << "." << std::endl;
        break;
    }
    case 0x32A:
    {
        //heading (0~360 degree)
        ins_yaw = (((u_int16_t)(msg->data[0]) << 8) + msg->data[1]) * 0.01;
        //pitch (-90~90 degree)
        ins_pitch = (((u_int16_t)(msg->data[2]) << 8) + msg->data[3]) * 0.01;
        //roll (-180~180 degree)
        ins_roll = (((u_int16_t)(msg->data[4]) << 8) + msg->data[5]) * 0.01;

        // printf("ins_yaw:%lf\n",ins_yaw);
        // curpos.pose.orientation.z = 90 - ins_yaw;
        ins_yaw = 90.0 - ins_yaw;
        // geometry_msgs::Quaternion quat;
        // quat = tf::createQuaternionMsgFromYaw(NormalizeAngle(ins_yaw/57.3));
        // curpos.pose.orientation = quat;

        break;
    }
    case 0x32B://rpysimga
    {

        break;
    }
    case 0x324:
    {
            // double start, finish;
    // //clock_t为CPU时钟计时单元数
    // start = clock_ms();
        clock_t start, finish;
        //clock_t为CPU时钟计时单元数
        start = clock();
        ins_latitude = (((u_int32_t)(msg->data[0]) << 24) | ((u_int32_t)(msg->data[1]) << 16) | ((u_int32_t)(msg->data[2]) << 8) | msg->data[3]) * 1E-7;

        ins_longtitude= (((u_int32_t)(msg->data[4]) << 24) | ((u_int32_t)(msg->data[5]) << 16) | ((u_int32_t)(msg->data[6]) << 8) | msg->data[7]) * 1E-7;

        // ROS_INFO("ins_latitude: %lf, ins_longtitude: %lf\n", ins_latitude,ins_longtitude);
        // LL_gaus.LLtoGaus(sour_EPSG, des_EPSG, ins_longtitude, ins_latitude, easting, northing);
        // ROS_INFO("easting: %lf, northing: %lf\n", easting,northing);
        // std::cout << " 222222222222222222222 " << std::endl;
        ROS_INFO("long: %lf, lat: %lf\n", ins_longtitude,ins_latitude);

        // curpos.pose.position.x = easting;
        // curpos.pose.position.y = northing;
        b_endFrame = true;
        finish = clock();
    //clock()函数返回此时CPU时钟计时单元数
        // std::cout<<"the time cost is:" << double(finish - start) / CLOCKS_PER_SEC * 1000<<std::endl;
        // finish = clock_ms();
    // ROS_INFO("The Proj cost time is %.10lf",(double)finish -(double)start );
        break;
    }
    // case 814:
    // {    
    //     ins_latitude = (((u_int64_t)(msg->data[0]) << 56) | ((u_int64_t)(msg->data[1]) << 48) | 
    //     ((u_int64_t)(msg->data[2]) << 40)| ((u_int64_t)(msg->data[3]) << 32)| 
    //     ((u_int64_t)(msg->data[4]) << 24)| ((u_int64_t)(msg->data[5]) << 16)| 
    //     ((u_int64_t)(msg->data[6]) << 8)| ((u_int64_t)(msg->data[7]))) * 1E-8;

    //     // ins_longtitude= (((u_int32_t)(msg->data[4]) << 24) | ((u_int32_t)(msg->data[5]) << 16) | ((u_int32_t)(msg->data[6]) << 8) | msg->data[7]) * 1E-7;

    //     // //printf("ins_latitude: %lf, ins_longtitude: %lf\n", ins_latitude,ins_longtitude);
    //     // LL_gaus.LLtoGaus(sour_EPSG, des_EPSG, ins_longtitude, ins_latitude, easting, northing);
    //     // //printf("easting: %lf, northing: %lf\n", easting,northing);
    //     // curpos.pose.position.x = easting;
    //     // curpos.pose.position.y = northing;
    //     // b_endFrame = true;
    //     break;
    // }
    // case 813:
    // {    
    //     ins_longtitude = (((u_int64_t)(msg->data[0]) << 56) | ((u_int64_t)(msg->data[1]) << 48) | 
    //     ((u_int64_t)(msg->data[2]) << 40)| ((u_int64_t)(msg->data[3]) << 32)| 
    //     ((u_int64_t)(msg->data[4]) << 24)| ((u_int64_t)(msg->data[5]) << 16)| 
    //     ((u_int64_t)(msg->data[6]) << 8)| ((u_int64_t)(msg->data[7]))) * 1E-8;

    //     // printf("ins_latitude: %lf, ins_longtitude: %lf\n", ins_latitude,ins_longtitude);
        
    //     break;
    // }
    default:
        break;
    }

    // LL_gaus.LLtoGaus(sour_EPSG, des_EPSG, ins_longtitude, ins_latitude, easting, northing);
    // //printf("easting: %lf, northing: %lf\n", easting,northing);
    // curpos.pose.position.x = easting;
    // curpos.pose.position.y = northing;
    // b_endFrame = true;
    
}

void mainback(ros::NodeHandle nh)
{
    // while (ros::ok())
    {
        ros::Subscriber sub_Frame_data = nh.subscribe<can_msgs::Frame>("/can1_received_messages", 1, &LocationFrameCallBack);
        ros::MultiThreadedSpinner spinner(1);
        spinner.spin();
    }
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "gps_bridge");
    ros::NodeHandle nh;
    std::thread t(mainback, nh);
    // std::thread t(NavSatTCP_recv);

    ros::Publisher pub = nh.advertise<geometry_msgs::PoseStamped>("/current_pose", 10);
    ros::Publisher pub_location = nh.advertise<smartcar_msgs::Location>("smartcar/location", 10);
    ros::Publisher pub_nav = nh.advertise<nav_msgs::Odometry>("base_pose_ground_truth", 10);

    ros::Rate loop_rate(500);


    while (ros::ok())
    {
        if (b_endFrame)
        {
            auto start_control = std::chrono::high_resolution_clock::now();
            NavSat_send(pub, pub_location, pub_nav);
             auto end_control = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> cost_time = end_control - start_control;
            std::cout << "The ControlMethod cost time is: " << cost_time.count() << " ms" << std::endl;
            b_endFrame = false;
        }

        loop_rate.sleep();

    }

    t.join();
    return 0;
}