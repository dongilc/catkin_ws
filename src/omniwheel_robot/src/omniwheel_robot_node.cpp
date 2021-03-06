/*
 * omniwheel_robot_node.cpp
 *
 *  Created on: Oct 29, 2018
 *      Author: cdi
 */

#include "vesc_control.h"

// Settings
#define VESC_ID_0				0
#define VESC_ID_1				1
#define VESC_ID_2				2
#define VESC_ID_START			VESC_ID_0
#define VESC_ID_END				VESC_ID_2	// Change this depend on your condition
#define CAN_FORWARD_OFF			0
#define CAN_FORWARD_ON			1
#define BRAKE_CURRENT			10.
#define BRAKE_THRESHOLD			8.	// bigger than (BRAKE_CURRENT/2)

// COMM_SET Types
#define COMM_SET_DUTY			5
#define COMM_SET_CURRENT		6
#define COMM_SET_CURRENT_BRAKE	7
#define COMM_SET_RPM			8
#define COMM_SET_POS			9
#define COMM_SET_HANDBRAKE		10
#define COMM_SET_DPS			38

// Conversions
#define RAD2DEG         		180.0/M_PI  // radian to deg
#define RPS2DPS					RAD2DEG	

// Uncomment this only when you want to see the below infomations.
//#define PRINT_SENSOR_CORE
//#define PRINT_SENSOR_CUSTOMS

