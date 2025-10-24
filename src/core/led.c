#include "pin.h"
#include "led.h"
#include "global.h"

CarLed* Led_Setup(int bcm) {
    CarLed* led = malloc(sizeof(CarLed));

    if (led == NULL) {
        printf("car_led.c: ERROR can't allocate memory for led with bcm %d\n", bcm);
        abort();
    }

    led->pin.bcm = bcm;
    led->pin.mode = MODE_WRITE;
}

void Led_BrightOn(CarLed* led) {
    if (led == NULL) {
        printf("car_led.c (%d): ERROR led pin not initialized!\n", 25);
        abort();
    }

    Pin_Write(&led->pin, VALUE_HIGH);
}

void Led_BrightOff(CarLed* led) {
    if (led == NULL) {
        printf("car_led.c (%d): ERROR led pin not initialized!\n", 34);
        abort();
    }

    Pin_Write(&led->pin, VALUE_LOW);
}

