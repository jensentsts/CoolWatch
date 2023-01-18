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
    AppDataPackage();
    AppDataPackage(std::string app_name, Graph icon);
};

class AppBase : public Resource
{
protected:
    lv_obj_t *_root;
    lv_obj_t *_container;
    lv_obj_t *_title_container;
    lv_obj_t *_title_disp;
    AppDataPackage _app_data_package;

public:
    AppBase();
    AppBase(AppDataPackage *);
    ~AppBase();
    /**
     * @brief app启动
     * @note Start()只会在app启动时运行一次
     * 
     * @return lv_obj_t* 返回this->_root
     */
    lv_obj_t *Start();
    /**
     * @brief 循环
     * @note while (appNotExit()) { Loop(); }
     */
    void Loop();
    /**
     * @brief app退出
     * @note Stop()只会在结束时运行一次
     */
    void Stop();
    // @todo
    // void BackstageUpdate();
};

#endif // __AppBase_h
