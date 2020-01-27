// -*- mode:c++; fill-column: 100; -*-

#ifndef VESC_DRIVER_VESC_PACKET_H_
#define VESC_DRIVER_VESC_PACKET_H_

#include <string>
#include <vector>
#include <utility>

#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>

#include "vesc_driver/datatypes.h"	//cdi
#include "vesc_driver/v8stdint.h"
#include "vesc_msgs/VescSetCustomApp.h"	//cdi

namespace vesc_driver
{

typedef std::vector<uint8_t> Buffer;
typedef std::pair<Buffer::iterator, Buffer::iterator> BufferRange;
typedef std::pair<Buffer::const_iterator, Buffer::const_iterator> BufferRangeConst;

/** The raw frame for communicating with the VESC */
class VescFrame
{
public:
  virtual ~VescFrame() {}

  // getters
  virtual const Buffer& frame() const {return *frame_;}

  // VESC packet properties
  static const int VESC_MAX_PAYLOAD_SIZE = 1024;          ///< Maximum VESC payload size, in bytes
  static const int VESC_MIN_FRAME_SIZE = 5;               ///< Smallest VESC frame size, in bytes
  static const int VESC_MAX_FRAME_SIZE = 6 + VESC_MAX_PAYLOAD_SIZE; ///< Largest VESC frame size, in bytes
  static const unsigned int VESC_SOF_VAL_SMALL_FRAME = 2; ///< VESC start of "small" frame value
  static const unsigned int VESC_SOF_VAL_LARGE_FRAME = 3; ///< VESC start of "large" frame value
  static const unsigned int VESC_EOF_VAL = 3;             ///< VESC end-of-frame value

  /** CRC parameters for the VESC */
  typedef boost::crc_optimal<16, 0x1021, 0, 0, false, false> CRC;

protected:
  /** Construct frame with specified payload size. */
  VescFrame(int payload_size);
  VescFrame(int payload_size, int sendCan_flag, int canId_num);

  boost::shared_ptr<Buffer> frame_; ///< Stores frame data, shared_ptr for shallow copy
  BufferRange payload_;             ///< View into frame's payload section

  //cdi
  int sendCan;
  int CanId;

private:
  /** Construct from buffer. Used by VescPacketFactory factory. */
  VescFrame(const BufferRangeConst& frame, const BufferRangeConst& payload);

  /** Give VescPacketFactory access to private constructor. */
  friend class VescPacketFactory;
};

/*------------------------------------------------------------------------------------------------*/

/** A VescPacket is a VescFrame with a non-zero length payload */
class VescPacket : public VescFrame
{
public:
  virtual ~VescPacket() {}

  virtual const std::string& name() const {return name_;}

protected:
  VescPacket(const std::string& name, int payload_size, int payload_id);
  VescPacket(const std::string& name, int payload_size, int payload_id, int canf_flag, int can_id);
  VescPacket(const std::string& name, boost::shared_ptr<VescFrame> raw);

private:
  std::string name_;
};

typedef boost::shared_ptr<VescPacket> VescPacketPtr;
typedef boost::shared_ptr<VescPacket const> VescPacketConstPtr;

/*------------------------------------------------------------------------------------------------*/

class VescPacketFWVersion : public VescPacket
{
public:
  VescPacketFWVersion(boost::shared_ptr<VescFrame> raw);

  int fwMajor() const;
  int fwMinor() const;

  int length() const;

};

class VescPacketRequestFWVersion : public VescPacket
{
public:
  VescPacketRequestFWVersion();

};

/*------------------------------------------------------------------------------------------------*/

class VescPacketValues : public VescPacket
{
public:
  VescPacketValues(boost::shared_ptr<VescFrame> raw);

#ifdef FW_2_18
  double v_in() const;
  double temp_mos1() const;
  double temp_mos2() const;
  double temp_mos3() const;
  double temp_mos4() const;
  double temp_mos5() const;
  double temp_mos6() const;
  double temp_pcb() const;
  double current_motor() const;
  double current_in() const;
  double rpm() const;
  double duty_now() const;
  double amp_hours() const;
  double amp_hours_charged() const;
  double watt_hours() const;
  double watt_hours_charged() const;
  double tachometer() const;
  double tachometer_abs() const;
  int fault_code() const;
#endif

#ifdef FW_3_38
  double temp_fet_filtered() const;
  double temp_motor_filtered() const;
  double current_motor() const;
  double current_in() const;
  double foc_d_axis_current() const;
  double foc_q_axis_current() const;
  double rpm() const;
  double v_in() const;
  double duty_now() const;
  double amp_hours() const;
  double amp_hours_charged() const;
  double watt_hours() const;
  double watt_hours_charged() const;
  double tachometer() const;
  double tachometer_abs() const;
  int fault_code() const;
  double pid_pos_now() const;
#endif

#ifdef FW_3_40
  double temp_fet_filtered() const;
  double temp_motor_filtered() const;
  double current_motor() const;
  double current_in() const;
  double foc_d_axis_current() const;
  double foc_q_axis_current() const;
  double rpm() const;
  double v_in() const;
  double duty_now() const;
  double amp_hours() const;
  double amp_hours_charged() const;
  double watt_hours() const;
  double watt_hours_charged() const;
  double tachometer() const;
  double tachometer_abs() const;
  int fault_code() const;
  double pid_pos_now() const;
  int controller_id() const;
#endif

};

class VescPacketRequestValues : public VescPacket
{
public:
  VescPacketRequestValues();
};

/*------------------------------------------------------------------------------------------------*/

class VescPacketCustomApp : public VescPacket
{
public:
	VescPacketCustomApp(boost::shared_ptr<VescFrame> raw);

