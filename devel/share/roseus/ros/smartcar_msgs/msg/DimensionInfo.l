;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::DimensionInfo)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'DimensionInfo (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::DIMENSIONINFO")
  (make-package "SMARTCAR_MSGS::DIMENSIONINFO"))

(in-package "ROS")
;;//! \htmlinclude DimensionInfo.msg.html


(defclass smartcar_msgs::DimensionInfo
  :super ros::object
  :slots (_wheel_base _front_wheel_base _rear_wheel_base _track _mass _front_cornering_stiffness _rear_cornering_stiffness _max_friction_coefficient _Iz ))

(defmethod smartcar_msgs::DimensionInfo
  (:init
   (&key
    ((:wheel_base __wheel_base) 0.0)
    ((:front_wheel_base __front_wheel_base) 0.0)
    ((:rear_wheel_base __rear_wheel_base) 0.0)
    ((:track __track) 0.0)
    ((:mass __mass) 0.0)
    ((:front_cornering_stiffness __front_cornering_stiffness) 0.0)
    ((:rear_cornering_stiffness __rear_cornering_stiffness) 0.0)
    ((:max_friction_coefficient __max_friction_coefficient) 0.0)
    ((:Iz __Iz) 0.0)
    )
   (send-super :init)
   (setq _wheel_base (float __wheel_base))
   (setq _front_wheel_base (float __front_wheel_base))
   (setq _rear_wheel_base (float __rear_wheel_base))
   (setq _track (float __track))
   (setq _mass (float __mass))
   (setq _front_cornering_stiffness (float __front_cornering_stiffness))
   (setq _rear_cornering_stiffness (float __rear_cornering_stiffness))
   (setq _max_friction_coefficient (float __max_friction_coefficient))
   (setq _Iz (float __Iz))
   self)
  (:wheel_base
   (&optional __wheel_base)
   (if __wheel_base (setq _wheel_base __wheel_base)) _wheel_base)
  (:front_wheel_base
   (&optional __front_wheel_base)
   (if __front_wheel_base (setq _front_wheel_base __front_wheel_base)) _front_wheel_base)
  (:rear_wheel_base
   (&optional __rear_wheel_base)
   (if __rear_wheel_base (setq _rear_wheel_base __rear_wheel_base)) _rear_wheel_base)
  (:track
   (&optional __track)
   (if __track (setq _track __track)) _track)
  (:mass
   (&optional __mass)
   (if __mass (setq _mass __mass)) _mass)
  (:front_cornering_stiffness
   (&optional __front_cornering_stiffness)
   (if __front_cornering_stiffness (setq _front_cornering_stiffness __front_cornering_stiffness)) _front_cornering_stiffness)
  (:rear_cornering_stiffness
   (&optional __rear_cornering_stiffness)
   (if __rear_cornering_stiffness (setq _rear_cornering_stiffness __rear_cornering_stiffness)) _rear_cornering_stiffness)
  (:max_friction_coefficient
   (&optional __max_friction_coefficient)
   (if __max_friction_coefficient (setq _max_friction_coefficient __max_friction_coefficient)) _max_friction_coefficient)
  (:Iz
   (&optional __Iz)
   (if __Iz (setq _Iz __Iz)) _Iz)
  (:serialization-length
   ()
   (+
    ;; float64 _wheel_base
    8
    ;; float64 _front_wheel_base
    8
    ;; float64 _rear_wheel_base
    8
    ;; float64 _track
    8
    ;; float64 _mass
    8
    ;; float64 _front_cornering_stiffness
    8
    ;; float64 _rear_cornering_stiffness
    8
    ;; float64 _max_friction_coefficient
    8
    ;; float64 _Iz
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _wheel_base
       (sys::poke _wheel_base (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _front_wheel_base
       (sys::poke _front_wheel_base (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rear_wheel_base
       (sys::poke _rear_wheel_base (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _track
       (sys::poke _track (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _mass
       (sys::poke _mass (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _front_cornering_stiffness
       (sys::poke _front_cornering_stiffness (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rear_cornering_stiffness
       (sys::poke _rear_cornering_stiffness (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_friction_coefficient
       (sys::poke _max_friction_coefficient (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _Iz
       (sys::poke _Iz (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _wheel_base
     (setq _wheel_base (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _front_wheel_base
     (setq _front_wheel_base (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rear_wheel_base
     (setq _rear_wheel_base (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _track
     (setq _track (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _mass
     (setq _mass (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _front_cornering_stiffness
     (setq _front_cornering_stiffness (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rear_cornering_stiffness
     (setq _rear_cornering_stiffness (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_friction_coefficient
     (setq _max_friction_coefficient (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _Iz
     (setq _Iz (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get smartcar_msgs::DimensionInfo :md5sum-) "83b23d28199a7ca222af4ff1d8a32e6b")
(setf (get smartcar_msgs::DimensionInfo :datatype-) "smartcar_msgs/DimensionInfo")
(setf (get smartcar_msgs::DimensionInfo :definition-)
      "float64 wheel_base
float64 front_wheel_base
float64 rear_wheel_base
float64 track
float64 mass
float64 front_cornering_stiffness
float64 rear_cornering_stiffness
float64 max_friction_coefficient
float64 Iz

")



(provide :smartcar_msgs/DimensionInfo "83b23d28199a7ca222af4ff1d8a32e6b")


