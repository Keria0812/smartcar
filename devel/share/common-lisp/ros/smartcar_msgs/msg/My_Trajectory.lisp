; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude My_Trajectory.msg.html

(cl:defclass <My_Trajectory> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (lane_id
    :reader lane_id
    :initarg :lane_id
    :type cl:integer
    :initform 0)
   (ESTOP
    :reader ESTOP
    :initarg :ESTOP
    :type cl:boolean
    :initform cl:nil)
   (trajectory_points
    :reader trajectory_points
    :initarg :trajectory_points
    :type (cl:vector smartcar_msgs-msg:My_Trajectory_Point)
   :initform (cl:make-array 0 :element-type 'smartcar_msgs-msg:My_Trajectory_Point :initial-element (cl:make-instance 'smartcar_msgs-msg:My_Trajectory_Point)))
   (num
    :reader num
    :initarg :num
    :type cl:integer
    :initform 0))
)

(cl:defclass My_Trajectory (<My_Trajectory>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <My_Trajectory>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'My_Trajectory)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<My_Trajectory> is deprecated: use smartcar_msgs-msg:My_Trajectory instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <My_Trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:header-val is deprecated.  Use smartcar_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'lane_id-val :lambda-list '(m))
(cl:defmethod lane_id-val ((m <My_Trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:lane_id-val is deprecated.  Use smartcar_msgs-msg:lane_id instead.")
  (lane_id m))

(cl:ensure-generic-function 'ESTOP-val :lambda-list '(m))
(cl:defmethod ESTOP-val ((m <My_Trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:ESTOP-val is deprecated.  Use smartcar_msgs-msg:ESTOP instead.")
  (ESTOP m))

(cl:ensure-generic-function 'trajectory_points-val :lambda-list '(m))
(cl:defmethod trajectory_points-val ((m <My_Trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:trajectory_points-val is deprecated.  Use smartcar_msgs-msg:trajectory_points instead.")
  (trajectory_points m))

(cl:ensure-generic-function 'num-val :lambda-list '(m))
(cl:defmethod num-val ((m <My_Trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:num-val is deprecated.  Use smartcar_msgs-msg:num instead.")
  (num m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <My_Trajectory>) ostream)
  "Serializes a message object of type '<My_Trajectory>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'lane_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ESTOP) 1 0)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'trajectory_points))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'trajectory_points))
  (cl:let* ((signed (cl:slot-value msg 'num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <My_Trajectory>) istream)
  "Deserializes a message object of type '<My_Trajectory>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'lane_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:slot-value msg 'ESTOP) (cl:not (cl:zerop (cl:read-byte istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'trajectory_points) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'trajectory_points)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'smartcar_msgs-msg:My_Trajectory_Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<My_Trajectory>)))
  "Returns string type for a message object of type '<My_Trajectory>"
  "smartcar_msgs/My_Trajectory")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'My_Trajectory)))
  "Returns string type for a message object of type 'My_Trajectory"
  "smartcar_msgs/My_Trajectory")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<My_Trajectory>)))
  "Returns md5sum for a message object of type '<My_Trajectory>"
  "71feceee353912c5f03c9c52a30dd4cf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'My_Trajectory)))
  "Returns md5sum for a message object of type 'My_Trajectory"
  "71feceee353912c5f03c9c52a30dd4cf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<My_Trajectory>)))
  "Returns full string definition for message of type '<My_Trajectory>"
  (cl:format cl:nil "Header header~%int32 lane_id~%bool ESTOP~%My_Trajectory_Point[] trajectory_points~%int32 num~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory_Point~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%float64 l~%float64 dkappa~%float64 ddkappa~%float64 v~%float64 a~%float64 relative_time~%float64 gear~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'My_Trajectory)))
  "Returns full string definition for message of type 'My_Trajectory"
  (cl:format cl:nil "Header header~%int32 lane_id~%bool ESTOP~%My_Trajectory_Point[] trajectory_points~%int32 num~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory_Point~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%float64 l~%float64 dkappa~%float64 ddkappa~%float64 v~%float64 a~%float64 relative_time~%float64 gear~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <My_Trajectory>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'trajectory_points) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <My_Trajectory>))
  "Converts a ROS message object to a list"
  (cl:list 'My_Trajectory
    (cl:cons ':header (header msg))
    (cl:cons ':lane_id (lane_id msg))
    (cl:cons ':ESTOP (ESTOP msg))
    (cl:cons ':trajectory_points (trajectory_points msg))
    (cl:cons ':num (num msg))
))
