;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::Augmented_My_Trajectory_Point)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'Augmented_My_Trajectory_Point (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::AUGMENTED_MY_TRAJECTORY_POINT")
  (make-package "SMARTCAR_MSGS::AUGMENTED_MY_TRAJECTORY_POINT"))

(in-package "ROS")
;;//! \htmlinclude Augmented_My_Trajectory_Point.msg.html


(defclass smartcar_msgs::Augmented_My_Trajectory_Point
  :super ros::object
  :slots (_trajectory_point _vehicle_info _goal_id _preview_id _lateral_distance_error _max_lateral_distance_error _average_lateral_distance_error _velocity_error _max_velocity_error _average_velocity_error _heading_error _max_heading_error _average_heading_error _computational_time _average_computational_time _max_computational_time _slope ))

(defmethod smartcar_msgs::Augmented_My_Trajectory_Point
  (:init
   (&key
    ((:trajectory_point __trajectory_point) (instance smartcar_msgs::My_Trajectory_Point :init))
    ((:vehicle_info __vehicle_info) (instance smartcar_msgs::VehicleInfo :init))
    ((:goal_id __goal_id) 0.0)
    ((:preview_id __preview_id) 0.0)
    ((:lateral_distance_error __lateral_distance_error) 0.0)
    ((:max_lateral_distance_error __max_lateral_distance_error) 0.0)
    ((:average_lateral_distance_error __average_lateral_distance_error) 0.0)
    ((:velocity_error __velocity_error) 0.0)
    ((:max_velocity_error __max_velocity_error) 0.0)
    ((:average_velocity_error __average_velocity_error) 0.0)
    ((:heading_error __heading_error) 0.0)
    ((:max_heading_error __max_heading_error) 0.0)
    ((:average_heading_error __average_heading_error) 0.0)
    ((:computational_time __computational_time) 0.0)
    ((:average_computational_time __average_computational_time) 0.0)
    ((:max_computational_time __max_computational_time) 0.0)
    ((:slope __slope) 0.0)
    )
   (send-super :init)
   (setq _trajectory_point __trajectory_point)
   (setq _vehicle_info __vehicle_info)
   (setq _goal_id (float __goal_id))
   (setq _preview_id (float __preview_id))
   (setq _lateral_distance_error (float __lateral_distance_error))
   (setq _max_lateral_distance_error (float __max_lateral_distance_error))
   (setq _average_lateral_distance_error (float __average_lateral_distance_error))
   (setq _velocity_error (float __velocity_error))
   (setq _max_velocity_error (float __max_velocity_error))
   (setq _average_velocity_error (float __average_velocity_error))
   (setq _heading_error (float __heading_error))
   (setq _max_heading_error (float __max_heading_error))
   (setq _average_heading_error (float __average_heading_error))
   (setq _computational_time (float __computational_time))
   (setq _average_computational_time (float __average_computational_time))
   (setq _max_computational_time (float __max_computational_time))
   (setq _slope (float __slope))
   self)
  (:trajectory_point
   (&rest __trajectory_point)
   (if (keywordp (car __trajectory_point))
       (send* _trajectory_point __trajectory_point)
     (progn
       (if __trajectory_point (setq _trajectory_point (car __trajectory_point)))
       _trajectory_point)))
  (:vehicle_info
   (&rest __vehicle_info)
   (if (keywordp (car __vehicle_info))
       (send* _vehicle_info __vehicle_info)
     (progn
       (if __vehicle_info (setq _vehicle_info (car __vehicle_info)))
       _vehicle_info)))
  (:goal_id
   (&optional __goal_id)
   (if __goal_id (setq _goal_id __goal_id)) _goal_id)
  (:preview_id
   (&optional __preview_id)
   (if __preview_id (setq _preview_id __preview_id)) _preview_id)
  (:lateral_distance_error
   (&optional __lateral_distance_error)
   (if __lateral_distance_error (setq _lateral_distance_error __lateral_distance_error)) _lateral_distance_error)
  (:max_lateral_distance_error
   (&optional __max_lateral_distance_error)
   (if __max_lateral_distance_error (setq _max_lateral_distance_error __max_lateral_distance_error)) _max_lateral_distance_error)
  (:average_lateral_distance_error
   (&optional __average_lateral_distance_error)
   (if __average_lateral_distance_error (setq _average_lateral_distance_error __average_lateral_distance_error)) _average_lateral_distance_error)
  (:velocity_error
   (&optional __velocity_error)
   (if __velocity_error (setq _velocity_error __velocity_error)) _velocity_error)
  (:max_velocity_error
   (&optional __max_velocity_error)
   (if __max_velocity_error (setq _max_velocity_error __max_velocity_error)) _max_velocity_error)
  (:average_velocity_error
   (&optional __average_velocity_error)
   (if __average_velocity_error (setq _average_velocity_error __average_velocity_error)) _average_velocity_error)
  (:heading_error
   (&optional __heading_error)
   (if __heading_error (setq _heading_error __heading_error)) _heading_error)
  (:max_heading_error
   (&optional __max_heading_error)
   (if __max_heading_error (setq _max_heading_error __max_heading_error)) _max_heading_error)
  (:average_heading_error
   (&optional __average_heading_error)
   (if __average_heading_error (setq _average_heading_error __average_heading_error)) _average_heading_error)
  (:computational_time
   (&optional __computational_time)
   (if __computational_time (setq _computational_time __computational_time)) _computational_time)
  (:average_computational_time
   (&optional __average_computational_time)
   (if __average_computational_time (setq _average_computational_time __average_computational_time)) _average_computational_time)
  (:max_computational_time
   (&optional __max_computational_time)
   (if __max_computational_time (setq _max_computational_time __max_computational_time)) _max_computational_time)
  (:slope
   (&optional __slope)
   (if __slope (setq _slope __slope)) _slope)
  (:serialization-length
   ()
   (+
    ;; smartcar_msgs/My_Trajectory_Point _trajectory_point
    (send _trajectory_point :serialization-length)
    ;; smartcar_msgs/VehicleInfo _vehicle_info
    (send _vehicle_info :serialization-length)
    ;; float64 _goal_id
    8
    ;; float64 _preview_id
    8
    ;; float64 _lateral_distance_error
    8
    ;; float64 _max_lateral_distance_error
    8
    ;; float64 _average_lateral_distance_error
    8
    ;; float64 _velocity_error
    8
    ;; float64 _max_velocity_error
    8
    ;; float64 _average_velocity_error
    8
    ;; float64 _heading_error
    8
    ;; float64 _max_heading_error
    8
    ;; float64 _average_heading_error
    8
    ;; float64 _computational_time
    8
    ;; float64 _average_computational_time
    8
    ;; float64 _max_computational_time
    8
    ;; float64 _slope
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; smartcar_msgs/My_Trajectory_Point _trajectory_point
       (send _trajectory_point :serialize s)
     ;; smartcar_msgs/VehicleInfo _vehicle_info
       (send _vehicle_info :serialize s)
     ;; float64 _goal_id
       (sys::poke _goal_id (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _preview_id
       (sys::poke _preview_id (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _lateral_distance_error
       (sys::poke _lateral_distance_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_lateral_distance_error
       (sys::poke _max_lateral_distance_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _average_lateral_distance_error
       (sys::poke _average_lateral_distance_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity_error
       (sys::poke _velocity_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_velocity_error
       (sys::poke _max_velocity_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _average_velocity_error
       (sys::poke _average_velocity_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _heading_error
       (sys::poke _heading_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_heading_error
       (sys::poke _max_heading_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _average_heading_error
       (sys::poke _average_heading_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _computational_time
       (sys::poke _computational_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _average_computational_time
       (sys::poke _average_computational_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_computational_time
       (sys::poke _max_computational_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _slope
       (sys::poke _slope (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; smartcar_msgs/My_Trajectory_Point _trajectory_point
     (send _trajectory_point :deserialize buf ptr-) (incf ptr- (send _trajectory_point :serialization-length))
   ;; smartcar_msgs/VehicleInfo _vehicle_info
     (send _vehicle_info :deserialize buf ptr-) (incf ptr- (send _vehicle_info :serialization-length))
   ;; float64 _goal_id
     (setq _goal_id (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _preview_id
     (setq _preview_id (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _lateral_distance_error
     (setq _lateral_distance_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_lateral_distance_error
     (setq _max_lateral_distance_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _average_lateral_distance_error
     (setq _average_lateral_distance_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity_error
     (setq _velocity_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_velocity_error
     (setq _max_velocity_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _average_velocity_error
     (setq _average_velocity_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _heading_error
     (setq _heading_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_heading_error
     (setq _max_heading_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _average_heading_error
     (setq _average_heading_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _computational_time
     (setq _computational_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _average_computational_time
     (setq _average_computational_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_computational_time
     (setq _max_computational_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _slope
     (setq _slope (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get smartcar_msgs::Augmented_My_Trajectory_Point :md5sum-) "7730dde01d7004063a0f1a42c12ce23e")
(setf (get smartcar_msgs::Augmented_My_Trajectory_Point :datatype-) "smartcar_msgs/Augmented_My_Trajectory_Point")
(setf (get smartcar_msgs::Augmented_My_Trajectory_Point :definition-)
      "My_Trajectory_Point trajectory_point
VehicleInfo vehicle_info
float64 goal_id
float64 preview_id
float64 lateral_distance_error
float64 max_lateral_distance_error
float64 average_lateral_distance_error
float64 velocity_error
float64 max_velocity_error
float64 average_velocity_error
float64 heading_error
float64 max_heading_error
float64 average_heading_error
float64 computational_time
float64 average_computational_time
float64 max_computational_time
float64 slope


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

================================================================================
MSG: smartcar_msgs/VehicleInfo
Header header
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



(provide :smartcar_msgs/Augmented_My_Trajectory_Point "7730dde01d7004063a0f1a42c12ce23e")


