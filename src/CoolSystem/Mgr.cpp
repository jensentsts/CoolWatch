
#include "Mgr.h"

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <arduino.h>
#include "lvgl.h"
#include "TFT_eSPI.h"
#include "FT6336U.h"
#include "json/json.h"

#include "Graph.h"
#include "SysConf.h"
#include "Hardware.h"
#include "CoolApp.h"
#include "Interface.h"
#include "AppBase.h"

TaskMgr task_mgr;
AppPackageMgr app_package_mgr;
HardwareIOMgr hardwareio_mgr;
InterfaceMgr interface_mgr;
ResourceMgr resource_mgr;

//////////////////////////////////////////////////////////////////////////////
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

    this->_compass_active = false;
    this->_has_booted = false;
}

void HardwareIOMgr::Load()
{
    if (this->_has_booted)
    {
        return;
    }
#if DEBUG == 1
    Serial.printf("Start to Boot. \r\n");
#endif
    resource_mgr.Load();
    interface_mgr.Load();
    app_package_mgr.Load();
    task_mgr.Load();
    interface_mgr.Transfer("StartAnimation");
    this->_has_booted = true;
}

void HardwareIOMgr::Close()
{
    interface_mgr.Close();
    resource_mgr.SaveAll();
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

inline void HardwareIOMgr::ScreenRotate(uint8_t r)
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

inline QMC5883L_DataPackage HardwareIOMgr::Compass_GetData()
{
    return QMC5883L_GetData();
}

inline uint16_t HardwareIOMgr::Compass_GetXData()
{
    return QMC5883L_GetXData();
}

inline uint16_t HardwareIOMgr::Compass_GetYData()
{
    return QMC5883L_GetYData();
}

inline uint16_t HardwareIOMgr::Compass_GetZData()
{
    return QMC5883L_GetZData();
}
//////////////////////////////////////////////////////////////////////////////
AppPackageMgr::AppPackageMgr()
{
}

void AppPackageMgr::Load()
{
    this->_app_vector.clear();
    this->_app_vector.push_back(Settings());
    this->_app_map.clear();
    for (size_t i = 0; i < this->_app_vector.size(); ++i)
    {
        this->_app_map[this->_app_vector[i].GetDataPackage()->package_name] = &this->_app_vector[i];
    }
}

void AppPackageMgr::Close()
{
}

inline AppBase *AppPackageMgr::operator[](std::string package_name)
{
    return this->_app_map[package_name];
}

AppBase *AppPackageMgr::operator[](size_t index)
{
    if (index >= this->_app_map.size())
    {
        return nullptr;
    }
    return &this->_app_vector[index];
}

inline size_t AppPackageMgr::size()
{
    return this->_app_vector.size();
}
//////////////////////////////////////////////////////////////////////////////

/**
 * @brief 在esp任务中运行App的函数
 *
 * @param arg 传入类型为AppBase*，指向某个App
 */
void TaskRunner(void *arg)
{
    AppBase *app = (AppBase *)arg;
    app->Start();
    do
    {
        app->Loop();
    } while (app->GetStatue() == RUNNING);
    app->Stop();
    task_mgr.TerminateApp(app->GetDataPackage()->package_name);
}

TaskMgr::TaskMgr()
{
}

void TaskMgr::Load()
{
}

void TaskMgr::Close()
{
}

/**
 * @brief 启动app
 * @param package_name app包名
 */
void TaskMgr::StartApp(std::string package_name)
{
    // 任务已创建则不重复创建
    if (this->_running_app.find(package_name) != this->_running_app.end())
    {
        return;
    }
    TaskHandle_t handle;
    AppBase *app = app_package_mgr[package_name];
    xTaskCreate(TaskRunner,
                package_name.c_str(),
                APP_STACK_SIZE,
                app,
                APP_SYS_PRIORITY,
                &handle);
    this->_running_app[package_name] = handle;
}

/**
 * @brief 结束app任务
 * @param package_name app包名
 */
void TaskMgr::TerminateApp(std::string package_name)
{
    // 任务未创建则退出
    if (this->_running_app.find(package_name) == this->_running_app.end())
    {
        return;
    }
    vTaskDelete(this->_running_app[package_name]);
}

void TaskMgr::ActivityMonitor()
{
    // @todo
    if (lv_disp_get_inactive_time(NULL) >= SYS_TICK_STOP_TIME)
    {
        TFTLCD_TickStop();
    }
}

//////////////////////////////////////////////////////////////////////////////
InterfaceMgr::InterfaceMgr()
{
    this->_app_root = nullptr;
}

void InterfaceMgr::_StartAnimationPlay()
{
    // 防止bug
    this->_desktop.Hide();
    this->_cards.Hide();
    this->_lock.Hide();
    this->_stop_animation.Hide();
    this->_currentDisplay.clear();
    this->_currentDisplay.push_back(&this->_start_animation);
    this->_start_animation.Show();
}

void InterfaceMgr::_StopAnimationPlay()
{
    // 防止bug
    this->_desktop.Hide();
    this->_cards.Hide();
    this->_lock.Hide();
    this->_start_animation.Hide();
    if (this->_app_root != nullptr)
    {
        lv_obj_del(this->_app_root);
    }
    this->_currentDisplay.clear();
    this->_currentDisplay.push_back(&this->_stop_animation);
    this->_stop_animation.Show();
}

void InterfaceMgr::Load()
{
    this->_start_animation.Show();
}

void InterfaceMgr::Close()
{
}

void InterfaceMgr::Transfer(lv_point_t point, lv_dir_t dir)
{
    // @todo
    TransferObj transfer_obj;
    if (point.y < GESTURE_MARGIN)
    {
        transfer_obj.area = LV_DIR_TOP;
    }
    else if (point.y > HEIGHT - GESTURE_MARGIN)
    {
        transfer_obj.area = LV_DIR_BOTTOM;
    }
    else if (point.x < GESTURE_MARGIN)
    {
        transfer_obj.area = LV_DIR_LEFT;
    }
    else if (point.x > WIDTH - GESTURE_MARGIN)
    {
        transfer_obj.area = LV_DIR_RIGHT;
    }
    else
    {
        transfer_obj.area = LV_DIR_ALL;
    }
    transfer_obj.dir = dir;
}

void InterfaceMgr::Transfer(std::string)
{
}

void InterfaceMgr::StopApp()
{
    if (this->_app_root == nullptr)
    {
        return;
    }
}
//////////////////////////////////////////////////////////////////////////////
ResourceMgr::ResourceMgr()
{
}

void ResourceMgr::Load()
{
    // @todo
    config["SysInfo"]["Name"] = "CoolWatch";
    config["SysInfo"]["Version"] = "0.0.1";
    config["SysInfo"]["BatteryStatue"] = 0;
}

void ResourceMgr::Close()
{
    this->SaveAll();
}

void ResourceMgr::SaveAll()
{
    // @todo
}
//////////////////////////////////////////////////////////////////////////////
