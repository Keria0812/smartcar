// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let My_Trajectory_Point = require('./My_Trajectory_Point.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class My_Trajectory {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.lane_id = null;
      this.ESTOP = null;
      this.trajectory_points = null;
      this.num = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('lane_id')) {
        this.lane_id = initObj.lane_id
      }
      else {
        this.lane_id = 0;
      }
      if (initObj.hasOwnProperty('ESTOP')) {
        this.ESTOP = initObj.ESTOP
      }
      else {
        this.ESTOP = false;
      }
      if (initObj.hasOwnProperty('trajectory_points')) {
        this.trajectory_points = initObj.trajectory_points
      }
      else {
        this.trajectory_points = [];
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
    // Serializes a message object of type My_Trajectory
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [lane_id]
    bufferOffset = _serializer.int32(obj.lane_id, buffer, bufferOffset);
    // Serialize message field [ESTOP]
    bufferOffset = _serializer.bool(obj.ESTOP, buffer, bufferOffset);
    // Serialize message field [trajectory_points]
    // Serialize the length for message field [trajectory_points]
    bufferOffset = _serializer.uint32(obj.trajectory_points.length, buffer, bufferOffset);
    obj.trajectory_points.forEach((val) => {
      bufferOffset = My_Trajectory_Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [num]
    bufferOffset = _serializer.int32(obj.num, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type My_Trajectory
    let len;
    let data = new My_Trajectory(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [lane_id]
    data.lane_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [ESTOP]
    data.ESTOP = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [trajectory_points]
    // Deserialize array length for message field [trajectory_points]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.trajectory_points = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.trajectory_points[i] = My_Trajectory_Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [num]
    data.num = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 104 * object.trajectory_points.length;
    return length + 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/My_Trajectory';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '71feceee353912c5f03c9c52a30dd4cf';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    int32 lane_id
    bool ESTOP
    My_Trajectory_Point[] trajectory_points
    int32 num
    
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
    const resolved = new My_Trajectory(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.lane_id !== undefined) {
      resolved.lane_id = msg.lane_id;
    }
    else {
      resolved.lane_id = 0
    }

    if (msg.ESTOP !== undefined) {
      resolved.ESTOP = msg.ESTOP;
    }
    else {
      resolved.ESTOP = false
    }

    if (msg.trajectory_points !== undefined) {
      resolved.trajectory_points = new Array(msg.trajectory_points.length);
      for (let i = 0; i < resolved.trajectory_points.length; ++i) {
        resolved.trajectory_points[i] = My_Trajectory_Point.Resolve(msg.trajectory_points[i]);
      }
    }
    else {
      resolved.trajectory_points = []
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

module.exports = My_Trajectory;
