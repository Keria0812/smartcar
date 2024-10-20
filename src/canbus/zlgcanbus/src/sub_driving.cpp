#include "ros/ros.h"
// #include "goolf_pub_sub/drive_info.h"
// #include "ulog.h"
#include <can_msgs/Frame.h>
#include <smartcar_msgs/Control.h>
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
double steer_cmd = 0;
double brake_cmd = 0;
double throttle_cmd = 0;
int steer_val = 0x0a;
uint8_t enable = 0;
uint8_t lastswitch = 0;
extern struct CanbusMeta *CANBUS_META;
void CanRecieve(int channels, CanbusMeta *meta);
void car_run(const can_msgs::Frame::ConstPtr &angmsg);
void controlcmdrecv(const smartcar_msgs::Control::ConstPtr &msg);

bool meta_init = false;

struct can_frame frame_1 = {0};
struct CanbusMeta *meta = CANBUS_META;

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


void mainback(ros::NodeHandle nh)
{

    ros::Subscriber sub_cmd = nh.subscribe<can_msgs::Frame>("/can0_sent_messages" , 5,&car_run );
    ros::MultiThreadedSpinner spinner(1);
    spinner.spin();
}

int main(int argc, char *argv[]) 
{
    ros::init(argc, argv, "zlgcanbus");
    ros::NodeHandle driver;

    //subscribe steering angle message from cmd_node
    // ros::Subscriber sub_cmd = driver.subscribe<can_msgs::Frame>("/can0_sent_messages" , 5,&car_run );
    // ros::Subscriber sub_cmddata = driver.subscribe<smartcar_msgs::Control>("/ctrl_command", 1, &controlcmdrecv );
    g_VehicleChassis_msg_pub = driver.advertise<can_msgs::Frame>("/can0_received_messages", 10);
    g_rtkmsg_pub = driver.advertise<can_msgs::Frame>("/can1_received_messages", 10);


    //broadcast RTK location message to control model& path_publisher

    int channels = 2;
    if (!meta->do_init(channels, NULL, NULL)) 
    {
        printf("init can device with channels = %d failed.", channels);
        exit(1);
    }
    meta_init = true;

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

    

    std::thread t(mainback, driver);


    ros::Rate loop_rate(1000);

    while (ros::ok()) 
    {
        CanRecieve(2,meta);
        // ros::spinOnce();

        // finish = clock_ms();
        // if(((double)finish - (double)start)  > 20)
        // {
        //     //steercmd
        //     frame_1.can_dlc = 4;
        //     frame_1.can_id = 0x64;
        //     memset(frame_1.data,0x00,8);
        //     frame_1.data[0] = ((signed short int)(steer_cmd*10))&0xff;
        //     frame_1.data[1] = ((signed short int)(steer_cmd*10))>>8;
        //     frame_1.data[2] = enable;//enable;
        //     frame_1.data[3] = 0x0a;
        //     int ret = meta->do_send(0, &frame_1);
        //     //brake
        //     frame_1.can_dlc = 8;
        //     frame_1.can_id = 0x60;
        //     memset(frame_1.data,0x00,8);
        //     frame_1.data[0] = ((signed short int)(brake_cmd/0.000015259))&0xff;
        //     frame_1.data[1] = ((signed short int)(brake_cmd/0.000015259)>>8);
        //     frame_1.data[2] = 0;
        //     frame_1.data[3] = 0;  //EN
        //     ret = meta->do_send(0, &frame_1);
        //     //throttle
        //     frame_1.can_dlc = 8;
        //     frame_1.can_id = 0x62;
        //     memset(frame_1.data,0x00,8);
        //     frame_1.data[0] = ((signed short int)(throttle_cmd/0.000015259))&0xff;
        //     frame_1.data[1] = ((signed short int)(throttle_cmd/0.000015259)>>8);
        //     frame_1.data[2] = 0;
        //     frame_1.data[3] = 0;  //EN
        //     ret = meta->do_send(0, &frame_1);

        //     //signal light
        //     frame_1.can_dlc = 5;
        //     frame_1.can_id = 0x68;
        //     memset(frame_1.data,0x00,8);
        //     frame_1.data[0] = 0;
        //     frame_1.data[1] = 0;
        //     frame_1.data[2] = 0;
        //     frame_1.data[3] = 0;  
        //     ret = meta->do_send(0, &frame_1);

        //     start = finish;
        // }
    }
    meta->do_cleanup(channels);
    t.join();
    return 0;
}

void CanRecieve(int channels, CanbusMeta *meta) {
        /* receive channle 0 */
        int channel_id = 0;
        struct can_frame frame[10] = {0};
        int ret = meta->do_recv(channel_id, &frame[0]);
        if (ret > 0) {
            // printf("%d vehicle messages in channel0: \n",ret);
            for (size_t j = 0; j < ret; j++)
            {
                unsigned _id = CAN_GET_ID(&frame[j]);
                printf("msgid: %04x [",_id);
                for(int i = 0; i < 8; i++)
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

                g_VehicleChassis_msg_pub.publish(vehicle_msg);
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
            // printf("%d rtk messages in channel1: \n",ret);
 
            for (size_t j = 0; j < ret; j++)
            {
                unsigned _id = CAN_GET_ID(&frame[j]);

                printf("The msgid: %04x [",_id);
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

                // switch (rtk_msg.id) {               
                //     case 0x32A: 
                //     case 0x504:
                //         break;
                //     default:
                //         break;
                // }
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
    frame_1.can_dlc = 8;
    frame_1.can_id = angmsg->id;
    for(int i = 0; i < frame_1.can_dlc; i++)
    {
        frame_1.data[i]=angmsg->data[i];
    }
    // frame_1.data = angmsg->data;
    if (meta_init)
    {
        int ret = meta->do_send(0, &frame_1);

    }
    std::cout << "control cmd received : " << frame_1.can_id << std::endl;

}

// void controlcmdrecv(const smartcar_msgs::Control::ConstPtr &msg)
// {
//     steer_cmd = msg->steer;
//     brake_cmd = msg->brake;
//     throttle_cmd = msg->throttle;
//     steer_val = msg->steer_val;
//     enable = msg->enable;

//     std::cout << "steer_cmd: " << steer_cmd << std::endl;
//     std::cout << "brake_cmd: " << brake_cmd << std::endl;
//     std::cout << "throttle_cmd: " << throttle_cmd << std::endl;
//     std::cout << "enable: " << enable << std::endl;
// }