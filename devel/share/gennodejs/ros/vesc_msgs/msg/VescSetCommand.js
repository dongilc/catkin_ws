// Auto-generated. Do not edit!

// (in-package vesc_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class VescSetCommand {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.data = null;
      this.send_can = null;
      this.can_id = null;
    }
    else {
      if (initObj.hasOwnProperty('data')) {
        this.data = initObj.data
      }
      else {
        this.data = 0.0;
      }
      if (initObj.hasOwnProperty('send_can')) {
        this.send_can = initObj.send_can
      }
      else {
        this.send_can = false;
      }
      if (initObj.hasOwnProperty('can_id')) {
        this.can_id = initObj.can_id
      }
      else {
        this.can_id = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VescSetCommand
    // Serialize message field [data]
    bufferOffset = _serializer.float64(obj.data, buffer, bufferOffset);
    // Serialize message field [send_can]
    bufferOffset = _serializer.bool(obj.send_can, buffer, bufferOffset);
    // Serialize message field [can_id]
    bufferOffset = _serializer.uint8(obj.can_id, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VescSetCommand
    let len;
    let data = new VescSetCommand(null);
    // Deserialize message field [data]
    data.data = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [send_can]
    data.send_can = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [can_id]
    data.can_id = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 10;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vesc_msgs/VescSetCommand';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9cffe44297165322576d6c2378fd0593';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 data
    bool  send_can
    uint8 can_id
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VescSetCommand(null);
    if (msg.data !== undefined) {
      resolved.data = msg.data;
    }
    else {
      resolved.data = 0.0
    }

    if (msg.send_can !== undefined) {
      resolved.send_can = msg.send_can;
    }
    else {
      resolved.send_can = false
    }

    if (msg.can_id !== undefined) {
      resolved.can_id = msg.can_id;
    }
    else {
      resolved.can_id = 0
    }

    return resolved;
    }
};

module.exports = VescSetCommand;
