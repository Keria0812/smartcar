;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::My_Trajectory)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'My_Trajectory (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::MY_TRAJECTORY")
  (make-package "SMARTCAR_MSGS::MY_TRAJECTORY"))

(in-package "ROS")
;;//! \htmlinclude My_Trajectory.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::My_Trajectory
  :super ros::object
  :slots (_header _lane_id _ESTOP _trajectory_points _num ))

(defmethod smartcar_msgs::My_Trajectory
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:lane_id __lane_id) 0)
    ((:ESTOP __ESTOP) nil)
    ((:trajectory_points __trajectory_points) ())
    ((:num __num) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _lane_id (round __lane_id))
   (setq _ESTOP __ESTOP)
   (setq _trajectory_points __trajectory_points)
   (setq _num (round __num))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:lane_id
   (&optional __lane_id)
   (if __lane_id (setq _lane_id __lane_id)) _lane_id)
  (:ESTOP
   (&optional (__ESTOP :null))
   (if (not (eq __ESTOP :null)) (setq _ESTOP __ESTOP)) _ESTOP)
  (:trajectory_points
   (&rest __trajectory_points)
   (if (keywordp (car __trajectory_points))
       (send* _trajectory_points __trajectory_points)
     (progn
       (if __trajectory_points (setq _trajectory_points (car __trajectory_points)))
       _trajectory_points)))
  (:num
   (&optional __num)
   (if __num (setq _num __num)) _num)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _lane_id
    4
    ;; bool _ESTOP
    1
    ;; smartcar_msgs/My_Trajectory_Point[] _trajectory_points
    (apply #'+ (send-all _trajectory_points :serialization-length)) 4
    ;; int32 _num
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _lane_id
       (write-long _lane_id s)
     ;; bool _ESTOP
       (if _ESTOP (write-byte -1 s) (write-byte 0 s))
     ;; smartcar_msgs/My_Trajectory_Point[] _trajectory_points
     (write-long (length _trajectory_points) s)
     (dolist (elem _trajectory_points)
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
   ;; int32 _lane_id
     (setq _lane_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _ESTOP
     (setq _ESTOP (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; smartcar_msgs/My_Trajectory_Point[] _trajectory_points
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _trajectory_points (let (r) (dotimes (i n) (push (instance smartcar_msgs::My_Trajectory_Point :init) r)) r))
     (dolist (elem- _trajectory_points)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int32 _num
     (setq _num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smartcar_msgs::My_Trajectory :md5sum-) "71feceee353912c5f03c9c52a30dd4cf")
(setf (get smartcar_msgs::My_Trajectory :datatype-) "smartcar_msgs/My_Trajectory")
(setf (get smartcar_msgs::My_Trajectory :definition-)
      "Header header
int32 lane_id
bool ESTOP
My_Trajectory_Point[] trajectory_points
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



(provide :smartcar_msgs/My_Trajectory "71feceee353912c5f03c9c52a30dd4cf")


