// Generated by gencpp from file vesc_msgs/VescGetCustomApp.msg
// DO NOT EDIT!


#ifndef VESC_MSGS_MESSAGE_VESCGETCUSTOMAPP_H
#define VESC_MSGS_MESSAGE_VESCGETCUSTOMAPP_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace vesc_msgs
{
template <class ContainerAllocator>
struct VescGetCustomApp_
{
  typedef VescGetCustomApp_<ContainerAllocator> Type;

  VescGetCustomApp_()
    : header()
    , send_mode_index1(0)
    , fw_ver_major(0)
    , fw_ver_minor(0)
    , voltage_input(0.0)
    , temperature_pcb(0.0)
    , current_motor(0.0)
    , current_input(0.0)
    , speed(0.0)
    , duty_cycle(0.0)
    , charge_drawn(0.0)
    , charge_regen(0.0)
    , energy_drawn(0.0)
    , energy_regen(0.0)
    , displacement(0.0)
    , distance_traveled(0.0)
    , fault_code(0)
    , pid_pos_now(0.0)
    , enc_rps()
    , enc_rad()
    , app_status_code(0)
    , send_mode_index2(0)
    , can_dev_num(0)
    , can_id()  {
    }
  VescGetCustomApp_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , send_mode_index1(0)
    , fw_ver_major(0)
    , fw_ver_minor(0)
    , voltage_input(0.0)
    , temperature_pcb(0.0)
    , current_motor(0.0)
    , current_input(0.0)
    , speed(0.0)
    , duty_cycle(0.0)
    , charge_drawn(0.0)
    , charge_regen(0.0)
    , energy_drawn(0.0)
    , energy_regen(0.0)
    , displacement(0.0)
    , distance_traveled(0.0)
    , fault_code(0)
    , pid_pos_now(0.0)
    , enc_rps(_alloc)
    , enc_rad(_alloc)
    , app_status_code(0)
    , send_mode_index2(0)
    , can_dev_num(0)
    , can_id(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef int32_t _send_mode_index1_type;
  _send_mode_index1_type send_mode_index1;

   typedef int32_t _fw_ver_major_type;
  _fw_ver_major_type fw_ver_major;

   typedef int32_t _fw_ver_minor_type;
  _fw_ver_minor_type fw_ver_minor;

   typedef double _voltage_input_type;
  _voltage_input_type voltage_input;

   typedef double _temperature_pcb_type;
  _temperature_pcb_type temperature_pcb;

   typedef double _current_motor_type;
  _current_motor_type current_motor;

   typedef double _current_input_type;
  _current_input_type current_input;

   typedef double _speed_type;
  _speed_type speed;

   typedef double _duty_cycle_type;
  _duty_cycle_type duty_cycle;

   typedef double _charge_drawn_type;
  _charge_drawn_type charge_drawn;

   typedef double _charge_regen_type;
  _charge_regen_type charge_regen;

   typedef double _energy_drawn_type;
  _energy_drawn_type energy_drawn;

   typedef double _energy_regen_type;
  _energy_regen_type energy_regen;

   typedef double _displacement_type;
  _displacement_type displacement;

   typedef double _distance_traveled_type;
  _distance_traveled_type distance_traveled;

   typedef int32_t _fault_code_type;
  _fault_code_type fault_code;

   typedef double _pid_pos_now_type;
  _pid_pos_now_type pid_pos_now;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _enc_rps_type;
  _enc_rps_type enc_rps;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _enc_rad_type;
  _enc_rad_type enc_rad;

   typedef int32_t _app_status_code_type;
  _app_status_code_type app_status_code;

   typedef int32_t _send_mode_index2_type;
  _send_mode_index2_type send_mode_index2;

   typedef int32_t _can_dev_num_type;
  _can_dev_num_type can_dev_num;

   typedef std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other >  _can_id_type;
  _can_id_type can_id;





  typedef boost::shared_ptr< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> const> ConstPtr;

}; // struct VescGetCustomApp_

typedef ::vesc_msgs::VescGetCustomApp_<std::allocator<void> > VescGetCustomApp;

typedef boost::shared_ptr< ::vesc_msgs::VescGetCustomApp > VescGetCustomAppPtr;
typedef boost::shared_ptr< ::vesc_msgs::VescGetCustomApp const> VescGetCustomAppConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace vesc_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'vesc_msgs': ['/home/cdi/SynologyDrive/workspace/catkin_ws/src/vesc/vesc_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >
{
  static const char* value()
  {
    return "90215f495cfc9bdca67860d224bb3fe7";
  }

  static const char* value(const ::vesc_msgs::VescGetCustomApp_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x90215f495cfc9bdcULL;
  static const uint64_t static_value2 = 0xa67860d224bb3fe7ULL;
};

template<class ContainerAllocator>
struct DataType< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >
{
  static const char* value()
  {
    return "vesc_msgs/VescGetCustomApp";
  }

  static const char* value(const ::vesc_msgs::VescGetCustomApp_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# VESCuino CDI CUSTOM_APP RX Messages\n"
"\n"
"Header  header\n"
"\n"
"# FW Version Data\n"
"int32 send_mode_index1\n"
"int32 fw_ver_major\n"
"int32 fw_ver_minor\n"
"\n"
"# Original Get Value Data\n"
"float64 voltage_input        # input voltage (volt)\n"
"float64 temperature_pcb      # temperature of printed circuit board (degrees Celsius)\n"
"float64 current_motor        # motor current (ampere)\n"
"float64 current_input        # input current (ampere)\n"
"float64 speed                # motor electrical speed (revolutions per minute) \n"
"float64 duty_cycle           # duty cycle (0 to 1)\n"
"float64 charge_drawn         # electric charge drawn from input (ampere-hour)\n"
"float64 charge_regen         # electric charge regenerated to input (ampere-hour)\n"
"float64 energy_drawn         # energy drawn from input (watt-hour)\n"
"float64 energy_regen         # energy regenerated to input (watt-hour)\n"
"float64 displacement         # net tachometer (counts)\n"
"float64 distance_traveled    # total tachnometer (counts)\n"
"int32   fault_code\n"
"float64 pid_pos_now    		 # pid position now (deg) 0~360\n"
"\n"
"# Raw Encoder Data\n"
"float64[] enc_rps		     # Encoder Read Raw Data (No Delay, rad/sec) \n"
"float64[] enc_rad			 # Encoder Read Raw Data (No Delay, rad)\n"
"int32 app_status_code        # application status code\n"
"\n"
"# CAN Status Data \n"
"int32 send_mode_index2\n"
"int32 can_dev_num\n"
"int32[] can_id\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::vesc_msgs::VescGetCustomApp_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.send_mode_index1);
      stream.next(m.fw_ver_major);
      stream.next(m.fw_ver_minor);
      stream.next(m.voltage_input);
      stream.next(m.temperature_pcb);
      stream.next(m.current_motor);
      stream.next(m.current_input);
      stream.next(m.speed);
      stream.next(m.duty_cycle);
      stream.next(m.charge_drawn);
      stream.next(m.charge_regen);
      stream.next(m.energy_drawn);
      stream.next(m.energy_regen);
      stream.next(m.displacement);
      stream.next(m.distance_traveled);
      stream.next(m.fault_code);
      stream.next(m.pid_pos_now);
      stream.next(m.enc_rps);
      stream.next(m.enc_rad);
      stream.next(m.app_status_code);
      stream.next(m.send_mode_index2);
      stream.next(m.can_dev_num);
      stream.next(m.can_id);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VescGetCustomApp_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::vesc_msgs::VescGetCustomApp_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::vesc_msgs::VescGetCustomApp_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "send_mode_index1: ";
    Printer<int32_t>::stream(s, indent + "  ", v.send_mode_index1);
    s << indent << "fw_ver_major: ";
    Printer<int32_t>::stream(s, indent + "  ", v.fw_ver_major);
    s << indent << "fw_ver_minor: ";
    Printer<int32_t>::stream(s, indent + "  ", v.fw_ver_minor);
    s << indent << "voltage_input: ";
    Printer<double>::stream(s, indent + "  ", v.voltage_input);
    s << indent << "temperature_pcb: ";
    Printer<double>::stream(s, indent + "  ", v.temperature_pcb);
    s << indent << "current_motor: ";
    Printer<double>::stream(s, indent + "  ", v.current_motor);
    s << indent << "current_input: ";
    Printer<double>::stream(s, indent + "  ", v.current_input);
    s << indent << "speed: ";
    Printer<double>::stream(s, indent + "  ", v.speed);
    s << indent << "duty_cycle: ";
    Printer<double>::stream(s, indent + "  ", v.duty_cycle);
    s << indent << "charge_drawn: ";
    Printer<double>::stream(s, indent + "  ", v.charge_drawn);
    s << indent << "charge_regen: ";
    Printer<double>::stream(s, indent + "  ", v.charge_regen);
    s << indent << "energy_drawn: ";
    Printer<double>::stream(s, indent + "  ", v.energy_drawn);
    s << indent << "energy_regen: ";
    Printer<double>::stream(s, indent + "  ", v.energy_regen);
    s << indent << "displacement: ";
    Printer<double>::stream(s, indent + "  ", v.displacement);
    s << indent << "distance_traveled: ";
    Printer<double>::stream(s, indent + "  ", v.distance_traveled);
    s << indent << "fault_code: ";
    Printer<int32_t>::stream(s, indent + "  ", v.fault_code);
    s << indent << "pid_pos_now: ";
    Printer<double>::stream(s, indent + "  ", v.pid_pos_now);
    s << indent << "enc_rps[]" << std::endl;
    for (size_t i = 0; i < v.enc_rps.size(); ++i)
    {
      s << indent << "  enc_rps[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.enc_rps[i]);
    }
    s << indent << "enc_rad[]" << std::endl;
    for (size_t i = 0; i < v.enc_rad.size(); ++i)
    {
      s << indent << "  enc_rad[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.enc_rad[i]);
    }
    s << indent << "app_status_code: ";
    Printer<int32_t>::stream(s, indent + "  ", v.app_status_code);
    s << indent << "send_mode_index2: ";
    Printer<int32_t>::stream(s, indent + "  ", v.send_mode_index2);
    s << indent << "can_dev_num: ";
    Printer<int32_t>::stream(s, indent + "  ", v.can_dev_num);
    s << indent << "can_id[]" << std::endl;
    for (size_t i = 0; i < v.can_id.size(); ++i)
    {
      s << indent << "  can_id[" << i << "]: ";
      Printer<int32_t>::stream(s, indent + "  ", v.can_id[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // VESC_MSGS_MESSAGE_VESCGETCUSTOMAPP_H
