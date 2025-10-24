#include "pin.h"
#include "led.h"
#include "global.h"

#define LED_PIN_1 7 // (CE0)
#define LED_PIN_2 8 // (CE1)

#define LIGHTS_MAX 4

typedef enum {
    LIGHT_1,
    LIGHT_2,
    LIGHT_3,
    LIGHT_4
} CAR_LIGHTS;

//#define LL2 2
//#define LR2 3

static CarLed* sCarLedLights[LIGHTS_MAX] = {NULL};

void Lights_Init(void) {
    sCarLedLights[LIGHT_1] = Led_Setup(LED_PIN_1);
    sCarLedLights[LIGHT_2] = Led_Setup(LED_PIN_2);
}

void Light_On(CAR_LIGHTS light) {
    switch (light) {
        case LIGHT_1:
            Led_BrightOn(sCarLedLights[LIGHT_1]);
            break;
        case LIGHT_2:
            Led_BrightOn(sCarLedLights[LIGHT_2]);
            break;
        case LIGHT_3:
            Led_BrightOn(sCarLedLights[LIGHT_3]);
            break;
        case LIGHT_4:
            Led_BrightOn(sCarLedLights[LIGHT_4]);
            break;
    }
}

void Lights_On(void) {
    Led_BrightOn(sCarLedLights[LIGHT_1]);
    Led_BrightOn(sCarLedLights[LIGHT_2]);
}