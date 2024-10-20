#include "ros/ros.h"
#include "goolf_pub_sub/drive_info.h"
#include "ulog.h"

static uint64_t clock_ms()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "autolabor_planning");
    ros::NodeHandle planning;
    ros::Publisher pub = planning.advertise<goolf_pub_sub::drive_info>("drive_info", 1000);
    goolf_pub_sub::drive_info drive_info; //定义结构体变量

    drive_info.speed = 0;
    drive_info.angle = 0;
    drive_info.gear = 2; // D

    uint8_t flag = 0;
    uint64_t now1 = clock_ms();
    uint64_t now2 = clock_ms();
    while (ros::ok())
    {
        uint64_t next1 = clock_ms();
        if ((next1 - now1) >= 200)
        {
            now1 = next1;
            pub.publish(drive_info);
            LOG_INFO("Gear:%d,speed:%.2f,angle:%d", drive_info.gear, drive_info.speed, drive_info.angle);
        }
        uint16_t next2 = clock_ms();
        if ((next2 - now2) >= 1000)
        {
            now2 = next2;
            if (flag == 0)
            {
                drive_info.speed += 0.5; // km/h
                drive_info.angle += 10;  //方向盘转角 度  （-400 - 400）
                if (drive_info.speed > 20.0 && drive_info.angle > 400)
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                drive_info.speed -= 0.5; // km/h
                drive_info.angle -= 10;  //方向盘转角 度  （-400 - 400）
                if (drive_info.speed < 0.0 && drive_info.angle <= 0)
                {
                    flag = 2;
                }
            }
            if (flag == 2)
            {
                exit(1);
            }
        }
        ros::spinOnce();
    }
    return 0;
}