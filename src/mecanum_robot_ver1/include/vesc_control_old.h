/*
 * vesc_control.h
 *
 *  Created on: Jan 12, 2018
 *      Author: cdi
 */

#ifndef VESC_CONTROL_H_
#define VESC_CONTROL_H_

#include "ros/ros.h"
#include <std_msgs/Bool.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include "vesc_msgs/VescSetCommand.h"	//cdi
#include "vesc_msgs/VescStateStamped.h"	//cdi
#include "vesc_msgs/VescGetCustomApp.h"	//cdi
#include "vesc_msgs/VescSetCustomApp.h"	//cdi

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

	int ctm_state;	// 0:ready, 1:init, 2:run, 3:end
	double* erpm;
	double* rps;
	double* rad;
	double* current;
	double* speed;
	double* dps;
	double* duty;
	double* position;
	double* enc_deg;
	double* brake;
	int*    custom_cmd_type;
	double* custom_cmd_value;

	ros::Time startTime;
	std_msgs::Bool enable;
	ros::Publisher vesc_cmd_get_customs, vesc_cmd_set_customs, vesc_cmd_alive, vesc_cmd_speed, vesc_cmd_current, vesc_cmd_duty, vesc_cmd_position, vesc_cmd_brake;
	vesc_msgs::VescSetCommand cmd_msg;
	vesc_msgs::VescSetCustomApp custom_tx_msg;

	TeleopVesc(const int no_of_vesc)
	{
		NO_VESC = no_of_vesc;

		erpm = new double[NO_VESC];
		rps = new double[NO_VESC];
		rad = new double[NO_VESC];
		current = new double[NO_VESC];
		speed = new double[NO_VESC];
		dps = new double[NO_VESC];
		duty = new double[NO_VESC];
		position = new double[NO_VESC];
		enc_deg = new double[NO_VESC];
		brake = new double[NO_VESC];
		custom_cmd_type = new int[NO_VESC];
		custom_cmd_value = new double[NO_VESC];

		// init
		for(int i=0; i<NO_VESC; i++) {
			erpm[i] = 0.;
			rps[i] = 0.;
			rad[i] = 0.;
			current[i] = 0.;
			speed[i] = 0.;
			dps[i] = 0.;
			duty[i] = 0.;
			position[i] = 0.;
			enc_deg[i] = 0.;
			brake[i] = 0.;
			custom_cmd_type[i] = 0.;
			custom_cmd_value[i] = 0.;
		}

		// Publisher
		vesc_cmd_get_customs = nh_.advertise<std_msgs::Bool>("commands/motor/get_customs", 10);
		vesc_cmd_set_customs = nh_.advertise<vesc_msgs::VescSetCustomApp>("commands/motor/set_customs", 10);
		vesc_cmd_alive = nh_.advertise<std_msgs::Bool>("commands/motor/alive", 10);
		vesc_cmd_speed = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/speed", 10);
		vesc_cmd_duty = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/duty_cycle", 10);
		vesc_cmd_current = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/current", 10);
		vesc_cmd_position = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/position", 10);
		vesc_cmd_brake = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/brake", 10);

		// Subscriber
		vesc_sensor_core_ = nh_.subscribe<vesc_msgs::VescStateStamped>("sensors/core", 10, &TeleopVesc::stateCallback, this);
		vesc_sensor_customs_= nh_.subscribe<vesc_msgs::VescGetCustomApp>("sensors/customs", 10, &TeleopVesc::customsCallback, this);
		vesc_keyboard_input_ = nh_.subscribe<geometry_msgs::Twist>("cmd_vel", 10, &TeleopVesc::keyboardCallback, this);
		joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopVesc::joyCallback, this);
	}

	~TeleopVesc() {
		delete[] erpm;
		delete[] rps;
		delete[] rad;
		delete[] current;
		delete[] speed;
		delete[] dps;
		delete[] duty;
		delete[] position;
		delete[] enc_deg;
		delete[] brake;
		delete[] custom_cmd_type;
		delete[] custom_cmd_value;
	}

	void setCmdMsg(double data, int send_can, int can_id);
	void setCustomMsg(int can_id, int send_can, int cmd_type, double data);
	void requestCustoms();
	void setCustomOut();
	void setCurrentOut();
	void setBrakeOut();
	void setDutyCycleOut();
	void setSpeedOut();
	void setPositionOut();

private:
	void stateCallback(const vesc_msgs::VescStateStamped::ConstPtr& state_msg);
	void customsCallback(const vesc_msgs::VescGetCustomApp::ConstPtr& custom_rx_msg);
	void keyboardCallback(const geometry_msgs::Twist::ConstPtr& cmd_vel);
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

	ros::NodeHandle nh_;
	ros::Subscriber joy_sub_;
	ros::Subscriber vesc_sensor_core_, vesc_sensor_customs_, vesc_keyboard_input_;
};

#endif
