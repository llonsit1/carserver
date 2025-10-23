#include "pin.h"
#include "global.h"

bool gPinsInitialized = false;

#define DEBUG_MSG(x) if (sPinsDebug) puts(x)

static int sGetHighLowFromPinValues[sizeof(PIN_VALUES)] = {HIGH, LOW};


static inline void Pin_InitialCheck(void) {
    if (!gPinsInitialized) {
        printf("ERROR: WiringPi not initialized aborting..");
        exit(EXIT_FAILURE);
    } 
}

static inline bool Pin_Nil(CarPin* pin) {
    if (pin == NULL) {
        printf("car_pin.c: ERROR Pin not initialized refusing to do something with it!\n");
        return true;
    } 
    return false;
}

void Pin_Init() {
    wiringPiSetupGpio();
    gPinsInitialized = true;
}

#define VALIDATE_PIN(pin) if (Pin_Nil(pin)) return;

CarPin* Pin_Enable(int bcm, PIN_MODES mode) {
    Pin_InitialCheck();
    CarPin* pin = malloc(sizeof(CarPin));

    if (pin == NULL) {
        printf("car_pin.c: Can't allocate memory for pins aborting..\n");
        abort();
    }

    pin->bcm = bcm;

    switch (mode) {
        case MODE_READ:
            pin->mode = MODE_READ;
            printf("car_pin.c: Read mode not implemented yet...\n");
            break;
        case MODE_WRITE:
            pin->mode = MODE_WRITE;
            pinMode(pin->bcm, OUTPUT);
            break;
        case MODE_ANALOG_WRITE:
            pin->mode = MODE_ANALOG_WRITE;
            pinMode(pin->bcm, PWM_OUTPUT);
            break;
        default:
            printf("car_pin.c: Unknown pin mode!...\n");
            break;
    }
    return pin;
}

void Pin_SetRange(CarPin* pin, int range) {
    Pin_InitialCheck();

    VALIDATE_PIN(pin)

    if (pin->mode != MODE_ANALOG_WRITE) {
        printf("car_pin.c: ERROR: Invalid mode for this pin!\n");
        return;
    }

    pin->range = range;
}

void Pin_Write(CarPin* pin, PIN_VALUES val) {
    Pin_InitialCheck();

    VALIDATE_PIN(pin)


    if (pin->mode != MODE_WRITE) {
        printf("This pin not in write mode aborting..\n");
        return;
    }

    digitalWrite(pin->bcm, sGetHighLowFromPinValues[val]);
}

void Pin_AnalogWrite(CarPin* pin, int value) {
    Pin_InitialCheck();

    VALIDATE_PIN(pin)

    pwmWrite(pin->bcm, value);
}

void Pin_Free(CarPin* pin) {
    free(pin);
}