  int length() const;

  int send_mode_1() const;
  int fwMajor() const;
  int fwMinor() const;
  int controller_id() const;

  // GET_VALUE Returns
  // double temp_fet_filtered() const;
  // double temp_motor_filtered() const;
  // double current_motor() const;
  // double current_in() const;
  // double foc_d_axis_current() const;
  // double foc_q_axis_current() const;
  // double rpm() const;
  // double v_in() const;
  // double duty_now() const;
  // double amp_hours() const;
  // double amp_hours_charged() const;
  // double watt_hours() const;
  // double watt_hours_charged() const;
  // double tachometer() const;
  // double tachometer_abs() const;
  int fault_code() const;
  // double pid_pos_now() const;
  int app_status_code() const;

  double enc_rps() const;
  //double enc_rad() const;
  double current() const; //191201
  double duty() const;    //191201
  //double enc_dps() const;
  //double enc_deg() const;

  int send_mode_2() const;
  int can_devs_num() const;
  int can_id(int id) const;
  double enc_rps_can(int id) const;
  //double enc_rad_can(int id) const;
  double current_can(int id) const; //191201
  double duty_can(int id) const;    //191201
  //double enc_dps_can(int id) const;
  //double enc_deg_can(int id) const;

};

class VescPacketRequestCustomApp : public VescPacket
{
public:
	VescPacketRequestCustomApp();
};

class VescPacketSetCustomAppData : public VescPacket
{
public:
	VescPacketSetCustomAppData(const vesc_msgs::VescSetCustomApp::ConstPtr& custom_set_msg);
};

/*------------------------------------------------------------------------------------------------*/

//cdi
class VescPacketSetALIVE : public VescPacket
{
public:
	VescPacketSetALIVE();
};

/*------------------------------------------------------------------------------------------------*/

class VescPacketSetDuty : public VescPacket
{
public:
  VescPacketSetDuty(double duty);
  VescPacketSetDuty(double duty, int canf_flag, int can_id);

  //  double duty() const;
};

/*------------------------------------------------------------------------------------------------*/

class VescPacketSetCurrent : public VescPacket
{
public:
  VescPacketSetCurrent(double current);
  VescPacketSetCurrent(double current, int canf_flag, int can_id);

  //  double current() const;
};

/*------------------------------------------------------------------------------------------------*/

class VescPacketSetCurrentBrake : public VescPacket
{
public:
  VescPacketSetCurrentBrake(double current_brake);
  VescPacketSetCurrentBrake(double current_brake, int canf_flag, int can_id);

  //  double current_brake() const;
};

/*------------------------------------------------------------------------------------------------*/

class VescPacketSetRPM : public VescPacket
{
public:
  VescPacketSetRPM(double rpm);
  VescPacketSetRPM(double rpm, int canf_flag, int can_id);

  //  double rpm() const;
};

/*------------------------------------------------------------------------------------------------*/

class VescPacketSetPos : public VescPacket
{
public:
  VescPacketSetPos(double pos);
  VescPacketSetPos(double pos, int canf_flag, int can_id);

  //  double pos() const;
};

/*------------------------------------------------------------------------------------------------*/

class VescPacketSetServoPos : public VescPacket
{
public:
  VescPacketSetServoPos(double servo_pos);
  VescPacketSetServoPos(double rpm, int canf_flag, int can_id);

  //  double servo_pos() const;
};

/*------------------------------------------------------------------------------------------------*/

class VescPacketCommPrint : public VescPacket
{
public:
  VescPacketCommPrint(boost::shared_ptr<VescFrame> raw);

  int length() const;
  int rxmsg1() const;
  int rxmsg2() const;
  int rxmsg3() const;
  int rxmsg4() const;
  int rxmsg5() const;

};

/*------------------------------------------------------------------------------------------------*/

} // namespace vesc_driver

#endif // VESC_DRIVER_VESC_PACKET_H_
