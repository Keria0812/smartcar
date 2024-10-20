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

class LongitudinalData {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vel_from_localization = null;
      this.vel_from_wheels = null;
      this.acceleration = null;
      this.traveled_distance = null;
      this.fl_wheel_angular_velocity = null;
      this.fr_wheel_angular_velocity = null;
      this.bl_wheel_angular_velocity = null;
      this.br_wheel_angular_velocity = null;
      this.gas_percent = null;
      this.fl_gas_torque = null;
      this.fr_gas_torque = null;
      this.bl_gas_torque = null;
      this.br_gas_torque = null;
      this.fl_brake_Torque = null;
      this.fr_brake_torque = null;
      this.bl_brake_torque = null;
      this.br_brake_torque = null;
    }
    else {
      if (initObj.hasOwnProperty('vel_from_localization')) {
        this.vel_from_localization = initObj.vel_from_localization
      }
      else {
        this.vel_from_localization = 0.0;
      }
      if (initObj.hasOwnProperty('vel_from_wheels')) {
        this.vel_from_wheels = initObj.vel_from_wheels
      }
      else {
        this.vel_from_wheels = 0.0;
      }
      if (initObj.hasOwnProperty('acceleration')) {
        this.acceleration = initObj.acceleration
      }
      else {
        this.acceleration = 0.0;
      }
      if (initObj.hasOwnProperty('traveled_distance')) {
        this.traveled_distance = initObj.traveled_distance
      }
      else {
        this.traveled_distance = 0.0;
      }
      if (initObj.hasOwnProperty('fl_wheel_angular_velocity')) {
        this.fl_wheel_angular_velocity = initObj.fl_wheel_angular_velocity
      }
      else {
        this.fl_wheel_angular_velocity = 0.0;
      }
      if (initObj.hasOwnProperty('fr_wheel_angular_velocity')) {
        this.fr_wheel_angular_velocity = initObj.fr_wheel_angular_velocity
      }
      else {
        this.fr_wheel_angular_velocity = 0.0;
      }
      if (initObj.hasOwnProperty('bl_wheel_angular_velocity')) {
        this.bl_wheel_angular_velocity = initObj.bl_wheel_angular_velocity
      }
      else {
        this.bl_wheel_angular_velocity = 0.0;
      }
      if (initObj.hasOwnProperty('br_wheel_angular_velocity')) {
        this.br_wheel_angular_velocity = initObj.br_wheel_angular_velocity
      }
      else {
        this.br_wheel_angular_velocity = 0.0;
      }
      if (initObj.hasOwnProperty('gas_percent')) {
        this.gas_percent = initObj.gas_percent
      }
      else {
        this.gas_percent = 0.0;
      }
      if (initObj.hasOwnProperty('fl_gas_torque')) {
        this.fl_gas_torque = initObj.fl_gas_torque
      }
      else {
        this.fl_gas_torque = 0.0;
      }
      if (initObj.hasOwnProperty('fr_gas_torque')) {
        this.fr_gas_torque = initObj.fr_gas_torque
      }
      else {
        this.fr_gas_torque = 0.0;
      }
      if (initObj.hasOwnProperty('bl_gas_torque')) {
        this.bl_gas_torque = initObj.bl_gas_torque
      }
      else {
        this.bl_gas_torque = 0.0;
      }
      if (initObj.hasOwnProperty('br_gas_torque')) {
        this.br_gas_torque = initObj.br_gas_torque
      }
      else {
        this.br_gas_torque = 0.0;
      }
      if (initObj.hasOwnProperty('fl_brake_Torque')) {
        this.fl_brake_Torque = initObj.fl_brake_Torque
      }
      else {
        this.fl_brake_Torque = 0.0;
      }
      if (initObj.hasOwnProperty('fr_brake_torque')) {
        this.fr_brake_torque = initObj.fr_brake_torque
      }
      else {
        this.fr_brake_torque = 0.0;
      }
      if (initObj.hasOwnProperty('bl_brake_torque')) {
        this.bl_brake_torque = initObj.bl_brake_torque
      }
      else {
        this.bl_brake_torque = 0.0;
      }
      if (initObj.hasOwnProperty('br_brake_torque')) {
        this.br_brake_torque = initObj.br_brake_torque
      }
      else {
        this.br_brake_torque = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LongitudinalData
    // Serialize message field [vel_from_localization]
    bufferOffset = _serializer.float64(obj.vel_from_localization, buffer, bufferOffset);
    // Serialize message field [vel_from_wheels]
    bufferOffset = _serializer.float64(obj.vel_from_wheels, buffer, bufferOffset);
    // Serialize message field [acceleration]
    bufferOffset = _serializer.float64(obj.acceleration, buffer, bufferOffset);
    // Serialize message field [traveled_distance]
    bufferOffset = _serializer.float64(obj.traveled_distance, buffer, bufferOffset);
    // Serialize message field [fl_wheel_angular_velocity]
    bufferOffset = _serializer.float64(obj.fl_wheel_angular_velocity, buffer, bufferOffset);
    // Serialize message field [fr_wheel_angular_velocity]
    bufferOffset = _serializer.float64(obj.fr_wheel_angular_velocity, buffer, bufferOffset);
    // Serialize message field [bl_wheel_angular_velocity]
    bufferOffset = _serializer.float64(obj.bl_wheel_angular_velocity, buffer, bufferOffset);
    // Serialize message field [br_wheel_angular_velocity]
    bufferOffset = _serializer.float64(obj.br_wheel_angular_velocity, buffer, bufferOffset);
    // Serialize message field [gas_percent]
    bufferOffset = _serializer.float64(obj.gas_percent, buffer, bufferOffset);
    // Serialize message field [fl_gas_torque]
    bufferOffset = _serializer.float64(obj.fl_gas_torque, buffer, bufferOffset);
    // Serialize message field [fr_gas_torque]
    bufferOffset = _serializer.float64(obj.fr_gas_torque, buffer, bufferOffset);
    // Serialize message field [bl_gas_torque]
    bufferOffset = _serializer.float64(obj.bl_gas_torque, buffer, bufferOffset);
    // Serialize message field [br_gas_torque]
    bufferOffset = _serializer.float64(obj.br_gas_torque, buffer, bufferOffset);
    // Serialize message field [fl_brake_Torque]
    bufferOffset = _serializer.float64(obj.fl_brake_Torque, buffer, bufferOffset);
    // Serialize message field [fr_brake_torque]
    bufferOffset = _serializer.float64(obj.fr_brake_torque, buffer, bufferOffset);
    // Serialize message field [bl_brake_torque]
    bufferOffset = _serializer.float64(obj.bl_brake_torque, buffer, bufferOffset);
    // Serialize message field [br_brake_torque]
    bufferOffset = _serializer.float64(obj.br_brake_torque, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LongitudinalData
    let len;
    let data = new LongitudinalData(null);
    // Deserialize message field [vel_from_localization]
    data.vel_from_localization = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [vel_from_wheels]
    data.vel_from_wheels = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [acceleration]
    data.acceleration = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [traveled_distance]
    data.traveled_distance = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fl_wheel_angular_velocity]
    data.fl_wheel_angular_velocity = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fr_wheel_angular_velocity]
    data.fr_wheel_angular_velocity = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [bl_wheel_angular_velocity]
    data.bl_wheel_angular_velocity = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [br_wheel_angular_velocity]
    data.br_wheel_angular_velocity = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gas_percent]
    data.gas_percent = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fl_gas_torque]
    data.fl_gas_torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fr_gas_torque]
    data.fr_gas_torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [bl_gas_torque]
    data.bl_gas_torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [br_gas_torque]
    data.br_gas_torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fl_brake_Torque]
    data.fl_brake_Torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fr_brake_torque]
    data.fr_brake_torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [bl_brake_torque]
    data.bl_brake_torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [br_brake_torque]
    data.br_brake_torque = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 136;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/LongitudinalData';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5e1bfb472e4917d66e73052e666a6e34';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LongitudinalData(null);
    if (msg.vel_from_localization !== undefined) {
      resolved.vel_from_localization = msg.vel_from_localization;
    }
    else {
      resolved.vel_from_localization = 0.0
    }

    if (msg.vel_from_wheels !== undefined) {
      resolved.vel_from_wheels = msg.vel_from_wheels;
    }
    else {
      resolved.vel_from_wheels = 0.0
    }

    if (msg.acceleration !== undefined) {
      resolved.acceleration = msg.acceleration;
    }
    else {
      resolved.acceleration = 0.0
    }

    if (msg.traveled_distance !== undefined) {
      resolved.traveled_distance = msg.traveled_distance;
    }
    else {
      resolved.traveled_distance = 0.0
    }

    if (msg.fl_wheel_angular_velocity !== undefined) {
      resolved.fl_wheel_angular_velocity = msg.fl_wheel_angular_velocity;
    }
    else {
      resolved.fl_wheel_angular_velocity = 0.0
    }

    if (msg.fr_wheel_angular_velocity !== undefined) {
      resolved.fr_wheel_angular_velocity = msg.fr_wheel_angular_velocity;
    }
    else {
      resolved.fr_wheel_angular_velocity = 0.0
    }

    if (msg.bl_wheel_angular_velocity !== undefined) {
      resolved.bl_wheel_angular_velocity = msg.bl_wheel_angular_velocity;
    }
    else {
      resolved.bl_wheel_angular_velocity = 0.0
    }

    if (msg.br_wheel_angular_velocity !== undefined) {
      resolved.br_wheel_angular_velocity = msg.br_wheel_angular_velocity;
    }
    else {
      resolved.br_wheel_angular_velocity = 0.0
    }

    if (msg.gas_percent !== undefined) {
      resolved.gas_percent = msg.gas_percent;
    }
    else {
      resolved.gas_percent = 0.0
    }

    if (msg.fl_gas_torque !== undefined) {
      resolved.fl_gas_torque = msg.fl_gas_torque;
    }
    else {
      resolved.fl_gas_torque = 0.0
    }

    if (msg.fr_gas_torque !== undefined) {
      resolved.fr_gas_torque = msg.fr_gas_torque;
    }
    else {
      resolved.fr_gas_torque = 0.0
    }

    if (msg.bl_gas_torque !== undefined) {
      resolved.bl_gas_torque = msg.bl_gas_torque;
    }
    else {
      resolved.bl_gas_torque = 0.0
    }

    if (msg.br_gas_torque !== undefined) {
      resolved.br_gas_torque = msg.br_gas_torque;
    }
    else {
      resolved.br_gas_torque = 0.0
    }

    if (msg.fl_brake_Torque !== undefined) {
      resolved.fl_brake_Torque = msg.fl_brake_Torque;
    }
    else {
      resolved.fl_brake_Torque = 0.0
    }

    if (msg.fr_brake_torque !== undefined) {
      resolved.fr_brake_torque = msg.fr_brake_torque;
    }
    else {
      resolved.fr_brake_torque = 0.0
    }

    if (msg.bl_brake_torque !== undefined) {
      resolved.bl_brake_torque = msg.bl_brake_torque;
    }
    else {
      resolved.bl_brake_torque = 0.0
    }

    if (msg.br_brake_torque !== undefined) {
      resolved.br_brake_torque = msg.br_brake_torque;
    }
    else {
      resolved.br_brake_torque = 0.0
    }

    return resolved;
    }
};

module.exports = LongitudinalData;
