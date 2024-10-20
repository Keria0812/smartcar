#include "ros/ros.h"
#include <fstream>
#include <string.h>
#include <cmath>
#include <iostream>

#include <algorithm>

#include <iomanip>

#include <utility>
#include <vector>


#include <thread>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>
#include <eigen3/Eigen/Core>
#include <limits>

#include <deque>

/***********添加***************/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
float my_gas = 0;
float my_brake = 0;
/***********添加***************/


#include <pthread.h>

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include <signal.h>


// #include <iau_ros_msgs/VehicleStatus.h>
#include <smartcar_msgs/VehicleStatus.h>
// #include <iau_ros_msgs/Location.h>
#include <smartcar_msgs/VehicleLocation.h>
// #include <iau_ros_msgs/Follow.h>
// #include <iau_ros_msgs/PointXYA.h>
// #include <iau_ros_msgs/VehicleCMD.h>
#include <smartcar_msgs/VehicleCmd.h>
#include <smartcar_msgs/ControlCommandStamped.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <mutex>
#include <simulator/sim_info.hpp>
#include <simulator/grid_publisher.h>
#include <nav_msgs/Odometry.h>
#include <smartcar_msgs/Location.h>
#include <simulator/common.h>
#include <smartcar_msgs/VehicleChassis.h>
#include <std_msgs/Float32.h>
#include <simulator/pid.h>
std::string des_ip = "";
std::string sou_ip = "";

std::mutex carmaker;

#define DEBUG_FLAG (1)
bool recvStatusFlag = false;
bool recvCMDFlag = false;
int drivemodeFlag = 1;
using namespace Eigen;

double laststeerangcmd = 0;

ros::Publisher *pub_VehicleStatus;
ros::Publisher *pub_Location;
ros::Publisher *pub_Location2;
ros::Publisher *pub_Location3;
ros::Publisher *pub_Imu;
ros::Publisher *pub_joy;
ros::Publisher *pub_currentspeed;
ros::Publisher *pub_chassis;
ros::Publisher *pub_steer_vel;
ros::Publisher *pub_rviz_speed;
ITS::Grid *process_grid;

struct CarStatus gcarstatus;
struct VehicleCMD gcmd = {0, 0, 0, 0, 1};
struct manulCMD mcmd = {0, 0, 0};
struct autoCMD acmd = {0, 0};
int closestIndex = 0;

int MAX_V = 100;
int MAX_ACC = 120;

double targetVel = 0.0;

void udp2topic();
std::vector<std::vector<double>>* calibration_table_ = nullptr;


double PI = 3.1415926;
inline double NormalizeAngle(double theta)
{
  //限制在-pi~pi
  auto n = (int)(theta / (2 * PI));
  theta -= n * (2 * PI);
  if (theta >= PI)
  {
    theta -= 2 * PI;
  }
  if (theta < -PI)
  {
    theta += 2 * PI;
  }
  theta = std::min(theta, PI);
  theta = std::max(theta, -PI);

  return theta;
}

