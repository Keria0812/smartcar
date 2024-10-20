// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let LongitudinalData = require('./LongitudinalData.js');
let LateralData = require('./LateralData.js');
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VehicleInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.localization = null;
      this.longitudinal_data = null;
      this.lateral_data = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('localization')) {
        this.localization = initObj.localization
      }
      else {
        this.localization = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('longitudinal_data')) {
        this.longitudinal_data = initObj.longitudinal_data
      }
      else {
        this.longitudinal_data = new LongitudinalData();
      }
      if (initObj.hasOwnProperty('lateral_data')) {
        this.lateral_data = initObj.lateral_data
      }
      else {
        this.lateral_data = new LateralData();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [localization]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.localization, buffer, bufferOffset);
    // Serialize message field [longitudinal_data]
    bufferOffset = LongitudinalData.serialize(obj.longitudinal_data, buffer, bufferOffset);
    // Serialize message field [lateral_data]
    bufferOffset = LateralData.serialize(obj.lateral_data, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleInfo
    let len;
    let data = new VehicleInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [localization]
    data.localization = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [longitudinal_data]
    data.longitudinal_data = LongitudinalData.deserialize(buffer, bufferOffset);
    // Deserialize message field [lateral_data]
    data.lateral_data = LateralData.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 272;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/VehicleInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ce1548f612651099d85d928f1bef6a2e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    geometry_msgs/Point localization
    LongitudinalData longitudinal_data
    LateralData lateral_data
    
    
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
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    ================================================================================
    MSG: smartcar_msgs/LongitudinalData
    float64 vel_from_localization
    float64 vel_from_wheels
    float64 acceleration
    float64 traveled_distance
    float64 fl_wheel_angular_velocity
    float64 fr_wheel_angular_velocity
    float64 bl_wheel_angular_velocity
    float64 br_wheel_angular_velocity
    float64 gas_percent
    float64 fl_gas_torque
    float64 fr_gas_torque
    float64 bl_gas_torque
    float64 br_gas_torque
    float64 fl_brake_Torque
    float64 fr_brake_torque
    float64 bl_brake_torque
    float64 br_brake_torque
    
    ================================================================================
    MSG: smartcar_msgs/LateralData
    float64 heading_angle
    float64 steering_wheel_angle_actual
    float64 steering_wheel_expected
    float64 steering_wheel_error
    float64 steering_wheel_cmd
    
    float64 fl_steering_angle_actual
    float64 fr_steering_angle_actual
    float64 single_track_steering_angle
    float64 fl_steering_angle_expected
    float64 fr_steering_angle_expected
    float64 fl_steering_error
    float64 fr_steering_error
    float64 fl_steering_cmd
    float64 fr_steering_cmd
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VehicleInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.localization !== undefined) {
      resolved.localization = geometry_msgs.msg.Point.Resolve(msg.localization)
    }
    else {
      resolved.localization = new geometry_msgs.msg.Point()
    }

    if (msg.longitudinal_data !== undefined) {
      resolved.longitudinal_data = LongitudinalData.Resolve(msg.longitudinal_data)
    }
    else {
      resolved.longitudinal_data = new LongitudinalData()
    }

    if (msg.lateral_data !== undefined) {
      resolved.lateral_data = LateralData.Resolve(msg.lateral_data)
    }
    else {
      resolved.lateral_data = new LateralData()
    }

    return resolved;
    }
};

module.exports = VehicleInfo;
