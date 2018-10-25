/*
 * computed_torque_control.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: cdi
 */

#include "ros/ros.h"
#include "computed_torque_control.h"

void CTM::RunCTM(double *erpm, double *current_vel, double *target_vel, double *curr_out, double *kp_ctm, double *kd_ctm)
{
	bool print_ros_info = false;

	for(int i=0; i<NO_OF_WHEEL; i++) {
		rpm[i] = Dir[i]*erpm[i]*ERPM2RPM;			// Calculate rpm. erpm to rpm
		rps[i] = rpm[i]*RPM2RPS;					// Calculate velocity(rad/sec). rpm to rad/sec
		rps_lpf[i] = mat_LowpassFilter(rps[i], rps_lpf[i], 15.0);	// Calculate velocity lowpass filter
		rad[i] = mat_Integral(rps[i], rad[i]);	// Calculate position(rad)

		//if(print_ros_info) ROS_INFO("%d - rotational vel:%.3f, rotational pos:%.3f", i, rps[i], rad[i]);
		//if(print_ros_info) ROS_INFO("%d - rotational vel:%.3f, rotational vel_lpf:%.3f", i, rps[i], rps_lpf[i]);
	}

	// Calculate Task space velocity:vx(m/s), wz(rad/s) / position:x(m), z(rad)
	current_vel[0] = vel[0] = ROW/2.*(rps[0] + rps[1]);
	current_vel[1] = vel[1] = ROW/2./(DCW_X+DCW_Y)*(-rps[0] + rps[1]);
	pos[0] = ROW/2.*(rad[0] + rad[1]);
	pos[1] = ROW/2./(DCW_X+DCW_Y)*(-rad[0] + rad[1]);
	if(print_ros_info) ROS_INFO("forward vel:%.3f, pos:%.3f / rotational vel:%.3f, pos:%.3f", vel[0], pos[0], vel[1], pos[1]);

	// variables
	double thddot_cp[NO_OF_WHEEL];
	double T_M_dyn[NO_OF_WHEEL];
	double T_V_dyn[NO_OF_WHEEL];
	double T_SUM[NO_OF_WHEEL];

	// Target values
    target_pos[0] = mat_Integral(target_vel[0], target_pos[0]);
	target_pos[1] = mat_Integral(target_vel[1], target_pos[1]);

	// thetaddot_cp calculation
	thddot_cp[0] = kd_ctm[0]*(target_vel[0] - vel[0]) + kp_ctm[0]*(target_pos[0] - pos[0]);	// x term
	thddot_cp[1] = kd_ctm[1]*(target_vel[1] - vel[1]) + kp_ctm[1]*(target_pos[1] - pos[1]);	// delta term
	if(print_ros_info)
		ROS_INFO("target vel. - for:%.3f (m/s), rot:%.3f (dps)", target_vel[0], target_vel[1]*RAD2DEG);
	if(print_ros_info)
		ROS_INFO("target pos. - for:%.3f (m), rot:%.3f (deg)", target_pos[0], target_pos[1]*RAD2DEG);

	// torque inertia term
	T_M_dyn[0] = M_dyn[0][0]*thddot_cp[0] + M_dyn[0][1]*thddot_cp[1];
	T_M_dyn[1] = M_dyn[1][0]*thddot_cp[0] + M_dyn[1][1]*thddot_cp[1];
	if(print_ros_info) ROS_INFO("torque inertia term - left:%.3f, right:%.3f", T_M_dyn[0], T_M_dyn[1]);

	// torque feed-forward due to viscous friction - only considered viscous friction on wheel (BL*wL, BR*wR)
	T_V_dyn[0] = V_dyn[0]*rps[0];
	T_V_dyn[1] = V_dyn[1]*rps[1];
	if(print_ros_info) ROS_INFO("torque friction term - left:%.3f, right:%.3f", T_V_dyn[0], T_V_dyn[1]);

	// torque out
	T_SUM[0] = T_M_dyn[0] + T_V_dyn[0];
	T_SUM[1] = T_M_dyn[1] + T_V_dyn[1];
	if(print_ros_info) ROS_INFO("torque sum - left:%.3f, right:%.3f", T_SUM[0], T_SUM[1]);

	// control current out
	curr_out[0] = Dir[0]*T_SUM[0]/Motor_Kt[0];
	curr_out[1] = Dir[1]*T_SUM[1]/Motor_Kt[1];
	if(print_ros_info) ROS_INFO("curr_out - left:%.3f, right:%.3f", curr_out[0], curr_out[1]);
	if(print_ros_info) ROS_INFO("-----------------------------------------------------------");

	// ROS Publish
	ctm_msg.stamp = ros::Time::now();
	ctm_msg.target_vel.clear();
	ctm_msg.target_vel.push_back(target_vel[0]);
	ctm_msg.target_vel.push_back(target_vel[1]);
	ctm_msg.current_vel.clear();
	ctm_msg.current_vel.push_back(vel[0]);
	ctm_msg.current_vel.push_back(vel[1]);
	ctm_msg.target_pos.clear();
	ctm_msg.target_pos.push_back(target_pos[0]);
	ctm_msg.target_pos.push_back(target_pos[1]);
	ctm_msg.current_pos.clear();
	ctm_msg.current_pos.push_back(pos[0]);
	ctm_msg.current_pos.push_back(pos[1]);
	ctm_pub.publish(ctm_msg);
}

void CTM::InitCTM()
{
	for(int i=0; i<NO_OF_WHEEL; i++) {
		rpm[i] = 0.;
		rps[i] = 0.;
		rps_lpf[i] = 0.;
		rad[i] = 0.;
	}

	for(int i=0; i<DOF; i++) {
		vel[i] = 0.;
		pos[i] = 0.;
		target_pos[i] = target_speed[i] = 0.;
	}
}

double CTM::mat_Integral(double in, double out_last)
{
	double out;
	out = out_last + in*DT;

	return out;
}

double CTM::mat_LowpassFilter(double in, double out_last, double hz)
{
	double out_lpf;
	out_lpf = (out_last + DT*(double)2.0f*(double)M_PI*hz*in)/((double)1.0 + DT*(double)2.0f*(double)M_PI*hz);

	return out_lpf;
}
