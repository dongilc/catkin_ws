#include <leg_controllers/leg_desired.h>

void LegDesired::init()
{
    // hip joint offset from body center
    _x_offset[0].p(0) = 0.816;
    _x_offset[0].p(1) = 0.17;
    _x_offset[0].p(2) = -0.095;//0.37085;

    _x_offset[1].p(0) = 0.816;
    _x_offset[1].p(1) = -0.17;
    _x_offset[1].p(2) = -0.095;//0.37085;

    _x_offset[2].p(0) = -0.816;
    _x_offset[2].p(1) = 0.17;
    _x_offset[2].p(2) = -0.095;//0.37085;

    _x_offset[3].p(0) = -0.816;
    _x_offset[3].p(1) = -0.17;
    _x_offset[3].p(2) = -0.095;//0.37085;

}

void LegDesired::getLegDesired(std::array<KDL::Frame, 4>& _xd)
{
    for (size_t i=0; i<4; i++)
    {
        _xd[i].p = _leg_d[i].p;
    }
}

void LegDesired::compute(double cmd_T[3], 
                        double cmd_R[3],
                        std::array<KDL::Frame, 4>& _x_foot,
                        KDL::Frame _T_0)
{
    for (size_t i=0; i<3; i++)
    {
        _cmd_T[i] = cmd_T[i];
    }

    // // rotated hip joint position
    _R_body_d = KDL::Rotation(KDL::Rotation::RPY(cmd_R[0], cmd_R[1], cmd_R[2]));


    for (size_t i=0; i<4; i++)
    {
        _hip[i] = _R_body_d * _x_offset[i].p;
    }

    // desired leg vector
    for (size_t i=0; i<4; i++)
    {
        _leg_d[i].p = _x_foot[i].p - (_T_0.p + _cmd_T + _hip[i]);
    }
       
}



