/*
 * @file MainState.cpp
 * @author Connor Novak
 * @date 2018-11-13
 *
 * Subscribes to /cmd_behavior, publishes msgs to /cmd_vel based on tractor's
 * current state.
 */

#include "MainState.h"
#include <ros/console.h>  // Used for logging
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/String.h>
#include <vector>

#include <typeinfo>


MainState::MainState()
 : rate(ros::Rate(2))
 , state_sub(n.subscribe("/state_controller/cmd_state", 1, &MainState::MainState::stateCB, this))
 , activate_sub(n.subscribe("/state_controller/cmd_activate", 1, &MainState::MainState::activateCB, this))
 , behavior_twist_sub(n.subscribe("/state_controller/cmd_behavior_twist", 10, &MainState::MainState::behaviorCBTwist, this))
 , behavior_hitch_sub(n.subscribe("/state_controller/cmd_behavior_hitch", 10, &MainState::MainState::behaviorCBHitch, this))
 , state_pub(n.advertise<std_msgs::String>("state", 1))
 , command_twist_pub(n.advertise<geometry_msgs::Twist>("cmd_twist", 1))
 , command_hitch_pub(n.advertise<geometry_msgs::Pose>("cmd_hitch",1))
 , curr_state()
 , is_activated(false)
 , behavior_map(getBehaviorMap(n)) {
   setState("safety");
}

void MainState::stateCB(const std_msgs::String& msg) {
  // Callback for /cmd_state, updates and publishes curr_state
  if (msg.data != curr_state.data) setState(msg);
}

void MainState::activateCB(const std_msgs::Bool& msg) {
  // Callback for /cmd_activate, updates activated state if switch
  if (is_activated != msg.data) is_activated = msg.data;
  else {
    if (is_activated) ROS_WARN("Tractor is already activated");
    else ROS_WARN("Tractor is already disactivated");
    return;
  }
  if (is_activated) ROS_INFO("Activating Tractor");
  else {ROS_INFO("Disactivating Tractor");}
  return;
}

void MainState::behaviorCBTwist(const state_controller::TwistLabeled& msg) {
  // Publishes Twist msg if behavior is currently activated

  // Get priority of behavior sending msg
  auto msg_behavior = behavior_map[msg.label.data];
  auto priority = msg_behavior->getPriority();

  // Estop overwrites Teleop overwrites Bn
  if (priority == 0) setState(msg.label);
  else if (priority == 1 && behavior_map[curr_state.data]->getPriority() != 0) setState(msg.label);

  // Update behavior, publish message
  msg_behavior->setMessage(msg);
  if (msg.label.data == curr_state.data) {
    command_twist_pub.publish(msg.twist);
  }
}

void MainState::behaviorCBHitch(const state_controller::PoseLabeled& msg) {
  // Publishes msg if behavior is currently activated

  // Get priority of behavior sending msg
  auto msg_behavior = behavior_map[msg.label.data];
  auto priority = msg_behavior->getPriority();

  // Estop overwrites Teleop overwrites Bn
  if (priority == 0) setState(msg.label);
  else if (priority == 1 && behavior_map[curr_state.data]->getPriority() != 0) setState(msg.label);
  //
  // Update behavior, publish message
  msg_behavior->setMessage(msg);
  if (msg.label.data == curr_state.data) {
    command_hitch_pub.publish(msg.pose);
  }
}

void MainState::setState(std_msgs::String state) {
  /*! \brief Updates state with new state.
  *
  * @param[in] ROS std_msgs/String, state label
  * setState checks for existence of state, then
  * updates current state with given state, logs info
  * message, publishes new state to /state
  */
  if (curr_state.data != state.data) {
    if (behavior_map.find(state.data) != behavior_map.end()) {
      curr_state = state;
      ROS_INFO("Activating State %s", state.data.c_str());
      state_pub.publish(curr_state);
    } else ROS_WARN("State %s is not loaded to state controller", state.data.c_str());
  }
}

void MainState::setState(std::string state) {
  /*! \brief Updates state with new state.
  *
  * @param[in] string, state label
  * setState checks for existence of state, then
  * updates current state with given state, logs info
  * message, publishes new state to /state
  */
  if (curr_state.data != state) {
    if (behavior_map.find(state) != behavior_map.end()) {
      curr_state.data = state;
      ROS_INFO("Activating State %s", state.c_str());
      state_pub.publish(curr_state);
    } else ROS_WARN("State %s is not loaded to state controller", state.c_str());
  }
}

int main(int argc, char** argv) {

  ros::init(argc, argv, "MainState");
  MainState mainstate;
  ros::spin();
}
