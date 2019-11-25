// Auto-generated. Do not edit!

// (in-package amg_p1.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class MP_Message {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.x = null;
      this.th = null;
      this.x_input = null;
      this.vel_out = null;
      this.theta_out = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = [];
      }
      if (initObj.hasOwnProperty('th')) {
        this.th = initObj.th
      }
      else {
        this.th = [];
      }
      if (initObj.hasOwnProperty('x_input')) {
        this.x_input = initObj.x_input
      }
      else {
        this.x_input = [];
      }
      if (initObj.hasOwnProperty('vel_out')) {
        this.vel_out = initObj.vel_out
      }
      else {
        this.vel_out = 0.0;
      }
      if (initObj.hasOwnProperty('theta_out')) {
        this.theta_out = initObj.theta_out
      }
      else {
        this.theta_out = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MP_Message
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _arraySerializer.float64(obj.x, buffer, bufferOffset, null);
    // Serialize message field [th]
    bufferOffset = _arraySerializer.float64(obj.th, buffer, bufferOffset, null);
    // Serialize message field [x_input]
    bufferOffset = _arraySerializer.float64(obj.x_input, buffer, bufferOffset, null);
    // Serialize message field [vel_out]
    bufferOffset = _serializer.float64(obj.vel_out, buffer, bufferOffset);
    // Serialize message field [theta_out]
    bufferOffset = _serializer.float64(obj.theta_out, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MP_Message
    let len;
    let data = new MP_Message(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [th]
    data.th = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [x_input]
    data.x_input = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [vel_out]
    data.vel_out = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [theta_out]
    data.theta_out = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.x.length;
    length += 8 * object.th.length;
    length += 8 * object.x_input.length;
    return length + 36;
  }

  static datatype() {
    // Returns string type for a message object
    return 'amg_p1/MP_Message';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '79bb341ec382fab4793fae5691c7faf8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    float64[] x
    float64[] th
    float64[] x_input
    
    float64 vel_out
    float64 theta_out
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MP_Message(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = []
    }

    if (msg.th !== undefined) {
      resolved.th = msg.th;
    }
    else {
      resolved.th = []
    }

    if (msg.x_input !== undefined) {
      resolved.x_input = msg.x_input;
    }
    else {
      resolved.x_input = []
    }

    if (msg.vel_out !== undefined) {
      resolved.vel_out = msg.vel_out;
    }
    else {
      resolved.vel_out = 0.0
    }

    if (msg.theta_out !== undefined) {
      resolved.theta_out = msg.theta_out;
    }
    else {
      resolved.theta_out = 0.0
    }

    return resolved;
    }
};

module.exports = MP_Message;
