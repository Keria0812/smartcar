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
let VehicleInfo = require('./VehicleInfo.js');

//-----------------------------------------------------------

class Augmented_My_Trajectory_Point {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.trajectory_point = null;
      this.vehicle_info = null;
      this.goal_id = null;
      this.preview_id = null;
      this.lateral_distance_error = null;
      this.max_lateral_distance_error = null;
      this.average_lateral_distance_error = null;
      this.velocity_error = null;
      this.max_velocity_error = null;
      this.average_velocity_error = null;
      this.heading_error = null;
      this.max_heading_error = null;
      this.average_heading_error = null;
      this.computational_time = null;
      this.average_computational_time = null;
      this.max_computational_time = null;
      this.slope = null;
    }
    else {
      if (initObj.hasOwnProperty('trajectory_point')) {
        this.trajectory_point = initObj.trajectory_point
      }
      else {
        this.trajectory_point = new My_Trajectory_Point();
      }
      if (initObj.hasOwnProperty('vehicle_info')) {
        this.vehicle_info = initObj.vehicle_info
      }
      else {
        this.vehicle_info = new VehicleInfo();
      }
      if (initObj.hasOwnProperty('goal_id')) {
        this.goal_id = initObj.goal_id
      }
      else {
        this.goal_id = 0.0;
      }
      if (initObj.hasOwnProperty('preview_id')) {
        this.preview_id = initObj.preview_id
      }
      else {
        this.preview_id = 0.0;
      }
      if (initObj.hasOwnProperty('lateral_distance_error')) {
        this.lateral_distance_error = initObj.lateral_distance_error
      }
      else {
        this.lateral_distance_error = 0.0;
      }
      if (initObj.hasOwnProperty('max_lateral_distance_error')) {
        this.max_lateral_distance_error = initObj.max_lateral_distance_error
      }
      else {
        this.max_lateral_distance_error = 0.0;
      }
      if (initObj.hasOwnProperty('average_lateral_distance_error')) {
        this.average_lateral_distance_error = initObj.average_lateral_distance_error
      }
      else {
        this.average_lateral_distance_error = 0.0;
      }
      if (initObj.hasOwnProperty('velocity_error')) {
        this.velocity_error = initObj.velocity_error
      }
      else {
        this.velocity_error = 0.0;
      }
      if (initObj.hasOwnProperty('max_velocity_error')) {
        this.max_velocity_error = initObj.max_velocity_error
      }
      else {
        this.max_velocity_error = 0.0;
      }
      if (initObj.hasOwnProperty('average_velocity_error')) {
        this.average_velocity_error = initObj.average_velocity_error
      }
      else {
        this.average_velocity_error = 0.0;
      }
      if (initObj.hasOwnProperty('heading_error')) {
        this.heading_error = initObj.heading_error
      }
      else {
        this.heading_error = 0.0;
      }
      if (initObj.hasOwnProperty('max_heading_error')) {
        this.max_heading_error = initObj.max_heading_error
      }
      else {
        this.max_heading_error = 0.0;
      }
      if (initObj.hasOwnProperty('average_heading_error')) {
        this.average_heading_error = initObj.average_heading_error
      }
      else {
        this.average_heading_error = 0.0;
      }
      if (initObj.hasOwnProperty('computational_time')) {
        this.computational_time = initObj.computational_time
      }
      else {
        this.computational_time = 0.0;
      }
      if (initObj.hasOwnProperty('average_computational_time')) {
        this.average_computational_time = initObj.average_computational_time
      }
      else {
        this.average_computational_time = 0.0;
      }
      if (initObj.hasOwnProperty('max_computational_time')) {
        this.max_computational_time = initObj.max_computational_time
      }
      else {
        this.max_computational_time = 0.0;
      }
      if (initObj.hasOwnProperty('slope')) {
        this.slope = initObj.slope
      }
      else {
        this.slope = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Augmented_My_Trajectory_Point
    // Serialize message field [trajectory_point]
    bufferOffset = My_Trajectory_Point.serialize(obj.trajectory_point, buffer, bufferOffset);
    // Serialize message field [vehicle_info]
    bufferOffset = VehicleInfo.serialize(obj.vehicle_info, buffer, bufferOffset);
    // Serialize message field [goal_id]
    bufferOffset = _serializer.float64(obj.goal_id, buffer, bufferOffset);
    // Serialize message field [preview_id]
    bufferOffset = _serializer.float64(obj.preview_id, buffer, bufferOffset);
    // Serialize message field [lateral_distance_error]
    bufferOffset = _serializer.float64(obj.lateral_distance_error, buffer, bufferOffset);
    // Serialize message field [max_lateral_distance_error]
    bufferOffset = _serializer.float64(obj.max_lateral_distance_error, buffer, bufferOffset);
    // Serialize message field [average_lateral_distance_error]
    bufferOffset = _serializer.float64(obj.average_lateral_distance_error, buffer, bufferOffset);
    // Serialize message field [velocity_error]
    bufferOffset = _serializer.float64(obj.velocity_error, buffer, bufferOffset);
    // Serialize message field [max_velocity_error]
    bufferOffset = _serializer.float64(obj.max_velocity_error, buffer, bufferOffset);
    // Serialize message field [average_velocity_error]
    bufferOffset = _serializer.float64(obj.average_velocity_error, buffer, bufferOffset);
    // Serialize message field [heading_error]
    bufferOffset = _serializer.float64(obj.heading_error, buffer, bufferOffset);
    // Serialize message field [max_heading_error]
    bufferOffset = _serializer.float64(obj.max_heading_error, buffer, bufferOffset);
    // Serialize message field [average_heading_error]
    bufferOffset = _serializer.float64(obj.average_heading_error, buffer, bufferOffset);
    // Serialize message field [computational_time]
    bufferOffset = _serializer.float64(obj.computational_time, buffer, bufferOffset);
    // Serialize message field [average_computational_time]
    bufferOffset = _serializer.float64(obj.average_computational_time, buffer, bufferOffset);
    // Serialize message field [max_computational_time]
    bufferOffset = _serializer.float64(obj.max_computational_time, buffer, bufferOffset);
    // Serialize message field [slope]
    bufferOffset = _serializer.float64(obj.slope, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Augmented_My_Trajectory_Point
    let len;
    let data = new Augmented_My_Trajectory_Point(null);
    // Deserialize message field [trajectory_point]
    data.trajectory_point = My_Trajectory_Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [vehicle_info]
    data.vehicle_info = VehicleInfo.deserialize(buffer, bufferOffset);
    // Deserialize message field [goal_id]
    data.goal_id = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [preview_id]
    data.preview_id = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [lateral_distance_error]
    data.lateral_distance_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_lateral_distance_error]
    data.max_lateral_distance_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [average_lateral_distance_error]
    data.average_lateral_distance_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velocity_error]
    data.velocity_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_velocity_error]
    data.max_velocity_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [average_velocity_error]
    data.average_velocity_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [heading_error]
    data.heading_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_heading_error]
    data.max_heading_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [average_heading_error]
    data.average_heading_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [computational_time]
    data.computational_time = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [average_computational_time]
    data.average_computational_time = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_computational_time]
    data.max_computational_time = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [slope]
    data.slope = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += VehicleInfo.getMessageSize(object.vehicle_info);
    return length + 224;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/Augmented_My_Trajectory_Point';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7730dde01d7004063a0f1a42c12ce23e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    My_Trajectory_Point trajectory_point
    VehicleInfo vehicle_info
    float64 goal_id
    float64 preview_id
    float64 lateral_distance_error
    float64 max_lateral_distance_error
    float64 average_lateral_distance_error
    float64 velocity_error
    float64 max_velocity_error
    float64 average_velocity_error
    float64 heading_error
    float64 max_heading_error
    float64 average_heading_error
    float64 computational_time
    float64 average_computational_time
    float64 max_computational_time
    float64 slope
    
    
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
    
    ================================================================================
    MSG: smartcar_msgs/VehicleInfo
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
    const resolved = new Augmented_My_Trajectory_Point(null);
    if (msg.trajectory_point !== undefined) {
      resolved.trajectory_point = My_Trajectory_Point.Resolve(msg.trajectory_point)
    }
    else {
      resolved.trajectory_point = new My_Trajectory_Point()
    }

    if (msg.vehicle_info !== undefined) {
      resolved.vehicle_info = VehicleInfo.Resolve(msg.vehicle_info)
    }
    else {
      resolved.vehicle_info = new VehicleInfo()
    }

    if (msg.goal_id !== undefined) {
      resolved.goal_id = msg.goal_id;
    }
    else {
      resolved.goal_id = 0.0
    }

    if (msg.preview_id !== undefined) {
      resolved.preview_id = msg.preview_id;
    }
    else {
      resolved.preview_id = 0.0
    }

    if (msg.lateral_distance_error !== undefined) {
      resolved.lateral_distance_error = msg.lateral_distance_error;
    }
    else {
      resolved.lateral_distance_error = 0.0
    }

    if (msg.max_lateral_distance_error !== undefined) {
      resolved.max_lateral_distance_error = msg.max_lateral_distance_error;
    }
    else {
      resolved.max_lateral_distance_error = 0.0
    }

    if (msg.average_lateral_distance_error !== undefined) {
      resolved.average_lateral_distance_error = msg.average_lateral_distance_error;
    }
    else {
      resolved.average_lateral_distance_error = 0.0
    }

    if (msg.velocity_error !== undefined) {
      resolved.velocity_error = msg.velocity_error;
    }
    else {
      resolved.velocity_error = 0.0
    }

    if (msg.max_velocity_error !== undefined) {
      resolved.max_velocity_error = msg.max_velocity_error;
    }
    else {
      resolved.max_velocity_error = 0.0
    }

    if (msg.average_velocity_error !== undefined) {
      resolved.average_velocity_error = msg.average_velocity_error;
    }
    else {
      resolved.average_velocity_error = 0.0
    }

    if (msg.heading_error !== undefined) {
      resolved.heading_error = msg.heading_error;
    }
    else {
      resolved.heading_error = 0.0
    }

    if (msg.max_heading_error !== undefined) {
      resolved.max_heading_error = msg.max_heading_error;
    }
    else {
      resolved.max_heading_error = 0.0
    }

    if (msg.average_heading_error !== undefined) {
      resolved.average_heading_error = msg.average_heading_error;
    }
    else {
      resolved.average_heading_error = 0.0
    }

    if (msg.computational_time !== undefined) {
      resolved.computational_time = msg.computational_time;
    }
    else {
      resolved.computational_time = 0.0
    }

    if (msg.average_computational_time !== undefined) {
      resolved.average_computational_time = msg.average_computational_time;
    }
    else {
      resolved.average_computational_time = 0.0
    }

    if (msg.max_computational_time !== undefined) {
      resolved.max_computational_time = msg.max_computational_time;
    }
    else {
      resolved.max_computational_time = 0.0
    }

    if (msg.slope !== undefined) {
      resolved.slope = msg.slope;
    }
    else {
      resolved.slope = 0.0
    }

    return resolved;
    }
};

module.exports = Augmented_My_Trajectory_Point;
