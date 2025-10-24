#include "global.h"
#include "motor.h"
#include "wheel.h"

#define SERVER_MOTOR_IN1 10
#define SERVER_MOTOR_IN2 9

typedef struct Servo_s {
    Motor* motor;
} Servo;

Servo servo;

void Servo_Init(void) {
    servo.motor = malloc(sizeof(Motor));

    if (servo.motor == NULL) {
        puts("FATAL: Can't allocate memory!");
        abort();
    }

    Motor_Setup(servo.motor, SERVER_MOTOR_IN1, SERVER_MOTOR_IN2, -1);
}

void Servo_Forward(void) {
    Motor_Forward(servo.motor);
}

void Servo_Reverse(void) {
    Motor_Reverse(servo.motor);
}

void Servo_Destroy(void) {
    free(servo.motor);
}

void Servo_Stop(void) {
    Motor_Stop(servo.motor);
}
