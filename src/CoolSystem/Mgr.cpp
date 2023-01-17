
#include "Mgr.h"

#include <vector>
#include <string>
#include <arduino.h>

#include "Hardware.h"
#include "CoolApp.h"
#include "hardware.h"

HardwareIOMgr::HardwareIOMgr()
{
    Power_Init();
    Power_On();
    QMC5883L_Init();
    this->_screen.init();
    this->_screen_touch.begin();
    ledcSetup(LCD_BLK_PWM_CHANNEL, 2000, TFT_BL);
    ledcAttachPin(LCD_BLK, LCD_BLK_PWM_CHANNEL);
    ledcWrite(LCD_BLK_PWM_CHANNEL, (int)(1 * 255));
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf_1, NULL, DISP_BUF_SIZE);
    /* 显示设备注册 */
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = WIDTH;
    disp_drv.ver_res = HEIGHT;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = TFTLCD_DispFlush;
    lv_disp_drv_register(&disp_drv);
    /* 输入设备注册 */
    
}

HardwareIOMgr::~HardwareIOMgr()
{
}

void HardwareIOMgr::Compass_Cmd(bool cmd)
{
    if (cmd)
    {
        QMC5883L_Start();
    }
    else
    {
        QMC5883L_Stop();
    }
}

void HardwareIOMgr::ScreenRotate(uint8_t r)
{
    this->_screen.setRotation(r);
}

void HardwareIOMgr::ScreenFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    this->_screen.startWrite();
    this->_screen.setAddrWindow(area->x1, area->y1, w, h);
    this->_screen.pushColors(&color_p->full, w * h, true);
    this->_screen.endWrite();
    /* 反馈显示结果*/
    lv_disp_flush_ready(disp);
}

QMC5883L_DataPackage HardwareIOMgr::Compass_GetData()
{
    return QMC5883L_GetData();
}

uint16_t Compass_GetXData()
{
    return QMC5883L_GetXData();
}

uint16_t Compass_GetYData()
{
    return QMC5883L_GetYData();
}

uint16_t Compass_GetZData()
{
    return QMC5883L_GetZData();
}

void HardwareIOMgr::Shutdown()
{
    interface_mgr.StopAnimationPlay();
    Power_Off();
}

AppDataPackage::AppDataPackage(std::string app_name, Graph *icon)
{
    this->app_name = app_name;
    this->icon = icon;
}

AppMgr::AppMgr()
{
    _app_list.push_back(AppDataPackage("Settings", nullptr));
}

AppMgr::~AppMgr()
{
}

InterfaceMgr::InterfaceMgr()
{
}

InterfaceMgr::~InterfaceMgr()
{
}

void InterfaceMgr::StartAnimationPlay()
{
}

void InterfaceMgr::StopAnimationPlay()
{
}

FileMgr::FileMgr()
{
}

FileMgr::~FileMgr()
{
}
