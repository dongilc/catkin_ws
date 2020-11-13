#include <ros/ros.h>

#include "mjvesc_driver.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "mjvesc_driver_node");
  ros::NodeHandle nh;
  ros::NodeHandle private_nh("~");

  vesc_driver::VescDriver vesc_driver(nh, private_nh);

  ros::spin();

  return 0;
}
