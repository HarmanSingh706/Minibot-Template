#include "chassis_task.h"

#include "robot.h"
#include "remote.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;

float chassis_rad;

void Chassis_Task_Init()
{
    // Init chassis hardware
}

void Chassis_Ctrl_Loop()
{
    // Control loop for the chassis
}
/*
int main(void) {
    float result[4];
    float kinematicMap1[4][3] = {
        {-0.09, 0.09, 0.75},
        {-0.09, -0.09, 0.75},
        {0.09, -0.09, 0.75},
        {0.09, 0.09, 0.75}
    };


    kinematicMapping(kinematicMap1, 5, 7, 8, result);

    printf("Resulting vector:\n");
    for (int i = 0; i < 4; i++) {
        printf("%f\n", result[i]);
    }

    return 0;
}
*\