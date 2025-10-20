#include "global.h"
#include "motor.h"
#include "wheel.h"


#define MOTOR_A1_ENABLE -1
#define MOTOR_B1_ENABLE -1
#define MOTOR_A2_ENABLE -1
#define MOTOR_B2_ENABLE -1

// Motor - L1
#define MOTOR_A1_IN1 17
#define MOTOR_A1_IN2 27

// Motor - R1
#define MOTOR_B1_IN1 5
#define MOTOR_B1_IN2 6

// Motor - L2
#define MOTOR_A2_IN1 23
#define MOTOR_A2_IN2 24

// Motor - R2
#define MOTOR_B2_IN1 16
#define MOTOR_B2_IN2 26

#define WHEEL_MAX 4

Wheel sWheels[WHEEL_MAX];

/*
 * Initialize the four wheels of the car
 */
void Wheel_Init(void) {
  for (int i = 0; i < WHEEL_MAX; i++) {
    sWheels[i].motor = Motor_Alloc();

    if (sWheels[i].motor == NULL) {
      puts("Couldn't allocate memory for the core motors aborting...");
      abort();
    }
  }

  // Maybe?: Temporal
  sWheels[WHEEL_R1].motor->enable = MOTOR_A1_ENABLE;
  sWheels[WHEEL_R1].motor->input0 = MOTOR_A1_IN1;
  sWheels[WHEEL_R1].motor->input1 = MOTOR_A1_IN2;

  sWheels[WHEEL_R2].motor->enable = MOTOR_A2_ENABLE;
  sWheels[WHEEL_R2].motor->input0 = MOTOR_A2_IN1;
  sWheels[WHEEL_R2].motor->input1 = MOTOR_A2_IN2;

  sWheels[WHEEL_L1].motor->enable = MOTOR_B1_ENABLE;
  sWheels[WHEEL_L1].motor->input0 = MOTOR_B1_IN1;
  sWheels[WHEEL_L1].motor->input1 = MOTOR_B1_IN2;

  sWheels[WHEEL_L2].motor->enable = MOTOR_B2_ENABLE;
  sWheels[WHEEL_L2].motor->input0 = MOTOR_B2_IN1;
  sWheels[WHEEL_L2].motor->input1 = MOTOR_B2_IN2;

  // Now that we initialized the Pin inputs now we can use pinMode with them
  for (int i = 0; i < WHEEL_MAX; i++) {
    Motor_Setup(sWheels[i].motor);
  }
}

// Test movements
void Wheel_MoveForward(WHEEL wheel) {
  switch (wheel) {
    case WHEEL_L1:
      puts("MOVING WHEEL_L1");
      Motor_Forward(sWheels[WHEEL_L1].motor);
      break;
    case WHEEL_R1:
      puts("MOVING WHEEL_R1");
      Motor_Forward(sWheels[WHEEL_R1].motor);
      break;
    case WHEEL_L2:
      puts("MOVING WHEEL_L2");
      Motor_Forward(sWheels[WHEEL_L2].motor);
      break;
    case WHEEL_R2:
      puts("MOVING WHEEL_R2");
      Motor_Forward(sWheels[WHEEL_R2].motor);
      break;
    default:
        assert(wheel);
        break;
  }
}

void Wheel_Reverse(WHEEL wheel) {
  switch (wheel) {
    case WHEEL_L1:
      Motor_Reverse(sWheels[WHEEL_L1].motor);
      break;
    case WHEEL_R1:
      Motor_Reverse(sWheels[WHEEL_R1].motor);
      break;
    case WHEEL_L2:
      Motor_Reverse(sWheels[WHEEL_L2].motor);
      break;
    case WHEEL_R2:
      Motor_Reverse(sWheels[WHEEL_R2].motor);
      break;
    default:
      assert(wheel);
      break;
  }
}

void Wheel_Stop(WHEEL wheel) {
  switch (wheel) {
    case WHEEL_L1:
      Motor_Stop(sWheels[WHEEL_L1].motor);
      break;
    case WHEEL_R1:
      Motor_Stop(sWheels[WHEEL_R1].motor);
      break;
    case WHEEL_L2:
      Motor_Stop(sWheels[WHEEL_L2].motor);
      break;
    case WHEEL_R2:
      Motor_Stop(sWheels[WHEEL_R2].motor);
      break;
    default:
      assert(wheel);
      break;
  }
}

#if false
void Motor_Test() {
//  printf("Writing to PIN: %d", LED_PIN);
  Motor_Setup();

//   pwmSetRange(200);
//   pwmWrite(MOTOR_A1_EN, 50);

  char buf[200];

  while (true) {
     scanf("%s", buf);
     if (strncmp(buf, "MOVE_R1", 6) == 0) {
        puts("Received MOVE_R1 command!");
        moveR1();
     } else if (strncmp(buf, "MOVE_L1", 6) == 0) {
        puts("Received MOVE_L1 command!");
        moveL1();
      } else if (strncmp(buf, "STOP_R1", 6) == 0) {
        puts("Received STOP_R1 command!");
        stopR1();
    } else if (strncmp(buf, "STOP_L1", 6) == 0) {
        puts("Received STOP_L1 command!");
        stopL1();
    }
   }
}
#endif
