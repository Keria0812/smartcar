;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::RemoteCmd)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'RemoteCmd (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::REMOTECMD")
  (make-package "SMARTCAR_MSGS::REMOTECMD"))

(in-package "ROS")
;;//! \htmlinclude RemoteCmd.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::RemoteCmd
  :super ros::object
  :slots (_header _vehicle_cmd _control_mode ))

(defmethod smartcar_msgs::RemoteCmd
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:vehicle_cmd __vehicle_cmd) (instance smartcar_msgs::VehicleCmd :init))
    ((:control_mode __control_mode) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _vehicle_cmd __vehicle_cmd)
   (setq _control_mode (round __control_mode))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:vehicle_cmd
   (&rest __vehicle_cmd)
   (if (keywordp (car __vehicle_cmd))
       (send* _vehicle_cmd __vehicle_cmd)
     (progn
       (if __vehicle_cmd (setq _vehicle_cmd (car __vehicle_cmd)))
       _vehicle_cmd)))
  (:control_mode
   (&optional __control_mode)
   (if __control_mode (setq _control_mode __control_mode)) _control_mode)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; smartcar_msgs/VehicleCmd _vehicle_cmd
    (send _vehicle_cmd :serialization-length)
    ;; int32 _control_mode
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; smartcar_msgs/VehicleCmd _vehicle_cmd
       (send _vehicle_cmd :serialize s)
     ;; int32 _control_mode
       (write-long _control_mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; smartcar_msgs/VehicleCmd _vehicle_cmd
     (send _vehicle_cmd :deserialize buf ptr-) (incf ptr- (send _vehicle_cmd :serialization-length))
   ;; int32 _control_mode
     (setq _control_mode (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smartcar_msgs::RemoteCmd :md5sum-) "8e7e759a4d90007f22d93622c3d044bd")
(setf (get smartcar_msgs::RemoteCmd :datatype-) "smartcar_msgs/RemoteCmd")
(setf (get smartcar_msgs::RemoteCmd :definition-)
      "Header header
smartcar_msgs/VehicleCmd vehicle_cmd
int32 control_mode

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
MSG: smartcar_msgs/VehicleCmd
Header header
smartcar_msgs/SteerCmd steer_cmd
smartcar_msgs/AccelCmd accel_cmd
smartcar_msgs/BrakeCmd brake_cmd
smartcar_msgs/LampCmd lamp_cmd
int32 gear
int32 mode
geometry_msgs/TwistStamped twist_cmd
smartcar_msgs/ControlCommand ctrl_cmd
int32 emergency

================================================================================
MSG: smartcar_msgs/SteerCmd
Header header
int32 steer

================================================================================
MSG: smartcar_msgs/AccelCmd
Header header
int32 accel

================================================================================
MSG: smartcar_msgs/BrakeCmd
Header header
int32 brake

================================================================================
MSG: smartcar_msgs/LampCmd
Header header
int32 l
int32 r

================================================================================
MSG: geometry_msgs/TwistStamped
# A twist with reference coordinate frame and timestamp
Header header
Twist twist

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
MSG: smartcar_msgs/ControlCommand
float64 linear_velocity #m/s
float64 linear_acceleration #m/s^2
float64 steering_angle #rad
float64 steering_speed #rad/s
")



(provide :smartcar_msgs/RemoteCmd "8e7e759a4d90007f22d93622c3d044bd")


