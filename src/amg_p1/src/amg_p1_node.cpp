/*
 * amg_p1_node.h
 *
 *  Created on: Jan 12, 2018
 *      Author: cdi
 */

#include "amg_p1.h"
#include "computed_torque_control.h"
#include "lqr_motion_planner.h"
#include "mpc_motion_planner.h"

// Settings
#define VESC_ID_LEFT_WHEEL		0
#define VESC_ID_RIGHT_WHEEL		1
#define VESC_ID_LEFT_ACT		2
#define VESC_ID_RIGHT_ACT		3
#define CAN_FORWARD_OFF			0
#define CAN_FORWARD_ON			1
#define BRAKE_CURRENT			10.
#define BRAKE_THRESHOLD			8.	// bigger than (BRAKE_CURRENT/2)

//#define PRINT_SENSOR_CORE
//#define PRINT_SENSOR_CUSTOMS

void TeleopVesc::customsCallback(const vesc_msgs::VescGetCustomApp::ConstPtr& custom_msg)
{
#ifdef PRINT_SENSOR_CUSTOMS
	ROS_INFO("------------------------------------------");
	ROS_INFO("header:%6.4f", custom_msg->header.stamp.toSec());
	ROS_INFO("voltage input:%.2f V", custom_msg->voltage_input);
	ROS_INFO("temperature pcb:%.2f C", custom_msg->temperature_pcb);
	ROS_INFO("current motor:%.2f A", custom_msg->current_motor);
	ROS_INFO("current input:%.2f A", custom_msg->current_input);
	ROS_INFO("erpm:%.2f", custom_msg->speed);
	ROS_INFO("duty:%.2f", custom_msg->duty_cycle);
	ROS_INFO("amp_hours:%.2f", custom_msg->charge_drawn);
	ROS_INFO("amp_hours_charged:%.2f", custom_msg->charge_regen);
	ROS_INFO("watt_hours:%.2f", custom_msg->energy_drawn);
	ROS_INFO("watt_hours_charged:%.2f", custom_msg->energy_regen);
	ROS_INFO("tachometer:%.2f", custom_msg->displacement);
	ROS_INFO("tachometer_abs:%.2f", custom_msg->distance_traveled);
	ROS_INFO("fault code:%d", custom_msg->fault_code);
	ROS_INFO("pid_pos_now:%.2f", custom_msg->pid_pos_now);
	ROS_INFO("rps_0:%.2f, rad_0:%.2f", custom_msg->enc_rps[0], custom_msg->enc_rad[0]);
#endif

	for(int i=0; i<NO_VESC; i++) {
		rps[i] = custom_msg->enc_rps[i];
		rad[i] = custom_msg->enc_rad[i];
	}
}

void TeleopVesc::stateCallback(const vesc_msgs::VescStateStamped::ConstPtr& state_msg)
{
#ifdef PRINT_SENSOR_CORE
	ROS_INFO("------------------------------------------");
	ROS_INFO("header:%6.4f", state_msg->header.stamp.toSec());
	ROS_INFO("voltage input:%.2f V", state_msg->state.voltage_input);
	ROS_INFO("temperature pcb:%.2f C", state_msg->state.temperature_pcb);
	ROS_INFO("current motor:%.2f A", state_msg->state.current_motor);
	ROS_INFO("current input:%.2f A", state_msg->state.current_input);
	ROS_INFO("erpm:%.2f", state_msg->state.speed);
	ROS_INFO("duty:%.2f", state_msg->state.duty_cycle);
	ROS_INFO("amp_hours:%.2f", state_msg->state.charge_drawn);
	ROS_INFO("amp_hours_charged:%.2f", state_msg->state.charge_regen);
	ROS_INFO("watt_hours:%.2f", state_msg->state.energy_drawn);
	ROS_INFO("watt_hours_charged:%.2f", state_msg->state.energy_regen);
	ROS_INFO("tachometer:%.2f", state_msg->state.displacement);
	ROS_INFO("tachometer_abs:%.2f", state_msg->state.distance_traveled);
	ROS_INFO("fault code:%d", state_msg->state.fault_code);
#endif
}

