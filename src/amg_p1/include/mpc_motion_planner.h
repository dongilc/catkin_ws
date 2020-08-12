/*
 * mpc_motion_planner.h
 *
 *  Created on: July 15, 2018
 *      Author: cdi
 */

#ifndef MPC_MOTION_PLANNER_H_
#define MPC_MOTION_PLANNER_H_

#include "ros/ros.h"
#include "amg_p1/MP_Message.h"

class MPC_MOTION_PLANNER
{
private:
	//
	// Model Parameter
	int state_num;
	double** Ap;
	double* Bp;
	double* Cp;
	double* k_mpc;
	double* k_y;

	int Np;
	int Nc;
	int rw;
	int rate_hz;

	// states
	double *xm;
	double *xm_old;
	double *delta_xm;
	double *Ap_xm;
	double *Bp_u;
	double *Xf;
	double *r;
	double u_mpc;

public:
	//
	ros::NodeHandle nh_;
	ros::Publisher mpc_mp_pub;
	amg_p1::MP_Message mpc_mp_msg;

	MPC_MOTION_PLANNER(int state_num_, double (*Ap_)[10], double* Bp_, double* Cp_,
			int Np_, int Nc_, int rw_, int rate_hz_,
			double* k_mpc_, double* k_y_)
	{
		// param
		state_num = state_num_;
		Ap = new double*[state_num];
		for(int i=0; i<state_num; i++)	Ap[i] = new double[state_num];
		Bp = new double[state_num];
		Cp = new double[state_num];
		for(int i=0; i<state_num; i++) {
			for(int j=0; j<state_num; j++)	Ap[i][j] = Ap_[i][j];
			Bp[i] = Bp_[i];
			Cp[i] = Cp_[i];
		}

		Np = Np_;
		Nc = Nc_;
		rw = rw_;
		rate_hz = rate_hz_;

		k_mpc = new double[state_num+1];
		for(int i=0; i<(state_num+1); i++)	k_mpc[i] = k_mpc_[i];
		k_y = new double[Np];
		for(int i=0; i<Np; i++)	k_y[i] = k_y_[i];

		// states
		xm = new double[state_num];
		xm_old = new double[state_num];
		delta_xm = new double[state_num];
		Ap_xm = new double[state_num];
		Bp_u = new double[state_num];
		Xf = new double[state_num+1];
		r = new double[Np];

		// init
		for(int i=0; i<state_num; i++) {
			xm[i] = 0.;
			xm_old[i] = 0.;
			delta_xm[i] = 0.;
			Ap_xm[i] = 0.;
			Bp_u[i] = 0.;
		}
		for(int i=0; i<(state_num+1); i++) Xf[i] = 0.;
		for(int i=0; i<Np; i++)	r[i] = 0.;
		u_mpc = 0;
	}

	~MPC_MOTION_PLANNER() {
		for(int i=0; i<state_num; i++)	delete[] Ap[i];
		delete[] Ap;
		delete[] Bp;
		delete[] Cp;
		delete[] k_mpc;
		delete[] k_y;
	}

	void Run_MPC_MODEL(double vel_in, double *vel_out, double *th_out);
	void pushback_vector(double *a, double b, int row);
	void copy_vector(double *a, double *b, int row);
	void multiply_matrix_and_vector(double **a, double *b, double *c, int row, int column);
	void multiply_vector_and_vector(double *a, double *b, double *c, int row);
	void multiply_vector_and_num(double *a, double b, double *c, int row);
	void sum_two_vectors(double *a, double *b, double *c, int row);
	void substract_two_vectors(double *a, double *b, double *c, int row);
	void merge_vector_and_number(double *a, double b, double *c, int row);
};

#endif
