/*
 * @Copyright: jinxiaoxin@whut.edu.cn
 * @Author: jinxiaoxin235
 * @Date: 2023-06-09 21:25:13
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2024-03-26 20:07:11
 * @FilePath: /miniEV_grad/src/pathfollower/src/controller.cpp
 */
#include "pathfollower/controller.h"

#include "assert.h"

namespace PathFollower {

bool ControlCommand::setCommand(double steering_angle, double linear_velocity) {
    steering_angle_ = steering_angle;
    linear_velocity_ = linear_velocity; 
    return true;

};//enable_steer_vel
bool ControlCommand::setCommand(double steering_angle, double linear_velocity, double linear_acceleration) {
    steering_angle_ = steering_angle;
    linear_velocity_ = linear_velocity;

    linear_acceleration_ = linear_acceleration;
    Enable_linear_acceleration_ = true;
    return true;

};//enable_steer_acc
bool ControlCommand::setCommand(double steering_angle, double linear_velocity, double linear_acceleration, double steering_speed) {
    steering_angle_ = steering_angle;
    linear_velocity_ = linear_velocity;

    linear_acceleration_ = linear_acceleration;
    Enable_linear_acceleration_ = true;

    steering_speed_ = steering_speed;
    Enable_steering_speed_ = true;
    return true;
};//enable_steer_rotate_acc


bool ControlCommand::setVehicleStop() {
    steering_angle_ = 0.0;
    linear_velocity_ = 0.0;

    linear_acceleration_ = -3.0;
    Enable_linear_acceleration_ = true;
    return true;
}; 
Controller::Controller(const std::string &vehicle_physical_config)
{   
    std::cout << vehicle_physical_config << std::endl;
    assert(this->physical_.initPhysical(vehicle_physical_config));
    
    std::vector<double> den(3, 0.0);
    std::vector<double> num(3, 0.0);
    Filter::LpfCoefficients(0.01, 10, &den, &num);
    // std::vector<double> den(2, 0.0);
    // std::vector<double> num(2, 0.0);
    // Filter::LpfCoefficients(0.02, 5, &den, &num);
    //一个十阶低通滤波器
    steeringcmd_losspass_filter_->set_coefficients(den, num);

    // std::cout << " 222222222222 \n";
    this->lateral_error_filter_ = Filter::MeanFilter(10);
    this->lateralRate_error_filter_ = Filter::MeanFilter(10);
    this->heading_error_filter_ = Filter::MeanFilter(10);
    this->headingRate_error_filter_ = Filter::MeanFilter(10);
    this->curvature_filter_ = Filter::MeanFilter(25);
    this->direction_filter_ = Filter::MeanFilter(500);

};


bool Controller::updateVehicleStatus(const smartcar_msgs::Location &cur_status, std::mutex &status_mutex) {
    std::lock_guard<std::mutex> _guard(status_mutex);
    cur_status_.cur_pos.point_.x = cur_status.global_pos.x;
    cur_status_.cur_pos.point_.y = cur_status.global_pos.y;
    cur_status_.cur_pos.point_.z = cur_status.global_pos.z;

    cur_status_.cur_pos.rpy_.x = NormalizeAngle( cur_status.orientation[0]);
    cur_status_.cur_pos.rpy_.y = NormalizeAngle(cur_status.orientation[1]);
    cur_status_.cur_pos.rpy_.z = NormalizeAngle(cur_status.orientation[2]);

    cur_status_.cur_pos.heading_ = cur_status.orientation[2];
    cur_status_.cur_pos.linear_velocity_ = cur_status.v_x;

    cur_status_.linear_vel.x = cur_status.v_x;
    cur_status_.linear_vel.y = cur_status.v_y;
    cur_status_.linear_vel.z = cur_status.v_z;

    cur_status_.linear_acc.x = cur_status.accel_x;
    cur_status_.linear_acc.y = cur_status.accel_y;
    cur_status_.linear_acc.z = cur_status.accel_z;

    cur_status_.rpy_rate.x = cur_status.rpy_rate[0];
    cur_status_.rpy_rate.y = cur_status.rpy_rate[1];
    cur_status_.rpy_rate.z = cur_status.rpy_rate[2];

    cur_status_.utm_vel.x = cur_status.global_speed[0];
    cur_status_.utm_vel.y = cur_status.global_speed[1];
    cur_status_.utm_vel.z = cur_status.global_speed[2];

    cur_status_.utm_acc.x = cur_status.accelerate[0];
    cur_status_.utm_acc.y = cur_status.accelerate[1];
    cur_status_.utm_acc.z = cur_status.accelerate[2];

    printf("The heading is %f \n", cur_status_.cur_pos.heading_ * 57.3);
    cur_status_.speed = std::sqrt(std::pow(cur_status_.linear_vel.x, 2) + 
    std::pow(cur_status_.linear_vel.y, 2) + std::pow(cur_status_.linear_vel.z, 2));
    // cur_status_.cur_pos.Quaternion2EulerAgnle(cur_pos.orientation);
    // cur_status_.cur_pos.heading_ = cur_status_.cur_pos.rpy_.z;
    // cur_status_.cur_pos.linear_velocity_ = cur_velocity;
    return true;
};
bool Controller::updateTarget(const geometry_msgs::PoseArray &follow_path, double target_velocity, std::mutex &path_mutex) {
    if (follow_path_.updateTrajectory(follow_path, path_mutex)) {
        target_velocity_ = target_velocity;
        return true;
    }
    return false;    
};

bool Controller::updateVehicleChassis(const smartcar_msgs::VehicleChassis &cur_chassis, std::mutex &chassis_mutex) {
    std::lock_guard<std::mutex> _guard(chassis_mutex);
    cur_chassis_.feedback_steering_angle = cur_chassis.feedback_steerAng;
    cur_chassis_.speed = cur_chassis.vehiclespeed/3.6;
    // cur_status_.cur_pos.linear_velocity_ = cur_chassis.vehiclespeed*3.6;

    return true;
};


bool Controller::Follow(const smartcar_msgs::Location &cur_status,  std::mutex &status_mutex, 
                const geometry_msgs::PoseArray &follow_path,  std::mutex &path_mutex,
                const smartcar_msgs::VehicleChassis &cur_chassis, std::mutex &chassis_mutex,
                double target_velocity, ControlCommand &cur_cmd) {
                            
        auto start_control = std::chrono::high_resolution_clock::now();
        if (this->updateVehicleStatus(cur_status, status_mutex) 
            && this->updateTarget(follow_path, target_velocity, path_mutex)
            && this->updateVehicleChassis(cur_chassis, chassis_mutex)) {
            if (this->FollowMethod(cur_cmd)) {
                auto end_control = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> cost_time = end_control - start_control;
                std::cout << "The ControlMethod cost time is: " << cost_time.count() << " ms" << std::endl;
                return true;
            } else {
                auto end_control = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> cost_time = end_control - start_control;
                std::cout << "The ControlMethod cost time is: " << cost_time.count() << " ms" << std::endl;
                std::cerr << "The ControlMethod get error: ... " << std::endl;
            }
        }
        return false;
};


size_t Controller::QueryNearestPoseFromXY(const Trajectory &path, const Pose &pose) const {
    size_t min_index = 0;
    Pose cur_pos = pose;
    if (path.poses_.size() > 2) {
        double d_min = cur_pos.getDistanceFromXY(path.poses_[0]);
        for (size_t i = 1; i < path.poses_.size(); ++i) {
            double d_temp = cur_pos.getDistanceFromXY(path.poses_[i]);
            if (d_temp - d_min > 0.00001) break;//减少查找次数，对于结构性道路效果较好，交叉道路可能会有问题 
            if (d_temp < d_min ) {
                d_min = d_temp;
                min_index = i;
            }
        }
    }
    return min_index;
}

double Controller::VelocityError2Accelerate(double vel_error, double sim_dt) const  {
    if (longitudinalvelocitypid_) {
        // std::cout << "The vel error is "<< vel_error << std::endl;
        return longitudinalvelocitypid_->Control(vel_error, sim_dt);
    } 
    std::cerr << "The Velocity PID isn't Init. " << std::endl;
    return 0.0;
};

double Controller::calcLateralError(const Pose &loca_pos, const Pose &nearest_pos) const {
       return -(nearest_pos.point_.x - loca_pos.point_.x )* std::sin(nearest_pos.heading_)
        + (nearest_pos.point_.y - loca_pos.point_.y ) * std::cos(nearest_pos.heading_);
};

bool VehiclePhysical::initPhysical(const std::string &vehicle_physical_config) {
    YAML::Node config = YAML::LoadFile(vehicle_physical_config);
    bool init = true;
    //缺少关键词，则赋值为-1.0，便于后面检查
    this->steer_ratio_ = config["steer_ratio"] ? config["steer_ratio"].as<double>() : -1.0;
    this->length_ = config["length"] ? config["length"].as<double>() : -1.0;
    this->width_ = config["width"] ? config["width"].as<double>() : -1.0;;
    this->height_ = config["height"] ? config["height"].as<double>() : -1.0;
    this->wheel_base_ = config["wheel_base"] ? config["wheel_base"].as<double>() : -1.0;
    this->rear_overhang_ = config["rear_overhang"] ? config["rear_overhang"].as<double>() : -1.0;;//后悬
    this->front_overhang_ = config["front_overhang"] ? config["front_overhang"].as<double>() : -1.0;//前悬
    this->mass_ = config["mass"] ? config["mass"].as<double>() : -1.0;;//kg
    this->cf_ = config["cf"] ? config["cf"].as<double>() : -1.0;//
    this->cr_ = config["cr"] ? config["cr"].as<double>() : -1.0;//侧偏刚度

    this->lf_mass_ = config["lf_mass"] ? config["lf_mass"].as<double>() : -1.0;
    this->lr_mass_ = config["lr_mass"] ? config["lr_mass"].as<double>() : -1.0;
    this->rf_mass_ = config["rf_mass"] ? config["rf_mass"].as<double>() : -1.0;
    this->rr_mass_ = config["rr_mass"] ? config["rr_mass"].as<double>() : -1.0;


    this->lf_ = config["lf"] ? config["lf"].as<double>() : -1.0;//前轮到重心
    this->lr_ = config["lr"] ? config["lr"].as<double>() : -1.0; //后轮到重心
    this->max_steering_angle_ = config["max_steering_angle"] ? config["max_steering_angle"].as<double>() : -1.0;//deg

    this->max_steering_angle_ = config["max_steering_angle"] ? config["max_steering_angle"].as<double>() : -1.0;//deg
    this->max_steering_speed_ = config["max_steering_speed"] ? config["max_steering_speed"].as<double>() : -1.0;//deg

    this->max_steering_angle_ = this->max_steering_angle_ / 180.0 * M_PI; //rad
    this->max_steering_speed_ = this->max_steering_speed_ / 180.0 * M_PI; //rad
    this->min_radius_turn_ =   this->max_steering_angle_ > 0.0 ? this->wheel_base_ / std::tan(max_steering_angle_ / this->steer_ratio_ ) : __DBL_MAX__;

    this->max_lon_acceleration_ = config["max_lon_acceleration"] ? config["max_lon_acceleration"].as<double>() : -1.0;//m/s2
    this->max_lon_deceleration_ = config["max_lon_deceleration"] ? config["max_lon_deceleration"].as<double>() : -1.0;//m/s2


    if (lf_ < 0.0) {
        this->lf_ = wheel_base_ * (1.0 - (lf_mass_ + rf_mass_)/ mass_);
        this->lr_ = wheel_base_ * (1.0 - (lr_mass_ + rr_mass_)/ mass_);
    }

    this->front_mass_ = (1.0 - lf_ / wheel_base_ ) * mass_;
    this->rear_mass_ = (1.0 - lr_ / wheel_base_ ) * mass_;

    this->iz_ = this->lf_ * this->lf_ * this->front_mass_ + this->lr_ * this->lr_ * this->rear_mass_;

    if (this->steer_ratio_ < -0.01) {
        fprintf(stderr, "The Vehicle steer_ratio_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle steer_ratio_ is %f  .\n", this->steer_ratio_);
    }
    if (this->length_ < -0.01) {
        fprintf(stderr, "The Vehicle length_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle length_ is %f m .\n", this->length_);
    }
    if (this->width_ < -0.01) {
        fprintf(stderr, "The Vehicle width_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle width_ is %f m .\n", this->width_);
    }
    if (this->height_ < -0.01) {
        fprintf(stderr, "The Vehicle height_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle height_ is %f m .\n", this->height_);
    }
    if (this->wheel_base_ < -0.01) {
        fprintf(stderr, "The Vehicle wheel_base_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle wheel_base_ is %f m .\n", this->wheel_base_);
    }
    
    if (this->rear_overhang_ < -0.01) {
        fprintf(stderr, "The Vehicle rear_overhang_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle rear_overhang_ is %f m .\n", this->rear_overhang_);
    }
    if (this->front_overhang_ < -0.01) {
        fprintf(stderr, "The Vehicle front_overhang_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle front_overhang_ is %f m .\n", this->front_overhang_);
    }
    if (this->mass_ < -0.01) {
        fprintf(stderr, "The Vehicle mass_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle mass_ is %f kg .\n", this->mass_);
    }
    if (this->max_steering_angle_ < -0.01) {
        fprintf(stderr, "The Vehicle max_steering_angle_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle max_steering_angle_ is %f ° .\n", this->max_steering_angle_);
        printf("The Vehicle min_radius_turn_ is %f m .\n", this->min_radius_turn_);
    }
    if (this->cf_ < -0.01) {
        fprintf(stderr, "The Vehicle cf_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle cf_ is %f  .\n", this->cf_);
    }
    if (this->cr_ < -0.01) {
        fprintf(stderr, "The Vehicle cr_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle cr_ is %f  .\n", this->cr_);
    }
    if (this->lf_ < -0.01) {
        fprintf(stderr, "The Vehicle lf_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle lf_ is %f m .\n", this->lf_);
    }
    if (this->lr_ < -0.01) {
        fprintf(stderr, "The Vehicle lr_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle lr_ is %f m .\n", this->lf_);
        printf("The Vehicle front_mass_ is %f kg .\n", this->front_mass_);
        printf("The Vehicle rear_mass_ is %f kg .\n", this->rear_mass_);
    }
    if (this->max_lon_acceleration_ < -0.01) {
        fprintf(stderr, "The Vehicle max_lon_acceleration_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle max_lon_acceleration_ is %f m/s2 .\n", this->max_lon_acceleration_);
    }
    if (this->max_lon_deceleration_ < -0.01) {
        fprintf(stderr, "The Vehicle max_lon_deceleration_ is missing .\n");
        init  = false;
    } else {
        printf("The Vehicle max_lon_deceleration_ is %f m/s2 .\n", this->max_lon_deceleration_);
    }
    if (!init) {
        fprintf(stderr, "The Vehicle init wrong....................Goto Break!\n");
        return false;
    } 
    std::cout << "The VehiclePhysicalConfig was loaded successfully! " << std::endl;
    return true;
};

}//PathFollower