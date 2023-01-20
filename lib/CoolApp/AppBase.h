/**
 * @file AppBase.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 这里的APP既承担了类似于.apk文件的功能，又承担了安装后可以直接运行的app的功能。即：直接运行.apk而不加以安装和卸载。
 * @version 1.0.0
 * @date 2023-01-15
 *
 * @copyright CC4.0 BY-NC-SA
 *
 */

#ifndef __AppBase_h
#define __AppBase_h

#include "lvgl.h"

#include "Graph.h"
#include "Resource.h"
#include "SysConf.h"
#include "hardware.h"

struct Graph_t;

/**
 * @brief Create a App Package Data object
 *
 * @param package_name 包名
 * @param app_title app标题名
 * @param icon 图标
 * @return Resource 返回格式：{ "package_name": [String]package_name, "app_title": [String]app_title, "icon": [graph object], "app_pointer": [Pointer]nullptr }
 */
Resource CreateAppPackageData(std::string package_name = "Unknown", std::string app_title = "Untitled", Resource icon = CreateGraph(), void* app_pointer = nullptr);

// app运行状态
enum AppRuntimeStatue
{
    READY,  // 已就绪，（程序加载完毕后、程序已退出）
    RUNNING // 运行时（Loop()）
};

class AppBase
{
protected:
    lv_obj_t *_root;
    lv_obj_t *_container;
    lv_obj_t *_title_container;
    lv_obj_t *_title_disp;
    Resource _app_data_package;
    AppRuntimeStatue _statue;

public:
    AppBase();
    AppBase(Resource);
    ~AppBase();
    Resource GetDataPackage() const;
    AppRuntimeStatue GetStatue();
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
