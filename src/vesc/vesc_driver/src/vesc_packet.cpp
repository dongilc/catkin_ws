// -*- mode:c++; fill-column: 100; -*-

#include "vesc_driver/vesc_packet.h"

#include <cassert>
#include <iterator>

#include <boost/range/begin.hpp>
#include <boost/range/distance.hpp>
#include <boost/range/end.hpp>

#include "vesc_driver/vesc_packet_factory.h"
#include "vesc_driver/datatypes.h"
#include "vesc_msgs/VescSetCustomApp.h"	//cdi

namespace vesc_driver
{

VescFrame::VescFrame(int payload_size)
{
  assert(payload_size >= 0 && payload_size <= 1024);

  if (payload_size < 256) {
    // single byte payload size
    frame_.reset(new Buffer(VESC_MIN_FRAME_SIZE + payload_size));
    *frame_->begin() = 2;
    *(frame_->begin() + 1) = payload_size;
    payload_.first = frame_->begin() + 2;
  }
  else {
    // two byte payload size
    frame_.reset(new Buffer(VESC_MIN_FRAME_SIZE + 1 + payload_size));
    *frame_->begin() = 3;
    *(frame_->begin() + 1) = payload_size >> 8;
    *(frame_->begin() + 2) = payload_size & 0xFF;
    payload_.first = frame_->begin() + 3;
  }

  payload_.second = payload_.first + payload_size;
  *(frame_->end() - 1) = 3;
}

VescFrame::VescFrame(int payload_size, int sendCan_flag, int canId_num) :
		sendCan(sendCan_flag),
		CanId(canId_num)
{
  assert(payload_size >= 0 && payload_size <= 1024);

  // can forward, cdi
  if (sendCan) {
	  payload_size += 2;
  }

  if (payload_size < 256) {
    // single byte payload size
    frame_.reset(new Buffer(VESC_MIN_FRAME_SIZE + payload_size));
    *frame_->begin() = 2;
    *(frame_->begin() + 1) = payload_size;
    payload_.first = frame_->begin() + 2;
  }
  else {
    // two byte payload size
    frame_.reset(new Buffer(VESC_MIN_FRAME_SIZE + 1 + payload_size));
    *frame_->begin() = 3;
    *(frame_->begin() + 1) = payload_size >> 8;
    *(frame_->begin() + 2) = payload_size & 0xFF;
    payload_.first = frame_->begin() + 3;
  }

  // can forward, cdi
  if (sendCan) {
	  *payload_.first = COMM_FORWARD_CAN;
	  *(payload_.first + 1) = CanId;
  }

  payload_.second = payload_.first + payload_size;
  *(frame_->end() - 1) = 3;
}

VescFrame::VescFrame(const BufferRangeConst& frame, const BufferRangeConst& payload)
{
  /* VescPacketFactory::createPacket() should make sure that the input is valid, but run a few cheap
     checks anyway */
  assert(boost::distance(frame) >= VESC_MIN_FRAME_SIZE);
  assert(boost::distance(frame) <= VESC_MAX_FRAME_SIZE);
  assert(boost::distance(payload) <= VESC_MAX_PAYLOAD_SIZE);
  assert(std::distance(frame.first, payload.first) > 0 &&
         std::distance(payload.second, frame.second) > 0);

  frame_.reset(new Buffer(boost::begin(frame), boost::end(frame)));
  payload_.first = frame_->begin() + std::distance(frame.first, payload.first);
  payload_.second = frame_->begin() + std::distance(frame.first, payload.second);
}

VescPacket::VescPacket(const std::string& name, int payload_size, int payload_id) :
  VescFrame(payload_size), name_(name)
{
  assert(payload_id >= 0 && payload_id < 256);
  assert(boost::distance(payload_) > 0);
  *payload_.first = payload_id;
}

VescPacket::VescPacket(const std::string& name, int payload_size, int payload_id, int canf_flag, int can_id) :
  VescFrame(payload_size, canf_flag, can_id), name_(name)
{
  assert(payload_id >= 0 && payload_id < 256);
  assert(boost::distance(payload_) > 0);

  if (canf_flag) {
	  *(payload_.first + 2) = payload_id;
  }
  else
  {
	  *payload_.first = payload_id;
  }
}

VescPacket::VescPacket(const std::string& name, boost::shared_ptr<VescFrame> raw) :
  VescFrame(*raw), name_(name)
{
}


/*------------------------------------------------------------------------------------------------*/

// Rx Part
VescPacketFWVersion::VescPacketFWVersion(boost::shared_ptr<VescFrame> raw) :
  VescPacket("FWVersion", raw)
{
}

int VescPacketFWVersion::length() const
{
  return *(payload_.first + 3);
}

int VescPacketFWVersion::fwMajor() const
{
  return *(payload_.first + 1);
}

int VescPacketFWVersion::fwMinor() const
{
  return *(payload_.first + 2);
}

REGISTER_PACKET_TYPE(COMM_FW_VERSION, VescPacketFWVersion)

// Tx Part
VescPacketRequestFWVersion::VescPacketRequestFWVersion() :
  VescPacket("RequestFWVersion", 1, COMM_FW_VERSION)
{
  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/

// Rx Part
VescPacketValues::VescPacketValues(boost::shared_ptr<VescFrame> raw) :
  VescPacket("Values", raw)
{
}

#ifdef FW_2_18
// FW 2.18
double VescPacketValues::temp_mos1() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 1)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 2)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::temp_mos2() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 3)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 4)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::temp_mos3() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 5)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 6)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::temp_mos4() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 7)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 8)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::temp_mos5() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 9)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 10)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::temp_mos6() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 11)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 12)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::temp_pcb() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 13)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 14)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::current_motor() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 15)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 16)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 17)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 18)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::current_in() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 19)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 20)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 21)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 22)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::duty_now() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 23)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 24)));
  return static_cast<double>(v) / 1000.0;
}
double VescPacketValues::rpm() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 25)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 26)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 27)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 28)));
  return static_cast<double>(v);
}
double VescPacketValues::v_in() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 29)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 30)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::amp_hours() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 31)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 32)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 33)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 34)));
  return static_cast<double>(v);
}
double VescPacketValues::amp_hours_charged() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 35)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 36)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 37)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 38)));
  return static_cast<double>(v);
}
double VescPacketValues::watt_hours() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 39)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 40)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 41)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 42)));
  return static_cast<double>(v);
}
double VescPacketValues::watt_hours_charged() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 43)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 44)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 45)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 46)));
  return static_cast<double>(v);
}
double VescPacketValues::tachometer() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 47)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 48)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 49)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 50)));
  return static_cast<double>(v);
}
double VescPacketValues::tachometer_abs() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 51)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 52)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 53)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 54)));
  return static_cast<double>(v);
}
int VescPacketValues::fault_code() const
{
  return static_cast<int32_t>(*(payload_.first + 55));
}
#endif

