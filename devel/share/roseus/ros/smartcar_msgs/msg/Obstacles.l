;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::Obstacles)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'Obstacles (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::OBSTACLES")
  (make-package "SMARTCAR_MSGS::OBSTACLES"))

(in-package "ROS")
;;//! \htmlinclude Obstacles.msg.html


(defclass smartcar_msgs::Obstacles
  :super ros::object
  :slots (_Obstacles ))

(defmethod smartcar_msgs::Obstacles
  (:init
   (&key
    ((:Obstacles __Obstacles) ())
    )
   (send-super :init)
   (setq _Obstacles __Obstacles)
   self)
  (:Obstacles
   (&rest __Obstacles)
   (if (keywordp (car __Obstacles))
       (send* _Obstacles __Obstacles)
     (progn
       (if __Obstacles (setq _Obstacles (car __Obstacles)))
       _Obstacles)))
  (:serialization-length
   ()
   (+
    ;; smartcar_msgs/ObstacleAttr[] _Obstacles
    (apply #'+ (send-all _Obstacles :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; smartcar_msgs/ObstacleAttr[] _Obstacles
     (write-long (length _Obstacles) s)
     (dolist (elem _Obstacles)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; smartcar_msgs/ObstacleAttr[] _Obstacles
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Obstacles (let (r) (dotimes (i n) (push (instance smartcar_msgs::ObstacleAttr :init) r)) r))
     (dolist (elem- _Obstacles)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get smartcar_msgs::Obstacles :md5sum-) "42f94931bc3e97baf969e4dc42dad246")
(setf (get smartcar_msgs::Obstacles :datatype-) "smartcar_msgs/Obstacles")
(setf (get smartcar_msgs::Obstacles :definition-)
      " ObstacleAttr[] Obstacles
================================================================================
MSG: smartcar_msgs/ObstacleAttr
int8 id
float64 x
float64 y
float64 z
float64 length
float64 width
float64 height
float64 heading
float64 speed
")



(provide :smartcar_msgs/Obstacles "42f94931bc3e97baf969e4dc42dad246")


