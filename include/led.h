#ifndef LED_H
#define LED_H

typedef struct CarLed_s {
    CarPin pin;
} CarLed;

CarLed* Led_Setup(int bcm);
void Led_BrightOn(CarLed* led);
void Led_BrightOff(CarLed* led);
#endif /* LED_H */