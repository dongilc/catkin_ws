#pragma once

#include <array>

// kdl
// #include <kdl/tree.hpp>
// #include <kdl/kdl.hpp>
// #include <kdl/chain.hpp>
// #include <kdl/chaindynparam.hpp>
// #include <kdl_parser/kdl_parser.hpp>
// #include <kdl/chainfksolverpos_recursive.hpp> // forward kinematics: position
// #include <kdl/chainjnttojacsolver.hpp>        // jacobian
// #include <kdl/chaindynparam.hpp>              // inverse dynamics


#include <leg_controllers/virtual_spring_damper_controller.h>
#include <leg_controllers/leg_desired.h>

#define PI 3.141592

class LegController
{
public:
    LegController() {}

    void init();

    void setControlInput(double cmd_T[3], double cmd_R[3], std::array<KDL::Vector, 4>& p_leg, std::array<Eigen::Vector3d, 4>& v_leg, std::array<KDL::JntArray, 4>& G_leg);

    void getControlOutput(std::array<Eigen::Vector3d, 4>& F_leg);

    void compute(double _flag_leg_home[1]);

public:
    std::array<KDL::JntArray, 4> _G_leg;              // gravity torque vector

    std::array<KDL::Vector, 4> _p_leg;
	std::array<Eigen::Vector3d, 4> _v_leg;
    std::array<Eigen::Vector3d,4> _F_leg;
    std::array<Eigen::Vector3d,4> _tau_leg;

    KDL::Frame _T_0;
    std::array<KDL::Frame, 4> _x_foot;
    std::array<KDL::Frame, 4> _xd, _xd_amp, _xd_n;
    std::array<KDL::Vector, 4> _xd_dot;


    double _cmd_T[3], _cmd_R[3];

    float _ts, _tc_leg_home, _t_leg_home;
    float omega_leg_home;
    

    // controllers
    VirtualSpringDamperController _virtual_spring_damper_controller;
    LegDesired _leg_desired;
    
};