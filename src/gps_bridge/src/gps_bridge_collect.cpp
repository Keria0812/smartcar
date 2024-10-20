/*
 * @Date: 2021-10-25 13:55:24
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-01-22 03:58:49
 * @FilePath: /miniEV/src/gps_bridge/src/gps_bridge_collect.cpp
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

bool recvflag = false;
// geometry_msgs::PoseStamped curpos;
double lastX =0, lastY=0;
std::ofstream * my_samplefile_;
//publish sensor_msgs/NavSat{Fix,Status}
void NavSat_recv(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    const geometry_msgs::PoseStamped curpos = *msg;

    recvflag = true;
    if(((curpos.pose.position.x - lastX) * (curpos.pose.position.x - lastX) + (curpos.pose.position.y - lastY) * (curpos.pose.position.y - lastY)) > 0.04){
                
        double roll, pitch, yaw;
        tf::Quaternion quat;
        tf::quaternionMsgToTF(curpos.pose.orientation, quat);
        std::cout << curpos.pose.orientation.x << " " << curpos.pose.orientation.y  << " " << curpos.pose.orientation.z<< " " << curpos.pose.orientation.w<< " " << std::endl;
        tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);//进行转换
        
        *my_samplefile_<< std::fixed << std::setprecision(3) << curpos.pose.position.x << "\t"<< curpos.pose.position.y << "\t" << yaw  <<"\n";
        ROS_INFO("UTM X:    %.3lf   UTM Y:  %.3lf", curpos.pose.position.x, curpos.pose.position.y);
        lastX = curpos.pose.position.x;
        lastY = curpos.pose.position.y;
        recvflag = false;
    }
}


int main(int argc, char **argv)
{

    ros::init(argc, argv, "gps_collect");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<geometry_msgs::PoseStamped>("/current_pose", 10, &NavSat_recv);

    time_t nowT;       // time_t就是long int 类型
    nowT = time(NULL); // 取得当前时间 ,秒级
    char strT[32];
    /* 使用 strftime 将时间格式化成字符串（"YYYY-MM-DD hh:mm:ss"格式)*/
    strftime(strT, sizeof(strT), "%Y-%m-%d-%H:%M:%S", localtime(&nowT));
    std::string str = strT;
    // std::string str1 = "/home/chenjian/catkin_ws/";
    std::string str2 = ".txt";
    // str = str1 + str + str2;
    str = str + str2;

    //std::cout<<timestamp()<<std::endl;
    /*  
    ios::app：　　　如果没有文件，那么生成空文件；如果有文件，那么在文件尾追加。
    ios::ate：　　　文件打开后定位到文件尾，ios:app就包含有此属性
    ios::binary：　以二进制方式打开文件，缺省的方式是文本方式。两种方式的区别见前文
    ios::in：　　　 文件以输入方式打开（文件数据输入到内存）
    ios::out：　　　文件以输出方式打开（内存数据输出到文件）
    ios::nocreate： 不建立文件，所以文件不存在时打开失败
    ios::noreplace：不覆盖文件，所以打开文件时如果文件存在失败
    ios::trunc：　　如果文件存在，把文件清空再写入
    */
    // std::cout<<timestamp()<<std::endl;
    std::ofstream my_samplefile (str,std::ios::app|std::ios::out|std::ios::in );
    //std::cout<<timestamp()<<std::endl;
    //std::cout<<timestamp()<<std::endl;<< ros::Time::now() << "\t" 
    if(my_samplefile.fail()){
       std::cout<<"打开文件错误!"<<std::endl;
       return -1;
    }
    my_samplefile_ = &my_samplefile;
    ros::spin();
    // ros::Rate loop_rate(100);
    // while (ros::ok())
    // {
    //     ros::spinOnce();
    //     if(recvflag){
    //         if(((curpos.pose.position.x - lastX) * (curpos.pose.position.x - lastX) + (curpos.pose.position.y - lastY) * (curpos.pose.position.y - lastY)) > 0.04){
                
    //             double roll, pitch, yaw;
    //             tf::Quaternion quat;
    //             tf::quaternionMsgToTF(curpos.pose.orientation, quat);
    //             std::cout << curpos.pose.orientation.x << " " << curpos.pose.orientation.y  << " " << curpos.pose.orientation.z<< " " << curpos.pose.orientation.w<< " " << std::endl;

    //             tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);//进行转换
                
    //             my_samplefile<<std::fixed << std::setprecision(3) << curpos.pose.position.x << "\t"<< curpos.pose.position.y << "\t" << yaw  <<"\n";
    //             ROS_INFO("UTM X:    %.3lf   UTM Y:  %.3lf", curpos.pose.position.x, curpos.pose.position.y);
    //             lastX = curpos.pose.position.x;
    //             lastY = curpos.pose.position.y;
    //             recvflag = false;
    //         }

    //     }

    //     loop_rate.sleep();
    // }
    my_samplefile.close();
    //std::cout<<timestamp()<<std::endl;

    return 0;
}