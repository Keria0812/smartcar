;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::LongitudinalData)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'LongitudinalData (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::LONGITUDINALDATA")
  (make-package "SMARTCAR_MSGS::LONGITUDINALDATA"))

(in-package "ROS")
;;//! \htmlinclude LongitudinalData.msg.html


(defclass smartcar_msgs::LongitudinalData
  :super ros::object
  :slots (_vel_from_localization _vel_from_wheels _acceleration _traveled_distance _fl_wheel_angular_velocity _fr_wheel_angular_velocity _bl_wheel_angular_velocity _br_wheel_angular_velocity _gas_percent _fl_gas_torque _fr_gas_torque _bl_gas_torque _br_gas_torque _fl_brake_Torque _fr_brake_torque _bl_brake_torque _br_brake_torque ))

(defmethod smartcar_msgs::LongitudinalData
  (:init
   (&key
    ((:vel_from_localization __vel_from_localization) 0.0)
    ((:vel_from_wheels __vel_from_wheels) 0.0)
    ((:acceleration __acceleration) 0.0)
    ((:traveled_distance __traveled_distance) 0.0)
    ((:fl_wheel_angular_velocity __fl_wheel_angular_velocity) 0.0)
    ((:fr_wheel_angular_velocity __fr_wheel_angular_velocity) 0.0)
    ((:bl_wheel_angular_velocity __bl_wheel_angular_velocity) 0.0)
    ((:br_wheel_angular_velocity __br_wheel_angular_velocity) 0.0)
    ((:gas_percent __gas_percent) 0.0)
    ((:fl_gas_torque __fl_gas_torque) 0.0)
    ((:fr_gas_torque __fr_gas_torque) 0.0)
    ((:bl_gas_torque __bl_gas_torque) 0.0)
    ((:br_gas_torque __br_gas_torque) 0.0)
    ((:fl_brake_Torque __fl_brake_Torque) 0.0)
    ((:fr_brake_torque __fr_brake_torque) 0.0)
    ((:bl_brake_torque __bl_brake_torque) 0.0)
    ((:br_brake_torque __br_brake_torque) 0.0)
    )
   (send-super :init)
   (setq _vel_from_localization (float __vel_from_localization))
   (setq _vel_from_wheels (float __vel_from_wheels))
   (setq _acceleration (float __acceleration))
   (setq _traveled_distance (float __traveled_distance))
   (setq _fl_wheel_angular_velocity (float __fl_wheel_angular_velocity))
   (setq _fr_wheel_angular_velocity (float __fr_wheel_angular_velocity))
   (setq _bl_wheel_angular_velocity (float __bl_wheel_angular_velocity))
   (setq _br_wheel_angular_velocity (float __br_wheel_angular_velocity))
   (setq _gas_percent (float __gas_percent))
   (setq _fl_gas_torque (float __fl_gas_torque))
   (setq _fr_gas_torque (float __fr_gas_torque))
   (setq _bl_gas_torque (float __bl_gas_torque))
   (setq _br_gas_torque (float __br_gas_torque))
   (setq _fl_brake_Torque (float __fl_brake_Torque))
   (setq _fr_brake_torque (float __fr_brake_torque))
   (setq _bl_brake_torque (float __bl_brake_torque))
   (setq _br_brake_torque (float __br_brake_torque))
   self)
  (:vel_from_localization
   (&optional __vel_from_localization)
   (if __vel_from_localization (setq _vel_from_localization __vel_from_localization)) _vel_from_localization)
  (:vel_from_wheels
   (&optional __vel_from_wheels)
   (if __vel_from_wheels (setq _vel_from_wheels __vel_from_wheels)) _vel_from_wheels)
  (:acceleration
   (&optional __acceleration)
   (if __acceleration (setq _acceleration __acceleration)) _acceleration)
  (:traveled_distance
   (&optional __traveled_distance)
   (if __traveled_distance (setq _traveled_distance __traveled_distance)) _traveled_distance)
  (:fl_wheel_angular_velocity
   (&optional __fl_wheel_angular_velocity)
   (if __fl_wheel_angular_velocity (setq _fl_wheel_angular_velocity __fl_wheel_angular_velocity)) _fl_wheel_angular_velocity)
  (:fr_wheel_angular_velocity
   (&optional __fr_wheel_angular_velocity)
   (if __fr_wheel_angular_velocity (setq _fr_wheel_angular_velocity __fr_wheel_angular_velocity)) _fr_wheel_angular_velocity)
  (:bl_wheel_angular_velocity
   (&optional __bl_wheel_angular_velocity)
   (if __bl_wheel_angular_velocity (setq _bl_wheel_angular_velocity __bl_wheel_angular_velocity)) _bl_wheel_angular_velocity)
  (:br_wheel_angular_velocity
   (&optional __br_wheel_angular_velocity)
   (if __br_wheel_angular_velocity (setq _br_wheel_angular_velocity __br_wheel_angular_velocity)) _br_wheel_angular_velocity)
  (:gas_percent
   (&optional __gas_percent)
   (if __gas_percent (setq _gas_percent __gas_percent)) _gas_percent)
  (:fl_gas_torque
   (&optional __fl_gas_torque)
   (if __fl_gas_torque (setq _fl_gas_torque __fl_gas_torque)) _fl_gas_torque)
  (:fr_gas_torque
   (&optional __fr_gas_torque)
   (if __fr_gas_torque (setq _fr_gas_torque __fr_gas_torque)) _fr_gas_torque)
  (:bl_gas_torque
   (&optional __bl_gas_torque)
   (if __bl_gas_torque (setq _bl_gas_torque __bl_gas_torque)) _bl_gas_torque)
  (:br_gas_torque
   (&optional __br_gas_torque)
   (if __br_gas_torque (setq _br_gas_torque __br_gas_torque)) _br_gas_torque)
  (:fl_brake_Torque
   (&optional __fl_brake_Torque)
   (if __fl_brake_Torque (setq _fl_brake_Torque __fl_brake_Torque)) _fl_brake_Torque)
  (:fr_brake_torque
   (&optional __fr_brake_torque)
   (if __fr_brake_torque (setq _fr_brake_torque __fr_brake_torque)) _fr_brake_torque)
  (:bl_brake_torque
   (&optional __bl_brake_torque)
   (if __bl_brake_torque (setq _bl_brake_torque __bl_brake_torque)) _bl_brake_torque)
  (:br_brake_torque
   (&optional __br_brake_torque)
   (if __br_brake_torque (setq _br_brake_torque __br_brake_torque)) _br_brake_torque)
  (:serialization-length
   ()
   (+
    ;; float64 _vel_from_localization
    8
    ;; float64 _vel_from_wheels
    8
    ;; float64 _acceleration
    8
    ;; float64 _traveled_distance
    8
    ;; float64 _fl_wheel_angular_velocity
    8
    ;; float64 _fr_wheel_angular_velocity
    8
    ;; float64 _bl_wheel_angular_velocity
    8
    ;; float64 _br_wheel_angular_velocity
    8
    ;; float64 _gas_percent
    8
    ;; float64 _fl_gas_torque
    8
    ;; float64 _fr_gas_torque
    8
    ;; float64 _bl_gas_torque
    8
    ;; float64 _br_gas_torque
    8
    ;; float64 _fl_brake_Torque
    8
    ;; float64 _fr_brake_torque
    8
    ;; float64 _bl_brake_torque
    8
    ;; float64 _br_brake_torque
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _vel_from_localization
       (sys::poke _vel_from_localization (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _vel_from_wheels
       (sys::poke _vel_from_wheels (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _acceleration
       (sys::poke _acceleration (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _traveled_distance
       (sys::poke _traveled_distance (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fl_wheel_angular_velocity
       (sys::poke _fl_wheel_angular_velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fr_wheel_angular_velocity
       (sys::poke _fr_wheel_angular_velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _bl_wheel_angular_velocity
       (sys::poke _bl_wheel_angular_velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _br_wheel_angular_velocity
       (sys::poke _br_wheel_angular_velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _gas_percent
       (sys::poke _gas_percent (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fl_gas_torque
       (sys::poke _fl_gas_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fr_gas_torque
       (sys::poke _fr_gas_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _bl_gas_torque
       (sys::poke _bl_gas_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _br_gas_torque
       (sys::poke _br_gas_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fl_brake_Torque
       (sys::poke _fl_brake_Torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fr_brake_torque
       (sys::poke _fr_brake_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _bl_brake_torque
       (sys::poke _bl_brake_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _br_brake_torque
       (sys::poke _br_brake_torque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _vel_from_localization
     (setq _vel_from_localization (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _vel_from_wheels
     (setq _vel_from_wheels (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _acceleration
     (setq _acceleration (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _traveled_distance
     (setq _traveled_distance (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fl_wheel_angular_velocity
     (setq _fl_wheel_angular_velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fr_wheel_angular_velocity
     (setq _fr_wheel_angular_velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _bl_wheel_angular_velocity
     (setq _bl_wheel_angular_velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _br_wheel_angular_velocity
     (setq _br_wheel_angular_velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _gas_percent
     (setq _gas_percent (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fl_gas_torque
     (setq _fl_gas_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fr_gas_torque
     (setq _fr_gas_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _bl_gas_torque
     (setq _bl_gas_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _br_gas_torque
     (setq _br_gas_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fl_brake_Torque
     (setq _fl_brake_Torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fr_brake_torque
     (setq _fr_brake_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _bl_brake_torque
     (setq _bl_brake_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _br_brake_torque
     (setq _br_brake_torque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get smartcar_msgs::LongitudinalData :md5sum-) "5e1bfb472e4917d66e73052e666a6e34")
(setf (get smartcar_msgs::LongitudinalData :datatype-) "smartcar_msgs/LongitudinalData")
(setf (get smartcar_msgs::LongitudinalData :definition-)
      "float64 vel_from_localization
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

")



(provide :smartcar_msgs/LongitudinalData "5e1bfb472e4917d66e73052e666a6e34")