void TeleopVesc::customsCallback(const vesc_msgs::VescGetCustomApp::ConstPtr& custom_rx_msg)
{
#ifdef PRINT_SENSOR_CUSTOMS
	ROS_INFO("------------------------------------------");
	ROS_INFO("header:%6.4f", custom_rx_msg->header.stamp.toSec());
	ROS_INFO("voltage input:%.2f V", custom_rx_msg->voltage_input);
	ROS_INFO("temperature pcb:%.2f C", custom_rx_msg->temperature_pcb);
	ROS_INFO("current motor:%.2f A", custom_rx_msg->current_motor);
	ROS_INFO("current input:%.2f A", custom_rx_msg->current_input);
	ROS_INFO("erpm:%.2f", custom_rx_msg->speed);
	ROS_INFO("duty:%.2f", custom_rx_msg->duty_cycle);
	ROS_INFO("amp_hours:%.2f", custom_rx_msg->charge_drawn);
	ROS_INFO("amp_hours_charged:%.2f", custom_rx_msg->charge_regen);
	ROS_INFO("watt_hours:%.2f", custom_rx_msg->energy_drawn);	
	ROS_INFO("watt_hours_charged:%.2f", custom_rx_msg->energy_regen);
	ROS_INFO("tachometer:%.2f", custom_rx_msg->displacement);
	ROS_INFO("tachometer_abs:%.2f", custom_rx_msg->distance_traveled);
	ROS_INFO("fault code:%d", custom_rx_msg->fault_code);
	ROS_INFO("pid_pos_now:%.2f", custom_rx_msg->pid_pos_now);
	ROS_INFO("rps_0:%.2f, rad_0:%.2f", custom_rx_msg->enc_rps[0], custom_rx_msg->enc_rad[0]);
#endif

	for(int i=VESC_ID_START; i<=VESC_ID_END; i++) {
		rps[i] = custom_rx_msg->enc_rps[i];
		rad[i] = custom_rx_msg->enc_rad[i];
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
	ROS_INFO("pid_pos_now:%.2f", state_msg->pid_pos_now);
	ROS_INFO("controller_id:%d", custom_rx_msg->controller_id);
#endif
}

void TeleopVesc::setCmdMsg(double data, int send_can, int can_id)
{
	cmd_msg.data = data;
	cmd_msg.send_can = send_can;
	cmd_msg.can_id = can_id;
}

void TeleopVesc::setCustomMsg(int can_id, int send_can, int cmd_type, double data)
{
	//
	custom_tx_msg.id_set.push_back(can_id);
	custom_tx_msg.can_forward_set.push_back(send_can);
	custom_tx_msg.comm_set.push_back(cmd_type);
	custom_tx_msg.value_set.push_back(data);
}

void TeleopVesc::requestCustoms()
{
	std_msgs::Bool msg;
	msg.data = true;
	vesc_cmd_get_customs.publish(msg);
}

void TeleopVesc::setCustomOut()
{
	int num_of_id = 0;
	int id;
	int can_forw = 0;

	if(enable.data)
	{
		// Clear Custom Message
		custom_tx_msg.id_set.clear();
		custom_tx_msg.can_forward_set.clear();
		custom_tx_msg.comm_set.clear();
		custom_tx_msg.value_set.clear();

		// Custom Command
		for(int i=VESC_ID_START; i<=VESC_ID_END; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCustomMsg(i, can_forw, custom_cmd_type[i], custom_cmd_value[i]);
			num_of_id++;
		}
		custom_tx_msg.num_of_id = num_of_id;
		custom_tx_msg.data_bytes = 3 + 6*num_of_id;
		vesc_cmd_set_customs.publish(custom_tx_msg);
	}
}

void TeleopVesc::setCurrentOut()
{
	int id;
	int can_forw = 0;

	if(enable.data)
	{
		// current
		for(int i=VESC_ID_START; i<=VESC_ID_END; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCmdMsg(current[i], can_forw, i);
			vesc_cmd_current.publish(cmd_msg);
		}
	}
}

void TeleopVesc::setBrakeOut()
{
	int id;
	int can_forw = 0;

	if(enable.data)
	{
		// current
		for(int i=VESC_ID_START; i<=VESC_ID_END; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCmdMsg(brake[i], can_forw, i);
			vesc_cmd_brake.publish(cmd_msg);
		}
	}
}

void TeleopVesc::setDutyCycleOut()
{
	int id;
	int can_forw = 0;

	if(enable.data)
	{
		// current
		for(int i=VESC_ID_START; i<=VESC_ID_END; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCmdMsg(duty[i], can_forw, i);
			vesc_cmd_duty.publish(cmd_msg);
		}
	}
}

void TeleopVesc::setSpeedOut()
{
	int id;
	int can_forw = 0;

	if(enable.data)
	{
		// speed
		for(int i=VESC_ID_START; i<=VESC_ID_END; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCmdMsg(speed[i], can_forw, i);
			vesc_cmd_speed.publish(cmd_msg);
		}
	}
}

void TeleopVesc::setPositionOut()
{
	int id;
	int can_forw = 0;

	if(enable.data)
	{
		// position
		for(int i=VESC_ID_START; i<=VESC_ID_END; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCmdMsg(enc_deg[i], can_forw, i);
			vesc_cmd_position.publish(cmd_msg);
		}
	}
}

void TeleopVesc::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	double joy_cmd_forward, joy_cmd_lateral, joy_cmd_steering, joy_cmd_brake;

	// xbox initial value ignore
	std_msgs::Header jh = joy->header;
	if(jh.seq<10) {
		joy_cmd_forward = 0;
		joy_cmd_steering = 0;
		joy_cmd_brake = 0;
	}
	else {
		joy_cmd_forward = (joy->axes[JR_X]);
		joy_cmd_lateral = (joy->axes[JR_Y]);
		joy_cmd_steering = (joy->axes[JL_Y])*(5.0);
		joy_cmd_brake = (joy->axes[RT]-1)/(-2.0);
	}

	speed[0] = joy_cmd_forward;
	speed[1] = joy_cmd_lateral;
	speed[2] = joy_cmd_steering;

/*
	// enable
	if(joy->axes[RT]==-1)   {
		if(enable.data == false) {
			enable.data = true;
			if(ctm_state==0)	ctm_state = 1;	// init
			ROS_INFO("Control Enabled, State:%d", ctm_state);
		}
		else if(enable.data == true) {
			enable.data = false;
			if(ctm_state==2)	ctm_state = 3;	// end
			ROS_INFO("Control Disabled, State:%d", ctm_state);
		}
	}
/*
	// cruise
	// command set
	if(joy->buttons[RB]) {
		if(cruise.data == false) {
			cruise.data = true;
			ROS_INFO("Cruise On");
		}
		else
		{
			cruise.data = false;
			ROS_INFO("Cruise Off");
		}
	}/*
	else if(joy->buttons[BT_X])	{
		if(joy_cont_mode!=1) {
			joy_cont_mode = 1;
			ROS_INFO("Computed Torque Control Mode");
		}
	}
	else if(joy->buttons[BT_Y])	{
		joy_cont_mode = 2;
	}
	else if(joy->buttons[BT_B])	{
		joy_cont_mode = 3;
	}*/

/*
	switch (joy_cont_mode) {
	case 0:
		//default mode
		if(cruise.data==false) {
			speed[0] = (15000.0*joy_cmd_forward - 3000.0*joy_cmd_steering);
			speed[1] = -(15000.0*joy_cmd_forward + 3000.0*joy_cmd_steering);
		}
		break;
	case 1:
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
	*/
}

double duty_limit(double input_duty)
{
	double duty_limit = 0.95;
	double output_duty;

	if(input_duty>=duty_limit)	output_duty = duty_limit;
	else if(input_duty<=-duty_limit)	output_duty = -duty_limit;
	else output_duty = input_duty;

	return output_duty;
}

