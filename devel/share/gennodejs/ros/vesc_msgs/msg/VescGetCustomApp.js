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
      this.voltage_input = null;
      this.temperature_pcb = null;
      this.current_motor = null;
      this.current_input = null;
      this.speed = null;
      this.duty_cycle = null;
      this.charge_drawn = null;
      this.charge_regen = null;
      this.energy_drawn = null;
      this.energy_regen = null;
      this.displacement = null;
      this.distance_traveled = null;
      this.fault_code = null;
      this.pid_pos_now = null;
      this.enc_rps = null;
      this.enc_rad = null;
      this.app_status_code = null;
      this.send_mode_index2 = null;
      this.can_dev_num = null;
      this.can_id = null;
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
      if (initObj.hasOwnProperty('voltage_input')) {
        this.voltage_input = initObj.voltage_input
      }
      else {
        this.voltage_input = 0.0;
      }
      if (initObj.hasOwnProperty('temperature_pcb')) {
        this.temperature_pcb = initObj.temperature_pcb
      }
      else {
        this.temperature_pcb = 0.0;
      }
      if (initObj.hasOwnProperty('current_motor')) {
        this.current_motor = initObj.current_motor
      }
      else {
        this.current_motor = 0.0;
      }
      if (initObj.hasOwnProperty('current_input')) {
        this.current_input = initObj.current_input
      }
      else {
        this.current_input = 0.0;
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0.0;
      }
      if (initObj.hasOwnProperty('duty_cycle')) {
        this.duty_cycle = initObj.duty_cycle
      }
      else {
        this.duty_cycle = 0.0;
      }
      if (initObj.hasOwnProperty('charge_drawn')) {
        this.charge_drawn = initObj.charge_drawn
      }
      else {
        this.charge_drawn = 0.0;
      }
      if (initObj.hasOwnProperty('charge_regen')) {
        this.charge_regen = initObj.charge_regen
      }
      else {
        this.charge_regen = 0.0;
      }
      if (initObj.hasOwnProperty('energy_drawn')) {
        this.energy_drawn = initObj.energy_drawn
      }
      else {
        this.energy_drawn = 0.0;
      }
      if (initObj.hasOwnProperty('energy_regen')) {
        this.energy_regen = initObj.energy_regen
      }
      else {
        this.energy_regen = 0.0;
      }
      if (initObj.hasOwnProperty('displacement')) {
        this.displacement = initObj.displacement
      }
      else {
        this.displacement = 0.0;
      }
      if (initObj.hasOwnProperty('distance_traveled')) {
        this.distance_traveled = initObj.distance_traveled
      }
      else {
        this.distance_traveled = 0.0;
      }
      if (initObj.hasOwnProperty('fault_code')) {
        this.fault_code = initObj.fault_code
      }
      else {
        this.fault_code = 0;
      }
      if (initObj.hasOwnProperty('pid_pos_now')) {
        this.pid_pos_now = initObj.pid_pos_now
      }
      else {
        this.pid_pos_now = 0.0;
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
      if (initObj.hasOwnProperty('can_dev_num')) {
        this.can_dev_num = initObj.can_dev_num
      }
      else {
        this.can_dev_num = 0;
      }
      if (initObj.hasOwnProperty('can_id')) {
        this.can_id = initObj.can_id
      }
      else {
        this.can_id = [];
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
    // Serialize message field [voltage_input]
    bufferOffset = _serializer.float64(obj.voltage_input, buffer, bufferOffset);
    // Serialize message field [temperature_pcb]
    bufferOffset = _serializer.float64(obj.temperature_pcb, buffer, bufferOffset);
    // Serialize message field [current_motor]
    bufferOffset = _serializer.float64(obj.current_motor, buffer, bufferOffset);
    // Serialize message field [current_input]
    bufferOffset = _serializer.float64(obj.current_input, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float64(obj.speed, buffer, bufferOffset);
    // Serialize message field [duty_cycle]
    bufferOffset = _serializer.float64(obj.duty_cycle, buffer, bufferOffset);
    // Serialize message field [charge_drawn]
    bufferOffset = _serializer.float64(obj.charge_drawn, buffer, bufferOffset);
    // Serialize message field [charge_regen]
    bufferOffset = _serializer.float64(obj.charge_regen, buffer, bufferOffset);
    // Serialize message field [energy_drawn]
    bufferOffset = _serializer.float64(obj.energy_drawn, buffer, bufferOffset);
    // Serialize message field [energy_regen]
    bufferOffset = _serializer.float64(obj.energy_regen, buffer, bufferOffset);
    // Serialize message field [displacement]
    bufferOffset = _serializer.float64(obj.displacement, buffer, bufferOffset);
    // Serialize message field [distance_traveled]
    bufferOffset = _serializer.float64(obj.distance_traveled, buffer, bufferOffset);
    // Serialize message field [fault_code]
    bufferOffset = _serializer.int32(obj.fault_code, buffer, bufferOffset);
    // Serialize message field [pid_pos_now]
    bufferOffset = _serializer.float64(obj.pid_pos_now, buffer, bufferOffset);
    // Serialize message field [enc_rps]
    bufferOffset = _arraySerializer.float64(obj.enc_rps, buffer, bufferOffset, null);
    // Serialize message field [enc_rad]
    bufferOffset = _arraySerializer.float64(obj.enc_rad, buffer, bufferOffset, null);
    // Serialize message field [app_status_code]
    bufferOffset = _serializer.int32(obj.app_status_code, buffer, bufferOffset);
    // Serialize message field [send_mode_index2]
    bufferOffset = _serializer.int32(obj.send_mode_index2, buffer, bufferOffset);
    // Serialize message field [can_dev_num]
    bufferOffset = _serializer.int32(obj.can_dev_num, buffer, bufferOffset);
    // Serialize message field [can_id]
    bufferOffset = _arraySerializer.int32(obj.can_id, buffer, bufferOffset, null);
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
    // Deserialize message field [voltage_input]
    data.voltage_input = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [temperature_pcb]
    data.temperature_pcb = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [current_motor]
    data.current_motor = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [current_input]
    data.current_input = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [duty_cycle]
    data.duty_cycle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [charge_drawn]
    data.charge_drawn = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [charge_regen]
    data.charge_regen = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [energy_drawn]
    data.energy_drawn = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [energy_regen]
    data.energy_regen = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [displacement]
    data.displacement = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [distance_traveled]
    data.distance_traveled = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fault_code]
    data.fault_code = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [pid_pos_now]
    data.pid_pos_now = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [enc_rps]
    data.enc_rps = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [enc_rad]
    data.enc_rad = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [app_status_code]
    data.app_status_code = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [send_mode_index2]
    data.send_mode_index2 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [can_dev_num]
    data.can_dev_num = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [can_id]
    data.can_id = _arrayDeserializer.int32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 8 * object.enc_rps.length;
    length += 8 * object.enc_rad.length;
    length += 4 * object.can_id.length;
    return length + 144;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vesc_msgs/VescGetCustomApp';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '90215f495cfc9bdca67860d224bb3fe7';
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
    float64 voltage_input        # input voltage (volt)
    float64 temperature_pcb      # temperature of printed circuit board (degrees Celsius)
    float64 current_motor        # motor current (ampere)
    float64 current_input        # input current (ampere)
    float64 speed                # motor electrical speed (revolutions per minute) 
    float64 duty_cycle           # duty cycle (0 to 1)
    float64 charge_drawn         # electric charge drawn from input (ampere-hour)
    float64 charge_regen         # electric charge regenerated to input (ampere-hour)
    float64 energy_drawn         # energy drawn from input (watt-hour)
    float64 energy_regen         # energy regenerated to input (watt-hour)
    float64 displacement         # net tachometer (counts)
    float64 distance_traveled    # total tachnometer (counts)
    int32   fault_code
    float64 pid_pos_now    		 # pid position now (deg) 0~360
    
    # Raw Encoder Data
    float64[] enc_rps		     # Encoder Read Raw Data (No Delay, rad/sec) 
    float64[] enc_rad			 # Encoder Read Raw Data (No Delay, rad)
    int32 app_status_code        # application status code
    
    # CAN Status Data 
    int32 send_mode_index2
    int32 can_dev_num
    int32[] can_id
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

    if (msg.voltage_input !== undefined) {
      resolved.voltage_input = msg.voltage_input;
    }
    else {
      resolved.voltage_input = 0.0
    }

    if (msg.temperature_pcb !== undefined) {
      resolved.temperature_pcb = msg.temperature_pcb;
    }
    else {
      resolved.temperature_pcb = 0.0
    }

    if (msg.current_motor !== undefined) {
      resolved.current_motor = msg.current_motor;
    }
    else {
      resolved.current_motor = 0.0
    }

    if (msg.current_input !== undefined) {
      resolved.current_input = msg.current_input;
    }
    else {
      resolved.current_input = 0.0
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0.0
    }

    if (msg.duty_cycle !== undefined) {
      resolved.duty_cycle = msg.duty_cycle;
    }
    else {
      resolved.duty_cycle = 0.0
    }

    if (msg.charge_drawn !== undefined) {
      resolved.charge_drawn = msg.charge_drawn;
    }
    else {
      resolved.charge_drawn = 0.0
    }

    if (msg.charge_regen !== undefined) {
      resolved.charge_regen = msg.charge_regen;
    }
    else {
      resolved.charge_regen = 0.0
    }

    if (msg.energy_drawn !== undefined) {
      resolved.energy_drawn = msg.energy_drawn;
    }
    else {
      resolved.energy_drawn = 0.0
    }

    if (msg.energy_regen !== undefined) {
      resolved.energy_regen = msg.energy_regen;
    }
    else {
      resolved.energy_regen = 0.0
    }

    if (msg.displacement !== undefined) {
      resolved.displacement = msg.displacement;
    }
    else {
      resolved.displacement = 0.0
    }

    if (msg.distance_traveled !== undefined) {
      resolved.distance_traveled = msg.distance_traveled;
    }
    else {
      resolved.distance_traveled = 0.0
    }

    if (msg.fault_code !== undefined) {
      resolved.fault_code = msg.fault_code;
    }
    else {
      resolved.fault_code = 0
    }

    if (msg.pid_pos_now !== undefined) {
      resolved.pid_pos_now = msg.pid_pos_now;
    }
    else {
      resolved.pid_pos_now = 0.0
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

    if (msg.can_dev_num !== undefined) {
      resolved.can_dev_num = msg.can_dev_num;
    }
    else {
      resolved.can_dev_num = 0
    }

    if (msg.can_id !== undefined) {
      resolved.can_id = msg.can_id;
    }
    else {
      resolved.can_id = []
    }

    return resolved;
    }
};

module.exports = VescGetCustomApp;
