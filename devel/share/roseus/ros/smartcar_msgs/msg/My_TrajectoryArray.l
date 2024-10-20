;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::My_TrajectoryArray)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'My_TrajectoryArray (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::MY_TRAJECTORYARRAY")
  (make-package "SMARTCAR_MSGS::MY_TRAJECTORYARRAY"))

(in-package "ROS")
;;//! \htmlinclude My_TrajectoryArray.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::My_TrajectoryArray
  :super ros::object
  :slots (_header _lanes _num ))

(defmethod smartcar_msgs::My_TrajectoryArray
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:lanes __lanes) ())
    ((:num __num) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _lanes __lanes)
   (setq _num (round __num))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:lanes
   (&rest __lanes)
   (if (keywordp (car __lanes))
       (send* _lanes __lanes)
     (progn
       (if __lanes (setq _lanes (car __lanes)))
       _lanes)))
  (:num
   (&optional __num)
   (if __num (setq _num __num)) _num)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; smartcar_msgs/My_Trajectory[] _lanes
    (apply #'+ (send-all _lanes :serialization-length)) 4
    ;; int32 _num
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; smartcar_msgs/My_Trajectory[] _lanes
     (write-long (length _lanes) s)
     (dolist (elem _lanes)
       (send elem :serialize s)
       )
     ;; int32 _num
       (write-long _num s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; smartcar_msgs/My_Trajectory[] _lanes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lanes (let (r) (dotimes (i n) (push (instance smartcar_msgs::My_Trajectory :init) r)) r))
     (dolist (elem- _lanes)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int32 _num
     (setq _num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smartcar_msgs::My_TrajectoryArray :md5sum-) "5ccdd33f237885519dadb3b742c24919")
(setf (get smartcar_msgs::My_TrajectoryArray :datatype-) "smartcar_msgs/My_TrajectoryArray")
(setf (get smartcar_msgs::My_TrajectoryArray :definition-)
      "Header header
My_Trajectory[] lanes
int32 num

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



(provide :smartcar_msgs/My_TrajectoryArray "5ccdd33f237885519dadb3b742c24919")


