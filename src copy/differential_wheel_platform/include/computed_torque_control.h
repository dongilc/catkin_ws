/*
 * computed_torque_control.h
 *
 *  Created on: Nov 29, 2017
 *      Author: cdi
 */

#ifndef COMPUTED_TORQUE_CONTROL_H_
#define COMPUTED_TORQUE_CONTROL_H_

#include "ros/ros.h"
#include "diff_wheel_platform/CTM_Message.h"

// Declare Variables
#define TO_STRING(var)	#var
#define RAD2DEG			180.0/M_PI  // radian to deg
#define DEG2RAD			M_PI/180.0  // deg to radian
#define RPM2RPS			2*M_PI/60.0 // rpm to rad/sec
#define DPS2RPM			60.0/360.0  // deg/sec to rpm
#define RPM2DPS			360.0/60.0  // rpm to deg/sec

class CTM
{
private:
	//
	double* Dir;	// Wheel Direction Correction
	double* V_dyn;
	double* Motor_Kt;
	double** M_dyn;

	double* rpm;
	double* rps;
	double* rps_lpf;
	double* rad;
	double* vel;
	double* pos;
	double* target_speed;
	double* target_pos;

	ros::NodeHandle nh_;

public:
	int NO_OF_WHEEL;
	int DOF;
	int POLEPAIR;
	double ERPM2RPM;
	double ROW;
	double DCW_X;
	double DCW_Y;
	double DT;
	//
	ros::Publisher ctm_pub;
	diff_wheel_platform::CTM_Message ctm_msg;

	CTM(int number_of_wheel, int degree_of_freedom, int polepair_num, double radius_of_wheel, double dcw_x, double dcw_y, int rate_hz,
			int* dir_vector, double (*inertial_vector)[10], double* friction_vector, double* motor_kt)
	{
		// basic parameters
		NO_OF_WHEEL = number_of_wheel;
		DOF = degree_of_freedom;
		POLEPAIR = polepair_num;
		ERPM2RPM = 1./POLEPAIR;
		ROW = radius_of_wheel;
		DCW_X = dcw_x;
		DCW_Y = dcw_y;
		DT = 1./rate_hz;

		// speed calculation variables
		rpm = new double[NO_OF_WHEEL];
		rps = new double[NO_OF_WHEEL];
		rps_lpf = new double[NO_OF_WHEEL];
		rad = new double[NO_OF_WHEEL];
		vel = new double[DOF];
		pos = new double[DOF];

		// CTM variables
		target_speed = new double[NO_OF_WHEEL];
		target_pos = new double[NO_OF_WHEEL];
		Dir = new double[NO_OF_WHEEL];
		V_dyn = new double[NO_OF_WHEEL];
		Motor_Kt = new double[NO_OF_WHEEL];
		M_dyn = new double*[DOF];
		for(int i=0; i<NO_OF_WHEEL; i++)	M_dyn[i] = new double[DOF];

		for(int i=0; i<NO_OF_WHEEL; i++)	{
			Dir[i] = dir_vector[i];
			V_dyn[i] = friction_vector[i];
			Motor_Kt[i] = motor_kt[i];
			for(int j=0; j<DOF; j++)	M_dyn[i][j] = inertial_vector[i][j];
		}

		//ROS_INFO("M_dyn = [%.3f %.3f]\n", M_dyn[0][0], M_dyn[0][1]);
		//ROS_INFO("        [%.3f %.3f]\n", M_dyn[1][0], M_dyn[1][1]);
		ROS_INFO("CTM Class Constructed");

		// Publisher
		ctm_pub = nh_.advertise<diff_wheel_platform::CTM_Message>("ctm/msgs", 10);
	}

	~CTM() {
		ROS_INFO("CTM Class Destructed");
		delete[] rpm;
		delete[] Dir;	// Wheel Direction Correction
		delete[] V_dyn;
		delete[] Motor_Kt;
		for(int i=0; i<NO_OF_WHEEL; i++)	delete[] M_dyn[i];
		delete[] M_dyn;

		delete[] rpm;
		delete[] rps;
		delete[] rps_lpf;
		delete[] rad;
		delete[] vel;
		delete[] pos;
		delete[] target_speed;
		delete[] target_pos;
	}

	void InitCTM();
	void RunCTM(double *speed, double *current_vel, double *target_vel, double *curr_out, double *kp_ctm, double *kd_ctm);
	double mat_Integral(double in, double out_last);
	double mat_LowpassFilter(double in, double out_last, double hz);
};

#endif