void TeleopVesc::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	double joy_cmd_forward, joy_cmd_steering, joy_cmd_brake, joy_cmd_roll, joy_cmd_pitch;

	// xbox initial value ignore
	std_msgs::Header jh = joy->header;
	if(jh.seq<10) {
		joy_cmd_forward = 0;
		joy_cmd_steering = 0;
		joy_cmd_brake = 0;
		joy_cmd_roll = 0;
		joy_cmd_pitch = 0;
	}
	else {
		//joy_cmd_forward = (joy->axes[JR_X]);
		//joy_cmd_steering = (joy->axes[JL_Y]);
		//joy_cmd_brake = (joy->axes[RT]-1)/(-2.0);
		//joy_cmd_forward = (joy->axes[RT]-1)/(-2.0);
		joy_cmd_forward = (joy->axes[JR_X]);
		joy_cmd_brake = (joy->axes[RT]-1)/(-2.0);
		joy_cmd_steering = (joy->axes[JR_Y]);
		joy_cmd_roll = (joy->axes[JL_Y]);
		joy_cmd_pitch = -(joy->axes[JL_X]);

		//ROS_INFO("joy_cmd_forward:%.2f, joy_cmd_brake:%.2f", joy_cmd_forward, joy_cmd_brake);
	}

	// enable
	if(joy->axes[RT]==-1 && joy->axes[LT]==-1)   {
		if(joy_trigger_init_flag.data == false) joy_trigger_init_flag.data = true;
	}
	if(joy->buttons[RB])	{
		// Control Enable
		if(enable.data == false) {
			if(joy_trigger_init_flag.data) {
				enable.data = true;
				if(ctm_state==0)	ctm_state = 1;	// init
				ROS_INFO("Control Enabled, State:%d", ctm_state);
			}
			else ROS_INFO("Joystick LT & RT Init. Required");
		}
	}
	if(joy->buttons[LB])	{
		// Control Disable
		if(enable.data == true) {
			enable.data = false;
			if(ctm_state==2)	ctm_state = 3;	// end
			ROS_INFO("Control Disabled, State:%d", ctm_state);
		}
	}

	// command set
	if(joy->buttons[BT_A]) {
		if(joy_cont_mode!=0) {
			joy_cont_mode = 0;
			ROS_INFO("Current Control Mode");
		}
	}
	else if(joy->buttons[BT_X])	{
		if(joy_cont_mode!=1) {
			joy_cont_mode = 1;
			ROS_INFO("Computed Torque Control Mode");
		}
	}
	else if(joy->buttons[BT_Y])	{
		joy_cont_mode = 2;
		//deg_total_target[VESC_ID_LEFT_ACT] = 30000;
		//deg_total_target[VESC_ID_RIGHT_ACT] = -30000;

		// Deg_Total Reset
		ROS_INFO("deg_total_left:%.2f, deg_total_right:%.2f", deg_total[0], deg_total[1]);
		ROS_INFO("Init Balancing Platform Zero");
		resetDegTotal();
		ROS_INFO("deg_total_left:%.2f, deg_total_right:%.2f", deg_total[0], deg_total[1]);
	}
	else if(joy->buttons[BT_B])	{
		joy_cont_mode = 3;
		//deg_total_target[VESC_ID_LEFT_ACT] = -30000;
		//deg_total_target[VESC_ID_RIGHT_ACT] = 30000;

		/*
		if(motion_planner_mode==0) {
			motion_planner_mode = 1;
			ROS_INFO("MPC Motion Planner On");
		}
		else if(motion_planner_mode==1) {
			motion_planner_mode = 0;
			ROS_INFO("LQR Motion Planner On");
		}
		*/
	}

	switch (joy_cont_mode) {
	case 0:
		//default mode
		current[VESC_ID_LEFT_WHEEL] = (10.0*joy_cmd_forward - 5.0*joy_cmd_steering);
		current[VESC_ID_RIGHT_WHEEL] = -(10.0*joy_cmd_forward + 5.0*joy_cmd_steering);
		brake[VESC_ID_LEFT_WHEEL] = brake[VESC_ID_RIGHT_WHEEL] = BRAKE_CURRENT*joy_cmd_brake;
		dps_target[VESC_ID_LEFT_ACT] = (100000.0*joy_cmd_roll - 50000.0*joy_cmd_pitch);
		dps_target[VESC_ID_RIGHT_ACT] = -(100000.0*joy_cmd_roll + 50000.0*joy_cmd_pitch);

		//speed[0] = (10000.0*joy_cmd_forward - 5000.0*joy_cmd_steering);
		//speed[1] = -(10000.0*joy_cmd_forward + 5000.0*joy_cmd_steering);

		//position[0] = 2.*3.14*joy_cmd_forward;
		//position[1] = 2.*3.14*joy_cmd_steering;
		break;
	case 1:
		// CTM Speed Control
		brake[0] = brake[1] = BRAKE_CURRENT*joy_cmd_brake;
		if(brake[0]<BRAKE_THRESHOLD) {
			vel_target[0] = 1.0*joy_cmd_forward;			// m/s
			vel_target[1] = 100.0*joy_cmd_steering*DEG2RAD;	// deg/sec
		}
		else {
			for(int i=0; i<NO_DOF; i++) vel_target[i] = 0.;
		}
		// actuator
		dps_target[VESC_ID_LEFT_ACT] = (100000.0*joy_cmd_roll - 50000.0*joy_cmd_pitch);
		dps_target[VESC_ID_RIGHT_ACT] = -(100000.0*joy_cmd_roll + 50000.0*joy_cmd_pitch);
		break;
	case 2:
		//

		break;
	case 3:
		//
		break;

	default:
		//
		break;
	}
}

