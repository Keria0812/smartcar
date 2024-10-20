;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::VehicleInfo)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'VehicleInfo (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::VEHICLEINFO")
  (make-package "SMARTCAR_MSGS::VEHICLEINFO"))

(in-package "ROS")
;;//! \htmlinclude VehicleInfo.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::VehicleInfo
  :super ros::object
  :slots (_header _localization _longitudinal_data _lateral_data ))

(defmethod smartcar_msgs::VehicleInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:localization __localization) (instance geometry_msgs::Point :init))
    ((:longitudinal_data __longitudinal_data) (instance smartcar_msgs::LongitudinalData :init))
    ((:lateral_data __lateral_data) (instance smartcar_msgs::LateralData :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _localization __localization)
   (setq _longitudinal_data __longitudinal_data)
   (setq _lateral_data __lateral_data)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:localization
   (&rest __localization)
   (if (keywordp (car __localization))
       (send* _localization __localization)
     (progn
       (if __localization (setq _localization (car __localization)))
       _localization)))
  (:longitudinal_data
   (&rest __longitudinal_data)
   (if (keywordp (car __longitudinal_data))
       (send* _longitudinal_data __longitudinal_data)
     (progn
       (if __longitudinal_data (setq _longitudinal_data (car __longitudinal_data)))
       _longitudinal_data)))
  (:lateral_data
   (&rest __lateral_data)
   (if (keywordp (car __lateral_data))
       (send* _lateral_data __lateral_data)
     (progn
       (if __lateral_data (setq _lateral_data (car __lateral_data)))
       _lateral_data)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Point _localization
    (send _localization :serialization-length)
    ;; smartcar_msgs/LongitudinalData _longitudinal_data
    (send _longitudinal_data :serialization-length)
    ;; smartcar_msgs/LateralData _lateral_data
    (send _lateral_data :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Point _localization
       (send _localization :serialize s)
     ;; smartcar_msgs/LongitudinalData _longitudinal_data
       (send _longitudinal_data :serialize s)
     ;; smartcar_msgs/LateralData _lateral_data
       (send _lateral_data :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Point _localization
     (send _localization :deserialize buf ptr-) (incf ptr- (send _localization :serialization-length))
   ;; smartcar_msgs/LongitudinalData _longitudinal_data
     (send _longitudinal_data :deserialize buf ptr-) (incf ptr- (send _longitudinal_data :serialization-length))
   ;; smartcar_msgs/LateralData _lateral_data
     (send _lateral_data :deserialize buf ptr-) (incf ptr- (send _lateral_data :serialization-length))
   ;;
   self)
  )

(setf (get smartcar_msgs::VehicleInfo :md5sum-) "ce1548f612651099d85d928f1bef6a2e")
(setf (get smartcar_msgs::VehicleInfo :datatype-) "smartcar_msgs/VehicleInfo")
(setf (get smartcar_msgs::VehicleInfo :definition-)
      "Header header
geometry_msgs/Point localization
LongitudinalData longitudinal_data
LateralData lateral_data


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

================================================================================
MSG: smartcar_msgs/LongitudinalData
float64 vel_from_localization
float64 vel_from_wheels
float64 acceleration
float64 traveled_distance
float64 fl_wheel_angular_velocity
float64 fr_wheel_angular_velocity
float64 bl_wheel_angular_velocity
float64 br_wheel_angular_velocity
float64 gas_percent
float64 fl_gas_torque
float64 fr_gas_torque
float64 bl_gas_torque
float64 br_gas_torque
float64 fl_brake_Torque
float64 fr_brake_torque
float64 bl_brake_torque
float64 br_brake_torque

================================================================================
MSG: smartcar_msgs/LateralData
float64 heading_angle
float64 steering_wheel_angle_actual
float64 steering_wheel_expected
float64 steering_wheel_error
float64 steering_wheel_cmd

float64 fl_steering_angle_actual
float64 fr_steering_angle_actual
float64 single_track_steering_angle
float64 fl_steering_angle_expected
float64 fr_steering_angle_expected
float64 fl_steering_error
float64 fr_steering_error
float64 fl_steering_cmd
float64 fr_steering_cmd


")



(provide :smartcar_msgs/VehicleInfo "ce1548f612651099d85d928f1bef6a2e")


