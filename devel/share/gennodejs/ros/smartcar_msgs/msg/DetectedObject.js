// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let My_Trajectory = require('./My_Trajectory.js');
let std_msgs = _finder('std_msgs');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class DetectedObject {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.id = null;
      this.label = null;
      this.score = null;
      this.color = null;
      this.valid = null;
      this.space_frame = null;
      this.x = null;
      this.y = null;
      this.z = null;
      this.heading = null;
      this.length = null;
      this.width = null;
      this.height = null;
      this.speed = null;
      this.foot_lf = null;
      this.foot_lr = null;
      this.foot_rf = null;
      this.foot_rr = null;
      this.utm_x = null;
      this.utm_y = null;
      this.utm_z = null;
      this.utm_heading = null;
      this.utm_foot_lf = null;
      this.utm_foot_lr = null;
      this.utm_foot_rf = null;
      this.utm_foot_rr = null;
      this.utm_twist = null;
      this.pose_reliable = null;
      this.velocity_reliable = null;
      this.acceleration_reliable = null;
      this.indicator_state = null;
      this.behavior_state = null;
      this.user_defined_info = null;
      this.is_static = null;
      this.trajectory_ = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = '';
      }
      if (initObj.hasOwnProperty('label')) {
        this.label = initObj.label
      }
      else {
        this.label = '';
      }
      if (initObj.hasOwnProperty('score')) {
        this.score = initObj.score
      }
      else {
        this.score = 0.0;
      }
      if (initObj.hasOwnProperty('color')) {
        this.color = initObj.color
      }
      else {
        this.color = new std_msgs.msg.ColorRGBA();
      }
      if (initObj.hasOwnProperty('valid')) {
        this.valid = initObj.valid
      }
      else {
        this.valid = false;
      }
      if (initObj.hasOwnProperty('space_frame')) {
        this.space_frame = initObj.space_frame
      }
      else {
        this.space_frame = '';
      }
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = 0.0;
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = 0.0;
      }
      if (initObj.hasOwnProperty('z')) {
        this.z = initObj.z
      }
      else {
        this.z = 0.0;
      }
      if (initObj.hasOwnProperty('heading')) {
        this.heading = initObj.heading
      }
      else {
        this.heading = 0.0;
      }
      if (initObj.hasOwnProperty('length')) {
        this.length = initObj.length
      }
      else {
        this.length = 0.0;
      }
      if (initObj.hasOwnProperty('width')) {
        this.width = initObj.width
      }
      else {
        this.width = 0.0;
      }
      if (initObj.hasOwnProperty('height')) {
        this.height = initObj.height
      }
      else {
        this.height = 0.0;
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0.0;
      }
      if (initObj.hasOwnProperty('foot_lf')) {
        this.foot_lf = initObj.foot_lf
      }
      else {
        this.foot_lf = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('foot_lr')) {
        this.foot_lr = initObj.foot_lr
      }
      else {
        this.foot_lr = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('foot_rf')) {
        this.foot_rf = initObj.foot_rf
      }
      else {
        this.foot_rf = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('foot_rr')) {
        this.foot_rr = initObj.foot_rr
      }
      else {
        this.foot_rr = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('utm_x')) {
        this.utm_x = initObj.utm_x
      }
      else {
        this.utm_x = 0.0;
      }
      if (initObj.hasOwnProperty('utm_y')) {
        this.utm_y = initObj.utm_y
      }
      else {
        this.utm_y = 0.0;
      }
      if (initObj.hasOwnProperty('utm_z')) {
        this.utm_z = initObj.utm_z
      }
      else {
        this.utm_z = 0.0;
      }
      if (initObj.hasOwnProperty('utm_heading')) {
        this.utm_heading = initObj.utm_heading
      }
      else {
        this.utm_heading = 0.0;
      }
      if (initObj.hasOwnProperty('utm_foot_lf')) {
        this.utm_foot_lf = initObj.utm_foot_lf
      }
      else {
        this.utm_foot_lf = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('utm_foot_lr')) {
        this.utm_foot_lr = initObj.utm_foot_lr
      }
      else {
        this.utm_foot_lr = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('utm_foot_rf')) {
        this.utm_foot_rf = initObj.utm_foot_rf
      }
      else {
        this.utm_foot_rf = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('utm_foot_rr')) {
        this.utm_foot_rr = initObj.utm_foot_rr
      }
      else {
        this.utm_foot_rr = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('utm_twist')) {
        this.utm_twist = initObj.utm_twist
      }
      else {
        this.utm_twist = new geometry_msgs.msg.Twist();
      }
      if (initObj.hasOwnProperty('pose_reliable')) {
        this.pose_reliable = initObj.pose_reliable
      }
      else {
        this.pose_reliable = false;
      }
      if (initObj.hasOwnProperty('velocity_reliable')) {
        this.velocity_reliable = initObj.velocity_reliable
      }
      else {
        this.velocity_reliable = false;
      }
      if (initObj.hasOwnProperty('acceleration_reliable')) {
        this.acceleration_reliable = initObj.acceleration_reliable
      }
      else {
        this.acceleration_reliable = false;
      }
      if (initObj.hasOwnProperty('indicator_state')) {
        this.indicator_state = initObj.indicator_state
      }
      else {
        this.indicator_state = 0;
      }
      if (initObj.hasOwnProperty('behavior_state')) {
        this.behavior_state = initObj.behavior_state
      }
      else {
        this.behavior_state = 0;
      }
      if (initObj.hasOwnProperty('user_defined_info')) {
        this.user_defined_info = initObj.user_defined_info
      }
      else {
        this.user_defined_info = [];
      }
      if (initObj.hasOwnProperty('is_static')) {
        this.is_static = initObj.is_static
      }
      else {
        this.is_static = false;
      }
      if (initObj.hasOwnProperty('trajectory_')) {
        this.trajectory_ = initObj.trajectory_
      }
      else {
        this.trajectory_ = new My_Trajectory();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DetectedObject
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [id]
    bufferOffset = _serializer.string(obj.id, buffer, bufferOffset);
    // Serialize message field [label]
    bufferOffset = _serializer.string(obj.label, buffer, bufferOffset);
    // Serialize message field [score]
    bufferOffset = _serializer.float32(obj.score, buffer, bufferOffset);
    // Serialize message field [color]
    bufferOffset = std_msgs.msg.ColorRGBA.serialize(obj.color, buffer, bufferOffset);
    // Serialize message field [valid]
    bufferOffset = _serializer.bool(obj.valid, buffer, bufferOffset);
    // Serialize message field [space_frame]
    bufferOffset = _serializer.string(obj.space_frame, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _serializer.float64(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float64(obj.y, buffer, bufferOffset);
    // Serialize message field [z]
    bufferOffset = _serializer.float64(obj.z, buffer, bufferOffset);
    // Serialize message field [heading]
    bufferOffset = _serializer.float64(obj.heading, buffer, bufferOffset);
    // Serialize message field [length]
    bufferOffset = _serializer.float32(obj.length, buffer, bufferOffset);
    // Serialize message field [width]
    bufferOffset = _serializer.float32(obj.width, buffer, bufferOffset);
    // Serialize message field [height]
    bufferOffset = _serializer.float32(obj.height, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float32(obj.speed, buffer, bufferOffset);
    // Serialize message field [foot_lf]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.foot_lf, buffer, bufferOffset);
    // Serialize message field [foot_lr]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.foot_lr, buffer, bufferOffset);
    // Serialize message field [foot_rf]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.foot_rf, buffer, bufferOffset);
    // Serialize message field [foot_rr]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.foot_rr, buffer, bufferOffset);
    // Serialize message field [utm_x]
    bufferOffset = _serializer.float64(obj.utm_x, buffer, bufferOffset);
    // Serialize message field [utm_y]
    bufferOffset = _serializer.float64(obj.utm_y, buffer, bufferOffset);
    // Serialize message field [utm_z]
    bufferOffset = _serializer.float64(obj.utm_z, buffer, bufferOffset);
    // Serialize message field [utm_heading]
    bufferOffset = _serializer.float64(obj.utm_heading, buffer, bufferOffset);
    // Serialize message field [utm_foot_lf]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.utm_foot_lf, buffer, bufferOffset);
    // Serialize message field [utm_foot_lr]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.utm_foot_lr, buffer, bufferOffset);
    // Serialize message field [utm_foot_rf]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.utm_foot_rf, buffer, bufferOffset);
    // Serialize message field [utm_foot_rr]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.utm_foot_rr, buffer, bufferOffset);
    // Serialize message field [utm_twist]
    bufferOffset = geometry_msgs.msg.Twist.serialize(obj.utm_twist, buffer, bufferOffset);
    // Serialize message field [pose_reliable]
    bufferOffset = _serializer.bool(obj.pose_reliable, buffer, bufferOffset);
    // Serialize message field [velocity_reliable]
    bufferOffset = _serializer.bool(obj.velocity_reliable, buffer, bufferOffset);
    // Serialize message field [acceleration_reliable]
    bufferOffset = _serializer.bool(obj.acceleration_reliable, buffer, bufferOffset);
    // Serialize message field [indicator_state]
    bufferOffset = _serializer.uint8(obj.indicator_state, buffer, bufferOffset);
    // Serialize message field [behavior_state]
    bufferOffset = _serializer.uint8(obj.behavior_state, buffer, bufferOffset);
    // Serialize message field [user_defined_info]
    bufferOffset = _arraySerializer.string(obj.user_defined_info, buffer, bufferOffset, null);
    // Serialize message field [is_static]
    bufferOffset = _serializer.bool(obj.is_static, buffer, bufferOffset);
    // Serialize message field [trajectory_]
    bufferOffset = My_Trajectory.serialize(obj.trajectory_, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DetectedObject
    let len;
    let data = new DetectedObject(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [id]
    data.id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [label]
    data.label = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [score]
    data.score = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [color]
    data.color = std_msgs.msg.ColorRGBA.deserialize(buffer, bufferOffset);
    // Deserialize message field [valid]
    data.valid = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [space_frame]
    data.space_frame = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [z]
    data.z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [heading]
    data.heading = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [length]
    data.length = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [width]
    data.width = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [height]
    data.height = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [foot_lf]
    data.foot_lf = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [foot_lr]
    data.foot_lr = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [foot_rf]
    data.foot_rf = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [foot_rr]
    data.foot_rr = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [utm_x]
    data.utm_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [utm_y]
    data.utm_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [utm_z]
    data.utm_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [utm_heading]
    data.utm_heading = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [utm_foot_lf]
    data.utm_foot_lf = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [utm_foot_lr]
    data.utm_foot_lr = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [utm_foot_rf]
    data.utm_foot_rf = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [utm_foot_rr]
    data.utm_foot_rr = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [utm_twist]
    data.utm_twist = geometry_msgs.msg.Twist.deserialize(buffer, bufferOffset);
    // Deserialize message field [pose_reliable]
    data.pose_reliable = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [velocity_reliable]
    data.velocity_reliable = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [acceleration_reliable]
    data.acceleration_reliable = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [indicator_state]
    data.indicator_state = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [behavior_state]
    data.behavior_state = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [user_defined_info]
    data.user_defined_info = _arrayDeserializer.string(buffer, bufferOffset, null)
    // Deserialize message field [is_static]
    data.is_static = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [trajectory_]
    data.trajectory_ = My_Trajectory.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += _getByteLength(object.id);
    length += _getByteLength(object.label);
    length += _getByteLength(object.space_frame);
    object.user_defined_info.forEach((val) => {
      length += 4 + _getByteLength(val);
    });
    length += My_Trajectory.getMessageSize(object.trajectory_);
    return length + 363;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/DetectedObject';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8263e8ba2bd27309693c5d19983a7eff';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header                 header
    
    string                           id      #便于后续预测轨迹赋值每个点的id, 最后的id为perception_id+trajectory_index，即id=2_12，代表id为2的障碍物的第12个轨迹点。
    string                          label
    float32                         score   #Score as defined by the detection, Optional
    std_msgs/ColorRGBA              color   # Define this object specific color
    bool                            valid   # Defines if this object is valid, or invalid as defined by the filtering
    
    ################ 3D BB
    string                          space_frame #3D Space coordinate frame of the object, required if pose and dimensions are defines
    float64                         x  #car frame x-forward y-left, z-up
    float64                         y
    float64                         z
    float64                         heading
    float32                         length
    float32                         width
    float32                         height
    float32                         speed
    geometry_msgs/Point             foot_lf #车辆坐标系下，左前
    geometry_msgs/Point             foot_lr #左后
    geometry_msgs/Point             foot_rf #右前
    geometry_msgs/Point             foot_rr #右后
    
    
    float64                         utm_x  #utm frame x-forward y-left, z-up
    float64                         utm_y
    float64                         utm_z
    float64                         utm_heading
    geometry_msgs/Point             utm_foot_lf
    geometry_msgs/Point             utm_foot_lr
    geometry_msgs/Point             utm_foot_rf
    geometry_msgs/Point             utm_foot_rr
    geometry_msgs/Twist             utm_twist
    
    
    bool                            pose_reliable
    bool                            velocity_reliable
    bool                            acceleration_reliable
    
    ############### Indicator information
    uint8                          indicator_state # INDICATOR_LEFT = 0, INDICATOR_RIGHT = 1, INDICATOR_BOTH = 2, INDICATOR_NONE = 3
    
    ############### Behavior State of the Detected Object
    uint8                           behavior_state # FORWARD_STATE = 0, STOPPING_STATE = 1, BRANCH_LEFT_STATE = 2, BRANCH_RIGHT_STATE = 3, YIELDING_STATE = 4, ACCELERATING_STATE = 5, SLOWDOWN_STATE = 6
    
    #
    string[]                        user_defined_info
    bool is_static
    
    My_Trajectory trajectory_  #预测轨迹
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: std_msgs/ColorRGBA
    float32 r
    float32 g
    float32 b
    float32 a
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    ================================================================================
    MSG: geometry_msgs/Twist
    # This expresses velocity in free space broken into its linear and angular parts.
    Vector3  linear
    Vector3  angular
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    ================================================================================
    MSG: smartcar_msgs/My_Trajectory
    Header header
    int32 lane_id
    bool ESTOP
    My_Trajectory_Point[] trajectory_points
    int32 num
    
    ================================================================================
    MSG: smartcar_msgs/My_Trajectory_Point
    float64 x
    float64 y
    float64 z
    float64 theta
    float64 kappa
    float64 s
    float64 l
    float64 dkappa
    float64 ddkappa
    float64 v
    float64 a
    float64 relative_time
    float64 gear
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DetectedObject(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = ''
    }

    if (msg.label !== undefined) {
      resolved.label = msg.label;
    }
    else {
      resolved.label = ''
    }

    if (msg.score !== undefined) {
      resolved.score = msg.score;
    }
    else {
      resolved.score = 0.0
    }

    if (msg.color !== undefined) {
      resolved.color = std_msgs.msg.ColorRGBA.Resolve(msg.color)
    }
    else {
      resolved.color = new std_msgs.msg.ColorRGBA()
    }

    if (msg.valid !== undefined) {
      resolved.valid = msg.valid;
    }
    else {
      resolved.valid = false
    }

    if (msg.space_frame !== undefined) {
      resolved.space_frame = msg.space_frame;
    }
    else {
      resolved.space_frame = ''
    }

    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = 0.0
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = 0.0
    }

    if (msg.z !== undefined) {
      resolved.z = msg.z;
    }
    else {
      resolved.z = 0.0
    }

    if (msg.heading !== undefined) {
      resolved.heading = msg.heading;
    }
    else {
      resolved.heading = 0.0
    }

    if (msg.length !== undefined) {
      resolved.length = msg.length;
    }
    else {
      resolved.length = 0.0
    }

    if (msg.width !== undefined) {
      resolved.width = msg.width;
    }
    else {
      resolved.width = 0.0
    }

    if (msg.height !== undefined) {
      resolved.height = msg.height;
    }
    else {
      resolved.height = 0.0
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0.0
    }

    if (msg.foot_lf !== undefined) {
      resolved.foot_lf = geometry_msgs.msg.Point.Resolve(msg.foot_lf)
    }
    else {
      resolved.foot_lf = new geometry_msgs.msg.Point()
    }

    if (msg.foot_lr !== undefined) {
      resolved.foot_lr = geometry_msgs.msg.Point.Resolve(msg.foot_lr)
    }
    else {
      resolved.foot_lr = new geometry_msgs.msg.Point()
    }

    if (msg.foot_rf !== undefined) {
      resolved.foot_rf = geometry_msgs.msg.Point.Resolve(msg.foot_rf)
    }
    else {
      resolved.foot_rf = new geometry_msgs.msg.Point()
    }

    if (msg.foot_rr !== undefined) {
      resolved.foot_rr = geometry_msgs.msg.Point.Resolve(msg.foot_rr)
    }
    else {
      resolved.foot_rr = new geometry_msgs.msg.Point()
    }

    if (msg.utm_x !== undefined) {
      resolved.utm_x = msg.utm_x;
    }
    else {
      resolved.utm_x = 0.0
    }

    if (msg.utm_y !== undefined) {
      resolved.utm_y = msg.utm_y;
    }
    else {
      resolved.utm_y = 0.0
    }

    if (msg.utm_z !== undefined) {
      resolved.utm_z = msg.utm_z;
    }
    else {
      resolved.utm_z = 0.0
    }

    if (msg.utm_heading !== undefined) {
      resolved.utm_heading = msg.utm_heading;
    }
    else {
      resolved.utm_heading = 0.0
    }

    if (msg.utm_foot_lf !== undefined) {
      resolved.utm_foot_lf = geometry_msgs.msg.Point.Resolve(msg.utm_foot_lf)
    }
    else {
      resolved.utm_foot_lf = new geometry_msgs.msg.Point()
    }

    if (msg.utm_foot_lr !== undefined) {
      resolved.utm_foot_lr = geometry_msgs.msg.Point.Resolve(msg.utm_foot_lr)
    }
    else {
      resolved.utm_foot_lr = new geometry_msgs.msg.Point()
    }

    if (msg.utm_foot_rf !== undefined) {
      resolved.utm_foot_rf = geometry_msgs.msg.Point.Resolve(msg.utm_foot_rf)
    }
    else {
      resolved.utm_foot_rf = new geometry_msgs.msg.Point()
    }

    if (msg.utm_foot_rr !== undefined) {
      resolved.utm_foot_rr = geometry_msgs.msg.Point.Resolve(msg.utm_foot_rr)
    }
    else {
      resolved.utm_foot_rr = new geometry_msgs.msg.Point()
    }

    if (msg.utm_twist !== undefined) {
      resolved.utm_twist = geometry_msgs.msg.Twist.Resolve(msg.utm_twist)
    }
    else {
      resolved.utm_twist = new geometry_msgs.msg.Twist()
    }

    if (msg.pose_reliable !== undefined) {
      resolved.pose_reliable = msg.pose_reliable;
    }
    else {
      resolved.pose_reliable = false
    }

    if (msg.velocity_reliable !== undefined) {
      resolved.velocity_reliable = msg.velocity_reliable;
    }
    else {
      resolved.velocity_reliable = false
    }

    if (msg.acceleration_reliable !== undefined) {
      resolved.acceleration_reliable = msg.acceleration_reliable;
    }
    else {
      resolved.acceleration_reliable = false
    }

    if (msg.indicator_state !== undefined) {
      resolved.indicator_state = msg.indicator_state;
    }
    else {
      resolved.indicator_state = 0
    }

    if (msg.behavior_state !== undefined) {
      resolved.behavior_state = msg.behavior_state;
    }
    else {
      resolved.behavior_state = 0
    }

    if (msg.user_defined_info !== undefined) {
      resolved.user_defined_info = msg.user_defined_info;
    }
    else {
      resolved.user_defined_info = []
    }

    if (msg.is_static !== undefined) {
      resolved.is_static = msg.is_static;
    }
    else {
      resolved.is_static = false
    }

    if (msg.trajectory_ !== undefined) {
      resolved.trajectory_ = My_Trajectory.Resolve(msg.trajectory_)
    }
    else {
      resolved.trajectory_ = new My_Trajectory()
    }

    return resolved;
    }
};

module.exports = DetectedObject;
