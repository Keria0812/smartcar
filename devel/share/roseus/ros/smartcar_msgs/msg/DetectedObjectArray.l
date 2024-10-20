;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::DetectedObjectArray)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'DetectedObjectArray (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::DETECTEDOBJECTARRAY")
  (make-package "SMARTCAR_MSGS::DETECTEDOBJECTARRAY"))

(in-package "ROS")
;;//! \htmlinclude DetectedObjectArray.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::DetectedObjectArray
  :super ros::object
  :slots (_header _objects _num ))

(defmethod smartcar_msgs::DetectedObjectArray
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:objects __objects) ())
    ((:num __num) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _objects __objects)
   (setq _num (round __num))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:objects
   (&rest __objects)
   (if (keywordp (car __objects))
       (send* _objects __objects)
     (progn
       (if __objects (setq _objects (car __objects)))
       _objects)))
  (:num
   (&optional __num)
   (if __num (setq _num __num)) _num)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; smartcar_msgs/DetectedObject[] _objects
    (apply #'+ (send-all _objects :serialization-length)) 4
    ;; uint32 _num
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; smartcar_msgs/DetectedObject[] _objects
     (write-long (length _objects) s)
     (dolist (elem _objects)
       (send elem :serialize s)
       )
     ;; uint32 _num
       (write-long _num s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; smartcar_msgs/DetectedObject[] _objects
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _objects (let (r) (dotimes (i n) (push (instance smartcar_msgs::DetectedObject :init) r)) r))
     (dolist (elem- _objects)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; uint32 _num
     (setq _num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smartcar_msgs::DetectedObjectArray :md5sum-) "c68050d331471548543425b21258f71a")
(setf (get smartcar_msgs::DetectedObjectArray :datatype-) "smartcar_msgs/DetectedObjectArray")
(setf (get smartcar_msgs::DetectedObjectArray :definition-)
      "std_msgs/Header header
DetectedObject[] objects
uint32 num
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: smartcar_msgs/DetectedObject
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
================================================================================
MSG: std_msgs/ColorRGBA
float32 r
float32 g
float32 b
float32 a

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Twist
# This expresses velocity in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
================================================================================
MSG: smartcar_msgs/My_Trajectory
Header header
int32 lane_id
bool ESTOP
My_Trajectory_Point[] trajectory_points
int32 num

================================================================================
MSG: smartcar_msgs/My_Trajectory_Point
float64 x
float64 y
float64 z
float64 theta
float64 kappa
float64 s
float64 l
float64 dkappa
float64 ddkappa
float64 v
float64 a
float64 relative_time
float64 gear

")



(provide :smartcar_msgs/DetectedObjectArray "c68050d331471548543425b21258f71a")


