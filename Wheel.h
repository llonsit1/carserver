#ifndef WHEEL_H
#define WHEEL_H
typedef enum {
    WHEEL_L1,
    WHEEL_R1,
    WHEEL_L2,
    WHEEL_R2
} WHEEL;

typedef struct Wheel_s {
    Motor* motor;
} Wheel;

void Wheel_Init(void);
void Wheel_MoveForward(WHEEL wheel);
void Wheel_Reverse(WHEEL wheel);
void Wheel_Stop(WHEEL wheel);
void Move_Reverse(void);
#endif /* WHEEL_H */
