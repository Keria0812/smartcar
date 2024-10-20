#include "dynamic_routing.h"

PlanningConf Config_;  //配置文件读取

//全局变量
std::vector<Obstacle> AllObstacle;  //感知一帧识别到的所有障碍物
smartcar_msgs::DetectedObjectArray msg_AllObstacle;
std::pair<vector<double>, vector<double>> reference_path;  //参考路径点位置（x,y）
std::vector<ReferencePoint> reference_points;              //参考路径点参数
smartcar_msgs::My_TrajectoryArray sub_reference_line_msg;
smartcar_msgs::My_TrajectoryArray sub_reference_line;
geometry_msgs::Pose start_pose_;    //起点
geometry_msgs::Pose goal_pose_;     //终点
smartcar_msgs::Location sub_odom_;  // odom
bool cango;                         //判断车是否需要局部规划
bool canend;                        //判断局部规划的轨迹是否到达终点
bool update_init_lon;               //更新参考线
bool messege1;                      //控制发布一次的变量
bool messege2;                      //控制发布一次的变量

double init_lon_state;              //初始弧长
Eigen::Vector3d origin_mgrs_point;  //地图MGRS的原点
// CubicSpline2D *csp;                                       //样条插值函数
std::vector<double> accumulated_s;  //纵向距离

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

//-------------------------------------------回调函数---------------------------------------------//
void Dynamic_routing::path_pose_call_backs(const smartcar_msgs::My_TrajectoryArray &msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    sub_reference_line_msg = msg;
    reference_line_msg_init = true;
    reference_line_msg_update = true;
}

