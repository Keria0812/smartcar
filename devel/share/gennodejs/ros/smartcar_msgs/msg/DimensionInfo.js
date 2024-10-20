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

class DimensionInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.wheel_base = null;
      this.front_wheel_base = null;
      this.rear_wheel_base = null;
      this.track = null;
      this.mass = null;
      this.front_cornering_stiffness = null;
      this.rear_cornering_stiffness = null;
      this.max_friction_coefficient = null;
      this.Iz = null;
    }
    else {
      if (initObj.hasOwnProperty('wheel_base')) {
        this.wheel_base = initObj.wheel_base
      }
      else {
        this.wheel_base = 0.0;
      }
      if (initObj.hasOwnProperty('front_wheel_base')) {
        this.front_wheel_base = initObj.front_wheel_base
      }
      else {
        this.front_wheel_base = 0.0;
      }
      if (initObj.hasOwnProperty('rear_wheel_base')) {
        this.rear_wheel_base = initObj.rear_wheel_base
      }
      else {
        this.rear_wheel_base = 0.0;
      }
      if (initObj.hasOwnProperty('track')) {
        this.track = initObj.track
      }
      else {
        this.track = 0.0;
      }
      if (initObj.hasOwnProperty('mass')) {
        this.mass = initObj.mass
      }
      else {
        this.mass = 0.0;
      }
      if (initObj.hasOwnProperty('front_cornering_stiffness')) {
        this.front_cornering_stiffness = initObj.front_cornering_stiffness
      }
      else {
        this.front_cornering_stiffness = 0.0;
      }
      if (initObj.hasOwnProperty('rear_cornering_stiffness')) {
        this.rear_cornering_stiffness = initObj.rear_cornering_stiffness
      }
      else {
        this.rear_cornering_stiffness = 0.0;
      }
      if (initObj.hasOwnProperty('max_friction_coefficient')) {
        this.max_friction_coefficient = initObj.max_friction_coefficient
      }
      else {
        this.max_friction_coefficient = 0.0;
      }
      if (initObj.hasOwnProperty('Iz')) {
        this.Iz = initObj.Iz
      }
      else {
        this.Iz = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DimensionInfo
    // Serialize message field [wheel_base]
    bufferOffset = _serializer.float64(obj.wheel_base, buffer, bufferOffset);
    // Serialize message field [front_wheel_base]
    bufferOffset = _serializer.float64(obj.front_wheel_base, buffer, bufferOffset);
    // Serialize message field [rear_wheel_base]
    bufferOffset = _serializer.float64(obj.rear_wheel_base, buffer, bufferOffset);
    // Serialize message field [track]
    bufferOffset = _serializer.float64(obj.track, buffer, bufferOffset);
    // Serialize message field [mass]
    bufferOffset = _serializer.float64(obj.mass, buffer, bufferOffset);
    // Serialize message field [front_cornering_stiffness]
    bufferOffset = _serializer.float64(obj.front_cornering_stiffness, buffer, bufferOffset);
    // Serialize message field [rear_cornering_stiffness]
    bufferOffset = _serializer.float64(obj.rear_cornering_stiffness, buffer, bufferOffset);
    // Serialize message field [max_friction_coefficient]
    bufferOffset = _serializer.float64(obj.max_friction_coefficient, buffer, bufferOffset);
    // Serialize message field [Iz]
    bufferOffset = _serializer.float64(obj.Iz, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DimensionInfo
    let len;
    let data = new DimensionInfo(null);
    // Deserialize message field [wheel_base]
    data.wheel_base = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [front_wheel_base]
    data.front_wheel_base = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rear_wheel_base]
    data.rear_wheel_base = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [track]
    data.track = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [mass]
    data.mass = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [front_cornering_stiffness]
    data.front_cornering_stiffness = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rear_cornering_stiffness]
    data.rear_cornering_stiffness = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_friction_coefficient]
    data.max_friction_coefficient = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [Iz]
    data.Iz = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 72;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/DimensionInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '83b23d28199a7ca222af4ff1d8a32e6b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 wheel_base
    float64 front_wheel_base
    float64 rear_wheel_base
    float64 track
    float64 mass
    float64 front_cornering_stiffness
    float64 rear_cornering_stiffness
    float64 max_friction_coefficient
    float64 Iz
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DimensionInfo(null);
    if (msg.wheel_base !== undefined) {
      resolved.wheel_base = msg.wheel_base;
    }
    else {
      resolved.wheel_base = 0.0
    }

    if (msg.front_wheel_base !== undefined) {
      resolved.front_wheel_base = msg.front_wheel_base;
    }
    else {
      resolved.front_wheel_base = 0.0
    }

    if (msg.rear_wheel_base !== undefined) {
      resolved.rear_wheel_base = msg.rear_wheel_base;
    }
    else {
      resolved.rear_wheel_base = 0.0
    }

    if (msg.track !== undefined) {
      resolved.track = msg.track;
    }
    else {
      resolved.track = 0.0
    }

    if (msg.mass !== undefined) {
      resolved.mass = msg.mass;
    }
    else {
      resolved.mass = 0.0
    }

    if (msg.front_cornering_stiffness !== undefined) {
      resolved.front_cornering_stiffness = msg.front_cornering_stiffness;
    }
    else {
      resolved.front_cornering_stiffness = 0.0
    }

    if (msg.rear_cornering_stiffness !== undefined) {
      resolved.rear_cornering_stiffness = msg.rear_cornering_stiffness;
    }
    else {
      resolved.rear_cornering_stiffness = 0.0
    }

    if (msg.max_friction_coefficient !== undefined) {
      resolved.max_friction_coefficient = msg.max_friction_coefficient;
    }
    else {
      resolved.max_friction_coefficient = 0.0
    }

    if (msg.Iz !== undefined) {
      resolved.Iz = msg.Iz;
    }
    else {
      resolved.Iz = 0.0
    }

    return resolved;
    }
};

module.exports = DimensionInfo;