#ifdef FW_3_38
// FW 3.38
double VescPacketValues::temp_fet_filtered() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 1)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 2)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::temp_motor_filtered() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 3)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 4)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::current_motor() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 5)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 6)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 7)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 8)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::current_in() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 9)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 10)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 11)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 12)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::foc_d_axis_current() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 13)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 14)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 15)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 16)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::foc_q_axis_current() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 17)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 18)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 19)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 20)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::duty_now() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 21)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 22)));
  return static_cast<double>(v) / 1000.0;
}
double VescPacketValues::rpm() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 23)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 24)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 25)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 26)));
  return static_cast<double>(v);
}
double VescPacketValues::v_in() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 27)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 28)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::amp_hours() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 29)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 30)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 31)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 32)));
  return static_cast<double>(v);
}
double VescPacketValues::amp_hours_charged() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 33)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 34)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 35)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 36)));
  return static_cast<double>(v);
}
double VescPacketValues::watt_hours() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 37)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 38)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 39)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 40)));
  return static_cast<double>(v);
}
double VescPacketValues::watt_hours_charged() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 41)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 42)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 43)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 44)));
  return static_cast<double>(v);
}
double VescPacketValues::tachometer() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 45)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 46)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 47)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 48)));
  return static_cast<double>(v);
}
double VescPacketValues::tachometer_abs() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 49)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 50)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 51)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 52)));
  return static_cast<double>(v);
}
int VescPacketValues::fault_code() const
{
  return static_cast<int32_t>(*(payload_.first + 53));
}
double VescPacketValues::pid_pos_now() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 54)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 55)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 56)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 57)));
  return static_cast<double>(v) / 1000000.0;
}
#endif

