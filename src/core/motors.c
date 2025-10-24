#include "pin.h"
#include "global.h"
#include "motor.h"

#define L298N_MAX_ANALOG_RANGE 200

static bool sPinsInitialized = false;
bool sPinsDebug = true;

#define DEBUG_MSG(x) if (sPinsDebug) puts(x)

Motor* Motor_Alloc(void) {
    Motor* newMotor = malloc(sizeof(Motor));

    if (newMotor == NULL) {
        puts("Error: can't allocate motor");
        return NULL;
    }

    return newMotor;
}

void Motor_Setup(Motor* motor, int in1, int in2, int enable) {
    //TODO: pinMode the enable pin
    printf("Setting up motor with input0: %d and input1: %d\n", in1, in2);
    bool setEnable = true;

    if (enable == -1) {
        printf("motors.c: Not using enable pin for this motor\n");
        setEnable = false;
    }

    if (in1 == -1 || in2 == -1) {
        printf("motors.c: Invalid input values!\n");
        return;
    }

    if (setEnable) {
        motor->enable = Pin_Enable(enable, MODE_ANALOG_WRITE);
        Pin_SetRange(motor->enable, L298N_MAX_ANALOG_RANGE);
    }

    motor->input0 = Pin_Enable(in1, MODE_WRITE);
    motor->input1 = Pin_Enable(in2, MODE_WRITE);
}

static void Motor_CheckPins(void) {
    if (!sPinsInitialized) {
        printf("ERROR: WiringPi not initialized aborting..");
        exit(EXIT_FAILURE);
    }
}

void Motor_Forward(Motor* motor) {
    if (motor == NULL) {
        puts("Motor not initialized refusing to move it forward!\n");
        return;
    }

    DEBUG_MSG("Moving motor in forward");
    Pin_Write(motor->input0, VALUE_HIGH);
    Pin_Write(motor->input1, VALUE_LOW);
}

void Motor_Reverse(Motor* motor) {
    if (motor == NULL) {
        puts("Motor not initialized refusing to move it in reverse!\n");
        return;
    }

    DEBUG_MSG("Moving motor in reverse");
    Pin_Write(motor->input0, VALUE_LOW);
    Pin_Write(motor->input1, VALUE_HIGH);
}

void Motor_Stop(Motor* motor) {
    if (motor == NULL) {
        puts("Motor not initialized refusing to stop it!\n");
        return;
    }

    Pin_Write(motor->input0, VALUE_LOW);
    Pin_Write(motor->input1, VALUE_LOW);
}

void Motor_SetSpeed(Motor* motor, int speed) {
    if (speed < 0 || speed > L298N_MAX_ANALOG_RANGE) {
        printf("motors.c: ERROR Invalid speed!\n");
        return;
    }

    Pin_AnalogWrite(motor->enable, speed);
}

void Motor_Free(Motor* motor) {
    free(motor->input0);
    free(motor->input1);
    free(motor);
}
