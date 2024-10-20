;; Auto-generated. Do not edit!


(when (boundp 'object_msgs::TrafficLightState)
  (if (not (find-package "OBJECT_MSGS"))
    (make-package "OBJECT_MSGS"))
  (shadow 'TrafficLightState (find-package "OBJECT_MSGS")))
(unless (find-package "OBJECT_MSGS::TRAFFICLIGHTSTATE")
  (make-package "OBJECT_MSGS::TRAFFICLIGHTSTATE"))

(in-package "ROS")
;;//! \htmlinclude TrafficLightState.msg.html


(defclass object_msgs::TrafficLightState
  :super ros::object
  :slots (_lamp_states _id ))

(defmethod object_msgs::TrafficLightState
  (:init
   (&key
    ((:lamp_states __lamp_states) ())
    ((:id __id) 0)
    )
   (send-super :init)
   (setq _lamp_states __lamp_states)
   (setq _id (round __id))
   self)
  (:lamp_states
   (&rest __lamp_states)
   (if (keywordp (car __lamp_states))
       (send* _lamp_states __lamp_states)
     (progn
       (if __lamp_states (setq _lamp_states (car __lamp_states)))
       _lamp_states)))
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:serialization-length
   ()
   (+
    ;; object_msgs/LampState[] _lamp_states
    (apply #'+ (send-all _lamp_states :serialization-length)) 4
    ;; int32 _id
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; object_msgs/LampState[] _lamp_states
     (write-long (length _lamp_states) s)
     (dolist (elem _lamp_states)
       (send elem :serialize s)
       )
     ;; int32 _id
       (write-long _id s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; object_msgs/LampState[] _lamp_states
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lamp_states (let (r) (dotimes (i n) (push (instance object_msgs::LampState :init) r)) r))
     (dolist (elem- _lamp_states)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get object_msgs::TrafficLightState :md5sum-) "e8e13d98ab9da18d92f4dd32e357fa36")
(setf (get object_msgs::TrafficLightState :datatype-) "object_msgs/TrafficLightState")
(setf (get object_msgs::TrafficLightState :definition-)
      "object_msgs/LampState[] lamp_states
int32 id
================================================================================
MSG: object_msgs/LampState
uint8 UNKNOWN=0
uint8 RED=1
uint8 GREEN=2
uint8 YELLOW=3
uint8 LEFT=4
uint8 RIGHT=5
uint8 UP=6
uint8 DOWN=7
uint32 type
float32 confidence
")



(provide :object_msgs/TrafficLightState "e8e13d98ab9da18d92f4dd32e357fa36")