#ifdef FW_3_40
// FW 3.40
double VescPacketValues::temp_fet_filtered() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 1)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 2)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::temp_motor_filtered() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 3)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 4)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::current_motor() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 5)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 6)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 7)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 8)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::current_in() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 9)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 10)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 11)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 12)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::foc_d_axis_current() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 13)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 14)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 15)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 16)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::foc_q_axis_current() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 17)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 18)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 19)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 20)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketValues::duty_now() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 21)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 22)));
  return static_cast<double>(v) / 1000.0;
}
double VescPacketValues::rpm() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 23)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 24)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 25)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 26)));
  return static_cast<double>(v);
}
double VescPacketValues::v_in() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 27)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 28)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketValues::amp_hours() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 29)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 30)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 31)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 32)));
  return static_cast<double>(v);
}
double VescPacketValues::amp_hours_charged() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 33)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 34)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 35)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 36)));
  return static_cast<double>(v);
}
double VescPacketValues::watt_hours() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 37)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 38)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 39)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 40)));
  return static_cast<double>(v);
}
double VescPacketValues::watt_hours_charged() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 41)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 42)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 43)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 44)));
  return static_cast<double>(v);
}
double VescPacketValues::tachometer() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 45)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 46)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 47)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 48)));
  return static_cast<double>(v);
}
double VescPacketValues::tachometer_abs() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 49)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 50)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 51)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 52)));
  return static_cast<double>(v);
}
int VescPacketValues::fault_code() const
{
  return static_cast<int32_t>(*(payload_.first + 53));
}
double VescPacketValues::pid_pos_now() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 54)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 55)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 56)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 57)));
  return static_cast<double>(v) / 1000000.0;
}
int VescPacketValues::controller_id() const
{
  return static_cast<int32_t>(*(payload_.first + 58));
}
#endif

REGISTER_PACKET_TYPE(COMM_GET_VALUES, VescPacketValues)

