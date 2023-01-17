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

#include <Arduino.h>
#include "hardware.h"
#include "lvgl.h"
#include "Mgr.h"

void TFTLCD_DispFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

#endif // __TFT_LCD_h
