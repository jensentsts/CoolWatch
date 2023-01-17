
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

void HardwareIOMgr::Screen_Touch(short x, short y)
{
    
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
