#include "ros/ros.h"
// #include "goolf_pub_sub/drive_info.h"
// #include "ulog.h"
#include <can_msgs/Frame.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>

#include "can.h"
#include "candriver.h"
#include "controlcan.h" //for usbcan ii+
//#include "zcan.h"  //for usbcanfd 200U
static ros::Publisher g_rtkmsg_pub;
static ros::Publisher g_VehicleChassis_msg_pub;
extern struct CanbusMeta *CANBUS_META;
void CanRecieve(int channels, CanbusMeta *meta);
void car_run(const can_msgs::Frame::ConstPtr &angmsg);
     struct can_frame frame_1 = {0};

// void mainback(ros::NodeHandle nh)
// {

//   ros::Subscriber sub_cmd = nh.subscribe<can_msgs::Frame>("/can0_sent_messages", 100,&car_run );
//   ros::MultiThreadedSpinner spinner(1);
//   spinner.spin();
static uint64_t clock_ms()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}


int main(int argc, char *argv[]) 
{
    ros::init(argc, argv, "autolabor_driver");
    ros::NodeHandle driver;
    struct CanbusMeta *meta = CANBUS_META;
    // struct CanbusMeta *meta_VC = CANBUS_META;

    //subscribe steering angle message from cmd_node
    ros::Subscriber sub_cmd = driver.subscribe<can_msgs::Frame>("/can0_sent_messages", 100,&car_run );

    //broadcast RTK location message to control model& path_publisher
    g_rtkmsg_pub = driver.advertise<can_msgs::Frame>("/can0_received_messages", 10);
    // g_VehicleChassis_msg_pub = driver.advertise<can_msgs::Frame>("/can1_received_messages", 10);


    int channels = 2;
    if (!meta->do_init(channels, NULL, NULL)) 
    {
        printf("init can device with channels=%d failed.", channels);
        exit(1);
    }

    // usleep(1000000);


    // std::thread t(mainback, driver);
    double start, finish;
    //clock_t为CPU时钟计时单元数
    start = clock_ms();
    //clock()函数返回此时CPU时钟计时单元数
    /*
     你的代码
     
    */
    
    //clock()函数返回此时CPU时钟计时单元数
    // cout <<endl<<"the time cost is:" << double(finish - start) / CLOCKS_PER_SEC<<endl;



    ros::Rate loop_rate(50);

    while (ros::ok()) 
    {
        CanRecieve(2,meta);
        ros::spinOnce();
        finish = clock_ms();
        if(((double)finish - (double)start)  > 20)
        {
            // std::cout << "111111111111 " << std::endl;
            //  frame_1.data[0] = ((signed short int)(-360.0*10))&0xff;
            // frame_1.data[1] = ((signed short int)(-360.0*10))>>8;
            int ret = meta->do_send(0, &frame_1);
            //printf("frame0 : %x frame1 : %x\n",frame_1.data[0] ,frame_1.data[1] ) ;
            // printf("msgid: %04x [",frame_1.can_id);
            // for(int i = 0;i<frame_1.can_dlc;i++)
            // {
            //     printf("%02x ",frame_1.data[i]);
            // }
            // printf("]\n");
            std::cout << "11111111111111111111111111111"<<std::endl;
            start = finish;
        }
    }
    meta->do_cleanup(channels);
    // t.join();


    // ros::Subscriber sub = driver.subscribe<goolf_pub_sub::drive_info>("drive_info", 10, boost::bind(&CanRecieve, _1,
    // channels, meta)); ros::spin();
    return 0;
}

void CanRecieve(int channels, CanbusMeta *meta) {
        /* receive channle 0 */
        int channel_id = 0;
        // int channel_id_VehicleChissis = 1;
        struct can_frame frame[10] = {0};
        // struct can_frame frame_VehicleChissis[10] = {0};
        int ret = meta->do_recv(channel_id, &frame[0]);
        // int ret_VehicleChissis = meta->do_recv(channel_id_VehicleChissis, &frame_VehicleChissis[0]);
        if (ret > 0) {
            printf("%d vehicle messages in channel0: \n",ret);
            for (size_t j = 0; j < ret; j++)
            {
                unsigned _id = CAN_GET_ID(&frame[j]);
                printf("msgid: %04x [",_id);
                for(int i = 0;i<8;i++)
                {
                    printf("%02x ",frame[j].data[i]);
                }
                printf("]\n");

                can_msgs::Frame vehicle_msg;
                vehicle_msg.id = _id;
                vehicle_msg.dlc = 8;

                for(int i = 0;i<8;i++)
                {
                    vehicle_msg.data[i] = frame[j].data[i];
                }
                // g_VehicleChassis_msg_pub.publish(vehicle_msg);
                
                switch (vehicle_msg.id) {               
                    case 0x32A: 
                    case 0x504:
                        break;
                    default:
                        break;
                }
            }
        } 
        else if (ret == -1) 
        {
            //ROS_ERROR("can device '%s' recv ch%ld failed", meta->name, i);
        }
        else
        {
            //ROS_ERROR("can device '%s' recv ch%ld failed, no message", meta->name, i);
        }

        /* receive channle 1 */
        channel_id = 1;
        ret = meta->do_recv(channel_id, &frame[0]);
        if (ret > 0) {
            printf("%d rtk messages in channel1: \n",ret);
 
            for (size_t j = 0; j < ret; j++)
            {
                unsigned _id = CAN_GET_ID(&frame[j]);

                printf("msgid: %04x [",_id);
                for(int i = 0;i<8;i++)
                {
                    printf("%02x ",frame[j].data[i]);
                }
                printf("]\n");

                can_msgs::Frame rtk_msg;
                rtk_msg.id = _id;
                rtk_msg.dlc = 8;
                for(int i = 0;i<8;i++)
                {
                    rtk_msg.data[i] = frame[j].data[i];
                }
                g_rtkmsg_pub.publish(rtk_msg);

                switch (rtk_msg.id) {               
                    case 0x32A: 
                    case 0x504:
                        break;
                    default:
                        break;
                }
            }
        } 
        else if (ret == -1) 
        {
            //ROS_ERROR("can device '%s' recv ch%ld failed", meta->name, i);
        }
        else
        {
            //ROS_ERROR("can device '%s' recv ch%ld failed, no message", meta->name, i);
        }
}

void car_run(const can_msgs::Frame::ConstPtr &angmsg)
{
    frame_1.can_dlc = 4;
    frame_1.can_id = angmsg->id;
    for(int i = 0;i<4;i++)
    {
        frame_1.data[i]=angmsg->data[i];
    }
    std::cout << "control cmd received.\n" << std::endl;
}