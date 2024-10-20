; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude My_TrajectoryArray.msg.html

(cl:defclass <My_TrajectoryArray> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (lanes
    :reader lanes
    :initarg :lanes
    :type (cl:vector smartcar_msgs-msg:My_Trajectory)
   :initform (cl:make-array 0 :element-type 'smartcar_msgs-msg:My_Trajectory :initial-element (cl:make-instance 'smartcar_msgs-msg:My_Trajectory)))
   (num
    :reader num
    :initarg :num
    :type cl:integer
    :initform 0))
)

(cl:defclass My_TrajectoryArray (<My_TrajectoryArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <My_TrajectoryArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'My_TrajectoryArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<My_TrajectoryArray> is deprecated: use smartcar_msgs-msg:My_TrajectoryArray instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <My_TrajectoryArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:header-val is deprecated.  Use smartcar_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'lanes-val :lambda-list '(m))
(cl:defmethod lanes-val ((m <My_TrajectoryArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:lanes-val is deprecated.  Use smartcar_msgs-msg:lanes instead.")
  (lanes m))

(cl:ensure-generic-function 'num-val :lambda-list '(m))
(cl:defmethod num-val ((m <My_TrajectoryArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:num-val is deprecated.  Use smartcar_msgs-msg:num instead.")
  (num m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <My_TrajectoryArray>) ostream)
  "Serializes a message object of type '<My_TrajectoryArray>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'lanes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'lanes))
  (cl:let* ((signed (cl:slot-value msg 'num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <My_TrajectoryArray>) istream)
  "Deserializes a message object of type '<My_TrajectoryArray>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'lanes) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'lanes)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'smartcar_msgs-msg:My_Trajectory))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<My_TrajectoryArray>)))
  "Returns string type for a message object of type '<My_TrajectoryArray>"
  "smartcar_msgs/My_TrajectoryArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'My_TrajectoryArray)))
  "Returns string type for a message object of type 'My_TrajectoryArray"
  "smartcar_msgs/My_TrajectoryArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<My_TrajectoryArray>)))
  "Returns md5sum for a message object of type '<My_TrajectoryArray>"
  "5ccdd33f237885519dadb3b742c24919")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'My_TrajectoryArray)))
  "Returns md5sum for a message object of type 'My_TrajectoryArray"
  "5ccdd33f237885519dadb3b742c24919")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<My_TrajectoryArray>)))
  "Returns full string definition for message of type '<My_TrajectoryArray>"
  (cl:format cl:nil "Header header~%My_Trajectory[] lanes~%int32 num~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory~%Header header~%int32 lane_id~%bool ESTOP~%My_Trajectory_Point[] trajectory_points~%int32 num~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory_Point~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%float64 l~%float64 dkappa~%float64 ddkappa~%float64 v~%float64 a~%float64 relative_time~%float64 gear~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'My_TrajectoryArray)))
  "Returns full string definition for message of type 'My_TrajectoryArray"
  (cl:format cl:nil "Header header~%My_Trajectory[] lanes~%int32 num~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory~%Header header~%int32 lane_id~%bool ESTOP~%My_Trajectory_Point[] trajectory_points~%int32 num~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory_Point~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%float64 l~%float64 dkappa~%float64 ddkappa~%float64 v~%float64 a~%float64 relative_time~%float64 gear~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <My_TrajectoryArray>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'lanes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <My_TrajectoryArray>))
  "Converts a ROS message object to a list"
  (cl:list 'My_TrajectoryArray
    (cl:cons ':header (header msg))
    (cl:cons ':lanes (lanes msg))
    (cl:cons ':num (num msg))
))
