
#include "AppBase.h"

#include "lvgl.h"
#include "AsResource.h"

AppBase::AppBase()
{
    this->_container = lv_obj_create(nullptr); // @todo
}

AppBase::~AppBase()
{

}

AppDataPackage::AppDataPackage(std::string app_name, Graph *icon)
{
    this->app_name = app_name;
    this->icon = icon;
}
