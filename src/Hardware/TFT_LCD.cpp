#include "TFT_LCD.h"
#include "Mgr.h"

// 暂无实权
void TFTLCD_DispFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    hardwareio_mgr.ScreenFlush(disp, area, color_p);
}