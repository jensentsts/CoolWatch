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

#include "AppBase.h"
#include "hardware.h"

/**
 * @brief 用于 Resource 的派生类赋予 MgrBase 派生类权限
 */
class MgrBase
{
    // Nothing here, for rights in Resource.
};

/**
 * @brief 硬件输入输出管理器
 */
class HardwareIOMgr : public MgrBase
{
private:

public:
    HardwareIOMgr(/* args */);
    ~HardwareIOMgr();

    void Compass_Cmd(bool cmd);
    QMC5883L_DataPackage Compass_GetData();
    uint16_t Compass_GetXData();
    uint16_t Compass_GetYData();
    uint16_t Compass_GetZData();

    void Screen_Touch(short x, short y);
    
    void Shutdown();
};

/**
 * @brief App管理器
 */
class AppMgr : public MgrBase
{
private:
    std::vector<AppDataPackage> _app_list;

public:
    AppMgr(/* args */);
    ~AppMgr();
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

public:
    InterfaceMgr(/* args */);
    ~InterfaceMgr();
    void StartAnimationPlay();
    void StopAnimationPlay();
};


/**
 * @brief 负责USB、“文件”保存
 */
class FileMgr
{
private:
    /* data */
public:
    FileMgr(/* args */);
    ~FileMgr();
};

extern AppMgr app_mgr;
extern HardwareIOMgr hardwareio_mgr;
extern InterfaceMgr interface_mgr;
extern FileMgr file_mgr;

#endif // __Mgr_h
