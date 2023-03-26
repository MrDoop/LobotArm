#include "robot_arm.hpp"

#include <Arduino.h>

void RobotArm::setPosition(Vector3 target)
{
    calculateStateForBase(target);
    calculateStateForArm(target);
}

void RobotArm::calculateStateForBase(Vector3 target)
{
    state[0] = 90 + RAD_TO_DEG * atan2(position.x - target.x, position.z - target.z);
}
void RobotArm::calculateStateForArm(Vector3 target)
{
    double distance = Vector3::getDistance(joint1Offset, target);
    double y_diff = target.y - joint1Offset.y;
    double x_diff = sqrt(distance * distance - y_diff * y_diff);

    double p1_x = x_diff, p1_y = y_diff;

    double r1 = joint1_length, r2 = joint2_length;

    if (distance > r1 + r2)
        return;

    if (distance < r2 - r1)
        return;


    double a = (r1 * r1 - r2 * r2 + distance * distance) / (2 * distance);
    double h = sqrt(r1 * r1 - a * a);

    double middle_x = a*p1_x/distance;
    double middle_y = a*p1_y/distance;

    double intersection_x = middle_x - h * p1_y / distance;
    double intersection_y = middle_y + h * p1_x / distance;

    state[1] = -90 + RAD_TO_DEG * atan2(intersection_y, intersection_x);

    Vector3 joint2_pos = getJoint1Pos();

    distance = Vector3::getDistance(target, joint2_pos);
    y_diff = target.y - joint2_pos.y;
    x_diff = sqrt(distance * distance - y_diff * y_diff);

    state[2] = RAD_TO_DEG * atan2(y_diff, x_diff) - state[1];
}

Vector3 RobotArm::getJoint1Pos()
{
    double height = cos(DEG_TO_RAD * state[1]) * joint1_length;
    double distance = sin(DEG_TO_RAD * state[1]) * joint1_length;

    return position + joint1Offset + (Vector3){-cos(DEG_TO_RAD * state[0]) * distance, height, sin(DEG_TO_RAD * state[0]) * distance};
}

Vector3 RobotArm::getJoint2Pos()
{
    double height = sin(DEG_TO_RAD * (state[2] + state[1])) * joint2_length;
    double distance = cos(DEG_TO_RAD * (state[2] + state[1])) * joint2_length;

    return getJoint1Pos() + (Vector3){cos(DEG_TO_RAD * state[0]) * distance, height, -sin(DEG_TO_RAD * state[0]) * distance};
}
