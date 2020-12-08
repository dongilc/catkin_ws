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
#include "sensor_msgs/Imu.h"

class TeleopVesc
{
public:
	int NO_VESC;
	std::string port_name;

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
	double* current_status;
	double* duty_status;
	int*	controller_id;
	int*    custom_cmd_type;
	double* custom_cmd_value;
	int* 	custom_status;
	int* 	last_custom_status;
	int 	app_status_code;
	int 	last_app_status_code;
	int*	led;

	ros::Time startTime;
	std_msgs::Bool enable;
	ros::Publisher vesc_cmd_get_customs, vesc_cmd_set_customs, vesc_cmd_alive, vesc_cmd_speed, vesc_cmd_current, vesc_cmd_duty, vesc_cmd_position, vesc_cmd_brake;
	std_msgs::Bool led_R, led_Y, led_G;
	ros::Publisher odroid_gpio_LED_R, odroid_gpio_LED_Y, odroid_gpio_LED_G, odroid_gpio_FEEDER;
	vesc_msgs::VescSetCommand cmd_msg;
	vesc_msgs::VescSetCustomApp custom_tx_msg;
	std::string topic_name;

	TeleopVesc(const int no_of_vesc, const std::string port)
	{
		NO_VESC = no_of_vesc;
		port_name = port;

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
		current_status = new double[NO_VESC];
		duty_status = new double[NO_VESC];
		controller_id = new int[NO_VESC];
		custom_cmd_type = new int[NO_VESC];
		custom_cmd_value = new double[NO_VESC];
		custom_status = new int[NO_VESC];
		last_custom_status = new int[NO_VESC];
		led = new int[3];

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
			current_status[i] = 0.;
			duty_status[i] = 0.;
			controller_id[i] = 0;
			custom_cmd_type[i] = 0;
			custom_status[i] = 0;
			last_custom_status[i] = 0;
		}
		led[0] = led[1] = led[2] = false;
		led_R.data = led_Y.data = led_G.data = false;

		// Publisher
		topic_name = port + "/commands/motor/get_customs";
		vesc_cmd_get_customs = nh_.advertise<std_msgs::Bool>(topic_name, 10);
		topic_name = port + "/commands/motor/set_customs";
		vesc_cmd_set_customs = nh_.advertise<vesc_msgs::VescSetCustomApp>(topic_name, 10);
		topic_name = port + "/commands/motor/alive";
		vesc_cmd_alive = nh_.advertise<std_msgs::Bool>(topic_name, 10);
		topic_name = port + "/commands/motor/speed";
		vesc_cmd_speed = nh_.advertise<vesc_msgs::VescSetCommand>(topic_name, 10);
		topic_name = port + "/commands/motor/duty_cycle";
		vesc_cmd_duty = nh_.advertise<vesc_msgs::VescSetCommand>(topic_name, 10);
		topic_name = port + "/commands/motor/current";
		vesc_cmd_current = nh_.advertise<vesc_msgs::VescSetCommand>(topic_name, 10);
		topic_name = port + "/commands/motor/position";
		vesc_cmd_position = nh_.advertise<vesc_msgs::VescSetCommand>(topic_name, 10);
		topic_name = port + "/commands/motor/brake";
		vesc_cmd_brake = nh_.advertise<vesc_msgs::VescSetCommand>(topic_name, 10);
		//
		odroid_gpio_LED_R = nh_.advertise<std_msgs::Bool>("led_red", 10);
		odroid_gpio_LED_Y = nh_.advertise<std_msgs::Bool>("led_yellow", 10);
		odroid_gpio_LED_G = nh_.advertise<std_msgs::Bool>("led_green", 10);
		odroid_gpio_FEEDER = nh_.advertise<std_msgs::Bool>("feeder", 10);

		// Subscriber
		topic_name = port + "/sensors/core";
		vesc_sensor_core_ = nh_.subscribe<vesc_msgs::VescStateStamped>(topic_name, 10, &TeleopVesc::stateCallback, this);
		topic_name = port + "/sensors/customs";
		vesc_sensor_customs_= nh_.subscribe<vesc_msgs::VescGetCustomApp>(topic_name, 10, &TeleopVesc::customsCallback, this);
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
		delete[] current_status;
		delete[] duty_status;
		delete[] controller_id;
		delete[] custom_cmd_type;
		delete[] custom_cmd_value;
		delete[] custom_status;
		delete[] last_custom_status;
		delete[] led;
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
	void LEDToggleRED(int flag);
	void LEDToggleGreen(int flag);

private:
	void stateCallback(const vesc_msgs::VescStateStamped::ConstPtr& state_msg);
	void customsCallback(const vesc_msgs::VescGetCustomApp::ConstPtr& custom_rx_msg);

	ros::NodeHandle nh_;
	ros::Subscriber vesc_sensor_core_, vesc_sensor_customs_;
};

//
class TeleopInput
{
public:
	TeleopVesc *vh1_, *vh2_, *vh3_;
	double launcher_incline_angle;

	TeleopInput(TeleopVesc *p_vesc1, TeleopVesc *p_vesc2, TeleopVesc *p_vesc3)
	{	
		vh1_ = p_vesc1;
		vh2_ = p_vesc2;
		vh3_ = p_vesc3;
		joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopInput::joyCallback, this);
		keyboard_input_ = nh_.subscribe<geometry_msgs::Twist>("cmd_vel", 10, &TeleopInput::keyboardCallback, this);
		imu_data = nh_.subscribe<sensor_msgs::Imu>("imu", 1000, &TeleopInput::imuDataCallback, this);
	}

private:
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
	void keyboardCallback(const geometry_msgs::Twist::ConstPtr& cmd_vel);
	void imuDataCallback(const sensor_msgs::Imu::ConstPtr& msg);

	ros::NodeHandle nh_;
	ros::Subscriber joy_sub_, keyboard_input_, imu_data;
};

class TrapezoidalVelProfile
{
public:
	float Amax;
	float dt;

	TrapezoidalVelProfile(float Acc_maximum, float DT)
	{
		Amax = Acc_maximum;
		dt = DT;
	}
	void GenProfile(float v_ref, float *v_now);

private:
};

#endif
