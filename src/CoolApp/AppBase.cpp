
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
