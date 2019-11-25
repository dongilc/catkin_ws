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

class LA_Message {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.deg_total_target = null;
      this.deg_total_now = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('deg_total_target')) {
        this.deg_total_target = initObj.deg_total_target
      }
      else {
        this.deg_total_target = [];
      }
      if (initObj.hasOwnProperty('deg_total_now')) {
        this.deg_total_now = initObj.deg_total_now
      }
      else {
        this.deg_total_now = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LA_Message
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [deg_total_target]
    bufferOffset = _arraySerializer.float64(obj.deg_total_target, buffer, bufferOffset, null);
    // Serialize message field [deg_total_now]
    bufferOffset = _arraySerializer.float64(obj.deg_total_now, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LA_Message
    let len;
    let data = new LA_Message(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [deg_total_target]
    data.deg_total_target = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [deg_total_now]
    data.deg_total_now = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.deg_total_target.length;
    length += 8 * object.deg_total_now.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'amg_p1/LA_Message';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7905fa336d4f2fe4db8c49c8192c0986';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    
    float64[] deg_total_target
    float64[] deg_total_now
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LA_Message(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.deg_total_target !== undefined) {
      resolved.deg_total_target = msg.deg_total_target;
    }
    else {
      resolved.deg_total_target = []
    }

    if (msg.deg_total_now !== undefined) {
      resolved.deg_total_now = msg.deg_total_now;
    }
    else {
      resolved.deg_total_now = []
    }

    return resolved;
    }
};

module.exports = LA_Message;