// Tx Part
VescPacketRequestValues::VescPacketRequestValues() :
  VescPacket("GetValue", 1, COMM_GET_VALUES)
{
  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/

// Rx Part
//cdi
VescPacketCustomApp::VescPacketCustomApp(boost::shared_ptr<VescFrame> raw) :
  VescPacket("CustomApp", raw)
{
}

int VescPacketCustomApp::length() const
{
  return boost::distance(payload_);
}

int VescPacketCustomApp::send_mode_1() const
{
	return *(payload_.first + 1);
}
int VescPacketCustomApp::fwMajor() const
{
	return *(payload_.first + 2);
}
int VescPacketCustomApp::fwMinor() const
{
	return *(payload_.first + 3);
}

/*
double VescPacketCustomApp::temp_fet_filtered() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 4)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 5)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketCustomApp::temp_motor_filtered() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 6)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 7)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketCustomApp::current_motor() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 8)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 9)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 10)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 11)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketCustomApp::current_in() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 12)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 13)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 14)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 15)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketCustomApp::duty_now() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 16)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 17)));
  return static_cast<double>(v) / 1000.0;
}
double VescPacketCustomApp::rpm() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 18)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 19)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 20)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 21)));
  return static_cast<double>(v);
}
double VescPacketCustomApp::v_in() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 22)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 23)));
  return static_cast<double>(v) / 10.0;
}
double VescPacketCustomApp::amp_hours() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 24)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 25)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 26)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 27)));
  return static_cast<double>(v);
}
double VescPacketCustomApp::amp_hours_charged() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 28)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 29)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 30)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 31)));
  return static_cast<double>(v);
}
double VescPacketCustomApp::watt_hours() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 32)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 33)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 34)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 35)));
  return static_cast<double>(v);
}
double VescPacketCustomApp::watt_hours_charged() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 36)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 37)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 38)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 49)));
  return static_cast<double>(v);
}
double VescPacketCustomApp::tachometer() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 40)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 41)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 42)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 43)));
  return static_cast<double>(v);
}
double VescPacketCustomApp::tachometer_abs() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 44)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 45)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 46)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 47)));
  return static_cast<double>(v);
}
*/
int VescPacketCustomApp::fault_code() const
{
  return static_cast<int32_t>(*(payload_.first + 4));
}
/*
double VescPacketCustomApp::pid_pos_now() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 49)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 50)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 51)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 52)));
  return static_cast<double>(v) / 1000000.0;
}
*/

int VescPacketCustomApp::controller_id() const
{
  return *(payload_.first + 5);
}
double VescPacketCustomApp::enc_rps() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 6)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 7)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 8)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 9)));
  return static_cast<double>(v) / 100000.0;
}
// double VescPacketCustomApp::enc_rad() const
// {
//   int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 57)) << 24) +
//                                    (static_cast<uint32_t>(*(payload_.first + 58)) << 16) +
//                                    (static_cast<uint32_t>(*(payload_.first + 59)) << 8) +
//                                    static_cast<uint32_t>(*(payload_.first + 60)));
//   return static_cast<double>(v) / 100.0;
// }
//191201
double VescPacketCustomApp::current() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 10)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 11)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketCustomApp::duty() const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 12)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 13)));
  return static_cast<double>(v) / 1000.0;
}
// double VescPacketCustomApp::enc_dps() const
// {
//   int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 53)) << 24) +
//                                    (static_cast<uint32_t>(*(payload_.first + 54)) << 16) +
//                                    (static_cast<uint32_t>(*(payload_.first + 55)) << 8) +
//                                    static_cast<uint32_t>(*(payload_.first + 56)));
//   return static_cast<double>(v) / 1000.0;
// }
// double VescPacketCustomApp::enc_deg() const
// {
//   int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 57)) << 24) +
//                                    (static_cast<uint32_t>(*(payload_.first + 58)) << 16) +
//                                    (static_cast<uint32_t>(*(payload_.first + 59)) << 8) +
//                                    static_cast<uint32_t>(*(payload_.first + 60)));
//   return static_cast<double>(v) / 1000.0;
// }
int VescPacketCustomApp::app_status_code() const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 14)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 15)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 16)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 17)));
  return v;
}
int VescPacketCustomApp::send_mode_2() const
{
	return *(payload_.first + 18);
}
int VescPacketCustomApp::can_devs_num() const
{
	return *(payload_.first + 19);
}
// can id => can_m:0, can_s:1~
int VescPacketCustomApp::can_id(int id) const
{
	return *(payload_.first + 20 + (id)*9);
}
// double VescPacketCustomApp::enc_rps_can(int id) const
// {
//   int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 65 + (id)*9)) << 24) +
//                                    (static_cast<uint32_t>(*(payload_.first + 66 + (id)*9)) << 16) +
//                                    (static_cast<uint32_t>(*(payload_.first + 67 + (id)*9)) << 8) +
//                                    static_cast<uint32_t>(*(payload_.first + 68 + (id)*9)));
//   return static_cast<double>(v) / 100000.0;
// }
// double VescPacketCustomApp::enc_rad_can(int id) const
// {
//   int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 69 + (id)*9)) << 24) +
//                                    (static_cast<uint32_t>(*(payload_.first + 70 + (id)*9)) << 16) +
//                                    (static_cast<uint32_t>(*(payload_.first + 71 + (id)*9)) << 8) +
//                                    static_cast<uint32_t>(*(payload_.first + 72 + (id)*9)));
//   return static_cast<double>(v) / 100.0;
// }
//191201
double VescPacketCustomApp::enc_rps_can(int id) const
{
  int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 21 + (id)*9)) << 24) +
                                   (static_cast<uint32_t>(*(payload_.first + 22 + (id)*9)) << 16) +
                                   (static_cast<uint32_t>(*(payload_.first + 23 + (id)*9)) << 8) +
                                   static_cast<uint32_t>(*(payload_.first + 24 + (id)*9)));
  return static_cast<double>(v) / 100000.0;
}
double VescPacketCustomApp::current_can(int id) const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 25 + (id)*9)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 26 + (id)*9)));
  return static_cast<double>(v) / 100.0;
}
double VescPacketCustomApp::duty_can(int id) const
{
  int16_t v = static_cast<int16_t>((static_cast<uint16_t>(*(payload_.first + 27 + (id)*9)) << 8) +
                                   static_cast<uint16_t>(*(payload_.first + 28 + (id)*9)));
  return static_cast<double>(v) / 1000.0;
}
// double VescPacketCustomApp::enc_dps_can(int id) const
// {
//   int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 64 + (id)*9)) << 24) +
//                                    (static_cast<uint32_t>(*(payload_.first + 65 + (id)*9)) << 16) +
//                                    (static_cast<uint32_t>(*(payload_.first + 66 + (id)*9)) << 8) +
//                                    static_cast<uint32_t>(*(payload_.first + 67 + (id)*9)));
//   return static_cast<double>(v) / 1000.0;
// }
// double VescPacketCustomApp::enc_deg_can(int id) const
// {
//   int32_t v = static_cast<int32_t>((static_cast<uint32_t>(*(payload_.first + 68 + (id)*9)) << 24) +
//                                    (static_cast<uint32_t>(*(payload_.first + 69 + (id)*9)) << 16) +
//                                    (static_cast<uint32_t>(*(payload_.first + 70 + (id)*9)) << 8) +
//                                    static_cast<uint32_t>(*(payload_.first + 71 + (id)*9)));
//   return static_cast<double>(v) / 1000.0;
// }

