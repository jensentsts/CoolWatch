#ifndef __pins_h
#define __pins_h

#pragma once

#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/adc.h>
#include <driver/usb_serial_jtag.h>

extern const int POWER_IO = 39;         // GPIO1
extern const int KEY_POWER = 38;        // GPIO2

extern const int ADC_BAT = 15;          // ADC2_CHANNEL_3;

extern const auto DRDY = GPIO_NUM_45;
extern const auto IIC_SCL = GPIO_NUM_47;
extern const auto IIC_SDA = GPIO_NUM_48;

extern const auto USB_DP = USB_DP_GPIO_NUM;
extern const auto USB_DM = USB_DM_GPIO_NUM;

extern const auto LCD_BLK = 35;
extern const auto LCD_BLK_PWM_CHANNEL = 0;
extern const auto LCD_SDA = 34;
extern const auto LCD_SCL = 33;
extern const auto LCD_CS = 32;
extern const auto LCD_DC = 31;
extern const auto LCD_RST = 30;

#endif // __pins_h
