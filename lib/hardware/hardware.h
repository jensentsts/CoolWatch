#ifndef __hardware_h
#define __hardware_h

#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/adc.h>
#include <driver/usb_serial_jtag.h>

#include "pins.h"

typedef enum
{
    BATTERY,
    BATTERY_LOW_POWER,
    USB_CONNECTED
}PowerStatue;

void Power_On();
void Power_Off();
double Power_Quantity();
PowerStatue Power_GetStatue();

#endif // __hardware_h
