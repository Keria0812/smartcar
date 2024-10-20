;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::My_Trajectory_Point)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'My_Trajectory_Point (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::MY_TRAJECTORY_POINT")
  (make-package "SMARTCAR_MSGS::MY_TRAJECTORY_POINT"))

(in-package "ROS")
;;//! \htmlinclude My_Trajectory_Point.msg.html


(defclass smartcar_msgs::My_Trajectory_Point
  :super ros::object
  :slots (_x _y _z _theta _kappa _s _l _dkappa _ddkappa _v _a _relative_time _gear ))

(defmethod smartcar_msgs::My_Trajectory_Point
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:theta __theta) 0.0)
    ((:kappa __kappa) 0.0)
    ((:s __s) 0.0)
    ((:l __l) 0.0)
    ((:dkappa __dkappa) 0.0)
    ((:ddkappa __ddkappa) 0.0)
    ((:v __v) 0.0)
    ((:a __a) 0.0)
    ((:relative_time __relative_time) 0.0)
    ((:gear __gear) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _theta (float __theta))
   (setq _kappa (float __kappa))
   (setq _s (float __s))
   (setq _l (float __l))
   (setq _dkappa (float __dkappa))
   (setq _ddkappa (float __ddkappa))
   (setq _v (float __v))
   (setq _a (float __a))
   (setq _relative_time (float __relative_time))
   (setq _gear (float __gear))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:kappa
   (&optional __kappa)
   (if __kappa (setq _kappa __kappa)) _kappa)
  (:s
   (&optional __s)
   (if __s (setq _s __s)) _s)
  (:l
   (&optional __l)
   (if __l (setq _l __l)) _l)
  (:dkappa
   (&optional __dkappa)
   (if __dkappa (setq _dkappa __dkappa)) _dkappa)
  (:ddkappa
   (&optional __ddkappa)
   (if __ddkappa (setq _ddkappa __ddkappa)) _ddkappa)
  (:v
   (&optional __v)
   (if __v (setq _v __v)) _v)
  (:a
   (&optional __a)
   (if __a (setq _a __a)) _a)
  (:relative_time
   (&optional __relative_time)
   (if __relative_time (setq _relative_time __relative_time)) _relative_time)
  (:gear
   (&optional __gear)
   (if __gear (setq _gear __gear)) _gear)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float64 _theta
    8
    ;; float64 _kappa
    8
    ;; float64 _s
    8
    ;; float64 _l
    8
    ;; float64 _dkappa
    8
    ;; float64 _ddkappa
    8
    ;; float64 _v
    8
    ;; float64 _a
    8
    ;; float64 _relative_time
    8
    ;; float64 _gear
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _kappa
       (sys::poke _kappa (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _s
       (sys::poke _s (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _l
       (sys::poke _l (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dkappa
       (sys::poke _dkappa (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ddkappa
       (sys::poke _ddkappa (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _v
       (sys::poke _v (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _a
       (sys::poke _a (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _relative_time
       (sys::poke _relative_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _gear
       (sys::poke _gear (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _theta
     (setq _theta (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _kappa
     (setq _kappa (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _s
     (setq _s (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _l
     (setq _l (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dkappa
     (setq _dkappa (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ddkappa
     (setq _ddkappa (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _v
     (setq _v (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _a
     (setq _a (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _relative_time
     (setq _relative_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _gear
     (setq _gear (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get smartcar_msgs::My_Trajectory_Point :md5sum-) "9b99836b373278ef538727f7eb83a3fe")
(setf (get smartcar_msgs::My_Trajectory_Point :datatype-) "smartcar_msgs/My_Trajectory_Point")
(setf (get smartcar_msgs::My_Trajectory_Point :definition-)
      "float64 x
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



(provide :smartcar_msgs/My_Trajectory_Point "9b99836b373278ef538727f7eb83a3fe")