void udpsend()
{

  int fa = 0;
  fa = socket(AF_INET, SOCK_DGRAM, 0);
  if (fa < 0)
  {
    std::cout << "failed" << std::endl;
  }

  struct sockaddr_in server_addr, cliaddr;
  bzero(&server_addr, sizeof(server_addr)); //目的ip 和端口
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(des_ip.c_str());
  server_addr.sin_port = htons(8081);

  bzero(&cliaddr, sizeof(cliaddr)); //发送端ip和端口
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_addr.s_addr = inet_addr(sou_ip.c_str());
  cliaddr.sin_port = htons(9091);
  if (bind(fa, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) == -1)
  {
    std::cout << "bind fail!" << std::endl;
  }

  //人工0、自动1切换
  if (drivemodeFlag == 1)
  {
    gcmd.drivemode = 1;
  }
  else if (drivemodeFlag == 2)
  {
    gcmd.drivemode = 2;
  }
  else
  {
    gcmd.drivemode = 0;
  }

  if (gcmd.drivemode == 0)
  {
    gcmd.steeringAng = mcmd.steeringAng;
    gcmd.gas = mcmd.gas;
    gcmd.brake = mcmd.brake;
  }
  else if (gcmd.drivemode == 1)
  {
    gcmd.steeringAng = acmd.steeringAng;
    if (calibration_table_ == nullptr) {//全局指针，没变的时候发的加速度命令，变了就根据标定表发
      gcmd.acceleration = acmd.acceleration;

    } else {
      // std::cout<<acmd.acceleration<< " "<<gcarstatus.pitch<<std::endl;
      acmd.acceleration -= 0.65*9.8* std::sin(gcarstatus.pitch);//带坡度的实验要加这一句
      // std::cout<<acmd.acceleration<< " "<<gcarstatus.pitch<<std::endl;
      int V_I =  std::min((int)std::floor(fabs(gcarstatus.speed*3.6)), MAX_V-1);
      int A_I =  std::min((int)std::floor(fabs(acmd.acceleration + 3.5)/0.05), MAX_ACC-1);
      A_I = std::max((int)A_I, 0);

      printf("%ld %ld %ld\n", calibration_table_->size(), V_I, A_I);
      PID  longitudinalvelocitypid_ = PID(0.32,0.0,0.0, 0.02, -0.00, 0.02, -0.00);//发udp的函数

      double cur_driver = calibration_table_->at(V_I).at(A_I) ;
      gcmd.drivemode = 0;
      
      gcmd.gas = std::max(0.0, cur_driver + longitudinalvelocitypid_.Control(acmd.acceleration - gcarstatus.accel_x, 0.02));
      gcmd.brake = std::max(0.0, -cur_driver- + longitudinalvelocitypid_.Control(acmd.acceleration - gcarstatus.accel_x, 0.02));
      // if (gcmd.gas > 0.0) gcmd.gas += 0.02;
      // if (gcmd.brake > 0.0) gcmd.brake = 0.02;

      std::cout << "dasssssssssss "<< cur_driver << "  "  << acmd.acceleration<< " " <<gcmd.gas <<" " <<  gcmd.brake  <<std::endl;
    }
  }
  else if (gcmd.drivemode == 2)
  {
    gcmd.acceleration = 0;
    gcmd.brake = 0;
    gcmd.gas = 0;
    gcmd.steeringAng = 0;
  }

  int maxbuf = sizeof(gcmd);
  char buf[maxbuf];
  memset(buf, 0, maxbuf);
  memcpy(buf, &gcmd, sizeof(gcmd));
  sendto(fa, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
  // printf("send success\n");
  close(fa);
}

void udprecvstop()
{
  // if(100 %20 ==0){
  int fa = 0;
  fa = socket(AF_INET, SOCK_DGRAM, 0);
  if (fa < 0)
  {
    std::cout << "failed" << std::endl;
  }

  struct sockaddr_in server_addr, cliaddr;
  bzero(&server_addr, sizeof(server_addr)); //目的ip 和端口
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(sou_ip.c_str());
  server_addr.sin_port = htons(9090);

  // bzero(&cliaddr, sizeof(cliaddr)); //发送端ip和端口
  // cliaddr.sin_family = AF_INET;
  // cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  // cliaddr.sin_port = htons(9091);
  // if (bind(fa, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) == -1) {

  //     std::cout<<"bind fail!"<<std::endl;
  // }

  int maxbuf = 4;
  char buf[maxbuf];
  memset(buf, 0, maxbuf);
  // memcpy(buf, &gcmd, sizeof(gcmd));
  sendto(fa, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
  // printf("send success\n");
  close(fa);
  // }
}

/******************************************************************************/
void receiveUDPMessageLoop()
{

  // 1. 定义服务器ip地址和侦听端口，初始化要绑定的网络地址结构，例如：
  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));                //初始化结构体
  server_addr.sin_family = AF_INET;                        //地址类型为AF_INET
  server_addr.sin_port = htons(9090);                      //服务器端口
  server_addr.sin_addr.s_addr = inet_addr(sou_ip.c_str()); /// INADDR_ANY;  //本机IP地址

  // 2. 建立套接字文件描述符，使用socket()，
  int shou = 0;
  shou = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (shou < 0)
  {
    printf("create sock error\n");
    exit(-1);
  }

  // setnonblocking(shou);

  // 3. 绑定侦听端口，使用bind()函数，将套接字文件描述符和一个地址类型变量进行绑定
  int ret = bind(shou, (struct sockaddr *)&server_addr, sizeof(server_addr)); //绑定地址
  if (ret < 0)
  {
    printf("bind shou error\n");
    exit(-1);
  }
  else
  {
    printf("create udp success\n");
  }

  // 4.接收客户端的数据，使用recvfrom()函数接受客户端的网络数据。
  struct sockaddr_in client_addr;           //再创建一个地址类型变量存储收到的地址
  bzero(&client_addr, sizeof(client_addr)); //初始化结构体
  unsigned int len = sizeof(client_addr);   //在 linux 平台下，socklen_t 类型是 unsigned int 类型的别名
  while (ros::ok())
  {
    // if (1)
    // {
    // recved = false;

    int maxbuf = sizeof(gcarstatus);
    char buf[maxbuf];
    memset(buf, 0, maxbuf);
    int n = recvfrom(shou, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &len);
    // printf(" 接收数据长度: %d \n",n);
    if (n < maxbuf)
    {
      printf("接收数据长度: %d \n", n);
      printf("线程结束\n");
      break;
    }
    // printf("inno_data length = %ld\n",sizeof(inno_data));
    // memcpy(&inno_data,buf,sizeof(inno_data));
    // printf("receive msg from %s:%d len=%ld:\n",inet_ntoa(client_addr.sin_addr), client_addr.sin_port, sizeof(buf));
    // double curent_gas =0;
    // double curent_brake =0;
    {
      // std::lock_guard<std::mutex> lock(carmaker);
      memcpy(&gcarstatus, buf, sizeof(gcarstatus));
      // printf(" speed= %f\n",gcarstatus.speed);
      // my_gas = curent_gas;
      // my_brake = curent_brake;
      recvStatusFlag = true;
    }
    udp2topic();
  }
}

