#pragma once

#include <array>

// kdl
#include <kdl/chaindynparam.hpp>  // for Vector2d type


class SegwayController
{
public:
    SegwayController() {}

    void init();

    void setControlInput();

    void getControlOutput(Eigen::Vector2d &tau_segway);

    void compute();

public:
    Eigen::Vector2d _tau_segway;

};