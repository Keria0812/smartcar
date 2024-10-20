/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-04-24 14:33:36
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-27 04:04:37
 * @FilePath: /miniEV_grad/src/vehicle_controlev/src/main.cpp
 */
#include "EVcontroller.h"
#include <iostream>
#include <ros/ros.h>
#include <thread>
#include <string>
#include <array>
#include <fstream>

#include "../src/PIDController.hpp"

#include <smartcar_msgs/VehicleStatus.h>
#include <smartcar_msgs/VehicleLocation.h>
// // #include <pathfollower/common.h>
// #include <

#include <smartcar_msgs/VehicleCmd.h>
#include <smartcar_msgs/ControlCommandStamped.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <mutex>
#include <nav_msgs/Odometry.h>
#include <smartcar_msgs/Location.h>
#include <smartcar_msgs/VehicleChassis.h>
#include <std_msgs/Float32.h>
#include <can_msgs/Frame.h>

#include <yaml-cpp/yaml.h>


#include "filters/digital_filter.h"
#include "filters/digital_filter_coefficients.h"
#include "filters/mean_filter.h"

bool isGetVehiclChassis = false;
std::mutex vehicle_chassis;
std::mutex location_mutex;

bool location_update = false;
std::unique_ptr<Filter::DigitalFilter> acc_losspass_filter_ = std::make_unique<Filter::DigitalFilter>();
std::unique_ptr<Filter::MeanFilter> acc_mean_filter_ = std::make_unique<Filter::MeanFilter>(60);

static double cur_driver = 0.0;
// Filter::MeanFilter acc_mean_filter_;


smartcar_msgs::VehicleChassis vehiclechassis_ev;
smartcar_msgs::Location cur_location;
enum EVID {
    Whell_Speed = 0x305,
    VCU_Vehicle_Status = 0x304,
    VCU_Vehicle_Diagnosis = 0x301,
    Vehicle_Status_BMS = 0x303,
    Vehicle_Status_FeedBack = 0x302,

    Vehicle_Control_Flag = 0x501,
    Vehicle_Control_Light = 0x506,
    Vehicle_Control_Gas = 0x504,
    Vehicle_Control_Brake = 0x503,
    Vehicle_Control_TireSteer = 0x502,
};

std::array<std::string, 3> ControlMode = {"LatLon", "Lat", "Lon"};

std::string CtrlMode = ControlMode[0];

struct VehicleEVCMD {
    double gas = 0.0;
    double brake_ = 0.0;
    double tire_steer_ = 0.0;
    double target_vel_ = 0.0;
    double target_acceleration_ = 0.0;
    int gear = 0;
}cur_cmd;

struct VehicleDignosis {
    bool remote_state = 0;
    bool iECU_state = 0;
    bool DBS_state = 0;
    bool steer_state = 0;
    bool eme_stop_state = 0;
}dignosis;

struct MotorBMS {
    int motor_speed = 0;
    double motor_power = 0.0;
    int BMS_SOC = 0;
    double BMSCurr = 0.0;
    double BMSVol = 0.0;
}motorbms;

struct VehicleFeedBack {
    int BrakeLight_State = 0;
    int WireAcc_Pedal_Pos = 0;
    double Vehicle_Torque = 0.0;
    int OriginalAcc_PedalPos = 0;
    int BrakPedal_Status = 0;
    int MCU_Vol = 0;
    int MCU_Cur = 0;
    int MCU_Temp = 0;
}vehicle_chassis_feedback;

void VehicleCMDCallBack(const smartcar_msgs::ControlCommandStamped::ConstPtr &msg) {
    // if (msg->cmd.linear_velocity > 0.0000000001) {
    //     cur_cmd.gas = 
    // }
    
    cur_cmd.tire_steer_ = msg->cmd.steering_angle * 57.3;
    // std::cout << "111111111111111111111111111 " <<  cur_cmd.tire_steer_ << std::endl;
    cur_cmd.target_vel_ = msg->cmd.linear_velocity;//m/s
    cur_cmd.target_acceleration_ = msg->cmd.linear_acceleration;
    if (cur_cmd.target_acceleration_ > 2.0) cur_cmd.target_acceleration_ = 2.0;
    if (cur_cmd.target_acceleration_ < -2.5) cur_cmd.target_acceleration_ = -2.5;
    return ;
};
class LowPassFilter {
public:
    LowPassFilter(float frequency, float sample_time) : 
        alpha_(2 * M_PI * frequency * sample_time / (1 + 2 * M_PI * frequency * sample_time)),
        output_(0)
    {}

