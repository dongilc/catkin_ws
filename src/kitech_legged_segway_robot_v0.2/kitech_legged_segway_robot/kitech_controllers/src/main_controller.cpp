#include <main_controller.h>

using namespace kitech_controllers;

namespace kitech_controllers
{

bool MainController::init(hardware_interface::EffortJointInterface* hw, ros::NodeHandle &n)
{	
	_loop_count = 0;
	_node_ptr = &n;

	// List of controlled joints
	if (!n.getParam("joints", _joint_names))
	{
		ROS_ERROR("Could not find joint name");
		return false;
	}
	_n_joints = _joint_names.size();

	if(_n_joints == 0)
	{
		ROS_ERROR("List of joint names is empty.");
		return false;
	}
	else
	{
		ROS_INFO("Find %d joints", _n_joints);
	}

	// urdf
	urdf::Model urdf;
	if (!urdf.initParam("robot_description"))
	{
		ROS_ERROR("Failed to parse urdf file");
		return false;
	}
	else
	{
		ROS_INFO("Success to parse urdf file");
	}

	// joint handle
	for(int i=0; i<_n_joints; i++)
	{
		try
		{
			_joints.push_back(hw->getHandle(_joint_names[i]));
		}
		catch (const hardware_interface::HardwareInterfaceException& e)
		{
			ROS_ERROR_STREAM("Exception thrown: " << e.what());
			return false;
		}

		urdf::JointConstSharedPtr joint_urdf = urdf.getJoint(_joint_names[i]);
		if (!joint_urdf)
		{
			ROS_ERROR("Could not find joint '%s' in urdf", _joint_names[i].c_str());
			return false;
		}
		_joint_urdfs.push_back(joint_urdf); 
	}

	// kdl parser
	if (!kdl_parser::treeFromUrdfModel(urdf, _kdl_tree)){
		ROS_ERROR("Failed to construct kdl tree");
		return false;
	}

	// kdl chain
	std::string root_name, tip_name[4];

	root_name = "body";
	tip_name[0] = "LF_foot"; tip_name[1] = "RF_foot"; tip_name[2] = "LH_foot"; tip_name[3] = "RH_foot";

	_gravity.reset(new KDL::Vector(0.0, 0.0, -9.81));

	for (int i=0; i<4; i++)
	{
		if(!_kdl_tree.getChain(root_name, tip_name[i], _kdl_chain[i]))
		{
			ROS_ERROR_STREAM("Failed to get KDL chain from tree: ");
			ROS_ERROR_STREAM("  "<<root_name<<" --> "<<tip_name);

			return false;
		}
		else
		{
			_fk_pos_solver[i].reset(new KDL::ChainFkSolverPos_recursive(_kdl_chain[i]));
			_jnt_to_jac_solver[i].reset(new KDL::ChainJntToJacSolver(_kdl_chain[i]));
			_id_solver[i].reset(new KDL::ChainDynParam(_kdl_chain[i],*_gravity));
		}
	}

	_tau_d.data = Eigen::VectorXd::Zero(_n_joints);
	_q_d.data = Eigen::VectorXd::Zero(_n_joints);
	_qdot_d.data = Eigen::VectorXd::Zero(_n_joints);
	_q.data = Eigen::VectorXd::Zero(_n_joints);
	_qdot.data = Eigen::VectorXd::Zero(_n_joints);
	_q_e.data = Eigen::VectorXd::Zero(_n_joints);
	_qdot_e.data = Eigen::VectorXd::Zero(_n_joints);

	for (int i=0; i<4; i++)
	{
        // joint state
        _q_leg[i].resize(3);
		_qdot_leg[i].resize(3);

		// Jacobian
		_J_leg[i].resize(3);

		// Dynamics
		_M_leg[i].resize(3);
		_C_leg[i].resize(3);
		_G_leg[i].resize(3);
    }


	// initialization of controller class
	_body_cmd_joy.init();
	_leg_controller.init();
	_segway_controller.init();

    return true;
}

void MainController::starting(const ros::Time& time)
{
	_t = 0;
	
	// get joint positions
	for(size_t i=0; i<_n_joints; i++) 
	{
		_q(i) = _joints[i].getPosition();
		_qdot(i) = _joints[i].getVelocity();
	}

	ROS_INFO("Starting Main Controller");
}

void MainController::setCommand(const std_msgs::Float64MultiArrayConstPtr& msg)
{
	if(msg->data.size()!=_n_joints)
	{ 
	ROS_ERROR_STREAM("Dimension of command (" << msg->data.size() << ") does not match number of joints (" << _n_joints << ")! Not executing!");
	return; 
	}
	_commands_buffer.writeFromNonRT(msg->data);
}

void MainController::update(const ros::Time& time, const ros::Duration& period)
{
	std::vector<double> & commands = *_commands_buffer.readFromRT();
	
	double dt = period.toSec();
	double q_d_old;

	_t += dt;


	// update joint commands/states
	for (size_t i=0; i<_n_joints; i++)
	{
		// state
		_q(i) = _joints[i].getPosition();
		_qdot(i) = _joints[i].getVelocity();
	}

	// update state from tree (12x1) to each leg (4x3)
	for (size_t i = 0; i<12; i++)
	{
		if (i < 3)
		{
			_q_leg[0](i) = _q(i);
			_qdot_leg[0](i) = _qdot(i);
		}
		else if (i < 6)
		{
			_q_leg[1](i - 3) = _q(i);
			_qdot_leg[1](i - 3) = _qdot(i);
		}
		else if (i < 9)
		{
			_q_leg[2](i - 6) = _q(i);
			_qdot_leg[2](i - 6) = _qdot(i);
		}
		else
		{
			_q_leg[3](i - 9) = _q(i);
			_qdot_leg[3](i - 9) = _qdot(i);
		}
	}

	// forward kinematics & inverse dynamics
	for (size_t i=0; i<4; i++)
	{
		_fk_pos_solver[i]->JntToCart(_q_leg[i], _frame_leg[i]);

		_jnt_to_jac_solver[i]->JntToJac(_q_leg[i], _J_leg[i]);
		_Jv_leg[i] = _J_leg[i].data.block(0,0,3,3);	
		_p_leg[i] = _frame_leg[i].p;
		_v_leg[i] = _Jv_leg[i]*_qdot_leg[i].data;

		_id_solver[i]->JntToMass(_q_leg[i], _M_leg[i]);
		_id_solver[i]->JntToCoriolis(_q_leg[i], _qdot_leg[i], _C_leg[i]);
        _id_solver[i]->JntToGravity(_q_leg[i], _G_leg[i]);
	}

	// command from joystikc
	_body_cmd_joy.getBodyDesired(_cmd_T, _cmd_R, _cmd_wheel, _flag_leg_home, _flag_fold);
	// printf("flag: %f", _flag_fold[0]);
    // printf("\n");

	// leg controller
	_leg_controller.setControlInput(_cmd_T, _cmd_R, _p_leg, _v_leg, _G_leg);
	_leg_controller.compute(_flag_leg_home);
	_leg_controller.getControlOutput(_F_leg);

	for (int i=0; i<4; i++)
	{
		_tau_leg[i] = _Jv_leg[i].transpose() * _F_leg[i];
	}

	// segway controller
	_segway_controller.setControlInput();
	_segway_controller.compute();
	_segway_controller.getControlOutput(_tau_segway);

	
	// torque command (from each controller to main controller)
	for (int i = 0; i < _n_joints; i++)
	{
		if (i < 12) // leg controller
		{
			if (i < 3)
				_tau_d(i) = _tau_leg[0](i);
			else if (i < 6)
				_tau_d(i) = _tau_leg[1](i - 3);
			else if (i < 9)
				_tau_d(i) = _tau_leg[2](i - 6);
			else if (i < 12)
				_tau_d(i) = _tau_leg[3](i - 9);
		}
		else // segway controller
		{
			_tau_d(i) = _cmd_wheel[i-12];//_tau_segway(i - 12);
		}
	}

	// set torque input to joint handle
	for(int i=0; i<_n_joints; i++)
	{
		_joints[i].setCommand(_tau_d(i));
	}

	print_state();
}

void MainController::print_state()
{
	static int count = 0;
	if (count > 500)
	{
		printf("*********************************************************\n\n");
		printf("*** LF Joint Angle [deg.] ***\n");
		printf("q_0: %f, ", _q(0) * R2D);
		printf("q_1: %f, ", _q(1) * R2D);
		printf("q_2: %f, ", _q(2) * R2D);
		printf("\n");
		printf("*** LF Joint Torque [N/m] ***\n");
		printf("t_0: %f, ", _tau_leg[0](0));
		printf("t_1: %f, ", _tau_leg[0](1));
		printf("t_2: %f, ", _tau_leg[0](2));
		printf("\n");
		printf("\n");

		printf("*** RF Joint Angle [deg.] ***\n");
		printf("q_0: %f, ", _q(3) * R2D);
		printf("q_1: %f, ", _q(4) * R2D);
		printf("q_2: %f, ", _q(5) * R2D);
		printf("\n");
		printf("*** RF Joint Torque [N/m] ***\n");
		printf("t_0: %f, ", _tau_leg[1](0));
		printf("t_1: %f, ", _tau_leg[1](1));
		printf("t_2: %f, ", _tau_leg[1](2));
		printf("\n");
		printf("\n");

		printf("*** LH Joint Angle [deg.] ***\n");
		printf("q_0: %f, ", _q(6) * R2D);
		printf("q_1: %f, ", _q(7) * R2D);
		printf("q_2: %f, ", _q(8) * R2D);
		printf("\n");
		printf("*** LH Joint Torque [N/m] ***\n");
		printf("t_0: %f, ", _tau_leg[2](0));
		printf("t_1: %f, ", _tau_leg[2](1));
		printf("t_2: %f, ", _tau_leg[2](2));
		printf("\n");
		printf("\n");

		printf("*** RH Joint Angle [deg.] ***\n");
		printf("q_0: %f, ", _q(9) * R2D);
		printf("q_1: %f, ", _q(10) * R2D);
		printf("q_2: %f, ", _q(11) * R2D);
		printf("\n");
		printf("*** RH Joint Torque [N/m] ***\n");
		printf("t_0: %f, ", _tau_leg[3](0));
		printf("t_1: %f, ", _tau_leg[3](1));
		printf("t_2: %f, ", _tau_leg[3](2));
		printf("\n");
		printf("\n");

		printf("*** Wheel Torque [N/m] ***\n");
		printf("Left: %f, ", _cmd_wheel[0]);
		printf("Right: %f, ", _cmd_wheel[1]);
		printf("\n");
		printf("\n");

		printf("*********************************************************\n\n");
		printf("*** Leg Force form Leg Controller ***\n");
		printf("LF_Fx: %f, ", _F_leg[0](0));
		printf("LF_Fy: %f, ", _F_leg[0](1));
		printf("LF_Fz: %f, ", _F_leg[0](2));
		printf("\n");
		printf("\n");

		printf("RF_Fx: %f, ", _F_leg[1](0));
		printf("RF_Fy: %f, ", _F_leg[1](1));
		printf("RF_Fz: %f, ", _F_leg[1](2));
		printf("\n");
		printf("\n");

		printf("LH_Fx: %f, ", _F_leg[2](0));
		printf("LH_Fy: %f, ", _F_leg[2](1));
		printf("LH_Fz: %f, ", _F_leg[2](2));
		printf("\n");
		printf("\n");

		printf("RH_Fx: %f, ", _F_leg[3](0));
		printf("RH_Fy: %f, ", _F_leg[3](1));
		printf("RH_Fz: %f, ", _F_leg[3](2));
		printf("\n");
		printf("\n");

		printf("*********************************************************\n\n");
		printf("*** Joystick Command Verification ***\n");
		printf("X: %f, ", _cmd_T[0]);
		printf("Y: %f, ", _cmd_T[1]);
		printf("Z: %f, ", _cmd_T[2]);
		printf("\n");
		printf("\n");

		printf("Roll: %f, ", _cmd_R[0]);
		printf("Pitch: %f, ", _cmd_R[1]);
		printf("Yaw: %f, ", _cmd_R[2]);
		printf("\n");
		printf("\n");

		printf("*********************************************************\n\n");
		printf("*** Flag Test ***\n");
		printf("flag_leg_home: %f ", _flag_leg_home[0]);
		printf("\n");
		printf("\n");

		// printf("*********************************************************\n\n");
		// printf("*** q_leg ***\n");
		// printf("LF_q0: %f, ", _q_leg[0](0) * R2D);
		// printf("LF_q1: %f, ", _q_leg[0](1) * R2D);
		// printf("LF_q2: %f, ", _q_leg[0](2) * R2D);
		// printf("\n");
		// printf("RF_q0: %f, ", _q_leg[1](0) * R2D);
		// printf("RF_q1: %f, ", _q_leg[1](1) * R2D);
		// printf("RF_q2: %f, ", _q_leg[1](2) * R2D);
		// printf("\n");
		// printf("LH_q0: %f, ", _q_leg[2](0) * R2D);
		// printf("LH_q1: %f, ", _q_leg[2](1) * R2D);
		// printf("LH_q2: %f, ", _q_leg[2](2) * R2D);
		// printf("\n");
		// printf("\n");


		count = 0;
	}
	count ++;
}

}
PLUGINLIB_EXPORT_CLASS(kitech_controllers::MainController, controller_interface::ControllerBase)
