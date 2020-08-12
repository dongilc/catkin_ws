/*
 * diff_wheel_platform.h
 *
 *  Created on: Nov 29, 2017
 *      Author: cdi
 */

#include "diff_wheel_platform.h"
#include "computed_torque_control.h"

// Settings
#define VESC_ID_LEFT_WHEEL		0
#define VESC_ID_RIGHT_WHEEL		1
#define CAN_FORWARD_OFF			0
#define CAN_FORWARD_ON			1
#define BRAKE_THRESHOLD			11.0

/*
void TeleopVesc::speedsCallback(const vesc_msgs::VescGetSpeeds::ConstPtr& speeds_msg)
{
#ifdef PRINT_SENSOR_SPEEDS
	ROS_INFO("------------------------------------------");
	ROS_INFO("erpm1:%.2f", speeds_msg->speed1);
	ROS_INFO("erpm2:%.2f", speeds_msg->speed2);
#endif

	erpm[0] = speeds_msg->speed1;
	erpm[1] = speeds_msg->speed2;
}
*/

void TeleopVesc::stateCallback(const vesc_msgs::VescStateStamped::ConstPtr& state_msg)
{
#ifdef PRINT_SENSOR_CORE
	ROS_INFO("------------------------------------------");
	ROS_INFO("header:%6.4f", state_msg->header.stamp.toSec());
	ROS_INFO("voltage input:%.2f V", state_msg->state.voltage_input);
	ROS_INFO("temperature pcb:%.2f Deg", state_msg->state.temperature_pcb);
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
	if(joy->axes[RT]==-1 && joy->axes[LT]==-1)   {
		if(enable.data == false) {
			enable.data = true;
			if(ctm_state==0)	ctm_state = 1;	// init
			ROS_INFO("Control Enabled, State:%d", ctm_state);
		}
	}
	if(joy->buttons[RB])	{
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
	}
	else if(joy->buttons[BT_B])	{
		joy_cont_mode = 3;
	}

	switch (joy_cont_mode) {
	case 0:
		//default mode
		current[0] = -(10.0*joy_cmd_forward - 5.0*joy_cmd_steering);
		current[1] = 10.0*joy_cmd_forward + 5.0*joy_cmd_steering;
		brake[0] = brake[1] = 20.0*joy_cmd_brake;
		break;
	case 1:
		// CTM Speed Control
		brake[0] = brake[1] = 20.0*joy_cmd_brake;
		if(brake[0]<BRAKE_THRESHOLD) {
			target_vel[0] = 2.5*joy_cmd_forward;			// m/s
			target_vel[1] = 60.0*joy_cmd_steering*DEG2RAD;	// deg/sec
		}
		else {
			for(int i=0; i<NO_VESC; i++) target_vel[i] = 0.;
		}
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

void TeleopVesc::requestSpeeds()
{
	std_msgs::Bool msg;
	msg.data = true;
	vesc_cmd_get_speeds.publish(msg);
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
		// current
		// motor1
		setCmd(0., CAN_FORWARD_OFF, VESC_ID_LEFT_WHEEL);
		vesc_cmd_current.publish(cmd_msg);

		// current
		setCmd(0., CAN_FORWARD_ON, VESC_ID_RIGHT_WHEEL);
		vesc_cmd_current.publish(cmd_msg);
	}

	//ROS_INFO("en:%d, brake1=%.3f, brake2=%.3f, curr1=%.3f, curr2=%.3f", enable.data, brake[0], brake[1], current[0], current[1]);
}

int main(int argc, char **argv)              // 노드 메인 함수
{
  ros::init(argc, argv, "vesc_control_node");     // 노드명 초기화

  // TeleopVesc Class
  int num_of_wheel = 2;
  int degree_of_freedom = 2;
  TeleopVesc *teleop_vesc = new TeleopVesc(num_of_wheel, degree_of_freedom);
  teleop_vesc->enable.data = false;
  teleop_vesc->joy_cont_mode = 0;	// mode=0 default:current out
  teleop_vesc->ctm_state = 0;

  // CTM Class
  // Parameter of DEVIEW_DIFF_CTM
  int num_of_polepair = 15;
  double radius_of_wheel = 0.0638;
  double dcw_x = 0.176;		// distance from center to wheel of m1 along x
  double dcw_y = 0.158;		// distance from center to wheel of m1 along x
  int rate_hz = 500;	//hz
  int motor_direction[num_of_wheel] = {-1, 1};
  double M_dyn[num_of_wheel][10] = { {0.7120, -0.1283}, {0.7120, 0.1283} };
  double V_dyn[num_of_wheel] = {0., 0.};	//{0.1292, -0.0310};
  double Motor_Kt[num_of_wheel] = {0.6, 0.6}; //{0.5838, 0.6060};
  double Kp_ctm[num_of_wheel] = {10., 30.};	// Kp; for, rot
  double Kd_ctm[num_of_wheel] = {5., 15.};	// Kd; for, rot
  CTM *vesc_ctm = new CTM(num_of_wheel, degree_of_freedom, num_of_polepair, radius_of_wheel, dcw_x, dcw_y, rate_hz,
		  motor_direction, M_dyn, V_dyn, Motor_Kt);

  // ROS Loop
  ros::Rate loop_rate(rate_hz); //Hz
  ROS_INFO("Start Tele-operation");
  while (ros::ok())
  {
	  if(teleop_vesc->joy_cont_mode==0)		// Current Control Mode
	  {
		  teleop_vesc->setCurrentOut();
	  }
	  else if(teleop_vesc->joy_cont_mode==1)	// Computed Torque Control Mode
	  {
		  // 1. Initialization
		  if(teleop_vesc->ctm_state==1) {
			  for(int i=0; i<teleop_vesc->NO_DOF; i++) {
				  teleop_vesc->vel[i] = 0.;
				  teleop_vesc->target_vel[i] = 0.;
			  }

			  teleop_vesc->ctm_state = 2;
		  }

		  // 2. Computed Torque Method Run
		  if(teleop_vesc->ctm_state==2 && teleop_vesc->enable.data) {
			  teleop_vesc->requestSpeeds();
			  vesc_ctm->RunCTM(teleop_vesc->erpm,  teleop_vesc->vel, teleop_vesc->target_vel, teleop_vesc->current, Kp_ctm, Kd_ctm);
			  //
//			  ROS_INFO("CTM - Forward => Vel: %.3f, Target Vel: %.3f (m/s) / Rotation => Velocity: %.3f, Target Vel: %.3f (dps)",
//						  teleop_vesc->vel[0], teleop_vesc->target_vel[0], teleop_vesc->vel[1]*RAD2DEG, teleop_vesc->target_vel[1]*RAD2DEG);
//			  ROS_INFO("CTM - Current Out Left: %.3f A, Right: %.3f A", teleop_vesc->current[0], teleop_vesc->current[1]);
		  }

		  // 3. Disable CTM
		  if(teleop_vesc->ctm_state==3) {
			  for(int i=0; i<teleop_vesc->NO_VESC; i++) {
				  teleop_vesc->current[i] = 0.;
			  }
			  for(int i=0; i<teleop_vesc->NO_DOF; i++) {
				  teleop_vesc->vel[i] = 0.;
				  teleop_vesc->target_vel[i] = 0.;
			  }
			  teleop_vesc->ctm_state = 0;
		  }

		  teleop_vesc->setCurrentOut();
	  }

	  ros::spinOnce();
	  loop_rate.sleep();
  }

  return 0;
}
