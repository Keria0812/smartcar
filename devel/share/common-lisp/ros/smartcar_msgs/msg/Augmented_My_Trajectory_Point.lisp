; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude Augmented_My_Trajectory_Point.msg.html

(cl:defclass <Augmented_My_Trajectory_Point> (roslisp-msg-protocol:ros-message)
  ((trajectory_point
    :reader trajectory_point
    :initarg :trajectory_point
    :type smartcar_msgs-msg:My_Trajectory_Point
    :initform (cl:make-instance 'smartcar_msgs-msg:My_Trajectory_Point))
   (vehicle_info
    :reader vehicle_info
    :initarg :vehicle_info
    :type smartcar_msgs-msg:VehicleInfo
    :initform (cl:make-instance 'smartcar_msgs-msg:VehicleInfo))
   (goal_id
    :reader goal_id
    :initarg :goal_id
    :type cl:float
    :initform 0.0)
   (preview_id
    :reader preview_id
    :initarg :preview_id
    :type cl:float
    :initform 0.0)
   (lateral_distance_error
    :reader lateral_distance_error
    :initarg :lateral_distance_error
    :type cl:float
    :initform 0.0)
   (max_lateral_distance_error
    :reader max_lateral_distance_error
    :initarg :max_lateral_distance_error
    :type cl:float
    :initform 0.0)
   (average_lateral_distance_error
    :reader average_lateral_distance_error
    :initarg :average_lateral_distance_error
    :type cl:float
    :initform 0.0)
   (velocity_error
    :reader velocity_error
    :initarg :velocity_error
    :type cl:float
    :initform 0.0)
   (max_velocity_error
    :reader max_velocity_error
    :initarg :max_velocity_error
    :type cl:float
    :initform 0.0)
   (average_velocity_error
    :reader average_velocity_error
    :initarg :average_velocity_error
    :type cl:float
    :initform 0.0)
   (heading_error
    :reader heading_error
    :initarg :heading_error
    :type cl:float
    :initform 0.0)
   (max_heading_error
    :reader max_heading_error
    :initarg :max_heading_error
    :type cl:float
    :initform 0.0)
   (average_heading_error
    :reader average_heading_error
    :initarg :average_heading_error
    :type cl:float
    :initform 0.0)
   (computational_time
    :reader computational_time
    :initarg :computational_time
    :type cl:float
    :initform 0.0)
   (average_computational_time
    :reader average_computational_time
    :initarg :average_computational_time
    :type cl:float
    :initform 0.0)
   (max_computational_time
    :reader max_computational_time
    :initarg :max_computational_time
    :type cl:float
    :initform 0.0)
   (slope
    :reader slope
    :initarg :slope
    :type cl:float
    :initform 0.0))
)

(cl:defclass Augmented_My_Trajectory_Point (<Augmented_My_Trajectory_Point>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Augmented_My_Trajectory_Point>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Augmented_My_Trajectory_Point)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<Augmented_My_Trajectory_Point> is deprecated: use smartcar_msgs-msg:Augmented_My_Trajectory_Point instead.")))

(cl:ensure-generic-function 'trajectory_point-val :lambda-list '(m))
(cl:defmethod trajectory_point-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:trajectory_point-val is deprecated.  Use smartcar_msgs-msg:trajectory_point instead.")
  (trajectory_point m))

(cl:ensure-generic-function 'vehicle_info-val :lambda-list '(m))
(cl:defmethod vehicle_info-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:vehicle_info-val is deprecated.  Use smartcar_msgs-msg:vehicle_info instead.")
  (vehicle_info m))

(cl:ensure-generic-function 'goal_id-val :lambda-list '(m))
(cl:defmethod goal_id-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:goal_id-val is deprecated.  Use smartcar_msgs-msg:goal_id instead.")
  (goal_id m))

(cl:ensure-generic-function 'preview_id-val :lambda-list '(m))
(cl:defmethod preview_id-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:preview_id-val is deprecated.  Use smartcar_msgs-msg:preview_id instead.")
  (preview_id m))

(cl:ensure-generic-function 'lateral_distance_error-val :lambda-list '(m))
(cl:defmethod lateral_distance_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:lateral_distance_error-val is deprecated.  Use smartcar_msgs-msg:lateral_distance_error instead.")
  (lateral_distance_error m))

(cl:ensure-generic-function 'max_lateral_distance_error-val :lambda-list '(m))
(cl:defmethod max_lateral_distance_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:max_lateral_distance_error-val is deprecated.  Use smartcar_msgs-msg:max_lateral_distance_error instead.")
  (max_lateral_distance_error m))

(cl:ensure-generic-function 'average_lateral_distance_error-val :lambda-list '(m))
(cl:defmethod average_lateral_distance_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:average_lateral_distance_error-val is deprecated.  Use smartcar_msgs-msg:average_lateral_distance_error instead.")
  (average_lateral_distance_error m))

(cl:ensure-generic-function 'velocity_error-val :lambda-list '(m))
(cl:defmethod velocity_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:velocity_error-val is deprecated.  Use smartcar_msgs-msg:velocity_error instead.")
  (velocity_error m))

(cl:ensure-generic-function 'max_velocity_error-val :lambda-list '(m))
(cl:defmethod max_velocity_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:max_velocity_error-val is deprecated.  Use smartcar_msgs-msg:max_velocity_error instead.")
  (max_velocity_error m))

(cl:ensure-generic-function 'average_velocity_error-val :lambda-list '(m))
(cl:defmethod average_velocity_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:average_velocity_error-val is deprecated.  Use smartcar_msgs-msg:average_velocity_error instead.")
  (average_velocity_error m))

(cl:ensure-generic-function 'heading_error-val :lambda-list '(m))
(cl:defmethod heading_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:heading_error-val is deprecated.  Use smartcar_msgs-msg:heading_error instead.")
  (heading_error m))

(cl:ensure-generic-function 'max_heading_error-val :lambda-list '(m))
(cl:defmethod max_heading_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:max_heading_error-val is deprecated.  Use smartcar_msgs-msg:max_heading_error instead.")
  (max_heading_error m))

(cl:ensure-generic-function 'average_heading_error-val :lambda-list '(m))
(cl:defmethod average_heading_error-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:average_heading_error-val is deprecated.  Use smartcar_msgs-msg:average_heading_error instead.")
  (average_heading_error m))

(cl:ensure-generic-function 'computational_time-val :lambda-list '(m))
(cl:defmethod computational_time-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:computational_time-val is deprecated.  Use smartcar_msgs-msg:computational_time instead.")
  (computational_time m))

(cl:ensure-generic-function 'average_computational_time-val :lambda-list '(m))
(cl:defmethod average_computational_time-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:average_computational_time-val is deprecated.  Use smartcar_msgs-msg:average_computational_time instead.")
  (average_computational_time m))

(cl:ensure-generic-function 'max_computational_time-val :lambda-list '(m))
(cl:defmethod max_computational_time-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:max_computational_time-val is deprecated.  Use smartcar_msgs-msg:max_computational_time instead.")
  (max_computational_time m))

(cl:ensure-generic-function 'slope-val :lambda-list '(m))
(cl:defmethod slope-val ((m <Augmented_My_Trajectory_Point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:slope-val is deprecated.  Use smartcar_msgs-msg:slope instead.")
  (slope m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Augmented_My_Trajectory_Point>) ostream)
  "Serializes a message object of type '<Augmented_My_Trajectory_Point>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'trajectory_point) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'vehicle_info) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'goal_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'preview_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'lateral_distance_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'max_lateral_distance_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'average_lateral_distance_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'velocity_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'max_velocity_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'average_velocity_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'heading_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'max_heading_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'average_heading_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'computational_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'average_computational_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'max_computational_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'slope))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Augmented_My_Trajectory_Point>) istream)
  "Deserializes a message object of type '<Augmented_My_Trajectory_Point>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'trajectory_point) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'vehicle_info) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'goal_id) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'preview_id) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'lateral_distance_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_lateral_distance_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'average_lateral_distance_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocity_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_velocity_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'average_velocity_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_heading_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'average_heading_error) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'computational_time) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'average_computational_time) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_computational_time) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'slope) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Augmented_My_Trajectory_Point>)))
  "Returns string type for a message object of type '<Augmented_My_Trajectory_Point>"
  "smartcar_msgs/Augmented_My_Trajectory_Point")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Augmented_My_Trajectory_Point)))
  "Returns string type for a message object of type 'Augmented_My_Trajectory_Point"
  "smartcar_msgs/Augmented_My_Trajectory_Point")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Augmented_My_Trajectory_Point>)))
  "Returns md5sum for a message object of type '<Augmented_My_Trajectory_Point>"
  "7730dde01d7004063a0f1a42c12ce23e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Augmented_My_Trajectory_Point)))
  "Returns md5sum for a message object of type 'Augmented_My_Trajectory_Point"
  "7730dde01d7004063a0f1a42c12ce23e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Augmented_My_Trajectory_Point>)))
  "Returns full string definition for message of type '<Augmented_My_Trajectory_Point>"
  (cl:format cl:nil "My_Trajectory_Point trajectory_point~%VehicleInfo vehicle_info~%float64 goal_id~%float64 preview_id~%float64 lateral_distance_error~%float64 max_lateral_distance_error~%float64 average_lateral_distance_error~%float64 velocity_error~%float64 max_velocity_error~%float64 average_velocity_error~%float64 heading_error~%float64 max_heading_error~%float64 average_heading_error~%float64 computational_time~%float64 average_computational_time~%float64 max_computational_time~%float64 slope~%~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory_Point~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%float64 l~%float64 dkappa~%float64 ddkappa~%float64 v~%float64 a~%float64 relative_time~%float64 gear~%~%================================================================================~%MSG: smartcar_msgs/VehicleInfo~%Header header~%geometry_msgs/Point localization~%LongitudinalData longitudinal_data~%LateralData lateral_data~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: smartcar_msgs/LongitudinalData~%float64 vel_from_localization~%float64 vel_from_wheels~%float64 acceleration~%float64 traveled_distance~%float64 fl_wheel_angular_velocity~%float64 fr_wheel_angular_velocity~%float64 bl_wheel_angular_velocity~%float64 br_wheel_angular_velocity~%float64 gas_percent~%float64 fl_gas_torque~%float64 fr_gas_torque~%float64 bl_gas_torque~%float64 br_gas_torque~%float64 fl_brake_Torque~%float64 fr_brake_torque~%float64 bl_brake_torque~%float64 br_brake_torque~%~%================================================================================~%MSG: smartcar_msgs/LateralData~%float64 heading_angle~%float64 steering_wheel_angle_actual~%float64 steering_wheel_expected~%float64 steering_wheel_error~%float64 steering_wheel_cmd~%~%float64 fl_steering_angle_actual~%float64 fr_steering_angle_actual~%float64 single_track_steering_angle~%float64 fl_steering_angle_expected~%float64 fr_steering_angle_expected~%float64 fl_steering_error~%float64 fr_steering_error~%float64 fl_steering_cmd~%float64 fr_steering_cmd~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Augmented_My_Trajectory_Point)))
  "Returns full string definition for message of type 'Augmented_My_Trajectory_Point"
  (cl:format cl:nil "My_Trajectory_Point trajectory_point~%VehicleInfo vehicle_info~%float64 goal_id~%float64 preview_id~%float64 lateral_distance_error~%float64 max_lateral_distance_error~%float64 average_lateral_distance_error~%float64 velocity_error~%float64 max_velocity_error~%float64 average_velocity_error~%float64 heading_error~%float64 max_heading_error~%float64 average_heading_error~%float64 computational_time~%float64 average_computational_time~%float64 max_computational_time~%float64 slope~%~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory_Point~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%float64 l~%float64 dkappa~%float64 ddkappa~%float64 v~%float64 a~%float64 relative_time~%float64 gear~%~%================================================================================~%MSG: smartcar_msgs/VehicleInfo~%Header header~%geometry_msgs/Point localization~%LongitudinalData longitudinal_data~%LateralData lateral_data~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: smartcar_msgs/LongitudinalData~%float64 vel_from_localization~%float64 vel_from_wheels~%float64 acceleration~%float64 traveled_distance~%float64 fl_wheel_angular_velocity~%float64 fr_wheel_angular_velocity~%float64 bl_wheel_angular_velocity~%float64 br_wheel_angular_velocity~%float64 gas_percent~%float64 fl_gas_torque~%float64 fr_gas_torque~%float64 bl_gas_torque~%float64 br_gas_torque~%float64 fl_brake_Torque~%float64 fr_brake_torque~%float64 bl_brake_torque~%float64 br_brake_torque~%~%================================================================================~%MSG: smartcar_msgs/LateralData~%float64 heading_angle~%float64 steering_wheel_angle_actual~%float64 steering_wheel_expected~%float64 steering_wheel_error~%float64 steering_wheel_cmd~%~%float64 fl_steering_angle_actual~%float64 fr_steering_angle_actual~%float64 single_track_steering_angle~%float64 fl_steering_angle_expected~%float64 fr_steering_angle_expected~%float64 fl_steering_error~%float64 fr_steering_error~%float64 fl_steering_cmd~%float64 fr_steering_cmd~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Augmented_My_Trajectory_Point>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'trajectory_point))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'vehicle_info))
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
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Augmented_My_Trajectory_Point>))
  "Converts a ROS message object to a list"
  (cl:list 'Augmented_My_Trajectory_Point
    (cl:cons ':trajectory_point (trajectory_point msg))
    (cl:cons ':vehicle_info (vehicle_info msg))
    (cl:cons ':goal_id (goal_id msg))
    (cl:cons ':preview_id (preview_id msg))
    (cl:cons ':lateral_distance_error (lateral_distance_error msg))
    (cl:cons ':max_lateral_distance_error (max_lateral_distance_error msg))
    (cl:cons ':average_lateral_distance_error (average_lateral_distance_error msg))
    (cl:cons ':velocity_error (velocity_error msg))
    (cl:cons ':max_velocity_error (max_velocity_error msg))
    (cl:cons ':average_velocity_error (average_velocity_error msg))
    (cl:cons ':heading_error (heading_error msg))
    (cl:cons ':max_heading_error (max_heading_error msg))
    (cl:cons ':average_heading_error (average_heading_error msg))
    (cl:cons ':computational_time (computational_time msg))
    (cl:cons ':average_computational_time (average_computational_time msg))
    (cl:cons ':max_computational_time (max_computational_time msg))
    (cl:cons ':slope (slope msg))
))
