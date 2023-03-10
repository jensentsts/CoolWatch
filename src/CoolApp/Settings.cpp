
#include "AppBase.h"
#include "Graph.h"
#include "SysConf.h"
#include "Settings.h"
#include "Settings/SettingsImg.h"

Settings::Settings() : AppBase()
{
    this->_app_data_package["app_title"] = "Settings";
    this->_app_data_package["package_name"] = "Settings";
    this->_app_data_package["icon"] = CreateGraph(APP_ICON_WIDTH, APP_ICON_HEIGHT, (uint16_t*)gImage_Settings);
}

Settings::~Settings()
{
}

void Settings::Show()
{
    AppBase::Show();
}

void Settings::Start()
{
    AppBase::Start();
}

void Settings::Loop()
{

}

void Settings::Stop()
{

}
