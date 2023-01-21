/**
 * @file Mgr.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief Manager是软件层与驱动层的中间层、调度层，承上而启下。软件层不直接访问硬件层，硬件层的信息反馈给Mgr。
 * @version 1.0.0
 * @date 2023-01-15
 *
 * @copyright CC4.0 BY-NC-SA
 *
 */

#ifndef __Mgr_h
#define __Mgr_h

#include <vector>
#include <string>
#include <arduino.h>
#include <map>
#include <utility>
#include "lvgl.h"
#include "TFT_eSPI.h"
#include "FT6336U.h"
#include "json/json.h"

#include "Graph.h"
#include "SysConf.h"

#include "CoolApp.h"
#include "Interface.h"
#include "hardware.h"

#define DISP_BUF_SIZE ((240 * 320) / 10)
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf_1[DISP_BUF_SIZE];

/**
 * @brief Mgr基础类，定义Mgr的基本行为
 */
class MgrBase
{
public:
    virtual void Load() = 0;
    virtual void Close() = 0;
};

/**
 * @brief 硬件输入输出管理器
 */
class HardwareIOMgr : public MgrBase
{
private:
    TFT_eSPI _screen;
    FT6336U _screen_touch = FT6336U(LCD_SDA, LCD_SCL, LCD_RST, GPIO_NUM_NC);
    FT6336U_TouchPointType _screen_touch_point;

    bool _compass_active;

    bool _has_booted;

public:
    HardwareIOMgr();

    void Load();
    void Close();

    void ScreenFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
    void ScreenTouchRead(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
    void ScreenRotate(uint8_t r);

    void Compass_Cmd(bool cmd);
    QMC5883L_DataPackage Compass_GetData();
    uint16_t Compass_GetXData();
    uint16_t Compass_GetYData();
    uint16_t Compass_GetZData();
};

/**
 * @brief App包管理器（CoolWatch上运行的应用相当于直接运行的安装包）
 */
class AppPackageMgr : public MgrBase
{
private:
    std::vector<AppBase> _app_arr;
    Resource _apps;

public:
    AppPackageMgr(/* args */);
    void Load();
    void Close();

    Resource GetAppPackageArray() const;
};

/**
 * @brief 任务管理器
 * @note 原则上讲权限最高
 */
class TaskMgr : public MgrBase
{
private:
    std::map<std::string, TaskHandle_t> _running_app; // 此处不用 Resource

public:
    TaskMgr();
    void Load();
    void Close();

    void StartApp(AppBase *app_pointer);
    void TerminateApp(std::string package_name);
    void ActivityMonitor(); // 系统活跃性检测（例如ESP睡眠、息屏等）
};

/**
 * @brief 界面管理，统率锁屏、桌面、卡片页、APP界面的切入切出、信息传递等
 */
class InterfaceMgr : public MgrBase
{
private:
    // 手势判断
    lv_obj_t *_left_side_bar;
    lv_obj_t *_right_side_bar;
    lv_obj_t *_top_side_bar;
    lv_obj_t *_bottom_side_bar;

    std::vector<InterfaceBase> _interface_arr;
    Resource _interfaces;
    std::string _on_show;

    void _StartAnimationPlay();
    void _StopAnimationPlay();

public:
    InterfaceMgr();
    void Load();
    void Close();
    void Transfer(std::string package_name);
    static void SideBarGesture(lv_event_t *event);
};

extern TaskMgr task_mgr;
extern AppPackageMgr app_package_mgr;
extern HardwareIOMgr hardwareio_mgr;
extern InterfaceMgr interface_mgr;
extern Resource resource_root;

#endif // __Mgr_h
