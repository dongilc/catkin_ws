#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include <ros/ros.h>
#include <state_controller/TwistLabeled.h>
#include <state_controller/BehaviorLib.h>
#include <state_controller/PoseLabeled.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt8.h>
#include <map>

class MainState{
public:
  explicit MainState();
private:
  ros::NodeHandle n;
  ros::Subscriber state_sub;
  ros::Subscriber activate_sub;
  ros::Subscriber behavior_twist_sub;
  ros::Subscriber behavior_hitch_sub;
  ros::Publisher state_pub;
  ros::Publisher command_twist_pub;
  ros::Publisher command_hitch_pub;
  ros::Rate rate;
  std_msgs::String curr_state;

  std::map<std::string, Behavior*> behavior_map;
  bool is_activated;

  void stateCB(const std_msgs::String& msg);
  void activateCB(const std_msgs::Bool& msg);
  void behaviorCBTwist(const state_controller::TwistLabeled& msg);
  void behaviorCBHitch(const state_controller::PoseLabeled& msg);
  void setState(std_msgs::String state);
  void setState(std::string state);
  void addBehavior(std::pair<std::string, std::string> pair);
};

#endif //MAIN_STATE_H
