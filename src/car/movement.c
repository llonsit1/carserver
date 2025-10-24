#include "global.h"
#include "motor.h"
#include "wheel.h"
#include "servo.h"

// Move the car in forward
void Move_Forward(void) {
    Wheel_MoveForward(WHEEL_R1);
    Wheel_MoveForward(WHEEL_L1);
    Wheel_MoveForward(WHEEL_L2);
    Wheel_MoveForward(WHEEL_R2);
}

void Move_Reverse(void) {
    Wheel_Reverse(WHEEL_R1);
    Wheel_Reverse(WHEEL_L1);
    Wheel_Reverse(WHEEL_L2);
    Wheel_Reverse(WHEEL_R2);
}

// Stop all the car wheels
void Move_Stop(void) {
    Wheel_Stop(WHEEL_R1);
    Wheel_Stop(WHEEL_L1);
    Wheel_Stop(WHEEL_L2);
    Wheel_Stop(WHEEL_R2);
    Servo_Stop();
}

void Move_Rotate(void) {
    Wheel_MoveForward(WHEEL_L2);
    Wheel_MoveForward(WHEEL_L1);
    Wheel_MoveForward(WHEEL_R2);
    Wheel_MoveForward(WHEEL_R1);
}

void Move_ForwardRight(void) {
    Wheel_Stop(WHEEL_L2);
    Wheel_MoveForward(WHEEL_R2);
    Wheel_MoveForward(WHEEL_L1);
    Wheel_Stop(WHEEL_R1);
}

void Move_ForwardLeft(void) {
    Wheel_MoveForward(WHEEL_L2);
    Wheel_Stop(WHEEL_R2);
    Wheel_MoveForward(WHEEL_R1);
    Wheel_Stop(WHEEL_L1);
}

void Move_Left(void) {
    Wheel_MoveForward(WHEEL_L2);
    Wheel_MoveForward(WHEEL_L1);
    Wheel_Reverse(WHEEL_R2);
    Wheel_Reverse(WHEEL_R1);
}

void Move_Right(void) {
    Wheel_Reverse(WHEEL_L2);
    Wheel_Reverse(WHEEL_L1);
    Wheel_MoveForward(WHEEL_R2);
    Wheel_MoveForward(WHEEL_R1);
}

void Move_ReverseRight(void) {
    Wheel_Stop(WHEEL_L2);
    Wheel_Reverse(WHEEL_R2);
    Wheel_Reverse(WHEEL_L1);
    Wheel_Stop(WHEEL_R1);
}

void Move_ReverseLeft(void) {
    Wheel_Reverse(WHEEL_L2);
    Wheel_Stop(WHEEL_R2);
    Wheel_Reverse(WHEEL_R1);
    Wheel_Stop(WHEEL_L1);
}

void Move_ServoUp(void) {
    Servo_Forward();
}

void Move_ServoDown(void) {
    Servo_Reverse();
}

void Move_ServoStop(void) {
    Servo_Stop();
}

void Move_SetSpeedLow(void) {
    Wheel_SetSpeed(WHEEL_L1, 50);
    Wheel_SetSpeed(WHEEL_L2, 50);
    Wheel_SetSpeed(WHEEL_R2, 50);
    Wheel_SetSpeed(WHEEL_R1, 50);
}

void Move_SetSpeedMedium(void) {
    Wheel_SetSpeed(WHEEL_L1, 100);
    Wheel_SetSpeed(WHEEL_L2, 100);
    Wheel_SetSpeed(WHEEL_R2, 100);
    Wheel_SetSpeed(WHEEL_R1, 100);
}

void Move_SetSpeedMaxium(void) {
    Wheel_SetSpeed(WHEEL_L1, 200);
    Wheel_SetSpeed(WHEEL_L2, 200);
    Wheel_SetSpeed(WHEEL_R2, 200);
    Wheel_SetSpeed(WHEEL_R1, 200);
}
