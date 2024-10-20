; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude VehicleLightCommand.msg.html

(cl:defclass <VehicleLightCommand> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (brakelight_cmd
    :reader brakelight_cmd
    :initarg :brakelight_cmd
    :type cl:integer
    :initform 0)
   (iecu_lock_cmd
    :reader iecu_lock_cmd
    :initarg :iecu_lock_cmd
    :type cl:integer
    :initform 0)
   (turn_light_cmd
    :reader turn_light_cmd
    :initarg :turn_light_cmd
    :type cl:integer
    :initform 0)
   (car_light_cmd
    :reader car_light_cmd
    :initarg :car_light_cmd
    :type cl:integer
    :initform 0))
)

(cl:defclass VehicleLightCommand (<VehicleLightCommand>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleLightCommand>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleLightCommand)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<VehicleLightCommand> is deprecated: use smartcar_msgs-msg:VehicleLightCommand instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleLightCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:header-val is deprecated.  Use smartcar_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'brakelight_cmd-val :lambda-list '(m))
(cl:defmethod brakelight_cmd-val ((m <VehicleLightCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:brakelight_cmd-val is deprecated.  Use smartcar_msgs-msg:brakelight_cmd instead.")
  (brakelight_cmd m))

(cl:ensure-generic-function 'iecu_lock_cmd-val :lambda-list '(m))
(cl:defmethod iecu_lock_cmd-val ((m <VehicleLightCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:iecu_lock_cmd-val is deprecated.  Use smartcar_msgs-msg:iecu_lock_cmd instead.")
  (iecu_lock_cmd m))

(cl:ensure-generic-function 'turn_light_cmd-val :lambda-list '(m))
(cl:defmethod turn_light_cmd-val ((m <VehicleLightCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:turn_light_cmd-val is deprecated.  Use smartcar_msgs-msg:turn_light_cmd instead.")
  (turn_light_cmd m))

(cl:ensure-generic-function 'car_light_cmd-val :lambda-list '(m))
(cl:defmethod car_light_cmd-val ((m <VehicleLightCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:car_light_cmd-val is deprecated.  Use smartcar_msgs-msg:car_light_cmd instead.")
  (car_light_cmd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleLightCommand>) ostream)
  "Serializes a message object of type '<VehicleLightCommand>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'brakelight_cmd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'iecu_lock_cmd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'turn_light_cmd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'car_light_cmd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleLightCommand>) istream)
  "Deserializes a message object of type '<VehicleLightCommand>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'brakelight_cmd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'iecu_lock_cmd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'turn_light_cmd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'car_light_cmd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleLightCommand>)))
  "Returns string type for a message object of type '<VehicleLightCommand>"
  "smartcar_msgs/VehicleLightCommand")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleLightCommand)))
  "Returns string type for a message object of type 'VehicleLightCommand"
  "smartcar_msgs/VehicleLightCommand")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleLightCommand>)))
  "Returns md5sum for a message object of type '<VehicleLightCommand>"
  "8e2364f8ec89eb4c9476632c281aea24")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleLightCommand)))
  "Returns md5sum for a message object of type 'VehicleLightCommand"
  "8e2364f8ec89eb4c9476632c281aea24")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleLightCommand>)))
  "Returns full string definition for message of type '<VehicleLightCommand>"
  (cl:format cl:nil "Header header~%~%#brakelight ~%int32 brakelight_cmd~%~%#iecu_lock,1 unlock~%int32 iecu_lock_cmd~%~%#0 mid, 1 turn left, 2 turn right~%int32 turn_light_cmd ~%~%#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam~%int32 car_light_cmd~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleLightCommand)))
  "Returns full string definition for message of type 'VehicleLightCommand"
  (cl:format cl:nil "Header header~%~%#brakelight ~%int32 brakelight_cmd~%~%#iecu_lock,1 unlock~%int32 iecu_lock_cmd~%~%#0 mid, 1 turn left, 2 turn right~%int32 turn_light_cmd ~%~%#0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam~%int32 car_light_cmd~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleLightCommand>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleLightCommand>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleLightCommand
    (cl:cons ':header (header msg))
    (cl:cons ':brakelight_cmd (brakelight_cmd msg))
    (cl:cons ':iecu_lock_cmd (iecu_lock_cmd msg))
    (cl:cons ':turn_light_cmd (turn_light_cmd msg))
    (cl:cons ':car_light_cmd (car_light_cmd msg))
))
