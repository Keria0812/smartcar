;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::Grid)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'Grid (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::GRID")
  (make-package "SMARTCAR_MSGS::GRID"))

(in-package "ROS")
;;//! \htmlinclude Grid.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::Grid
  :super ros::object
  :slots (_header _timestamp _width _height _width_step _height_step _grid_nums _grid _enabled ))

(defmethod smartcar_msgs::Grid
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:timestamp __timestamp) (instance ros::time :init))
    ((:width __width) 0)
    ((:height __height) 0)
    ((:width_step __width_step) 0.0)
    ((:height_step __height_step) 0.0)
    ((:grid_nums __grid_nums) 0)
    ((:grid __grid) (make-array 0 :initial-element 0 :element-type :integer))
    ((:enabled __enabled) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _timestamp __timestamp)
   (setq _width (round __width))
   (setq _height (round __height))
   (setq _width_step (float __width_step))
   (setq _height_step (float __height_step))
   (setq _grid_nums (round __grid_nums))
   (setq _grid __grid)
   (setq _enabled (round __enabled))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:timestamp
   (&optional __timestamp)
   (if __timestamp (setq _timestamp __timestamp)) _timestamp)
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:width_step
   (&optional __width_step)
   (if __width_step (setq _width_step __width_step)) _width_step)
  (:height_step
   (&optional __height_step)
   (if __height_step (setq _height_step __height_step)) _height_step)
  (:grid_nums
   (&optional __grid_nums)
   (if __grid_nums (setq _grid_nums __grid_nums)) _grid_nums)
  (:grid
   (&optional __grid)
   (if __grid (setq _grid __grid)) _grid)
  (:enabled
   (&optional __enabled)
   (if __enabled (setq _enabled __enabled)) _enabled)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; time _timestamp
    8
    ;; int32 _width
    4
    ;; int32 _height
    4
    ;; float32 _width_step
    4
    ;; float32 _height_step
    4
    ;; int32 _grid_nums
    4
    ;; int8[] _grid
    (* 1    (length _grid)) 4
    ;; int8 _enabled
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; time _timestamp
       (write-long (send _timestamp :sec) s) (write-long (send _timestamp :nsec) s)
     ;; int32 _width
       (write-long _width s)
     ;; int32 _height
       (write-long _height s)
     ;; float32 _width_step
       (sys::poke _width_step (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _height_step
       (sys::poke _height_step (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _grid_nums
       (write-long _grid_nums s)
     ;; int8[] _grid
     (write-long (length _grid) s)
     (dotimes (i (length _grid))
       (write-byte (elt _grid i) s)
       )
     ;; int8 _enabled
       (write-byte _enabled s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; time _timestamp
     (send _timestamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _timestamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _width
     (setq _width (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _height
     (setq _height (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _width_step
     (setq _width_step (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _height_step
     (setq _height_step (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _grid_nums
     (setq _grid_nums (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int8[] _grid
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _grid (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _grid i) (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> (elt _grid i) 127) (setf (elt _grid i) (- (elt _grid i) 256)))
     ))
   ;; int8 _enabled
     (setq _enabled (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _enabled 127) (setq _enabled (- _enabled 256)))
   ;;
   self)
  )

(setf (get smartcar_msgs::Grid :md5sum-) "bbc2797365011f70b841464ee55d9225")
(setf (get smartcar_msgs::Grid :datatype-) "smartcar_msgs/Grid")
(setf (get smartcar_msgs::Grid :definition-)
      "Header 	   header
time       timestamp
int32      width
int32      height
float32    width_step
float32    height_step
int32      grid_nums
int8[]     grid
int8       enabled

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



(provide :smartcar_msgs/Grid "bbc2797365011f70b841464ee55d9225")


