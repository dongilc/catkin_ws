#include <body_cmd_joy.h>

void BodyCmdJoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	std_msgs::Header jh = joy->header;

    _t_X = (joy->axes[BT_UD]);
    _t_Y = (joy->axes[BT_LR]);
    _t_Zp = (joy->buttons[LB]);
    _t_Zm = (joy->buttons[LT]);
    _r_Xp = (joy->buttons[BT_B]);
    _r_Xm = (joy->buttons[BT_X]);
    _r_Yp = (joy->buttons[BT_Y]);
    _r_Ym = (joy->buttons[BT_A]);
    _r_Zp = (joy->buttons[RB]);
    _r_Zm = (joy->buttons[RT]);

    _L = (joy->axes[JL_X]);
    _R = (joy->axes[JR_X]);

    _flag_fold = (joy->buttons[START]);
}

void BodyCmdJoy::init()
{
	// Subscriber
	_joy_sub = _nh.subscribe<sensor_msgs::Joy>("joy", 1, &BodyCmdJoy::joyCallback, this);

	ROS_INFO("Start Tele-operation");
}

void BodyCmdJoy::getBodyDesired(double cmd_T[3], 
                                double cmd_R[3], 
                                double cmd_wheel[2],
                                double flag_leg_home[1],
                                double flag_fold[1])
{
    _flag_leg_home = flag_leg_home[0];

    _cmd_T[0] = _cmd_T[0] + 0.00008*_t_X;
    _cmd_T[1] = _cmd_T[1] + 0.00005*_t_Y;
    _cmd_T[2] = _cmd_T[2] + 0.0003*_t_Zp - 0.0003*_t_Zm;

	_cmd_R[0] = _cmd_R[0] + 0.00005*_r_Xp - 0.00005*_r_Xm;
    _cmd_R[1] = _cmd_R[1] + 0.0001*_r_Yp - 0.0001*_r_Ym;
    _cmd_R[2] = _cmd_R[2] + 0.0001*_r_Zp - 0.0001*_r_Zm;

    _cmd_wheel[0] = _L*50;
    _cmd_wheel[1] = _R*50;

    for (size_t i=0; i<3; i++)
    {
        cmd_T[i] = _cmd_T[i];
        cmd_R[i] = _cmd_R[i];
        if (i<2)
        {
            cmd_wheel[i] = _cmd_wheel[i];
        }
    }

    if ((_flag_fold > 0) && (_flag_fold != _flag_fold_old))
    {
        _flag_leg_home = 1;
    }

    if ((_flag_leg_home < 1) && (_flag_leg_home != _flag_leg_home_old))
    {
        for (int i=0; i<3; i++)
        {
            _cmd_T[i] = 0.0;
            _cmd_R[i] = 0.0;
            if (i<2)
            {
                _cmd_wheel[i] = 0.0;
            }
        }
    }
    
    _flag_fold_old = _flag_fold;
    flag_fold[0] = _flag_fold;
    _flag_leg_home_old = _flag_leg_home;
    flag_leg_home[0] = _flag_leg_home;
}