//cdi
#if defined(FW_3_38) || defined(FW_3_40)
REGISTER_PACKET_TYPE(COMM_CUSTOM_APP_DATA, VescPacketCustomApp)
#endif

// Tx Part
// Simple requeset
VescPacketRequestCustomApp::VescPacketRequestCustomApp() :
#if defined(FW_3_38) || defined(FW_3_40)
	VescPacket("RequestCustomApp", 2, COMM_CUSTOM_APP_DATA)
#endif
{
	*(payload_.first + 1) = static_cast<uint8_t>(5);	// model : USB = 5

	VescFrame::CRC crc_calc;
	crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
	uint16_t crc = crc_calc.checksum();
	*(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
	*(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

// Simple requeset + DataSet
VescPacketSetCustomAppData::VescPacketSetCustomAppData(const vesc_msgs::VescSetCustomApp::ConstPtr& custom_set_msg) :
#if defined(FW_3_38) || defined(FW_3_40)
	VescPacket("SetCustomAppData", custom_set_msg->data_bytes + 1, COMM_CUSTOM_APP_DATA)
#endif
{
  int cnt=1;

	*(payload_.first + cnt++) = static_cast<uint8_t>(5);	// model : USB = 5
  *(payload_.first + cnt++) = static_cast<uint8_t>(custom_set_msg->num_of_id);

  for(int i=0; i<custom_set_msg->num_of_id; i++) 
  {
    *(payload_.first + cnt++) = static_cast<uint8_t>(custom_set_msg->id_set[i]);
    *(payload_.first + cnt++) = static_cast<uint8_t>(custom_set_msg->comm_set[i]);

    int32_t v = 0;
    switch(custom_set_msg->comm_set[i]) {
        case COMM_SET_DUTY:
          v = static_cast<int32_t>(custom_set_msg->value_set[i] * 100000.0);
          break;
        case COMM_SET_CURRENT:
          v = static_cast<int32_t>(custom_set_msg->value_set[i] * 1000.0);
          break;
        case COMM_SET_CURRENT_BRAKE:
          v = static_cast<int32_t>(custom_set_msg->value_set[i] * 1000.0);
          break;
        case COMM_SET_RPM:
          v = static_cast<int32_t>(custom_set_msg->value_set[i]);
          break;
        case COMM_SET_POS:
          v = static_cast<int32_t>(custom_set_msg->value_set[i] * 1000000.0);
          break;
        case COMM_SET_DPS:
          v = static_cast<int32_t>(custom_set_msg->value_set[i] * 1000.0);
          break;
        case COMM_SET_GOTO:
          v = static_cast<int32_t>(custom_set_msg->value_set[i] * 1000.0);
          break;
        case COMM_SET_FINDHOME:
          v = static_cast<int32_t>(custom_set_msg->value_set[i] * 1000.0);
          break;
        case COMM_SET_DUTY_PAIR:
          v = static_cast<int32_t>(custom_set_msg->value_set[i]);
          break;
        default:
          v = 0;
          break;
    }
  
    //printf("id=%d, comm_set=%d, value=%d \n", custom_set_msg->id_set[i],custom_set_msg->comm_set[i],  v);

    *(payload_.first + cnt++) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
    *(payload_.first + cnt++) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
    *(payload_.first + cnt++) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
    *(payload_.first + cnt++) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);
  }

	VescFrame::CRC crc_calc;
	crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
	uint16_t crc = crc_calc.checksum();
	*(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
	*(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);

  //printf("cnt=%d, crc checksum=%d\n", cnt, crc);
}

/*------------------------------------------------------------------------------------------------*/

//cdi
VescPacketSetALIVE::VescPacketSetALIVE() :
  VescPacket("SetALIVE", 1, COMM_ALIVE)
{
  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/


VescPacketSetDuty::VescPacketSetDuty(double duty) :
  VescPacket("SetDuty", 5, COMM_SET_DUTY)
{
  /** @todo range check duty */

  int32_t v = static_cast<int32_t>(duty * 100000.0);

  *(payload_.first + 1) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

VescPacketSetDuty::VescPacketSetDuty(double duty, int canf_flag, int can_id) :
  VescPacket("SetDuty", 5, COMM_SET_DUTY, canf_flag, can_id)
{
  int32_t v = static_cast<int32_t>(duty * 100000.0);

  int payload_first_offset = 0;

  if(canf_flag) payload_first_offset = 2;
  else payload_first_offset = 0;

  *(payload_.first + 1 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4 + payload_first_offset) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/

VescPacketSetCurrent::VescPacketSetCurrent(double current) :
  VescPacket("SetCurrent", 5, COMM_SET_CURRENT)
{
  int32_t v = static_cast<int32_t>(current * 1000.0);

  *(payload_.first + 1) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);

#ifdef DEBUG_VIEW_PACKET
  printf("crc checksum=%d\n", crc);
#endif
}

//cdi
VescPacketSetCurrent::VescPacketSetCurrent(double current, int canf_flag, int can_id) :
  VescPacket("SetCurrent", 5, COMM_SET_CURRENT, canf_flag, can_id)
{
  int32_t v = static_cast<int32_t>(current * 1000.0);

  int payload_first_offset = 0;

  if(canf_flag) payload_first_offset = 2;
  else payload_first_offset = 0;

  *(payload_.first + 1 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4 + payload_first_offset) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/

VescPacketSetCurrentBrake::VescPacketSetCurrentBrake(double current_brake) :
  VescPacket("SetCurrentBrake", 5, COMM_SET_CURRENT_BRAKE)
{
  int32_t v = static_cast<int32_t>(current_brake * 1000.0);

  *(payload_.first + 1) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

//cdi
VescPacketSetCurrentBrake::VescPacketSetCurrentBrake(double current_brake, int canf_flag, int can_id) :
  VescPacket("SetCurrentBrake", 5, COMM_SET_CURRENT_BRAKE, canf_flag, can_id)
{
  int32_t v = static_cast<int32_t>(current_brake * 1000.0);

  int payload_first_offset = 0;

    if(canf_flag) payload_first_offset = 2;
    else payload_first_offset = 0;

  *(payload_.first + 1 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4 + payload_first_offset) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/

VescPacketSetRPM::VescPacketSetRPM(double rpm) :
  VescPacket("SetRPM", 5, COMM_SET_RPM)
{
  int32_t v = static_cast<int32_t>(rpm);

  *(payload_.first + 1) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

//cdi
VescPacketSetRPM::VescPacketSetRPM(double rpm, int canf_flag, int can_id) :
  VescPacket("SetRPM", 5, COMM_SET_RPM, canf_flag, can_id)
{
  int32_t v = static_cast<int32_t>(rpm);

  int payload_first_offset = 0;

  if(canf_flag) payload_first_offset = 2;
  else payload_first_offset = 0;

  *(payload_.first + 1 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4 + payload_first_offset) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/

VescPacketSetPos::VescPacketSetPos(double pos) :
  VescPacket("SetPos", 5, COMM_SET_POS)
{
  /** @todo range check pos */

  int32_t v = static_cast<int32_t>(pos * 1000000.0);

  *(payload_.first + 1) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

VescPacketSetPos::VescPacketSetPos(double pos, int canf_flag, int can_id) :
  VescPacket("SetPos", 5, COMM_SET_POS, canf_flag, can_id)
{
  /** @todo range check pos */

  int32_t v = static_cast<int32_t>(pos * 1000000.0);

  int payload_first_offset = 0;

  if(canf_flag) payload_first_offset = 2;
  else payload_first_offset = 0;

  *(payload_.first + 1 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 24) & 0xFF);
  *(payload_.first + 2 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 16) & 0xFF);
  *(payload_.first + 3 + payload_first_offset) = static_cast<uint8_t>((static_cast<uint32_t>(v) >> 8) & 0xFF);
  *(payload_.first + 4 + payload_first_offset) = static_cast<uint8_t>(static_cast<uint32_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/

VescPacketSetServoPos::VescPacketSetServoPos(double servo_pos) :
  VescPacket("SetServoPos", 3, COMM_SET_SERVO_POS)
{
  /** @todo range check pos */

  int16_t v = static_cast<int16_t>(servo_pos * 1000.0);

  *(payload_.first + 1) = static_cast<uint8_t>((static_cast<uint16_t>(v) >> 8) & 0xFF);
  *(payload_.first + 2) = static_cast<uint8_t>(static_cast<uint16_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

VescPacketSetServoPos::VescPacketSetServoPos(double servo_pos, int canf_flag, int can_id) :
  VescPacket("SetServoPos", 3, COMM_SET_SERVO_POS, canf_flag, can_id)
{
  /** @todo range check pos */

  int16_t v = static_cast<int16_t>(servo_pos * 1000.0);

  int payload_first_offset = 0;

  if(canf_flag) payload_first_offset = 2;
  else payload_first_offset = 0;

  *(payload_.first + 1) = static_cast<uint8_t>((static_cast<uint16_t>(v) >> 8) & 0xFF);
  *(payload_.first + 2) = static_cast<uint8_t>(static_cast<uint16_t>(v) & 0xFF);

  VescFrame::CRC crc_calc;
  crc_calc.process_bytes(&(*payload_.first), boost::distance(payload_));
  uint16_t crc = crc_calc.checksum();
  *(frame_->end() - 3) = static_cast<uint8_t>(crc >> 8);
  *(frame_->end() - 2) = static_cast<uint8_t>(crc & 0xFF);
}

/*------------------------------------------------------------------------------------------------*/

// Rx Part
VescPacketCommPrint::VescPacketCommPrint(boost::shared_ptr<VescFrame> raw) :
  VescPacket("CommPrint", raw)
{
}

int VescPacketCommPrint::length() const
{
  return boost::distance(payload_);
}

int VescPacketCommPrint::rxmsg1() const
{
  return *(payload_.first + 1);
}

int VescPacketCommPrint::rxmsg2() const
{
  return *(payload_.first + 2);
}

int VescPacketCommPrint::rxmsg3() const
{
  return *(payload_.first + 3);
}

int VescPacketCommPrint::rxmsg4() const
{
  return *(payload_.first + 4);
}

int VescPacketCommPrint::rxmsg5() const
{
  return *(payload_.first + 5);
}

REGISTER_PACKET_TYPE(COMM_PRINT, VescPacketCommPrint)

/*------------------------------------------------------------------------------------------------*/


} // namespace vesc_driver
