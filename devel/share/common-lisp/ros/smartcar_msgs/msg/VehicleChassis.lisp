; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude VehicleChassis.msg.html

(cl:defclass <VehicleChassis> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (cmd_torque
    :reader cmd_torque
    :initarg :cmd_torque
    :type cl:float
    :initform 0.0)
   (cmd_decelaration
    :reader cmd_decelaration
    :initarg :cmd_decelaration
    :type cl:float
    :initform 0.0)
   (cmd_gas
    :reader cmd_gas
    :initarg :cmd_gas
    :type cl:float
    :initform 0.0)
   (cmd_brake
    :reader cmd_brake
    :initarg :cmd_brake
    :type cl:float
    :initform 0.0)
   (cmd_steerAng
    :reader cmd_steerAng
    :initarg :cmd_steerAng
    :type cl:float
    :initform 0.0)
   (feedback_brake_press
    :reader feedback_brake_press
    :initarg :feedback_brake_press
    :type cl:float
    :initform 0.0)
   (feedback_gas
    :reader feedback_gas
    :initarg :feedback_gas
    :type cl:float
    :initform 0.0)
   (feedback_torque
    :reader feedback_torque
    :initarg :feedback_torque
    :type cl:float
    :initform 0.0)
   (feedback_Motor_rotv
    :reader feedback_Motor_rotv
    :initarg :feedback_Motor_rotv
    :type cl:float
    :initform 0.0)
   (feedback_steerAng
    :reader feedback_steerAng
    :initarg :feedback_steerAng
    :type cl:float
    :initform 0.0)
   (feedback_tireAng
    :reader feedback_tireAng
    :initarg :feedback_tireAng
    :type cl:float
    :initform 0.0)
   (gas_pedal_press
    :reader gas_pedal_press
    :initarg :gas_pedal_press
    :type cl:boolean
    :initform cl:nil)
   (brake_pedal_press
    :reader brake_pedal_press
    :initarg :brake_pedal_press
    :type cl:boolean
    :initform cl:nil)
   (gear
    :reader gear
    :initarg :gear
    :type cl:string
    :initform "")
   (orientation
    :reader orientation
    :initarg :orientation
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (linear_velocity
    :reader linear_velocity
    :initarg :linear_velocity
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (vehicleAcceleration
    :reader vehicleAcceleration
    :initarg :vehicleAcceleration
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (wheelspeed
    :reader wheelspeed
    :initarg :wheelspeed
    :type (cl:vector cl:float)
   :initform (cl:make-array 4 :element-type 'cl:float :initial-element 0.0))
   (light_state
    :reader light_state
    :initarg :light_state
    :type smartcar_msgs-msg:VehicleLightState
    :initform (cl:make-instance 'smartcar_msgs-msg:VehicleLightState))
   (vehiclespeed
    :reader vehiclespeed
    :initarg :vehiclespeed
    :type cl:float
    :initform 0.0)
   (vcu_mode
    :reader vcu_mode
    :initarg :vcu_mode
    :type cl:integer
    :initform 0))
)

(cl:defclass VehicleChassis (<VehicleChassis>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleChassis>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleChassis)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<VehicleChassis> is deprecated: use smartcar_msgs-msg:VehicleChassis instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:header-val is deprecated.  Use smartcar_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'cmd_torque-val :lambda-list '(m))
(cl:defmethod cmd_torque-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:cmd_torque-val is deprecated.  Use smartcar_msgs-msg:cmd_torque instead.")
  (cmd_torque m))

(cl:ensure-generic-function 'cmd_decelaration-val :lambda-list '(m))
(cl:defmethod cmd_decelaration-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:cmd_decelaration-val is deprecated.  Use smartcar_msgs-msg:cmd_decelaration instead.")
  (cmd_decelaration m))

(cl:ensure-generic-function 'cmd_gas-val :lambda-list '(m))
(cl:defmethod cmd_gas-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:cmd_gas-val is deprecated.  Use smartcar_msgs-msg:cmd_gas instead.")
  (cmd_gas m))

(cl:ensure-generic-function 'cmd_brake-val :lambda-list '(m))
(cl:defmethod cmd_brake-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:cmd_brake-val is deprecated.  Use smartcar_msgs-msg:cmd_brake instead.")
  (cmd_brake m))

(cl:ensure-generic-function 'cmd_steerAng-val :lambda-list '(m))
(cl:defmethod cmd_steerAng-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:cmd_steerAng-val is deprecated.  Use smartcar_msgs-msg:cmd_steerAng instead.")
  (cmd_steerAng m))

(cl:ensure-generic-function 'feedback_brake_press-val :lambda-list '(m))
(cl:defmethod feedback_brake_press-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:feedback_brake_press-val is deprecated.  Use smartcar_msgs-msg:feedback_brake_press instead.")
  (feedback_brake_press m))

(cl:ensure-generic-function 'feedback_gas-val :lambda-list '(m))
(cl:defmethod feedback_gas-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:feedback_gas-val is deprecated.  Use smartcar_msgs-msg:feedback_gas instead.")
  (feedback_gas m))

(cl:ensure-generic-function 'feedback_torque-val :lambda-list '(m))
(cl:defmethod feedback_torque-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:feedback_torque-val is deprecated.  Use smartcar_msgs-msg:feedback_torque instead.")
  (feedback_torque m))

(cl:ensure-generic-function 'feedback_Motor_rotv-val :lambda-list '(m))
(cl:defmethod feedback_Motor_rotv-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:feedback_Motor_rotv-val is deprecated.  Use smartcar_msgs-msg:feedback_Motor_rotv instead.")
  (feedback_Motor_rotv m))

(cl:ensure-generic-function 'feedback_steerAng-val :lambda-list '(m))
(cl:defmethod feedback_steerAng-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:feedback_steerAng-val is deprecated.  Use smartcar_msgs-msg:feedback_steerAng instead.")
  (feedback_steerAng m))

(cl:ensure-generic-function 'feedback_tireAng-val :lambda-list '(m))
(cl:defmethod feedback_tireAng-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:feedback_tireAng-val is deprecated.  Use smartcar_msgs-msg:feedback_tireAng instead.")
  (feedback_tireAng m))

(cl:ensure-generic-function 'gas_pedal_press-val :lambda-list '(m))
(cl:defmethod gas_pedal_press-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:gas_pedal_press-val is deprecated.  Use smartcar_msgs-msg:gas_pedal_press instead.")
  (gas_pedal_press m))

(cl:ensure-generic-function 'brake_pedal_press-val :lambda-list '(m))
(cl:defmethod brake_pedal_press-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:brake_pedal_press-val is deprecated.  Use smartcar_msgs-msg:brake_pedal_press instead.")
  (brake_pedal_press m))

(cl:ensure-generic-function 'gear-val :lambda-list '(m))
(cl:defmethod gear-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:gear-val is deprecated.  Use smartcar_msgs-msg:gear instead.")
  (gear m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:orientation-val is deprecated.  Use smartcar_msgs-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'linear_velocity-val :lambda-list '(m))
(cl:defmethod linear_velocity-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:linear_velocity-val is deprecated.  Use smartcar_msgs-msg:linear_velocity instead.")
  (linear_velocity m))

(cl:ensure-generic-function 'vehicleAcceleration-val :lambda-list '(m))
(cl:defmethod vehicleAcceleration-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:vehicleAcceleration-val is deprecated.  Use smartcar_msgs-msg:vehicleAcceleration instead.")
  (vehicleAcceleration m))

(cl:ensure-generic-function 'wheelspeed-val :lambda-list '(m))
(cl:defmethod wheelspeed-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:wheelspeed-val is deprecated.  Use smartcar_msgs-msg:wheelspeed instead.")
  (wheelspeed m))

(cl:ensure-generic-function 'light_state-val :lambda-list '(m))
(cl:defmethod light_state-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:light_state-val is deprecated.  Use smartcar_msgs-msg:light_state instead.")
  (light_state m))

(cl:ensure-generic-function 'vehiclespeed-val :lambda-list '(m))
(cl:defmethod vehiclespeed-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:vehiclespeed-val is deprecated.  Use smartcar_msgs-msg:vehiclespeed instead.")
  (vehiclespeed m))

(cl:ensure-generic-function 'vcu_mode-val :lambda-list '(m))
(cl:defmethod vcu_mode-val ((m <VehicleChassis>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:vcu_mode-val is deprecated.  Use smartcar_msgs-msg:vcu_mode instead.")
  (vcu_mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleChassis>) ostream)
  "Serializes a message object of type '<VehicleChassis>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'cmd_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'cmd_decelaration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'cmd_gas))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'cmd_brake))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'cmd_steerAng))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'feedback_brake_press))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'feedback_gas))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'feedback_torque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'feedback_Motor_rotv))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'feedback_steerAng))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'feedback_tireAng))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'gas_pedal_press) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'brake_pedal_press) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'gear))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'gear))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'orientation))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'linear_velocity))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'vehicleAcceleration))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'wheelspeed))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'light_state) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'vehiclespeed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'vcu_mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleChassis>) istream)
  "Deserializes a message object of type '<VehicleChassis>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'cmd_torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'cmd_decelaration) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'cmd_gas) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'cmd_brake) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'cmd_steerAng) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'feedback_brake_press) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'feedback_gas) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'feedback_torque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'feedback_Motor_rotv) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'feedback_steerAng) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'feedback_tireAng) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:slot-value msg 'gas_pedal_press) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'brake_pedal_press) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gear) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'gear) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:setf (cl:slot-value msg 'orientation) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'orientation)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'linear_velocity) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'linear_velocity)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'vehicleAcceleration) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'vehicleAcceleration)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'wheelspeed) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'wheelspeed)))
    (cl:dotimes (i 4)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'light_state) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vehiclespeed) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'vcu_mode) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleChassis>)))
  "Returns string type for a message object of type '<VehicleChassis>"
  "smartcar_msgs/VehicleChassis")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleChassis)))
  "Returns string type for a message object of type 'VehicleChassis"
  "smartcar_msgs/VehicleChassis")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleChassis>)))
  "Returns md5sum for a message object of type '<VehicleChassis>"
  "ebba083aece22e9a5c6fc1592f401f4c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleChassis)))
  "Returns md5sum for a message object of type 'VehicleChassis"
  "ebba083aece22e9a5c6fc1592f401f4c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleChassis>)))
  "Returns full string definition for message of type '<VehicleChassis>"
  (cl:format cl:nil "Header header~%#控制量~%float64 cmd_torque  #N·m~%float64 cmd_decelaration #m/s^2~%float64 cmd_gas ~%float64 cmd_brake~%float64 cmd_steerAng #deg~%#反馈量~%float64 feedback_brake_press  #%100~%float64 feedback_gas  #%100~%float64 feedback_torque  #N·m~%float64 feedback_Motor_rotv #round/min~%float64 feedback_steerAng #deg~%float64 feedback_tireAng #deg~%~%~%bool gas_pedal_press~%bool brake_pedal_press~%string gear~%float64[3] orientation #deg, Guass frame(deg), X-front, Y-right, Z-down pitch, roll, yaw~%float64[3] linear_velocity  #km/h, Guass frame~%float64[3] vehicleAcceleration #m/s^2 vehicle frame~%float64[4] wheelspeed #FL、FR、RL、RR km/h~%~%#EV~%smartcar_msgs/VehicleLightState light_state #EV~%#km/h~%float64 vehiclespeed ~%~%#vcu_mode, 0 manual_driving, 1 iECU , 2 remote_driving, 3 only control steer, 4 only control gas/brake~%int32 vcu_mode  ~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/VehicleLightState~%Header header~%#0 mid, 1 turn left, 2 turn right~%int32 turn_light ~%~%#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam~%int32 car_light~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleChassis)))
  "Returns full string definition for message of type 'VehicleChassis"
  (cl:format cl:nil "Header header~%#控制量~%float64 cmd_torque  #N·m~%float64 cmd_decelaration #m/s^2~%float64 cmd_gas ~%float64 cmd_brake~%float64 cmd_steerAng #deg~%#反馈量~%float64 feedback_brake_press  #%100~%float64 feedback_gas  #%100~%float64 feedback_torque  #N·m~%float64 feedback_Motor_rotv #round/min~%float64 feedback_steerAng #deg~%float64 feedback_tireAng #deg~%~%~%bool gas_pedal_press~%bool brake_pedal_press~%string gear~%float64[3] orientation #deg, Guass frame(deg), X-front, Y-right, Z-down pitch, roll, yaw~%float64[3] linear_velocity  #km/h, Guass frame~%float64[3] vehicleAcceleration #m/s^2 vehicle frame~%float64[4] wheelspeed #FL、FR、RL、RR km/h~%~%#EV~%smartcar_msgs/VehicleLightState light_state #EV~%#km/h~%float64 vehiclespeed ~%~%#vcu_mode, 0 manual_driving, 1 iECU , 2 remote_driving, 3 only control steer, 4 only control gas/brake~%int32 vcu_mode  ~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/VehicleLightState~%Header header~%#0 mid, 1 turn left, 2 turn right~%int32 turn_light ~%~%#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam~%int32 car_light~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleChassis>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
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
     1
     1
     4 (cl:length (cl:slot-value msg 'gear))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'orientation) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'linear_velocity) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'vehicleAcceleration) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'wheelspeed) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'light_state))
     8
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleChassis>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleChassis
    (cl:cons ':header (header msg))
    (cl:cons ':cmd_torque (cmd_torque msg))
    (cl:cons ':cmd_decelaration (cmd_decelaration msg))
    (cl:cons ':cmd_gas (cmd_gas msg))
    (cl:cons ':cmd_brake (cmd_brake msg))
    (cl:cons ':cmd_steerAng (cmd_steerAng msg))
    (cl:cons ':feedback_brake_press (feedback_brake_press msg))
    (cl:cons ':feedback_gas (feedback_gas msg))
    (cl:cons ':feedback_torque (feedback_torque msg))
    (cl:cons ':feedback_Motor_rotv (feedback_Motor_rotv msg))
    (cl:cons ':feedback_steerAng (feedback_steerAng msg))
    (cl:cons ':feedback_tireAng (feedback_tireAng msg))
    (cl:cons ':gas_pedal_press (gas_pedal_press msg))
    (cl:cons ':brake_pedal_press (brake_pedal_press msg))
    (cl:cons ':gear (gear msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':linear_velocity (linear_velocity msg))
    (cl:cons ':vehicleAcceleration (vehicleAcceleration msg))
    (cl:cons ':wheelspeed (wheelspeed msg))
    (cl:cons ':light_state (light_state msg))
    (cl:cons ':vehiclespeed (vehiclespeed msg))
    (cl:cons ':vcu_mode (vcu_mode msg))
))
