// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VehicleLightCommand {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.brakelight_cmd = null;
      this.iecu_lock_cmd = null;
      this.turn_light_cmd = null;
      this.car_light_cmd = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('brakelight_cmd')) {
        this.brakelight_cmd = initObj.brakelight_cmd
      }
      else {
        this.brakelight_cmd = 0;
      }
      if (initObj.hasOwnProperty('iecu_lock_cmd')) {
        this.iecu_lock_cmd = initObj.iecu_lock_cmd
      }
      else {
        this.iecu_lock_cmd = 0;
      }
      if (initObj.hasOwnProperty('turn_light_cmd')) {
        this.turn_light_cmd = initObj.turn_light_cmd
      }
      else {
        this.turn_light_cmd = 0;
      }
      if (initObj.hasOwnProperty('car_light_cmd')) {
        this.car_light_cmd = initObj.car_light_cmd
      }
      else {
        this.car_light_cmd = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleLightCommand
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [brakelight_cmd]
    bufferOffset = _serializer.int32(obj.brakelight_cmd, buffer, bufferOffset);
    // Serialize message field [iecu_lock_cmd]
    bufferOffset = _serializer.int32(obj.iecu_lock_cmd, buffer, bufferOffset);
    // Serialize message field [turn_light_cmd]
    bufferOffset = _serializer.int32(obj.turn_light_cmd, buffer, bufferOffset);
    // Serialize message field [car_light_cmd]
    bufferOffset = _serializer.int32(obj.car_light_cmd, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleLightCommand
    let len;
    let data = new VehicleLightCommand(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [brakelight_cmd]
    data.brakelight_cmd = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [iecu_lock_cmd]
    data.iecu_lock_cmd = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [turn_light_cmd]
    data.turn_light_cmd = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [car_light_cmd]
    data.car_light_cmd = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/VehicleLightCommand';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8e2364f8ec89eb4c9476632c281aea24';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    #brakelight 
    int32 brakelight_cmd
    
    #iecu_lock,1 unlock
    int32 iecu_lock_cmd
    
    #0 mid, 1 turn left, 2 turn right
    int32 turn_light_cmd 
    
    #0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam
    int32 car_light_cmd
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VehicleLightCommand(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.brakelight_cmd !== undefined) {
      resolved.brakelight_cmd = msg.brakelight_cmd;
    }
    else {
      resolved.brakelight_cmd = 0
    }

    if (msg.iecu_lock_cmd !== undefined) {
      resolved.iecu_lock_cmd = msg.iecu_lock_cmd;
    }
    else {
      resolved.iecu_lock_cmd = 0
    }

    if (msg.turn_light_cmd !== undefined) {
      resolved.turn_light_cmd = msg.turn_light_cmd;
    }
    else {
      resolved.turn_light_cmd = 0
    }

    if (msg.car_light_cmd !== undefined) {
      resolved.car_light_cmd = msg.car_light_cmd;
    }
    else {
      resolved.car_light_cmd = 0
    }

    return resolved;
    }
};

module.exports = VehicleLightCommand;
