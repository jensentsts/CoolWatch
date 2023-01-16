/**
 * @file AppBase.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 
 * @version 1.0.0
 * @date 2023-01-15
 * 
 * @copyright CC4.0 BY-NC-SA
 * 
 */

#ifndef __AppBase_h
#define __AppBase_h

#include "AsResource.h"
#include "lvgl.h"
#include "Mgr.h"

class AppBase : public Resource
{
private:
    lv_obj_t *_container;
    AppDataPackage _app_data_package;

public:
    AppBase(/* args */);
    ~AppBase();
};

#endif // __AppBase_h