void VehicleCMDCallBack(const smartcar_msgs::ControlCommandStamped::ConstPtr &msg)
{

  acmd.steeringAng = msg->cmd.steering_angle;
  targetVel = msg->cmd.linear_velocity;
  // msg->cmd.linear_velocity = 27.7777777777778;
  ROS_INFO("speed =%f", gcarstatus.speed);
  // acmd.steeringAng = -msg->cmd.steering_angle * 3.1415926 /180;
  double g_t = 2;
  double g_A = 0;
  if (gcarstatus.speed > 1.0)
   g_A = (msg->cmd.linear_velocity - gcarstatus.speed) / g_t;
  else
   g_A = (msg->cmd.linear_velocity + gcarstatus.speed) / g_t;

  // double g_A = ( 27.7777777777778 - gcarstatus.speed) / g_t;

  if (g_A > 3)
  {
    g_A = 3;
  }
  if (g_A < -3)
  {
    g_A = -3;
  }
  if (msg->cmd.linear_velocity == 0)
  {
    g_A = -1.5;
  }
  acmd.acceleration = g_A ;
  acmd.acceleration = msg->cmd.linear_acceleration;

  // acmd.acceleration = msg->cmd.linear_acceleration ;
  ROS_WARN("The Steer is %f deg, The linea is %f \n", acmd.steeringAng * 57.3, msg->cmd.linear_velocity);

  recvCMDFlag = true;
}