/*订阅获取中心线坐标*/
void Dynamic_routing::update_path(const smartcar_msgs::My_Trajectory &path_point_) {
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
void Dynamic_routing::odom_call_back(const smartcar_msgs::Location &odom) {
    std::lock_guard<std::mutex> lock(mutex_);
    sub_odom_ = odom;  //车的里程信息，就是位置信息
    pos_msg_init = 1;
    pos_msg_update = 1;
}

/*订阅感知的障碍物*/
void Dynamic_routing::ObstacleCallBack(const smartcar_msgs::DetectedObjectArray &msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    msg_AllObstacle = msg;
    objects_msg_update = 1;
}


void Dynamic_routing::egoSLPathCallback(const nav_msgs::Path &ego_SL_path) {
    if (ego_SL_human_path_.header.frame_id !=ego_SL_path.header.frame_id) update_human_path_ = true;
    ego_SL_human_path_ = ego_SL_path;
};

void Dynamic_routing::samplePointsCallback(const nav_msgs::Path::ConstPtr& msg) {
    update_sample_points_ = true;
    learning_sample_points_ = *msg;
}
//------------------------------------------子函数---------------------------------------------//

//判断车是否走完轨迹的设置距离，是的话再发给局部规划，在车目前的位置之前更新局部规划轨迹
bool Dynamic_routing::is_update_dynamic(nav_msgs::Path &trj_point_array, Car_Info &odom, int size) {
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
bool Dynamic_routing::Approaching_Obstacles(vector<Point2D> Obstacles, nav_msgs::Odometry &odom, double distances) {
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
Dynamic_routing::Dynamic_routing(void) {
    ros::NodeHandle n;
    // ros::param::get("hdmap_file_path", this->file_path_);
    ros::param::get("use_lattice_planner", this->use_lattice_planner);  //选择规划方案
    ros::param::get("use_lateral_optimization", this->FLAGS_lateral_optimization);
    ros::param::get("COLLISION_CHECK_THRESHOLD", this->COLLISION_CHECK_THRESHOLD);
    ros::param::get("MaxT", this->MaxT);
    ros::param::get("MinT", this->MinT);
    ros::param::get("go_Sizes", this->go_sizes);                            //轨迹更新的地方
    ros::param::get("set_Sizes", this->set_sizes);                          //轨迹开始的地方
    ros::param::get("Approaching_obstacles", this->Approaching_obstacles);  //距离障碍物
    ros::param::get("enable_forecast", enable_forecast_);
    ros::param::get("reference_line_id", reference_line_id);
    ros::param::get("debug_pathfollow", debug_pathfollow_);
    ros::param::get("number_of_cpu_cores", number_of_cpu_cores_);
    ros::param::get("planning_by_learning", planning_by_learning_);

    calc_pool_  = std::make_shared<ThreadPool>(number_of_cpu_cores_);
 
    ROS_INFO_STREAM("dynamic_routing enable_forecast_: " << enable_forecast_);

    std::string PLAN_CONF_FILE_NAME;
    n.param<std::string>("planning/planning_config_path", PLAN_CONF_FILE_NAME, "/home/unknow");
    Status read_status = Config_.ReadControlConf(PLAN_CONF_FILE_NAME);
    if (read_status.status != "OK") {
        ROS_INFO_STREAM("Unable to load plan conf file " << PLAN_CONF_FILE_NAME);
    }
    ROS_INFO_STREAM("Planning conf file:" << PLAN_CONF_FILE_NAME << " had beed loaded!");

    ////////////////////////////////发布////////////////////////////////////////
    waypoints_pub_ = n.advertise<nav_msgs::Path>("dynamic_waypoints", 10);        //发布局部轨迹
    local_paths_v = n.advertise<geometry_msgs::PoseArray>("dynamic_paths_v", 10);  //发布局部轨迹的速度
    local_paths_t = n.advertise<geometry_msgs::PoseArray>("dynamic_paths_t", 10);  //发布局部轨迹的航向角
    local_paths_k = n.advertise<geometry_msgs::PoseArray>("dynamic_paths_k", 10);  //发布局部轨迹的曲率

    Start_Dynamic = n.advertise<std_msgs::String>("Start_Dynamic", 10);   //发布局部轨迹成功生存的信号
    waypoints_center_ = n.advertise<nav_msgs::Path>("Center_Path", 10);   //发布参考线
    pub_plot = n.advertise<geometry_msgs::PoseArray>("XY_Graphy", 1000);  //画ST/SL图

    ACC_Target_ = n.advertise<smartcar_msgs::ACCTarget>("ACC_Target", 1);   //发布ACC的目标，id、相对S坐标、速度

    // ros::Publisher pub_plot = n.advertise<geometry_msgs::PoseArray>("XY_Graphy", 1000);  //画ST/SL图

// egoSLPathCallback
    //  pub_ego_SLpath_ = rospy.Publisher("egoSLpath", Path, queue_size=10)
    /////////////////////////////////订阅///////////////////////////////////////
    // start_pose_subscriber_ = n.subscribe("/initialpose", 10, &Dynamic_routing::start_pose_call_backs, this);  //订阅
    odom_sub_ =
        n.subscribe("smartcar/location", 10, &Dynamic_routing::odom_call_back, this);  //订阅vehicle_control.cpp的里程计
    // subMap = n.subscribe("/map", 1, &Dynamic_routing::setHybridMap, this);
    // goal_pose_subscriber_ =
    // n.subscribe("/move_base_simple/goal", 10, &Dynamic_routing::goal_pose_call_backs, this);  //订阅
    path_pose_subscriber_ =
        n.subscribe("ReferenceLine_CenterPoint", 1000, &Dynamic_routing::path_pose_call_backs, this);  //订阅

    ego_SL_path_sub_ =
        n.subscribe("egoSLpath", 10, &Dynamic_routing::egoSLPathCallback, this);  //订阅

    vis_feasible_paths = n.advertise<visualization_msgs::Marker>("vis_feasible_paths", 10);

    local_path_pub = n.advertise<smartcar_msgs::Lane>("/local_trajectory", 100);

    pub_sl_graph_ = n.advertise<smartcar_msgs::My_TrajectoryArray>("/sl_graph4sample", 10);

    sub_sample_points_ = n.subscribe<nav_msgs::Path>("LearningSamplePoints", 10, &Dynamic_routing::samplePointsCallback, this);
    if (enable_forecast_) {
        sub_obstacle = n.subscribe("/prediction/motion_predictor/objects", 10, &Dynamic_routing::ObstacleCallBack, this);
    } else {
        sub_obstacle = n.subscribe("ITS/DetectObjects", 10, &Dynamic_routing::ObstacleCallBack, this);
    }
    

    //----------------------加载地图------------------------//
    // maps = lanelet::load(file_path_, projector);
    //----------------------获得MGRS原点------------------------//
    // shared_ptr<XmlDomDocument> doc = make_shared<XmlDomDocument>(this->file_path_.c_str());
    // if (doc)
    // {
    //   //----------------------获得经纬度原点------------------------//
    //   origin_gps_pt_.lat = atof(doc->getChildAttribute("osm", 0, "node", 0, "lat").c_str());
    //   origin_gps_pt_.lon = atof(doc->getChildAttribute("osm", 0, "node", 0, "lon").c_str());
    // }
    // origin_mgrs_point(0) = projector.forward(origin_gps_pt_).x();
    // origin_mgrs_point(1) = projector.forward(origin_gps_pt_).y();
    // origin_mgrs_point(2) = 0;

    //参数初始化
    cout = 0;
    canend = false;
    string aa = "0";
    start_dynamic.data = aa.c_str();
    Start_Dynamic.publish(start_dynamic);

    routing_thread_ = new boost::thread(boost::bind(&Dynamic_routing::thread_routing, this));
}

Dynamic_routing::~Dynamic_routing(void) {
    delete routing_thread_;
    // delete best_frenet_path;
}

void Dynamic_routing::thread_routing(void) {
    ros::NodeHandle n;
    ros::Rate loop_rate(10);
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
    std::cout << "try get first position\n";
    while (!pos_msg_init) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (!ros::ok()) return;
    }
    std::cout << "has got position\n";

    // 2.尝试抓取参考线
    std::cout << "try get first reference_line\n";
    while (!reference_line_msg_init) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (!ros::ok()) return;
    }
    std::cout << "has got reference_line\n";

    std::cout << "all sensor is working!\n";
    size_t errorrr = 0;
    while (n.ok()) {
        if (Config_.FLAGS_Plan4NGSIM_)
        if (!pos_msg_update || !objects_msg_update) continue;

        auto plan_start = std::chrono::system_clock::now();
        // ros::spinOnce();
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

        //更新参考线消息
        if (reference_line_msg_update) {
            std::lock_guard<std::mutex> lock(mutex_);
            // ROS_INFO("update sub_reference_line");
            sub_reference_line = sub_reference_line_msg;
            reference_line_msg_update = false;
            // update_path(sub_reference_line.lanes.front());
            // int lane_index = 0;
            // bool has_ref_lane = ros::param::has("plan/ref_lane");
            // if (has_ref_lane) {
            //     ros::param::get("plan/ref_lane", lane_index);
            // }
            // update_path(sub_reference_line.lanes[lane_index]);
            no_reference_line_count = 0;
        } else {
            no_reference_line_count++;
        }

        if (no_reference_line_count >= 20) {
            no_reference_line_count = 20;
            std::cout << "no reference_line info" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        /*更新感知限制的障碍物*/
        std::vector<std::vector<double>> training_datas;
        std::vector<double> cur_scene;
        
        cur_scene.emplace_back(sub_odom_.global_pos.x);
        cur_scene.emplace_back(sub_odom_.global_pos.y);
        cur_scene.emplace_back(sub_odom_.speed);
        cur_scene.emplace_back(sub_odom_.orientation[2]);
        cur_scene.emplace_back(0);
        if (objects_msg_update) {
            smartcar_msgs::DetectedObjectArray tmp_msg;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                tmp_msg = msg_AllObstacle;
                objects_msg_update = false;
            }
            ob.setObstacles(tmp_msg);
            
        }
        
        smartcar_msgs::DetectedObjectArray tmp_msg;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tmp_msg = msg_AllObstacle;
        }
        // printf("%ld, dsaadasdss\n", tmp_msg.objects.size());
        for (auto obstacle : tmp_msg.objects)
        {
            cur_scene.emplace_back(obstacle.utm_x);
            cur_scene.emplace_back(obstacle.utm_y);
            cur_scene.emplace_back(obstacle.speed);
            cur_scene.emplace_back(obstacle.utm_heading);
            cur_scene.emplace_back(0);
        }
        cur_scene.emplace_back(0.0);
        cur_scene.emplace_back(0.0);
        cur_scene.emplace_back(0.0);
        // printf("%ld dasssss\n", cur_scene.size());
        DiscretizedTrajectory ego_human_traj;


        if (Config_.FLAGS_Plan4NGSIM_)
         {

            //更新自车人类轨迹，每个点100ms
            std::cout << update_human_path_ << std::endl;
            if (/*Config_.FLAGS_Plan4NGSIM_ &&*/ update_human_path_) {
                size_t cur_min_index = 0;
                double cur_dis = (ego_SL_human_path_.poses[cur_min_index].pose.position.x - car_info.x) * (ego_SL_human_path_.poses[cur_min_index].pose.position.x - car_info.x) 
                                +(ego_SL_human_path_.poses[cur_min_index].pose.position.y - car_info.y) * (ego_SL_human_path_.poses[cur_min_index].pose.position.y - car_info.y);
                for (size_t i = 0; i < ego_SL_human_path_.poses.size(); i++) {
                    TrajectoryPoint tmp;
                    tmp.s = ego_SL_human_path_.poses[i].pose.position.x;
                    tmp.d = ego_SL_human_path_.poses[i].pose.position.y;
                    tmp.x = ego_SL_human_path_.poses[i].pose.position.x;
                    tmp.y = ego_SL_human_path_.poses[i].pose.position.y;
                    tmp.v = ego_SL_human_path_.poses[i].pose.position.z;//另一边写的时候把v写在z里
                    double dis = (ego_SL_human_path_.poses[i].pose.position.x - car_info.x) * (ego_SL_human_path_.poses[i].pose.position.x - car_info.x) 
                                +(ego_SL_human_path_.poses[i].pose.position.y - car_info.y) * (ego_SL_human_path_.poses[i].pose.position.y - car_info.y);
                    if (dis < cur_dis) {
                        cur_dis = dis;
                        cur_min_index = i;
                        // printf("%f %f %f dfsfd\n", cur_dis,ego_SL_human_path_.poses[i].pose.position.x ,  car_info.x);
                    } 
                    tmp.kappa = static_cast<double>(cur_min_index);
                    
                
                    //暂时用速度存一下当前点的索引
                    // std::cout << tmp.v << std::endl;
                    ego_human_traj.emplace_back(tmp);
                }
                // if (cur_min_index >=ego_SL_human_path_.poses.size() - 80) {
                //     loop_rate.sleep();
                //     continue;
                // }

            }
        }
        DiscretizedTrajectory sample_points;
        
        if (planning_by_learning_) {
            if (!update_sample_points_) {
                std::cout << "no pos info" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            } else {
                for (size_t i = 0; i < learning_sample_points_.poses.size(); i++) {
                    TrajectoryPoint tmp;
                    tmp.s = learning_sample_points_.poses[i].pose.position.x;
                    tmp.d = learning_sample_points_.poses[i].pose.position.y;
                    tmp.x = learning_sample_points_.poses[i].pose.position.x;
                    tmp.y = learning_sample_points_.poses[i].pose.position.y;
                    tmp.v = learning_sample_points_.poses[i].pose.position.z;//另一边写的时候把v写在z里
                    tmp.relative_time = learning_sample_points_.poses[i].header.stamp.toSec();
                    sample_points.emplace_back(tmp);
                }
            }
        }

        //--------------------------------------------------创建障碍物对象--------------------------------------------------//
        std::vector<const Obstacle *> obstacles;  // Apollo是这种类型，不想改里面的源码，所以对外调整类型
        for (size_t i = 0; i < AllObstacle.size(); i++) {
            obstacles.emplace_back(&AllObstacle[i]);
            
        }
        ob.visualization(AllObstacle);
        




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
        double target_vel = Config_.default_cruise_speed;
        // // 车道剧中保持辅助和轨迹跟踪专用
        // if (car_info.x < 800) {
        //     target_vel = std::min(target_vel, 100.0/3.6 * (car_info.x / 800.0));
        // }
        // if (car_info.x > 1450) {
        //     target_vel = std::min(target_vel, 100.0/3.6 * (1.0 - (car_info.x -1600) / 800.0));
        // }
        // target_vel = std::max(10.0, target_vel);

        // if (car_info.x < 500) {
        //     target_vel = std::min(target_vel, 40.0/3.6);
        // } else if (car_info.x > 500 && car_info.x < 550) {
        //     target_vel = std::min(target_vel, 55.0/3.6);
        // } else if (car_info.x > 550 && car_info.x < 600) {
        //     target_vel = std::min(target_vel, 70.0/3.6);
        // } else if (car_info.x > 600 && car_info.x < 650) {
        //     target_vel = std::min(target_vel, 85.0/3.6);
        // } else if (car_info.x > 650 && car_info.x < 1400) {
        //     target_vel = std::min(target_vel, 100.0/3.6);
        // }
        // else if (car_info.x > 1400 && car_info.x < 1450) {
        //     target_vel = std::min(target_vel, 90.0/3.6);
        // } else if (car_info.x > 1450 && car_info.x < 1500) {
        //     target_vel = std::min(target_vel, 80.0/3.6);
        // } else if (car_info.x > 1500 && car_info.x < 1550) {
        //     target_vel = std::min(target_vel, 70.0/3.6);
        // } else if (car_info.x > 1550 && car_info.x < 1600) {
        //     target_vel = std::min(target_vel, 55.0/3.6);
        // }else if (car_info.x > 1600) {
        //     target_vel = std::min(target_vel, 40.0/3.6);
        // }

        if (debug_pathfollow_) {
            //发布给跟踪模块
            smartcar_msgs::Lane glane;  //原autoware控制使用
            geometry_msgs::TwistStamped plan_speed;
            // plan_speed.twist.linear.x = 10 / 3.6;  // target_speed / 3.6; //m/s
            // if((n - match_index) < 50){
            //     plan_speed.twist.linear.x = 0;  //如果距离终点还剩50个点就刹车
            // }
                smartcar_msgs::Waypoint waypoint;
            int index = 0;
            if (sub_reference_line.lanes.size() > 1) {
                index = 1;
            }
            if (sub_reference_line.lanes.size() > 0) {
                for (int i = 0; i < sub_reference_line.lanes[index].trajectory_points.size(); i++) {
                    waypoint.pose.pose.position.x = sub_reference_line.lanes[index].trajectory_points[i].x;
                    waypoint.pose.pose.position.y = sub_reference_line.lanes[index].trajectory_points[i].y;
                    // sub_reference_line.lanes[1].trajectory_points[i].kappa
                    printf("%f dsa  ssssssssssssss\n", sub_reference_line.lanes[index].trajectory_points[i].kappa);
                    waypoint.twist.twist.linear.x = target_vel;
                    glane.waypoints.push_back(waypoint);
                }

            }
            update_path(sub_reference_line.lanes[1]);

            ReferencePoint matched_point = PathMatcher::MatchToPath(reference_points, planning_init_point.path_point().x,
                                                            planning_init_point.path_point().y);

            // 2. according to the matched point, compute the init state in Frenet frame.
            std::array<double, 3> init_s;
            std::array<double, 3> init_d;
            LP.ComputeInitFrenetState(matched_point, planning_init_point, &init_s, &init_d);
            if (reference_points.back().accumulated_s_ >= Config_.FLAGS_speed_lon_decision_horizon)  //参考线太长
            {
                lon_decision_horizon = Config_.FLAGS_speed_lon_decision_horizon;
            } else {
                lon_decision_horizon = reference_points.back().accumulated_s_;  //前瞻最长纵向距离
            }
            //与Apollo不同，我们的前探距离不加上init_s[0]，因为我们的仿真的参考线不长
            auto ptr_path_time_graph = std::make_shared<PathTimeGraph>(obstacles, reference_points, init_s[0],
                                                                init_s[0] + lon_decision_horizon, //前瞻多少m lon_decision_horizon
                                                                0.0, Config_.FLAGS_trajectory_time_length, init_d);
            ST_Boundary acc_target = ptr_path_time_graph->getACCTargetST(init_s[0]);
            smartcar_msgs::ACCTarget ACCTarget;
            if ( acc_target.obstacle_id == -1) {
                ACCTarget.object_id = acc_target.obstacle_id;
                ACCTarget.relative_dis = 1000.0;
                ACCTarget.velocity = 1000.0;
            } else {
                ACCTarget.object_id = acc_target.obstacle_id;
                ACCTarget.relative_dis = acc_target.bottom_left_point_.s();
                ACCTarget.velocity = acc_target.obstacle_velocity;
            }
            ACCTarget.header.stamp = ros::Time::now();
            // (std::stod(acc_target.obstacle_id), acc_target.bottom_left_point_.s(), acc_target.obstacle_velocity);
            //这样写很危险，后面再优化，因为障碍物ID有可能发生变化，而我要根据障碍物ID计算加速度
            // if (ACCTarget[0] == -1.0) {
            //     ACCTarget[1] = 1000.0;
            //     ACCTarget[2] = 1000.0;
            // }
            ACC_Target_.publish(ACCTarget);
            printf("Target Obs : %f %f \n", acc_target.bottom_left_point_.s(), acc_target.obstacle_velocity);
            std::cout << "We Debug PathFollow , it's target speed is " <<target_vel<< " !" << std::endl;;
            local_path_pub.publish(glane);
            loop_rate.sleep();
            continue;
        }
        size_t all_pairs_num = 0;
        size_t in_valid_num = 0;
        size_t end_traj_num = 0;
        for (int lane_index = 0; lane_index < sub_reference_line.lanes.size(); lane_index++) {
            if (planning_by_learning_ && lane_index != 1) {
                continue;
            }

            // printf("????????????????????????????????????????????????????????????????????????????????????\n");
            update_path(sub_reference_line.lanes[lane_index]);
            // std::vector<int> 
            // ---------------------------------------------RIO范围的纵向距离确定-----------------------------------------------//
            if (accumulated_s[accumulated_s.size() - 1] >= Config_.FLAGS_speed_lon_decision_horizon)  //参考线太长
            {
                lon_decision_horizon = Config_.FLAGS_speed_lon_decision_horizon;
            } else {
                lon_decision_horizon = accumulated_s[accumulated_s.size() - 1];  //前瞻最长纵向距离
            }

            // lon_decision_horizon = accumulated_s[accumulated_s.size() - 1];  //我们参考线短，直接参考线的长度
            // std::cout << "lon_decision_horizon:" << lon_decision_horizon << "\n";
            // std::cout << "reference_points_size:" << reference_points.size() << "\n";
            
            std::vector<DiscretizedTrajectory> cur_sl_graph;
            
            //--------------------------------------------------生成轨迹--------------------------------------------------//
            init_relative_time = 0;        // ros::Time::now().toSec();
            if (use_lattice_planner == 2)  // lattice规划
            {
                
                //轨迹生成
                std::vector<size_t> analysis_data;
                
                PlanningTarget planning_target(target_vel, accumulated_s);  //目标
                std::vector<TrajFeature> tmp_features;
                if (planning_by_learning_) {
                    best_path =
                    LP.LatticePlanbyMySampleModel(planning_init_point, planning_target, obstacles, accumulated_s, reference_points,
                        FLAGS_lateral_optimization, init_relative_time, lon_decision_horizon, feasible_paths_, 
                        sample_points, tmp_features, calc_pool_, cur_sl_graph, analysis_data);//我加的IRL的东西
                }
                else {
                    best_path =
                    LP.LatticePlan(planning_init_point, planning_target, obstacles, accumulated_s, reference_points,
                        FLAGS_lateral_optimization, init_relative_time, lon_decision_horizon, feasible_paths_, 
                        ego_human_traj, tmp_features, calc_pool_, cur_sl_graph, analysis_data);//我加的IRL的东西                    
                }
                all_pairs_num += analysis_data[0];
                in_valid_num += analysis_data[1];
                end_traj_num += analysis_data[2];
                ros::param::get("reference_line_id", reference_line_id);

                if (feasible_paths_.size() == 0) {
                    ROS_WARN("The Lane %d has no traj!", lane_index);
                    continue;
                }

                if (Config_.FLAGS_Plan4NGSIM_)
                for (size_t fet = 0; fet < tmp_features.size(); fet++) {
                    for (auto obs : obstacles) {
                        if (abs(obs->centerpoint.position.y - tmp_features[fet].lat_offset) < obs->obstacle_width) {
                            double s_8 =  obs->centerpoint.position.x + obs->obstacle_velocity * tmp_features[fet].length_time;
                            if( (s_8 - tmp_features[fet].length_s + car_info.x) * (obs->centerpoint.position.x - car_info.x) > 0.0) {
                                tmp_features[fet].is_collision = false;
                            } else {
                                tmp_features[fet].is_collision = true;
                            }
                        }

                    }
                    if (lane_index == 1 && fet == tmp_features.size() - 1) {
                        traj_features.insert(traj_features.begin(), tmp_features[fet]);
                    } else if (fet <tmp_features.size() - 1 ) {
                        traj_features.emplace_back(tmp_features[fet]);
                    }
                }
                if (lane_index == 2) best_path.cost += 1000.0;

                if (lane_index != reference_line_id) {
                    best_path.cost += 10.0;
                } else {
                    best_path.cost += 0.0;
                }
                if (lane_index == 0) best_path.cost += 1.0;
                multiple_best_path.push_back(best_path);   

                std::cout << "lane_index" << lane_index << " cost: " << best_path.cost << std::endl;
                ROS_INFO("best_path_size: %ld %ld", best_path.size(), tmp_features.size());
                std::chrono::duration<double> Lattice_cost_time = std::chrono::system_clock::now() - plan_start;
                std::cout << "Lattice_cost_time: " << Lattice_cost_time.count() * 1000 << " ms." << std::endl;
                // ROS_INFO("feasible_paths_size: %ld", feasible_paths_.size());
                //可视化一条参考线上的所有可行轨迹
                std::vector<visualization_msgs::Marker> best_ref_maker(feasible_paths_.size());
                for (int i = 0; i < best_ref_maker.size(); i++) {
                    best_ref_maker[i].id = i + lane_index * 100;
                    best_ref_maker[i].header.frame_id = "map";
                    best_ref_maker[i].header.stamp = ros::Time::now();
                    best_ref_maker[i].ns = "lattice planner";
                    best_ref_maker[i].action = visualization_msgs::Marker::ADD;
                    best_ref_maker[i].type = visualization_msgs::Marker::POINTS;

                    //设置点的粗细
                    best_ref_maker[i].scale.x = 0.1;
                    best_ref_maker[i].scale.y = 0.1;

                    //设置线的颜色
                    best_ref_maker[i].color.r = 0.0f;
                    best_ref_maker[i].color.g = 0.0;
                    best_ref_maker[i].color.b = 1.0f;
                    best_ref_maker[i].color.a = 1.0f;
                    best_ref_maker[i].lifetime = ros::Duration(1);

                    best_ref_maker[i].color.r = 0.0f;
                    best_ref_maker[i].color.g = 0.5;
                    best_ref_maker[i].color.b = 1.0f;
                    best_ref_maker[i].color.a = 1.0f;
                    if (i == 0) {
                        best_ref_maker[i].color.r = 0.0f;
                        best_ref_maker[i].color.g = 1.0;
                        best_ref_maker[i].color.b = 0.0f;
                        best_ref_maker[i].color.a = 1.0f;
                        best_ref_maker[i].scale.x = 0.2;
                        best_ref_maker[i].scale.y = 0.2;
                    }
                    // printf("Path %d, %f , %f", i, feasible_paths_[i]. );


                    for (int j = 0; j < feasible_paths_[i].size(); j++) {
                        geometry_msgs::PoseStamped pose_stamp;
                        pose_stamp.header.frame_id = "map";
                        pose_stamp.header.stamp = ros::Time::now();
                        double tmp_x = feasible_paths_[i][j].x ;
                        double tmp_y = feasible_paths_[i][j].y ;

                        // double tmp_x = feasible_paths_[i][j].x - sub_odom_.global_pos.x;
                        // double tmp_y = feasible_paths_[i][j].y - sub_odom_.global_pos.y;

                        pose_stamp.pose.position.x = tmp_x;
                        pose_stamp.pose.position.y = tmp_y;
                        // pose_stamp.pose.position.z = 0;
                        pose_stamp.pose.position.z = car_info.z;
                        best_ref_maker[i].points.push_back(pose_stamp.pose.position);
                    }
                    // // std::cout << "best_path:" << best_path.size() << "\n";
                    // for (int i = 0; i < 9; i++) {
                    //     cur_scene[i * 5+4] = feasible_paths_[i].back().relative_time;
                    // }
                    // cur_scene[45] = feasible_paths_[i].back().s;
                    // cur_scene[46] = feasible_paths_[i].back().d;
                    // cur_scene[47] = feasible_paths_[i].back().v;

                    // training_datas.emplace_back(cur_scene);
                    vis_feasible_paths.publish(best_ref_maker[i]);
                }
            }
        }

        //获得最终行驶的轨迹
        final_best_path = FindDriveReferenceLineInfo();
        ROS_INFO("feasible_paths_size: %ld", feasible_paths_.size());
        if (final_best_path.size() == 0) {
            loop_rate.sleep();
            continue;
        }
        std::vector<ReferencePoint> final_path_refpoints;


        std::vector<double> headings;
        std::vector<double> kappas;
        std::vector<double> dkappas;
        std::vector<double> cur_accumulated_s;
        std::vector<std::pair<double, double>> xy_points;

        // auto beforeTime = std::chrono::steady_clock::now(); //计时开始
        for (size_t i = 0; i < final_best_path.size(); i++) {
            reference_path.first.push_back(final_best_path[i].x);
            reference_path.second.push_back(final_best_path[i].y);
            std::pair<double, double> xy;
            xy.first = final_best_path[i].x;
            xy.second = final_best_path[i].y;
            xy_points.push_back(xy);
        }
        for (auto path_point : final_best_path) {
                //创建ReferencePoint类
            ReferencePoint reference_point(
                path_point.kappa, path_point.dkappa, path_point.x, path_point.y , path_point.theta, path_point.s);
            final_path_refpoints.emplace_back(reference_point);
        }
        // if (!PathMatcher::ComputePathProfile(xy_points, &headings, &cur_accumulated_s, &kappas, &dkappas)) {
        //     ROS_WARN("rerferenceline generate failed!");
        // } else {
        //     for (size_t i = 0; i < xy_points.size(); i++) {
        //         //创建ReferencePoint类
        //         ReferencePoint reference_point(
        //             kappas[i], dkappas[i], xy_points[i].first, xy_points[i].second, headings[i], cur_accumulated_s[i]);
        //         final_path_refpoints.emplace_back(reference_point);
        //     }
        //     // ROS_WARN("rerferenceline generate successfully!");
        // }
        ReferencePoint matched_point = PathMatcher::MatchToPath(final_path_refpoints, planning_init_point.path_point().x,
                                                          planning_init_point.path_point().y);

        // 2. according to the matched point, compute the init state in Frenet frame.
        std::array<double, 3> init_s;
        std::array<double, 3> init_d;

        LP.ComputeInitFrenetState(matched_point, planning_init_point, &init_s, &init_d);
        if (final_path_refpoints.back().accumulated_s_ >= Config_.FLAGS_speed_lon_decision_horizon)  //参考线太长
        {
            lon_decision_horizon = Config_.FLAGS_speed_lon_decision_horizon;
        } else {
            lon_decision_horizon = final_path_refpoints.back().accumulated_s_;  //前瞻最长纵向距离
        }
        //与Apollo不同，我们的前探距离不加上init_s[0]，因为我们的仿真的参考线不长
        auto ptr_path_time_graph = std::make_shared<PathTimeGraph>(obstacles, final_path_refpoints, init_s[0],
                                                             init_s[0] + lon_decision_horizon, //前瞻多少m lon_decision_horizon
                                                             0.0, Config_.FLAGS_trajectory_time_length, init_d);
        ST_Boundary acc_target = ptr_path_time_graph->getACCTargetST(init_s[0]);
        smartcar_msgs::ACCTarget ACCTarget;
        if ( acc_target.obstacle_id == -1) {
            ACCTarget.object_id = acc_target.obstacle_id;
            ACCTarget.relative_dis = 1000.0;
            ACCTarget.velocity = 1000.0;
        } else {
            ACCTarget.object_id = acc_target.obstacle_id;
            ACCTarget.relative_dis = acc_target.bottom_left_point_.s();
            ACCTarget.velocity = acc_target.obstacle_velocity;
        }
        // (std::stod(acc_target.obstacle_id), acc_target.bottom_left_point_.s(), acc_target.obstacle_velocity);
        //这样写很危险，后面再优化，因为障碍物ID有可能发生变化，而我要根据障碍物ID计算加速度
        // if (ACCTarget[0] == -1.0) {
        //     ACCTarget[1] = 1000.0;
        //     ACCTarget[2] = 1000.0;
        // }
        ACC_Target_.publish(ACCTarget);
        printf("Target Obs : %f %f \n", acc_target.bottom_left_point_.s(), acc_target.obstacle_velocity);
        // ptr_path_time_graph->
        //可视化最终的行驶轨迹
        visualization_msgs::Marker maker_best_path;
        maker_best_path.id = 1000000;
        maker_best_path.header.frame_id = "map";
        maker_best_path.header.stamp = ros::Time::now();
        maker_best_path.ns = "lattice planner";
        maker_best_path.action = visualization_msgs::Marker::ADD;
        maker_best_path.type = visualization_msgs::Marker::POINTS;

        //设置点的粗细
        maker_best_path.scale.x = 0.5;
        maker_best_path.scale.y = 0.5;

        //设置线的颜色
        maker_best_path.color.r = 1.0f;
        maker_best_path.color.g = 0.0;
        maker_best_path.color.b = 0.0f;
        maker_best_path.color.a = 1.0f;
        maker_best_path.lifetime = ros::Duration(1);
        for (int j = 0; j < final_best_path.size(); j++) {
            geometry_msgs::PoseStamped pose_stamp;
            pose_stamp.header.frame_id = Frame_id;
            pose_stamp.header.stamp = ros::Time::now();
            pose_stamp.pose.position.x = final_best_path[j].x ;
            pose_stamp.pose.position.y = final_best_path[j].y ;
            // pose_stamp.pose.position.x = final_best_path[j].x - sub_odom_.global_pos.x;
            // pose_stamp.pose.position.y = final_best_path[j].y - sub_odom_.global_pos.y;
            // pose_stamp.pose.position.z = 0;
            pose_stamp.pose.position.z = car_info.z;
            pose_stamp.pose.orientation.w = 1;
            maker_best_path.points.push_back(pose_stamp.pose.position);
        }
        vis_feasible_paths.publish(maker_best_path);

        //发布给跟踪模块
        smartcar_msgs::Lane glane;  //原autoware控制使用
        geometry_msgs::TwistStamped plan_speed;
        plan_speed.twist.linear.x = 10 / 3.6;  // target_speed / 3.6; //m/s
        // if((n - match_index) < 50){
        //     plan_speed.twist.linear.x = 0;  //如果距离终点还剩50个点就刹车
        // }
        smartcar_msgs::Waypoint waypoint;
        for (int i = 0; i < final_best_path.size(); i++) {
            waypoint.pose.pose.position.x = final_best_path[i].x;
            waypoint.pose.pose.position.y = final_best_path[i].y;

            waypoint.twist.twist.linear.x = sqrt(pow(final_best_path[final_best_path.size() / 2].s_d, 2) +
                                                 pow(final_best_path[final_best_path.size() / 2].d_d, 2));
            waypoint.twist.twist.linear.x = std::min(waypoint.twist.twist.linear.x, target_vel);
        // glane.waypoints.begin()->twist.twist.linear.x = target_vel;

            // waypoint.twist.twist.linear.x = sqrt(pow(final_best_path[i ].s_d, 2) +
            //                                      pow(final_best_path[i ].d_d, 2));

            // if (waypoint.twist.twist.linear.x > 0 && waypoint.twist.twist.linear.x < 1) {
            //   waypoint.twist.twist.linear.x = 1;
            // }
            // if (glane.waypoints.end()->twist.twist.linear.x > 0) {
            //   waypoint.twist.twist.linear.x = 1.0;
            // }
            if (final_best_path[i].s_d > 0 && final_best_path[i].s_d < 1.0)
             {
              waypoint.twist.twist.linear.x = 1.0;
            }
            // ROS_INFO("index: %d   speed: %f", i, waypoint.twist.twist.linear.x);
            glane.waypoints.push_back(waypoint);
        }
        // glane.waypoints.begin()->twist.twist.linear.x = target_vel;
        local_path_pub.publish(glane);
        // printf("DSAAAAAAAAAAAAAAAA %ld\n", traj_features.size());
        if (Config_.FLAGS_Plan4NGSIM_) {
            string features_file_name = "/home/jinxiaoxin/master_graduation/Driving-IRL-NGSIM/features/" + ego_SL_human_path_.header.frame_id + ".csv";
            writeCsvFile(features_file_name, traj_features, traj_features.size(), ego_SL_human_path_.header.frame_id,  sub_odom_.header.frame_id);
            printf("The Vehicle id %s, Frame_odom %s, objc_frame %s, humanlikenexx %f \n",ego_SL_human_path_.header.frame_id.c_str(),  
            sub_odom_.header.frame_id.c_str(),msg_AllObstacle.header.frame_id.c_str(), traj_features.begin()->human_likeness);
            if (sub_odom_.header.frame_id != msg_AllObstacle.header.frame_id) errorrr++;
        }
        auto plan_end = std::chrono::system_clock::now();
        // string features_file_name = "/home/chiao/jinxiaoxin/Driving-IRL-NGSIM/train_data/Traningdatas.csv";
        // writeTraingData(features_file_name, training_datas,ego_SL_human_path_.header.frame_id,  sub_odom_.header.frame_id);
            // writeCsvFile(features_file_name, training_datas, traj_features.size(), ego_SL_human_path_.header.frame_id,  sub_odom_.header.frame_id);
        std::string file_name = "/home/jinxiaoxin/master_graduation/Driving-IRL-NGSIM/lattice_traj_test/Lattice_test_bylearning.csv";
        std::ofstream csvFile(file_name, std::ios::app);
        std::chrono::duration<double> cost_time = plan_end - plan_start;
        std::cout << ego_SL_human_path_.header.frame_id << "," 
        << sub_odom_.header.frame_id <<"," << std:: endl;
        csvFile << ego_SL_human_path_.header.frame_id << "," 
        << sub_odom_.header.frame_id <<"," 
        << all_pairs_num << "," 
        << in_valid_num << "," 
        << end_traj_num << "," 
        << car_info.speed << "," 
        << ACCTarget.relative_dis << "," 
        << ACCTarget.velocity << "," 
        << cost_time.count()*1000.0 << "," 
        << std::endl;
        std::cout << "cost_time: " << cost_time.count() * 1000 << " ms." << std::endl;
        ////////////////////////////////以上是局部规划//////////////////////////////////
        loop_rate.sleep();
        
    }
    std::cout << "ERROR : " << errorrr << std::endl;
    spin.stop();
}

DiscretizedTrajectory Dynamic_routing::FindDriveReferenceLineInfo() {
    double min_cost = std::numeric_limits<double>::infinity();
    int index_ = 0;
    for (int i = 0; i < multiple_best_path.size(); i++) {
        if (multiple_best_path[i].cost < min_cost) {
            index_ = i;
            min_cost = multiple_best_path[i].cost;
        }
    }
    return multiple_best_path[index_];
}