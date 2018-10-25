/*
 * tennis_ball_machine_node.h
 *
 *  Created on: Jan 12, 2018
 *      Author: cdi
 */

#include "tennis_ball_machine_node.h"

// Settings
#define VESC_ID_LEFT_WHEEL		0
#define VESC_ID_RIGHT_WHEEL		1
#define CAN_FORWARD_OFF			0
#define CAN_FORWARD_ON			1
#define BRAKE_THRESHOLD			11.0

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
#endif

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
	double joy_cmd_forward, joy_cmd_steering, joy_cmd_brake;

	// xbox initial value ignore
	std_msgs::Header jh = joy->header;
	if(jh.seq<10) {
		joy_cmd_forward = 0;
		joy_cmd_steering = 0;
		joy_cmd_brake = 0;
	}
	else {
		joy_cmd_forward = (joy->axes[JR_X]);
		joy_cmd_steering = (joy->axes[JL_Y]);
		joy_cmd_brake = (joy->axes[RT]-1)/(-2.0);
	}

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
		  setCmd(brake[0], CAN_FORWARD_OFF, VESC_ID_LEFT_WHEEL);
		  vesc_cmd_brake.publish(cmd_msg);

		  // motor2
		  setCmd(brake[1], CAN_FORWARD_ON, VESC_ID_RIGHT_WHEEL);
		  vesc_cmd_brake.publish(cmd_msg);
	  }
	  else {
		  // current
		  // motor1
		  setCmd(current[0], CAN_FORWARD_OFF, VESC_ID_LEFT_WHEEL);
		  vesc_cmd_current.publish(cmd_msg);

		  // current
		  setCmd(current[1], CAN_FORWARD_ON, VESC_ID_RIGHT_WHEEL);
		  vesc_cmd_current.publish(cmd_msg);
	  }
	}
	else
	{
		// current zero
		// motor1
		setCmd(0., CAN_FORWARD_OFF, VESC_ID_LEFT_WHEEL);
		vesc_cmd_current.publish(cmd_msg);

		// motor2
		setCmd(0., CAN_FORWARD_ON, VESC_ID_RIGHT_WHEEL);
		vesc_cmd_current.publish(cmd_msg);
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

int main(int argc, char **argv)              // 노드 메인 함수
{
  ros::init(argc, argv, "vesc_control_node");     // 노드명 초기화

  // TeleopVesc Class
  int num_of_wheel = 2;
  int degree_of_freedom = 2;
  TeleopVesc *teleop_vesc = new TeleopVesc(num_of_wheel, degree_of_freedom);
  teleop_vesc->enable.data = false;
  teleop_vesc->cruise.data = false;
  teleop_vesc->joy_cont_mode = 0;	// mode=0 default:current out
  teleop_vesc->ctm_state = 0;

  // ROS Loop
  int rate_hz = 500;	//hz
  ros::Rate loop_rate(rate_hz); //Hz
  ROS_INFO("Start Tele-operation");
  while (ros::ok())
  {
	  if(teleop_vesc->joy_cont_mode==0)		// Current Control Mode
	  {
		  teleop_vesc->requestCustoms();
		  //teleop_vesc->setCurrentOut();
		  teleop_vesc->setSpeedOut();
	  }

	  ros::spinOnce();
	  loop_rate.sleep();
  }

  return 0;
}