    float filter(float input) {
        output_ = alpha_ * input + (1 - alpha_) * output_;
        return output_;
    }

private:
    const float alpha_;
    float output_;
};

float frequency = 10;    // 截止频率为10 Hz
float sample_time = 0.02; // 采样时间为0.01 s
LowPassFilter filter(frequency, sample_time);
LowPassFilter filteracc(frequency, sample_time);

auto start_time_vehicle = std::chrono::system_clock::now();

void VehicleChassisCallBack(const can_msgs::Frame::ConstPtr &msg) {
        // std::cout << "Get The VehicleChassis INFO!" << msg->id << std::endl;

    switch (msg->id)
    {
    case Whell_Speed : {
        vehiclechassis_ev.wheelspeed[0] = double((uint16_t)((msg->data[1] ) << 8 | (uint16_t)(msg->data[0]))) * 0.1 ;
        vehiclechassis_ev.wheelspeed[1] = double((uint16_t)((msg->data[3] ) << 8 | (uint16_t)(msg->data[2]))) * 0.1 ;
        vehiclechassis_ev.wheelspeed[2] = double((uint16_t)((msg->data[5] ) << 8 | (uint16_t)(msg->data[4]))) * 0.1 ;
        vehiclechassis_ev.wheelspeed[3] = double((uint16_t)((msg->data[7] ) << 8 | (uint16_t)(msg->data[6]))) * 0.1 ;// km/h
        // vehiclechassis_ev.wheelspeed[0] = double((uint16_t)((msg->data[1] & 0x7F) << 8 | (uint16_t)(msg->data[0]))) * 0.1 ;
        // vehiclechassis_ev.wheelspeed[1] = double((uint16_t)((msg->data[3] & 0x7F) << 8 | (uint16_t)(msg->data[2]))) * 0.1 ;
        // vehiclechassis_ev.wheelspeed[2] = double((uint16_t)((msg->data[5] & 0x7F) << 8 | (uint16_t)(msg->data[4]))) * 0.1 ;
        // vehiclechassis_ev.wheelspeed[3] = double((uint16_t)((msg->data[7] & 0x7F) << 8 | (uint16_t)(msg->data[6]))) * 0.1 ;// km/h
        // std::cout << "The Tire Speed is :" << std::endl;
        // std::cout << "The FL : is " <<  vehiclechassis_ev.wheelspeed[0] << " km/h!" << std::endl;
        // std::cout << "The FR : is " <<  vehiclechassis_ev.wheelspeed[1] << " km/h!" << std::endl;
        // std::cout << "The RL : is " <<  vehiclechassis_ev.wheelspeed[2] << " km/h!" << std::endl;
        // std::cout << "The RR : is " <<  vehiclechassis_ev.wheelspeed[3] << " km/h!" << std::endl;
        std::cout << std::endl;
        break;
    }
    case VCU_Vehicle_Status : {

        auto elapsed_time1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time_vehicle).count();
        // std::cout << "The Simple Time is : " << elapsed_time1 << " ms!" << std::endl;
        
        vehiclechassis_ev.vehiclespeed = double((uint16_t)((msg->data[1] ) << 8 | (uint16_t)(msg->data[0]))) * 0.1 - 80.0; //km/h
        vehiclechassis_ev.vehiclespeed = filter.filter(vehiclechassis_ev.vehiclespeed);

        vehiclechassis_ev.feedback_brake_press = double((uint16_t)((msg->data[3]) << 8 | (uint16_t)(msg->data[2]))) * 0.1 ; //8.0 Mpa
        vehiclechassis_ev.feedback_tireAng = double((uint16_t)((msg->data[5]) << 8 | (uint16_t)(msg->data[4]))) * 0.1 - 40.0;//deg,tire
        int gear = (uint16_t)(msg->data[6]);
        switch (gear)
        {
        case 0: { vehiclechassis_ev.gear = 'N';break;}
        case 1: { vehiclechassis_ev.gear = 'D';break;}
        case 2: { vehiclechassis_ev.gear = 'R';break;}
        case 3: { vehiclechassis_ev.gear = 'P';break;}   
        default: break;
        }
        // std::cout << "The VCU_Vehicle_Speed : is " <<  vehiclechassis_ev.vehiclespeed << " km/h!" << std::endl;


        vehiclechassis_ev.vcu_mode = (uint16_t)(msg->data[7] & 7) ;
        vehiclechassis_ev.light_state.car_light = (uint16_t)(msg->data[7] >> 3 & 3);
        vehiclechassis_ev.light_state.turn_light = (uint16_t)(msg->data[7] >> 5 & 7);
        // std::cout << "The Gear is " << vehiclechassis_ev.gear << " , && We are on " ;
        // switch (vehiclechassis_ev.vcu_mode) {
        //     case 0 : { std::cout << "Manual Driving! \n" ;break;}
        //     case 1 : { std::cout << "IECU MOde     ! \n" ;break;}
        //     case 2 : { std::cout << "Remote Driving! \n" ;break;}
        //     case 3 : { std::cout << "Auto Streer ! \n" ;break;}
        //     case 4 : { std::cout << "Auto Longitu! \n" ;break;}
        // }
        // std::cout << "The Feedback_brake_press is " << vehiclechassis_ev.feedback_brake_press << " Mpa, " 
        // << "Feedback_tireAng is " << vehiclechassis_ev.feedback_tireAng << " °！" <<  std::endl;
        // std::cout << "The Turn Light is " ;
        // switch (vehiclechassis_ev.light_state.turn_light) {
        //     case 0 : { std::cout << "Keep Middle! \n" ;break;}
        //     case 1 : { std::cout << "Turn Left  ! \n" ;break;}
        //     case 2 : { std::cout << "Turn Right ! \n" ;break;}
        // }
        // std::cout << "The Car Front Light is ";
        // switch (vehiclechassis_ev.light_state.car_light) {
        //     case 0 : { std::cout << "Close           ! \n" ;break;}
        //     case 1 : { std::cout << "Clearrance lamp ! \n" ;break;}
        //     case 2 : { std::cout << "Dipped Light    ! \n" ;break;}
        //     case 3 : { std::cout << "Heightlight on full beam! \n" ;break;}
        // }
        start_time_vehicle = std::chrono::system_clock::now();

        break;
    }
    case VCU_Vehicle_Diagnosis : {
        dignosis.eme_stop_state = (uint16_t)(msg->data[0]);
        dignosis.steer_state = (uint16_t)(msg->data[1]);
        dignosis.DBS_state = (uint16_t)(msg->data[2]);
        dignosis.iECU_state = (uint16_t)(msg->data[4]);
        dignosis.remote_state =(uint16_t)(msg->data[3]);

        // if (dignosis.remote_state) ROS_WARN("The remote_ctrl_signal is lost!");
        // if (dignosis.steer_state) ROS_WARN("The steer_signal is lost!");
        // if (dignosis.iECU_state) ROS_WARN("The iECU_signal is lost!");
        // if (dignosis.DBS_state) ROS_WARN("The DBS_signal is lost!");
        // if (dignosis.eme_stop_state) ROS_WARN("We hit the emergency stop switch!");
        // dignosis.
        break;
    }
    case Vehicle_Status_BMS : {
        motorbms.BMSVol = double((uint16_t)((msg->data[1] & 0x1F) | (uint16_t)(msg->data[0]))) * 0.1;
        motorbms.BMSCurr = double((uint16_t)((msg->data[3] & 0xF)) | (uint16_t)(msg->data[2] << 3) | (uint16_t)(msg->data[1] >> 5)) * 0.1 - 1000.0;
        motorbms.BMS_SOC = int((uint16_t)((msg->data[4] & 0xF) | (uint16_t)(msg->data[3] >> 4)));
        motorbms.motor_power = double((uint16_t)(msg->data[5] & 0x7F) | (uint16_t)(msg->data[4] >> 4)) * 0.1 - 102.0;
        motorbms.motor_speed = int(((uint16_t)(msg->data[7]  & 0x3F) | (uint16_t)(msg->data[6] << 1) | (uint16_t)(msg->data[5] >> 7)));

        // std::cout << "The MUC_Motor_Speed is " <<  motorbms.motor_speed << " rpm !" << std::endl;
        // std::cout << "The motor_power     is " <<  motorbms.motor_power << " kw  !" << std::endl;
        // std::cout << "The MUC_Motor_Speed is " <<  motorbms.motor_speed << " !" << std::endl;
        // std::cout << "The MUC_Motor_Speed is " <<  motorbms.motor_speed << " !" << std::endl;

        break;
    }
    case Vehicle_Status_FeedBack : {
        // std::cout << "Get The VehicleChassis Vehicle_Status_FeedBack!" << msg->id << std::endl;
        vehicle_chassis_feedback.MCU_Temp = (uint16_t)(msg->data[0]);
        vehicle_chassis_feedback.MCU_Cur = (uint16_t)(msg->data[1]) | (uint16_t)(msg->data[2] & 7 << 8) - 1023;
        vehicle_chassis_feedback.MCU_Vol =  (uint16_t)(msg->data[3] & 0x1F) | (uint16_t)(msg->data[2] >> 3);
        vehicle_chassis_feedback.BrakPedal_Status =  (uint16_t)(msg->data[3] >> 6) & 1;
        vehicle_chassis_feedback.OriginalAcc_PedalPos = (uint16_t)(msg->data[4]);
        vehicle_chassis_feedback.Vehicle_Torque = ((uint16_t)(msg->data[5]) | (uint16_t)((msg->data[3] & 0xF) << 8)) * 0.25 - 511.0;
        vehicle_chassis_feedback.WireAcc_Pedal_Pos = (uint16_t)(msg->data[7]);
        vehicle_chassis_feedback.BrakeLight_State = (uint16_t)(msg->data[3] >> 5) & 1;

        // std::cout << "Vehicle_Status_FeedBack : " << std::endl;

        // if (vehicle_chassis_feedback.BrakPedal_Status) std::cout << "The Brake is hit !" << std::endl; 
        // if (vehicle_chassis_feedback.BrakeLight_State) std::cout << "The BrakeLight is light !" << std::endl; 
//jiasu0.5， 减速0.33 0.54
        // std::cout << "The Gas      is %" << vehicle_chassis_feedback.OriginalAcc_PedalPos << " !" << std::endl;
        // std::cout << "The Wire Gas is %" << vehicle_chassis_feedback.WireAcc_Pedal_Pos << " !" << std::endl;

        break;
    }
    
    default:
        break;
    }

    isGetVehiclChassis = true;
};
void control(const VehicleEVCMD &ctrl_cmd, ros::Publisher &pub) {

    can_msgs::Frame frame_flag;
    can_msgs::Frame frame_gas;
    can_msgs::Frame frame_brake;
    can_msgs::Frame frame_tire_steer;
    can_msgs::Frame frame_light;

    bool enable_steer = false;
    bool enable_gas = false;
    bool enable_brake = false;

    if (CtrlMode == ControlMode[0]) {
        enable_steer = true;
        enable_gas = true;
        enable_brake = true;
    } else if (CtrlMode == ControlMode[1]) {
        enable_steer = true;
        enable_gas = false;
        enable_brake = false;
    } else if (CtrlMode == ControlMode[2]) {
        enable_steer = false;
        enable_gas = true;
        enable_brake = true;
    } else {
        ROS_WARN("The CtrlMode is wrong!");
    }

    frame_flag.id = Vehicle_Control_Flag;
    frame_flag.dlc = 8;
    frame_flag.data[0] = 1;
    pub.publish(frame_flag);

    // if (ctrl_cmd.brake_ > 0.000000000000001) ctrl_cmd.gas = 0.0;

    
    


    frame_gas.id = Vehicle_Control_Gas;
    frame_gas.dlc = 8;
    frame_gas.data[0] = enable_gas;
    // frame.data[3] = cur_cmd.gear;//0空挡、1前进档、2倒车档
    frame_gas.data[3] = 1;//0空挡、1前进档、2倒车档
    frame_gas.data[5] =  (uint16_t)((ctrl_cmd.gas / 0.01) / 0.01) & 255;
    frame_gas.data[6] =  (uint16_t)((ctrl_cmd.gas / 0.01) / 0.01) >> 8;
    pub.publish(frame_gas);

    frame_brake.id = Vehicle_Control_Brake;
    frame_brake.dlc = 8;
    frame_brake.data[0] = enable_brake;
    frame_brake.data[1] = (uint16_t)(ctrl_cmd.brake_ / 0.01);
    pub.publish(frame_brake);

    frame_tire_steer.id = Vehicle_Control_TireSteer;
    frame_tire_steer.dlc = 8;
    frame_tire_steer.data[0] = enable_steer;
    frame_tire_steer.data[1] =  10;
    frame_tire_steer.data[4] =  (uint16_t) ( (ctrl_cmd.tire_steer_ + 30.0) / 0.1 ) & 255 ;
    frame_tire_steer.data[5] =  (uint16_t) ( (ctrl_cmd.tire_steer_ + 30.0) / 0.1 ) >> 8;
    pub.publish(frame_tire_steer);


    frame_light.id = Vehicle_Control_Light;
    frame_light.dlc = 8;
    frame_light.data[0] = 128;
    frame_light.data[1] = 0;
    pub.publish(frame_light);

    // //
    // std::cout << "The steer CMD is " << ctrl_cmd.tire_steer_ << std::endl;
    // std::cout << "The Gas  is " << ctrl_cmd.gas << "The Brake is " << ctrl_cmd.brake_ << std::endl;
    // std::cout << "TargetAcc " << cur_cmd.target_acceleration_ << std::endl;

    

}

