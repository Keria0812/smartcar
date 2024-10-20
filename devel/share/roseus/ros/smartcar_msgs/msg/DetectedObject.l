;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::DetectedObject)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'DetectedObject (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::DETECTEDOBJECT")
  (make-package "SMARTCAR_MSGS::DETECTEDOBJECT"))

(in-package "ROS")
;;//! \htmlinclude DetectedObject.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::DetectedObject
  :super ros::object
  :slots (_header _id _label _score _color _valid _space_frame _x _y _z _heading _length _width _height _speed _foot_lf _foot_lr _foot_rf _foot_rr _utm_x _utm_y _utm_z _utm_heading _utm_foot_lf _utm_foot_lr _utm_foot_rf _utm_foot_rr _utm_twist _pose_reliable _velocity_reliable _acceleration_reliable _indicator_state _behavior_state _user_defined_info _is_static _trajectory_ ))

(defmethod smartcar_msgs::DetectedObject
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:id __id) "")
    ((:label __label) "")
    ((:score __score) 0.0)
    ((:color __color) (instance std_msgs::ColorRGBA :init))
    ((:valid __valid) nil)
    ((:space_frame __space_frame) "")
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:heading __heading) 0.0)
    ((:length __length) 0.0)
    ((:width __width) 0.0)
    ((:height __height) 0.0)
    ((:speed __speed) 0.0)
    ((:foot_lf __foot_lf) (instance geometry_msgs::Point :init))
    ((:foot_lr __foot_lr) (instance geometry_msgs::Point :init))
    ((:foot_rf __foot_rf) (instance geometry_msgs::Point :init))
    ((:foot_rr __foot_rr) (instance geometry_msgs::Point :init))
    ((:utm_x __utm_x) 0.0)
    ((:utm_y __utm_y) 0.0)
    ((:utm_z __utm_z) 0.0)
    ((:utm_heading __utm_heading) 0.0)
    ((:utm_foot_lf __utm_foot_lf) (instance geometry_msgs::Point :init))
    ((:utm_foot_lr __utm_foot_lr) (instance geometry_msgs::Point :init))
    ((:utm_foot_rf __utm_foot_rf) (instance geometry_msgs::Point :init))
    ((:utm_foot_rr __utm_foot_rr) (instance geometry_msgs::Point :init))
    ((:utm_twist __utm_twist) (instance geometry_msgs::Twist :init))
    ((:pose_reliable __pose_reliable) nil)
    ((:velocity_reliable __velocity_reliable) nil)
    ((:acceleration_reliable __acceleration_reliable) nil)
    ((:indicator_state __indicator_state) 0)
    ((:behavior_state __behavior_state) 0)
    ((:user_defined_info __user_defined_info) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:is_static __is_static) nil)
    ((:trajectory_ __trajectory_) (instance smartcar_msgs::My_Trajectory :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _id (string __id))
   (setq _label (string __label))
   (setq _score (float __score))
   (setq _color __color)
   (setq _valid __valid)
   (setq _space_frame (string __space_frame))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _heading (float __heading))
   (setq _length (float __length))
   (setq _width (float __width))
   (setq _height (float __height))
   (setq _speed (float __speed))
   (setq _foot_lf __foot_lf)
   (setq _foot_lr __foot_lr)
   (setq _foot_rf __foot_rf)
   (setq _foot_rr __foot_rr)
   (setq _utm_x (float __utm_x))
   (setq _utm_y (float __utm_y))
   (setq _utm_z (float __utm_z))
   (setq _utm_heading (float __utm_heading))
   (setq _utm_foot_lf __utm_foot_lf)
   (setq _utm_foot_lr __utm_foot_lr)
   (setq _utm_foot_rf __utm_foot_rf)
   (setq _utm_foot_rr __utm_foot_rr)
   (setq _utm_twist __utm_twist)
   (setq _pose_reliable __pose_reliable)
   (setq _velocity_reliable __velocity_reliable)
   (setq _acceleration_reliable __acceleration_reliable)
   (setq _indicator_state (round __indicator_state))
   (setq _behavior_state (round __behavior_state))
   (setq _user_defined_info __user_defined_info)
   (setq _is_static __is_static)
   (setq _trajectory_ __trajectory_)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:label
   (&optional __label)
   (if __label (setq _label __label)) _label)
  (:score
   (&optional __score)
   (if __score (setq _score __score)) _score)
  (:color
   (&rest __color)
   (if (keywordp (car __color))
       (send* _color __color)
     (progn
       (if __color (setq _color (car __color)))
       _color)))
  (:valid
   (&optional (__valid :null))
   (if (not (eq __valid :null)) (setq _valid __valid)) _valid)
  (:space_frame
   (&optional __space_frame)
   (if __space_frame (setq _space_frame __space_frame)) _space_frame)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:heading
   (&optional __heading)
   (if __heading (setq _heading __heading)) _heading)
  (:length
   (&optional __length)
   (if __length (setq _length __length)) _length)
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:foot_lf
   (&rest __foot_lf)
   (if (keywordp (car __foot_lf))
       (send* _foot_lf __foot_lf)
     (progn
       (if __foot_lf (setq _foot_lf (car __foot_lf)))
       _foot_lf)))
  (:foot_lr
   (&rest __foot_lr)
   (if (keywordp (car __foot_lr))
       (send* _foot_lr __foot_lr)
     (progn
       (if __foot_lr (setq _foot_lr (car __foot_lr)))
       _foot_lr)))
  (:foot_rf
   (&rest __foot_rf)
   (if (keywordp (car __foot_rf))
       (send* _foot_rf __foot_rf)
     (progn
       (if __foot_rf (setq _foot_rf (car __foot_rf)))
       _foot_rf)))
  (:foot_rr
   (&rest __foot_rr)
   (if (keywordp (car __foot_rr))
       (send* _foot_rr __foot_rr)
     (progn
       (if __foot_rr (setq _foot_rr (car __foot_rr)))
       _foot_rr)))
  (:utm_x
   (&optional __utm_x)
   (if __utm_x (setq _utm_x __utm_x)) _utm_x)
  (:utm_y
   (&optional __utm_y)
   (if __utm_y (setq _utm_y __utm_y)) _utm_y)
  (:utm_z
   (&optional __utm_z)
   (if __utm_z (setq _utm_z __utm_z)) _utm_z)
  (:utm_heading
   (&optional __utm_heading)
   (if __utm_heading (setq _utm_heading __utm_heading)) _utm_heading)
  (:utm_foot_lf
   (&rest __utm_foot_lf)
   (if (keywordp (car __utm_foot_lf))
       (send* _utm_foot_lf __utm_foot_lf)
     (progn
       (if __utm_foot_lf (setq _utm_foot_lf (car __utm_foot_lf)))
       _utm_foot_lf)))
  (:utm_foot_lr
   (&rest __utm_foot_lr)
   (if (keywordp (car __utm_foot_lr))
       (send* _utm_foot_lr __utm_foot_lr)
     (progn
       (if __utm_foot_lr (setq _utm_foot_lr (car __utm_foot_lr)))
       _utm_foot_lr)))
  (:utm_foot_rf
   (&rest __utm_foot_rf)
   (if (keywordp (car __utm_foot_rf))
       (send* _utm_foot_rf __utm_foot_rf)
     (progn
       (if __utm_foot_rf (setq _utm_foot_rf (car __utm_foot_rf)))
       _utm_foot_rf)))
  (:utm_foot_rr
   (&rest __utm_foot_rr)
   (if (keywordp (car __utm_foot_rr))
       (send* _utm_foot_rr __utm_foot_rr)
     (progn
       (if __utm_foot_rr (setq _utm_foot_rr (car __utm_foot_rr)))
       _utm_foot_rr)))
  (:utm_twist
   (&rest __utm_twist)
   (if (keywordp (car __utm_twist))
       (send* _utm_twist __utm_twist)
     (progn
       (if __utm_twist (setq _utm_twist (car __utm_twist)))
       _utm_twist)))
  (:pose_reliable
   (&optional (__pose_reliable :null))
   (if (not (eq __pose_reliable :null)) (setq _pose_reliable __pose_reliable)) _pose_reliable)
  (:velocity_reliable
   (&optional (__velocity_reliable :null))
   (if (not (eq __velocity_reliable :null)) (setq _velocity_reliable __velocity_reliable)) _velocity_reliable)
  (:acceleration_reliable
   (&optional (__acceleration_reliable :null))
   (if (not (eq __acceleration_reliable :null)) (setq _acceleration_reliable __acceleration_reliable)) _acceleration_reliable)
  (:indicator_state
   (&optional __indicator_state)
   (if __indicator_state (setq _indicator_state __indicator_state)) _indicator_state)
  (:behavior_state
   (&optional __behavior_state)
   (if __behavior_state (setq _behavior_state __behavior_state)) _behavior_state)
  (:user_defined_info
   (&optional __user_defined_info)
   (if __user_defined_info (setq _user_defined_info __user_defined_info)) _user_defined_info)
  (:is_static
   (&optional (__is_static :null))
   (if (not (eq __is_static :null)) (setq _is_static __is_static)) _is_static)
  (:trajectory_
   (&rest __trajectory_)
   (if (keywordp (car __trajectory_))
       (send* _trajectory_ __trajectory_)
     (progn
       (if __trajectory_ (setq _trajectory_ (car __trajectory_)))
       _trajectory_)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _id
    4 (length _id)
    ;; string _label
    4 (length _label)
    ;; float32 _score
    4
    ;; std_msgs/ColorRGBA _color
    (send _color :serialization-length)
    ;; bool _valid
    1
    ;; string _space_frame
    4 (length _space_frame)
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float64 _heading
    8
    ;; float32 _length
    4
    ;; float32 _width
    4
    ;; float32 _height
    4
    ;; float32 _speed
    4
    ;; geometry_msgs/Point _foot_lf
    (send _foot_lf :serialization-length)
    ;; geometry_msgs/Point _foot_lr
    (send _foot_lr :serialization-length)
    ;; geometry_msgs/Point _foot_rf
    (send _foot_rf :serialization-length)
    ;; geometry_msgs/Point _foot_rr
    (send _foot_rr :serialization-length)
    ;; float64 _utm_x
    8
    ;; float64 _utm_y
    8
    ;; float64 _utm_z
    8
    ;; float64 _utm_heading
    8
    ;; geometry_msgs/Point _utm_foot_lf
    (send _utm_foot_lf :serialization-length)
    ;; geometry_msgs/Point _utm_foot_lr
    (send _utm_foot_lr :serialization-length)
    ;; geometry_msgs/Point _utm_foot_rf
    (send _utm_foot_rf :serialization-length)
    ;; geometry_msgs/Point _utm_foot_rr
    (send _utm_foot_rr :serialization-length)
    ;; geometry_msgs/Twist _utm_twist
    (send _utm_twist :serialization-length)
    ;; bool _pose_reliable
    1
    ;; bool _velocity_reliable
    1
    ;; bool _acceleration_reliable
    1
    ;; uint8 _indicator_state
    1
    ;; uint8 _behavior_state
    1
    ;; string[] _user_defined_info
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _user_defined_info)) 4
    ;; bool _is_static
    1
    ;; smartcar_msgs/My_Trajectory _trajectory_
    (send _trajectory_ :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; string _label
       (write-long (length _label) s) (princ _label s)
     ;; float32 _score
       (sys::poke _score (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; std_msgs/ColorRGBA _color
       (send _color :serialize s)
     ;; bool _valid
       (if _valid (write-byte -1 s) (write-byte 0 s))
     ;; string _space_frame
       (write-long (length _space_frame) s) (princ _space_frame s)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _heading
       (sys::poke _heading (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _length
       (sys::poke _length (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _width
       (sys::poke _width (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _height
       (sys::poke _height (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; geometry_msgs/Point _foot_lf
       (send _foot_lf :serialize s)
     ;; geometry_msgs/Point _foot_lr
       (send _foot_lr :serialize s)
     ;; geometry_msgs/Point _foot_rf
       (send _foot_rf :serialize s)
     ;; geometry_msgs/Point _foot_rr
       (send _foot_rr :serialize s)
     ;; float64 _utm_x
       (sys::poke _utm_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _utm_y
       (sys::poke _utm_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _utm_z
       (sys::poke _utm_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _utm_heading
       (sys::poke _utm_heading (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; geometry_msgs/Point _utm_foot_lf
       (send _utm_foot_lf :serialize s)
     ;; geometry_msgs/Point _utm_foot_lr
       (send _utm_foot_lr :serialize s)
     ;; geometry_msgs/Point _utm_foot_rf
       (send _utm_foot_rf :serialize s)
     ;; geometry_msgs/Point _utm_foot_rr
       (send _utm_foot_rr :serialize s)
     ;; geometry_msgs/Twist _utm_twist
       (send _utm_twist :serialize s)
     ;; bool _pose_reliable
       (if _pose_reliable (write-byte -1 s) (write-byte 0 s))
     ;; bool _velocity_reliable
       (if _velocity_reliable (write-byte -1 s) (write-byte 0 s))
     ;; bool _acceleration_reliable
       (if _acceleration_reliable (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _indicator_state
       (write-byte _indicator_state s)
     ;; uint8 _behavior_state
       (write-byte _behavior_state s)
     ;; string[] _user_defined_info
     (write-long (length _user_defined_info) s)
     (dolist (elem _user_defined_info)
       (write-long (length elem) s) (princ elem s)
       )
     ;; bool _is_static
       (if _is_static (write-byte -1 s) (write-byte 0 s))
     ;; smartcar_msgs/My_Trajectory _trajectory_
       (send _trajectory_ :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _label
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _label (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32 _score
     (setq _score (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; std_msgs/ColorRGBA _color
     (send _color :deserialize buf ptr-) (incf ptr- (send _color :serialization-length))
   ;; bool _valid
     (setq _valid (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _space_frame
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _space_frame (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _heading
     (setq _heading (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _length
     (setq _length (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _width
     (setq _width (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _height
     (setq _height (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; geometry_msgs/Point _foot_lf
     (send _foot_lf :deserialize buf ptr-) (incf ptr- (send _foot_lf :serialization-length))
   ;; geometry_msgs/Point _foot_lr
     (send _foot_lr :deserialize buf ptr-) (incf ptr- (send _foot_lr :serialization-length))
   ;; geometry_msgs/Point _foot_rf
     (send _foot_rf :deserialize buf ptr-) (incf ptr- (send _foot_rf :serialization-length))
   ;; geometry_msgs/Point _foot_rr
     (send _foot_rr :deserialize buf ptr-) (incf ptr- (send _foot_rr :serialization-length))
   ;; float64 _utm_x
     (setq _utm_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _utm_y
     (setq _utm_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _utm_z
     (setq _utm_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _utm_heading
     (setq _utm_heading (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; geometry_msgs/Point _utm_foot_lf
     (send _utm_foot_lf :deserialize buf ptr-) (incf ptr- (send _utm_foot_lf :serialization-length))
   ;; geometry_msgs/Point _utm_foot_lr
     (send _utm_foot_lr :deserialize buf ptr-) (incf ptr- (send _utm_foot_lr :serialization-length))
   ;; geometry_msgs/Point _utm_foot_rf
     (send _utm_foot_rf :deserialize buf ptr-) (incf ptr- (send _utm_foot_rf :serialization-length))
   ;; geometry_msgs/Point _utm_foot_rr
     (send _utm_foot_rr :deserialize buf ptr-) (incf ptr- (send _utm_foot_rr :serialization-length))
   ;; geometry_msgs/Twist _utm_twist
     (send _utm_twist :deserialize buf ptr-) (incf ptr- (send _utm_twist :serialization-length))
   ;; bool _pose_reliable
     (setq _pose_reliable (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _velocity_reliable
     (setq _velocity_reliable (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _acceleration_reliable
     (setq _acceleration_reliable (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _indicator_state
     (setq _indicator_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _behavior_state
     (setq _behavior_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; string[] _user_defined_info
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _user_defined_info (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _user_defined_info i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; bool _is_static
     (setq _is_static (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; smartcar_msgs/My_Trajectory _trajectory_
     (send _trajectory_ :deserialize buf ptr-) (incf ptr- (send _trajectory_ :serialization-length))
   ;;
   self)
  )

(setf (get smartcar_msgs::DetectedObject :md5sum-) "8263e8ba2bd27309693c5d19983a7eff")
(setf (get smartcar_msgs::DetectedObject :datatype-) "smartcar_msgs/DetectedObject")
(setf (get smartcar_msgs::DetectedObject :definition-)
      "std_msgs/Header                 header

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



(provide :smartcar_msgs/DetectedObject "8263e8ba2bd27309693c5d19983a7eff")