void JoyCMDCallBack(const sensor_msgs::Joy::ConstPtr &msg)
{

  mcmd.steeringAng = msg->axes[0] * 450.0 * 3.1415926 / 180.0;
  // ROS_INFO("joy ang %f", mcmd.steeringAng);

  mcmd.gas = (msg->axes[2] + 1.0) / 2;
  mcmd.brake = (msg->axes[3] + 1.0) / 2;

  int tmp = 0;
  tmp |= msg->buttons[4];
  tmp |= msg->buttons[5];
  if (tmp == 1)
  {
    if (drivemodeFlag == 0)
    {
      drivemodeFlag = 1;
    }
    else
    {
      drivemodeFlag = 0;
    }
  }
  recvCMDFlag = true;

}

void mainback(ros::NodeHandle nh)
{

  ros::Subscriber sub_vehicleCMD_data = nh.subscribe<smartcar_msgs::ControlCommandStamped>("ctrl_cmd", 100, &VehicleCMDCallBack);
  ros::Subscriber sub_joyCMD_data = nh.subscribe<sensor_msgs::Joy>("/G29/joy", 100, &JoyCMDCallBack);
  ros::MultiThreadedSpinner spinner(2);
  spinner.spin();
}

u_int64_t lasttimestamp = 0;

int main(int argc, char **argv)
{

  ros::init(argc, argv, "simulator"); // ros系统中显示的节点名;
  ros::NodeHandle nh, nh_param("~");
  

  nh_param.param("drivemode", drivemodeFlag, int(1));
  nh_param.param<std::string>("des_ip", des_ip, "127.0.0.1");
  nh_param.param<std::string>("sou_ip", sou_ip, "127.0.0.1");

  ros::Publisher pub_VehicleStatus_ = nh.advertise<smartcar_msgs::VehicleStatus>("VehicleStatus", 10);
  ros::Publisher pub_Location_ = nh.advertise<geometry_msgs::PoseStamped>("current_pose", 10);
  //给plan的定位格式
  ros::Publisher pub_Location2_ = nh.advertise<nav_msgs::Odometry>("base_pose_ground_truth", 10);
  ros::Publisher pub_Imu_ = nh.advertise<sensor_msgs::Imu>("ImuData", 100);
  ros::Publisher pub_joy_ = nh.advertise<sensor_msgs::Joy>("ff_target", 10);
  ros::Publisher pub_currentspeed_ = nh.advertise<geometry_msgs::TwistStamped>("current_velocity", 10);

  ros::Publisher pub_location = nh.advertise<smartcar_msgs::Location>("smartcar/location", 10);
  ros::Publisher pub_chassis_ = nh.advertise<smartcar_msgs::VehicleChassis>("smartcar/chassis", 10);

  ros::Publisher pub_rviz_speed_ = nh.advertise<std_msgs::Float32>("rviz_speed", 10);

  pub_VehicleStatus = &pub_VehicleStatus_;
  pub_Location = &pub_Location_;
  pub_Location2 = &pub_Location2_;
  pub_Location3 = &pub_location;
  pub_Imu = &pub_Imu_;
  pub_joy = &pub_joy_;
  pub_currentspeed = &pub_currentspeed_;
  pub_chassis = &pub_chassis_;
  pub_rviz_speed = &pub_rviz_speed_;

  ITS::Grid process_grid_;
  process_grid = &process_grid_;

  std::ifstream file("/home/xining095/Carmaker/smartcar/miniEV_grad/calibration_table_copy.txt");
  if (!file.is_open()) {
      std::cerr << "Failed to open file!" << std::endl;
      return -1;
  }
  int num_rows = MAX_V;
  int num_cols = MAX_ACC;
  std::vector<std::vector<double>>  calibration_table(num_rows, std::vector<double>(num_cols, 0.0));
  for (int i = 0; i < num_rows; i++) {
      for (int j = 0; j < num_cols; j++) {
          if (!(file >> calibration_table[i][j])) {
              std::cerr << "Failed to read data from file!" << std::endl;
              return -1;
          }
          std::cout << calibration_table[i][j] << " ";
      }
      // std::cout << std::endl;
  }
  calibration_table_ = &calibration_table;//后面的是读文件读出来的，值传给前面

  std::thread t(mainback, nh);
  std::thread th1(receiveUDPMessageLoop);
  
  // std::ofstream * my_samplefile_;//要记录数据的时候打开这几行step1
  // std::string caliname = "/home/chiao/jinxiaoxin/mini4control/Calc/Vel_sinSignal_data_sim_tesla.txt";//记录不一样的数据记得改名字
  // std::ofstream my_samplefile (caliname,std::ios::app|std::ios::out|std::ios::in );
  // if(my_samplefile.fail()){
  //     std::cout<<"打开文件错误!"<<std::endl;
  //     return -1;
  // }
  // my_samplefile_ = &my_samplefile;
  //   *my_samplefile_<< "CMDdriver" << "\t"<< "GasFeedback" << "\t" << "targetVel" << 
  //   "\t" <<"AccX" << "\t" << "AccY" << "\t" << "CMD_acc" << "\t" << "GpsSpeed"  <<"\n";//要记录数据的时候打开这几行step1尾
  ros::Rate loop(100);
  while (ros::ok())
  {

    // u_int64_t a  = timestamp();

    if (/*a % 10 == 0 && a>lasttimestamp &&*/ recvCMDFlag /*&& recvCMDFlag*/ || drivemodeFlag == 2)
    {
      double cur_driver = 0.0;//zijidakaide
      // if (mcmd.gas > 0.0) {
      //   cur_driver = mcmd.gas;
      // } else {
      //   cur_driver = -mcmd.brake;
      // }
      std::cout << std::fixed << std::setprecision(4) << cur_driver << "\t"<< gcarstatus.feedback_gas_pedal << "\t"//step2头
      << targetVel << "\t" << gcarstatus.accel_x << "\t" << gcarstatus.accel_y << "\t" 
      << gcarstatus.speed << "\t" << gcarstatus.v_x * 3.6  <<"\n";
      //       *my_samplefile_<< std::fixed << std::setprecision(4) << cur_driver << "\t"<< gcarstatus.feedback_gas_pedal << "\t"
      // << targetVel << "\t" << gcarstatus.accel_x << "\t" << gcarstatus.accel_y << "\t" 
      // // << gcarstatus.feedback_brake_pedal << "\t" << gcarstatus.accel_x << "\t" << gcarstatus.accel_y << "\t" 
      // << acmd.acceleration << "\t" << gcarstatus.v_x * 3.6  <<"\n";//用gcarstatus.v_x * 3.6 画图
      ROS_INFO("start_time: %f", ros::Time::now().toSec());//step2尾，打开这些
      udpsend();
      // smartcar_msgs::VehicleStatus curstaus;
      // curstaus.header.stamp = ros::Time::now();
      // curstaus.drivemode = curstaus.MODE_AUTO;
      // curstaus.gearshift = 4; //P R N D 1 2 3 4
      // curstaus.angle = gcarstatus.steering_ang;
      // curstaus.speed = gcarstatus.speed;
      // pub_VehicleStatus.publish(curstaus);

      // geometry_msgs::TwistStamped currentspeed;
      // currentspeed.header.stamp = ros::Time::now();
      // currentspeed.twist.linear.x = gcarstatus.speed;
      // pub_currentspeed.publish(currentspeed);

      // geometry_msgs::PoseStamped curlocation;
      // curlocation.header.stamp = ros::Time::now();
      // curlocation.pose.position.x = gcarstatus.utm_x;
      // curlocation.pose.position.y = gcarstatus.utm_y;
      // // curlocation.pose.orientation.z = NormalizeAngle(gcarstatus.yaw) * 57.3;
      // // if(curlocation.pose.orientation.z <0){
      // //   curlocation.pose.orientation.z = curlocation.pose.orientation.z + 360;
      // // }

      // // std::cout<<"curlocation.orientation[2]"<<curlocation.orientation[2]<<std::endl;
      // geometry_msgs::Quaternion quat;
      // quat = tf::createQuaternionMsgFromYaw(NormalizeAngle(gcarstatus.yaw));
      // curlocation.pose.orientation = quat;src/simulation/simulator/src/simulator.cpp
      // pub_Location.publish(curlocation);

      // sensor_msgs::Imu imudata;
      // imudata.header.stamp = ros::Time::now();
      // imudata.angular_velocity.z = gcarstatus.rate_yaw * 57.3;
      // imudata.linear_acceleration.x = gcarstatus.accel_x;
      // imudata.linear_acceleration.y = gcarstatus.accel_y;
      // imudata.linear_acceleration.z = gcarstatus.accel_z;
      // pub_Imu.publish(imudata);

      // //给plan的定位
      // nav_msgs::Odometry odometry_;
      // odometry_.header.stamp = ros::Time::now();
      // odometry_.pose.pose.position.x = gcarstatus.utm_x;
      // odometry_.pose.pose.position.y = gcarstatus.utm_y;
      // odometry_.pose.pose.position.z = 0;

      // geometry_msgs::Quaternion quat_tmp;
      // quat_tmp = tf::createQuaternionMsgFromYaw(NormalizeAngle(gcarstatus.yaw));
      // odometry_.pose.pose.orientation = quat_tmp;

      // odometry_.twist.twist.linear.x = gcarstatus.v_x;
      // odometry_.twist.twist.linear.y = gcarstatus.v_y;
      // odometry_.twist.twist.linear.z = gcarstatus.v_z;
      // odometry_.twist.twist.angular.x = gcarstatus.rate_roll;
      // odometry_.twist.twist.angular.y = gcarstatus.rate_pitch;
      // odometry_.twist.twist.angular.z = gcarstatus.rate_yaw;
      // pub_Location2.publish(odometry_);

      // sensor_msgs::Joy curJoy;
      // double tmp = curstaus.angle;
      // if (fabs(curstaus.angle) > 450)
      // {
      //   if (curstaus.angle > 0)
      //     tmp = 450;
      //   else
      //     tmp = -450;
      // }
      // tmp = tmp / 450.0;

      // if (drivemodeFlag == 0)
      // {
      //   tmp = 0;
      //   curJoy.buttons.push_back(1);
      //   curJoy.axes.push_back(tmp);
      //   curJoy.axes.push_back(0.25);
      //   pub_joy.publish(curJoy);
      // }
      // else
      // {
      //   curJoy.buttons.push_back(0);
      //   curJoy.axes.push_back(tmp);
      //   curJoy.axes.push_back(0.25);
      //   pub_joy.publish(curJoy);
      // }

      // std::vector<struct object_info> tmp_object_array;
      // struct object_info tmp_object = {0};
      // for(int i=0; i<64; i++){
      //     if(gcarstatus.object_info_[i].Type == 0) break;
      //     tmp_object = gcarstatus.object_info_[i];
      //     tmp_object_array.push_back(tmp_object);
      // }
      // process_grid.process_data(tmp_object_array);
      // std::cout<<"time = "<<timestamp()<<std::endl;
      //   lasttimestamp = a;

      recvCMDFlag = false; //清除接收消息状态
      // ROS_INFO("end_time: %f", ros::Time::now().toSec());
    }

    loop.sleep();
  }
  udprecvstop();

  t.join();
  th1.join();
  return 0;
}