void LocationCallback(const smartcar_msgs::Location &msg) {
    std::lock_guard<std::mutex> _guard(location_mutex);
    cur_location = msg;
    location_update = true;
};

void mainback(ros::NodeHandle nh)
{
    ros::Subscriber sub_vehicleCMD_data = nh.subscribe<smartcar_msgs::ControlCommandStamped>("ctrl_cmd", 100, &VehicleCMDCallBack);
    ros::Subscriber sub_can0recv_data = nh.subscribe<can_msgs::Frame>("can0_received_messages", 100, &VehicleChassisCallBack);
    ros::Subscriber sub_location_ = nh.subscribe("smartcar/location", 1, &LocationCallback);
    ros::MultiThreadedSpinner spinner(3);
    spinner.spin();
}
void calibrated(ros::NodeHandle nh) {
    double a[2] = {0};  //初始化数组

    while (ros::ok()) {
    std::cout << "The Gas  is " << cur_driver << std::endl;
        std::cout << "请输入 油门[0-1] 刹车[0-1]\n";
        for (int i = 0; i < 2; ++i)  //输入
        {
            std::cin >> a[i];
        }
        cur_driver = a[0] - a[1];
    }

}

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "vehicle_controlEV");
    // EVcontroller control_EV;
    ros::NodeHandle nh, nh_param("~");
    // nh_param.param<double>("driver_cali", cur_driver, "0.0");
    // ros::param::get("driver_cali", cur_driver);


    ros::Publisher pub_VehicleStatus_ = nh.advertise<smartcar_msgs::VehicleStatus>("VehicleStatus", 10);
    ros::Publisher pub_chassis_ = nh.advertise<smartcar_msgs::VehicleChassis>("smartcar/chassis", 10);
    // ros::Publisher pub_driver_ = nh.advertise<std_msgs::Float32>("smartcar/driver", 10);


    ros::Publisher pub_VehicleCMD = nh.advertise<can_msgs::Frame>("/can0_sent_messages", 10);
    // PIDController * EVDriverPID = new PIDController(0.05, 0.0, 0.05,
                                    // 0.5, -0.8, 0.3, -0.5);
    // PIDController * EVDriverPID = new PIDController(0.1, 0.2, 0.01,
    //                                                 1.0, -1.0, 1.0, -1.0);
    //  PIDController * EVDriverPID = new PIDController(0.1, 0.00250, 0.000,
    //                                                 0.20, -00.20, 0.10, -0.10);
    PIDController * EVDriverPID = new PIDController(0.05, 0.12, 0.01,
                                                    1.0, -1.20, 1.0, -1.0);
    PIDController * EVDriverPIDde = new PIDController(0.005, 0.01, 0.00,
    1.0, -1.20, 1.0, -1.0);

    PIDController * EVSpeedPID = new PIDController(0.01, 0.05, 0.0,
    0.03, 0.0, 0.03, -0.03);

    // PIDController * EVSpeedPID = new PIDController(0.04, 0.0005, 0.00,
    // 0.4, -1.0, 0.4, -1.0);

    std::ifstream file("/home/xining095/Carmaker/smartcar/miniEV_grad/calibration_table.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return -1;
    }
    // std::ofstream * my_samplefile_;
    // std::string caliname = "/home/jinxiaoxin/master_graduation/miniEV/Calc/jiasu.txt";
    // std::ofstream my_samplefile (caliname,std::ios::app|std::ios::out|std::ios::in );
    // if(my_samplefile.fail()){
    //    std::cout<<"打开文件错误!"<<std::endl;
    //    return -1;
    // }
    // my_samplefile_ = &my_samplefile;
    // *my_samplefile_<< "CMDdriver" << "\t"<< "GasFeedback" << "\t" << "BrakeFeedback" << 
    // "\t" <<"AccY" << "\t" << "AccX" << "\t" << "ChassisSpeed" << "\t" << "GpsSpeed"  <<"\n";
