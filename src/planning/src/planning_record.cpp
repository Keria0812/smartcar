#include "planning_record.h"


PlanningConf Config_;  //配置文件读取

//全局变量
std::vector<Obstacle> AllObstacle;  //感知一帧识别到的所有障碍物
smartcar_msgs::DetectedObjectArray msg_AllObstacle;
std::pair<vector<double>, vector<double>> reference_path;  //参考路径点位置（x,y）
std::vector<ReferencePoint> reference_points;              //参考路径点参数
smartcar_msgs::My_Trajectory sub_reference_line_msg;
smartcar_msgs::My_Trajectory sub_reference_line;
geometry_msgs::Pose start_pose_;    //起点
geometry_msgs::Pose goal_pose_;     //终点
smartcar_msgs::Location sub_odom_;  // odom
bool cango;                         //判断车是否需要局部规划
bool canend;                        //判断局部规划的轨迹是否到达终点
bool update_init_lon;               //更新参考线
bool messege1;                      //控制发布一次的变量
bool messege2;                      //控制发布一次的变量
std::string log_file_name_;
double init_lon_state;              //初始弧长
Eigen::Vector3d origin_mgrs_point;  //地图MGRS的原点
// CubicSpline2D *csp;                                       //样条插值函数
std::vector<double> accumulated_s;  //纵向距离
bool acc_update = false;
std::mutex  cur_acc_mutex;
ros::Subscriber sub_acc_target_;
smartcar_msgs::ACCTarget cur_acc_target;
ros::Subscriber sub_vehicleCMD_data_;
double cmd_steering_angle;
double cmd_velocity;
double cmd_acc;
void writeCsvFile(const std::string& filename, const std::vector<TrajFeature> &trajFeatures, int numTrajFeatures, const std::string& vehicleId,  const std::string& frameid) {
    // 打开CSV文件
    std::ofstream csvFile(filename, std::ios::app);

    // 写入表头
    csvFile << "Vehicle ID" << ","
            << "Frame ID" << ","
            << "Lat Offset Cost" << ","
            << "Lat Comfort Cost" << ","
            << "Lon Objective Cost" << ","
            << "Lon Comfort Cost" << ","
            << "Lon Collision Cost" << ","
            << "Centripetal Acc Cost" << ","
            << "Speed Cost" << ","
            << "Dist Travelled Cost" << ","
            << "Human Likeness" << ","
            << "Is Collision" << ","
            << "Lat Offset" << ","
            << "Target Speed" << ","
            << "Length S" << ","
            << "Length Time" << std::endl;

    // 写入数据
    for (int i = 0; i < numTrajFeatures; i++) {
        csvFile << vehicleId << ","
                << frameid << ","
                << trajFeatures[i].lat_offset_cost << ","
                << trajFeatures[i].lat_comfort_cost << ","
                << trajFeatures[i].lon_objective_cost << ","
                << trajFeatures[i].lon_comfort_cost << ","
                << trajFeatures[i].lon_collision_cost << ","
                << trajFeatures[i].centripetal_acc_cost << ","
                << trajFeatures[i].speed_cost << ","
                << trajFeatures[i].dist_travelled_cost << ","
                << trajFeatures[i].human_likeness << ","
                << trajFeatures[i].is_collision << ","
                << trajFeatures[i].lat_offset << ","
                << trajFeatures[i].target_speed << ","
                << trajFeatures[i].length_s << ","
                << trajFeatures[i].length_time << std::endl;
    }
    csvFile << vehicleId << ","
                << frameid << ","
                << 0 << ","
                << 0 << ","
                << 0 << ","
                << 0 << ","
                << 0 << ","
                << 0 << ","
                << 0 << ","
                << 0 << ","
                << 0<< ","
                << 0 << ","
                << 0 << ","
                << 0 << ","
                << 0 << ","
                << 0 << std::endl;

    // 关闭CSV文件
    csvFile.close();
}


