#ifndef MOTOR_H
#define MOTOR_H
#include "pin.h"

typedef struct Motor_s {
    CarPin* enable;
    CarPin* input0;
    CarPin* input1;
} Motor;

void Motor_SetupRPIPins(void);
Motor* Motor_Alloc(void);
void Motor_Setup(Motor* motor, int in1, int in2, int enable);
void Motor_Forward(Motor* motor);
void Motor_Reverse(Motor* motor);
void Motor_Stop(Motor* motor);
void Motor_SetSpeed(Motor* motor, int speed);
#endif /* MOTOR_H */
