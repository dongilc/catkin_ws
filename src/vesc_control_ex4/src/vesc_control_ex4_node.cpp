/*
 * vesc_control_ex4.cpp
 * 
 *  Created on: Nov. 23, 2018
 *      Author: cdi
 */

#include "vesc_control.h"

/*
 * HuboQ Remastered
 * 
 * VESC1 
 * #0 - Left Wheel
 * #1 - Right Wheel
 * 
 * VESC2
 * #0 - LHR
 * #1 - LHP1
 * #2 - LHP2
 * #3 - LHK1
 * #4 - LHK2
 * 
 * VESC3
 * #0 - LAP
 * #1 - LAR
 * #2 - LAY
 * 
 */

// Settings
#define VESC_ID_0				0
#define VESC_ID_1				1
#define VESC_ID_2				2
#define VESC_ID_3				3
#define VESC_ID_4				4
#define CAN_FORWARD_OFF			0
#define CAN_FORWARD_ON			1
#define BRAKE_CURRENT			10.
#define BRAKE_THRESHOLD			8.	// bigger than (BRAKE_CURRENT/2)

// COMM_SET Types
#define COMM_ALIVE				30
#define COMM_SET_DUTY			5
#define COMM_SET_CURRENT		6
#define COMM_SET_CURRENT_BRAKE	7
#define COMM_SET_RPM			8
#define COMM_SET_POS			9
#define COMM_SET_HANDBRAKE		10
#define COMM_SET_DPS			38
#define COMM_SET_GOTO			39
#define COMM_SET_FINDHOME		40
#define COMM_SET_DUTY_PAIR		41

// Conversions
#define RAD2DEG         		180.0/M_PI  // radian to deg
#define RPS2DPS					RAD2DEG	

// copy from vesc firmware
enum HUBOQ_STATUS {
	FREE = 0,
	FIND_HOME,
	FIND_HOME_COMPLETE,
	FIND_HOME_FAIL,
	POSITON_CONTROL,
	CURRENT_CONTROL
};

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
/*
void TeleopInput::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	static int joy_cont_mode;
	double joy_cmd_forward, joy_cmd_steering, joy_cmd_brake;

	// Logitech F710 Controller
	//ROS_INFO("%.3f, %.3f, %.3f, %.3f", joy->axes[0], joy->axes[1], joy->axes[2], joy->axes[3]);
	//ROS_INFO("%d, %d", joy->buttons[0], joy->buttons[1]);	// 0, 1, 2, 3 : X, A, B, Y

	// xbox initial value ignore
	std_msgs::Header jh = joy->header;
	if(jh.seq<10) {
		joy_cmd_forward = 0;
		joy_cmd_steering = 0;
		joy_cmd_brake = 0;
	}
	else {
		joy_cmd_forward = (joy->axes[3]);
		joy_cmd_steering = (joy->axes[2]);
	}

	// enable
	// Button X - Free
	if(joy->buttons[0]==1) {
		joy_cont_mode = 0;
		vh1_->custom_cmd_type[0] = COMM_SET_CURRENT;
		vh1_->custom_cmd_value[0] = 0.;
		ROS_INFO("Control Off");
	}
	// Button A
	else if(joy->buttons[1]==1) {
		joy_cont_mode = 1;
		vh1_->custom_cmd_type[0] = COMM_SET_CURRENT;
		ROS_INFO("Current Control Mode");
	}
	// Button B
	else if(joy->buttons[2]==1) {
		joy_cont_mode = 2;
		vh1_->custom_cmd_type[0] = COMM_SET_DUTY;
		ROS_INFO("Duty Control Mode");
	}
	// Button Y
	else if(joy->buttons[3]==1) {
		joy_cont_mode = 3;
		vh1_->custom_cmd_type[0] = COMM_SET_CURRENT_BRAKE;
		ROS_INFO("Brake Control Mode");
	}
	// Button LB
	else if(joy->buttons[4]==1) {
		joy_cont_mode = 4;
		vh1_->custom_cmd_type[0] = COMM_SET_DPS;
		ROS_INFO("DPS Control Mode");
	}
	// Button RB
	else if(joy->buttons[5]==1) {
		joy_cont_mode = 5;
		vh1_->custom_cmd_type[0] = COMM_SET_GOTO;
		ROS_INFO("GOTO Control Mode");
	}
	// Button back
	else if(joy->buttons[8]==1) {
		vh1_->custom_cmd_type[0] = COMM_SET_CURRENT;
		vh1_->custom_cmd_type[1] = COMM_SET_CURRENT;
		vh1_->custom_cmd_value[0] = 0.;
		vh1_->custom_cmd_value[1] = 0.;
		ROS_INFO("Release all motor");
	}
	// Button start
	else if(joy->buttons[9]==1) {
		vh1_->custom_cmd_type[0] = COMM_SET_FINDHOME;
		vh1_->custom_cmd_type[1] = COMM_SET_FINDHOME;
		vh1_->custom_cmd_value[0] = 0.;
		vh1_->custom_cmd_value[1] = 0.;
		ROS_INFO("HuboQ Find Home");
	}

	switch (joy_cont_mode) {
	case 0:
		//default mode
		vh1_->custom_cmd_value[0] = 0.;
		break;
	case 1:
		//
		vh1_->custom_cmd_value[0] = (2.0*joy_cmd_forward + 1.0*joy_cmd_steering);
		break;
	case 2:
		//
		vh1_->custom_cmd_value[0] = -(0.2*joy_cmd_forward + 0.1*joy_cmd_steering);
		break;
	case 3:
		//
		vh1_->custom_cmd_value[0] = (20.0*joy_cmd_forward + 10.0*joy_cmd_steering);
		break;
	case 4:
		//
		vh1_->custom_cmd_value[0] = (1000.0*joy_cmd_forward + 100.0*joy_cmd_steering);
		break;
	case 5:
		//
		vh1_->custom_cmd_value[0] = (10000.0*joy_cmd_forward + 1000.0*joy_cmd_steering);
		break;
	default:
		//
		break;
	}
}
*/