void TeleopVesc::setCmd(double data, int send_can, int can_id)
{
	cmd_msg.data = data;
	cmd_msg.send_can = send_can;
	cmd_msg.can_id = can_id;
}

void TeleopVesc::requestCustoms()
{
	std_msgs::Bool msg;
	msg.data = true;
	vesc_cmd_get_customs.publish(msg);
}

void TeleopVesc::setCurrentOut()
{
	if(enable.data)
	{
	  //vesc_cmd_alive.publish(enable);

	  if(brake[0]>=BRAKE_THRESHOLD) {
		  // brake
		  // motor1
		  setCmd(brake[VESC_ID_LEFT_WHEEL], CAN_FORWARD_OFF, VESC_ID_LEFT_WHEEL);
		  vesc_cmd_brake.publish(cmd_msg);

		  // motor2
		  setCmd(brake[VESC_ID_RIGHT_WHEEL], CAN_FORWARD_ON, VESC_ID_RIGHT_WHEEL);
		  vesc_cmd_brake.publish(cmd_msg);
	  }
	  else {
		  // current
		  // motor1
		  setCmd(current[VESC_ID_LEFT_WHEEL], CAN_FORWARD_OFF, VESC_ID_LEFT_WHEEL);
		  vesc_cmd_current.publish(cmd_msg);

		  // current
		  setCmd(current[VESC_ID_RIGHT_WHEEL], CAN_FORWARD_ON, VESC_ID_RIGHT_WHEEL);
		  vesc_cmd_current.publish(cmd_msg);
	  }
	}

	//ROS_INFO("en:%d, brake1=%.3f, brake2=%.3f, curr1=%.3f, curr2=%.3f", enable.data, brake[0], brake[1], current[0], current[1]);
}

void TeleopVesc::setSpeedOut()
{
	if(enable.data)
	{
	  // Speed
	  // motor1
	  setCmd(speed[0], CAN_FORWARD_OFF, VESC_ID_LEFT_WHEEL);
	  vesc_cmd_speed.publish(cmd_msg);

	  // motor2
	  setCmd(speed[1], CAN_FORWARD_ON, VESC_ID_RIGHT_WHEEL);
	  vesc_cmd_speed.publish(cmd_msg);
	}
}

void TeleopVesc::setPositionOut()
{
	if(enable.data)
	{
	  // Speed
	  // motor1
	  setCmd(enc_deg[0], CAN_FORWARD_OFF, 0);
	  vesc_cmd_position.publish(cmd_msg);

	  // motor2
	  setCmd(enc_deg[1], CAN_FORWARD_ON, 1);
	  vesc_cmd_position.publish(cmd_msg);
	}
}

void TeleopVesc::resetDegTotal(void)
{
	for(int i=0; i<NO_VESC; i++)	deg_total[i] = 0.;
}

double TeleopVesc::genProfile(double *deg_tacho, double *deg_prof, double *dps_prof, double dps_goal, const double Amax, const double dt)
{
	double dv;
	double ds;

	if(*dps_prof == dps_goal) {
		ds = *dps_prof*dt;
		*deg_prof += ds;
		while(*deg_prof > 360.) {
			*deg_prof -= 360.;
		}
		while(*deg_prof < 0.) {
			*deg_prof += 360.;
		}
		*deg_tacho += ds;
		return ds;
	}

	if(dps_goal > *dps_prof) {
		dv = Amax*dt;
	}
	else {
		dv = -Amax*dt;
	}

	if(fabs(dv) > fabs(dps_goal - *dps_prof)) {
		dv = dps_goal - *dps_prof;
	}

	ds = *dps_prof*dt + 0.5*dv*dt;
	*dps_prof += dv;
	*deg_prof += ds;

	while(*deg_prof > 360.) {
		*deg_prof -= 360.;
	}
	while(*deg_prof < 0.) {
		*deg_prof += 360.;
	}
	*deg_tacho += ds;
	return ds;
}

