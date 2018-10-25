/*
 * amg_p1.h
 *
 *  Created on: Jan 12, 2018
 *      Author: cdi
 */

#ifndef AMG_P1_H_
#define AMG_P1_H_

#include "ros/ros.h"
#include <std_msgs/Bool.h>
#include <sensor_msgs/Joy.h>
#include "vesc_msgs/VescSetCommand.h"	//cdi
//#include "vesc_msgs/VescGetSpeeds.h"	//cdi
#include "vesc_msgs/VescStateStamped.h"	//cdi
#include "vesc_msgs/VescGetCustomApp.h"	//cdi
#include "vesc_msgs/VescSetCustomApp.h"	//cdi

//#define PRINT_SENSOR_CORE
//#define PRINT_SENSOR_CUSTOMS

// Joystick, Joy Axis Index
typedef enum {
   JL_Y = 0,
   JL_X,
   LT,
   JR_Y,
   JR_X,
   RT,
   BT_LR,
   BT_UD
} JOY_AXIS;

// Joystick, Joy Button Index
typedef enum {
   BT_A = 0,
   BT_B,
   BT_X,
   BT_Y,
   LB,
   RB,
   BACK,
   START,
   POWER,
   STICK_L,
   STICK_R
} JOY_BUTTON;

class TeleopVesc
{
public:
	int NO_VESC;
	int NO_DOF;

	int ctm_state;	// 0:ready, 1:init, 2:run, 3:end
	double* erpm;
	double* vel;
	double* target_vel;
	double* current;
	double* speed;
	double* brake;

	TeleopVesc(int no_of_vesc, int no_of_dof)
	{
		NO_VESC = no_of_vesc;
		NO_DOF = no_of_dof;

		erpm = new double[NO_VESC];
		vel = new double[NO_DOF];
		target_vel = new double[NO_DOF];
		current = new double[NO_VESC];
		speed = new double[NO_VESC];
		brake = new double[NO_VESC];

		// Publisher
		vesc_cmd_get_customs = nh_.advertise<std_msgs::Bool>("commands/motor/get_customs", 10);
		vesc_cmd_alive = nh_.advertise<std_msgs::Bool>("commands/motor/alive", 10);
		vesc_cmd_speed = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/speed", 10);
		vesc_cmd_current = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/current", 10);
		vesc_cmd_brake = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/brake", 10);

		// Subscriber
		joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopVesc::joyCallback, this);
		vesc_sensor_core_ = nh_.subscribe<vesc_msgs::VescStateStamped>("sensors/core", 10, &TeleopVesc::stateCallback, this);
		vesc_sensor_customs_= nh_.subscribe<vesc_msgs::VescGetCustomApp>("sensors/customs", 10, &TeleopVesc::customsCallback, this);
	}

	int joy_cont_mode;

	std_msgs::Bool enable, cruise;
	ros::Publisher vesc_cmd_get_customs, vesc_cmd_alive, vesc_cmd_speed, vesc_cmd_current, vesc_cmd_brake;
	vesc_msgs::VescSetCommand cmd_msg;

	void setCmd(double data, int send_can, int can_id);
	void requestCustoms();
	void setCurrentOut();
	void setSpeedOut();

private:
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
	void stateCallback(const vesc_msgs::VescStateStamped::ConstPtr& state_msg);
	void customsCallback(const vesc_msgs::VescGetCustomApp::ConstPtr& customs_msg);

	ros::NodeHandle nh_;
	ros::Subscriber joy_sub_;
	ros::Subscriber vesc_sensor_core_, vesc_sensor_customs_;
};

#endif
