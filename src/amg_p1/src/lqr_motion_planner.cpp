/*
 * lqr_motion_planner.cpp
 *
 *  Created on: July 15, 2018
 *      Author: cdi
 */

#include "ros/ros.h"
#include "lqr_motion_planner.h"

void LQR_MOTION_PLANNER::Run_LQR_MODEL(double vel_in, double *vel_out, double *th_out)
{
	double dx, dxp, dth, dthp;
	double x_in, v_in;
	double dFc, dTd;

	double kd_t = 0.;
	double kp_t = 0.;
	double g = 9.8;

	dx = state_x[0];
	dxp = state_x[1];
	dth = state_th[0];
	dthp = state_th[1];

	x_in = x_input[0];
	v_in = x_input[1] = vel_in;

	// Control Input
	dFc = k_lqr[0]*(x_in - dx) + k_lqr[1]*(v_in - dxp) + k_lqr[2]*(-dth) + k_lqr[3]*(-dthp);
	dTd = 0;

	// Nonlinear model
	state_x[2] = ( -((Ipzz+mp*powf(lp,2))*dFc+lp*mp*(dTd-(kp_t-g*lp*mp)*dth-kd_t*dthp))/(powf(lp,2)*powf(mp,2)-(mc+mp)*(Ipzz+mp*powf(lp,2))) );
	state_th[2] = ( -(lp*mp*dFc+(mc+mp)*(dTd-(kp_t-g*lp*mp)*dth-kd_t*dthp))/(powf(lp,2)*powf(mp,2)-(mc+mp)*(Ipzz+mp*powf(lp,2))) );

	// integral
	state_x[1] = state_x[1] + state_x[2]*Ts;
	state_th[1] = state_th[1] + state_th[2]*Ts;
	state_x[0] = state_x[0] + state_x[1]*Ts;
	state_th[0] = state_th[0] + state_th[1]*Ts;

	x_input[0] = x_input[0] + v_in*Ts;

	// Out
	*vel_out = dxp;
	*th_out = dth;

	// publishing
	lqr_mp_msg.stamp = ros::Time::now();

	lqr_mp_msg.x.clear();
	lqr_mp_msg.x.push_back(state_x[0]);
	lqr_mp_msg.x.push_back(state_x[1]);
	lqr_mp_msg.x.push_back(state_x[2]);

	lqr_mp_msg.th.clear();
	lqr_mp_msg.th.push_back(state_th[0]);
	lqr_mp_msg.th.push_back(state_th[1]);
	lqr_mp_msg.th.push_back(state_th[2]);

	lqr_mp_msg.x_input.clear();
	lqr_mp_msg.x_input.push_back(x_input[0]);
	lqr_mp_msg.x_input.push_back(x_input[1]);

	lqr_mp_msg.vel_out = dxp;
	lqr_mp_msg.theta_out = dth;
}
