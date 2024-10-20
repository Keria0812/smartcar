// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let DetectedObject = require('./DetectedObject.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class DetectedObjectArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.objects = null;
      this.num = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('objects')) {
        this.objects = initObj.objects
      }
      else {
        this.objects = [];
      }
      if (initObj.hasOwnProperty('num')) {
        this.num = initObj.num
      }
      else {
        this.num = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DetectedObjectArray
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [objects]
    // Serialize the length for message field [objects]
    bufferOffset = _serializer.uint32(obj.objects.length, buffer, bufferOffset);
    obj.objects.forEach((val) => {
      bufferOffset = DetectedObject.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [num]
    bufferOffset = _serializer.uint32(obj.num, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DetectedObjectArray
    let len;
    let data = new DetectedObjectArray(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [objects]
    // Deserialize array length for message field [objects]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.objects = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.objects[i] = DetectedObject.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [num]
    data.num = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.objects.forEach((val) => {
      length += DetectedObject.getMessageSize(val);
    });
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/DetectedObjectArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c68050d331471548543425b21258f71a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    DetectedObject[] objects
    uint32 num
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
    MSG: smartcar_msgs/DetectedObject
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
    const resolved = new DetectedObjectArray(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.objects !== undefined) {
      resolved.objects = new Array(msg.objects.length);
      for (let i = 0; i < resolved.objects.length; ++i) {
        resolved.objects[i] = DetectedObject.Resolve(msg.objects[i]);
      }
    }
    else {
      resolved.objects = []
    }

    if (msg.num !== undefined) {
      resolved.num = msg.num;
    }
    else {
      resolved.num = 0
    }

    return resolved;
    }
};

module.exports = DetectedObjectArray;