void writeTraingData(const std::string& filename, const std::vector<std::vector<double>> &traingingdata, const std::string& vehicleId,  const std::string& frameid) {
    // 打开CSV文件
    std::ofstream csvFile(filename, std::ios::app);
    // 写入表头
    if (traingingdata.size() == 0) return;
    // std::cout << filename << std::endl;
    // printf("%ld the Traing data size %ld:" , traingingdata.size(), traingingdata[0].size());
    for (auto it : traingingdata) {
        for (auto iy : it) {
             csvFile << iy << ",";
        }
        csvFile << std::endl;
    }
    // 关闭CSV文件
    csvFile.close();
}
void writePlanningLog(const std::string& filename, const std::vector<double> &traingingdata) {
    // 打开CSV文件
    std::ofstream csvFile(filename, std::ios::app);
    // 写入表头
    if (traingingdata.size() == 0) return;
    // std::cout << filename << std::endl;
    // printf("%ld the Traing data size %ld:" , traingingdata.size(), traingingdata[0].size());
    for (auto it : traingingdata) 
    {
        csvFile << it << ",";
    }
    csvFile << std::endl;

    // 关闭CSV文件
    csvFile.close();
}
//-------------------------------------------回调函数---------------------------------------------//
// void PlanningRecord::path_pose_call_backs(const smartcar_msgs::My_TrajectoryArray &msg) {
//     std::lock_guard<std::mutex> lock(mutex_);
    
//     sub_reference_line_msg = msg;
//     reference_line_msg_init = true;
//     reference_line_msg_update = true;
// }
void PlanningRecord::goal_pose_call_backs(const smartcar_msgs::My_Trajectory &msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    sub_reference_line_msg = msg;
    reference_line_msg_init = true;
    // printf("@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    reference_line_msg_update = true;
};

void VehicleCMDCallBack(const smartcar_msgs::ControlCommandStamped::ConstPtr &msg)
{
    cmd_steering_angle = msg->cmd.steering_angle;
    cmd_velocity = msg->cmd.linear_velocity;
    cmd_acc = msg->cmd.linear_acceleration;
}

/*订阅获取中心线坐标*/
void PlanningRecord::update_path(const smartcar_msgs::My_Trajectory &path_point_) {
    cango = false;
    update_init_lon = false;
    reference_path.first.clear();
    reference_path.second.clear();
    accumulated_s.clear();
    reference_points.clear();

    if (path_point_.trajectory_points.size() > 0) {
        std::vector<double> headings;
        std::vector<double> kappas;
        std::vector<double> dkappas;
        std::vector<std::pair<double, double>> xy_points;

        // auto beforeTime = std::chrono::steady_clock::now(); //计时开始
        for (size_t i = 0; i < path_point_.trajectory_points.size(); i++) {
            reference_path.first.push_back(path_point_.trajectory_points[i].x);
            reference_path.second.push_back(path_point_.trajectory_points[i].y);
            std::pair<double, double> xy;
            xy.first = path_point_.trajectory_points[i].x;
            xy.second = path_point_.trajectory_points[i].y;
            xy_points.push_back(xy);
        }

        if (!PathMatcher::ComputePathProfile(xy_points, &headings, &accumulated_s, &kappas, &dkappas)) {
            ROS_WARN("rerferenceline generate failed!");
        } else {

            for (size_t i = 0; i < xy_points.size(); i++) {
                //创建ReferencePoint类


                ReferencePoint reference_point(
                    kappas[i], dkappas[i], xy_points[i].first, xy_points[i].second, headings[i], accumulated_s[i]);
                reference_points.emplace_back(reference_point);

            }
            // ROS_WARN("rerferenceline generate successfully!");
        }
        //参考线三次样条方程
        //输入(x1,y1),(x2,y2)......(xn,yn),返回 x-s坐标系与y-s坐标系
        // csp = new CubicSpline2D(reference_path.first, reference_path.second, accumulated_s); //只需要执行一次
        //初始化
        // kappa_init = kappas.front();
        // dkappa_init = dkappas.front();
        // init_lon_state = 0;  //复位
        // cango = true;        //复位
    }

}

/*读回ros odom坐标系数据 , 接收车的里程信息，控制车的移动*/
void PlanningRecord::odom_call_back(const smartcar_msgs::Location &odom) {
    std::lock_guard<std::mutex> lock(mutex_);
    sub_odom_ = odom;  //车的里程信息，就是位置信息
    pos_msg_init = 1;
    pos_msg_update = 1;
}

