#include "gimbal_task.h"

#include "robot.h"
#include "remote.h"
#include "user_math.h"
#include "chassis_task.h"
#include "dji_motor.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;
extern Gimbal_Target_t g_gimbal_target;

#include "dji_motor.h"

#define MAX_SPEED 100
#define GEARRATIO 1.5
#define JOYSTICK_MAX 660.0

DJI_Motor_Handle_t* motor_w5;

float gimbal_velocity = 0.0;

void Gimbal_Task_Init()
{
    Motor_Config_t chassis_w5 = {
        .can_bus = 1, // what can bus the motor is on
        .speed_controller_id = 5, // identifier for each motor
        .offset = 0, // Initial offset of the motor (used for encoder)
        .control_mode = VELOCITY_CONTROL, // Control mode of the motor
        .motor_reversal = MOTOR_REVERSAL_NORMAL, // Direction of the motor
        .velocity_pid = // pid
            {
                .kp = 500.0f,
                .kd = 0.0f,
                .kf = 0.0f,
                .output_limit = M2006_MAX_CURRENT_INT, // m2006 is the motor
            },
    };

    //create motor instances
    motor_w5 = DJI_Motor_Init(&chassis_w5, M2006);
}

void Update_Gimbal_State() {
    float gx = g_remote.controller.right_stick.x / JOYSTICK_MAX;
    gimbal_velocity = gx * MAX_SPEED;
}

void Gimbal_Ctrl_Loop()
{
    // Control loop for gimbal
    Update_Gimbal_State();

    DJI_Motor_Set_Velocity(motor_w5, gimbal_velocity);
}
