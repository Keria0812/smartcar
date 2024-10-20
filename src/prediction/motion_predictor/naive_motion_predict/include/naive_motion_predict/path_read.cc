#include <naive_motion_predict/path_read.h>

namespace smartcar {
namespace prediction {


/**
 * @brief Get the all files object
 * 
 * @param dir_in 
 * @param files 
 * @return true 
 * @return false 
 */
bool get_all_files(const std::string& dir_in, std::vector<std::string>& files) {
    if (dir_in.empty()) {
        return false;
    }
    struct stat s;
    stat(dir_in.c_str(), &s);
    if (!S_ISDIR(s.st_mode)) {
        return false;
    }
    DIR* open_dir = opendir(dir_in.c_str());
    if (NULL == open_dir) {
        std::exit(EXIT_FAILURE);
    }
    dirent* p = nullptr;
    while( (p = readdir(open_dir)) != nullptr) {
        struct stat st;
        if (p->d_name[0] != '.') {
            //因为是使用devC++ 获取windows下的文件，所以使用了 "\" ,linux下要换成"/"
            std::string name = dir_in + std::string("/") + std::string(p->d_name);
            stat(name.c_str(), &st);
            if (S_ISDIR(st.st_mode)) {
                get_all_files(name, files);
            }
            else if (S_ISREG(st.st_mode)) {
                files.push_back(name);
            }
        }
    }
    closedir(open_dir);
    return true;
}

/**
 * @brief 
 * 
 * @param files 
 */
std::vector<std::string> 
remove_erro_files(const std::vector<std::string>& files, const std::string& target_type) {
    std::vector<std::string> tmp_files;
    for (auto &file : files) {
        if (file.find(target_type) != std::string::npos) {
            tmp_files.push_back(file);
        }
    }

    return tmp_files;
}

/**
 * @brief 
 * 
 * @param filename 
 * @param scale 
 * @param waypoints 
 */
void loadWaypoints(const std::string filename, smartcar_msgs::My_Trajectory &waypoints) {

    waypoints.trajectory_points.resize(0);
    // double x, y, yaw;

    /*读取逗号分割，中间无空格
    20,30
    19,20.0这个格式*/
    // FILE *file = fopen(filename.c_str(), "rt");
    // if(file == nullptr){
    //     ROS_ERROR("no found waypoints");
    //     exit(0);
    // }
    // while(fscanf(file, "%lf,%lf", &x, &y) != EOF) {
    //     geometry_msgs::Point point;
    //     point.x = scale * x;
    //     point.y = scale * y;
    //     point.z = 0;
    //     ROS_INFO("X  %lf   Y   %lf",  point.x,  point.y);
    //     waypoints->push_back(point);
    // }
    // fclose(file);

    //读取tab分割
    // std::string input;
    // double temp1, temp2, temp3;
    // std::ifstream fin;
    // bool error = false;
    // fin.open(filename.c_str());
    // if (fin.fail()) {
    //     ROS_ERROR("no found waypoints");
    //     exit(0);
    // }
    // while(true){
    //     getline(fin,input);
    //     if (!fin) break; //check for eof
 
    //     std::istringstream buffer(input);
    //     buffer >> temp1 >> temp2 >> temp3;
 
    //     //check for non numerical input
    //     //and less/more input than needed
    //     if (!buffer || !buffer.eof())
    //     {
    //         error=true;
    //         break;
    //     }
    //     geometry_msgs::Point point;
    //     point.x = scale * temp1;
    //     point.y = scale * temp2;
    //     point.z = 0;
    //     waypoints->push_back(point);
 
    //     //do what you want with temp1 and temp2
    //     // printf("X %.3lf\tY %.3lf\tYaw %.3lf\n", temp1, temp2, temp3);
    // }
    // if (error)
    //     std::cout << "file is corrupted..." << std::endl;
    // fin.close();

    //自动获取Tab分割数据，不用指定行列
    std::ifstream fin;
    fin.open(filename);
    if (fin.fail()) {
        ROS_ERROR("no found reference line");
        exit(0);
    }
    std::string test = "";
    std::vector<std::vector<double>> tmpMyData;
    while (std::getline(fin, test))  //全局函数，隶属于<string>头文件，空行也会被读入，但流数据为空
    {
        if (test == "") continue;  //排除空行
        std::stringstream os_data(test);
        double tmp;
        std::vector<double> mydata;
        while (os_data >> tmp) {
            // ROS_INFO("into");
            // ROS_INFO("tmp: %.3f", tmp);
            mydata.push_back(tmp);
        }
        tmpMyData.push_back(mydata);
    }
    // std::cout << "MyData-row " << tmpMyData.size() << std::endl;
    // if (tmpMyData.size() > 0) {
    //     std::cout << "MyData-column " << tmpMyData[0].size() << std::endl;
    // }

    // for (int i = 0; i < tmpMyData.size(); i++) {
    //     for (int j = 0; j < tmpMyData[0].size(); j++) {
    //         std::cout << tmpMyData[i][j] << "    ";
    //     }
    //     std::cout << std::endl;
    // }

    //将读取的数据赋值给轨迹
    for (size_t i = 0; i < tmpMyData.size(); i++) {
        smartcar_msgs::My_Trajectory_Point tmp_point;
        tmp_point.x = tmpMyData[i][0];
        tmp_point.y = tmpMyData[i][1];
        tmp_point.theta = tmpMyData[i][2];
        waypoints.trajectory_points.push_back(tmp_point);
    }
    waypoints.num = tmpMyData.size();

}

void read_csv(const std::string filename, smartcar_msgs::My_Trajectory &waypoints) {
    // 读文件
    std::cout << "开始处理记录的轨迹\n";
    std::ifstream inFile(filename, std::ios::in);
    std::string lineStr;
    std::vector<std::vector<double>> strArray;
    while (getline(inFile, lineStr)){
      // 打印整行字符串
    //   std::cout << lineStr << std::endl;
      // 存成二维表结构
      std::stringstream ss(lineStr);
      std::string str;
      std::vector<double> lineArray;
      // 按照逗号分隔
      while (getline(ss, str, ',')) {
        if (str == "time(s)") {
          std::cout << "剔除标题行\n";
          break;;
        } else {
          std::stringstream stream;
          double tmp = 0;
          stream << str;//向stream中插入str
          stream >> tmp;
          lineArray.push_back(tmp);
        }
      }

      if (!lineArray.empty()) {
        strArray.push_back(lineArray);
      }


    }

    // for (long unsigned int i = 0; i < strArray.size(); i++) {
    //   for (long unsigned int j = 0; j < strArray[i].size(); j++) {
    //     std::cout <<strArray[i][j] << ",";
    //   }
    //   std::cout << "\n";
    // }
    std::cout << "traj_row: " << strArray.size() << std::endl;
    if (!strArray.empty()) std::cout << "traj_column: " << strArray[0].size() << std::endl; 

    waypoints.trajectory_points.resize(0);
    //将读取的数据赋值给轨迹
    for (size_t i = 0; i < strArray.size(); i++) {
        smartcar_msgs::My_Trajectory_Point tmp_point;
        tmp_point.relative_time = strArray[i][0];
        tmp_point.x = strArray[i][1];
        tmp_point.y = strArray[i][2];
        tmp_point.z = strArray[i][3];
        tmp_point.theta = strArray[i][4];
        tmp_point.v = strArray[i][5];
        waypoints.trajectory_points.push_back(tmp_point);
    }
    waypoints.num = strArray.size();   
}

/**
 * @brief 
 * 
 * @param waypoints 
 * @param path 
 */
void interpolatePathNaive(const smartcar_msgs::My_Trajectory &waypoints, nav_msgs::Path &path) {
    path.poses.clear();
    path.header.frame_id = "map";
    path.header.stamp = ros::Time::now();

    for(size_t i = 0; i < waypoints.trajectory_points.size(); i++) {
        geometry_msgs::PoseStamped pose;

        pose.pose.position.x = waypoints.trajectory_points[i].x;
        pose.pose.position.y = waypoints.trajectory_points[i].y;
        
        geometry_msgs::Quaternion quat_tmp;
        quat_tmp = tf::createQuaternionMsgFromRollPitchYaw(0.0, 0.0, NormalizeAngle(waypoints.trajectory_points[i].theta));
        pose.pose.orientation = quat_tmp;

        path.poses.push_back(pose);
    }
}


}   //namespace prediction
}   //namespace smartcar
