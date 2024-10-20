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

class VehicleLightState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.turn_light = null;
      this.car_light = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('turn_light')) {
        this.turn_light = initObj.turn_light
      }
      else {
        this.turn_light = 0;
      }
      if (initObj.hasOwnProperty('car_light')) {
        this.car_light = initObj.car_light
      }
      else {
        this.car_light = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleLightState
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [turn_light]
    bufferOffset = _serializer.int32(obj.turn_light, buffer, bufferOffset);
    // Serialize message field [car_light]
    bufferOffset = _serializer.int32(obj.car_light, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleLightState
    let len;
    let data = new VehicleLightState(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [turn_light]
    data.turn_light = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [car_light]
    data.car_light = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/VehicleLightState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8e22a6beadc4b37e8e1c81c5e770f4eb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    #0 mid, 1 turn left, 2 turn right
    int32 turn_light 
    
    #0 close, 1 small light, 2 dipped headlight, 3 headlights on full beam
    int32 car_light
    
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
    const resolved = new VehicleLightState(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.turn_light !== undefined) {
      resolved.turn_light = msg.turn_light;
    }
    else {
      resolved.turn_light = 0
    }

    if (msg.car_light !== undefined) {
      resolved.car_light = msg.car_light;
    }
    else {
      resolved.car_light = 0
    }

    return resolved;
    }
};

module.exports = VehicleLightState;
