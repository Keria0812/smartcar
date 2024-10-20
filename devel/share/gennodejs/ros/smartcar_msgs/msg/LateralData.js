// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class LateralData {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.heading_angle = null;
      this.steering_wheel_angle_actual = null;
      this.steering_wheel_expected = null;
      this.steering_wheel_error = null;
      this.steering_wheel_cmd = null;
      this.fl_steering_angle_actual = null;
      this.fr_steering_angle_actual = null;
      this.single_track_steering_angle = null;
      this.fl_steering_angle_expected = null;
      this.fr_steering_angle_expected = null;
      this.fl_steering_error = null;
      this.fr_steering_error = null;
      this.fl_steering_cmd = null;
      this.fr_steering_cmd = null;
    }
    else {
      if (initObj.hasOwnProperty('heading_angle')) {
        this.heading_angle = initObj.heading_angle
      }
      else {
        this.heading_angle = 0.0;
      }
      if (initObj.hasOwnProperty('steering_wheel_angle_actual')) {
        this.steering_wheel_angle_actual = initObj.steering_wheel_angle_actual
      }
      else {
        this.steering_wheel_angle_actual = 0.0;
      }
      if (initObj.hasOwnProperty('steering_wheel_expected')) {
        this.steering_wheel_expected = initObj.steering_wheel_expected
      }
      else {
        this.steering_wheel_expected = 0.0;
      }
      if (initObj.hasOwnProperty('steering_wheel_error')) {
        this.steering_wheel_error = initObj.steering_wheel_error
      }
      else {
        this.steering_wheel_error = 0.0;
      }
      if (initObj.hasOwnProperty('steering_wheel_cmd')) {
        this.steering_wheel_cmd = initObj.steering_wheel_cmd
      }
      else {
        this.steering_wheel_cmd = 0.0;
      }
      if (initObj.hasOwnProperty('fl_steering_angle_actual')) {
        this.fl_steering_angle_actual = initObj.fl_steering_angle_actual
      }
      else {
        this.fl_steering_angle_actual = 0.0;
      }
      if (initObj.hasOwnProperty('fr_steering_angle_actual')) {
        this.fr_steering_angle_actual = initObj.fr_steering_angle_actual
      }
      else {
        this.fr_steering_angle_actual = 0.0;
      }
      if (initObj.hasOwnProperty('single_track_steering_angle')) {
        this.single_track_steering_angle = initObj.single_track_steering_angle
      }
      else {
        this.single_track_steering_angle = 0.0;
      }
      if (initObj.hasOwnProperty('fl_steering_angle_expected')) {
        this.fl_steering_angle_expected = initObj.fl_steering_angle_expected
      }
      else {
        this.fl_steering_angle_expected = 0.0;
      }
      if (initObj.hasOwnProperty('fr_steering_angle_expected')) {
        this.fr_steering_angle_expected = initObj.fr_steering_angle_expected
      }
      else {
        this.fr_steering_angle_expected = 0.0;
      }
      if (initObj.hasOwnProperty('fl_steering_error')) {
        this.fl_steering_error = initObj.fl_steering_error
      }
      else {
        this.fl_steering_error = 0.0;
      }
      if (initObj.hasOwnProperty('fr_steering_error')) {
        this.fr_steering_error = initObj.fr_steering_error
      }
      else {
        this.fr_steering_error = 0.0;
      }
      if (initObj.hasOwnProperty('fl_steering_cmd')) {
        this.fl_steering_cmd = initObj.fl_steering_cmd
      }
      else {
        this.fl_steering_cmd = 0.0;
      }
      if (initObj.hasOwnProperty('fr_steering_cmd')) {
        this.fr_steering_cmd = initObj.fr_steering_cmd
      }
      else {
        this.fr_steering_cmd = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LateralData
    // Serialize message field [heading_angle]
    bufferOffset = _serializer.float64(obj.heading_angle, buffer, bufferOffset);
    // Serialize message field [steering_wheel_angle_actual]
    bufferOffset = _serializer.float64(obj.steering_wheel_angle_actual, buffer, bufferOffset);
    // Serialize message field [steering_wheel_expected]
    bufferOffset = _serializer.float64(obj.steering_wheel_expected, buffer, bufferOffset);
    // Serialize message field [steering_wheel_error]
    bufferOffset = _serializer.float64(obj.steering_wheel_error, buffer, bufferOffset);
    // Serialize message field [steering_wheel_cmd]
    bufferOffset = _serializer.float64(obj.steering_wheel_cmd, buffer, bufferOffset);
    // Serialize message field [fl_steering_angle_actual]
    bufferOffset = _serializer.float64(obj.fl_steering_angle_actual, buffer, bufferOffset);
    // Serialize message field [fr_steering_angle_actual]
    bufferOffset = _serializer.float64(obj.fr_steering_angle_actual, buffer, bufferOffset);
    // Serialize message field [single_track_steering_angle]
    bufferOffset = _serializer.float64(obj.single_track_steering_angle, buffer, bufferOffset);
    // Serialize message field [fl_steering_angle_expected]
    bufferOffset = _serializer.float64(obj.fl_steering_angle_expected, buffer, bufferOffset);
    // Serialize message field [fr_steering_angle_expected]
    bufferOffset = _serializer.float64(obj.fr_steering_angle_expected, buffer, bufferOffset);
    // Serialize message field [fl_steering_error]
    bufferOffset = _serializer.float64(obj.fl_steering_error, buffer, bufferOffset);
    // Serialize message field [fr_steering_error]
    bufferOffset = _serializer.float64(obj.fr_steering_error, buffer, bufferOffset);
    // Serialize message field [fl_steering_cmd]
    bufferOffset = _serializer.float64(obj.fl_steering_cmd, buffer, bufferOffset);
    // Serialize message field [fr_steering_cmd]
    bufferOffset = _serializer.float64(obj.fr_steering_cmd, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LateralData
    let len;
    let data = new LateralData(null);
    // Deserialize message field [heading_angle]
    data.heading_angle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steering_wheel_angle_actual]
    data.steering_wheel_angle_actual = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steering_wheel_expected]
    data.steering_wheel_expected = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steering_wheel_error]
    data.steering_wheel_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steering_wheel_cmd]
    data.steering_wheel_cmd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fl_steering_angle_actual]
    data.fl_steering_angle_actual = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fr_steering_angle_actual]
    data.fr_steering_angle_actual = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [single_track_steering_angle]
    data.single_track_steering_angle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fl_steering_angle_expected]
    data.fl_steering_angle_expected = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fr_steering_angle_expected]
    data.fr_steering_angle_expected = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fl_steering_error]
    data.fl_steering_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fr_steering_error]
    data.fr_steering_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fl_steering_cmd]
    data.fl_steering_cmd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fr_steering_cmd]
    data.fr_steering_cmd = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 112;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/LateralData';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cfef9feeb4812e9c07678250076f59e3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new LateralData(null);
    if (msg.heading_angle !== undefined) {
      resolved.heading_angle = msg.heading_angle;
    }
    else {
      resolved.heading_angle = 0.0
    }

    if (msg.steering_wheel_angle_actual !== undefined) {
      resolved.steering_wheel_angle_actual = msg.steering_wheel_angle_actual;
    }
    else {
      resolved.steering_wheel_angle_actual = 0.0
    }

    if (msg.steering_wheel_expected !== undefined) {
      resolved.steering_wheel_expected = msg.steering_wheel_expected;
    }
    else {
      resolved.steering_wheel_expected = 0.0
    }

    if (msg.steering_wheel_error !== undefined) {
      resolved.steering_wheel_error = msg.steering_wheel_error;
    }
    else {
      resolved.steering_wheel_error = 0.0
    }

    if (msg.steering_wheel_cmd !== undefined) {
      resolved.steering_wheel_cmd = msg.steering_wheel_cmd;
    }
    else {
      resolved.steering_wheel_cmd = 0.0
    }

    if (msg.fl_steering_angle_actual !== undefined) {
      resolved.fl_steering_angle_actual = msg.fl_steering_angle_actual;
    }
    else {
      resolved.fl_steering_angle_actual = 0.0
    }

    if (msg.fr_steering_angle_actual !== undefined) {
      resolved.fr_steering_angle_actual = msg.fr_steering_angle_actual;
    }
    else {
      resolved.fr_steering_angle_actual = 0.0
    }

    if (msg.single_track_steering_angle !== undefined) {
      resolved.single_track_steering_angle = msg.single_track_steering_angle;
    }
    else {
      resolved.single_track_steering_angle = 0.0
    }

    if (msg.fl_steering_angle_expected !== undefined) {
      resolved.fl_steering_angle_expected = msg.fl_steering_angle_expected;
    }
    else {
      resolved.fl_steering_angle_expected = 0.0
    }

    if (msg.fr_steering_angle_expected !== undefined) {
      resolved.fr_steering_angle_expected = msg.fr_steering_angle_expected;
    }
    else {
      resolved.fr_steering_angle_expected = 0.0
    }

    if (msg.fl_steering_error !== undefined) {
      resolved.fl_steering_error = msg.fl_steering_error;
    }
    else {
      resolved.fl_steering_error = 0.0
    }

    if (msg.fr_steering_error !== undefined) {
      resolved.fr_steering_error = msg.fr_steering_error;
    }
    else {
      resolved.fr_steering_error = 0.0
    }

    if (msg.fl_steering_cmd !== undefined) {
      resolved.fl_steering_cmd = msg.fl_steering_cmd;
    }
    else {
      resolved.fl_steering_cmd = 0.0
    }

    if (msg.fr_steering_cmd !== undefined) {
      resolved.fr_steering_cmd = msg.fr_steering_cmd;
    }
    else {
      resolved.fr_steering_cmd = 0.0
    }

    return resolved;
    }
};

module.exports = LateralData;
