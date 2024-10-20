; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude Obstacles.msg.html

(cl:defclass <Obstacles> (roslisp-msg-protocol:ros-message)
  ((Obstacles
    :reader Obstacles
    :initarg :Obstacles
    :type (cl:vector smartcar_msgs-msg:ObstacleAttr)
   :initform (cl:make-array 0 :element-type 'smartcar_msgs-msg:ObstacleAttr :initial-element (cl:make-instance 'smartcar_msgs-msg:ObstacleAttr))))
)

(cl:defclass Obstacles (<Obstacles>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Obstacles>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Obstacles)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<Obstacles> is deprecated: use smartcar_msgs-msg:Obstacles instead.")))

(cl:ensure-generic-function 'Obstacles-val :lambda-list '(m))
(cl:defmethod Obstacles-val ((m <Obstacles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:Obstacles-val is deprecated.  Use smartcar_msgs-msg:Obstacles instead.")
  (Obstacles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Obstacles>) ostream)
  "Serializes a message object of type '<Obstacles>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Obstacles))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'Obstacles))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Obstacles>) istream)
  "Deserializes a message object of type '<Obstacles>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Obstacles) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Obstacles)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'smartcar_msgs-msg:ObstacleAttr))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Obstacles>)))
  "Returns string type for a message object of type '<Obstacles>"
  "smartcar_msgs/Obstacles")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Obstacles)))
  "Returns string type for a message object of type 'Obstacles"
  "smartcar_msgs/Obstacles")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Obstacles>)))
  "Returns md5sum for a message object of type '<Obstacles>"
  "42f94931bc3e97baf969e4dc42dad246")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Obstacles)))
  "Returns md5sum for a message object of type 'Obstacles"
  "42f94931bc3e97baf969e4dc42dad246")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Obstacles>)))
  "Returns full string definition for message of type '<Obstacles>"
  (cl:format cl:nil " ObstacleAttr[] Obstacles~%================================================================================~%MSG: smartcar_msgs/ObstacleAttr~%int8 id~%float64 x~%float64 y~%float64 z~%float64 length~%float64 width~%float64 height~%float64 heading~%float64 speed~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Obstacles)))
  "Returns full string definition for message of type 'Obstacles"
  (cl:format cl:nil " ObstacleAttr[] Obstacles~%================================================================================~%MSG: smartcar_msgs/ObstacleAttr~%int8 id~%float64 x~%float64 y~%float64 z~%float64 length~%float64 width~%float64 height~%float64 heading~%float64 speed~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Obstacles>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Obstacles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Obstacles>))
  "Converts a ROS message object to a list"
  (cl:list 'Obstacles
    (cl:cons ':Obstacles (Obstacles msg))
))
