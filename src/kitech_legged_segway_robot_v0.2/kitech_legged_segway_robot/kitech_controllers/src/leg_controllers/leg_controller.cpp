#include <leg_controllers/leg_controller.h>

void LegController::init()
{
	_leg_desired.init();
	_virtual_spring_damper_controller.init();

	// time constants
	_ts = 0.001;
	_tc_leg_home  = 0.0;
	_t_leg_home = 6.0;
	omega_leg_home = 2.0*PI/_t_leg_home;

	// initial foot placement
    _x_foot[0].p(0) = 0.816;
    _x_foot[0].p(1) = 0.17+0.11;
    _x_foot[0].p(2) = 0.0;

    _x_foot[1].p(0) = 0.816;
    _x_foot[1].p(1) = -0.17-0.11;
    _x_foot[1].p(2) = 0.0;

    _x_foot[2].p(0) = -0.816;
    _x_foot[2].p(1) = 0.17+0.11;
    _x_foot[2].p(2) = 0.0;

    _x_foot[3].p(0) = -0.816;
    _x_foot[3].p(1) = -0.17-0.11;
    _x_foot[3].p(2) = 0.0;

	// initial body center
    _T_0.p(0) = 0.0;
    _T_0.p(1) = 0.0;
    _T_0.p(2) = 0.2;
}

void LegController::setControlInput(double cmd_T[3], 
									double cmd_R[3], 
									std::array<KDL::Vector, 4>& p_leg, 
									std::array<Eigen::Vector3d, 4>& v_leg,
									std::array<KDL::JntArray, 4>& G_leg) // 
{
	for (size_t i=0; i<3; i++)
	{
		_cmd_T[i] = cmd_T[i];
		_cmd_R[i] = cmd_R[i];
	}

	_p_leg = p_leg;
	_v_leg = v_leg;
	_G_leg = G_leg;
}

void LegController::getControlOutput(std::array<Eigen::Vector3d, 4>& F_leg)
{
    F_leg = _F_leg;
}

void LegController::compute(double _flag_leg_home[1])  
{
	_leg_desired.compute(_cmd_T, _cmd_R, _x_foot, _T_0);
	_leg_desired.getLegDesired(_xd);

	if (_flag_leg_home[0] > 0)
	{
		if (_tc_leg_home < _ts)  // define folding distance 
		{
			for (int i=0; i<4; i++)
			{
                _xd_n[i].p = _xd[i].p;

				_xd_amp[i].p(0) = (0.0 - _xd[i].p(0))*_ts/_t_leg_home;
				if (i == 0 || i == 2)
				{
					_xd_amp[i].p(1) = (0.11 - _xd[i].p(1))*_ts/_t_leg_home;
				}
				else
				{
					_xd_amp[i].p(1) = (-0.11 - _xd[i].p(1))*_ts/_t_leg_home;
				}
				
                _xd_amp[i].p(2) = (0.2 - _xd[i].p(2))*_ts/_t_leg_home;
			}

			_tc_leg_home = _tc_leg_home + _ts;
		}

        else if (_tc_leg_home < _t_leg_home)
        {
            for (int i=0; i<4; i++)
			{
				_xd_dot[i](0) = _xd_amp[i].p(0)*(1 - cos(omega_leg_home*_tc_leg_home));
                _xd_dot[i](1) = _xd_amp[i].p(1)*(1 - cos(omega_leg_home*_tc_leg_home));
                _xd_dot[i](2) = _xd_amp[i].p(2)*(1 - cos(omega_leg_home*_tc_leg_home));

                _xd_n[i].p = _xd_n[i].p + _xd_dot[i];
                _xd[i].p = _xd_n[i].p;
			}

            _tc_leg_home = _tc_leg_home + _ts;
        }

        else
        {
            _flag_leg_home[0] = 0;
            _tc_leg_home = 0.0;
			
			for (int i=0; i<4; i++)
			{
				_x_foot[i].p = _p_leg[i];
			}

			for (int i=0;i<3; i++)
			{
				_cmd_T[i] = 0.0;
				_cmd_R[i] = 0.0;
				_T_0.p(i) = 0.0;
			}
        }
    }
	printf("flag: %f \n", _flag_leg_home[0]);
	printf("tc: %f \n", _tc_leg_home);
	printf("x: %f ", _xd[0].p(0));
	printf("y: %f ", _xd[0].p(1));
	printf("z: %f ", _xd[0].p(2));
	printf("\n \n");

	_virtual_spring_damper_controller.setControlInput(_p_leg,_v_leg,_G_leg);
	_virtual_spring_damper_controller.compute(_xd);
	_virtual_spring_damper_controller.getControlOutput(_F_leg);
}

