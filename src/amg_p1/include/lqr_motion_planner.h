/*
 * lqr_motion_planner.h
 *
 *  Created on: July 15, 2018
 *      Author: cdi
 */

#ifndef LQR_MOTION_PLANNER_H_
#define LQR_MOTION_PLANNER_H_

#include "ros/ros.h"
#include "amg_p1/MP_Message.h"

class LQR_MOTION_PLANNER
{
private:
	//
	// Model Parameter
	int state_num;
	double mc;
	double mp;
	double lp;
	double Ipzz;
	double Ts;

	double* k_lqr;

	// State Variables
	double* state_x;
	double* state_th;
	double* x_input;	// x_in, dx_in

public:
	//
	ros::NodeHandle nh_;
	ros::Publisher lqr_mp_pub;
	amg_p1::MP_Message lqr_mp_msg;

	LQR_MOTION_PLANNER(int state_number, double m_cart, double m_pend, double l_pend, double I_pend_z, double* lqr_gain, double dt)
	{
		// parameters
		state_num = state_number;
		mc = m_cart;
		mp = m_pend;
		lp = l_pend;
		Ipzz = I_pend_z;
		Ts = dt;
		k_lqr = new double[state_num];
		for(int i=0; i<state_num; i++) k_lqr[i] = lqr_gain[i];

		// states
		state_x = new double[3];
		state_th = new double[3];
		x_input = new double[2];

		// init
		for(int i=0; i<3; i++) {
			state_x[i] = 0.;
			state_th[i] = 0.;
		}
		for(int i=0; i<2; i++) x_input[i] = 0.;
	}

	~LQR_MOTION_PLANNER() {
		delete[] k_lqr;
		delete[] x_input;
		delete[] state_x;
		delete[] state_th;
	}

	void Run_LQR_MODEL(double vel_in, double *vel_out, double *th_out);
};

#endif
