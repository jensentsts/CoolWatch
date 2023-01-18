
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
    TFTLCD_Init();

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
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = TFTLCD_TouchRead;
    lv_indev_drv_register(&indev_drv);

    TFTLCD_TickStart();

    _compass_active = false;
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
    this->_compass_active = cmd;
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

void HardwareIOMgr::ScreenTouchRead(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    this->_screen_touch_point = this->_screen_touch.scan();
    static int16_t last_x = 0;
    static int16_t last_y = 0;
    /* 判断屏幕是否被按下 */
    bool touched = this->_screen_touch_point.touch_count;
    if (touched)
    {
        last_x = this->_screen_touch_point.tp[0].x;
        last_y = this->_screen_touch_point.tp[0].y;
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    /* 将获取的坐标传入 LVGL */
    data->point.x = last_x;
    data->point.y = last_y;
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
    file_mgr.SaveAll();
    interface_mgr.StopAnimationPlay();
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

void InterfaceMgr::StartApp(int x, int y, lv_obj_t *app_root)
{

}


void InterfaceMgr::StartAnimationPlay()
{
    // 防止bug
    this->_desktop.Hide();
    this->_cards.Hide();
    this->_lock.Hide();
    this->_stop_animation.Hide();
    this->_start_animation.Start();
}

void InterfaceMgr::StopAnimationPlay()
{
    // 防止bug
    this->_desktop.Hide();
    this->_cards.Hide();
    this->_lock.Hide();
    this->_start_animation.Hide();
    this->_stop_animation.Start();
}

ConfigMgr::ConfigMgr()
{
    /* @todo */
    this->_desktop_bgimg.width = 0;
    this->_desktop_bgimg.height = 0;
    this->_desktop_bgimg.graph = nullptr;

    this->_lock_bgimg.width = 0;
    this->_lock_bgimg.height = 0;
    this->_lock_bgimg.graph = nullptr;
}

Graph ConfigMgr::DesktopBgImg()
{
    return this->_desktop_bgimg;
}

Graph ConfigMgr::LockBgImg()
{
    return this->_lock_bgimg;
}

FileMgr::FileMgr()
{
}

FileMgr::~FileMgr()
{
}

void FileMgr::SaveAll()
{
}
