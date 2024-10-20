#include <math.h>
#include <string.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "ros/ros.h"
// #include <track_publisher/linear_quadratic_regulator.h>
#include <deque>

/***********添加***************/
#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
float my_gas = 0;
float my_brake = 0;
/***********添加***************/

#include <arpa/inet.h>
#include <fcntl.h>
// #include <iau_ros_msgs/Follow.h>
// #include <iau_ros_msgs/Location.h>
// #include <iau_ros_msgs/PointXYA.h>
// #include <iau_ros_msgs/VehicleCMD.h>
// #include <iau_ros_msgs/VehicleStatus.h>
#include <math.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Joy.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <tf/tf.h>
#include <time.h>
#include <unistd.h>

#include <mutex>
std::mutex carmaker;

#define DEBUG_FLAG (1)
bool recvStatusFlag = false;
bool recvCMDFlag = false;
int drivemodeFlag = 1;
using namespace Eigen;

double laststeerangcmd = 0;
bool pub_stob = true;
ros::Publisher *pub = nullptr;

struct manulCMD {
    /* data */
    double steeringAng;
    double gas;
    double brake;
    int flag;
};

struct manulCMD mcmd = {0, 0, 0, 0};

void mainback() {
    ros::Rate loop(50);
    while (pub_stob) {
        {
            sensor_msgs::Joy curJoy;
            for(int i=0; i< 10; i++){
                curJoy.axes.push_back(0);
            }
            for(int i=0; i< 10; i++){
                curJoy.buttons.push_back(0);
            }

            curJoy.axes[0] = mcmd.steeringAng * 3.1415926 / 180.0;
            // ROS_INFO("joy ang %f", mcmd.steeringAng);

            curJoy.axes[2] = mcmd.gas * 2.0 - 1;
            curJoy.axes[3] = mcmd.brake * 2.0 - 1;

            curJoy.buttons[4] = mcmd.flag;
            pub->publish(curJoy);
            if(mcmd.flag == 1){
                mcmd.flag = 0;
            }
            loop.sleep();
        }
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "manual_control");  // ros系统中显示的节点名;
    ros::NodeHandle nh;

    ros::Publisher pub_joy = nh.advertise<sensor_msgs::Joy>("/G29/joy", 10);
    pub = &pub_joy;

    std::thread t(mainback);

    while (ros::ok()) {
        double a[4] = {0};  //初始化数组
        std::cout << "请输入 油门[0-1] 刹车[0-1] 转向[(-780)-780] 切换: \n";
        for (int i = 0; i < 4; ++i)  //输入
        {
            std::cin >> a[i];
        }
        mcmd.gas = a[0];
        mcmd.brake = a[1];
        mcmd.steeringAng = a[2];
        mcmd.flag = a[3];

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    
    if (t.joinable()) {
        pub_stob = false;
        t.join();
    }
    return 0;
}