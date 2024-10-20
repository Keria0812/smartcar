; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude DimensionInfo.msg.html

(cl:defclass <DimensionInfo> (roslisp-msg-protocol:ros-message)
  ((wheel_base
    :reader wheel_base
    :initarg :wheel_base
    :type cl:float
    :initform 0.0)
   (front_wheel_base
    :reader front_wheel_base
    :initarg :front_wheel_base
    :type cl:float
    :initform 0.0)
   (rear_wheel_base
    :reader rear_wheel_base
    :initarg :rear_wheel_base
    :type cl:float
    :initform 0.0)
   (track
    :reader track
    :initarg :track
    :type cl:float
    :initform 0.0)
   (mass
    :reader mass
    :initarg :mass
    :type cl:float
    :initform 0.0)
   (front_cornering_stiffness
    :reader front_cornering_stiffness
    :initarg :front_cornering_stiffness
    :type cl:float
    :initform 0.0)
   (rear_cornering_stiffness
    :reader rear_cornering_stiffness
    :initarg :rear_cornering_stiffness
    :type cl:float
    :initform 0.0)
   (max_friction_coefficient
    :reader max_friction_coefficient
    :initarg :max_friction_coefficient
    :type cl:float
    :initform 0.0)
   (Iz
    :reader Iz
    :initarg :Iz
    :type cl:float
    :initform 0.0))
)

(cl:defclass DimensionInfo (<DimensionInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DimensionInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DimensionInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<DimensionInfo> is deprecated: use smartcar_msgs-msg:DimensionInfo instead.")))

(cl:ensure-generic-function 'wheel_base-val :lambda-list '(m))
(cl:defmethod wheel_base-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:wheel_base-val is deprecated.  Use smartcar_msgs-msg:wheel_base instead.")
  (wheel_base m))

(cl:ensure-generic-function 'front_wheel_base-val :lambda-list '(m))
(cl:defmethod front_wheel_base-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:front_wheel_base-val is deprecated.  Use smartcar_msgs-msg:front_wheel_base instead.")
  (front_wheel_base m))

(cl:ensure-generic-function 'rear_wheel_base-val :lambda-list '(m))
(cl:defmethod rear_wheel_base-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:rear_wheel_base-val is deprecated.  Use smartcar_msgs-msg:rear_wheel_base instead.")
  (rear_wheel_base m))

(cl:ensure-generic-function 'track-val :lambda-list '(m))
(cl:defmethod track-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:track-val is deprecated.  Use smartcar_msgs-msg:track instead.")
  (track m))

(cl:ensure-generic-function 'mass-val :lambda-list '(m))
(cl:defmethod mass-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:mass-val is deprecated.  Use smartcar_msgs-msg:mass instead.")
  (mass m))

(cl:ensure-generic-function 'front_cornering_stiffness-val :lambda-list '(m))
(cl:defmethod front_cornering_stiffness-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:front_cornering_stiffness-val is deprecated.  Use smartcar_msgs-msg:front_cornering_stiffness instead.")
  (front_cornering_stiffness m))

(cl:ensure-generic-function 'rear_cornering_stiffness-val :lambda-list '(m))
(cl:defmethod rear_cornering_stiffness-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:rear_cornering_stiffness-val is deprecated.  Use smartcar_msgs-msg:rear_cornering_stiffness instead.")
  (rear_cornering_stiffness m))

(cl:ensure-generic-function 'max_friction_coefficient-val :lambda-list '(m))
(cl:defmethod max_friction_coefficient-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:max_friction_coefficient-val is deprecated.  Use smartcar_msgs-msg:max_friction_coefficient instead.")
  (max_friction_coefficient m))

(cl:ensure-generic-function 'Iz-val :lambda-list '(m))
(cl:defmethod Iz-val ((m <DimensionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:Iz-val is deprecated.  Use smartcar_msgs-msg:Iz instead.")
  (Iz m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DimensionInfo>) ostream)
  "Serializes a message object of type '<DimensionInfo>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'wheel_base))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'front_wheel_base))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'rear_wheel_base))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'track))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'mass))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'front_cornering_stiffness))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'rear_cornering_stiffness))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'max_friction_coefficient))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'Iz))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DimensionInfo>) istream)
  "Deserializes a message object of type '<DimensionInfo>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wheel_base) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_wheel_base) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_wheel_base) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'track) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mass) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_cornering_stiffness) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_cornering_stiffness) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_friction_coefficient) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Iz) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DimensionInfo>)))
  "Returns string type for a message object of type '<DimensionInfo>"
  "smartcar_msgs/DimensionInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DimensionInfo)))
  "Returns string type for a message object of type 'DimensionInfo"
  "smartcar_msgs/DimensionInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DimensionInfo>)))
  "Returns md5sum for a message object of type '<DimensionInfo>"
  "83b23d28199a7ca222af4ff1d8a32e6b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DimensionInfo)))
  "Returns md5sum for a message object of type 'DimensionInfo"
  "83b23d28199a7ca222af4ff1d8a32e6b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DimensionInfo>)))
  "Returns full string definition for message of type '<DimensionInfo>"
  (cl:format cl:nil "float64 wheel_base~%float64 front_wheel_base~%float64 rear_wheel_base~%float64 track~%float64 mass~%float64 front_cornering_stiffness~%float64 rear_cornering_stiffness~%float64 max_friction_coefficient~%float64 Iz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DimensionInfo)))
  "Returns full string definition for message of type 'DimensionInfo"
  (cl:format cl:nil "float64 wheel_base~%float64 front_wheel_base~%float64 rear_wheel_base~%float64 track~%float64 mass~%float64 front_cornering_stiffness~%float64 rear_cornering_stiffness~%float64 max_friction_coefficient~%float64 Iz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DimensionInfo>))
  (cl:+ 0
     8
     8
     8
     8
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DimensionInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'DimensionInfo
    (cl:cons ':wheel_base (wheel_base msg))
    (cl:cons ':front_wheel_base (front_wheel_base msg))
    (cl:cons ':rear_wheel_base (rear_wheel_base msg))
    (cl:cons ':track (track msg))
    (cl:cons ':mass (mass msg))
    (cl:cons ':front_cornering_stiffness (front_cornering_stiffness msg))
    (cl:cons ':rear_cornering_stiffness (rear_cornering_stiffness msg))
    (cl:cons ':max_friction_coefficient (max_friction_coefficient msg))
    (cl:cons ':Iz (Iz msg))
))
