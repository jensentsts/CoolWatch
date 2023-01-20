
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
#include "img.h"
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
    this->_app_arr.push_back(Settings());
    decltype(this->_app_arr)::iterator iter = this->_app_arr.begin();
    while (iter != this->_app_arr.end())
    {
        this->_apps[iter->GetDataPackage()["package_name"].asString()] = (AppBase *)&(*iter);
        iter++;
    }
}

void AppPackageMgr::Close()
{
}

Resource AppPackageMgr::GetAppPackageArray() const
{
    return this->_apps;
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
    task_mgr.TerminateApp(app->GetDataPackage()["package_name"].asString());
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
void TaskMgr::StartApp(AppBase *app_pointer)
{
    const std::string &package_name = app_pointer->GetDataPackage()["package_name"].asString();
    // 任务已创建则不重复创建
    if (this->_running_app.find(package_name) != this->_running_app.end())
    {
        return;
    }
    TaskHandle_t handle;
    AppBase *app = (AppBase *)app_package_mgr.GetAppPackageArray()[package_name].asPointer();
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
}

void InterfaceMgr::_StartAnimationPlay()
{
}

void InterfaceMgr::_StopAnimationPlay()
{
}

void InterfaceMgr::Load()
{
    this->_interface_arr.push_back(Desktop());
    this->_interface_arr.push_back(TopBar());
    this->_interface_arr.push_back(Cards());
    this->_interface_arr.push_back(MainInterface());
    this->_interface_arr.push_back(Lock());
    decltype(this->_interface_arr)::iterator iter = this->_interface_arr.begin();
    while (iter != this->_interface_arr.end())
    {
        this->_interfaces[iter->resource["package_name"].asString()] = (InterfaceBase *)&(*iter);
    }
}

void InterfaceMgr::Close()
{
}

void InterfaceMgr::Transfer(std::string interface_package_name)
{
}
//////////////////////////////////////////////////////////////////////////////
ResourceMgr::ResourceMgr()
{
}

void ResourceMgr::Load()
{
    // @todo
    resource["SysInfo"]["Name"] = "CoolWatch";
    resource["SysInfo"]["Version"] = "0.0.1";
    resource["App"]["Settings"]["icon"] = gImage_Settings;
    resource["Interface"]["Desktop"]["background_img"] = gImage_desktopImg;
}

void ResourceMgr::SaveAll()
{
    // @todo
}

void ResourceMgr::Close()
{
    this->SaveAll();
}

template <typename IndexType>
Resource ResourceMgr::operator[](IndexType index)
{
    return this->resource[index];
}
//////////////////////////////////////////////////////////////////////////////
