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

class CTM_Message {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.vel_target = null;
      this.vel_now = null;
      this.pos_target = null;
      this.pos_now = null;
      this.current = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('vel_target')) {
        this.vel_target = initObj.vel_target
      }
      else {
        this.vel_target = [];
      }
      if (initObj.hasOwnProperty('vel_now')) {
        this.vel_now = initObj.vel_now
      }
      else {
        this.vel_now = [];
      }
      if (initObj.hasOwnProperty('pos_target')) {
        this.pos_target = initObj.pos_target
      }
      else {
        this.pos_target = [];
      }
      if (initObj.hasOwnProperty('pos_now')) {
        this.pos_now = initObj.pos_now
      }
      else {
        this.pos_now = [];
      }
      if (initObj.hasOwnProperty('current')) {
        this.current = initObj.current
      }
      else {
        this.current = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CTM_Message
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [vel_target]
    bufferOffset = _arraySerializer.float64(obj.vel_target, buffer, bufferOffset, null);
    // Serialize message field [vel_now]
    bufferOffset = _arraySerializer.float64(obj.vel_now, buffer, bufferOffset, null);
    // Serialize message field [pos_target]
    bufferOffset = _arraySerializer.float64(obj.pos_target, buffer, bufferOffset, null);
    // Serialize message field [pos_now]
    bufferOffset = _arraySerializer.float64(obj.pos_now, buffer, bufferOffset, null);
    // Serialize message field [current]
    bufferOffset = _arraySerializer.float64(obj.current, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CTM_Message
    let len;
    let data = new CTM_Message(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [vel_target]
    data.vel_target = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [vel_now]
    data.vel_now = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [pos_target]
    data.pos_target = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [pos_now]
    data.pos_now = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [current]
    data.current = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.vel_target.length;
    length += 8 * object.vel_now.length;
    length += 8 * object.pos_target.length;
    length += 8 * object.pos_now.length;
    length += 8 * object.current.length;
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'amg_p1/CTM_Message';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b224801613d8b47decc0b74376cfcb04';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    float64[] vel_target
    float64[] vel_now
    float64[] pos_target
    float64[] pos_now
    float64[] current
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

    if (msg.vel_target !== undefined) {
      resolved.vel_target = msg.vel_target;
    }
    else {
      resolved.vel_target = []
    }

    if (msg.vel_now !== undefined) {
      resolved.vel_now = msg.vel_now;
    }
    else {
      resolved.vel_now = []
    }

    if (msg.pos_target !== undefined) {
      resolved.pos_target = msg.pos_target;
    }
    else {
      resolved.pos_target = []
    }

    if (msg.pos_now !== undefined) {
      resolved.pos_now = msg.pos_now;
    }
    else {
      resolved.pos_now = []
    }

    if (msg.current !== undefined) {
      resolved.current = msg.current;
    }
    else {
      resolved.current = []
    }

    return resolved;
    }
};

module.exports = CTM_Message;
