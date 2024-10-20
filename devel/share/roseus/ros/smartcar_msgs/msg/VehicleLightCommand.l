;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::VehicleLightCommand)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'VehicleLightCommand (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::VEHICLELIGHTCOMMAND")
  (make-package "SMARTCAR_MSGS::VEHICLELIGHTCOMMAND"))

(in-package "ROS")
;;//! \htmlinclude VehicleLightCommand.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::VehicleLightCommand
  :super ros::object
  :slots (_header _brakelight_cmd _iecu_lock_cmd _turn_light_cmd _car_light_cmd ))

(defmethod smartcar_msgs::VehicleLightCommand
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:brakelight_cmd __brakelight_cmd) 0)
    ((:iecu_lock_cmd __iecu_lock_cmd) 0)
    ((:turn_light_cmd __turn_light_cmd) 0)
    ((:car_light_cmd __car_light_cmd) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _brakelight_cmd (round __brakelight_cmd))
   (setq _iecu_lock_cmd (round __iecu_lock_cmd))
   (setq _turn_light_cmd (round __turn_light_cmd))
   (setq _car_light_cmd (round __car_light_cmd))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:brakelight_cmd
   (&optional __brakelight_cmd)
   (if __brakelight_cmd (setq _brakelight_cmd __brakelight_cmd)) _brakelight_cmd)
  (:iecu_lock_cmd
   (&optional __iecu_lock_cmd)
   (if __iecu_lock_cmd (setq _iecu_lock_cmd __iecu_lock_cmd)) _iecu_lock_cmd)
  (:turn_light_cmd
   (&optional __turn_light_cmd)
   (if __turn_light_cmd (setq _turn_light_cmd __turn_light_cmd)) _turn_light_cmd)
  (:car_light_cmd
   (&optional __car_light_cmd)
   (if __car_light_cmd (setq _car_light_cmd __car_light_cmd)) _car_light_cmd)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _brakelight_cmd
    4
    ;; int32 _iecu_lock_cmd
    4
    ;; int32 _turn_light_cmd
    4
    ;; int32 _car_light_cmd
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _brakelight_cmd
       (write-long _brakelight_cmd s)
     ;; int32 _iecu_lock_cmd
       (write-long _iecu_lock_cmd s)
     ;; int32 _turn_light_cmd
       (write-long _turn_light_cmd s)
     ;; int32 _car_light_cmd
       (write-long _car_light_cmd s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _brakelight_cmd
     (setq _brakelight_cmd (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _iecu_lock_cmd
     (setq _iecu_lock_cmd (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _turn_light_cmd
     (setq _turn_light_cmd (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _car_light_cmd
     (setq _car_light_cmd (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smartcar_msgs::VehicleLightCommand :md5sum-) "8e2364f8ec89eb4c9476632c281aea24")
(setf (get smartcar_msgs::VehicleLightCommand :datatype-) "smartcar_msgs/VehicleLightCommand")
(setf (get smartcar_msgs::VehicleLightCommand :definition-)
      "Header header

#brakelight 
int32 brakelight_cmd

#iecu_lock,1 unlock
int32 iecu_lock_cmd

#0 mid, 1 turn left, 2 turn right
int32 turn_light_cmd 

#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam
int32 car_light_cmd

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

")



(provide :smartcar_msgs/VehicleLightCommand "8e2364f8ec89eb4c9476632c281aea24")


