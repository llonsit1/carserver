#ifndef PIN_H
#define PIN_H

typedef int Pin_t;

typedef enum {
    MODE_READ, /* Input mode */
    MODE_WRITE, /* Output mode */
    MODE_ANALOG_WRITE /* PWM rate mode */
} PIN_MODES;

typedef enum {
    VALUE_HIGH,
    VALUE_LOW
} PIN_VALUES;

typedef struct CarPin_s {
    PIN_MODES mode;
    Pin_t bcm;
    int range;
} CarPin;

void Pin_Init();
CarPin* Pin_Enable(int pin, PIN_MODES mode);
void Pin_Write(CarPin* pin, PIN_VALUES val);
void Pin_Free(CarPin* pin);
void Pin_SetRange(CarPin* pin, int range);
void Pin_AnalogWrite(CarPin* pin, int value);
#endif /* PIN_H */
