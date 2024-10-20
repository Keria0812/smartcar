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
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class Location {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.ins_time = null;
      this.global_pos = null;
      this.wgs84_pos = null;
      this.global_speed = null;
      this.accelerate = null;
      this.orientation = null;
      this.rpy_rate = null;
      this.speed = null;
      this.v_x = null;
      this.v_y = null;
      this.v_z = null;
      this.accel_x = null;
      this.accel_y = null;
      this.accel_z = null;
      this.ins_std_error = null;
      this.ins_data_info = null;
      this.INS_status = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('ins_time')) {
        this.ins_time = initObj.ins_time
      }
      else {
        this.ins_time = new Array(2).fill(0);
      }
      if (initObj.hasOwnProperty('global_pos')) {
        this.global_pos = initObj.global_pos
      }
      else {
        this.global_pos = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('wgs84_pos')) {
        this.wgs84_pos = initObj.wgs84_pos
      }
      else {
        this.wgs84_pos = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('global_speed')) {
        this.global_speed = initObj.global_speed
      }
      else {
        this.global_speed = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('accelerate')) {
        this.accelerate = initObj.accelerate
      }
      else {
        this.accelerate = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('orientation')) {
        this.orientation = initObj.orientation
      }
      else {
        this.orientation = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('rpy_rate')) {
        this.rpy_rate = initObj.rpy_rate
      }
      else {
        this.rpy_rate = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0.0;
      }
      if (initObj.hasOwnProperty('v_x')) {
        this.v_x = initObj.v_x
      }
      else {
        this.v_x = 0.0;
      }
      if (initObj.hasOwnProperty('v_y')) {
        this.v_y = initObj.v_y
      }
      else {
        this.v_y = 0.0;
      }
      if (initObj.hasOwnProperty('v_z')) {
        this.v_z = initObj.v_z
      }
      else {
        this.v_z = 0.0;
      }
      if (initObj.hasOwnProperty('accel_x')) {
        this.accel_x = initObj.accel_x
      }
      else {
        this.accel_x = 0.0;
      }
      if (initObj.hasOwnProperty('accel_y')) {
        this.accel_y = initObj.accel_y
      }
      else {
        this.accel_y = 0.0;
      }
      if (initObj.hasOwnProperty('accel_z')) {
        this.accel_z = initObj.accel_z
      }
      else {
        this.accel_z = 0.0;
      }
      if (initObj.hasOwnProperty('ins_std_error')) {
        this.ins_std_error = initObj.ins_std_error
      }
      else {
        this.ins_std_error = new Array(4).fill(0);
      }
      if (initObj.hasOwnProperty('ins_data_info')) {
        this.ins_data_info = initObj.ins_data_info
      }
      else {
        this.ins_data_info = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('INS_status')) {
        this.INS_status = initObj.INS_status
      }
      else {
        this.INS_status = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Location
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Check that the constant length array field [ins_time] has the right length
    if (obj.ins_time.length !== 2) {
      throw new Error('Unable to serialize array field ins_time - length must be 2')
    }
    // Serialize message field [ins_time]
    bufferOffset = _arraySerializer.int32(obj.ins_time, buffer, bufferOffset, 2);
    // Serialize message field [global_pos]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.global_pos, buffer, bufferOffset);
    // Check that the constant length array field [wgs84_pos] has the right length
    if (obj.wgs84_pos.length !== 3) {
      throw new Error('Unable to serialize array field wgs84_pos - length must be 3')
    }
    // Serialize message field [wgs84_pos]
    bufferOffset = _arraySerializer.float64(obj.wgs84_pos, buffer, bufferOffset, 3);
    // Check that the constant length array field [global_speed] has the right length
    if (obj.global_speed.length !== 3) {
      throw new Error('Unable to serialize array field global_speed - length must be 3')
    }
    // Serialize message field [global_speed]
    bufferOffset = _arraySerializer.float32(obj.global_speed, buffer, bufferOffset, 3);
    // Check that the constant length array field [accelerate] has the right length
    if (obj.accelerate.length !== 3) {
      throw new Error('Unable to serialize array field accelerate - length must be 3')
    }
    // Serialize message field [accelerate]
    bufferOffset = _arraySerializer.float32(obj.accelerate, buffer, bufferOffset, 3);
    // Check that the constant length array field [orientation] has the right length
    if (obj.orientation.length !== 3) {
      throw new Error('Unable to serialize array field orientation - length must be 3')
    }
    // Serialize message field [orientation]
    bufferOffset = _arraySerializer.float32(obj.orientation, buffer, bufferOffset, 3);
    // Check that the constant length array field [rpy_rate] has the right length
    if (obj.rpy_rate.length !== 3) {
      throw new Error('Unable to serialize array field rpy_rate - length must be 3')
    }
    // Serialize message field [rpy_rate]
    bufferOffset = _arraySerializer.float32(obj.rpy_rate, buffer, bufferOffset, 3);
    // Serialize message field [speed]
    bufferOffset = _serializer.float64(obj.speed, buffer, bufferOffset);
    // Serialize message field [v_x]
    bufferOffset = _serializer.float64(obj.v_x, buffer, bufferOffset);
    // Serialize message field [v_y]
    bufferOffset = _serializer.float64(obj.v_y, buffer, bufferOffset);
    // Serialize message field [v_z]
    bufferOffset = _serializer.float64(obj.v_z, buffer, bufferOffset);
    // Serialize message field [accel_x]
    bufferOffset = _serializer.float64(obj.accel_x, buffer, bufferOffset);
    // Serialize message field [accel_y]
    bufferOffset = _serializer.float64(obj.accel_y, buffer, bufferOffset);
    // Serialize message field [accel_z]
    bufferOffset = _serializer.float64(obj.accel_z, buffer, bufferOffset);
    // Check that the constant length array field [ins_std_error] has the right length
    if (obj.ins_std_error.length !== 4) {
      throw new Error('Unable to serialize array field ins_std_error - length must be 4')
    }
    // Serialize message field [ins_std_error]
    bufferOffset = _arraySerializer.float32(obj.ins_std_error, buffer, bufferOffset, 4);
    // Check that the constant length array field [ins_data_info] has the right length
    if (obj.ins_data_info.length !== 3) {
      throw new Error('Unable to serialize array field ins_data_info - length must be 3')
    }
    // Serialize message field [ins_data_info]
    bufferOffset = _arraySerializer.int32(obj.ins_data_info, buffer, bufferOffset, 3);
    // Serialize message field [INS_status]
    bufferOffset = _serializer.string(obj.INS_status, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Location
    let len;
    let data = new Location(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [ins_time]
    data.ins_time = _arrayDeserializer.int32(buffer, bufferOffset, 2)
    // Deserialize message field [global_pos]
    data.global_pos = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [wgs84_pos]
    data.wgs84_pos = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [global_speed]
    data.global_speed = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [accelerate]
    data.accelerate = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [orientation]
    data.orientation = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [rpy_rate]
    data.rpy_rate = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [speed]
    data.speed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [v_x]
    data.v_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [v_y]
    data.v_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [v_z]
    data.v_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [accel_x]
    data.accel_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [accel_y]
    data.accel_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [accel_z]
    data.accel_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ins_std_error]
    data.ins_std_error = _arrayDeserializer.float32(buffer, bufferOffset, 4)
    // Deserialize message field [ins_data_info]
    data.ins_data_info = _arrayDeserializer.int32(buffer, bufferOffset, 3)
    // Deserialize message field [INS_status]
    data.INS_status = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += _getByteLength(object.INS_status);
    return length + 192;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/Location';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '00db5d5e3e65b48b95b9219165f53168';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header	   header # ROS time(s)
    
    int32[2]   ins_time # GPS weeks, GPS million seconds
    geometry_msgs/Point global_pos # x,y, east-north-sky frame(m)
    float64[3] wgs84_pos # lon,lat,alt, WGS84(rad,rad,m)
    float32[3] global_speed # east_speed,north_speed,up_speed,east-north-sky frame(m/s)
    float32[3] accelerate # /* m/s^2, utm坐标系 */
    float32[3] orientation # roll,pitch,yaw, Vehicle/Guass frame(rad,rad,rad)
    float32[3] rpy_rate # roll_rate, pitch_rate, yaw_rate, Vehicle frame(rad/s)
    float64    speed # 总的速度
    float64    v_x # base_link坐标系
    float64    v_y
    float64    v_z
    float64 accel_x # base_link坐标系
    float64 accel_y 
    float64 accel_z 
    
    float32[4] ins_std_error # std_lat, std_lon, std_height, std_heading
    int32[3]   ins_data_info # ins_num_satellite, gps_delay , wheel_speed
    string     INS_status # 0_NONE_,  16_SINGLE_, 17_PSRDIFF_ , 34_NARROW_FLOAT_, 50_NARROW_INT_
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Location(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.ins_time !== undefined) {
      resolved.ins_time = msg.ins_time;
    }
    else {
      resolved.ins_time = new Array(2).fill(0)
    }

    if (msg.global_pos !== undefined) {
      resolved.global_pos = geometry_msgs.msg.Point.Resolve(msg.global_pos)
    }
    else {
      resolved.global_pos = new geometry_msgs.msg.Point()
    }

    if (msg.wgs84_pos !== undefined) {
      resolved.wgs84_pos = msg.wgs84_pos;
    }
    else {
      resolved.wgs84_pos = new Array(3).fill(0)
    }

    if (msg.global_speed !== undefined) {
      resolved.global_speed = msg.global_speed;
    }
    else {
      resolved.global_speed = new Array(3).fill(0)
    }

    if (msg.accelerate !== undefined) {
      resolved.accelerate = msg.accelerate;
    }
    else {
      resolved.accelerate = new Array(3).fill(0)
    }

    if (msg.orientation !== undefined) {
      resolved.orientation = msg.orientation;
    }
    else {
      resolved.orientation = new Array(3).fill(0)
    }

    if (msg.rpy_rate !== undefined) {
      resolved.rpy_rate = msg.rpy_rate;
    }
    else {
      resolved.rpy_rate = new Array(3).fill(0)
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0.0
    }

    if (msg.v_x !== undefined) {
      resolved.v_x = msg.v_x;
    }
    else {
      resolved.v_x = 0.0
    }

    if (msg.v_y !== undefined) {
      resolved.v_y = msg.v_y;
    }
    else {
      resolved.v_y = 0.0
    }

    if (msg.v_z !== undefined) {
      resolved.v_z = msg.v_z;
    }
    else {
      resolved.v_z = 0.0
    }

    if (msg.accel_x !== undefined) {
      resolved.accel_x = msg.accel_x;
    }
    else {
      resolved.accel_x = 0.0
    }

    if (msg.accel_y !== undefined) {
      resolved.accel_y = msg.accel_y;
    }
    else {
      resolved.accel_y = 0.0
    }

    if (msg.accel_z !== undefined) {
      resolved.accel_z = msg.accel_z;
    }
    else {
      resolved.accel_z = 0.0
    }

    if (msg.ins_std_error !== undefined) {
      resolved.ins_std_error = msg.ins_std_error;
    }
    else {
      resolved.ins_std_error = new Array(4).fill(0)
    }

    if (msg.ins_data_info !== undefined) {
      resolved.ins_data_info = msg.ins_data_info;
    }
    else {
      resolved.ins_data_info = new Array(3).fill(0)
    }

    if (msg.INS_status !== undefined) {
      resolved.INS_status = msg.INS_status;
    }
    else {
      resolved.INS_status = ''
    }

    return resolved;
    }
};

module.exports = Location;
