#ifndef __pins_h
#define __pins_h

#pragma once

#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/adc.h>
#include <driver/usb_serial_jtag.h>

#define  POWER_IO 39         // GPIO1
#define  KEY_POWER 38        // GPIO2
#define  ADC_BAT 15          // ADC2_CHANNEL_3

#define  DRDY GPIO_NUM_45
#define  IIC_SCL GPIO_NUM_47
#define  IIC_SDA GPIO_NUM_48

#define  USB_DP USB_DP_GPIO_NUM
#define  USB_DM USB_DM_GPIO_NUM

#define  LCD_BLK 35
#define  LCD_BLK_PWM_CHANNEL 0
#define  LCD_SDA 34
#define  LCD_SCL 33
#define  LCD_CS 32
#define  LCD_DC 31
#define  LCD_RST 30

#endif // __pins_h
