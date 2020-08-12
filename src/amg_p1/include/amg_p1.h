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
#include "amg_p1/LA_Message.h"			//cdi

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

typedef enum {
   CURRENT_MODE = 0,
   CTM_MODE
} CONTROL_MODE;

typedef enum {
   LQR_MODE = 0,
   MPC_MODE
} MOTION_PLANNER_MODE;

class TeleopVesc
{
public:
	int NO_VESC;
	int NO_DOF;

	int ctm_state;	// 0:ready, 1:init, 2:run, 3:end
	double* erpm;
	double* rps;
	double* rad;
	double* current;
	double* speed;
	double* enc_deg;
	double* dps_target;
	double* dps_now;
	double* deg_now;
	double* deg_total;
	double* deg_total_target;
	double* brake;
	double* vel;
	double* vel_target;
	double* vel_mp_out;
	double* theta_mp_out;

	int joy_cont_mode;
	int motion_planner_mode;	// 0:lqr, 1:mpc

	std_msgs::Bool enable, joy_trigger_init_flag;
	ros::Publisher vesc_cmd_get_customs, vesc_cmd_alive, vesc_cmd_speed, vesc_cmd_current, vesc_cmd_position, vesc_cmd_brake;
	vesc_msgs::VescSetCommand cmd_msg;

	ros::Publisher actuator_deg_pub;
	amg_p1::LA_Message actuator_msg;

	TeleopVesc(const int no_of_vesc, const int no_of_dof, const int default_control_mode, const int default_motion_planner_mode)
	{
		NO_VESC = no_of_vesc;
		NO_DOF = no_of_dof;

		erpm = new double[NO_VESC];
		rps = new double[NO_VESC];
		rad = new double[NO_VESC];
		current = new double[NO_VESC];
		speed = new double[NO_VESC];
		enc_deg = new double[NO_VESC];
		dps_target = new double[NO_VESC];
		dps_now = new double[NO_VESC];
		deg_now = new double[NO_VESC];
		deg_total = new double[NO_VESC];
		deg_total_target = new double[NO_VESC];
		brake = new double[NO_VESC];

		vel = new double[NO_DOF];
		vel_target = new double[NO_DOF];
		vel_mp_out = new double[NO_DOF];
		theta_mp_out = new double[NO_DOF];

		// init
		for(int i=0; i<NO_VESC; i++) {
			erpm[i] = 0.;
			rps[i] = 0.;
			rad[i] = 0.;
			current[i] = 0.;
			speed[i] = 0.;
			enc_deg[i] = 0.;
			dps_target[i] = 0.;
			dps_now[i] = 0.;
			deg_now[i] = 0.;
			deg_total[i] = 0.;
			deg_total_target[i] = 0.;
			brake[i] = 0.;
		}
		for(int i=0; i<NO_DOF; i++) {
			vel[i] = 0.;
			vel_target[i] = 0.;
			vel_mp_out[i] = 0.;
			theta_mp_out[i] = 0.;
		}
		joy_cont_mode = default_control_mode;
		motion_planner_mode = default_motion_planner_mode;

		// Publisher
		vesc_cmd_get_customs = nh_.advertise<std_msgs::Bool>("commands/motor/get_customs", 10);
		vesc_cmd_alive = nh_.advertise<std_msgs::Bool>("commands/motor/alive", 10);
		vesc_cmd_speed = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/speed", 10);
		vesc_cmd_current = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/current", 10);
		vesc_cmd_position = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/position", 10);
		vesc_cmd_brake = nh_.advertise<vesc_msgs::VescSetCommand>("commands/motor/brake", 10);
		actuator_deg_pub = nh_.advertise<amg_p1::LA_Message>("linear_actuator/deg", 10);

		// Subscriber
		joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopVesc::joyCallback, this);
		vesc_sensor_core_ = nh_.subscribe<vesc_msgs::VescStateStamped>("sensors/core", 10, &TeleopVesc::stateCallback, this);
		vesc_sensor_customs_= nh_.subscribe<vesc_msgs::VescGetCustomApp>("sensors/customs", 10, &TeleopVesc::customsCallback, this);
	}

	~TeleopVesc() {
		ROS_INFO("CTM Class Destructed");
		delete[] erpm;
		delete[] rps;
		delete[] rad;
		delete[] current;	// Wheel Direction Correction
		delete[] speed;
		delete[] enc_deg;
		delete[] dps_target;
		delete[] dps_now;
		delete[] deg_now;
		delete[] deg_total;
		delete[] deg_total_target;
		delete[] brake;

		delete[] vel;
		delete[] vel_target;
		delete[] vel_mp_out;
		delete[] theta_mp_out;
	}

	void setCmd(double data, int send_can, int can_id);
	void requestCustoms();
	void setCurrentOut();
	void setSpeedOut();
	void setPositionOut();
	void setPositionTrajOut(const double dt);
	void setPositionTrajOut(double *deg_tot_goal, const double dt);
	double genProfile(double *deg_tacho, double *deg_prof, double *dps_prof, double dps_goal, const double Amax, const double dt);
	void resetDegTotal();
	void getActuatorDegTotalFromRollPitch(double roll_rad, double pitch_rad, double *deg_total);

private:
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
	void stateCallback(const vesc_msgs::VescStateStamped::ConstPtr& state_msg);
	void customsCallback(const vesc_msgs::VescGetCustomApp::ConstPtr& customs_msg);

	ros::NodeHandle nh_;
	ros::Subscriber joy_sub_;
	ros::Subscriber vesc_sensor_core_, vesc_sensor_customs_;
};

#endif
