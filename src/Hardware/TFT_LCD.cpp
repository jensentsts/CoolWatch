#include "TFT_LCD.h"
#include "Mgr.h"
#include "TimerConf.h"

hw_timer_t *tft_timer = nullptr;

void TFTLCD_Tick()
{
    lv_tick_inc(1);
}

void TFTLCD_Init()
{
    tft_timer = timerBegin(TFTLCD_TIMER, TFTLCD_TIMER_DIV, true);
    timerAttachInterrupt(tft_timer, TFTLCD_Tick, true);
    timerAlarmWrite(tft_timer, TFTLCD_TIMEOUT * 1000, false);
    timerAlarmEnable(tft_timer);
    timerSetAutoReload(tft_timer, true);
    timerStop(tft_timer);
}

// 暂无实权
void TFTLCD_DispFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    hardwareio_mgr.ScreenFlush(disp, area, color_p);
}

// 暂无实权
void TFTLCD_TouchRead(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    hardwareio_mgr.ScreenTouchRead(indev_driver, data);
}

void TFTLCD_TickStart()
{
    lv_tick_inc(0); /* @todo */
    lv_task_handler();
    timerWrite(tft_timer, 0);
    timerStart(tft_timer);
}

void TFTLCD_TickStop()
{
    timerStop(tft_timer);
}
