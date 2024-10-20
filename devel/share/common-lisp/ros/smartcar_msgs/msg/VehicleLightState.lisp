; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude VehicleLightState.msg.html

(cl:defclass <VehicleLightState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (turn_light
    :reader turn_light
    :initarg :turn_light
    :type cl:integer
    :initform 0)
   (car_light
    :reader car_light
    :initarg :car_light
    :type cl:integer
    :initform 0))
)

(cl:defclass VehicleLightState (<VehicleLightState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleLightState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleLightState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<VehicleLightState> is deprecated: use smartcar_msgs-msg:VehicleLightState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleLightState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:header-val is deprecated.  Use smartcar_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <VehicleLightState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:turn_light-val is deprecated.  Use smartcar_msgs-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'car_light-val :lambda-list '(m))
(cl:defmethod car_light-val ((m <VehicleLightState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:car_light-val is deprecated.  Use smartcar_msgs-msg:car_light instead.")
  (car_light m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleLightState>) ostream)
  "Serializes a message object of type '<VehicleLightState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'turn_light)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'car_light)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleLightState>) istream)
  "Deserializes a message object of type '<VehicleLightState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'turn_light) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'car_light) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleLightState>)))
  "Returns string type for a message object of type '<VehicleLightState>"
  "smartcar_msgs/VehicleLightState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleLightState)))
  "Returns string type for a message object of type 'VehicleLightState"
  "smartcar_msgs/VehicleLightState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleLightState>)))
  "Returns md5sum for a message object of type '<VehicleLightState>"
  "8e22a6beadc4b37e8e1c81c5e770f4eb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleLightState)))
  "Returns md5sum for a message object of type 'VehicleLightState"
  "8e22a6beadc4b37e8e1c81c5e770f4eb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleLightState>)))
  "Returns full string definition for message of type '<VehicleLightState>"
  (cl:format cl:nil "Header header~%#0 mid, 1 turn left, 2 turn right~%int32 turn_light ~%~%#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam~%int32 car_light~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleLightState)))
  "Returns full string definition for message of type 'VehicleLightState"
  (cl:format cl:nil "Header header~%#0 mid, 1 turn left, 2 turn right~%int32 turn_light ~%~%#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam~%int32 car_light~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleLightState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleLightState>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleLightState
    (cl:cons ':header (header msg))
    (cl:cons ':turn_light (turn_light msg))
    (cl:cons ':car_light (car_light msg))
))
