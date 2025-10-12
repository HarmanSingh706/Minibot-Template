#include "chassis_task.h"

#include "robot.h"
#include "remote.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;

float chassis_rad;

void Chassis_Task_Init()
{

    // Create config structs for each motor
    Motor_Config_t chassis_w1 = {
        .can_bus = 1, // what can bus the motor is on
        .speed_controller_id = 1, // identifier for each motor
        .offset = 0, // Initial offset of the motor (used for encoder)
        .control_mode = VELOCITY_CONTROL, // Control mode of the motor
        .motor_reversal = MOTOR_REVERSAL_NORMAL, // Direction of the motor
        .velocity_pid = // pid
            {
                .kp = 500.0f,
                .kd = 0.0f,
                .kf = 0.0f,
                .output_limit = M2006_MAX_CURRENT, // m2006 is the motor
            },
    };
    Motor_Config_t chassis_w2 = {
        .can_bus = 1,
        .speed_controller_id = 2,
        .offset = 0,
        .control_mode = VELOCITY_CONTROL,
        .motor_reversal = MOTOR_REVERSAL_REVERSED,
        .velocity_pid =
            {
                .kp = 500.0f,
                .kd = 0.0f,
                .kf = 0.0f,
                .output_limit = M2006_MAX_CURRENT,
            },
    };
    Motor_Config_t chassis_w3 = {
        .can_bus = 1,
        .speed_controller_id = 3,
        .offset = 0,
        .control_mode = VELOCITY_CONTROL,
        .motor_reversal = MOTOR_REVERSAL_NORMAL,
        .velocity_pid =
            {
                .kp = 500.0f,
                .kd = 0.0f,
                .kf = 0.0f,
                .output_limit = M2006_MAX_CURRENT,
            },
    };
    Motor_Config_t chassis_w4 = {
        .can_bus = 1,
        .speed_controller_id = 4,
        .offset = 0,
        .control_mode = VELOCITY_CONTROL,
        .motor_reversal = MOTOR_REVERSAL_REVERSED,
        .velocity_pid =
            {
                .kp = 500.0f,
                .kd = 0.0f,
                .kf = 0.0f,
                .output_limit = M2006_MAX_CURRENT,
            },
    };

    //create motor instances
    motor_w1 = DJI_Motor_Init(&chassis_w1, M2006); 
    motor_w2 = DJI_Motor_Init(&chassis_w2, M2006);
    motor_w3 = DJI_Motor_Init(&chassis_w3, M2006);
    motor_w4 = DJI_Motor_Init(&chassis_w4, M2006);
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