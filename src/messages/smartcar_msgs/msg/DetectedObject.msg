std_msgs/Header                 header

string                           id      #便于后续预测轨迹赋值每个点的id, 最后的id为perception_id+trajectory_index，即id=2_12，代表id为2的障碍物的第12个轨迹点。
string                          label
float32                         score   #Score as defined by the detection, Optional
std_msgs/ColorRGBA              color   # Define this object specific color
bool                            valid   # Defines if this object is valid, or invalid as defined by the filtering

################ 3D BB
string                          space_frame #3D Space coordinate frame of the object, required if pose and dimensions are defines
float64                         x  #car frame x-forward y-left, z-up
float64                         y
float64                         z
float64                         heading
float32                         length
float32                         width
float32                         height
float32                         speed
geometry_msgs/Point             foot_lf #车辆坐标系下，左前
geometry_msgs/Point             foot_lr #左后
geometry_msgs/Point             foot_rf #右前
geometry_msgs/Point             foot_rr #右后


float64                         utm_x  #utm frame x-forward y-left, z-up
float64                         utm_y
float64                         utm_z
float64                         utm_heading
geometry_msgs/Point             utm_foot_lf
geometry_msgs/Point             utm_foot_lr
geometry_msgs/Point             utm_foot_rf
geometry_msgs/Point             utm_foot_rr
geometry_msgs/Twist             utm_twist


bool                            pose_reliable
bool                            velocity_reliable
bool                            acceleration_reliable

############### Indicator information
uint8                          indicator_state # INDICATOR_LEFT = 0, INDICATOR_RIGHT = 1, INDICATOR_BOTH = 2, INDICATOR_NONE = 3

############### Behavior State of the Detected Object
uint8                           behavior_state # FORWARD_STATE = 0, STOPPING_STATE = 1, BRANCH_LEFT_STATE = 2, BRANCH_RIGHT_STATE = 3, YIELDING_STATE = 4, ACCELERATING_STATE = 5, SLOWDOWN_STATE = 6

#
string[]                        user_defined_info
bool is_static

My_Trajectory trajectory_  #预测轨迹