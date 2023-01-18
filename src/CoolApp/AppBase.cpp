#include "AppBase.h"
#include "lvgl.h"

AppDataPackage::AppDataPackage(std::string app_name, Graph *icon)
{
    this->app_name = app_name;
    this->icon = icon;
}

AppBase::AppBase()
{
}

AppBase::~AppBase()
{
}

void AppBase::Start()
{
    this->_container = lv_obj_create(nullptr);
}

void AppBase::Loop()
{
}

void AppBase::Stop()
{
}