void TeleopVesc::setPositionTrajOut(const double dt)
{
	if(enable.data)
	{
		double ds = 0;

		// actuators
		for(int id=VESC_ID_LEFT_ACT; id<=VESC_ID_RIGHT_ACT; id++)
		{
			ds = genProfile(&deg_total[id], &deg_now[id], &dps_now[id],	dps_target[id], 200000.0, dt);
			enc_deg[id] = deg_now[id]*DEG2RAD;
			//ROS_INFO("id:%d - deg_total:%.2f, ds:%.2f", id, deg_total[id], ds);
			setCmd(enc_deg[id], CAN_FORWARD_ON, id);
			vesc_cmd_position.publish(cmd_msg);
		}
	}
}

void TeleopVesc::setPositionTrajOut(double *deg_tot_goal, const double dt)
{
	if(enable.data)
	{
		double ds = 0;

		// actuators
		for(int id=VESC_ID_LEFT_ACT; id<=VESC_ID_RIGHT_ACT; id++)
		{
			ds = genProfile(&deg_total[id], &deg_now[id], &dps_now[id],	dps_target[id], 200000.0, dt);

			// pd control
			dps_target[id] = 50.*(deg_tot_goal[id] - deg_total[id]) - 10000.*ds;

			enc_deg[id] = deg_now[id]*DEG2RAD;
			//ROS_INFO("id:%d - deg_total:%.2f, ds:%.2f", id, deg_total[id], ds);
			setCmd(enc_deg[id], CAN_FORWARD_ON, id);
			vesc_cmd_position.publish(cmd_msg);
		}
	}
}

void TeleopVesc::getActuatorDegTotalFromRollPitch(double roll_rad, double pitch_rad, double *deg_total) {

	double r, p;	//
	double L, R;	// [mm]
	double REV2MM;	// motor [rev] to ball screw [mm]
	double REV2DEG;

	r = roll_rad;
	p = pitch_rad;

	L = (-0.7036*r*r*r + 10.9342*r*r - 126.0555*r + 0.0051) + (-23.6084*p*p*p + 13.0105*p*p + 126.2104*p + 0.0001);
	R = (0.4772*r*r*r + 10.9173*r*r + 126.0574*r + 0.0051) + (-23.6084*p*p*p + 13.0105*p*p + 126.2104*p + 0.0001);

	REV2MM = 2./14.025;
	REV2DEG = 360.;

	deg_total[VESC_ID_LEFT_ACT] = L/REV2MM*REV2DEG;
	deg_total[VESC_ID_RIGHT_ACT] = R/REV2MM*REV2DEG;
}

