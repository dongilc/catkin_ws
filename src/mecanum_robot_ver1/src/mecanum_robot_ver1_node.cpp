/*
 *  mecanum_robot_ver1_node.cpp
 * 
 *  Created on: Nov. 23, 2018
 *      Author: cdi
 */

#include "vesc_control.h"

// Settings
#define VESC_ID_0				0
#define VESC_ID_1				1
#define VESC_ID_2				2
#define VESC_ID_3				3
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

void TeleopInput::keyboardCallback(const geometry_msgs::Twist::ConstPtr& cmd_vel)
{
	/*
	//ROS_INFO("lin x:%.2f, y:%.2f, z:%.2f", cmd_vel->linear.x, cmd_vel->linear.y, cmd_vel->linear.z);
	//ROS_INFO("ang x:%.2f, y:%.2f, z:%.2f", cmd_vel->angular.x, cmd_vel->angular.y, cmd_vel->angular.z);
	dps[0] = cmd_vel->linear.x*2.;//cmd_vel->linear.x*200.;
	speed[0] = cmd_vel->angular.z*1.;
	if(cmd_vel->angular.z < 0) {
		enable.data = false;
		dps[0] = 0.;
		speed[0] = 0.;
	}
	else 
	{
		startTime = ros::Time::now();
		enable.data = true;
	}
	*/
}

void TeleopInput::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	static int joy_cont_mode;
	double joy_cmd_forward, joy_cmd_lateral, joy_cmd_steering, joy_cmd_brake;
	double joy_cmd_hit, joy_cmd_spin;

    //ROS_INFO("%.3f, %.3f, %.3f, %.3f", joy->axes[0], joy->axes[1], joy->axes[2], joy->axes[3]);
	//ROS_INFO("%d, %d", joy->buttons[0], joy->buttons[1]);

	joy_cmd_forward = (joy->axes[1])*(-0.5);
	joy_cmd_lateral = (joy->axes[2])*(0.5);
	joy_cmd_steering = (joy->axes[0])*(1.0);

	joy_cmd_hit = joy->axes[3]*(-500.0);
	joy_cmd_spin = joy->axes[0]*(500.0);

	if(joy->buttons[0] == 1)
	{
		vh2_->speed[0] += joy_cmd_hit - joy_cmd_spin;
		vh2_->speed[1] += -(joy_cmd_hit + joy_cmd_spin);

		if(joy->buttons[1] == 1)
		{
			if(vh2_->speed[0] >= (vh2_->speed[1]*-1.)) 
			{
				vh2_->speed[1] = vh2_->speed[0]*-1.;
			}
			else
			{
				vh2_->speed[0] = vh2_->speed[1]*-1.;
			}
		}
	}
	else
	{
		if(joy->buttons[1] == 1 && vh2_->speed[0]<=5000 && vh2_->speed[1]>=-5000)
		{
			vh2_->speed[0] = vh2_->speed[1] = 0;
		}

		vh1_->speed[0] = joy_cmd_forward;
		vh1_->speed[1] = joy_cmd_lateral;
		vh1_->speed[2] = joy_cmd_steering;
	}

	//ROS_INFO("%.3f, %.3f", vh2_->speed[0], vh2_->speed[1]);
	//ROS_INFO("vx=%.3f, vy=%.3f, wz=%.3f", vh1_->speed[0], vh1_->speed[1], vh1_->speed[2]);

