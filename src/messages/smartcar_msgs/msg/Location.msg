Header	   header # ROS time(s)

int32[2]   ins_time # GPS weeks, GPS million seconds
geometry_msgs/Point global_pos # x,y, east-north-sky frame(m)
float64[3] wgs84_pos # lon,lat,alt, WGS84(rad,rad,m)
float32[3] global_speed # east_speed,north_speed,up_speed,east-north-sky frame(m/s)
float32[3] accelerate # /* m/s^2, utm坐标系 */
float32[3] orientation # roll,pitch,yaw, Vehicle/Guass frame(rad,rad,rad)
float32[3] rpy_rate # roll_rate, pitch_rate, yaw_rate, Vehicle frame(rad/s)
float64    speed # 总的速度
float64    v_x # base_link坐标系
float64    v_y
float64    v_z
float64 accel_x # base_link坐标系
float64 accel_y 
float64 accel_z 

float32[4] ins_std_error # std_lat, std_lon, std_height, std_heading
int32[3]   ins_data_info # ins_num_satellite, gps_delay , wheel_speed
string     INS_status # 0_NONE_,  16_SINGLE_, 17_PSRDIFF_ , 34_NARROW_FLOAT_, 50_NARROW_INT_
