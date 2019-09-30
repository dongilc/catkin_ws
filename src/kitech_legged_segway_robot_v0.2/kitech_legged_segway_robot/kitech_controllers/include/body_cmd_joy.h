#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include <sensor_msgs/Joy.h>
#include <Eigen/Eigen>

class BodyCmdJoy
{
public:
    BodyCmdJoy() {}

    void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

    void init();

    void getBodyDesired(double cmd_T[3], 
                        double cmd_R[3], 
                        double cmd_wheel[2],
                        double flag_leg_home[1],
                        double flag_fold[1]);


private:
    // Joystick, Joy Axis Index
    typedef enum {
    JL_Y = 0,
    JL_X,
    JR_Y,
    JR_X,
    BT_LR,
    BT_UD
    } JOY_AXIS_LOGITECH_F710;

    // Joystick, Joy Button Index
    typedef enum {
    BT_X = 0,
    BT_A,
    BT_B,
    BT_Y,
    LB,
    RB,
    LT,
    RT,
    BACK,
    START,
    STICK_L,
    STICK_R
    } JOY_BUTTON_LOGITECH_F710;

    ros::Subscriber _joy_sub;
    ros::NodeHandle _nh;

    double _t_X, _t_Y, _t_Zp, _r_Xp, _r_Yp, _r_Zp;
    double             _t_Zm, _r_Xm, _r_Ym, _r_Zm;
    double _L, _R;

    double _cmd_T[3], _cmd_R[3];
    double _cmd_wheel[2];
    
    double _flag_fold, _flag_fold_old;
    double _flag_leg_home, _flag_leg_home_old;


};
