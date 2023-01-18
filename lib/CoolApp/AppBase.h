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
#include "hardware.h"
#include "Graph.h"

struct Graph;

struct AppDataPackage
{
    std::string app_name = "Untitled";
    Graph icon;
    AppDataPackage(std::string app_name, Graph icon);
};

class AppBase : public Resource
{
private:
    lv_obj_t *_container;
    AppDataPackage _app_data_package = AppDataPackage("Untitled", Graph());

public:
    AppBase();
    ~AppBase();
    void Start();
    void Loop();
    void Stop();
};

#endif // __AppBase_h

