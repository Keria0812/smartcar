; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude LongitudinalData.msg.html

(cl:defclass <LongitudinalData> (roslisp-msg-protocol:ros-message)
  ((vel_from_localization
    :reader vel_from_localization
    :initarg :vel_from_localization
    :type cl:float
    :initform 0.0)
   (vel_from_wheels
    :reader vel_from_wheels
    :initarg :vel_from_wheels
    :type cl:float
    :initform 0.0)
   (acceleration
    :reader acceleration
    :initarg :acceleration
    :type cl:float
    :initform 0.0)
   (traveled_distance
    :reader traveled_distance
    :initarg :traveled_distance
    :type cl:float
    :initform 0.0)
   (fl_wheel_angular_velocity
    :reader fl_wheel_angular_velocity
    :initarg :fl_wheel_angular_velocity
    :type cl:float
    :initform 0.0)
   (fr_wheel_angular_velocity
    :reader fr_wheel_angular_velocity
    :initarg :fr_wheel_angular_velocity
    :type cl:float
    :initform 0.0)
   (bl_wheel_angular_velocity
    :reader bl_wheel_angular_velocity
    :initarg :bl_wheel_angular_velocity
    :type cl:float
    :initform 0.0)
   (br_wheel_angular_velocity
    :reader br_wheel_angular_velocity
    :initarg :br_wheel_angular_velocity
    :type cl:float
    :initform 0.0)
   (gas_percent
    :reader gas_percent
    :initarg :gas_percent
    :type cl:float
    :initform 0.0)
   (fl_gas_torque
    :reader fl_gas_torque
    :initarg :fl_gas_torque
    :type cl:float
    :initform 0.0)
   (fr_gas_torque
    :reader fr_gas_torque
    :initarg :fr_gas_torque
    :type cl:float
    :initform 0.0)
   (bl_gas_torque
    :reader bl_gas_torque
    :initarg :bl_gas_torque
    :type cl:float
    :initform 0.0)
   (br_gas_torque
    :reader br_gas_torque
    :initarg :br_gas_torque
    :type cl:float
    :initform 0.0)
   (fl_brake_Torque
    :reader fl_brake_Torque
    :initarg :fl_brake_Torque
    :type cl:float
    :initform 0.0)
   (fr_brake_torque
    :reader fr_brake_torque
    :initarg :fr_brake_torque
    :type cl:float
    :initform 0.0)
   (bl_brake_torque
    :reader bl_brake_torque
    :initarg :bl_brake_torque
    :type cl:float
    :initform 0.0)
   (br_brake_torque
    :reader br_brake_torque
    :initarg :br_brake_torque
    :type cl:float
    :initform 0.0))
)