void omni_jacobian(double vx, double vy, double wz, double *duty1, double *duty2, double *duty3)
{
	// robot parameter
	static double radius_wheel = 24./1000.;
	static double d = 120./1000.;
	static double VEL2DUTY = 0.02;
	double u1, u2, u3;

	u1 = (1.0*vx - d*wz)/radius_wheel;
	u2 = (-0.5*vx + sqrt(3.)/2.*vy - d*wz)/radius_wheel;
	u3 = (-0.5*vx - sqrt(3.)/2.*vy - d*wz)/radius_wheel;

	*duty1 = duty_limit(u1*VEL2DUTY);
	*duty2 = duty_limit(u2*VEL2DUTY);
	*duty3 = duty_limit(u3*VEL2DUTY);
}

/*
 * Main Function
 * 
 */
int main(int argc, char **argv)            
{
  ros::init(argc, argv, "vesc_control_node");

  // loop freq
  int rate_hz = 50;	//hz

  // TeleopVesc Class
  const int num_of_vesc = VESC_ID_END+1;
  TeleopVesc *teleop_vesc = new TeleopVesc(num_of_vesc);
  teleop_vesc->enable.data = false;
  
  // ROS Loop
  int cnt_loop = 0;
  ros::Rate loop_rate(rate_hz); //Hz
  ROS_INFO("Start Tele-operation");
  while (ros::ok())
  {
		teleop_vesc->enable.data = true;

		// read encoder data.
		teleop_vesc->requestCustoms();
		//ROS_INFO("rps_0:%.2f(dps_0:%.2f), rad_0:%.2f", teleop_vesc->rps[0], teleop_vesc->rps[0]*RPS2DPS, teleop_vesc->rad[0]);
		//ROS_INFO("rps_1:%.2f(dps_1:%.2f), rad_1:%.2f", teleop_vesc->rps[1], teleop_vesc->rps[1]*RPS2DPS, teleop_vesc->rad[1]);
		//ROS_INFO("rps_2:%.2f(dps_2:%.2f), rad_2:%.2f", teleop_vesc->rps[2], teleop_vesc->rps[2]*RPS2DPS, teleop_vesc->rad[2]);
	
		// current example (A)
		//teleop_vesc->current[0] = 4.0;
		//teleop_vesc->current[1] = 4.0;
		// teleop_vesc->current[2] = -1.0;
		// teleop_vesc->current[3] = 1.0;
		//teleop_vesc->setCurrentOut();

		// // brake example (A)
		// teleop_vesc->brake[0] = 10.0;
		// teleop_vesc->brake[1] = 10.0;
		// teleop_vesc->brake[2] = 5.0;
		// teleop_vesc->brake[3] = 8.0;
		// teleop_vesc->setBrakeOut();

		// // speed example (erpm = rev/min*polepair, polepair=Encoder Ratio@vesc_tool)
		//teleop_vesc->speed[0] = 0.//-(15000.0 - 5000.0);
		//teleop_vesc->speed[1] = 1000.//(15000.0 + 5000.0);
		// teleop_vesc->speed[2] = -1000.0;
		// teleop_vesc->speed[3] = 5000.0;
		//teleop_vesc->setSpeedOut();

		// // // duty example (0.005~0.95)
		omni_jacobian(teleop_vesc->speed[0], teleop_vesc->speed[1], teleop_vesc->speed[2],
					  &(teleop_vesc->duty[0]), &(teleop_vesc->duty[1]), &(teleop_vesc->duty[2]));
		teleop_vesc->duty[0] = teleop_vesc->duty[0];//*sin(2*M_PI*1.*cnt_loop/rate_hz);
		teleop_vesc->duty[1] = teleop_vesc->duty[1];//*sin(2*M_PI*1.*cnt_loop/rate_hz);
		teleop_vesc->duty[2] = teleop_vesc->duty[2];//*sin(2*M_PI*1.*cnt_loop/rate_hz);
		teleop_vesc->setDutyCycleOut();

		// // position example (0~360 deg)
		//teleop_vesc->position[0] = 0.;
		// teleop_vesc->position[1] = 15.;
		// teleop_vesc->position[2] = 270.;
		// teleop_vesc->position[3] = -45.;
		//teleop_vesc->setPositionOut();

		// Custom example
		//teleop_vesc->custom_cmd_type[0] = COMM_SET_DUTY;
		//teleop_vesc->custom_cmd_value[0] = 0.6;
		//teleop_vesc->custom_cmd_type[1] = COMM_SET_DPS;
		//teleop_vesc->custom_cmd_value[1] = 1000.;
		//teleop_vesc->custom_cmd_type[2] = COMM_SET_DPS;
		//teleop_vesc->custom_cmd_value[2] = -1000.;
		//teleop_vesc->custom_cmd_type[3] = COMM_SET_DPS;
		//teleop_vesc->custom_cmd_value[3] = 1000.;
		// teleop_vesc->custom_cmd_type[1] = COMM_SET_DPS;
		//teleop_vesc->custom_cmd_value[1] = 0.;
		//teleop_vesc->setCustomOut();

		ros::spinOnce();
		loop_rate.sleep();
		cnt_loop++;
  }

  return 0;
}
