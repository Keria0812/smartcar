;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::VehicleLightState)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'VehicleLightState (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::VEHICLELIGHTSTATE")
  (make-package "SMARTCAR_MSGS::VEHICLELIGHTSTATE"))

(in-package "ROS")
;;//! \htmlinclude VehicleLightState.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::VehicleLightState
  :super ros::object
  :slots (_header _turn_light _car_light ))

(defmethod smartcar_msgs::VehicleLightState
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:turn_light __turn_light) 0)
    ((:car_light __car_light) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _turn_light (round __turn_light))
   (setq _car_light (round __car_light))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:turn_light
   (&optional __turn_light)
   (if __turn_light (setq _turn_light __turn_light)) _turn_light)
  (:car_light
   (&optional __car_light)
   (if __car_light (setq _car_light __car_light)) _car_light)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _turn_light
    4
    ;; int32 _car_light
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _turn_light
       (write-long _turn_light s)
     ;; int32 _car_light
       (write-long _car_light s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _turn_light
     (setq _turn_light (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _car_light
     (setq _car_light (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smartcar_msgs::VehicleLightState :md5sum-) "8e22a6beadc4b37e8e1c81c5e770f4eb")
(setf (get smartcar_msgs::VehicleLightState :datatype-) "smartcar_msgs/VehicleLightState")
(setf (get smartcar_msgs::VehicleLightState :definition-)
      "Header header
#0 mid, 1 turn left, 2 turn right
int32 turn_light 

#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam
int32 car_light

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



(provide :smartcar_msgs/VehicleLightState "8e22a6beadc4b37e8e1c81c5e770f4eb")


