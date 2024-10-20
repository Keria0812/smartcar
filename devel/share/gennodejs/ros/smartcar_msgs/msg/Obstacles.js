// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let ObstacleAttr = require('./ObstacleAttr.js');

//-----------------------------------------------------------

class Obstacles {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Obstacles = null;
    }
    else {
      if (initObj.hasOwnProperty('Obstacles')) {
        this.Obstacles = initObj.Obstacles
      }
      else {
        this.Obstacles = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Obstacles
    // Serialize message field [Obstacles]
    // Serialize the length for message field [Obstacles]
    bufferOffset = _serializer.uint32(obj.Obstacles.length, buffer, bufferOffset);
    obj.Obstacles.forEach((val) => {
      bufferOffset = ObstacleAttr.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Obstacles
    let len;
    let data = new Obstacles(null);
    // Deserialize message field [Obstacles]
    // Deserialize array length for message field [Obstacles]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.Obstacles = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.Obstacles[i] = ObstacleAttr.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 65 * object.Obstacles.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/Obstacles';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '42f94931bc3e97baf969e4dc42dad246';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
     ObstacleAttr[] Obstacles
    ================================================================================
    MSG: smartcar_msgs/ObstacleAttr
    int8 id
    float64 x
    float64 y
    float64 z
    float64 length
    float64 width
    float64 height
    float64 heading
    float64 speed
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Obstacles(null);
    if (msg.Obstacles !== undefined) {
      resolved.Obstacles = new Array(msg.Obstacles.length);
      for (let i = 0; i < resolved.Obstacles.length; ++i) {
        resolved.Obstacles[i] = ObstacleAttr.Resolve(msg.Obstacles[i]);
      }
    }
    else {
      resolved.Obstacles = []
    }

    return resolved;
    }
};

module.exports = Obstacles;
