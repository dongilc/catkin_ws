/*
 *  me_exp_2020_node.cpp
 * 
 *  Created on: Aug. 13, 2020
 *      Author: cdi
 */

#include "vesc_control.h"
#include <std_msgs/Float32MultiArray.h>

// Settings
#define VESC_ID_0				0
#define VESC_ID_1				1
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

// Uncomment this only when you want to see the below infomations.
//#define PRINT_SENSOR_CORE
//#define PRINT_SENSOR_CUSTOMS

// sub
float Method = 2;
float position_x = 180+150;
float position_y = 0;
float th1 = 0;
float th2 = 0;

int cnt = 0;
float value_goto_0 = 0;
float value_goto_offset_0 = 0;
float value_goto_1 = 0;
float value_goto_offset_1 = -16;
// 0 :: offset = 2916, 360deg = 9720, + = CCW, range 0~180;
// 1 :: offset = -220, 360deg = 2880, + = CW, range = +-155;
float COS2 = 0;
float SIN2_p = 0;
float SIN2_m = 0;
float th1_1 = 0;
float th1_2 = 0;
float th2_1 = 0;
float th2_2 = 0;

void TeleopInput::keyboardCallback(const geometry_msgs::Twist::ConstPtr& cmd_vel) {}

void TeleopInput::joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {}

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

void kinematicsCallback(const std_msgs::Float32MultiArray& kinematics)
{
	Method = kinematics.data.at(0);
	if(Method == 0) //FK
	{
		th1 = kinematics.data.at(1);
		th2 = kinematics.data.at(2);
	}
	else if(Method == 1) //IK
	{
		position_x = kinematics.data.at(1);
		position_y = kinematics.data.at(2);
	}
	else if(Method == 2) //RESET
	{
		th1 = 0;
		th2 = 0;
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
    int rate_hz = 50;	//hz

    // TeleopVesc Class
    TeleopVesc *teleop_vesc1 = new TeleopVesc(2, "/dev/ttyACM0"); 

    // TeleopInput Class
    TeleopInput tele_input(teleop_vesc1, NULL, NULL);

    // ROS Loop
    int cnt_lp = 0;
    ros::Rate loop_rate(rate_hz); //Hz
    ROS_INFO("Start Tele-operation");
    teleop_vesc1->enable.data = true;
    teleop_vesc1->startTime = ros::Time::now();

	//sub
	ros::NodeHandle nh_;
	ros::Subscriber sub = nh_.subscribe("kinematics", 1000, kinematicsCallback);

    while (ros::ok())
    { 
		

		//FK
		if(Method == 0)
		{
			position_x = 180*cos(th1*3.141592/180) + 150*cos((th1 + th2)*3.141592/180);
			position_y = 180*sin(th1*3.141592/180) + 150*sin((th1 + th2)*3.141592/180);
		}
		//IK
		else if(Method == 1)
		{
			COS2 = (pow(position_x, 2) + pow(position_y, 2) - 180*180 - 150*150)/(2*180*150);
			SIN2_p = sqrt(1-pow(COS2, 2));
			SIN2_m = -sqrt(1-pow(COS2, 2));
			th2_1 = atan2(SIN2_p,COS2)/3.141592*180;
			th1_1 = (atan2(position_y,position_x) - atan2(150*SIN2_p,180+150*COS2))/3.141592*180;
			th2_2 = atan2(SIN2_m,COS2)/3.141592*180;
			th1_2 = (atan2(position_y,position_x) - atan2(150*SIN2_m,180+150*COS2))/3.141592*180;

			if(position_x > 0)
			{
				if(th2_1 <= 0)
				{
					th1 = th1_1;
					th2 = th2_1;
				}
				else if(th2_2 <= 0)
				{
					th1 = th1_2;
					th2 = th2_2;
				}				
			}
			else if(position_x <= 0)
			{
				if(th2_1 >= 0)
				{
					th1 = th1_1;
					th2 = th2_1;
				}
				else if(th2_2 >= 0)
				{
					th1 = th1_2;
					th2 = th2_2;
				}
			}
		}
		//RESET
		else if(Method == 2)
		{
			th1 = 0;
			th2 = 0;
			position_x = 180+150;
			position_y = 0;
		}

		cnt++;

		
		if((180 < th1) || (th1 < 0))
		{
			ROS_INFO("OUT of Angle Range!");
		}

		else if((155 < th2) || (th2 < -150))
		{
			ROS_INFO("OUT of Angle Range!");
		}
		else if(position_y < 0)
		{
			ROS_INFO("Goal position is located  in Dead Zone :1");
		}
		else if(sqrt(pow(position_x,2) + pow(position_y,2)) > (180 + 150))
		{
			ROS_INFO("Goal position is located  in Dead Zone :2");
		}
		else if(((position_y <60) && (abs(position_x) < 60)) && (sqrt(pow(position_x,2) + pow(position_y,2)) < 60))
		{
			ROS_INFO("Goal position is located  in Dead Zone :3");
		}

		else
		{
			if(cnt>=400)
			{
		  		value_goto_0 = th1*23;
				value_goto_1 = -th2*8;

		  		cnt = 0;
		  		//ROS_INFO("custom_cmd_value[0] = %.3f custom_cmd_value[1] = %.3f", cnt, teleop_vesc1->custom_cmd_value[0], teleop_vesc1->custom_cmd_value[1]);
				if(Method == 0)
				{
					ROS_INFO("Method = FK, th1 = %f, th2 = %f", th1, th2);
				}
				else if(Method == 1)
				{
					ROS_INFO("Method = IK, position_x = %f, position_y = %f", position_x, position_y);
				}
				else if(Method == 2)
				{
					ROS_INFO("Ready");
				}

				//ROS_INFO("Method = %f, th1 = %f, th2 = %f, position_x = %f, position_y = %f", Method, th1, th2, position_x, position_y);
				
			}
			
			teleop_vesc1->custom_cmd_type[0] = COMM_SET_DPS;
			teleop_vesc1->custom_cmd_value[0] = 0;//value_goto_0 + value_goto_offset_0;
    		teleop_vesc1->custom_cmd_type[1] = COMM_SET_DPS;
    		teleop_vesc1->custom_cmd_value[1] = 0;//value_goto_1 + value_goto_offset_1;
			teleop_vesc1->setCustomOut();
			
		}
			

		ros::spinOnce();
		loop_rate.sleep();
    }

   return 0;
}
