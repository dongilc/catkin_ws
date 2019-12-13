// Auto-generated. Do not edit!

// (in-package vesc_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VescGetCustomApp {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.send_mode_index1 = null;
      this.fw_ver_major = null;
      this.fw_ver_minor = null;
      this.fault_code = null;
      this.app_status_code = null;
      this.send_mode_index2 = null;
      this.can_devs_num = null;
      this.can_id = null;
      this.custom_status = null;
      this.enc_rps = null;
      this.enc_rad = null;
      this.current = null;
      this.duty = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('send_mode_index1')) {
        this.send_mode_index1 = initObj.send_mode_index1
      }
      else {
        this.send_mode_index1 = 0;
      }
      if (initObj.hasOwnProperty('fw_ver_major')) {
        this.fw_ver_major = initObj.fw_ver_major
      }
      else {
        this.fw_ver_major = 0;
      }
      if (initObj.hasOwnProperty('fw_ver_minor')) {
        this.fw_ver_minor = initObj.fw_ver_minor
      }
      else {
        this.fw_ver_minor = 0;
      }
      if (initObj.hasOwnProperty('fault_code')) {
        this.fault_code = initObj.fault_code
      }
      else {
        this.fault_code = 0;
      }
      if (initObj.hasOwnProperty('app_status_code')) {
        this.app_status_code = initObj.app_status_code
      }
      else {
        this.app_status_code = 0;
      }
      if (initObj.hasOwnProperty('send_mode_index2')) {
        this.send_mode_index2 = initObj.send_mode_index2
      }
      else {
        this.send_mode_index2 = 0;
      }
      if (initObj.hasOwnProperty('can_devs_num')) {
        this.can_devs_num = initObj.can_devs_num
      }
      else {
        this.can_devs_num = 0;
      }
      if (initObj.hasOwnProperty('can_id')) {
        this.can_id = initObj.can_id
      }
      else {
        this.can_id = [];
      }
      if (initObj.hasOwnProperty('custom_status')) {
        this.custom_status = initObj.custom_status
      }
      else {
        this.custom_status = [];
      }
      if (initObj.hasOwnProperty('enc_rps')) {
        this.enc_rps = initObj.enc_rps
      }
      else {
        this.enc_rps = [];
      }
      if (initObj.hasOwnProperty('enc_rad')) {
        this.enc_rad = initObj.enc_rad
      }
      else {
        this.enc_rad = [];
      }
      if (initObj.hasOwnProperty('current')) {
        this.current = initObj.current
      }
      else {
        this.current = [];
      }
      if (initObj.hasOwnProperty('duty')) {
        this.duty = initObj.duty
      }
      else {
        this.duty = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VescGetCustomApp
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [send_mode_index1]
    bufferOffset = _serializer.int32(obj.send_mode_index1, buffer, bufferOffset);
    // Serialize message field [fw_ver_major]
    bufferOffset = _serializer.int32(obj.fw_ver_major, buffer, bufferOffset);
    // Serialize message field [fw_ver_minor]
    bufferOffset = _serializer.int32(obj.fw_ver_minor, buffer, bufferOffset);
    // Serialize message field [fault_code]
    bufferOffset = _serializer.int32(obj.fault_code, buffer, bufferOffset);
    // Serialize message field [app_status_code]
    bufferOffset = _serializer.int32(obj.app_status_code, buffer, bufferOffset);
    // Serialize message field [send_mode_index2]
    bufferOffset = _serializer.int32(obj.send_mode_index2, buffer, bufferOffset);
    // Serialize message field [can_devs_num]
    bufferOffset = _serializer.int32(obj.can_devs_num, buffer, bufferOffset);
    // Serialize message field [can_id]
    bufferOffset = _arraySerializer.int32(obj.can_id, buffer, bufferOffset, null);
    // Serialize message field [custom_status]
    bufferOffset = _arraySerializer.int32(obj.custom_status, buffer, bufferOffset, null);
    // Serialize message field [enc_rps]
    bufferOffset = _arraySerializer.float64(obj.enc_rps, buffer, bufferOffset, null);
    // Serialize message field [enc_rad]
    bufferOffset = _arraySerializer.float64(obj.enc_rad, buffer, bufferOffset, null);
    // Serialize message field [current]
    bufferOffset = _arraySerializer.float64(obj.current, buffer, bufferOffset, null);
    // Serialize message field [duty]
    bufferOffset = _arraySerializer.float64(obj.duty, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VescGetCustomApp
    let len;
    let data = new VescGetCustomApp(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [send_mode_index1]
    data.send_mode_index1 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [fw_ver_major]
    data.fw_ver_major = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [fw_ver_minor]
    data.fw_ver_minor = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [fault_code]
    data.fault_code = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [app_status_code]
    data.app_status_code = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [send_mode_index2]
    data.send_mode_index2 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [can_devs_num]
    data.can_devs_num = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [can_id]
    data.can_id = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [custom_status]
    data.custom_status = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [enc_rps]
    data.enc_rps = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [enc_rad]
    data.enc_rad = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [current]
    data.current = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [duty]
    data.duty = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 4 * object.can_id.length;
    length += 4 * object.custom_status.length;
    length += 8 * object.enc_rps.length;
    length += 8 * object.enc_rad.length;
    length += 8 * object.current.length;
    length += 8 * object.duty.length;
    return length + 52;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vesc_msgs/VescGetCustomApp';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'daa4967cc5ef43655bd186c327b3176d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # VESCuino CDI CUSTOM_APP RX Messages
    
    Header  header
    
    # FW Version Data
    int32 send_mode_index1
    int32 fw_ver_major
    int32 fw_ver_minor
    
    # Original Get Value Data
    #float64 voltage_input        # input voltage (volt)
    #float64 temperature_pcb      # temperature of printed circuit board (degrees Celsius)
    #float64 current_motor        # motor current (ampere)
    #float64 current_input        # input current (ampere)
    #float64 speed                # motor electrical speed (revolutions per minute) 
    #float64 duty_cycle           # duty cycle (0 to 1)
    #float64 charge_drawn         # electric charge drawn from input (ampere-hour)
    #float64 charge_regen         # electric charge regenerated to input (ampere-hour)
    #float64 energy_drawn         # energy drawn from input (watt-hour)
    #float64 energy_regen         # energy regenerated to input (watt-hour)
    #float64 displacement         # net tachometer (counts)
    #float64 distance_traveled    # total tachnometer (counts)
    int32   fault_code
    #float64 pid_pos_now    		 # pid position now (deg) 0~360
    
    int32 app_status_code        # application status code
    
    # CAN Status Data 
    int32 send_mode_index2
    int32 can_devs_num
    int32[] can_id
    int32[] custom_status
    
    # Raw Encoder Data
    float64[] enc_rps		     # Encoder Read Raw Data (No Delay, rad/sec) 
    float64[] enc_rad			 # Encoder Read Raw Data (No Delay, rad)
    float64[] current			 # can status - current
    float64[] duty			     # can status - duty
    
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
    # 0: no frame
    # 1: global frame
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VescGetCustomApp(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.send_mode_index1 !== undefined) {
      resolved.send_mode_index1 = msg.send_mode_index1;
    }
    else {
      resolved.send_mode_index1 = 0
    }

    if (msg.fw_ver_major !== undefined) {
      resolved.fw_ver_major = msg.fw_ver_major;
    }
    else {
      resolved.fw_ver_major = 0
    }

    if (msg.fw_ver_minor !== undefined) {
      resolved.fw_ver_minor = msg.fw_ver_minor;
    }
    else {
      resolved.fw_ver_minor = 0
    }

    if (msg.fault_code !== undefined) {
      resolved.fault_code = msg.fault_code;
    }
    else {
      resolved.fault_code = 0
    }

    if (msg.app_status_code !== undefined) {
      resolved.app_status_code = msg.app_status_code;
    }
    else {
      resolved.app_status_code = 0
    }

    if (msg.send_mode_index2 !== undefined) {
      resolved.send_mode_index2 = msg.send_mode_index2;
    }
    else {
      resolved.send_mode_index2 = 0
    }

    if (msg.can_devs_num !== undefined) {
      resolved.can_devs_num = msg.can_devs_num;
    }
    else {
      resolved.can_devs_num = 0
    }

    if (msg.can_id !== undefined) {
      resolved.can_id = msg.can_id;
    }
    else {
      resolved.can_id = []
    }

    if (msg.custom_status !== undefined) {
      resolved.custom_status = msg.custom_status;
    }
    else {
      resolved.custom_status = []
    }

    if (msg.enc_rps !== undefined) {
      resolved.enc_rps = msg.enc_rps;
    }
    else {
      resolved.enc_rps = []
    }

    if (msg.enc_rad !== undefined) {
      resolved.enc_rad = msg.enc_rad;
    }
    else {
      resolved.enc_rad = []
    }

    if (msg.current !== undefined) {
      resolved.current = msg.current;
    }
    else {
      resolved.current = []
    }

    if (msg.duty !== undefined) {
      resolved.duty = msg.duty;
    }
    else {
      resolved.duty = []
    }

    return resolved;
    }
};

module.exports = VescGetCustomApp;
