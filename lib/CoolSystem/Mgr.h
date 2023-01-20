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

#include "Graph.h"
#include "SysConf.h"
#include "CoolApp.h"
#include "Interface.h"
#include "hardware.h"

#define DISP_BUF_SIZE ((240 * 320) / 10)
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf_1[DISP_BUF_SIZE];

/**
 * @brief 用于 Resource 的派生类赋予 MgrBase 派生类权限
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
    std::map<std::string, AppBase*> _app_map;
    std::vector<AppBase> _app_vector;

public:
    AppPackageMgr(/* args */);
    void Load();
    void Close();

    AppBase *operator[](std::string package_name);
    AppBase *operator[](size_t index);
    size_t size();
};

/**
 * @brief 任务管理器
 * @note 原则上讲权限最高
 */
class TaskMgr : public MgrBase
{
private:
    //std::vector<std::pair<AppBase*, TaskHandle_t> > _running_app; // 正在运行中的app
    std::map<std::string, TaskHandle_t> _running_app;

public:
    TaskMgr();
    void Load();
    void Close();

    void StartApp(std::string package_name);
    void TerminateApp(std::string package_name);
    void ActivityMonitor(); // 系统活跃性检测（例如ESP睡眠、息屏等）
};

/**
 * @brief 界面管理，统率锁屏、桌面、卡片页、APP界面的切入切出、信息传递等
 */
class InterfaceMgr : public MgrBase
{
private:
    StartAnimation _start_animation;
    StopAnimation _stop_animation;
    Lock _lock;
    Desktop _desktop;
    Cards _cards;
    TopBar _topbar;

    std::vector<InterfaceBase *> _currentDisplay;
    lv_obj_t *_app_root;
    size_t _app_index;
    void _StartAnimationPlay();
    void _StopAnimationPlay();

public:
    InterfaceMgr(/* args */);
    void Load();
    void Close();
    void AppStart(std::string package_name);
    void StopApp();
    void Transfer(lv_point_t point, lv_dir_t dir);
    void Transfer(std::string); // 强制切换
};

class ConfigMgr : public MgrBase
{
private:
    std::string _json;

public:
    ConfigMgr();
    void Load();
    void Close();
    /* @todo jsoncpp */
};

/**
 * @brief 负责USB、“文件”保存
 */
class FileMgr : public MgrBase
{
private:
    /* data */
public:
    FileMgr(/* args */);
    void SaveAll();
    void Load();
    void Close();
};

extern TaskMgr task_mgr;
extern AppPackageMgr app_package_mgr;
extern HardwareIOMgr hardwareio_mgr;
extern InterfaceMgr interface_mgr;
extern ConfigMgr config_mgr;
extern FileMgr file_mgr;

#endif // __Mgr_h