void udp2topic()
{
// // 38517414.982	3374902.242	2.865
//   // double init_x = 38517414.982;
//   // double init_y = 3374902.242;
//   // // gcarstatus.utm_x += init_x;
//   // // gcarstatus.utm_y += init_y;
  std_msgs::Float32 tmp_rviz_speed;
  tmp_rviz_speed.data = gcarstatus.speed * 3.6;
  pub_rviz_speed->publish(tmp_rviz_speed);

  // smartcar_msgs::VehicleStatus curstaus;
  // curstaus.header.stamp = ros::Time::now();
  // curstaus.drivemode = curstaus.MODE_AUTO;
  // curstaus.gearshift = 4; // P R N D 1 2 3 4
  // curstaus.angle = gcarstatus.steering_ang;
  // curstaus.speed = gcarstatus.speed;
  // pub_VehicleStatus->publish(curstaus);

  geometry_msgs::TwistStamped currentspeed;
  currentspeed.header.stamp = ros::Time::now();
  currentspeed.twist.linear.x = gcarstatus.speed;
  pub_currentspeed->publish(currentspeed);

  geometry_msgs::PoseStamped curlocation;
  curlocation.header.stamp = ros::Time::now();
  curlocation.header.frame_id = "map";
  curlocation.pose.position.x = gcarstatus.utm_x;
  curlocation.pose.position.y = gcarstatus.utm_y;
  curlocation.pose.position.z = gcarstatus.utm_z;

  // curlocation.pose.orientation.z = NormalizeAngle(gcarstatus.yaw) * 57.3;
  // if(curlocation.pose.orientation.z <0){
  //   curlocation.pose.orientation.z = curlocation.pose.orientation.z + 360;
  // }

  // std::cout<<"curlocation.orientation[2]"<<curlocation.orientation[2]<<std::endl;
  geometry_msgs::Quaternion quat;
  quat = tf::createQuaternionMsgFromYaw(NormalizeAngle(gcarstatus.yaw));
  curlocation.pose.orientation = quat;
  pub_Location->publish(curlocation);

  smartcar_msgs::Location g_location;
  g_location.header.stamp = ros::Time::now();
  g_location.ins_time[1] = (int64_t)(gcarstatus.Time * 1000.0);
  g_location.global_pos.x = gcarstatus.utm_x;
  g_location.global_pos.y = gcarstatus.utm_y;
  g_location.global_pos.z = gcarstatus.height;
  g_location.wgs84_pos[0] = gcarstatus.longitude;
  g_location.wgs84_pos[1] = gcarstatus.latitude;
  g_location.wgs84_pos[2] = gcarstatus.height;
  g_location.orientation[0] = gcarstatus.roll;
  g_location.orientation[1] = gcarstatus.pitch;
  g_location.orientation[2] = NormalizeAngle(gcarstatus.yaw);
  g_location.global_speed[0] = gcarstatus.east_speed;
  g_location.global_speed[1] = gcarstatus.north_speed;
  g_location.global_speed[2] = gcarstatus.up_speed;
  g_location.accelerate[0] = gcarstatus.acceleration_x;
  g_location.accelerate[1] = gcarstatus.acceleration_y;
  g_location.accelerate[2] = gcarstatus.acceleration_z;
  g_location.rpy_rate[0] = gcarstatus.rate_roll;
  g_location.rpy_rate[1] = gcarstatus.rate_pitch;
  g_location.rpy_rate[2] = gcarstatus.rate_yaw;

  g_location.speed = gcarstatus.speed;
  g_location.v_x = gcarstatus.v_x;
  g_location.v_y = gcarstatus.v_y;
  g_location.v_z = gcarstatus.v_z;
  g_location.accel_x = gcarstatus.accel_x;
  g_location.accel_y = gcarstatus.accel_y;
  g_location.accel_z = gcarstatus.accel_z;

  g_location.INS_status = "RTK-Fix";
  // std::cout<<"curlocation.orientation[2]"<<curlocation.orientation[2]<<std::endl;
  pub_Location3->publish(g_location);

  smartcar_msgs::VehicleChassis tmp_Chassis_;
  tmp_Chassis_.header.stamp = ros::Time::now();
  tmp_Chassis_.linear_velocity[0] = gcarstatus.v_x * 3.6;
  tmp_Chassis_.linear_velocity[1] = gcarstatus.v_y * 3.6;
  tmp_Chassis_.linear_velocity[2] = gcarstatus.v_z * 3.6;
  tmp_Chassis_.vehicleAcceleration[0] = gcarstatus.accel_x;
  tmp_Chassis_.vehicleAcceleration[1] = gcarstatus.accel_y;
  tmp_Chassis_.vehicleAcceleration[2] = gcarstatus.accel_z;
  tmp_Chassis_.cmd_gas = mcmd.gas;
  tmp_Chassis_.cmd_brake = mcmd.brake;
  tmp_Chassis_.feedback_torque = gcarstatus.feedback_torque;
  tmp_Chassis_.feedback_steerAng = gcarstatus.steering_ang;
  pub_chassis->publish(tmp_Chassis_);

  //给plan的加速度
  sensor_msgs::Imu imudata;
  imudata.header.stamp = ros::Time::now();
  imudata.angular_velocity.z = gcarstatus.rate_yaw * 57.3;
  imudata.linear_acceleration.x = gcarstatus.accel_x;
  imudata.linear_acceleration.y = gcarstatus.accel_y;
  imudata.linear_acceleration.z = gcarstatus.accel_z;
  pub_Imu->publish(imudata);

  //给plan的定位
  nav_msgs::Odometry odometry_;
  odometry_.header.stamp = ros::Time::now();
  odometry_.pose.pose.position.x = gcarstatus.utm_x;
  odometry_.pose.pose.position.y = gcarstatus.utm_y;
  odometry_.pose.pose.position.z = gcarstatus.utm_z;

  geometry_msgs::Quaternion quat_tmp;
  quat_tmp = tf::createQuaternionMsgFromRollPitchYaw(0.0, 0.0, NormalizeAngle(gcarstatus.yaw));
  odometry_.pose.pose.orientation = quat_tmp;

  odometry_.twist.twist.linear.x = gcarstatus.v_x;
  odometry_.twist.twist.linear.y = gcarstatus.v_y;
  odometry_.twist.twist.linear.z = gcarstatus.v_z;
  
  odometry_.twist.twist.angular.x = gcarstatus.rate_roll;
  odometry_.twist.twist.angular.y = gcarstatus.rate_pitch;
  odometry_.twist.twist.angular.z = gcarstatus.rate_yaw;
  pub_Location2->publish(odometry_);

  sensor_msgs::Joy curJoy;
  double tmp = tmp_Chassis_.feedback_steerAng;
  if (fabs(tmp) > 450)
  {
    if (tmp > 0)
      tmp = 450;
    else
      tmp = -450;
  }
  tmp = tmp / 450.0;

  if (drivemodeFlag == 0)
  {
    tmp = 0;
    curJoy.buttons.push_back(1);
    curJoy.axes.push_back(tmp);
    curJoy.axes.push_back(0.25);
    pub_joy->publish(curJoy);
  }
  else
  {
    curJoy.buttons.push_back(0);
    curJoy.axes.push_back(tmp);
    curJoy.axes.push_back(0.25);
    pub_joy->publish(curJoy);
  }

  std::vector<struct object_info> tmp_object_array;
  struct object_info tmp_object = {0};
  for (int i = 0; i < 64; i++)
  {
    if (gcarstatus.object_info_[i].Type == 0)
      break;
    tmp_object = gcarstatus.object_info_[i];
        tmp_object_array.push_back(tmp_object);
  }
  process_grid->egocar.pose.position.x = gcarstatus.utm_x ;
  process_grid->egocar.pose.position.y = gcarstatus.utm_y ;
  process_grid->egocar.pose.position.z = gcarstatus.utm_z;
    process_grid->egocar.pose.orientation.z = NormalizeAngle(gcarstatus.yaw );  //直接将yaw,赋值给z+ 2.865
    process_grid->process_data(tmp_object_array);
  // std::cout<<"time = "<<timestamp()<<std::endl;
  //   lasttimestamp = a;
}