#include <simulator/grid_publisher.h>

#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <tf/tf.h>

namespace ITS {
// Constructor
Grid::Grid() {
    nh.param("Tesla/length", length, 4.97);
    nh.param("Tesla/width", width, 1.6);
    nh.param("Tesla/heigth", heigth, 1.4);
    nh.param("Tesla/wheel_base", wheel_base, 2.97);
    nh.param("Tesla/rear_overhang", rear_overhang, 1.08);
    nh.param("Tesla/front_overhang", front_overhang, 0.92);
    nh.param("Tesla/tire_radius", tire_radius, 0.32);
    std::cout << length << " " << width <<" " << heigth<<" " <<wheel_base<< " "<< rear_overhang
        <<" " << front_overhang<<" " << tire_radius <<"\n";

}

// Destructor
Grid::~Grid() {}

void Grid::process_data(std::vector<struct object_info> &object_info_) {
    
    std::vector<struct Rect_point> RectArray;
    ROS_INFO("The object have %d\n", object_info_.size());
    smartcar_msgs::DetectedObjectArray DetectedObjectArray;
    for (int i = 0; i < object_info_.size(); i++) {
        //将原始坐标转为长方体几何中心坐标
        // 1、从sensor坐标系平移到车身坐标系,后轴中心为原点
        // printf("x %f", object_info_[i].x);
        // printf("  y %f", object_info_[i].y);
        // printf("  z %f", object_info_[i].z);
        // printf("  yaw %f\n", object_info_[i].heading * 57.1);
        double tmp_x = object_info_[i].x + (wheel_base + front_overhang);
        double tmp_y = object_info_[i].y;
        double tmp_z = object_info_[i].z;
        double tmp_yaw = object_info_[i].heading;
        // 2、计算几何中心
        tmp_x = tmp_x + object_info_[i].length / 2.0 * cos(tmp_yaw);
        tmp_y = tmp_y + object_info_[i].length / 2.0 * sin(tmp_yaw);
        tmp_z = tmp_z + object_info_[i].height / 2.0;
        // 3、求8个顶点，画bounding box
        // printf("object[%d]_x %f", i, tmp_x);
        // printf("  object[%d]_y %f", i, tmp_y);
        // printf("  object[%d]_z %f", i, tmp_z);
        // printf("  object[%d]_yaw %f\n", i, tmp_yaw);

        Eigen::Matrix3d rotz = Eigen::Matrix3d::Zero();
        rotz(0, 0) = cos(tmp_yaw);
        rotz(0, 1) = -sin(tmp_yaw);
        rotz(1, 0) = sin(tmp_yaw);
        rotz(1, 1) = cos(tmp_yaw);
        rotz(2, 2) = 1;

        Eigen::MatrixXd corners(3, 8);
        corners(0, 0) = object_info_[i].length / 2.0;
        corners(0, 1) = corners(0, 0);
        corners(0, 2) = -corners(0, 0);
        corners(0, 3) = -corners(0, 0);
        corners(0, 4) = corners(0, 0);
        corners(0, 5) = corners(0, 0);
        corners(0, 6) = -corners(0, 0);
        corners(0, 7) = -corners(0, 0);

        corners(1, 0) = object_info_[i].width / 2.0;
        corners(1, 1) = -corners(1, 0);
        corners(1, 2) = -corners(1, 0);
        corners(1, 3) = corners(1, 0);
        corners(1, 4) = corners(1, 0);
        corners(1, 5) = -corners(1, 0);
        corners(1, 6) = -corners(1, 0);
        corners(1, 7) = corners(1, 0);

        corners(2, 0) = object_info_[i].height / 2.0;
        corners(2, 1) = corners(2, 0);
        corners(2, 2) = corners(2, 0);
        corners(2, 3) = corners(2, 0);
        corners(2, 4) = -corners(2, 0);
        corners(2, 5) = -corners(2, 0);
        corners(2, 6) = -corners(2, 0);
        corners(2, 7) = -corners(2, 0);

        Eigen::MatrixXd tmp_corners_3d = (rotz * corners);
        for (int i = 0; i < 8; i++) {
            tmp_corners_3d(0, i) = tmp_corners_3d(0, i) + tmp_x;
            tmp_corners_3d(1, i) = tmp_corners_3d(1, i) + tmp_y;
            tmp_corners_3d(2, i) = tmp_corners_3d(2, i) + tmp_z;
        }
        Eigen::MatrixXd corners_3d = tmp_corners_3d.transpose();

        // for (int i = 0; i < 8; i++) {
        //     printf("x %f y %f z %f\n", corners_3d(i, 0), corners_3d(i, 1), corners_3d(i, 2));
        // }
        // std::cout << "  \n";

        //发布3D box
        publish_3Dbox_marker(corners_3d, i);

        //发布目标级数据
        smartcar_msgs::DetectedObject Detectedtmp_object;
        Detectedtmp_object.header.stamp = ros::Time::now();
        Detectedtmp_object.id = std::to_string(i * 100);
        Detectedtmp_object.label = "car";
        Detectedtmp_object.valid = 1;
        Detectedtmp_object.space_frame = "Vehicle frame";
        Detectedtmp_object.x = tmp_x;
        Detectedtmp_object.y = tmp_y;
        Detectedtmp_object.z = tmp_z;
        Detectedtmp_object.heading = tmp_yaw;
        Detectedtmp_object.length = object_info_[i].length;
        Detectedtmp_object.width = object_info_[i].width;
        Detectedtmp_object.height = object_info_[i].height;
        Detectedtmp_object.speed = object_info_[i].speed;
        Detectedtmp_object.pose_reliable = 1;
        Detectedtmp_object.velocity_reliable = 1;
        Detectedtmp_object.acceleration_reliable = 1;
        // DetectedObjectArray.objects.push_back(Detectedtmp_object);

        //存储每个长方体的四个顶点，用于转换为栅格
        struct Rect_point tmp_rect;
        tmp_rect.A = cv::Point2d(corners_3d(2,0), corners_3d(2,1));
        tmp_rect.B = cv::Point2d(corners_3d(1,0), corners_3d(1,1));
        tmp_rect.C = cv::Point2d(corners_3d(0,0), corners_3d(0,1));
        tmp_rect.D = cv::Point2d(corners_3d(3,0), corners_3d(3,1));
        tmp_rect.center = cv::Point2d(tmp_x, tmp_y);
        tmp_rect.radius = object_info_[i].length;

        Detectedtmp_object.foot_lf.x = tmp_rect.C.x;
        Detectedtmp_object.foot_lf.y = tmp_rect.C.y;

        Detectedtmp_object.foot_lr.x = tmp_rect.D.x;
        Detectedtmp_object.foot_lr.y = tmp_rect.D.y;

        Detectedtmp_object.foot_rf.x = tmp_rect.B.x;
        Detectedtmp_object.foot_rf.y = tmp_rect.B.y;

        Detectedtmp_object.foot_rr.x = tmp_rect.A.x;
        Detectedtmp_object.foot_rr.y = tmp_rect.A.y;

        local2global(Detectedtmp_object.foot_lf.x, Detectedtmp_object.foot_lf.y,
                    egocar.pose.position.x, egocar.pose.position.y, egocar.pose.orientation.z,
                    Detectedtmp_object.utm_foot_lf.x, Detectedtmp_object.utm_foot_lf.y);

        local2global(Detectedtmp_object.foot_lr.x, Detectedtmp_object.foot_lr.y,
                    egocar.pose.position.x, egocar.pose.position.y, egocar.pose.orientation.z,
                    Detectedtmp_object.utm_foot_lr.x, Detectedtmp_object.utm_foot_lr.y);

        local2global(Detectedtmp_object.foot_rf.x, Detectedtmp_object.foot_rf.y,
                    egocar.pose.position.x, egocar.pose.position.y, egocar.pose.orientation.z,
                    Detectedtmp_object.utm_foot_rf.x, Detectedtmp_object.utm_foot_rf.y);

        local2global(Detectedtmp_object.foot_rr.x, Detectedtmp_object.foot_rr.y,
                    egocar.pose.position.x, egocar.pose.position.y, egocar.pose.orientation.z,
                    Detectedtmp_object.utm_foot_rr.x, Detectedtmp_object.utm_foot_rr.y);
        
        local2global(Detectedtmp_object.x, Detectedtmp_object.y, Detectedtmp_object.heading,
                    egocar.pose.position.x, egocar.pose.position.y, egocar.pose.orientation.z,
                    Detectedtmp_object.utm_x, Detectedtmp_object.utm_y, Detectedtmp_object.utm_heading);

        Detectedtmp_object.utm_heading = tmp_yaw + egocar.pose.orientation.z;
        Detectedtmp_object.utm_z = tmp_z;
        

        DetectedObjectArray.objects.push_back(Detectedtmp_object);
        RectArray.push_back(tmp_rect);
        publish_3DboxId_marker(Detectedtmp_object.utm_x, Detectedtmp_object.utm_y, Detectedtmp_object.utm_z, 
                                    Detectedtmp_object.id, object_info_[i].height);
    }
    
    std::cout << " nobjects " << object_info_.size() << std::endl;
    std::cout << " RectArray size " << RectArray.size() << std::endl;
    std::cout <<"\n";
    if(DetectedObjectArray.objects.size() >0){
        DetectedObjectArray.header.stamp = ros::Time::now();
        DetectedObjectArray.num = DetectedObjectArray.objects.size();
        objects_pub.publish(DetectedObjectArray);
    }

    object2grid(RectArray);
}

void Grid::publish_3Dbox_marker(Eigen::MatrixXd &corners_3d_, int id_) {
    // publish target box with marker
    visualization_msgs::Marker line_strip;
    line_strip.header.frame_id = "base_link";
    line_strip.header.stamp = ros::Time::now();
    line_strip.ns = "target_box";  // namespace
    line_strip.action = visualization_msgs::Marker::ADD;
    line_strip.lifetime = ros::Duration(0.1);
    line_strip.pose.orientation.w = 1.0;
    line_strip.id = id_;                                       // unique id, useful when multiple markers exist.
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;  // marker type
    line_strip.scale.x = 0.1;                                  // width of the line
    line_strip.color.r = 0.0;
    line_strip.color.g = 1.0;
    line_strip.color.b = 0.0;  // color of the line: white.
    line_strip.color.a = 1.0;  //不透明度，设0则全透明
    geometry_msgs::Point p[8];
    // 填充是目标物的坐标
    for (int i = 0; i < 8; i++) {
        p[i].x = corners_3d_(i, 0);
        p[i].y = corners_3d_(i, 1);
        p[i].z = corners_3d_(i, 2);
    }
    // LINE_STRIP类型仅仅将line_strip.points中相邻的两个点相连，如0和1，1和2，2和3，为了保证矩形框的八条边都存在：
    line_strip.points.push_back(p[0]);
    line_strip.points.push_back(p[4]);
    line_strip.points.push_back(p[0]);
    line_strip.points.push_back(p[1]);
    line_strip.points.push_back(p[5]);
    line_strip.points.push_back(p[1]);
    line_strip.points.push_back(p[2]);
    line_strip.points.push_back(p[6]);
    line_strip.points.push_back(p[2]);
    line_strip.points.push_back(p[3]);
    line_strip.points.push_back(p[7]);
    line_strip.points.push_back(p[3]);
    line_strip.points.push_back(p[0]);
    for (int i = 4; i < 8; i++) {
        line_strip.points.push_back(p[i]);
    }
    line_strip.points.push_back(p[4]);

    box_pub.publish(line_strip);
}

void Grid::publish_3DboxId_marker(double x, double y, double z, std::string id_, double height) {
    visualization_msgs::Marker marker;
    marker.header.frame_id="map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "3DboxId_marker";
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.orientation.w = 1.0;
    marker.id = std::stoi(id_);
    marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    marker.lifetime = ros::Duration(0.2);

    marker.scale.z = 0.5;
    marker.color.b = 0;
    marker.color.g = 1;
    marker.color.r = 0;
    marker.color.a = 1;

    geometry_msgs::Pose pose;
    pose.position.x = x;
    pose.position.y = y;
    pose.position.z = z + height / 2.0 + 0.5;

    marker.text = "id: " + id_;
    marker.pose = pose;
    box_id_pub.publish(marker);

 
}

void Grid::object2grid(std::vector<struct Rect_point> &RectArray_) {

    std::vector<int8_t> encode_grid(grid_cloum * grid_row, -1);
 
    // std::vector<int8_t> *encode_grid = new std::vector<int8_t>(grid_row * grid_cloum, 0);
    for(int i=0; i < RectArray_.size(); i++){
        //根据矩形中心点找出所占栅格的大致范围，然后判断栅格是否在矩形框内
        double centerX = RectArray_[i].center.x + grid_cloum / 2 * grid_step; 
        double centerY = RectArray_[i].center.y + grid_row / 2 * grid_step;
        int grid_x = centerX / grid_step;
        int grid_y = centerY / grid_step;
        //不计算中心点超过栅格范围的
        if(grid_x > grid_cloum || grid_x <0 || grid_y > grid_row || grid_y< 0){
            continue;
        }
        // printf("  centerX %f ", centerX);
        // printf("  centerY %f \n", centerY);        
        // printf("  centerGridX %d ", grid_x);
        // printf("  centerGridY %d \n", grid_y);
        //目标栅格范围
        int num_step = std::ceil(RectArray_[i].radius / grid_step) / 2; //向上取整
        int min_cloum = std::max(0, grid_x - num_step);
        int max_cloum = std::min(grid_cloum, grid_x + num_step);
        int min_row = std::max(0, grid_y - num_step);
        int max_row = std::min(grid_row, grid_y + num_step);
        // printf("  num_step %d", num_step);
        // printf("  min_cloum %d", min_cloum);
        // printf("  max_cloum %d", max_cloum);
        // printf("  min_row %d", min_row);
        // printf("  max_row %d \n", max_row);

        //将计算目标栅格中心坐标，再移动到平移中心为（0，0），评断是否再矩形内，如果再，怎原栅格置1
        for(int j=min_cloum; j < max_cloum; j++){
            for(int k = min_row; k< max_row; k++){
                double tmp_grid_x = j * grid_step + grid_step/2.0 - grid_cloum / 2 * grid_step;
                double tmp_grid_y = k * grid_step + grid_step/2.0 - grid_row / 2 * grid_step;
                cv::Point2d tmp_P(tmp_grid_x, tmp_grid_y);
                // printf("  tmp_grid_x %f", tmp_P.x);
                // printf("  tmp_grid_y %f \n", tmp_P.y);
                if(isPointInRect(tmp_P, RectArray_[i])){
                    encode_grid[j + k * grid_cloum] = 127; //颜色
                    // printf("is grid %s\n", "true");
                } else {
                    encode_grid[j + k * grid_cloum] = -1;
                    // printf("is grid %s\n", "false");
                }

            }
        }
    }
    
    smartcar_msgs::Grid output1;
    output1.grid = encode_grid;
    output1.grid_nums = grid_nums;
    output1.height = grid_row;
    output1.height_step = grid_step;
    output1.timestamp = ros::Time::now();
    output1.width = grid_cloum;
    output1.width_step = grid_step;
    output1.header.stamp = ros::Time::now();
    grid_pub.publish(output1);

    nav_msgs::OccupancyGrid output2;
    output2.header.frame_id = "base_link";
    output2.header.stamp = ros::Time::now();
    output2.info.resolution = grid_step;
    output2.info.width = grid_cloum;
    output2.info.height = grid_row;
    output2.info.origin.position.x = -(grid_cloum / 2 * grid_step + grid_step/2.0);
    output2.info.origin.position.y = -(grid_row / 2 * grid_step + grid_step/2.0);
    output2.info.origin.position.z = 0.0;
    output2.info.origin.orientation.w = 1;
    output2.info.origin.orientation.x = 0;
    output2.info.origin.orientation.y = 0;
    output2.info.origin.orientation.z = 0;
    output2.data.resize(output2.info.width * output2.info.height);
    output2.data = encode_grid;
    occupancygrid_pub.publish(output2);

}

bool Grid::isPointInRect(cv::Point2d P, struct Rect_point rect) {
    //tl 左上角点， br 右下角点
    /**
     *  D--------------C
     *  |       P      |
     *  A--------------B
     *     
     *  AB X AP = (b.x - a.x, b.y - a.y) x (p.x - a.x, p.y - a.y) = 
     *               (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x -a.x); 
     *  BC X BP = (c.x - b.x, c.y - b.y) x (p.x - b.x, p.y - b.y) = 
     *               (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x);
     * */ 

    cv::Point2d A = rect.A;
    cv::Point2d B = rect.B;
    cv::Point2d C = rect.C;
    cv::Point2d D = rect.D;
    // printf(" A %f %f", A.x, A.y);
    // printf(" B %f %f", B.x, B.y);
    // printf(" C %f %f", C.x, C.y);
    // printf(" D %f %f\n", D.x, D.y);
    double x = P.x;
    double y = P.y;
    // printf("x = %f\n", x);
    double a = (B.x - A.x) * (y - A.y) - (B.y - A.y) * (x - A.x);
    double b = (C.x - B.x) * (y - B.y) - (C.y - B.y) * (x - B.x);
    double c = (D.x - C.x) * (y - C.y) - (D.y - C.y) * (x - C.x);
    double d = (A.x - D.x) * (y - D.y) - (A.y - D.y) * (x - D.x);
    if ((a >= 0 && b >= 0 && c >= 0 && d >= 0) || (a <= 0 && b <= 0 && c <= 0 && d <= 0)) {
        return true;
    }
    return false;
}

void Grid::local2global(const double &local_x, const double &local_y, const double &local_heading,
                    const double &ref_x, const double &ref_y, const double &ref_heading,
                    double &out_x, double &out_y, double &out_heading) {
                    
                    //将局部坐标系下的障碍物转为全局坐标系
                    double tmp_x = local_x * std::cos(ref_heading) + local_y * (-std::sin(ref_heading));;
                    double tmp_y = local_x * std::sin(ref_heading) + local_y * std::cos(ref_heading);
                    out_x = tmp_x + ref_x;
                    out_y = tmp_y + ref_y;
                    out_heading = local_heading + ref_heading;
                    ROS_INFO_STREAM("X  Y  heading: " << out_x <<" " << out_y << " " << out_heading << "\n");
                    
                    }

void Grid::local2global(const double &local_x, const double &local_y,
                    const double &ref_x, const double &ref_y, const double &ref_heading,
                    double &out_x, double &out_y) {
                    
                    //将局部坐标系下的障碍物转为全局坐标系
                    double tmp_x = local_x * std::cos(ref_heading) + local_y * (-std::sin(ref_heading));;
                    double tmp_y = local_x * std::sin(ref_heading) + local_y * std::cos(ref_heading);
                    out_x = tmp_x + ref_x;
                    out_y = tmp_y + ref_y;
                    ROS_INFO_STREAM("X  Y  :" << out_x <<" " << out_y << " " << "\n");
                    
                    }


}  // namespace ITS
