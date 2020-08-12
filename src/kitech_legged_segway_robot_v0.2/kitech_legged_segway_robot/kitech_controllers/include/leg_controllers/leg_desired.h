#include <array>

//kdl
#include <kdl/kdl.hpp>
#include <kdl/tree.hpp>

class LegDesired
{
public:
    LegDesired() {}

    void init();

    void compute(double cmd_T[3], 
                double cmd_R[3],
                std::array<KDL::Frame, 4>& _x_foot,
                KDL::Frame _T_0);

    void getLegDesired(std::array<KDL::Frame, 4>& _xd);
public:
    std::array<KDL::Frame, 4> _x_offset;
    std::array<KDL::Frame, 4> _x_foot;
    std::array<KDL::Frame, 4> _leg_d;
    std::array<KDL::Vector, 4> _hip;

    KDL::Vector _cmd_T;
    KDL::Frame _T_d;
    KDL::Rotation _R_body_d;
};