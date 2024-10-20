; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude DetectedObjectArray.msg.html

(cl:defclass <DetectedObjectArray> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (objects
    :reader objects
    :initarg :objects
    :type (cl:vector smartcar_msgs-msg:DetectedObject)
   :initform (cl:make-array 0 :element-type 'smartcar_msgs-msg:DetectedObject :initial-element (cl:make-instance 'smartcar_msgs-msg:DetectedObject)))
   (num
    :reader num
    :initarg :num
    :type cl:integer
    :initform 0))
)

(cl:defclass DetectedObjectArray (<DetectedObjectArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DetectedObjectArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DetectedObjectArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<DetectedObjectArray> is deprecated: use smartcar_msgs-msg:DetectedObjectArray instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <DetectedObjectArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:header-val is deprecated.  Use smartcar_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'objects-val :lambda-list '(m))
(cl:defmethod objects-val ((m <DetectedObjectArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:objects-val is deprecated.  Use smartcar_msgs-msg:objects instead.")
  (objects m))

(cl:ensure-generic-function 'num-val :lambda-list '(m))
(cl:defmethod num-val ((m <DetectedObjectArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:num-val is deprecated.  Use smartcar_msgs-msg:num instead.")
  (num m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DetectedObjectArray>) ostream)
  "Serializes a message object of type '<DetectedObjectArray>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'objects))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'objects))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'num)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DetectedObjectArray>) istream)
  "Deserializes a message object of type '<DetectedObjectArray>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'objects) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'objects)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'smartcar_msgs-msg:DetectedObject))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'num)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DetectedObjectArray>)))
  "Returns string type for a message object of type '<DetectedObjectArray>"
  "smartcar_msgs/DetectedObjectArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectedObjectArray)))
  "Returns string type for a message object of type 'DetectedObjectArray"
  "smartcar_msgs/DetectedObjectArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DetectedObjectArray>)))
  "Returns md5sum for a message object of type '<DetectedObjectArray>"
  "c68050d331471548543425b21258f71a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DetectedObjectArray)))
  "Returns md5sum for a message object of type 'DetectedObjectArray"
  "c68050d331471548543425b21258f71a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DetectedObjectArray>)))
  "Returns full string definition for message of type '<DetectedObjectArray>"
  (cl:format cl:nil "std_msgs/Header header~%DetectedObject[] objects~%uint32 num~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/DetectedObject~%std_msgs/Header                 header~%~%string                           id      #便于后续预测轨迹赋值每个点的id, 最后的id为perception_id+trajectory_index，即id=2_12，代表id为2的障碍物的第12个轨迹点。~%string                          label~%float32                         score   #Score as defined by the detection, Optional~%std_msgs/ColorRGBA              color   # Define this object specific color~%bool                            valid   # Defines if this object is valid, or invalid as defined by the filtering~%~%################ 3D BB~%string                          space_frame #3D Space coordinate frame of the object, required if pose and dimensions are defines~%float64                         x  #car frame x-forward y-left, z-up~%float64                         y~%float64                         z~%float64                         heading~%float32                         length~%float32                         width~%float32                         height~%float32                         speed~%geometry_msgs/Point             foot_lf #车辆坐标系下，左前~%geometry_msgs/Point             foot_lr #左后~%geometry_msgs/Point             foot_rf #右前~%geometry_msgs/Point             foot_rr #右后~%~%~%float64                         utm_x  #utm frame x-forward y-left, z-up~%float64                         utm_y~%float64                         utm_z~%float64                         utm_heading~%geometry_msgs/Point             utm_foot_lf~%geometry_msgs/Point             utm_foot_lr~%geometry_msgs/Point             utm_foot_rf~%geometry_msgs/Point             utm_foot_rr~%geometry_msgs/Twist             utm_twist~%~%~%bool                            pose_reliable~%bool                            velocity_reliable~%bool                            acceleration_reliable~%~%############### Indicator information~%uint8                          indicator_state # INDICATOR_LEFT = 0, INDICATOR_RIGHT = 1, INDICATOR_BOTH = 2, INDICATOR_NONE = 3~%~%############### Behavior State of the Detected Object~%uint8                           behavior_state # FORWARD_STATE = 0, STOPPING_STATE = 1, BRANCH_LEFT_STATE = 2, BRANCH_RIGHT_STATE = 3, YIELDING_STATE = 4, ACCELERATING_STATE = 5, SLOWDOWN_STATE = 6~%~%#~%string[]                        user_defined_info~%bool is_static~%~%My_Trajectory trajectory_  #预测轨迹~%================================================================================~%MSG: std_msgs/ColorRGBA~%float32 r~%float32 g~%float32 b~%float32 a~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: smartcar_msgs/My_Trajectory~%Header header~%int32 lane_id~%bool ESTOP~%My_Trajectory_Point[] trajectory_points~%int32 num~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory_Point~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%float64 l~%float64 dkappa~%float64 ddkappa~%float64 v~%float64 a~%float64 relative_time~%float64 gear~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DetectedObjectArray)))
  "Returns full string definition for message of type 'DetectedObjectArray"
  (cl:format cl:nil "std_msgs/Header header~%DetectedObject[] objects~%uint32 num~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/DetectedObject~%std_msgs/Header                 header~%~%string                           id      #便于后续预测轨迹赋值每个点的id, 最后的id为perception_id+trajectory_index，即id=2_12，代表id为2的障碍物的第12个轨迹点。~%string                          label~%float32                         score   #Score as defined by the detection, Optional~%std_msgs/ColorRGBA              color   # Define this object specific color~%bool                            valid   # Defines if this object is valid, or invalid as defined by the filtering~%~%################ 3D BB~%string                          space_frame #3D Space coordinate frame of the object, required if pose and dimensions are defines~%float64                         x  #car frame x-forward y-left, z-up~%float64                         y~%float64                         z~%float64                         heading~%float32                         length~%float32                         width~%float32                         height~%float32                         speed~%geometry_msgs/Point             foot_lf #车辆坐标系下，左前~%geometry_msgs/Point             foot_lr #左后~%geometry_msgs/Point             foot_rf #右前~%geometry_msgs/Point             foot_rr #右后~%~%~%float64                         utm_x  #utm frame x-forward y-left, z-up~%float64                         utm_y~%float64                         utm_z~%float64                         utm_heading~%geometry_msgs/Point             utm_foot_lf~%geometry_msgs/Point             utm_foot_lr~%geometry_msgs/Point             utm_foot_rf~%geometry_msgs/Point             utm_foot_rr~%geometry_msgs/Twist             utm_twist~%~%~%bool                            pose_reliable~%bool                            velocity_reliable~%bool                            acceleration_reliable~%~%############### Indicator information~%uint8                          indicator_state # INDICATOR_LEFT = 0, INDICATOR_RIGHT = 1, INDICATOR_BOTH = 2, INDICATOR_NONE = 3~%~%############### Behavior State of the Detected Object~%uint8                           behavior_state # FORWARD_STATE = 0, STOPPING_STATE = 1, BRANCH_LEFT_STATE = 2, BRANCH_RIGHT_STATE = 3, YIELDING_STATE = 4, ACCELERATING_STATE = 5, SLOWDOWN_STATE = 6~%~%#~%string[]                        user_defined_info~%bool is_static~%~%My_Trajectory trajectory_  #预测轨迹~%================================================================================~%MSG: std_msgs/ColorRGBA~%float32 r~%float32 g~%float32 b~%float32 a~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: smartcar_msgs/My_Trajectory~%Header header~%int32 lane_id~%bool ESTOP~%My_Trajectory_Point[] trajectory_points~%int32 num~%~%================================================================================~%MSG: smartcar_msgs/My_Trajectory_Point~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%float64 l~%float64 dkappa~%float64 ddkappa~%float64 v~%float64 a~%float64 relative_time~%float64 gear~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DetectedObjectArray>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'objects) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DetectedObjectArray>))
  "Converts a ROS message object to a list"
  (cl:list 'DetectedObjectArray
    (cl:cons ':header (header msg))
    (cl:cons ':objects (objects msg))
    (cl:cons ':num (num msg))
))
