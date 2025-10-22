#include "chassis_task.h"

#include "robot.h"
#include "remote.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;

float chassis_rad;

Motor_t* motor_w1;
Motor_t* motor_w2;
Motor_t* motor_w3;
Motor_t* motor_w4;

float kinematicMap1[4][3] = {
        {-0.09, 0.09, 0.75},
        {-0.09, -0.09, 0.75},
        {0.09, -0.09, 0.75},
        {0.09, 0.09, 0.75}
    };

void kinematicMapping(float kinematicMap[4][3], float x_speed, float y_speed, float angular_speed, float* result) {
    for (int i = 0; i < 4; i++) {
        result[i] = kinematicMap[i][0] * x_speed + kinematicMap[i][1] * y_speed + kinematicMap[i][2] * angular_speed;
    }
}

void Update_Chassis_State() {
    float lx = g_remote.controller.left_stick.x / 660
    float ly = g_remote.controller.left_stick.y / 660

    g_robot_state.chassis.x_speed = lx * 1
    g_robot_state.chassis.y_speed = ly * 1
    g_robot_state.chassis.angular_speed = 0
}

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
    Update_Chassis_State();

    float result[4];
    kinematicMapping(kinematicMap1, 
        g_robot_state.chassis.x_speed, 
        g_robot_state.chassis.y_speed, 
        g_robot_state.chassis.angular_speed, 
        result);
    DJI_Motor_Set_Velocity(motor_w1, result[0]);
    DJI_Motor_Set_Velocity(motor_w2, result[1]);
    DJI_Motor_Set_Velocity(motor_w3, result[2]);
    DJI_Motor_Set_Velocity(motor_w4, result[3]);
    
}