// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let VehicleLightState = require('./VehicleLightState.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VehicleChassis {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.cmd_torque = null;
      this.cmd_decelaration = null;
      this.cmd_gas = null;
      this.cmd_brake = null;
      this.cmd_steerAng = null;
      this.feedback_brake_press = null;
      this.feedback_gas = null;
      this.feedback_torque = null;
      this.feedback_Motor_rotv = null;
      this.feedback_steerAng = null;
      this.feedback_tireAng = null;
      this.gas_pedal_press = null;
      this.brake_pedal_press = null;
      this.gear = null;
      this.orientation = null;
      this.linear_velocity = null;
      this.vehicleAcceleration = null;
      this.wheelspeed = null;
      this.light_state = null;
      this.vehiclespeed = null;
      this.vcu_mode = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('cmd_torque')) {
        this.cmd_torque = initObj.cmd_torque
      }
      else {
        this.cmd_torque = 0.0;
      }
      if (initObj.hasOwnProperty('cmd_decelaration')) {
        this.cmd_decelaration = initObj.cmd_decelaration
      }
      else {
        this.cmd_decelaration = 0.0;
      }
      if (initObj.hasOwnProperty('cmd_gas')) {
        this.cmd_gas = initObj.cmd_gas
      }
      else {
        this.cmd_gas = 0.0;
      }
      if (initObj.hasOwnProperty('cmd_brake')) {
        this.cmd_brake = initObj.cmd_brake
      }
      else {
        this.cmd_brake = 0.0;
      }
      if (initObj.hasOwnProperty('cmd_steerAng')) {
        this.cmd_steerAng = initObj.cmd_steerAng
      }
      else {
        this.cmd_steerAng = 0.0;
      }
      if (initObj.hasOwnProperty('feedback_brake_press')) {
        this.feedback_brake_press = initObj.feedback_brake_press
      }
      else {
        this.feedback_brake_press = 0.0;
      }
      if (initObj.hasOwnProperty('feedback_gas')) {
        this.feedback_gas = initObj.feedback_gas
      }
      else {
        this.feedback_gas = 0.0;
      }
      if (initObj.hasOwnProperty('feedback_torque')) {
        this.feedback_torque = initObj.feedback_torque
      }
      else {
        this.feedback_torque = 0.0;
      }
      if (initObj.hasOwnProperty('feedback_Motor_rotv')) {
        this.feedback_Motor_rotv = initObj.feedback_Motor_rotv
      }
      else {
        this.feedback_Motor_rotv = 0.0;
      }
      if (initObj.hasOwnProperty('feedback_steerAng')) {
        this.feedback_steerAng = initObj.feedback_steerAng
      }
      else {
        this.feedback_steerAng = 0.0;
      }
      if (initObj.hasOwnProperty('feedback_tireAng')) {
        this.feedback_tireAng = initObj.feedback_tireAng
      }
      else {
        this.feedback_tireAng = 0.0;
      }
      if (initObj.hasOwnProperty('gas_pedal_press')) {
        this.gas_pedal_press = initObj.gas_pedal_press
      }
      else {
        this.gas_pedal_press = false;
      }
      if (initObj.hasOwnProperty('brake_pedal_press')) {
        this.brake_pedal_press = initObj.brake_pedal_press
      }
      else {
        this.brake_pedal_press = false;
      }
      if (initObj.hasOwnProperty('gear')) {
        this.gear = initObj.gear
      }
      else {
        this.gear = '';
      }
      if (initObj.hasOwnProperty('orientation')) {
        this.orientation = initObj.orientation
      }
      else {
        this.orientation = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('linear_velocity')) {
        this.linear_velocity = initObj.linear_velocity
      }
      else {
        this.linear_velocity = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('vehicleAcceleration')) {
        this.vehicleAcceleration = initObj.vehicleAcceleration
      }
      else {
        this.vehicleAcceleration = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('wheelspeed')) {
        this.wheelspeed = initObj.wheelspeed
      }
      else {
        this.wheelspeed = new Array(4).fill(0);
      }
      if (initObj.hasOwnProperty('light_state')) {
        this.light_state = initObj.light_state
      }
      else {
        this.light_state = new VehicleLightState();
      }
      if (initObj.hasOwnProperty('vehiclespeed')) {
        this.vehiclespeed = initObj.vehiclespeed
      }
      else {
        this.vehiclespeed = 0.0;
      }
      if (initObj.hasOwnProperty('vcu_mode')) {
        this.vcu_mode = initObj.vcu_mode
      }
      else {
        this.vcu_mode = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleChassis
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [cmd_torque]
    bufferOffset = _serializer.float64(obj.cmd_torque, buffer, bufferOffset);
    // Serialize message field [cmd_decelaration]
    bufferOffset = _serializer.float64(obj.cmd_decelaration, buffer, bufferOffset);
    // Serialize message field [cmd_gas]
    bufferOffset = _serializer.float64(obj.cmd_gas, buffer, bufferOffset);
    // Serialize message field [cmd_brake]
    bufferOffset = _serializer.float64(obj.cmd_brake, buffer, bufferOffset);
    // Serialize message field [cmd_steerAng]
    bufferOffset = _serializer.float64(obj.cmd_steerAng, buffer, bufferOffset);
    // Serialize message field [feedback_brake_press]
    bufferOffset = _serializer.float64(obj.feedback_brake_press, buffer, bufferOffset);
    // Serialize message field [feedback_gas]
    bufferOffset = _serializer.float64(obj.feedback_gas, buffer, bufferOffset);
    // Serialize message field [feedback_torque]
    bufferOffset = _serializer.float64(obj.feedback_torque, buffer, bufferOffset);
    // Serialize message field [feedback_Motor_rotv]
    bufferOffset = _serializer.float64(obj.feedback_Motor_rotv, buffer, bufferOffset);
    // Serialize message field [feedback_steerAng]
    bufferOffset = _serializer.float64(obj.feedback_steerAng, buffer, bufferOffset);
    // Serialize message field [feedback_tireAng]
    bufferOffset = _serializer.float64(obj.feedback_tireAng, buffer, bufferOffset);
    // Serialize message field [gas_pedal_press]
    bufferOffset = _serializer.bool(obj.gas_pedal_press, buffer, bufferOffset);
    // Serialize message field [brake_pedal_press]
    bufferOffset = _serializer.bool(obj.brake_pedal_press, buffer, bufferOffset);
    // Serialize message field [gear]
    bufferOffset = _serializer.string(obj.gear, buffer, bufferOffset);
    // Check that the constant length array field [orientation] has the right length
    if (obj.orientation.length !== 3) {
      throw new Error('Unable to serialize array field orientation - length must be 3')
    }
    // Serialize message field [orientation]
    bufferOffset = _arraySerializer.float64(obj.orientation, buffer, bufferOffset, 3);
    // Check that the constant length array field [linear_velocity] has the right length
    if (obj.linear_velocity.length !== 3) {
      throw new Error('Unable to serialize array field linear_velocity - length must be 3')
    }
    // Serialize message field [linear_velocity]
    bufferOffset = _arraySerializer.float64(obj.linear_velocity, buffer, bufferOffset, 3);
    // Check that the constant length array field [vehicleAcceleration] has the right length
    if (obj.vehicleAcceleration.length !== 3) {
      throw new Error('Unable to serialize array field vehicleAcceleration - length must be 3')
    }
    // Serialize message field [vehicleAcceleration]
    bufferOffset = _arraySerializer.float64(obj.vehicleAcceleration, buffer, bufferOffset, 3);
    // Check that the constant length array field [wheelspeed] has the right length
    if (obj.wheelspeed.length !== 4) {
      throw new Error('Unable to serialize array field wheelspeed - length must be 4')
    }
    // Serialize message field [wheelspeed]
    bufferOffset = _arraySerializer.float64(obj.wheelspeed, buffer, bufferOffset, 4);
    // Serialize message field [light_state]
    bufferOffset = VehicleLightState.serialize(obj.light_state, buffer, bufferOffset);
    // Serialize message field [vehiclespeed]
    bufferOffset = _serializer.float64(obj.vehiclespeed, buffer, bufferOffset);
    // Serialize message field [vcu_mode]
    bufferOffset = _serializer.int32(obj.vcu_mode, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleChassis
    let len;
    let data = new VehicleChassis(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [cmd_torque]
    data.cmd_torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [cmd_decelaration]
    data.cmd_decelaration = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [cmd_gas]
    data.cmd_gas = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [cmd_brake]
    data.cmd_brake = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [cmd_steerAng]
    data.cmd_steerAng = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [feedback_brake_press]
    data.feedback_brake_press = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [feedback_gas]
    data.feedback_gas = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [feedback_torque]
    data.feedback_torque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [feedback_Motor_rotv]
    data.feedback_Motor_rotv = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [feedback_steerAng]
    data.feedback_steerAng = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [feedback_tireAng]
    data.feedback_tireAng = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gas_pedal_press]
    data.gas_pedal_press = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [brake_pedal_press]
    data.brake_pedal_press = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [gear]
    data.gear = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [orientation]
    data.orientation = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [linear_velocity]
    data.linear_velocity = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [vehicleAcceleration]
    data.vehicleAcceleration = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [wheelspeed]
    data.wheelspeed = _arrayDeserializer.float64(buffer, bufferOffset, 4)
    // Deserialize message field [light_state]
    data.light_state = VehicleLightState.deserialize(buffer, bufferOffset);
    // Deserialize message field [vehiclespeed]
    data.vehiclespeed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [vcu_mode]
    data.vcu_mode = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += _getByteLength(object.gear);
    length += VehicleLightState.getMessageSize(object.light_state);
    return length + 210;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/VehicleChassis';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ebba083aece22e9a5c6fc1592f401f4c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    #控制量
    float64 cmd_torque  #N·m
    float64 cmd_decelaration #m/s^2
    float64 cmd_gas 
    float64 cmd_brake
    float64 cmd_steerAng #deg
    #反馈量
    float64 feedback_brake_press  #%100
    float64 feedback_gas  #%100
    float64 feedback_torque  #N·m
    float64 feedback_Motor_rotv #round/min
    float64 feedback_steerAng #deg
    float64 feedback_tireAng #deg
    
    
    bool gas_pedal_press
    bool brake_pedal_press
    string gear
    float64[3] orientation #deg, Guass frame(deg), X-front, Y-right, Z-down pitch, roll, yaw
    float64[3] linear_velocity  #km/h, Guass frame
    float64[3] vehicleAcceleration #m/s^2 vehicle frame
    float64[4] wheelspeed #FL、FR、RL、RR km/h
    
    #EV
    smartcar_msgs/VehicleLightState light_state #EV
    #km/h
    float64 vehiclespeed 
    
    #vcu_mode, 0 manual_driving, 1 iECU , 2 remote_driving, 3 only control steer, 4 only control gas/brake
    int32 vcu_mode  
    
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
    MSG: smartcar_msgs/VehicleLightState
    Header header
    #0 mid, 1 turn left, 2 turn right
    int32 turn_light 
    
    #0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam
    int32 car_light
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VehicleChassis(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.cmd_torque !== undefined) {
      resolved.cmd_torque = msg.cmd_torque;
    }
    else {
      resolved.cmd_torque = 0.0
    }

    if (msg.cmd_decelaration !== undefined) {
      resolved.cmd_decelaration = msg.cmd_decelaration;
    }
    else {
      resolved.cmd_decelaration = 0.0
    }

    if (msg.cmd_gas !== undefined) {
      resolved.cmd_gas = msg.cmd_gas;
    }
    else {
      resolved.cmd_gas = 0.0
    }

    if (msg.cmd_brake !== undefined) {
      resolved.cmd_brake = msg.cmd_brake;
    }
    else {
      resolved.cmd_brake = 0.0
    }

    if (msg.cmd_steerAng !== undefined) {
      resolved.cmd_steerAng = msg.cmd_steerAng;
    }
    else {
      resolved.cmd_steerAng = 0.0
    }

    if (msg.feedback_brake_press !== undefined) {
      resolved.feedback_brake_press = msg.feedback_brake_press;
    }
    else {
      resolved.feedback_brake_press = 0.0
    }

    if (msg.feedback_gas !== undefined) {
      resolved.feedback_gas = msg.feedback_gas;
    }
    else {
      resolved.feedback_gas = 0.0
    }

    if (msg.feedback_torque !== undefined) {
      resolved.feedback_torque = msg.feedback_torque;
    }
    else {
      resolved.feedback_torque = 0.0
    }

    if (msg.feedback_Motor_rotv !== undefined) {
      resolved.feedback_Motor_rotv = msg.feedback_Motor_rotv;
    }
    else {
      resolved.feedback_Motor_rotv = 0.0
    }

    if (msg.feedback_steerAng !== undefined) {
      resolved.feedback_steerAng = msg.feedback_steerAng;
    }
    else {
      resolved.feedback_steerAng = 0.0
    }

    if (msg.feedback_tireAng !== undefined) {
      resolved.feedback_tireAng = msg.feedback_tireAng;
    }
    else {
      resolved.feedback_tireAng = 0.0
    }

    if (msg.gas_pedal_press !== undefined) {
      resolved.gas_pedal_press = msg.gas_pedal_press;
    }
    else {
      resolved.gas_pedal_press = false
    }

    if (msg.brake_pedal_press !== undefined) {
      resolved.brake_pedal_press = msg.brake_pedal_press;
    }
    else {
      resolved.brake_pedal_press = false
    }

    if (msg.gear !== undefined) {
      resolved.gear = msg.gear;
    }
    else {
      resolved.gear = ''
    }

    if (msg.orientation !== undefined) {
      resolved.orientation = msg.orientation;
    }
    else {
      resolved.orientation = new Array(3).fill(0)
    }

    if (msg.linear_velocity !== undefined) {
      resolved.linear_velocity = msg.linear_velocity;
    }
    else {
      resolved.linear_velocity = new Array(3).fill(0)
    }

    if (msg.vehicleAcceleration !== undefined) {
      resolved.vehicleAcceleration = msg.vehicleAcceleration;
    }
    else {
      resolved.vehicleAcceleration = new Array(3).fill(0)
    }

    if (msg.wheelspeed !== undefined) {
      resolved.wheelspeed = msg.wheelspeed;
    }
    else {
      resolved.wheelspeed = new Array(4).fill(0)
    }

    if (msg.light_state !== undefined) {
      resolved.light_state = VehicleLightState.Resolve(msg.light_state)
    }
    else {
      resolved.light_state = new VehicleLightState()
    }

    if (msg.vehiclespeed !== undefined) {
      resolved.vehiclespeed = msg.vehiclespeed;
    }
    else {
      resolved.vehiclespeed = 0.0
    }

    if (msg.vcu_mode !== undefined) {
      resolved.vcu_mode = msg.vcu_mode;
    }
    else {
      resolved.vcu_mode = 0
    }

    return resolved;
    }
};

module.exports = VehicleChassis;
