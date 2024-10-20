;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::LateralData)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'LateralData (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::LATERALDATA")
  (make-package "SMARTCAR_MSGS::LATERALDATA"))

(in-package "ROS")
;;//! \htmlinclude LateralData.msg.html


(defclass smartcar_msgs::LateralData
  :super ros::object
  :slots (_heading_angle _steering_wheel_angle_actual _steering_wheel_expected _steering_wheel_error _steering_wheel_cmd _fl_steering_angle_actual _fr_steering_angle_actual _single_track_steering_angle _fl_steering_angle_expected _fr_steering_angle_expected _fl_steering_error _fr_steering_error _fl_steering_cmd _fr_steering_cmd ))

(defmethod smartcar_msgs::LateralData
  (:init
   (&key
    ((:heading_angle __heading_angle) 0.0)
    ((:steering_wheel_angle_actual __steering_wheel_angle_actual) 0.0)
    ((:steering_wheel_expected __steering_wheel_expected) 0.0)
    ((:steering_wheel_error __steering_wheel_error) 0.0)
    ((:steering_wheel_cmd __steering_wheel_cmd) 0.0)
    ((:fl_steering_angle_actual __fl_steering_angle_actual) 0.0)
    ((:fr_steering_angle_actual __fr_steering_angle_actual) 0.0)
    ((:single_track_steering_angle __single_track_steering_angle) 0.0)
    ((:fl_steering_angle_expected __fl_steering_angle_expected) 0.0)
    ((:fr_steering_angle_expected __fr_steering_angle_expected) 0.0)
    ((:fl_steering_error __fl_steering_error) 0.0)
    ((:fr_steering_error __fr_steering_error) 0.0)
    ((:fl_steering_cmd __fl_steering_cmd) 0.0)
    ((:fr_steering_cmd __fr_steering_cmd) 0.0)
    )
   (send-super :init)
   (setq _heading_angle (float __heading_angle))
   (setq _steering_wheel_angle_actual (float __steering_wheel_angle_actual))
   (setq _steering_wheel_expected (float __steering_wheel_expected))
   (setq _steering_wheel_error (float __steering_wheel_error))
   (setq _steering_wheel_cmd (float __steering_wheel_cmd))
   (setq _fl_steering_angle_actual (float __fl_steering_angle_actual))
   (setq _fr_steering_angle_actual (float __fr_steering_angle_actual))
   (setq _single_track_steering_angle (float __single_track_steering_angle))
   (setq _fl_steering_angle_expected (float __fl_steering_angle_expected))
   (setq _fr_steering_angle_expected (float __fr_steering_angle_expected))
   (setq _fl_steering_error (float __fl_steering_error))
   (setq _fr_steering_error (float __fr_steering_error))
   (setq _fl_steering_cmd (float __fl_steering_cmd))
   (setq _fr_steering_cmd (float __fr_steering_cmd))
   self)
  (:heading_angle
   (&optional __heading_angle)
   (if __heading_angle (setq _heading_angle __heading_angle)) _heading_angle)
  (:steering_wheel_angle_actual
   (&optional __steering_wheel_angle_actual)
   (if __steering_wheel_angle_actual (setq _steering_wheel_angle_actual __steering_wheel_angle_actual)) _steering_wheel_angle_actual)
  (:steering_wheel_expected
   (&optional __steering_wheel_expected)
   (if __steering_wheel_expected (setq _steering_wheel_expected __steering_wheel_expected)) _steering_wheel_expected)
  (:steering_wheel_error
   (&optional __steering_wheel_error)
   (if __steering_wheel_error (setq _steering_wheel_error __steering_wheel_error)) _steering_wheel_error)
  (:steering_wheel_cmd
   (&optional __steering_wheel_cmd)
   (if __steering_wheel_cmd (setq _steering_wheel_cmd __steering_wheel_cmd)) _steering_wheel_cmd)
  (:fl_steering_angle_actual
   (&optional __fl_steering_angle_actual)
   (if __fl_steering_angle_actual (setq _fl_steering_angle_actual __fl_steering_angle_actual)) _fl_steering_angle_actual)
  (:fr_steering_angle_actual
   (&optional __fr_steering_angle_actual)
   (if __fr_steering_angle_actual (setq _fr_steering_angle_actual __fr_steering_angle_actual)) _fr_steering_angle_actual)
  (:single_track_steering_angle
   (&optional __single_track_steering_angle)
   (if __single_track_steering_angle (setq _single_track_steering_angle __single_track_steering_angle)) _single_track_steering_angle)
  (:fl_steering_angle_expected
   (&optional __fl_steering_angle_expected)
   (if __fl_steering_angle_expected (setq _fl_steering_angle_expected __fl_steering_angle_expected)) _fl_steering_angle_expected)
  (:fr_steering_angle_expected
   (&optional __fr_steering_angle_expected)
   (if __fr_steering_angle_expected (setq _fr_steering_angle_expected __fr_steering_angle_expected)) _fr_steering_angle_expected)
  (:fl_steering_error
   (&optional __fl_steering_error)
   (if __fl_steering_error (setq _fl_steering_error __fl_steering_error)) _fl_steering_error)
  (:fr_steering_error
   (&optional __fr_steering_error)
   (if __fr_steering_error (setq _fr_steering_error __fr_steering_error)) _fr_steering_error)
  (:fl_steering_cmd
   (&optional __fl_steering_cmd)
   (if __fl_steering_cmd (setq _fl_steering_cmd __fl_steering_cmd)) _fl_steering_cmd)
  (:fr_steering_cmd
   (&optional __fr_steering_cmd)
   (if __fr_steering_cmd (setq _fr_steering_cmd __fr_steering_cmd)) _fr_steering_cmd)
  (:serialization-length
   ()
   (+
    ;; float64 _heading_angle
    8
    ;; float64 _steering_wheel_angle_actual
    8
    ;; float64 _steering_wheel_expected
    8
    ;; float64 _steering_wheel_error
    8
    ;; float64 _steering_wheel_cmd
    8
    ;; float64 _fl_steering_angle_actual
    8
    ;; float64 _fr_steering_angle_actual
    8
    ;; float64 _single_track_steering_angle
    8
    ;; float64 _fl_steering_angle_expected
    8
    ;; float64 _fr_steering_angle_expected
    8
    ;; float64 _fl_steering_error
    8
    ;; float64 _fr_steering_error
    8
    ;; float64 _fl_steering_cmd
    8
    ;; float64 _fr_steering_cmd
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _heading_angle
       (sys::poke _heading_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steering_wheel_angle_actual
       (sys::poke _steering_wheel_angle_actual (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steering_wheel_expected
       (sys::poke _steering_wheel_expected (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steering_wheel_error
       (sys::poke _steering_wheel_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steering_wheel_cmd
       (sys::poke _steering_wheel_cmd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fl_steering_angle_actual
       (sys::poke _fl_steering_angle_actual (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fr_steering_angle_actual
       (sys::poke _fr_steering_angle_actual (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _single_track_steering_angle
       (sys::poke _single_track_steering_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fl_steering_angle_expected
       (sys::poke _fl_steering_angle_expected (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fr_steering_angle_expected
       (sys::poke _fr_steering_angle_expected (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fl_steering_error
       (sys::poke _fl_steering_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fr_steering_error
       (sys::poke _fr_steering_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fl_steering_cmd
       (sys::poke _fl_steering_cmd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fr_steering_cmd
       (sys::poke _fr_steering_cmd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _heading_angle
     (setq _heading_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steering_wheel_angle_actual
     (setq _steering_wheel_angle_actual (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steering_wheel_expected
     (setq _steering_wheel_expected (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steering_wheel_error
     (setq _steering_wheel_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steering_wheel_cmd
     (setq _steering_wheel_cmd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fl_steering_angle_actual
     (setq _fl_steering_angle_actual (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fr_steering_angle_actual
     (setq _fr_steering_angle_actual (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _single_track_steering_angle
     (setq _single_track_steering_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fl_steering_angle_expected
     (setq _fl_steering_angle_expected (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fr_steering_angle_expected
     (setq _fr_steering_angle_expected (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fl_steering_error
     (setq _fl_steering_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fr_steering_error
     (setq _fr_steering_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fl_steering_cmd
     (setq _fl_steering_cmd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fr_steering_cmd
     (setq _fr_steering_cmd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get smartcar_msgs::LateralData :md5sum-) "cfef9feeb4812e9c07678250076f59e3")
(setf (get smartcar_msgs::LateralData :datatype-) "smartcar_msgs/LateralData")
(setf (get smartcar_msgs::LateralData :definition-)
      "float64 heading_angle
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



(provide :smartcar_msgs/LateralData "cfef9feeb4812e9c07678250076f59e3")


