#ifndef MOTOR_H
#define MOTOR_H
typedef int Pin_t;

typedef struct Motor_s {
    Pin_t enable;
    Pin_t input0;
    Pin_t input1;
} Motor;

void Motor_SetupRPIPins(void);
Motor* Motor_Alloc(void);
void Motor_Setup(Motor* motor);
void Motor_Forward(Motor* motor);
void Motor_Reverse(Motor* motor);
void Motor_Stop(Motor* motor);
#endif /* MOTOR_H */
