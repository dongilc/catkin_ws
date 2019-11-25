// Auto-generated. Do not edit!

// (in-package diff_wheel_platform.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class CTM_Message {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.target_vel = null;
      this.current_vel = null;
      this.target_pos = null;
      this.current_pos = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('target_vel')) {
        this.target_vel = initObj.target_vel
      }
      else {
        this.target_vel = [];
      }
      if (initObj.hasOwnProperty('current_vel')) {
        this.current_vel = initObj.current_vel
      }
      else {
        this.current_vel = [];
      }
      if (initObj.hasOwnProperty('target_pos')) {
        this.target_pos = initObj.target_pos
      }
      else {
        this.target_pos = [];
      }
      if (initObj.hasOwnProperty('current_pos')) {
        this.current_pos = initObj.current_pos
      }
      else {
        this.current_pos = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CTM_Message
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [target_vel]
    bufferOffset = _arraySerializer.float64(obj.target_vel, buffer, bufferOffset, null);
    // Serialize message field [current_vel]
    bufferOffset = _arraySerializer.float64(obj.current_vel, buffer, bufferOffset, null);
    // Serialize message field [target_pos]
    bufferOffset = _arraySerializer.float64(obj.target_pos, buffer, bufferOffset, null);
    // Serialize message field [current_pos]
    bufferOffset = _arraySerializer.float64(obj.current_pos, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CTM_Message
    let len;
    let data = new CTM_Message(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [target_vel]
    data.target_vel = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [current_vel]
    data.current_vel = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [target_pos]
    data.target_pos = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [current_pos]
    data.current_pos = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.target_vel.length;
    length += 8 * object.current_vel.length;
    length += 8 * object.target_pos.length;
    length += 8 * object.current_pos.length;
    return length + 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'diff_wheel_platform/CTM_Message';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ed2ad4965391603c3242af0f3ef56859';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    float64[] target_vel
    float64[] current_vel
    float64[] target_pos
    float64[] current_pos
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CTM_Message(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.target_vel !== undefined) {
      resolved.target_vel = msg.target_vel;
    }
    else {
      resolved.target_vel = []
    }

    if (msg.current_vel !== undefined) {
      resolved.current_vel = msg.current_vel;
    }
    else {
      resolved.current_vel = []
    }

    if (msg.target_pos !== undefined) {
      resolved.target_pos = msg.target_pos;
    }
    else {
      resolved.target_pos = []
    }

    if (msg.current_pos !== undefined) {
      resolved.current_pos = msg.current_pos;
    }
    else {
      resolved.current_pos = []
    }

    return resolved;
    }
};

module.exports = CTM_Message;
