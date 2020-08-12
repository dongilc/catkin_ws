#include <segway_controllers/segway_controller.h>

void SegwayController::init()
{
}

void SegwayController::setControlInput()
{

}

void SegwayController::getControlOutput(Eigen::Vector2d &tau_segway)
{
    tau_segway = _tau_segway;
}

void SegwayController::compute()
{
    _tau_segway(0) = 50.0;
    _tau_segway(1) = 50.0;

}

