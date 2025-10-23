#include "motor.h"
#include "global.h"

static bool sPinsInitialized = false;
bool sPinsDebug = true;

#define DEBUG_MSG(x) if (sPinsDebug) puts(x)

void Motor_SetupRPIPins(void) {
    wiringPiSetupGpio();
    sPinsInitialized = true;
}

Motor* Motor_Alloc(void) {
    Motor* newMotor = malloc(sizeof(Motor));

    if (newMotor == NULL) {
        puts("Error: can't allocate motor");
        return NULL;
    }

    return newMotor;
}

void Motor_Setup(Motor* motor) {
    //TODO: pinMode the enable pin
    printf("Setting up motor with input0: %d and input1: %d\n", motor->input0, motor->input1);
    pinMode(motor->input0, OUTPUT);
    pinMode(motor->input1, OUTPUT);
}

static void Motor_CheckPins(void) {
    if (!sPinsInitialized) {
        printf("ERROR: WiringPi not initialized aborting..");
        exit(EXIT_FAILURE);
    }
}

void Motor_Forward(Motor* motor) {
    Motor_CheckPins();

    if (motor == NULL) {
        puts("Motor not initialized refusing to move it forward!\n");
        return;
    }

    DEBUG_MSG("Moving motor in forward");
    digitalWrite(motor->input0, HIGH);
    digitalWrite(motor->input1, LOW);
}

void Motor_Reverse(Motor* motor) {
    Motor_CheckPins();

    if (motor == NULL) {
        puts("Motor not initialized refusing to move it in reverse!\n");
        return;
    }

    DEBUG_MSG("Moving motor in reverse");
    digitalWrite(motor->input0, LOW);
    digitalWrite(motor->input1, HIGH);
}

void Motor_Stop(Motor* motor) {
    Motor_CheckPins();

    if (motor == NULL) {
        puts("Motor not initialized refusing to stop it!\n");
        return;
    }

    digitalWrite(motor->input0, LOW);
    digitalWrite(motor->input1, LOW);
}
