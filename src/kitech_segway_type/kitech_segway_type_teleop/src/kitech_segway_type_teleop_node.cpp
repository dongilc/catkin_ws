/*
 * kitech_segway_type_teleop_node.cpp
 *
 *  Created on: July 30, 2019
 *      Author: cdi
 */

#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/Imu.h>

/*
// Xbox360 wireless
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
*/

// Joystick, Joy Axis Index
typedef enum {
   JL_Y = 0,
   JL_X,
   JR_Y,
   JR_X,
   BT_LR,
   BT_UD
} JOY_AXIS_LOGITECH_F710;

// Joystick, Joy Button Index
typedef enum {
   BT_X = 0,
   BT_A,
   BT_B,
   BT_Y,
   LB,
   RB,
   LT,
   RT,
   BACK,
   START,
   STICK_L,
   STICK_R
} JOY_BUTTON_LOGITECH_F710;

// Global Variables
float speed[2];

double body_vel_x;
double imu_angle_y, imu_angular_vel_y;
double u_lqr;

void joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	double joy_cmd_left_X, joy_cmd_right_X;

	// xbox initial value ignore
	std_msgs::Header jh = joy->header;
	if(jh.seq<10) {
		joy_cmd_left_X = 0;
		joy_cmd_right_X = 0;
	}
	else {
		joy_cmd_left_X = (joy->axes[JL_X]);
		joy_cmd_right_X = (joy->axes[JR_X]);
	}

	speed[0] = 5.0*joy_cmd_left_X;
	speed[1] = 5.0*joy_cmd_right_X;
}

void imuCallback(const sensor_msgs::Imu::ConstPtr& imu)
{
	// xbox initial value ignore
	std_msgs::Header jh = imu->header;
	if(jh.seq<10) {
		imu_angle_y = 0;
		imu_angular_vel_y = 0;
	}
	else {
		imu_angle_y = imu->orientation.y;
		imu_angular_vel_y = imu->angular_velocity.y;
	}
	//ROS_INFO("%.3f %.3f",imu_angle_y,imu_angular_vel_y);
}

void bodyVelCallback(const std_msgs::Float32 value)
{
	body_vel_x = value.data;
	//ROS_INFO("%.3f",body_vel_x);
}

/*
 * Main Function
 * 
 */
int main(int argc, char **argv)            
{
	ros::init(argc, argv, "kitech_segway_type_teleop_node");

	// ros
	ros::NodeHandle nh_;
	ros::Publisher  vel_cmd_left_, vel_cmd_right_;
	ros::Subscriber joy_sub_, imu_sub_, body_vel_sub_;

	// Publisher
	vel_cmd_left_ = nh_.advertise<std_msgs::Float32>("/leftMotorCmd", 10);
	vel_cmd_right_ = nh_.advertise<std_msgs::Float32>("/rightMotorCmd", 10);

	// Subscriber
	joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &joyCallback);
	imu_sub_ = nh_.subscribe<sensor_msgs::Imu>("vrep/imu", 10, &imuCallback);
	body_vel_sub_ = nh_.subscribe<std_msgs::Float32>("bodyVel", 10, &bodyVelCallback);

	std_msgs::Float32 vel_cmd;

	// loop freq
	int rate_hz = 100;	//hz

	// ROS Loop
	int cnt_loop = 0;
	ros::Rate loop_rate(rate_hz); //Hz
	ROS_INFO("Start Tele-operation");
	while (ros::ok())
	{
		//ROS_INFO("%.3f %.3f",speed[0],speed[1]);
		u_lqr = (1*body_vel_x + 10*imu_angle_y + 2*imu_angular_vel_y);
		//speed[0] = speed[1] = u_lqr;

		vel_cmd.data = speed[0];
		vel_cmd_left_.publish(vel_cmd);
		vel_cmd.data = speed[1];
		vel_cmd_right_.publish(vel_cmd);

		ros::spinOnce();
		loop_rate.sleep();
		cnt_loop++;
	}

	return 0;
}
