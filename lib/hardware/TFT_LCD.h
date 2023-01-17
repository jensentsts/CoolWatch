/**
 * @file TFT_LCD.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 
 * @version 1.0.0
 * @date 2023-01-17
 * 
 * @copyright CC4.0 BY-NC-SA
 * 
 */

#ifndef __TFT_LCD_h
#define __TFT_LCD_h

#include "lvgl.h"

void TFTLCD_Init();
void TFTLCD_DispFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void TFTLCD_TouchRead(lv_indev_drv_t * indev_driver, lv_indev_data_t * data);
void TFTLCD_TickStart();
void TFTLCD_TickStop();

#endif // __TFT_LCD_h
