#ifndef __Power_h
#define __Power_h

#include "pins.h"
#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/adc.h>

#define POWER_LOW_VOLTAGE_LEVEL 3.0
#define POWER_USB_CONNECTED_VOLTAGE_LEVEL 4.8

typedef enum
{
    BATTERY,
    BATTERY_LOW_POWER,
    USB_CONNECTED
}PowerStatue;

void Power_Init(void);
void Power_On(void);
void Power_Off(void);
double Power_Quantity(void);
PowerStatue Power_GetStatue(void);

#endif // __Power_h
