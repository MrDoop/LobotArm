#include "robot_arm.hpp"
#include <unity.h>


void clean_init() 
{
    auto arm = RobotArm();
    
    TEST_ASSERT_TRUE((arm.state[0] == 0));
    TEST_ASSERT_TRUE((arm.state[1] == 0));
    TEST_ASSERT_TRUE((arm.state[2] == 0));
    TEST_ASSERT_TRUE((arm.state[3] == 0));
}

void state_above() 
{
    auto arm = RobotArm();
    
    Vector3 target = {0,1,0};
    // armsetPosition(target);

    arm.getJoint1Pos();
    // TEST_ASSERT_TRUE((arm.state[0] == 0));
    // TEST_ASSERT_TRUE((arm.state[1] == 0));
    // TEST_ASSERT_TRUE((arm.state[2] == 0));
    // TEST_ASSERT_TRUE((arm.state[3] == 0));
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(clean_init);
    RUN_TEST(state_above);
    UNITY_END();
}