#include "TFT_LCD.h"
#include "Mgr.h"

// 暂无实权
void TFTLCD_DispFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    hardwareio_mgr.ScreenFlush(disp, area, color_p);
}

void TFTLCD_TouchRead(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    hardwareio_mgr.ScreenTouchRead(indev_driver, data);
}