/*订阅感知的障碍物*/
void PlanningRecord::ObstacleCallBack(const smartcar_msgs::DetectedObjectArray &msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    msg_AllObstacle = msg;
    objects_msg_update = 1;
}


void PlanningRecord::egoSLPathCallback(const nav_msgs::Path &ego_SL_path) {
    if (ego_SL_human_path_.header.frame_id !=ego_SL_path.header.frame_id) update_human_path_ = true;
    ego_SL_human_path_ = ego_SL_path;
};

void PlanningRecord::samplePointsCallback(const nav_msgs::Path::ConstPtr& msg) {
    update_sample_points_ = true;
    learning_sample_points_ = *msg;
}

void ACCTargetCallback(const smartcar_msgs::ACCTarget &msg) {
    std::lock_guard<std::mutex> _guard(cur_acc_mutex);//时间上不受影响但共享了全局变量，所以要加锁保证同一时刻只能由一个程序修改变量
    cur_acc_target = msg;
    acc_update = true;
};
//------------------------------------------子函数---------------------------------------------//

//判断车是否走完轨迹的设置距离，是的话再发给局部规划，在车目前的位置之前更新局部规划轨迹
bool PlanningRecord::is_update_dynamic(nav_msgs::Path &trj_point_array, Car_Info &odom, int size) {
    bool is_update;
    Point3D_ss pp;
    is_update = false;
    //车的当前位置
    pp.x = odom.x;
    pp.y = odom.y;
    pp.z = odom.z;
    double xx = trj_point_array.poses[size].pose.position.x;
    double yy = trj_point_array.poses[size].pose.position.y;
    double distance = sqrt(pow(pp.x - xx, 2) + pow(pp.y - yy, 2));
    if (distance < 1)  //接近了
    {
        is_update = true;
    }
    return is_update;
}

//判断车是否距离障碍物很近，很近返回true，目前没用上
bool PlanningRecord::Approaching_Obstacles(vector<Point2D> Obstacles, nav_msgs::Odometry &odom, double distances) {
    bool is_update;
    is_update = false;
    Point3D_ss pp;
    //车的当前位置
    pp.x = odom.pose.pose.position.x;
    pp.y = odom.pose.pose.position.y;
    pp.z = odom.pose.pose.position.z;
    if (Obstacles.size() > 0) {
        for (size_t i = 0; i < Obstacles.size(); i++) {
            double xx = Obstacles[i].x;
            double yy = Obstacles[i].y;
            double distance = sqrt(pow(pp.x - xx, 2) + pow(pp.y - yy, 2));
            if (distance < distances)  //接近了
            {
                is_update = true;
            }
        }
    }

    return is_update;
}



