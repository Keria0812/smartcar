
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <smartcar_msgs/VehicleLocation.h>
#include <netinet/in.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <dirent.h>

bool car_status = false;
int64_t max_count = 300;
uint64_t nocarinfo = max_count;
bool restart_py = false;
bool recv_py = false;
uint64_t high_steer_vel_count = 0;

bool first_flag = true;
int32_t simstatus = 1;
int sendcount = 0;

void udpsend(int status_);
void udprecv();
void udprecvstop();
double q_0 = 1.0;
double q_1 = 1.0;
double q_2 = 1.0;
double q_3 = 1.0;
double q_4 = 1.0;
double q_5 = 1.0;
double r_0 = 1.0;
double r_1 = 1.0;

void ScriptSend(std::string &cmd) {
    int sockfd, n;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("socket error\n");
        exit(2);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8081); /*访问服务器的8887号端口*/

    if ((n = connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) {
        printf("connect error\n");
        exit(1);
    }

    std::string tmp = cmd + "\r\n";
    send(sockfd, tmp.c_str(), sizeof(tmp), 0);
    close(sockfd);
}

void LocationCallBack(const smartcar_msgs::VehicleLocation::ConstPtr &msg) {
    nocarinfo = 0;
    // std::cout << ".........\n";
}

void Steer_VelCallBack(const std_msgs::Float64ConstPtr &msg) {
    double steer_vel = msg->data * 57.3;
    if (steer_vel > 150){
        high_steer_vel_count++;
        std::cout << "high_steer_vel_count: " << high_steer_vel_count << std::endl;
    }
    // std::cout << ".........\n";
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "Simulation_RemoteControl");  // ros系统中显示的节点名;
    ros::NodeHandle nh, nh_priv("~");

    ros::Subscriber sub_vehicleCMD_data = nh.subscribe<smartcar_msgs::VehicleLocation>("smartcar/Location", 1, &LocationCallBack);
    ros::Subscriber sub_steer_vel = nh.subscribe<std_msgs::Float64>("/steer_vel", 10, &Steer_VelCallBack);
    ros::Publisher pub_simstatus = nh.advertise<std_msgs::Int32>("simstatus", 10);

    std::thread t1(udprecv);

    // std::this_thread::sleep_for(std::chrono::seconds(5));
    std::string filename;
    nh_priv.param<std::string>("theta_path", filename, "/home");
    std::ifstream fin;
    bool error = false;
    fin.open(filename);
    if (fin.fail()) {
        ROS_ERROR("no found theta");
        exit(0);
    }
    std::string test = "";
    std::vector<std::vector<double>> MyData;
    const char* folderPath = "/home/xining095/Carmaker/smartcar/IAU (1)/Data/TestRun/05plan"; // 文件夹路径

    DIR* dir;
    struct dirent* entry;

    dir = opendir(folderPath);
    if (dir == NULL) {
        std::cerr << "Failed to open directory" << std::endl;
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // 判断是否是普通文件
            std::cout << entry->d_name << std::endl; // 打印文件名
            std::string testcase = std::string(entry->d_name);
            std::string test_cmd = "./src/simulation/simulator/include/CM_APO/ApoClntDemo.linux64 -apphost localhost StartStop 05plan/" +testcase;
            const char* command = test_cmd.c_str();
            int result = std::system(command);
            // printf("%d\n", result);
            if (result == 0) {
                printf("Testing %s !\n", testcase.c_str());
                sleep(10);
            } else {
    
                fprintf(stderr, "Error to test %s \n", testcase.c_str());
                continue;
            }
            const char* command_close = "./src/simulation/simulator/include/CM_APO/ApoClntDemo.linux64 -apphost localhost Stop";
            result = std::system(command_close);
            printf("Close the TestRun %d\n", result);
            sleep(1);
        }
    }

    closedir(dir);
    
    // const char* command = "./src/simulation/simulator/include/CM_APO/ApoClntDemo.linux64 -apphost localhost StartStop 05plan/123";
    

    
    // while (std::getline(fin, test)) //全局函数，隶属于<string>头文件，空行也会被读入，但流数据为空
    // {
    //     if(test == "") continue; //排除空行
    //     std::stringstream os_data(test);
    //     double tmp;
    //     std::vector<double> mydata;
    //     while(os_data >> tmp){
    //         // ROS_INFO("into");
    //         // ROS_INFO("tmp: %.3f", tmp);
    //         mydata.push_back(tmp);
    //     }
    //     MyData.push_back(mydata);
    //     // os_data << std::fixed << std::setprecision(3) << 12.00;
    //     // string xxx = "";
    //     // while (os_data >> xxx)
    //     // {
    //     //     /* code */
    //     // }
    // }
    std::string mycmd = "StartSim";
    ScriptSend(mycmd);
    std::cout <<"MyData " << MyData[0].size() << std::endl;
    std::cout <<"MyData " << MyData.size() << std::endl;
    int length = MyData.size();
    ros::param::set("pathfollow/dynamic_matrix_q0", MyData[length-1][0]);
    ros::param::set("pathfollow/dynamic_matrix_q1", MyData[length-1][1]);
    ros::param::set("pathfollow/dynamic_matrix_q2", MyData[length-1][2]);
    ros::param::set("pathfollow/dynamic_matrix_q3", MyData[length-1][3]);
    ros::param::set("pathfollow/dynamic_matrix_q4", MyData[length-1][4]);
    ros::param::set("pathfollow/dynamic_matrix_q5", MyData[length-1][5]);
    ros::param::set("pathfollow/dynamic_matrix_r0", MyData[length-1][6]);
    ros::param::set("pathfollow/dynamic_matrix_r1", MyData[length-1][7]);

    ros::Rate loop_rate(50);
    while (ros::ok()) {
        /* code */
        nocarinfo++;
        ros::spinOnce();
        // std::cout << "nocarinfo " << nocarinfo << std::endl;
        // if (nocarinfo == 0) {
        //     std_msgs::Int32 tmp;
        //     tmp.data = 1;  // start
        //     pub_simstatus.publish(tmp);
        //     udpsend(1);
        //     sendcount = 0;
        //     // std::cout << "running \n";
        // } else if (nocarinfo >= max_count && first_flag) {
        //     std::cout << "first run\n";
        //     std_msgs::Int32 tmp;
        //     tmp.data = 1;  // restart
        //     pub_simstatus.publish(tmp);
        //     udpsend(1);
        //     std::string mycmd = "StartSim";
        //     ScriptSend(mycmd);
        //     nocarinfo = 0;
        //     first_flag = false;
        //     // std::this_thread::sleep_for(std::chrono::seconds(1));
        // } else if(restart_py){
        //     std::cout << "restart run\n";
        //     std_msgs::Int32 tmp;
        //     tmp.data = 1;  // restart
        //     pub_simstatus.publish(tmp);
        //     udpsend(1);
        //     std::string mycmd = "StartSim";
        //     ScriptSend(mycmd);
        //     nocarinfo = 0;
        //     restart_py = false;
        //     recv_py = false;
        //     high_steer_vel_count = 0; 
        //     // std::this_thread::sleep_for(std::chrono::seconds(1));
        // } else {

        // }

        if (high_steer_vel_count >= 200) {
            std::string mycmd = "StopSim";
            ScriptSend(mycmd); 
            high_steer_vel_count = 0; 
            std::cout << "抖动太大，结束仿真" << std::endl;          
        }

        if(nocarinfo >= 500){
            // std::cout << "stop \n";
            high_steer_vel_count = 0; 
            nocarinfo = 500;
            std_msgs::Int32 tmp;
            tmp.data = 2;  // sim stop, start process data
            pub_simstatus.publish(tmp);
            sendcount++;
            if(sendcount == 1){
                udpsend(2);
            }
            if(sendcount > 100 && recv_py == false){
                udpsend(2);
                std::cout << "重发停止状态 \n";
            }
            
        }

        loop_rate.sleep();
    }
    udprecvstop();
    t1.join();

    return 0;
}