/*
	// enable
	if(joy->buttons[1]==0) {
		if(joy_cont_mode!=0) {
			joy_cont_mode = 0;
			ROS_INFO("Control Disabled");
		}
	}
	else if(joy->buttons[1]==1) {
		if(joy_cont_mode!=1) {
			joy_cont_mode = 1;
			ROS_INFO("Duty Control Mode");
		}
	}

	switch (joy_cont_mode) {
	case 0:
		//default mode
		duty[0] = duty[1] = 0.;
		break;
	case 1:
		//
		duty[0] = -(0.2*joy_cmd_forward + 0.1*joy_cmd_steering);
		duty[1] = +(0.2*joy_cmd_forward - 0.1*joy_cmd_steering);
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


void TeleopVesc::customsCallback(const vesc_msgs::VescGetCustomApp::ConstPtr& custom_rx_msg)
{
#ifdef PRINT_SENSOR_CUSTOMS
	ROS_INFO("------------------------------------------");
	ROS_INFO("header:%6.4f", custom_rx_msg->header.stamp.toSec());
	//ROS_INFO("voltage input:%.2f V", custom_rx_msg->voltage_input);
	//ROS_INFO("temperature pcb:%.2f C", custom_rx_msg->temperature_pcb);
	//ROS_INFO("current motor:%.2f A", custom_rx_msg->current_motor);
	//ROS_INFO("current input:%.2f A", custom_rx_msg->current_input);
	//ROS_INFO("erpm:%.2f", custom_rx_msg->speed);
	//ROS_INFO("duty:%.2f", custom_rx_msg->duty_cycle);
	//ROS_INFO("amp_hours:%.2f", custom_rx_msg->charge_drawn);
	//ROS_INFO("amp_hours_charged:%.2f", custom_rx_msg->charge_regen);
	//ROS_INFO("watt_hours:%.2f", custom_rx_msg->energy_drawn);	
	//ROS_INFO("watt_hours_charged:%.2f", custom_rx_msg->energy_regen);
	//ROS_INFO("tachometer:%.2f", custom_rx_msg->displacement);
	//ROS_INFO("tachometer_abs:%.2f", custom_rx_msg->distance_traveled);
	ROS_INFO("fault code:%d", custom_rx_msg->fault_code);
	//ROS_INFO("pid_pos_now:%.2f", custom_rx_msg->pid_pos_now);
	ROS_INFO("rps_0:%.2f, current_0:%.2f, duty_0:%.2f", custom_rx_msg->enc_rps[0], custom_rx_msg->current[0], custom_rx_msg->duty[0]);
	ROS_INFO("app status code:%d", custom_rx_msg->app_status_code);
#endif

	this->app_status_code = custom_rx_msg->app_status_code;
	
	for(int i=0; i<this->NO_VESC; i++) {
		this->controller_id[i] = custom_rx_msg->can_id[i];
		this->rps[i] = custom_rx_msg->enc_rps[i];
		//rad[i] = custom_rx_msg->enc_rad[i];
		this->current_status[i] = custom_rx_msg->current[i];
		this->duty_status[i] = custom_rx_msg->duty[i];
        this->custom_status[i] = custom_rx_msg->custom_status[i];
    }

	this->last_app_status_code = this->app_status_code;
	for(int i=0; i<this->NO_VESC; i++) this->last_custom_status[i] = this->custom_status[i];
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
	int can_forw = 0;
	int no_vesc = 0;

	no_vesc = this->NO_VESC;
	
	// Clear Custom Message
	custom_tx_msg.id_set.clear();
	custom_tx_msg.can_forward_set.clear();
	custom_tx_msg.comm_set.clear();
	custom_tx_msg.value_set.clear();

	// Custom Command
	for(int i=0; i<no_vesc; i++) {
		if(i==0) can_forw = CAN_FORWARD_OFF;
		else     can_forw = CAN_FORWARD_ON;
		setCustomMsg(i, can_forw, custom_cmd_type[i], custom_cmd_value[i]);
		num_of_id++;
	}
	custom_tx_msg.num_of_id = num_of_id;
	custom_tx_msg.data_bytes = 2 + 6*num_of_id;
	vesc_cmd_set_customs.publish(custom_tx_msg);
}

void TeleopVesc::setCurrentOut()
{
	int can_forw = 0;

	if(enable.data)
	{
		if(this->port_name=="/dev/ttyVESC1")
		{
			// current
			for(int i=0; i<=1; i++) {
				if(i==0) can_forw = CAN_FORWARD_OFF;
				else     can_forw = CAN_FORWARD_ON;
				setCmdMsg(this->current[i], can_forw, i);
				this->vesc_cmd_current.publish(cmd_msg);
			}
		}
	}
}

void TeleopVesc::setBrakeOut()
{
	int can_forw = 0;

	if(enable.data)
	{
		// current
		for(int i=0; i<=1; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCmdMsg(brake[i], can_forw, i);
			vesc_cmd_brake.publish(cmd_msg);
		}
	}
}

void TeleopVesc::setDutyCycleOut()
{
	int can_forw = 0;

	if(this->enable.data)
	{
		if(this->port_name=="/dev/ttyVESC0")
		{
			// duty
			for(int i=0; i<=3; i++) {
				if(i==0) can_forw = CAN_FORWARD_OFF;
				else     can_forw = CAN_FORWARD_ON;
				setCmdMsg(this->duty[i], can_forw, i);
				this->vesc_cmd_duty.publish(cmd_msg);
			}
		}
		/*
		else if(this->port_name=="/dev/ttyVESC2")
		{
			// duty
			setCmdMsg(this->duty[0], 0, 0);
			this->vesc_cmd_duty.publish(cmd_msg);
		}*/
	}
}

void TeleopVesc::setSpeedOut()
{
	int can_forw = 0;

	if(enable.data)
	{
		if(this->port_name=="/dev/ttyVESC1")
		{
			// speed
			for(int i=0; i<=1; i++) {
				if(i==0) can_forw = CAN_FORWARD_OFF;
				else     can_forw = CAN_FORWARD_ON;
				setCmdMsg(this->speed[i], can_forw, i);
				this->vesc_cmd_speed.publish(cmd_msg);
			}
		}
	}
}