//---------------------------------默认构造函数：规划函数,初始化参数---------------------------------//
PlanningRecord::PlanningRecord(void) {
    ros::NodeHandle n;
    ros::param::get("log_file_name", log_file_name_);  //
    std::string PLAN_CONF_FILE_NAME;

    n.param<std::string>("planning/planning_config_path", PLAN_CONF_FILE_NAME, "/home/unknow");
    Status read_status = Config_.ReadControlConf(PLAN_CONF_FILE_NAME);
    ////////////////////////////////发布////////////////////////////////////////
    Start_Dynamic = n.advertise<std_msgs::String>("Start_Dynamic", 10);   //发布局部轨迹成功生存的信号
    pub_plot = n.advertise<geometry_msgs::PoseArray>("XY_Graphy", 1000);  //画ST/SL图

    // ACC_Target_ = n.advertise<smartcar_msgs::ACCTarget>("ACC_Target", 1);   //发布ACC的目标，id、相对S坐标、速度

    // ros::Publisher pub_plot = n.advertise<geometry_msgs::PoseArray>("XY_Graphy", 1000);  //画ST/SL图

// egoSLPathCallback
    //  pub_ego_SLpath_ = rospy.Publisher("egoSLpath", Path, queue_size=10)
    /////////////////////////////////订阅///////////////////////////////////////
    // start_pose_subscriber_ = n.subscribe("/initialpose", 10, &PlanningRecord::start_pose_call_backs, this);  //订阅
    odom_sub_ =
        n.subscribe("smartcar/location", 10, &PlanningRecord::odom_call_back, this);  //订阅vehicle_control.cpp的里程计
    sub_vehicleCMD_data_ = n.subscribe<smartcar_msgs::ControlCommandStamped>("ctrl_cmd", 100, &VehicleCMDCallBack);
    // subMap = n.subscribe("/map", 1, &PlanningRecord::setHybridMap, this);
    global_lane_subscriber_ =
    n.subscribe("/global_lane", 10, &PlanningRecord::goal_pose_call_backs, this);  //订阅
    // path_pose_subscriber_ =
    //     n.subscribe("ReferenceLine_CenterPoint", 1000, &PlanningRecord::path_pose_call_backs, this);  //订阅
    sub_acc_target_ = n.subscribe("/ACC_Target", 1, &ACCTargetCallback);
    // ego_SL_path_sub_ =
    //     n.subscribe("egoSLpath", 10, &PlanningRecord::egoSLPathCallback, this);  //订阅

    // vis_feasible_paths = n.advertise<visualization_msgs::Marker>("vis_feasible_paths", 10);

    // local_path_pub = n.advertise<smartcar_msgs::Lane>("/local_trajectory", 100);

    // pub_sl_graph_ = n.advertise<smartcar_msgs::My_TrajectoryArray>("/sl_graph4sample", 10);

    // sub_sample_points_ = n.subscribe<nav_msgs::Path>("LearningSamplePoints", 10, &PlanningRecord::samplePointsCallback, this);
    // if (enable_forecast_) {
    //     sub_obstacle = n.subscribe("/prediction/motion_predictor/objects", 10, &PlanningRecord::ObstacleCallBack, this);
    // } else 
    {
        sub_obstacle = n.subscribe("ITS/DetectObjects", 10, &PlanningRecord::ObstacleCallBack, this);
    }
    

    //参数初始化
    cout = 0;
    canend = false;
    string aa = "0";
    // start_dynamic.data = aa.c_str();
    // Start_Dynamic.publish(start_dynamic);

    routing_thread_ = new boost::thread(boost::bind(&PlanningRecord::thread_routing, this));
}

PlanningRecord::~PlanningRecord(void) {
    delete routing_thread_;
    // delete best_frenet_path;
}