void udpsend(int status_) {
    int fa = 0;
    fa = socket(AF_INET, SOCK_DGRAM, 0);
    if (fa < 0) {
        std::cout << "failed" << std::endl;
    }

    struct sockaddr_in server_addr, cliaddr;
    bzero(&server_addr, sizeof(server_addr));  //目的ip 和端口
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(10240);

    bzero(&cliaddr, sizeof(cliaddr));  //发送端ip和端口
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    cliaddr.sin_port = htons(10241);
    if (bind(fa, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) == -1) {
        std::cout << "bind fail!" << std::endl;
    }

    int maxbuf = sizeof(int);
    // int tmp = 100;
    char buf[maxbuf];
    memset(buf, 0, maxbuf);
    int status = status_;
    memcpy(buf, &status, sizeof(status));
    // memcpy(buf+4, &tmp, sizeof(tmp));
    sendto(fa, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    // printf("send success\n");
    close(fa);
}

void udprecv() {
    // 1. 定义服务器ip地址和侦听端口，初始化要绑定的网络地址结构，例如：
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));              //初始化结构体
    server_addr.sin_family = AF_INET;                      //地址类型为AF_INET
    server_addr.sin_port = htons(10242);                    //服务器端口
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  /// INADDR_ANY;  //本机IP地址

    // 2. 建立套接字文件描述符，使用socket()，
    int shou = 0;
    shou = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (shou < 0) {
        printf("create sock error\n");
        exit(-1);
    }

    // setnonblocking(shou);

    // 3. 绑定侦听端口，使用bind()函数，将套接字文件描述符和一个地址类型变量进行绑定
    int ret = bind(shou, (struct sockaddr *)&server_addr, sizeof(server_addr));  //绑定地址
    if (ret < 0) {
        printf("bind shou error\n");
        exit(-1);
    } else {
        std::cout << "create udp success\n";
    }

    // 4.接收客户端的数据，使用recvfrom()函数接受客户端的网络数据。
    struct sockaddr_in client_addr;            //再创建一个地址类型变量存储收到的地址
    bzero(&client_addr, sizeof(client_addr));  //初始化结构体
    unsigned int len = sizeof(client_addr);    //在 linux 平台下，socklen_t 类型是 unsigned int 类型的别名
    int gcarstatus = 0;
    while (ros::ok()) {
        int maxbuf = 1024;//sizeof(gcarstatus);
        // char buf[maxbuf];
        // memset(buf, 0, maxbuf);
        // int n = recvfrom(shou, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &len);
        // printf(" 接收数据长度: %d \n",n);
        // if (n <= 4 ) {
        //     printf("接收数据长度: %d \n", n);
        //     printf("线程结束\n");
        //     break;
        // }
        // printf("inno_data length = %ld\n",sizeof(inno_data));
        // memcpy(&inno_data,buf,sizeof(inno_data));
        // printf("receive msg from %s:%d len=%ld:\n",inet_ntoa(client_addr.sin_addr), client_addr.sin_port,
        // sizeof(buf));
        // double curent_gas =0;
        // double curent_brake =0;
        // double

        // if(n == 20){
        //     // printf("pycharm 已接收到状态1\n");
        //     continue;
        // }
        // if(n == 24){
        //     // printf("pycharm 已接收到状态2\n");
        //     recv_py = true;
        //     continue;
        // }

        // {
        //     // std::lock_guard<std::mutex> lock(carmaker);
        //     // memcpy(&gcarstatus, buf, sizeof(gcarstatus));
        //     memcpy(&q_0, buf, sizeof(q_0));
        //     memcpy(&q_1, buf+8, sizeof(q_1));
        //     memcpy(&q_2, buf+16, sizeof(q_2));
        //     memcpy(&q_3, buf+24, sizeof(q_3));
        //     memcpy(&q_4, buf+32, sizeof(q_4));
        //     memcpy(&q_5, buf+40, sizeof(q_5));
        //     memcpy(&r_0, buf+48, sizeof(r_0));
        //     memcpy(&r_1, buf+56, sizeof(r_1));
        //     restart_py = true;
        //     printf("restart_py\n");
        //     printf(" q_0= %f\n",q_0);
        //     printf(" q_1= %f\n",q_1);
        //     printf(" q_2= %f\n",q_2);
        //     printf(" q_3= %f\n",q_3);
        //     printf(" q_4= %f\n",q_4);
        //     printf(" q_5= %f\n",q_5);
        //     printf(" r_0= %f\n",r_0);
        //     printf(" r_1= %f\n",r_1);
        //     ros::param::set("pathfollow/dynamic_matrix_q0", q_0);
        //     ros::param::set("pathfollow/dynamic_matrix_q1", q_1);
        //     ros::param::set("pathfollow/dynamic_matrix_q2", q_2);
        //     ros::param::set("pathfollow/dynamic_matrix_q3", q_3);
        //     ros::param::set("pathfollow/dynamic_matrix_q4", q_4);
        //     ros::param::set("pathfollow/dynamic_matrix_q5", q_5);
        //     ros::param::set("pathfollow/dynamic_matrix_r0", r_0);
        //     ros::param::set("pathfollow/dynamic_matrix_r1", r_1);

        //     // my_gas = curent_gas;
        //     // my_brake = curent_brake;
        //     // recvStatusFlag = true;
        // }
    }
}

void udprecvstop() {
    // if(100 %20 ==0){
    int fa = 0;
    fa = socket(AF_INET, SOCK_DGRAM, 0);
    if (fa < 0) {
        std::cout << "failed" << std::endl;
    }

    struct sockaddr_in server_addr, cliaddr;
    bzero(&server_addr, sizeof(server_addr));  //目的ip 和端口
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(10242);

    // bzero(&cliaddr, sizeof(cliaddr)); //发送端ip和端口
    // cliaddr.sin_family = AF_INET;
    // cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // cliaddr.sin_port = htons(9091);
    // if (bind(fa, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) == -1) {

    //     std::cout<<"bind fail!"<<std::endl;
    // }

    char maxbuf = 0;
    char buf[maxbuf];
    memset(buf, 0, maxbuf);
    // memcpy(buf, &gcmd, sizeof(gcmd));
    sendto(fa, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    // printf("send success\n");
    close(fa);
    // }
}