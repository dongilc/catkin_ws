#pragma once

#include <array>
#include <boost/scoped_ptr.hpp>
// #include <iostream>
// #include <Eigen/Dense>

// ros control
#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>
#include <control_toolbox/pid.h>
#include <realtime_tools/realtime_buffer.h>

#include <pluginlib/class_list_macros.h>
#include <std_msgs/Float64MultiArray.h>
#include <angles/angles.h>

#include <urdf/model.h>

// kdl
#include <kdl/tree.hpp>
#include <kdl/kdl.hpp>
#include <kdl/chain.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/chainfksolverpos_recursive.hpp> // forward kinematics: position
#include <kdl/chainfksolvervel_recursive.hpp> // forward kinematics: velocity
#include <kdl/chainjnttojacsolver.hpp>        // jacobian
#include <kdl/chaindynparam.hpp>              // inverse dynamics


// controller class
#include <body_cmd_joy.h>
#include <leg_controllers/leg_controller.h>
#include <segway_controllers/segway_controller.h>


// joystick command
#include <std_msgs/Float32.h>
#include <sensor_msgs/Joy.h>


#define PI 3.141592
#define D2R PI/180.0
#define R2D 180.0/PI

namespace kitech_controllers
{

class MainController: public controller_interface::Controller<hardware_interface::EffortJointInterface>
{
public:

    bool init(hardware_interface::EffortJointInterface* hw, ros::NodeHandle &n);
    
    void starting(const ros::Time& time);
	void stopping(const ros::Time& time) { }

	void setCommand(const std_msgs::Float64MultiArrayConstPtr& msg);

    void update(const ros::Time& time, const ros::Duration& period);

    void print_state();

private:
    int _loop_count;
	double _t;


    // ros nodehandle
	ros::NodeHandle* _node_ptr;

    // joint handles
	unsigned int _n_joints;
	std::vector<std::string> _joint_names;
	std::vector<hardware_interface::JointHandle> _joints;
	std::vector<urdf::JointConstSharedPtr> _joint_urdfs;

    // kdl
	boost::scoped_ptr<KDL::Vector> _gravity;
	KDL::Tree 	_kdl_tree;
	
    std::array<KDL::Chain, 4>	_kdl_chain;
	std::array<boost::scoped_ptr<KDL::ChainFkSolverPos_recursive>, 4> _fk_pos_solver;
	std::array<boost::scoped_ptr<KDL::ChainJntToJacSolver>, 4> _jnt_to_jac_solver; 
	std::array<boost::scoped_ptr<KDL::ChainDynParam>, 4> _id_solver;   

    std::array<KDL::JntSpaceInertiaMatrix, 4> _M_leg; // joint space intertia matrix
    std::array<KDL::JntArray, 4> _C_leg;              // coriolis vector
    std::array<KDL::JntArray, 4> _G_leg;              // gravity torque vector

    // cmd, state
	realtime_tools::RealtimeBuffer<std::vector<double> > _commands_buffer;
    
    KDL::JntArray _tau_d;
    KDL::JntArray _q_d, _qdot_d;
    KDL::JntArray _q, _qdot;
    KDL::JntArray _q_e, _qdot_e;

    // * leg cmd, state
    double _cmd_T[3], _cmd_R[3];
    double _cmd_wheel[2];
    
    std::array<KDL::JntArray, 4> _q_leg, _qdot_leg;
    std::array<KDL::Frame, 4> _frame_leg;
    std::array<KDL::Vector, 4> _p_leg;
	std::array<Eigen::Vector3d, 4> _v_leg;
	std::array<Eigen::Vector3d, 4> _F_leg;
	std::array<Eigen::Vector3d, 4> _tau_leg;
	std::array<KDL::Jacobian, 4> _J_leg;
	std::array<Eigen::MatrixXd, 4> _Jv_leg;
  
    // * segway cmd, state
    Eigen::Vector2d _tau_segway;

    // topic
	ros::Subscriber _command_sub;
	
    // controllers class
    BodyCmdJoy _body_cmd_joy;
    LegController _leg_controller;
    SegwayController _segway_controller;
    
    // flags..
    double _flag_leg_home[1];
    double _flag_fold[1];
};

}