(cl:defclass LongitudinalData (<LongitudinalData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LongitudinalData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LongitudinalData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<LongitudinalData> is deprecated: use smartcar_msgs-msg:LongitudinalData instead.")))

(cl:ensure-generic-function 'vel_from_localization-val :lambda-list '(m))
(cl:defmethod vel_from_localization-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:vel_from_localization-val is deprecated.  Use smartcar_msgs-msg:vel_from_localization instead.")
  (vel_from_localization m))

(cl:ensure-generic-function 'vel_from_wheels-val :lambda-list '(m))
(cl:defmethod vel_from_wheels-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:vel_from_wheels-val is deprecated.  Use smartcar_msgs-msg:vel_from_wheels instead.")
  (vel_from_wheels m))

(cl:ensure-generic-function 'acceleration-val :lambda-list '(m))
(cl:defmethod acceleration-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:acceleration-val is deprecated.  Use smartcar_msgs-msg:acceleration instead.")
  (acceleration m))

(cl:ensure-generic-function 'traveled_distance-val :lambda-list '(m))
(cl:defmethod traveled_distance-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:traveled_distance-val is deprecated.  Use smartcar_msgs-msg:traveled_distance instead.")
  (traveled_distance m))

(cl:ensure-generic-function 'fl_wheel_angular_velocity-val :lambda-list '(m))
(cl:defmethod fl_wheel_angular_velocity-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:fl_wheel_angular_velocity-val is deprecated.  Use smartcar_msgs-msg:fl_wheel_angular_velocity instead.")
  (fl_wheel_angular_velocity m))

(cl:ensure-generic-function 'fr_wheel_angular_velocity-val :lambda-list '(m))
(cl:defmethod fr_wheel_angular_velocity-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:fr_wheel_angular_velocity-val is deprecated.  Use smartcar_msgs-msg:fr_wheel_angular_velocity instead.")
  (fr_wheel_angular_velocity m))

(cl:ensure-generic-function 'bl_wheel_angular_velocity-val :lambda-list '(m))
(cl:defmethod bl_wheel_angular_velocity-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:bl_wheel_angular_velocity-val is deprecated.  Use smartcar_msgs-msg:bl_wheel_angular_velocity instead.")
  (bl_wheel_angular_velocity m))

(cl:ensure-generic-function 'br_wheel_angular_velocity-val :lambda-list '(m))
(cl:defmethod br_wheel_angular_velocity-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:br_wheel_angular_velocity-val is deprecated.  Use smartcar_msgs-msg:br_wheel_angular_velocity instead.")
  (br_wheel_angular_velocity m))

(cl:ensure-generic-function 'gas_percent-val :lambda-list '(m))
(cl:defmethod gas_percent-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:gas_percent-val is deprecated.  Use smartcar_msgs-msg:gas_percent instead.")
  (gas_percent m))

(cl:ensure-generic-function 'fl_gas_torque-val :lambda-list '(m))
(cl:defmethod fl_gas_torque-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:fl_gas_torque-val is deprecated.  Use smartcar_msgs-msg:fl_gas_torque instead.")
  (fl_gas_torque m))

(cl:ensure-generic-function 'fr_gas_torque-val :lambda-list '(m))
(cl:defmethod fr_gas_torque-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:fr_gas_torque-val is deprecated.  Use smartcar_msgs-msg:fr_gas_torque instead.")
  (fr_gas_torque m))

(cl:ensure-generic-function 'bl_gas_torque-val :lambda-list '(m))
(cl:defmethod bl_gas_torque-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:bl_gas_torque-val is deprecated.  Use smartcar_msgs-msg:bl_gas_torque instead.")
  (bl_gas_torque m))

(cl:ensure-generic-function 'br_gas_torque-val :lambda-list '(m))
(cl:defmethod br_gas_torque-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:br_gas_torque-val is deprecated.  Use smartcar_msgs-msg:br_gas_torque instead.")
  (br_gas_torque m))

(cl:ensure-generic-function 'fl_brake_Torque-val :lambda-list '(m))
(cl:defmethod fl_brake_Torque-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:fl_brake_Torque-val is deprecated.  Use smartcar_msgs-msg:fl_brake_Torque instead.")
  (fl_brake_Torque m))

(cl:ensure-generic-function 'fr_brake_torque-val :lambda-list '(m))
(cl:defmethod fr_brake_torque-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:fr_brake_torque-val is deprecated.  Use smartcar_msgs-msg:fr_brake_torque instead.")
  (fr_brake_torque m))

(cl:ensure-generic-function 'bl_brake_torque-val :lambda-list '(m))
(cl:defmethod bl_brake_torque-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:bl_brake_torque-val is deprecated.  Use smartcar_msgs-msg:bl_brake_torque instead.")
  (bl_brake_torque m))

(cl:ensure-generic-function 'br_brake_torque-val :lambda-list '(m))
(cl:defmethod br_brake_torque-val ((m <LongitudinalData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:br_brake_torque-val is deprecated.  Use smartcar_msgs-msg:br_brake_torque instead.")
  (br_brake_torque m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LongitudinalData>) ostream)
  "Serializes a message object of type '<LongitudinalData>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'vel_from_localization))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'vel_from_wheels))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'acceleration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'traveled_distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fl_wheel_angular_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fr_wheel_angular_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'bl_wheel_angular_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'br_wheel_angular_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gas_percent))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fl_gas_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fr_gas_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'bl_gas_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'br_gas_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fl_brake_Torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fr_brake_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'bl_brake_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'br_brake_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LongitudinalData>) istream)
  "Deserializes a message object of type '<LongitudinalData>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel_from_localization) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel_from_wheels) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acceleration) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'traveled_distance) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fl_wheel_angular_velocity) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fr_wheel_angular_velocity) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'bl_wheel_angular_velocity) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'br_wheel_angular_velocity) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gas_percent) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fl_gas_torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fr_gas_torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'bl_gas_torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'br_gas_torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fl_brake_Torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fr_brake_torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'bl_brake_torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'br_brake_torque) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LongitudinalData>)))
  "Returns string type for a message object of type '<LongitudinalData>"
  "smartcar_msgs/LongitudinalData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LongitudinalData)))
  "Returns string type for a message object of type 'LongitudinalData"
  "smartcar_msgs/LongitudinalData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LongitudinalData>)))
  "Returns md5sum for a message object of type '<LongitudinalData>"
  "5e1bfb472e4917d66e73052e666a6e34")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LongitudinalData)))
  "Returns md5sum for a message object of type 'LongitudinalData"
  "5e1bfb472e4917d66e73052e666a6e34")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LongitudinalData>)))
  "Returns full string definition for message of type '<LongitudinalData>"
  (cl:format cl:nil "float64 vel_from_localization~%float64 vel_from_wheels~%float64 acceleration~%float64 traveled_distance~%float64 fl_wheel_angular_velocity~%float64 fr_wheel_angular_velocity~%float64 bl_wheel_angular_velocity~%float64 br_wheel_angular_velocity~%float64 gas_percent~%float64 fl_gas_torque~%float64 fr_gas_torque~%float64 bl_gas_torque~%float64 br_gas_torque~%float64 fl_brake_Torque~%float64 fr_brake_torque~%float64 bl_brake_torque~%float64 br_brake_torque~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LongitudinalData)))
  "Returns full string definition for message of type 'LongitudinalData"
  (cl:format cl:nil "float64 vel_from_localization~%float64 vel_from_wheels~%float64 acceleration~%float64 traveled_distance~%float64 fl_wheel_angular_velocity~%float64 fr_wheel_angular_velocity~%float64 bl_wheel_angular_velocity~%float64 br_wheel_angular_velocity~%float64 gas_percent~%float64 fl_gas_torque~%float64 fr_gas_torque~%float64 bl_gas_torque~%float64 br_gas_torque~%float64 fl_brake_Torque~%float64 fr_brake_torque~%float64 bl_brake_torque~%float64 br_brake_torque~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LongitudinalData>))
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
     8
     8
     8
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LongitudinalData>))
  "Converts a ROS message object to a list"
  (cl:list 'LongitudinalData
    (cl:cons ':vel_from_localization (vel_from_localization msg))
    (cl:cons ':vel_from_wheels (vel_from_wheels msg))
    (cl:cons ':acceleration (acceleration msg))
    (cl:cons ':traveled_distance (traveled_distance msg))
    (cl:cons ':fl_wheel_angular_velocity (fl_wheel_angular_velocity msg))
    (cl:cons ':fr_wheel_angular_velocity (fr_wheel_angular_velocity msg))
    (cl:cons ':bl_wheel_angular_velocity (bl_wheel_angular_velocity msg))
    (cl:cons ':br_wheel_angular_velocity (br_wheel_angular_velocity msg))
    (cl:cons ':gas_percent (gas_percent msg))
    (cl:cons ':fl_gas_torque (fl_gas_torque msg))
    (cl:cons ':fr_gas_torque (fr_gas_torque msg))
    (cl:cons ':bl_gas_torque (bl_gas_torque msg))
    (cl:cons ':br_gas_torque (br_gas_torque msg))
    (cl:cons ':fl_brake_Torque (fl_brake_Torque msg))
    (cl:cons ':fr_brake_torque (fr_brake_torque msg))
    (cl:cons ':bl_brake_torque (bl_brake_torque msg))
    (cl:cons ':br_brake_torque (br_brake_torque msg))
))
