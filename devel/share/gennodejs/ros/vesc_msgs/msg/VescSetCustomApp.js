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

class VescSetCustomApp {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.num_of_id = null;
      this.id_set = null;
      this.comm_set = null;
      this.can_forward_set = null;
      this.value_set = null;
      this.data_bytes = null;
    }
    else {
      if (initObj.hasOwnProperty('num_of_id')) {
        this.num_of_id = initObj.num_of_id
      }
      else {
        this.num_of_id = 0;
      }
      if (initObj.hasOwnProperty('id_set')) {
        this.id_set = initObj.id_set
      }
      else {
        this.id_set = [];
      }
      if (initObj.hasOwnProperty('comm_set')) {
        this.comm_set = initObj.comm_set
      }
      else {
        this.comm_set = [];
      }
      if (initObj.hasOwnProperty('can_forward_set')) {
        this.can_forward_set = initObj.can_forward_set
      }
      else {
        this.can_forward_set = [];
      }
      if (initObj.hasOwnProperty('value_set')) {
        this.value_set = initObj.value_set
      }
      else {
        this.value_set = [];
      }
      if (initObj.hasOwnProperty('data_bytes')) {
        this.data_bytes = initObj.data_bytes
      }
      else {
        this.data_bytes = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VescSetCustomApp
    // Serialize message field [num_of_id]
    bufferOffset = _serializer.int32(obj.num_of_id, buffer, bufferOffset);
    // Serialize message field [id_set]
    bufferOffset = _arraySerializer.int32(obj.id_set, buffer, bufferOffset, null);
    // Serialize message field [comm_set]
    bufferOffset = _arraySerializer.int32(obj.comm_set, buffer, bufferOffset, null);
    // Serialize message field [can_forward_set]
    bufferOffset = _arraySerializer.bool(obj.can_forward_set, buffer, bufferOffset, null);
    // Serialize message field [value_set]
    bufferOffset = _arraySerializer.float64(obj.value_set, buffer, bufferOffset, null);
    // Serialize message field [data_bytes]
    bufferOffset = _serializer.int32(obj.data_bytes, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VescSetCustomApp
    let len;
    let data = new VescSetCustomApp(null);
    // Deserialize message field [num_of_id]
    data.num_of_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [id_set]
    data.id_set = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [comm_set]
    data.comm_set = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [can_forward_set]
    data.can_forward_set = _arrayDeserializer.bool(buffer, bufferOffset, null)
    // Deserialize message field [value_set]
    data.value_set = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [data_bytes]
    data.data_bytes = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.id_set.length;
    length += 4 * object.comm_set.length;
    length += object.can_forward_set.length;
    length += 8 * object.value_set.length;
    return length + 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vesc_msgs/VescSetCustomApp';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c46f4ff65abd5670780793173869e6b9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # VESCuino CDI CUSTOM_APP TX Messages
    
    int32       num_of_id
    int32[]     id_set
    int32[]     comm_set
    bool[]      can_forward_set
    float64[]   value_set
    int32       data_bytes
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VescSetCustomApp(null);
    if (msg.num_of_id !== undefined) {
      resolved.num_of_id = msg.num_of_id;
    }
    else {
      resolved.num_of_id = 0
    }

    if (msg.id_set !== undefined) {
      resolved.id_set = msg.id_set;
    }
    else {
      resolved.id_set = []
    }

    if (msg.comm_set !== undefined) {
      resolved.comm_set = msg.comm_set;
    }
    else {
      resolved.comm_set = []
    }

    if (msg.can_forward_set !== undefined) {
      resolved.can_forward_set = msg.can_forward_set;
    }
    else {
      resolved.can_forward_set = []
    }

    if (msg.value_set !== undefined) {
      resolved.value_set = msg.value_set;
    }
    else {
      resolved.value_set = []
    }

    if (msg.data_bytes !== undefined) {
      resolved.data_bytes = msg.data_bytes;
    }
    else {
      resolved.data_bytes = 0
    }

    return resolved;
    }
};

module.exports = VescSetCustomApp;
