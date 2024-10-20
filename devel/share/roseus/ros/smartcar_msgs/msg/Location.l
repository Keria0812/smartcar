;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::Location)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'Location (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::LOCATION")
  (make-package "SMARTCAR_MSGS::LOCATION"))

(in-package "ROS")
;;//! \htmlinclude Location.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::Location
  :super ros::object
  :slots (_header _ins_time _global_pos _wgs84_pos _global_speed _accelerate _orientation _rpy_rate _speed _v_x _v_y _v_z _accel_x _accel_y _accel_z _ins_std_error _ins_data_info _INS_status ))

(defmethod smartcar_msgs::Location
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:ins_time __ins_time) (make-array 2 :initial-element 0 :element-type :integer))
    ((:global_pos __global_pos) (instance geometry_msgs::Point :init))
    ((:wgs84_pos __wgs84_pos) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:global_speed __global_speed) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:accelerate __accelerate) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:orientation __orientation) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:rpy_rate __rpy_rate) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:speed __speed) 0.0)
    ((:v_x __v_x) 0.0)
    ((:v_y __v_y) 0.0)
    ((:v_z __v_z) 0.0)
    ((:accel_x __accel_x) 0.0)
    ((:accel_y __accel_y) 0.0)
    ((:accel_z __accel_z) 0.0)
    ((:ins_std_error __ins_std_error) (make-array 4 :initial-element 0.0 :element-type :float))
    ((:ins_data_info __ins_data_info) (make-array 3 :initial-element 0 :element-type :integer))
    ((:INS_status __INS_status) "")
    )
   (send-super :init)
   (setq _header __header)
   (setq _ins_time __ins_time)
   (setq _global_pos __global_pos)
   (setq _wgs84_pos __wgs84_pos)
   (setq _global_speed __global_speed)
   (setq _accelerate __accelerate)
   (setq _orientation __orientation)
   (setq _rpy_rate __rpy_rate)
   (setq _speed (float __speed))
   (setq _v_x (float __v_x))
   (setq _v_y (float __v_y))
   (setq _v_z (float __v_z))
   (setq _accel_x (float __accel_x))
   (setq _accel_y (float __accel_y))
   (setq _accel_z (float __accel_z))
   (setq _ins_std_error __ins_std_error)
   (setq _ins_data_info __ins_data_info)
   (setq _INS_status (string __INS_status))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:ins_time
   (&optional __ins_time)
   (if __ins_time (setq _ins_time __ins_time)) _ins_time)
  (:global_pos
   (&rest __global_pos)
   (if (keywordp (car __global_pos))
       (send* _global_pos __global_pos)
     (progn
       (if __global_pos (setq _global_pos (car __global_pos)))
       _global_pos)))
  (:wgs84_pos
   (&optional __wgs84_pos)
   (if __wgs84_pos (setq _wgs84_pos __wgs84_pos)) _wgs84_pos)
  (:global_speed
   (&optional __global_speed)
   (if __global_speed (setq _global_speed __global_speed)) _global_speed)
  (:accelerate
   (&optional __accelerate)
   (if __accelerate (setq _accelerate __accelerate)) _accelerate)
  (:orientation
   (&optional __orientation)
   (if __orientation (setq _orientation __orientation)) _orientation)
  (:rpy_rate
   (&optional __rpy_rate)
   (if __rpy_rate (setq _rpy_rate __rpy_rate)) _rpy_rate)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:v_x
   (&optional __v_x)
   (if __v_x (setq _v_x __v_x)) _v_x)
  (:v_y
   (&optional __v_y)
   (if __v_y (setq _v_y __v_y)) _v_y)
  (:v_z
   (&optional __v_z)
   (if __v_z (setq _v_z __v_z)) _v_z)
  (:accel_x
   (&optional __accel_x)
   (if __accel_x (setq _accel_x __accel_x)) _accel_x)
  (:accel_y
   (&optional __accel_y)
   (if __accel_y (setq _accel_y __accel_y)) _accel_y)
  (:accel_z
   (&optional __accel_z)
   (if __accel_z (setq _accel_z __accel_z)) _accel_z)
  (:ins_std_error
   (&optional __ins_std_error)
   (if __ins_std_error (setq _ins_std_error __ins_std_error)) _ins_std_error)
  (:ins_data_info
   (&optional __ins_data_info)
   (if __ins_data_info (setq _ins_data_info __ins_data_info)) _ins_data_info)
  (:INS_status
   (&optional __INS_status)
   (if __INS_status (setq _INS_status __INS_status)) _INS_status)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32[2] _ins_time
    (* 4    2)
    ;; geometry_msgs/Point _global_pos
    (send _global_pos :serialization-length)
    ;; float64[3] _wgs84_pos
    (* 8    3)
    ;; float32[3] _global_speed
    (* 4    3)
    ;; float32[3] _accelerate
    (* 4    3)
    ;; float32[3] _orientation
    (* 4    3)
    ;; float32[3] _rpy_rate
    (* 4    3)
    ;; float64 _speed
    8
    ;; float64 _v_x
    8
    ;; float64 _v_y
    8
    ;; float64 _v_z
    8
    ;; float64 _accel_x
    8
    ;; float64 _accel_y
    8
    ;; float64 _accel_z
    8
    ;; float32[4] _ins_std_error
    (* 4    4)
    ;; int32[3] _ins_data_info
    (* 4    3)
    ;; string _INS_status
    4 (length _INS_status)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32[2] _ins_time
     (dotimes (i 2)
       (write-long (elt _ins_time i) s)
       )
     ;; geometry_msgs/Point _global_pos
       (send _global_pos :serialize s)
     ;; float64[3] _wgs84_pos
     (dotimes (i 3)
       (sys::poke (elt _wgs84_pos i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float32[3] _global_speed
     (dotimes (i 3)
       (sys::poke (elt _global_speed i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _accelerate
     (dotimes (i 3)
       (sys::poke (elt _accelerate i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _orientation
     (dotimes (i 3)
       (sys::poke (elt _orientation i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _rpy_rate
     (dotimes (i 3)
       (sys::poke (elt _rpy_rate i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float64 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _v_x
       (sys::poke _v_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _v_y
       (sys::poke _v_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _v_z
       (sys::poke _v_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _accel_x
       (sys::poke _accel_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _accel_y
       (sys::poke _accel_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _accel_z
       (sys::poke _accel_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32[4] _ins_std_error
     (dotimes (i 4)
       (sys::poke (elt _ins_std_error i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; int32[3] _ins_data_info
     (dotimes (i 3)
       (write-long (elt _ins_data_info i) s)
       )
     ;; string _INS_status
       (write-long (length _INS_status) s) (princ _INS_status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32[2] _ins_time
   (dotimes (i (length _ins_time))
     (setf (elt _ins_time i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     )
   ;; geometry_msgs/Point _global_pos
     (send _global_pos :deserialize buf ptr-) (incf ptr- (send _global_pos :serialization-length))
   ;; float64[3] _wgs84_pos
   (dotimes (i (length _wgs84_pos))
     (setf (elt _wgs84_pos i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float32[3] _global_speed
   (dotimes (i (length _global_speed))
     (setf (elt _global_speed i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _accelerate
   (dotimes (i (length _accelerate))
     (setf (elt _accelerate i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _orientation
   (dotimes (i (length _orientation))
     (setf (elt _orientation i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _rpy_rate
   (dotimes (i (length _rpy_rate))
     (setf (elt _rpy_rate i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float64 _speed
     (setq _speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _v_x
     (setq _v_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _v_y
     (setq _v_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _v_z
     (setq _v_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _accel_x
     (setq _accel_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _accel_y
     (setq _accel_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _accel_z
     (setq _accel_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32[4] _ins_std_error
   (dotimes (i (length _ins_std_error))
     (setf (elt _ins_std_error i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; int32[3] _ins_data_info
   (dotimes (i (length _ins_data_info))
     (setf (elt _ins_data_info i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     )
   ;; string _INS_status
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _INS_status (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get smartcar_msgs::Location :md5sum-) "00db5d5e3e65b48b95b9219165f53168")
(setf (get smartcar_msgs::Location :datatype-) "smartcar_msgs/Location")
(setf (get smartcar_msgs::Location :definition-)
      "Header	   header # ROS time(s)

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
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :smartcar_msgs/Location "00db5d5e3e65b48b95b9219165f53168")


