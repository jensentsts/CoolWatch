#include "hardware.h"
#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/adc.h>
#include <driver/usb_serial_jtag.h>

void Power_On()
{
    gpio_init();
}

void Power_Off()
{

}

double Power_Quantity()
{

}

PowerStatue Power_GetStatue()
{

}