// std::unique_ptr<Filter::DigitalFilter> acc_losspass_filter_ = std::make_unique<Filter::DigitalFilter>();
// std::unique_ptr<Filter::MeanFilter> acc_mean_filter_ = std::make_unique<Filter::MeanFilter>(4);

    std::vector<double> den(3, 0.0);
    std::vector<double> num(3, 0.0);
    Filter::LpfCoefficients(0.01, 10, &den, &num);
    // std::vector<double> den(2, 0.0);
    // std::vector<double> num(2, 0.0);
    // Filter::LpfCoefficients(0.02, 5, &den, &num);
    //一个十阶低通滤波器
    acc_losspass_filter_->set_coefficients(den, num);

    // std::cout << " 222222222222 \n";
    // acc_mean_filter_ = Filter::MeanFilter(10);

    int num_rows = 60;
    int num_cols = 450;
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
    // YAML::Node config = YAML::LoadFile("");
    int control_modeFlag = 1;
    // FLAGS_trajectory_time_resolution = config["FLAGS_trajectory_time_resolution"].as<double>();

    nh_param.param("control_mode", control_modeFlag, int(0));//0，横纵向控制，1，横向控制，2，纵向控制
    nh_param.param("driver_cali", cur_driver, double(0.0));//0，横纵向控制，1，横向控制，2，纵向控制

    CtrlMode = ControlMode[control_modeFlag];
    // std::cout << control_modeFlag <<std::endl;

    std::thread t(mainback, nh);
    std::thread t_cal(calibrated, nh);

    ros::Rate loop(100);
    auto start_time = std::chrono::system_clock::now();

    double g_A = 0;

    while (ros::ok()) {
            // double cmd_gA = 1.5 * std::sin(g_A);
            // g_A += M_PI / 1750;
        // if (location_update) {
            auto start_time1 = std::chrono::system_clock::now();
            smartcar_msgs::VehicleChassis cur_chassis;
            cur_chassis.header.stamp = ros::Time::now();
            cur_chassis.vehiclespeed = vehiclechassis_ev.vehiclespeed;
            cur_chassis.feedback_steerAng = vehiclechassis_ev.feedback_tireAng / 180.0 * M_PI;
            cur_chassis.feedback_gas = vehicle_chassis_feedback.OriginalAcc_PedalPos;
            cur_chassis.feedback_brake_press = vehiclechassis_ev.feedback_brake_press;
            
            isGetVehiclChassis = false;
            location_update = false;
            cur_cmd.gear = 0;
            double cur_speed = vehiclechassis_ev.vehiclespeed; //km/h
            // double cur_speed = (vehiclechassis_ev.wheelspeed[0] + vehiclechassis_ev.wheelspeed[1] + vehiclechassis_ev.wheelspeed[2] + vehiclechassis_ev.wheelspeed[3]) / 4.0;
            // double target_speed = 20.0;//km/h
            double target_speed = cur_cmd.target_vel_ * 3.6;//km/h
            double cur_driver = 0.0;
            // cur_chassis.feedback_Motor_rotv = acc_losspass_filter_->Filter(cur_location.accel_y);
            // cur_chassis.feedback_torque = acc_mean_filter_->Update(cur_location.accel_y);
            // // cur_driver = EVDriverPID->Update(cur_cmd.target_acceleration_,filteracc.filter(cur_location.accel_y) );
            // if (cur_cmd.target_acceleration_ > 0.0)
            //     cur_driver = EVDriverPID->Update(cur_cmd.target_acceleration_,cur_chassis.feedback_torque);
            // else {
            //     if (cur_chassis.vehiclespeed <= 0.5) cur_driver = 0.1;
            //     else cur_driver = EVDriverPIDde->Update(cur_cmd.target_acceleration_,cur_chassis.feedback_torque);
            // }
            // if (cur_speed > 55 && cur_driver > 0.0) cur_driver = -cur_driver/5.0;

           

            // cur_driver = EVSpeedPID->Update(target_speed, cur_speed);
            ROS_INFO("The VehicleCurSpeed is %f km/h, The TargetSpeed is %f km/h, The cur_driver is %f \n!", cur_speed, target_speed, cur_driver);
            // ROS_INFO("The g_A is %f km/h, The feedback_gas is %f , The feedback_brake_press is %f \n!", cur_cmd.target_acceleration_, cur_chassis.feedback_gas, cur_chassis.feedback_brake_press);
            if (cur_cmd.target_acceleration_ <= -0.2) cur_cmd.target_acceleration_ += std::sin(cur_location.orientation[1]) ;
            int index_acc = (int)std::floor((cur_cmd.target_acceleration_ + 2.5)/0.01);
            index_acc = std::min(449, index_acc);
            index_acc = std::max(0, index_acc);

            cur_driver = calibration_table[(int)std::floor(cur_speed)][index_acc];
            cur_driver += EVSpeedPID->Update(cur_cmd.target_acceleration_, cur_location.accel_y);

            std::cout << std::fixed << std::setprecision(4) << cur_driver << "\t"<< cur_chassis.feedback_gas << "\t"
            << cur_chassis.feedback_brake_press << "\t" << cur_location.accel_y << "\t" << cur_location.accel_x << "\t" 
            << cur_chassis.vehiclespeed << "\t" << cur_location.speed * 3.6  <<"\n";
            // // std::cout << calibration_table.size() << " " << calibration_table[0].size() << std::endl;
            //  if (cur_speed != 0.0)
            // // *my_samplefile_<< std::fixed << std::setprecision(4) << cur_driver << "\t"<< cur_chassis.feedback_gas << "\t"
            // // << cur_chassis.feedback_brake_press << "\t" << cur_location.accel_y << "\t" << cur_cmd.target_acceleration_ << "\t" 
            // // << cur_chassis.vehiclespeed << "\t" << cur_location.speed * 3.6  <<"\n";

            // *my_samplefile_<< std::fixed << std::setprecision(4) << cur_driver << "\t"<< cur_chassis.feedback_gas << "\t"
            // << cur_chassis.feedback_brake_press << "\t" << cur_location.accel_y << "\t" << cur_location.accel_x << "\t" 
            // << cur_chassis.vehiclespeed << "\t" << cur_location.speed * 3.6  <<"\n";
            // cur_driver = cur_cmd.target_acceleration_;
            // cur_driver = std::max( cur_driver, -1.0);
            // cur_driver = std::min( cur_driver, 1.0);
            
            // cur_driver = 0.15;
            if (cur_driver > 0.0) {
                cur_cmd.gear = 1;
                cur_cmd.gas = cur_driver;
                cur_cmd.brake_ = 0.0;
            } else {
                cur_cmd.gear = 1;
                cur_cmd.brake_ = -cur_driver;
                cur_cmd.gas = 0.0;
            }
            
            control(cur_cmd, pub_VehicleCMD);
            cur_chassis.cmd_gas = cur_driver;
            
            pub_chassis_.publish(cur_chassis);
            // std_msgs::Float32 ddd = static_cast<std_msgs::Float32>(cur_driver) ;
            // pub_driver_.publish(aa);
            auto elapsed_time1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time1).count();
            // std::cout << "The plot cost : " << elapsed_time1 << " s!" << std::endl;
        // }
        loop.sleep();
    }
    // my_samplefile.close();

    // t_cal.join();
    t.join();
    return 0;

};