void TeleopInput::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	static int joy_cont_mode1, joy_btn_0, joy_btn_0_prev, joy_btn_1, joy_btn_1_prev;
	double joy_cmd_forward, joy_cmd_steering, joy_cmd_X, joy_cmd_Y, joy_cmd_Z, joy_cmd_aux;

	// Turnigy 9X controller
	//ROS_INFO("%.3f, %.3f, %.3f, %.3f, %.3f, %.3f", joy->axes[0], joy->axes[1], joy->axes[2], joy->axes[3], joy->axes[4], joy->axes[5]);
	//ROS_INFO("%d, %d", joy->buttons[0], joy->buttons[1]);	// 0, 1

	joy_cmd_X = (joy->axes[1]);
	joy_cmd_Y = (joy->axes[0]);
	joy_cmd_Z = (joy->axes[4]);
	
	joy_cmd_aux = (joy->axes[5]);

	joy_cmd_forward = (joy->axes[2]);
	joy_cmd_steering = (joy->axes[3]);

	joy_btn_0_prev = joy_btn_0;
	joy_btn_0 = joy->buttons[0];
	joy_btn_1_prev = joy_btn_1;
	joy_btn_1 = joy->buttons[1];

	// Button 0
	if(joy_btn_0==0 && joy_btn_0_prev==1) {
		joy_cont_mode1 = 0;
		ROS_INFO("Wheel Control Off");
	}
	else if(joy_btn_0==1 && joy_btn_0_prev==0) {
		joy_cont_mode1 = 1;
		ROS_INFO("Wheel Control On");
	}

	// Button 1
	if(joy_btn_1==1 && joy_btn_1_prev==0) {
		// find home - VESC2
		/*
		vh2_->custom_cmd_type[0] = COMM_SET_FINDHOME;
		vh2_->custom_cmd_type[1] = COMM_SET_FINDHOME;
		vh2_->custom_cmd_type[2] = COMM_SET_DUTY_PAIR;
		vh2_->custom_cmd_type[3] = COMM_SET_FINDHOME;
		vh2_->custom_cmd_type[4] = COMM_SET_DUTY_PAIR;
		vh2_->custom_cmd_value[0] = 0.;
		vh2_->custom_cmd_value[1] = 0.;
		vh2_->custom_cmd_value[2] = 1;
		vh2_->custom_cmd_value[3] = 0.;
		vh2_->custom_cmd_value[4] = 3;
*/
		// find home - VESC3
		vh3_->enable.data = false;

		vh3_->custom_cmd_type[0] = COMM_SET_FINDHOME;
		vh3_->custom_cmd_type[1] = COMM_SET_FINDHOME;
		vh3_->custom_cmd_value[0] = 100.;
		vh3_->custom_cmd_value[1] = 100.;
		vh3_->setCustomOut();
		ROS_INFO("HuboQ Find Home");

		vh3_->custom_cmd_type[0] = COMM_ALIVE;
		vh3_->custom_cmd_type[1] = COMM_ALIVE;
		vh3_->setCustomOut();
				
	}
	else if(joy_btn_1==0 && joy_btn_1_prev==1) {
		// release - VESC2
		vh2_->custom_cmd_type[0] = COMM_SET_CURRENT;
		vh2_->custom_cmd_type[1] = COMM_SET_CURRENT;
		vh2_->custom_cmd_type[2] = COMM_SET_CURRENT;
		vh2_->custom_cmd_type[3] = COMM_SET_CURRENT;
		vh2_->custom_cmd_type[4] = COMM_SET_CURRENT;
		vh2_->custom_cmd_value[0] = 0.;
		vh2_->custom_cmd_value[1] = 0.;
		vh2_->custom_cmd_value[2] = 0;
		vh2_->custom_cmd_value[3] = 0.;
		vh2_->custom_cmd_value[4] = 0;

		// release - VESC3
		vh3_->custom_cmd_type[0] = COMM_SET_CURRENT;
		vh3_->custom_cmd_type[1] = COMM_SET_CURRENT;
		vh3_->custom_cmd_value[0] = 0.;
		vh3_->custom_cmd_value[1] = 0.;
		vh3_->setCustomOut();
		vh3_->enable.data = false;

		ROS_INFO("HuboQ Release All");
	}

	switch (joy_cont_mode1) {
	case 0:
		// Wheel Control Off
		vh1_->duty[0] = 0.;
		vh1_->duty[1] = 0.;
		break;
	case 1:
		// Wheel Control On
		vh1_->duty[0] = (0.2*joy_cmd_forward - 0.1*joy_cmd_steering);
		vh1_->duty[1] = -(0.2*joy_cmd_forward + 0.1*joy_cmd_steering);
		break;
	default:
		//
		break;
	}
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

	if(this->last_app_status_code!=this->app_status_code)	
	{
		if(this->port_name=="/dev/ttyVESC3")
		{
			if(this->custom_status[0]==2 && this->last_custom_status[0]!=2) {
				ROS_INFO("VESC3, id=0, Success to find home");
			}
			else if(this->custom_status[1]==2 && this->last_custom_status[1]!=2) {
				ROS_INFO("VESC3, id=1, Success to find home");
			}

			if(this->custom_status[0]==2 && this->custom_status[1]==2 && this->enable.data!=true) {
				ROS_INFO("VESC3, Ready");
				this->enable.data = true;
			}
		}
		if(this->port_name=="/dev/ttyVESC2" && custom_rx_msg->can_devs_num==4) ROS_INFO("VESC2, Success to find home");
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
		if(this->port_name=="/dev/ttyACM1")
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
		if(this->port_name=="/dev/ttyACM1")
		{
			// duty
			for(int i=0; i<=1; i++) {
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
		// speed
		for(int i=0; i<=1; i++) {
			if(i==0) can_forw = CAN_FORWARD_OFF;
			else     can_forw = CAN_FORWARD_ON;
			setCmdMsg(speed[i], can_forw, i);
			vesc_cmd_speed.publish(cmd_msg);
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

/*
 * Main Function
 * 
 */
int main(int argc, char **argv)            
{
  ros::init(argc, argv, "vesc_control_node");

  // loop freq
//   int rate_hz = 500;	//hz
  int rate_hz = 100;	//hz

  // TeleopVesc Class
  TeleopVesc *teleop_vesc1 = new TeleopVesc(1, "/dev/ttyACM1"); 
  //TeleopVesc *teleop_vesc2 = new TeleopVesc(5, "/dev/ttyVESC2"); 
  //TeleopVesc *teleop_vesc3 = new TeleopVesc(3, "/dev/ttyVESC3"); 

// TeleopInput Class
  TeleopInput tele_input(teleop_vesc1, NULL, NULL);

  // ROS Loop
  int cnt_lp = 0;
  ros::Rate loop_rate(rate_hz); //Hz
  ROS_INFO("Start Tele-operation");
  teleop_vesc1->enable.data = true;
   
  teleop_vesc1->startTime = ros::Time::now();
  //teleop_vesc2->startTime = ros::Time::now();
  //teleop_vesc3->startTime = ros::Time::now();

  while (ros::ok())
  { 
	  
		// read encoder data.
		//teleop_vesc1->requestCustoms();
		//ROS_INFO("rps_0:%.2f(dps_0:%.2f), rad_0:%.2f", teleop_vesc1->rps[0], teleop_vesc1->rps[0]*RPS2DPS, teleop_vesc1->rad[0]);
		//ROS_INFO("rps_1:%.2f(dps_1:%.2f), rad_1:%.2f", teleop_vesc1->rps[1], teleop_vesc1->rps[1]*RPS2DPS, teleop_vesc1->rad[1]);
		//ROS_INFO("target_dps_0:%.2f, dps_0:%.2f, deg_0:%.2f", value_goto, teleop_vesc1->rps[0]*RPS2DPS, teleop_vesc1->rad[0]*RAD2DEG);
		//ROS_INFO("current_0:%.2f, dps_0:%.2f, deg_0:%.2f", value_goto, teleop_vesc1->rps[0]*RPS2DPS, teleop_vesc1->rad[0]*RAD2DEG);
		//ROS_INFO("target_dps_1:%.2f, dps_1:%.2f, deg_1:%.2f", -value_goto, teleop_vesc1->rps[1]*RPS2DPS, teleop_vesc1->rad[1]*RAD2DEG);

/*
		ROS_INFO("-------------------------------------------------------------------------------");
		for(int i=0; i<5; i++) {
		ROS_INFO("id:%d, rps_0:%.2f(dps_0:%.2f), curr_st:%.2f, duty_st:%.3f", 
					i, teleop_vesc2->rps[i], teleop_vesc2->rps[i]*RPS2DPS, teleop_vesc2->current_status[i], teleop_vesc2->duty_status[i]);
		}
*/

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
		//teleop_vesc->duty[0] = duty[0];
		//teleop_vesc->duty[1] = duty[1];
		//teleop_vesc->duty[2] = 0.1;
		// teleop_vesc->duty[3] = 0.5;
		//teleop_vesc1->setDutyCycleOut();

		//teleop_vesc2->setDutyCycleOut();
		//ROS_INFO("duty_0:%.2f, duty_1:%.2f", teleop_vesc->duty[0], teleop_vesc->duty[1]);

		// // position example (0~360 deg)
		//teleop_vesc->position[0] = 0.;
		// teleop_vesc->position[1] = 15.;
		// teleop_vesc->position[2] = 270.;
		// teleop_vesc->position[3] = -45.;
		//teleop_vesc->setPositionOut();

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

		// teleop_vesc1->custom_cmd_type[0] = COMM_SET_DPS;
		// teleop_vesc1->custom_cmd_value[0] = 300.;// + (40.)*sin(2*M_PI*(1.0)*(ros::Time::now() - teleop_vesc1->startTime).toSec());
		// teleop_vesc1->setCustomOut();
/*
		teleop_vesc2->setCustomOut();
		if(teleop_vesc2->custom_cmd_type[0]==COMM_SET_FINDHOME) teleop_vesc2->custom_cmd_type[0] = COMM_ALIVE;	// to run one time
		if(teleop_vesc2->custom_cmd_type[1]==COMM_SET_FINDHOME) teleop_vesc2->custom_cmd_type[1] = COMM_ALIVE;
		if(teleop_vesc2->custom_cmd_type[3]==COMM_SET_FINDHOME) teleop_vesc2->custom_cmd_type[3] = COMM_ALIVE;

		teleop_vesc3->requestCustoms();
		if(teleop_vesc3->enable.data==true) {
			teleop_vesc3->setCustomOut();
		}
		*/
		//if(teleop_vesc3->custom_cmd_type[0]==COMM_SET_FINDHOME) teleop_vesc3->custom_cmd_type[0] = COMM_ALIVE;	// to run one time
		//if(teleop_vesc3->custom_cmd_type[1]==COMM_SET_FINDHOME) teleop_vesc3->custom_cmd_type[1] = COMM_ALIVE;


		// IEEE ACCESS 19-12-16
		// Experiment
		// 1. Set current 3A - 30sec
		// teleop_vesc1->custom_cmd_type[0] = COMM_SET_CURRENT;
		// teleop_vesc1->custom_cmd_value[0] = 3.;
		// teleop_vesc1->setCustomOut();

		// // 2. Static Loading 1kg - 30sec
		// teleop_vesc1->custom_cmd_type[0] = COMM_SET_DPS;
		// teleop_vesc1->custom_cmd_value[0] = 0.;
		// teleop_vesc1->setCustomOut();

		// // 3. Dynamic Loading 1kg - 30sec
		// float freq = 1.0;
		// float amplitude = 8.;
		// float offset_deg = -160.;
		// teleop_vesc1->custom_cmd_type[0] = COMM_SET_GOTO;
		// teleop_vesc1->custom_cmd_value[0] = offset_deg + amplitude*2*M_PI*freq*cos(2*M_PI*freq*(ros::Time::now() - teleop_vesc1->startTime).toSec());;
		// teleop_vesc1->setCustomOut();

		// 4. Frequency Increasing Sine wave - 30sec
		static int cnt = 0;
		float tcnt = (cnt-rate_hz*4);
		float time = tcnt/rate_hz;
		float inc = tcnt/20.;
		float freq = 0.02*inc;
		if(freq<0)	freq = 0;
		float amplitude = 50000./inc;
		float DPS = amplitude*freq;
		if(DPS>20000) amplitude = 0;
		teleop_vesc1->custom_cmd_type[0] = COMM_SET_DPS;
		if(time==0)	DPS = 0;
		else teleop_vesc1->custom_cmd_value[0] = DPS*sin(2*M_PI*freq*time);
		teleop_vesc1->setCustomOut();
		//ROS_INFO("time = %.3f, DPS = %.3f, amplitude = %.3f, freq = %.3f, set_dps = %.3f, actual_dps = %.3f", time, DPS, amplitude, freq, teleop_vesc1->custom_cmd_value[0], teleop_vesc1->rps[0]*RPS2DPS);
		if(cnt==0) ROS_INFO("time, DPS, amplitude, freq, set_dps, actual_dps, current");
		if(amplitude>=0) ROS_INFO("%.3f %.3f %.3f %.3f %.3f %.3f %.3f", time, DPS, amplitude, freq, teleop_vesc1->custom_cmd_value[0], teleop_vesc1->rps[0]*RPS2DPS, teleop_vesc1->current_status[0]);
		if(cnt>(rate_hz*34)) cnt = 0;
		else cnt++;

		// // 5. DPS Control Low speed
		// static int cnt = 0;
		// int tcnt = (cnt-rate_hz*4);
		// float time = (float)tcnt/rate_hz;		
		// static float DPS = -1;
		// if(time==0)	DPS = 0;
		// if(time>0 && tcnt%2000==0) DPS += 5;
		// teleop_vesc1->custom_cmd_type[0] = COMM_SET_DPS;
		// teleop_vesc1->custom_cmd_value[0] = DPS;
		// if(DPS>=0) teleop_vesc1->setCustomOut();

		// if(DPS>=0) ROS_INFO("%.3f %d %.3f %.3f %.3f", time, tcnt, DPS, teleop_vesc1->custom_cmd_value[0], teleop_vesc1->rps[0]*RPS2DPS);

		// if(cnt>(rate_hz*34)) cnt = 0;
		// else cnt++;

		// // Extra test - 1min = 60s -> 360/60 = 6dps, 8*6 = 48dps(1rev/1min)
		// teleop_vesc1->custom_cmd_type[0] = COMM_SET_DPS;
		// teleop_vesc1->custom_cmd_value[0] = 48.;
		// teleop_vesc1->setCustomOut();

		// // 6. GOTO Control - Set 50hz
		// // Custom example
		// static int cnt = 0;
		// static float value_goto = 0;
		// static float value_goto_offset = 150;
		// cnt++;
		// if(cnt>=400) {
		// 	if(value_goto==-1440) 	value_goto = 0;
		// 	else if(value_goto==0)	value_goto = -1440;
		// 	cnt = 0;
		// 	ROS_INFO("%d %.3f", cnt, teleop_vesc1->custom_cmd_value[0]);
		// }
		// teleop_vesc1->custom_cmd_type[0] = COMM_SET_GOTO;
		// teleop_vesc1->custom_cmd_value[0] = value_goto + value_goto_offset;
		// teleop_vesc1->setCustomOut();	

		ros::spinOnce();
		loop_rate.sleep();
  }

  return 0;
}