void TeleopVesc::setPositionOut()
{
	int can_forw = 0;

	if(enable.data)
	{
		// position
		for(int i=0; i<=1; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCmdMsg(enc_deg[i], can_forw, i);
			vesc_cmd_position.publish(cmd_msg);
		}
	}
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

void mecanum_robot_jacobian(double vx, double vy, double wz, double *duty1, double *duty2, double *duty3, double *duty4)
{
	// robot parameter
	static double radius_wheel = 63.5/1000.;
	static double alpha = 0.325;	// alpha = L+l
	static double VEL2DUTY = 0.06;//0.02;
	static int 	  MOTOR_DIR[4] = {-1, -1, 1, 1};
	double u1, u2, u3, u4;
	
	u1 = MOTOR_DIR[0]*(1.0*vx - 1.0*vy - alpha*wz)/radius_wheel;
	u2 = MOTOR_DIR[1]*(1.0*vx + 1.0*vy - alpha*wz)/radius_wheel;
	u3 = MOTOR_DIR[2]*(1.0*vx - 1.0*vy + alpha*wz)/radius_wheel;
	u4 = MOTOR_DIR[3]*(1.0*vx + 1.0*vy + alpha*wz)/radius_wheel;

	*duty1 = duty_limit(u1*VEL2DUTY);
	*duty2 = duty_limit(u2*VEL2DUTY);
	*duty3 = duty_limit(u3*VEL2DUTY);
	*duty4 = duty_limit(u4*VEL2DUTY);
}

/*
 * Main Function
 * 
 */
int main(int argc, char **argv)            
{
  ros::init(argc, argv, "vesc_control_node");

  // loop freq
  int rate_hz = 100;	//hz

  // TeleopVesc Class
  TeleopVesc *teleop_vesc1 = new TeleopVesc(4, "/dev/ttyVESC0"); 
  TeleopVesc *teleop_vesc2 = new TeleopVesc(2, "/dev/ttyVESC1"); 

// TeleopInput Class
  TeleopInput tele_input(teleop_vesc1, teleop_vesc2, NULL);

  // ROS Loop
  int cnt_lp = 0;
  ros::Rate loop_rate(rate_hz); //Hz
  ROS_INFO("Start Tele-operation");
  teleop_vesc1->enable.data = true;
  teleop_vesc2->enable.data = true;

  teleop_vesc1->startTime = ros::Time::now();
  teleop_vesc2->startTime = ros::Time::now();

  while (ros::ok())
  { 
		// read encoder data.
		//teleop_vesc->requestCustoms();
		//ROS_INFO("rps_0:%.2f(dps_0:%.2f), rad_0:%.2f", teleop_vesc->rps[0], teleop_vesc->rps[0]*RPS2DPS, teleop_vesc->rad[0]);
		//ROS_INFO("rps_1:%.2f(dps_1:%.2f), rad_1:%.2f", teleop_vesc->rps[1], teleop_vesc->rps[1]*RPS2DPS, teleop_vesc->rad[1]);
		//ROS_INFO("rps_2:%.2f(dps_2:%.2f), rad_2:%.2f", teleop_vesc->rps[2], teleop_vesc->rps[2]*RPS2DPS, teleop_vesc->rad[2]);
		//ROS_INFO("rps_3:%.2f(dps_3:%.2f), rad_3:%.2f", teleop_vesc->rps[3], teleop_vesc->rps[3]*RPS2DPS, teleop_vesc->rad[3]);

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
		//teleop_vesc->speed[0] = -20000.;//-(15000.0 - 5000.0);
		//teleop_vesc->speed[1] = 5000.;//(15000.0 + 5000.0);
		// teleop_vesc->speed[2] = -1000.0;
		// teleop_vesc->speed[3] = 5000.0;
		//teleop_vesc->setSpeedOut();

		// // // duty example (0.005~0.95)
		mecanum_robot_jacobian(teleop_vesc1->speed[0], teleop_vesc1->speed[1], teleop_vesc1->speed[2],
					  &(teleop_vesc1->duty[0]), &(teleop_vesc1->duty[1]), &(teleop_vesc1->duty[2]), &(teleop_vesc1->duty[3]));
		//teleop_vesc->duty[0] = 0.1;
		//teleop_vesc->duty[1] = 0.1;
		//teleop_vesc->duty[2] = 0.1;
		//teleop_vesc->duty[3] = 0.1;
		teleop_vesc1->setDutyCycleOut();
		//ROS_INFO("duty_0:%.2f, duty_1:%.2f, duty_2:%.2f, duty_3:%.2f", teleop_vesc->duty[0], teleop_vesc->duty[1], teleop_vesc->duty[2], teleop_vesc->duty[3]);

		// // position example (0~360 deg)
		//teleop_vesc->position[0] = 0.;
		// teleop_vesc->position[1] = 15.;
		// teleop_vesc->position[2] = 270.;
		// teleop_vesc->position[3] = -45.;
		//teleop_vesc->setPositionOut();

		teleop_vesc2->setSpeedOut();

		// Custom example
		//freq = teleop_vesc->speed[0];
		//teleop_vesc->custom_cmd_type[0] = COMM_SET_DPS;
		//teleop_vesc->custom_cmd_value[0] = teleop_vesc->dps[0]*amplitude*2*M_PI*freq*cos(2*M_PI*freq*(ros::Time::now() - teleop_vesc->startTime).toSec());
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
  }

  return 0;
}
