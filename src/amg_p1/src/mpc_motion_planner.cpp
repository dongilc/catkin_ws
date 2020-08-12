/*
 * mpc_motion_planner.cpp
 *
 *  Created on: July 15, 2018
 *      Author: cdi
 */

#include "ros/ros.h"
#include "mpc_motion_planner.h"

void MPC_MOTION_PLANNER::Run_MPC_MODEL(double vel_in, double *vel_out, double *th_out)
{
	double y;
	double delta_u_ff;
	double delta_u_fb;
	double delta_u;

	// Control Input
	pushback_vector(r, vel_in, Np);								// r = vx_in
	multiply_vector_and_vector(k_y, r, &delta_u_ff, Np);	// delta_u_ff = K_y*r
	multiply_vector_and_vector(k_mpc, Xf, &delta_u_fb, 5);	// delta_u_fb = k_mpc*Xf
	delta_u = delta_u_ff - delta_u_fb;
	u_mpc += delta_u;

	// MPC model
	copy_vector(xm_old, xm, state_num);									// xm_old = xm;
	multiply_matrix_and_vector(Ap, xm, Ap_xm, state_num, state_num);	// Ap_xm = Ap*xm
	multiply_vector_and_num(Bp, u_mpc, Bp_u, state_num);				// Bp_u = Bp*u_mpc;
	sum_two_vectors(Ap_xm, Bp_u, xm, state_num);						// xm = Ap_xm + Bp_u;
	multiply_vector_and_vector(Cp, xm, &y, state_num);					// y = Cp*xm;
	substract_two_vectors(xm, xm_old, delta_xm, state_num);				// delta_xm = xm - xm_old;
	merge_vector_and_number(delta_xm, y, Xf, 5);						// Xf = [delta_xm; y];

	// Out
	*vel_out = xm[1];	// x_dot
	*th_out = xm[2];	// theta

	// publishing
	mpc_mp_msg.stamp = ros::Time::now();

	mpc_mp_msg.x.clear();
	mpc_mp_msg.x.push_back(xm[0]);
	mpc_mp_msg.x.push_back(xm[1]);

	mpc_mp_msg.th.clear();
	mpc_mp_msg.th.push_back(xm[2]);
	mpc_mp_msg.th.push_back(xm[3]);

	mpc_mp_msg.x_input.clear();
	mpc_mp_msg.x_input.push_back(vel_in);

	mpc_mp_msg.vel_out = xm[1];
	mpc_mp_msg.theta_out = xm[2];
}

void MPC_MOTION_PLANNER::pushback_vector(double *a, double b, int row)
{
	double temp[row];

	// 1. copy
	for(int i=0; i<row; i++)
	{
		temp[i] = a[i];
	}

	// 2. fifo pushback
	for(int i=0; i<(row-1); i++)
	{
		a[i] = temp[i+1];
	}
	a[row-1] = b;
}

void MPC_MOTION_PLANNER::copy_vector(double *a, double *b, int row)
{
	for(int i=0; i<row; i++)
	{
		a[i] = b[i];
	}
}

void MPC_MOTION_PLANNER::multiply_matrix_and_vector(double **a, double *b, double *c, int row, int column)
{
	for(int i=0; i<row; i++)
	{
		c[i] = 0;

		for(int j=0; j<column; j++)
		{
			c[i] += a[i][j]*b[j];
		}
	}
}

void MPC_MOTION_PLANNER::multiply_vector_and_vector(double *a, double *b, double *c, int row)
{
	*c = 0;

	for(int i=0; i<row; i++)
	{
		*c += a[i]*b[i];
	}
}

void MPC_MOTION_PLANNER::multiply_vector_and_num(double *a, double b, double *c, int row)
{
	for(int i=0; i<row; i++)
	{
		c[i] = a[i]*b;
	}
}

void MPC_MOTION_PLANNER::sum_two_vectors(double *a, double *b, double *c, int row)
{
	for(int i=0; i<row; i++)
	{
		c[i] = a[i] + b[i];
	}
}

void MPC_MOTION_PLANNER::substract_two_vectors(double *a, double *b, double *c, int row)
{
	for(int i=0; i<row; i++)
	{
		c[i] = a[i] - b[i];
	}
}

void MPC_MOTION_PLANNER::merge_vector_and_number(double *a, double b, double *c, int row)
{
	for(int i=0; i<(row-1); i++)
	{
		c[i] = a[i];
	}

	c[row-1] = b;
}
