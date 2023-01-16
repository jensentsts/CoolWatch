#ifndef __pins_h
#define __pins_h

#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/adc.h>
#include <driver/usb_serial_jtag.h>

extern const auto POWER_IO = GPIO_NUM_1;
extern const auto KEY_POWER = GPIO_NUM_2;
extern const auto IIC_SCL = GPIO_NUM_47;
extern const auto IIC_SDA = GPIO_NUM_48;
extern const auto DRDY = GPIO_NUM_45;
extern const auto ADC_BAT = ADC2_CHANNEL_3;
extern const auto USB_DP = USB_DP_GPIO_NUM;
extern const auto USB_DM = USB_DM_GPIO_NUM;
extern const auto LCD_BLK = GPIO_NUM_42;
extern const auto LCD_SDA = CLK_OUT1;
extern const auto LCD_SCL = CLK_OUT2;
extern const auto LCD_CS = GPIO_NUM_39;
extern const auto LCD_DC = GPIO_NUM_38;
extern const auto LCD_RST = GPIO_NUM_37;

#endif // __pins_h
