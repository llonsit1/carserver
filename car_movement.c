#include "global.h"
#include "motor.h"
#include "Wheel.h"

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
}

void Move_Rotate(void) {
    Wheel_MoveForward(WHEEL_L2);
    Wheel_MoveForward(WHEEL_L1);
    Wheel_MoveForward(WHEEL_R2);
    Wheel_MoveForward(WHEEL_R1);
}

void Move_ForwardRight(void) {
    Wheel_MoveForward(WHEEL_L2);
    Wheel_MoveForward(WHEEL_R2);
    Wheel_Stop(WHEEL_L1);
    Wheel_Stop(WHEEL_R1);
}

void Move_ForwardLeft(void) {
    Wheel_Stop(WHEEL_L2);
    Wheel_Stop(WHEEL_R2);
    Wheel_MoveForward(WHEEL_L1);
    Wheel_MoveForward(WHEEL_R1);
}

void Move_Left(void) {
    Wheel_Forward(WHEEL_L2);
    Wheel_Forward(WHEEL_L1);
    Wheel_Reverse(WEHEEL_R2);
    Wheel_Reverse(WEHEEL_R1);
}

void Move_Right(void) {
    Wheel_Reverse(WHEEL_L2);
    Wheel_Reverse(WHEEL_L1);
    Wheel_Forward(WEHEEL_R2);
    Wheel_Forward(WEHEEL_R1);
}

void Move_ReverseRight(void) {
    Wheel_Reverse(WHEEL_L2);
    Wheel_Reverse(WHEEL_R2);
    Wheel_Stop(WHEEL_L1);
    Wheel_Stop(WHEEL_R1);
}

void Move_ReverseLeft(void) {
    Wheel_Stop(WHEEL_L2);
    Wheel_Stop(WHEEL_R2);
    Wheel_Reverse(WHEEL_L1);
    Wheel_Reverse(WHEEL_R1);
}
