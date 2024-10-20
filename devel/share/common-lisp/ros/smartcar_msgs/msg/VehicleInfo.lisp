; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude VehicleInfo.msg.html

(cl:defclass <VehicleInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (localization
    :reader localization
    :initarg :localization
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (longitudinal_data
    :reader longitudinal_data
    :initarg :longitudinal_data
    :type smartcar_msgs-msg:LongitudinalData
    :initform (cl:make-instance 'smartcar_msgs-msg:LongitudinalData))
   (lateral_data
    :reader lateral_data
    :initarg :lateral_data
    :type smartcar_msgs-msg:LateralData
    :initform (cl:make-instance 'smartcar_msgs-msg:LateralData)))
)

(cl:defclass VehicleInfo (<VehicleInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<VehicleInfo> is deprecated: use smartcar_msgs-msg:VehicleInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:header-val is deprecated.  Use smartcar_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'localization-val :lambda-list '(m))
(cl:defmethod localization-val ((m <VehicleInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:localization-val is deprecated.  Use smartcar_msgs-msg:localization instead.")
  (localization m))

(cl:ensure-generic-function 'longitudinal_data-val :lambda-list '(m))
(cl:defmethod longitudinal_data-val ((m <VehicleInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:longitudinal_data-val is deprecated.  Use smartcar_msgs-msg:longitudinal_data instead.")
  (longitudinal_data m))

(cl:ensure-generic-function 'lateral_data-val :lambda-list '(m))
(cl:defmethod lateral_data-val ((m <VehicleInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:lateral_data-val is deprecated.  Use smartcar_msgs-msg:lateral_data instead.")
  (lateral_data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleInfo>) ostream)
  "Serializes a message object of type '<VehicleInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'localization) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'longitudinal_data) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'lateral_data) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleInfo>) istream)
  "Deserializes a message object of type '<VehicleInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'localization) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'longitudinal_data) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'lateral_data) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleInfo>)))
  "Returns string type for a message object of type '<VehicleInfo>"
  "smartcar_msgs/VehicleInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleInfo)))
  "Returns string type for a message object of type 'VehicleInfo"
  "smartcar_msgs/VehicleInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleInfo>)))
  "Returns md5sum for a message object of type '<VehicleInfo>"
  "ce1548f612651099d85d928f1bef6a2e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleInfo)))
  "Returns md5sum for a message object of type 'VehicleInfo"
  "ce1548f612651099d85d928f1bef6a2e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleInfo>)))
  "Returns full string definition for message of type '<VehicleInfo>"
  (cl:format cl:nil "Header header~%geometry_msgs/Point localization~%LongitudinalData longitudinal_data~%LateralData lateral_data~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: smartcar_msgs/LongitudinalData~%float64 vel_from_localization~%float64 vel_from_wheels~%float64 acceleration~%float64 traveled_distance~%float64 fl_wheel_angular_velocity~%float64 fr_wheel_angular_velocity~%float64 bl_wheel_angular_velocity~%float64 br_wheel_angular_velocity~%float64 gas_percent~%float64 fl_gas_torque~%float64 fr_gas_torque~%float64 bl_gas_torque~%float64 br_gas_torque~%float64 fl_brake_Torque~%float64 fr_brake_torque~%float64 bl_brake_torque~%float64 br_brake_torque~%~%================================================================================~%MSG: smartcar_msgs/LateralData~%float64 heading_angle~%float64 steering_wheel_angle_actual~%float64 steering_wheel_expected~%float64 steering_wheel_error~%float64 steering_wheel_cmd~%~%float64 fl_steering_angle_actual~%float64 fr_steering_angle_actual~%float64 single_track_steering_angle~%float64 fl_steering_angle_expected~%float64 fr_steering_angle_expected~%float64 fl_steering_error~%float64 fr_steering_error~%float64 fl_steering_cmd~%float64 fr_steering_cmd~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleInfo)))
  "Returns full string definition for message of type 'VehicleInfo"
  (cl:format cl:nil "Header header~%geometry_msgs/Point localization~%LongitudinalData longitudinal_data~%LateralData lateral_data~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: smartcar_msgs/LongitudinalData~%float64 vel_from_localization~%float64 vel_from_wheels~%float64 acceleration~%float64 traveled_distance~%float64 fl_wheel_angular_velocity~%float64 fr_wheel_angular_velocity~%float64 bl_wheel_angular_velocity~%float64 br_wheel_angular_velocity~%float64 gas_percent~%float64 fl_gas_torque~%float64 fr_gas_torque~%float64 bl_gas_torque~%float64 br_gas_torque~%float64 fl_brake_Torque~%float64 fr_brake_torque~%float64 bl_brake_torque~%float64 br_brake_torque~%~%================================================================================~%MSG: smartcar_msgs/LateralData~%float64 heading_angle~%float64 steering_wheel_angle_actual~%float64 steering_wheel_expected~%float64 steering_wheel_error~%float64 steering_wheel_cmd~%~%float64 fl_steering_angle_actual~%float64 fr_steering_angle_actual~%float64 single_track_steering_angle~%float64 fl_steering_angle_expected~%float64 fr_steering_angle_expected~%float64 fl_steering_error~%float64 fr_steering_error~%float64 fl_steering_cmd~%float64 fr_steering_cmd~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'localization))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'longitudinal_data))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'lateral_data))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleInfo
    (cl:cons ':header (header msg))
    (cl:cons ':localization (localization msg))
    (cl:cons ':longitudinal_data (longitudinal_data msg))
    (cl:cons ':lateral_data (lateral_data msg))
))
