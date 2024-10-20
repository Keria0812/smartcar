;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::ACCTarget)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'ACCTarget (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::ACCTARGET")
  (make-package "SMARTCAR_MSGS::ACCTARGET"))

(in-package "ROS")
;;//! \htmlinclude ACCTarget.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::ACCTarget
  :super ros::object
  :slots (_header _object_id _relative_dis _velocity ))

(defmethod smartcar_msgs::ACCTarget
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:object_id __object_id) "")
    ((:relative_dis __relative_dis) 0.0)
    ((:velocity __velocity) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _object_id (string __object_id))
   (setq _relative_dis (float __relative_dis))
   (setq _velocity (float __velocity))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:object_id
   (&optional __object_id)
   (if __object_id (setq _object_id __object_id)) _object_id)
  (:relative_dis
   (&optional __relative_dis)
   (if __relative_dis (setq _relative_dis __relative_dis)) _relative_dis)
  (:velocity
   (&optional __velocity)
   (if __velocity (setq _velocity __velocity)) _velocity)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _object_id
    4 (length _object_id)
    ;; float64 _relative_dis
    8
    ;; float64 _velocity
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _object_id
       (write-long (length _object_id) s) (princ _object_id s)
     ;; float64 _relative_dis
       (sys::poke _relative_dis (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity
       (sys::poke _velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _object_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _object_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _relative_dis
     (setq _relative_dis (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity
     (setq _velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get smartcar_msgs::ACCTarget :md5sum-) "8dc034c3e1b7e7f2a509e71e6d2e2ec0")
(setf (get smartcar_msgs::ACCTarget :datatype-) "smartcar_msgs/ACCTarget")
(setf (get smartcar_msgs::ACCTarget :definition-)
      "Header header
string  object_id  
float64 relative_dis
float64 velocity # m/s
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



(provide :smartcar_msgs/ACCTarget "8dc034c3e1b7e7f2a509e71e6d2e2ec0")


