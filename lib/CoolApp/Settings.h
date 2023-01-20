/**
 * @file Settings.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief “设置”App
 * @version 1.0.0
 * @date 2023-01-16
 * 
 * @copyright CC4.0 BY-NC-SA
 * 
 */

#ifndef __Settings_h
#define __Settings_h

#include "AppBase.h"

class Settings : public AppBase
{
private:
    lv_obj_t *_menu;

public:
    Settings();
    ~Settings();
    lv_obj_t* Start();
};

#endif // __Settings_h
