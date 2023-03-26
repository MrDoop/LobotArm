#pragma once
#include "vector3.hpp"


struct RobotArm
{
    void setPosition(Vector3 target);

    void calculateStateForBase(Vector3 target);
    void calculateStateForArm(Vector3 target);

    Vector3 getJoint1Pos();
    Vector3 getJoint2Pos();

    const double joint1_length = .105;
    const double joint2_length = .15;
    double state[4] = {};

    const Vector3 joint1Offset = {0, 0, 0};
    const Vector3 position = {0, 0, 0};

};