void PlanningRecord::thread_routing(void) {
    ros::NodeHandle n;
    ros::Rate loop_rate(50);
    //类实例化对象
    FrenetOptimalTrajectory fot;
    Obstacle ob(true);
    // ObstacleTest obt;  //里面有线程，目的就是发布模拟障碍物

    //前探距离
    double lon_decision_horizon = 0;
    double move_dis = 0, backup_mov_dis = 0;
    bool is_mov_ref = false;

    ros::AsyncSpinner spin(4);
    spin.start();

    //输入数据检查
    // 1.尝试抓取定位
    while (!reference_line_msg_update) {
        std::cout << "has not got lane\n" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (!ros::ok()) return;
    } 
   
    {
        std::lock_guard<std::mutex> lock(mutex_);
        // ROS_INFO("update sub_reference_line");
        sub_reference_line = sub_reference_line_msg;
        reference_line_msg_update = false;
        update_path(sub_reference_line);
    }
    std::cout << "has got reference_line\n";

    std::cout << "try get first position\n";
    while (!pos_msg_init) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (!ros::ok()) return;
    }
    std::cout << "has got position\n";
    
    std::cout << "all sensor is working!\n";
    
    size_t errorrr = 0;
    auto log_start = std::chrono::system_clock::now();

    while (n.ok()) {
        auto plan_start = std::chrono::system_clock::now();
        // ros::spinOnce();
        std::vector<double> planning_log;
        planning_log.reserve(100);
        double reference_line_id = 1.0;
        std::chrono::duration<double> log_time = plan_start - log_start;
        planning_log.emplace_back(log_time.count()*1000);
        ros::param::get("reference_line_id", reference_line_id);
        planning_log.emplace_back(reference_line_id) ;

        printf("LOG Time %f \n", log_time.count()*1000);
        {
            std::lock_guard<std::mutex> _guard(cur_acc_mutex);
            // planning_log.emplace_back(std::stod(cur_acc_target.object_id[1])) ;
            planning_log.emplace_back(cur_acc_target.relative_dis) ;
            planning_log.emplace_back(cur_acc_target.velocity);
            planning_log.emplace_back(cmd_steering_angle) ;
            planning_log.emplace_back(cmd_velocity) ;
            planning_log.emplace_back(cmd_acc) ;
        }

        std::cout << "####################################\n";
        if (pos_msg_update) {
            std::lock_guard<std::mutex> lock(mutex_);
            pos_msg_update = false;
            no_pos_count = 0;
            car_info.x = sub_odom_.global_pos.x;
            car_info.y = sub_odom_.global_pos.y;
            car_info.yaw = sub_odom_.orientation[2];
            car_info.speed = sub_odom_.speed;
            car_info.ax = sub_odom_.accel_x;
            car_info.z = sub_odom_.global_pos.z;
            car_info.z = 0;//不考虑高程信息

        } else {
            no_pos_count++;
        }
        if (no_pos_count >= 20) {
            no_pos_count = 20;
            std::cout << "no pos info" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }


        /*更新感知限制的障碍物*/
        // std::vector<std::vector<double>> training_datas;
        // std::vector<double> cur_scene;
        
        // cur_scene.emplace_back(sub_odom_.global_pos.x);
        // cur_scene.emplace_back(sub_odom_.global_pos.y);
        // cur_scene.emplace_back(sub_odom_.speed);
        // cur_scene.emplace_back(sub_odom_.orientation[2]);
        // cur_scene.emplace_back(0);
        // if (objects_msg_update) {
        //     smartcar_msgs::DetectedObjectArray tmp_msg;
        //     {
        //         std::lock_guard<std::mutex> lock(mutex_);
        //         tmp_msg = msg_AllObstacle;
        //         objects_msg_update = false;
        //     }
       
        // }
        
        smartcar_msgs::DetectedObjectArray tmp_msg;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tmp_msg = msg_AllObstacle;
        }
        ob.setObstacles(tmp_msg);

        // printf("%ld, dsaadasdss\n", tmp_msg.objects.size());
        // for (auto obstacle : tmp_msg.objects)
        // {
        //     cur_scene.emplace_back(obstacle.utm_x);
        //     cur_scene.emplace_back(obstacle.utm_y);
        //     cur_scene.emplace_back(obstacle.speed);
        //     cur_scene.emplace_back(obstacle.utm_heading);
        //     cur_scene.emplace_back(0);
        // }
        //--------------------------------------------------创建障碍物对象--------------------------------------------------//
        std::vector<const Obstacle *> obstacles;  // Apollo是这种类型，不想改里面的源码，所以对外调整类型
        for (size_t i = 0; i < AllObstacle.size(); i++) {
            obstacles.emplace_back(&AllObstacle[i]);
        }
        // ob.visualization(AllObstacle);
        
        // -----------------------------------------------轨迹生成过程-----------------------------------------------//
        
        multiple_best_path.clear();
        //对每一条参考线都规划一条最优轨迹
        std::vector<TrajFeature> traj_features;
        traj_features.reserve(500);
        
        //初始参数的输入
        InitialConditions lattice_ic = {
            // d0,    //初始的横向偏移值 [m]
            // dd0,   //初始的横向速度 [m/s]
            // ddd0,  //初始的横向加速度 [m/s^2]

            // init_lon_state,      //初始的纵向值[m]
            // ds0,                 //初始的纵向速度[m/s]
            // dds0,                //初始的纵向加速度[m/ss]
            init_relative_time,  //规划起始点的时间

            car_info.x,
            car_info.y,
            car_info.z,
            car_info.speed,
            car_info.ax,

            car_info.yaw,
            car_info.kappa,
            car_info.dkappa,
        };

        //创建起点参数t
        TrajectoryPoint planning_init_point(lattice_ic);
        ReferencePoint matched_point = PathMatcher::MatchToPath(reference_points, planning_init_point.path_point().x,
                                                        planning_init_point.path_point().y);
        // 2. according to the matched point, compute the init state in Frenet frame.
        std::array<double, 3> init_s;
        std::array<double, 3> init_d;

        LP.ComputeInitFrenetState(matched_point, planning_init_point, &init_s, &init_d);
        // std::cout << init_s[0] << " "  << init_d[0]<< std::endl;
        planning_log.emplace_back(car_info.x);
        planning_log.emplace_back(car_info.y);
        planning_log.emplace_back(car_info.speed);
        planning_log.emplace_back(car_info.yaw);
        planning_log.emplace_back(init_s[0]);
        planning_log.emplace_back(init_d[0]);
        planning_log.emplace_back(sub_odom_.accel_x);
        planning_log.emplace_back(sub_odom_.accel_y);

        printf("The OBS_SIZE %ld \n", obstacles.size());
        bool is_collision = false;
        for (auto obs : obstacles) {
            InitialConditions lattice_ic = {
            // d0,    //初始的横向偏移值 [m]
            // dd0,   //初始的横向速度 [m/s]
            // ddd0,  //初始的横向加速度 [m/s^2]

            // init_lon_state,      //初始的纵向值[m]
            // ds0,                 //初始的纵向速度[m/s]
            // dds0,                //初始的纵向加速度[m/ss]
            init_relative_time,  //规划起始点的时间

            obs->centerpoint.position.x,
            obs->centerpoint.position.y,
            obs->centerpoint.position.z,
            obs->obstacle_velocity,
            0.0,
            obs->obstacle_theta,
            0.0,
            0.0,
            };

        //创建起点参数t
            TrajectoryPoint planning_init_point(lattice_ic);
            // std::cout <<" The obstacles " <<std::endl;
            ReferencePoint matched_point = PathMatcher::MatchToPath(reference_points, planning_init_point.path_point().x,
                                                            planning_init_point.path_point().y);
            // 2. according to the matched point, compute the init state in Frenet frame.
            std::array<double, 3> init_s_obs;
            std::array<double, 3> init_d_obs;
            LP.ComputeInitFrenetState(matched_point, planning_init_point, &init_s_obs, &init_d_obs);

            if (fabs(init_s_obs[0] - init_s[0]) < Config_.FLAGS_vehicle_length+0.1 && fabs(init_d_obs[0] - init_d[0]) < Config_.FLAGS_vehicle_width) {
                is_collision = true;
            }
            // std::cout << "centerpoint " << obs->centerpoint.position.x << " " << obs->centerpoint.position.y
            // << " Vel " << obs->obstacle_velocity << " Yaw " << obs->obstacle_theta
            // << " S " << init_s_obs[0] << " L " << init_d_obs[0]
            // << " Length " << obs->obstacle_length << " Width " << obs->obstacle_width
            
            // <<std::endl;
            planning_log.emplace_back(obs->centerpoint.position.x);
            planning_log.emplace_back(obs->centerpoint.position.y);
            planning_log.emplace_back(obs->obstacle_velocity);
            planning_log.emplace_back(obs->obstacle_theta);
            planning_log.emplace_back(init_s_obs[0]);
            planning_log.emplace_back(init_d_obs[0]);
            planning_log.emplace_back(obs->obstacle_length);
            planning_log.emplace_back(obs->obstacle_width);
        }
        std::cout << "reference_line_id " << planning_log[1] << "\n" << 
        "ACC target " << planning_log[2] << "  " <<  planning_log[3] <<  "\n" <<
        "vel_track " << planning_log[4] << "  "  << planning_log[9] << "\n"
        << "acc_track " << planning_log[5] << " " <<   planning_log[13] <<  " " <<  planning_log[14] << "\n"
         << std::endl;;

        if (is_collision) {
            ROS_ERROR("The Vehicle Collided!");
        }
        if (fabs(sub_odom_.accel_y > 0.5)) {
            ROS_WARN("The Vehicle lateral acceleration is %f m/s2, This is Dangerous", sub_odom_.accel_y);
        }

        // if ()
        writePlanningLog(log_file_name_, planning_log);
        // 障碍物的id
        auto plan_end = std::chrono::system_clock::now();
        std::chrono::duration<double> cost_time = plan_end - plan_start;
        std::cout << "cost_time: " << cost_time.count() * 1000 << " ms." << std::endl;
        ////////////////////////////////以上是局部规划//////////////////////////////////
        loop_rate.sleep();
        
    }

    std::cout << "ERROR : " << errorrr << std::endl;
    spin.stop();
}

