
#include "Mgr.h"

#include <vector>
#include <string>
#include <arduino.h>

#include "Hardware.h"
#include "CoolApp.h"

AppDataPackage::AppDataPackage(std::string app_name, Graph* icon)
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

HardwareMgr::HardwareMgr()
{

}

HardwareMgr::~HardwareMgr()
{

}

FileMgr::FileMgr()
{

}

FileMgr::~FileMgr()
{
    
}