int main(int argc, char **argv)              // 노드 메인 함수
{
  ros::init(argc, argv, "vesc_control_node");     // 노드명 초기화

  // loop freq
  int rate_hz = 1000;	//hz

  // TeleopVesc Class
  const int num_of_vesc = 4;
  const int num_of_dof = 2;
  TeleopVesc *teleop_vesc = new TeleopVesc(num_of_vesc, num_of_dof, CURRENT_MODE, MPC_MODE);//MPC_MODE);//LQR_MODE);
  teleop_vesc->enable.data = false;
  teleop_vesc->ctm_state = 0;

  // CTM Class
  // Parameter of DEVIEW_DIFF_CTM
//  int num_of_polepair = 15;
//  double radius_of_wheel = 0.0638;
//  double dcw_x = 0.176;		// distance from center to wheel of m1 along x
//  double dcw_y = 0.158;		// distance from center to wheel of m1 along x
//  int rate_hz = 500;	//hz
//  int motor_direction[num_of_wheel] = {1, -1};
//  double M_dyn[num_of_wheel][10] = { {0.7120, -0.1283}, {0.7120, 0.1283} };
//  double V_dyn[num_of_wheel] = {0., 0.};	//{0.1292, -0.0310};
//  double Motor_Kt[num_of_wheel] = {0.6, 0.6}; //{0.5838, 0.6060};
//  double Kp_ctm[num_of_wheel] = {10., 30.};	// Kp; for, rot
//  double Kd_ctm[num_of_wheel] = {5., 15.};	// Kd; for, rot

  // Parameter of AMG PROTO1 - 4inch Benz Motor
  int num_of_wheel = 2;
  int num_of_polepair = 10;
  double radius_of_wheel = 0.05;
  double dcw_x = 0.19;		// distance from center to wheel of m1 along x
  double dcw_y = 0;		// distance from center to wheel of m1 along y
  //int motor_direction[num_of_wheel] = {1, -1};
  int motor_direction[num_of_wheel] = {-1, 1};	// reverse version
  //double M_dyn[num_of_wheel][10] = { {0.274, -0.04}, {0.274, 0.04} };	// unmanned 1 - 10kg
  double M_dyn[num_of_wheel][10] = { {0.424, -0.1}, {0.424, 0.1} };	// unmanned 2 - 16kg & roationalx2 trimmed
  //double M_dyn[num_of_wheel][10] = { {2.174, -0.196}, {2.174, 0.196} };	// manned
  double V_dyn[num_of_wheel] = {0., 0.};
  double Motor_Kt[num_of_wheel] = {0.25, 0.25};
  double Kp_ctm[num_of_wheel] = {10., 10.};	// Kp; for, rot
  double Kd_ctm[num_of_wheel] = {5., 5.};		// Kd; for, rot

  CTM *vesc_ctm = new CTM(num_of_wheel, num_of_dof, num_of_polepair, radius_of_wheel, dcw_x, dcw_y, rate_hz,
		  motor_direction, M_dyn, V_dyn, Motor_Kt);

  // LQR Motion Planner - Test. Param from 쇠공이
  int state_number_lqr = 4;
  double m_cart = 2.0;
  double m_pend = 0.5;
  double l_pend = 0.12;
  double I_pend_z = 0.0;
  double k_lqr_x[state_number_lqr] = {-22.36, -19.55, 86.34, 9.53};
  LQR_MOTION_PLANNER *lqr_x = new LQR_MOTION_PLANNER(state_number_lqr, m_cart, m_pend, l_pend, I_pend_z, k_lqr_x, (double)(1./rate_hz));
  LQR_MOTION_PLANNER *lqr_y = new LQR_MOTION_PLANNER(state_number_lqr, m_cart, m_pend, l_pend, I_pend_z, k_lqr_x, (double)(1./rate_hz));
  // Publisher
  lqr_x->lqr_mp_pub = lqr_x->nh_.advertise<amg_p1::MP_Message>("lqr_mp_x/msgs", 10);
  lqr_y->lqr_mp_pub = lqr_y->nh_.advertise<amg_p1::MP_Message>("lqr_mp_y/msgs", 10);

  // MPC Motion Planner
  /*
  double k_y[150] = {0, 0.0058, 0.0071, 0.0076, 0.0073, 0.0065, 0.0053, 0.0038, 0.0022, 0.0004, -0.0014, -0.0032, -0.0049, -0.0065, -0.007,
					-0.0089, -0.0098, -0.0103, -0.0105, -0.0104, -0.0103, -0.0101, -0.0100, -0.0099, -0.0098, -0.0097, -0.0096, -0.0095, -0.0095, -0.0094,
					-0.0093, -0.0092, -0.0091, -0.0091, -0.0090, -0.0089, -0.0089, -0.0088, -0.0087, -0.0087, -0.0086, -0.0086, -0.0085, -0.0084, -0.0084,
					-0.0083, -0.0083, -0.0082, -0.0082, -0.0081, -0.0080, -0.0080, -0.0079, -0.0079, -0.0078, -0.0078, -0.0077, -0.0077, -0.0076, -0.0076,
					-0.0075, -0.0075, -0.0074, -0.0074, -0.0073, -0.0072, -0.0072, -0.0071, -0.0071, -0.0070, -0.0070, -0.0069, -0.0069, -0.0068, -0.0068,
					-0.0067, -0.0067, -0.0066, -0.0066, -0.0065, -0.0065, -0.0064, -0.0064, -0.0063, -0.0063, -0.0062, -0.0062, -0.0061, -0.0061, -0.0060,
					-0.0059, -0.0059, -0.0058, -0.0058, -0.0057, -0.0057, -0.0056, -0.0056, -0.0055, -0.0055, -0.0054, -0.0054, -0.0053, -0.0052, -0.0052,
					-0.0051, -0.0051, -0.0050, -0.0049, -0.0049, -0.0048, -0.0048, -0.0047, -0.0046, -0.0045, -0.0045, -0.0044, -0.0043, -0.0042, -0.0042,
					-0.0041, -0.0040, -0.0039, -0.0038, -0.0037, -0.0036, -0.0035, -0.0034, -0.0032, -0.0031, -0.0030, -0.0028, -0.0026, -0.0025, -0.0023,
					-0.0021, -0.0019, -0.0016, -0.0014, -0.0011, -0.0008, -0.0004, -0.0001, 0.0003, 0.0007, 0.0012, 0.0017, 0.0023, 0.0029, 0.0036};
  double k_mpc[5] = {0, -51.73, 129.283, 13.861, -0.776};

  // state space eq
  int state_number_mpc = 4;
  double Ap[state_number_mpc][10] = { {1.0, 0.01, 0.001, 0.0},
					  	  	  	  	  {0, 1.0, 0.0245, 0.0001},
									  {0, 0, 1.0051, 0.01},
									  {0, 0, 1.0226, 1.0051} };
  double Bp[state_number_mpc] = {0.0, 0.0050, 0.0002, 0.0417};
  double Cp[state_number_mpc] = {0., 1., 0., 0.};
  int mpc_rate_hz = 100;
  int Np = 150;
  int Nc = 20;
  int rw = 1;
  */

  // AMG. Ipzz = 1.0, lp = 0.8, mc = 15.0, mp = 70.0
  double k_y[150] = {0.00503213066945279, 0.00915760458928098, 0.0124813202056292, 0.0150977203179203, 0.0170917618097535, 0.0185397995522236, 0.0195103917659968, 0.0200650336240824, 0.0202588253361758, 0.0201410802445902,
		  	  	  	 0.0197558782868527, 0.0191425694502896, 0.0183362316328939, 0.0173680868961321, 0.0162658797333301, 0.0150542207247444, 0.0137548985917188, 0.0123871635048891, 0.0109679841434050, 0.00951228088968378,
					 0.00812184649522331, 0.00679175819161906, 0.00551746526731066, 0.00429476101069583, 0.00311975677413684, 0.00198885799895290, 0.000898742053584575, -0.000153662251706821, -0.00117119359990478, -0.00215647566880867,
					 -0.00311193330701601, -0.00403980748404625, -0.00494216910677892, -0.00582093178739054, -0.00667786364150946, -0.00751459818932776, -0.00833264442688131, -0.00913339612959091, -0.00991814044542216, -0.0106880658306486,
					 -0.0114442693771411, -0.0121877635763602, -0.0129194825617562, -0.0136402878680602, -0.0143509737429767, -0.0150522720440269, -0.0157448567507308, -0.0164293481199500, -0.0171063165100098, -0.0177762858971781,
					 -0.0184397371061791, -0.0190971107746640, -0.0197488100699104, -0.0203952031745043, -0.0210366255563270, -0.0216733820368424, -0.0223057486704401, -0.0229339744464179, -0.0235582828240926, -0.0241788731105148,
					 -0.0247959216892757, -0.0254095831079733, -0.0260199910310674, -0.0266272590639629, -0.0272314814534371, -0.0278327336687019, -0.0284310728667081, -0.0290265382445343, -0.0296191512810471, -0.0302089158693413,
					 -0.0307958183407306, -0.0313798273804733, -0.0319608938347158, -0.0325389504074325, -0.0331139112455183, -0.0336856714094758, -0.0342541062264257, -0.0348190705214400, -0.0353803977224914, -0.0359378988334678,
					 -0.0364913612689488, -0.0370405475435218, -0.0375851938075957, -0.0381250082206801, -0.0386596691520573, -0.0391888231978044, -0.0397120830019624, -0.0402290248682711, -0.0407391861479880, -0.0412420623874290,
					 -0.0417371042178374, -0.0422237139683297, -0.0427012419809785, -0.0431689826054758, -0.0436261698484941, -0.0440719726510643, -0.0445054897647559, -0.0449257441951616, -0.0453316771782788, -0.0457221416529734,
					 -0.0460958951887278, -0.0464515923256670, -0.0467877762793663, -0.0471028699590335, -0.0473951662442218, -0.0476628174598588, -0.0479038239845124, -0.0481160219219987, -0.0482970697600820, -0.0484444339342645,
					 -0.0485553732072077, -0.0486269217681752, -0.0486558709474707, -0.0486387494338629, -0.0485718018725549, -0.0484509657121208, -0.0482718461571068, -0.0480296890725924, -0.0477193516729813, -0.0473352708149264,
					 -0.0468714286980969, -0.0463213157638052, -0.0456778905600572, -0.0449335363292676, -0.0440800140475233, -0.0431084116278271, -0.0420090889736002, -0.0407716185441700, -0.0393847210647778, -0.0378361959854487,
					 -0.0361128462594138, -0.0342003969798839, -0.0320834073672813, -0.0297451755731117, -0.0271676357058936, -0.0243312464473320, -0.0212148705738855, -0.0177956446356120, -0.0140488379972794, -0.00994770036106729,
					 -0.00546329684368629, -0.000564329580583944, 0.00478305524052303, 0.0106154760946993, 0.0169725418934377, 0.0238970961829637, 0.0314354812974216, 0.0396378240725426, 0.0485583448971738, 0.0582556920048773};
  double k_mpc[5] = {0, -295.049952087458, 2449.69383239746, 481.663159370422, -2.93575023412996};

  // state space eq
  int state_number_mpc = 4;
  double Ap[state_number_mpc][10] = { {1., 0.0100000000000000, 0.00203095013847244, 6.76844352753569e-06},
		  	  	  	  	  	  	  	  {0,	1.,	0.406398592276978,	0.00203095013847244},
		  	  	  	  	  	  	  	  {0,	0,	1.00308269217447,	0.0100102735303543},
		  	  	  	  	  	  	  	  {0,	0,	0.616855006134699,	1.00308269217447} };
  double Bp[state_number_mpc] = {3.02635070644951e-06, 0.000605520518939950, 3.70071089371800e-06, 0.000740522216248138};
  double Cp[state_number_mpc] = {0., 1., 0., 0.};
  int mpc_rate_hz = 100;
  int Np = 150;
  int Nc = 20;
  int rw = 0.1;
  MPC_MOTION_PLANNER *mpc_x = new MPC_MOTION_PLANNER(state_number_mpc, Ap, Bp, Cp,
				  	  	  	  	  	  	  	  	  	  Np, Nc, rw, mpc_rate_hz, k_mpc, k_y);
  MPC_MOTION_PLANNER *mpc_y = new MPC_MOTION_PLANNER(state_number_mpc, Ap, Bp, Cp,
  				  	  	  	  	  	  	  	  	  	  Np, Nc, rw, mpc_rate_hz, k_mpc, k_y);
  // Publisher
  mpc_x->mpc_mp_pub = mpc_x->nh_.advertise<amg_p1::MP_Message>("mpc_mp_x/msgs", 10);
  mpc_y->mpc_mp_pub = mpc_x->nh_.advertise<amg_p1::MP_Message>("mpc_mp_y/msgs", 10);

  // ROS Loop
  int cnt_lp = 0;
  ros::Rate loop_rate(rate_hz); //Hz
  ROS_INFO("Start Tele-operation");
  while (ros::ok())
  {
	  /*
	  if(teleop_vesc->joy_cont_mode==0)		// Current Control Mode
	  {
		  teleop_vesc->requestCustoms();
		  teleop_vesc->setCurrentOut();
		  //teleop_vesc->setPositionOut();
		  teleop_vesc->setPositionTrajOut((double)(1./rate_hz));
	  }
	  else if(teleop_vesc->joy_cont_mode==1)	// Computed Torque Control Mode
	  {
		  // Motion Planner
		  if(teleop_vesc->motion_planner_mode==LQR_MODE) {
			  lqr_x->Run_LQR_MODEL(teleop_vesc->vel_target[0], &teleop_vesc->vel_mp_out[0], &teleop_vesc->theta_mp_out[0]);	// forward, pitch
			  lqr_x->lqr_mp_pub.publish(lqr_x->lqr_mp_msg);
			  lqr_y->Run_LQR_MODEL(teleop_vesc->vel_target[1], &teleop_vesc->vel_mp_out[1], &teleop_vesc->theta_mp_out[1]);	// rotation, roll
			  lqr_y->lqr_mp_pub.publish(lqr_y->lqr_mp_msg);
		  }
		  else if(teleop_vesc->motion_planner_mode==MPC_MODE) {
			  if(cnt_lp==(rate_hz/mpc_rate_hz)) {
				  mpc_x->Run_MPC_MODEL(teleop_vesc->vel_target[0], &teleop_vesc->vel_mp_out[0], &teleop_vesc->theta_mp_out[0]);
				  mpc_x->mpc_mp_pub.publish(mpc_x->mpc_mp_msg);
				  mpc_y->Run_MPC_MODEL(teleop_vesc->vel_target[1], &teleop_vesc->vel_mp_out[1], &teleop_vesc->theta_mp_out[1]);
				  mpc_y->mpc_mp_pub.publish(mpc_y->mpc_mp_msg);
				  cnt_lp = 0;
			  }
			  cnt_lp++;
		  }

		  // 1. Initialization
		  if(teleop_vesc->ctm_state==1) {
			  for(int i=0; i<teleop_vesc->NO_DOF; i++) {
				  teleop_vesc->vel[i] = 0.;
				  teleop_vesc->vel_target[i] = 0.;
			  }

			  teleop_vesc->ctm_state = 2;
		  }

		  // 2. Computed Torque Method Run
		  if(teleop_vesc->ctm_state==2 && teleop_vesc->enable.data) {
			  teleop_vesc->requestCustoms();
			  //vesc_ctm->RunCTM(teleop_vesc->rps, teleop_vesc->rad, teleop_vesc->vel, teleop_vesc->vel_target, teleop_vesc->current, Kp_ctm, Kd_ctm);
			  vesc_ctm->RunCTM(teleop_vesc->rps, teleop_vesc->rad, teleop_vesc->vel, teleop_vesc->vel_mp_out, teleop_vesc->current, Kp_ctm, Kd_ctm);
			  //
			  
			//   if(cnt_lp==1000) {
			// 	  ROS_INFO("---------------------------------------------------------------------------------");
			// 	  ROS_INFO("CTM - Forward => Vel: %.3f, Target Vel: %.3f (m/s) / Rotation => Velocity: %.3f, Target Vel: %.3f (dps)",
			// 				  teleop_vesc->vel[0], teleop_vesc->target_vel[0], teleop_vesc->vel[1]*RAD2DEG, teleop_vesc->target_vel[1]*RAD2DEG);
			// 	  ROS_INFO("CTM - Current Out Left: %.3f A, Right: %.3f A", teleop_vesc->current[0], teleop_vesc->current[1]);
			// 	  cnt_lp = 0;
			//   }
			//   cnt_lp++;
			  
		  }

		  // 3. Disable CTM
		  if(teleop_vesc->ctm_state==3) {
			  for(int i=0; i<teleop_vesc->NO_DOF; i++) {
				  teleop_vesc->current[i] = 0.;
			  }
			  for(int i=0; i<teleop_vesc->NO_DOF; i++) {
				  teleop_vesc->vel[i] = 0.;
				  teleop_vesc->vel_target[i] = 0.;
			  }
			  teleop_vesc->ctm_state = 0;
		  }

		  teleop_vesc->setCurrentOut();
		  //teleop_vesc->setPositionTrajOut((double)(1./rate_hz));
		  //teleop_vesc->getActuatorDegTotalFromRollPitch(teleop_vesc->theta_mp_out[1]*(0.5), teleop_vesc->theta_mp_out[0]*(-1.), teleop_vesc->deg_total_target);
		  teleop_vesc->getActuatorDegTotalFromRollPitch(teleop_vesc->theta_mp_out[1]*(-0.4), teleop_vesc->theta_mp_out[0], teleop_vesc->deg_total_target);	// reverse version
//		  ROS_INFO("roll:%.2f[deg], pitch:%.2f[deg] / deg_tot - Left Act:%.2f, Right Act:%.2f",
//				  teleop_vesc->theta_mp_out[1]*RAD2DEG, teleop_vesc->theta_mp_out[0]*RAD2DEG,
//				  teleop_vesc->deg_total_target[2], teleop_vesc->deg_total_target[3]);
		  teleop_vesc->setPositionTrajOut(teleop_vesc->deg_total_target, (double)(1./rate_hz)); // TODO: pitch angle -> deg_total

		  // publishing
		  teleop_vesc->actuator_msg.stamp = ros::Time::now();

		  teleop_vesc->actuator_msg.deg_total_target.clear();
		  teleop_vesc->actuator_msg.deg_total_target.push_back(teleop_vesc->deg_total_target[VESC_ID_LEFT_ACT]);
		  teleop_vesc->actuator_msg.deg_total_target.push_back(teleop_vesc->deg_total_target[VESC_ID_RIGHT_ACT]);

		  teleop_vesc->actuator_msg.deg_total_now.clear();
		  teleop_vesc->actuator_msg.deg_total_now.push_back(teleop_vesc->deg_total[VESC_ID_LEFT_ACT]);
		  teleop_vesc->actuator_msg.deg_total_now.push_back(teleop_vesc->deg_total[VESC_ID_RIGHT_ACT]);

		  teleop_vesc->actuator_deg_pub.publish(teleop_vesc->actuator_msg);
	  }
*/
		teleop_vesc->requestCustoms();

		teleop_vesc->enable.data = true;
		teleop_vesc->current[0] = 2.0;
		teleop_vesc->current[1] = 2.0;
		teleop_vesc->setCurrentOut();

	  ros::spinOnce();
	  loop_rate.sleep();
  }

  return 0;
}
