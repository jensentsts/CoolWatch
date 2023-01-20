#include "AppBase.h"

#include "Graph.h"
#include "SysConf.h"
#include "lvgl.h"
#include "Resource.h"

Resource CreateAppPackageData(std::string package_name/* = "Unknown"*/, std::string app_title/* = "Untitled"*/, Resource icon/* = CreateGraph()*/, void *app_pointer)
{
    Resource res;
    res["package_name"] = package_name;
    res["app_pointer"] = app_pointer;
    res["app_title"] = app_title;
    res["icon"] = icon;
    return res;
}

AppBase::AppBase()
{
    this->_root = nullptr;
    this->_statue = READY;
    this->_app_data_package = CreateAppPackageData();
    this->_app_data_package["app_title"] = this;
}

AppBase::AppBase(Resource pkg)
{
    this->_root = nullptr;
    this->_app_data_package = pkg;
    this->_app_data_package["app_title"] = this;
    this->_statue = READY;
}

AppBase::~AppBase()
{
}

Resource AppBase::GetDataPackage() const
{
    return this->_app_data_package;
}

AppRuntimeStatue AppBase::GetStatue()
{
    return this->_statue;
}

lv_obj_t *AppBase::Start()
{
    if (this->_root != nullptr)
    {
        return this->_root;
    }

    // _root
    this->_root = lv_obj_create(nullptr);
    lv_obj_set_width(this->_root, WIDTH);
    lv_obj_set_height(this->_root, HEIGHT);
    lv_obj_set_flex_flow(this->_root, LV_FLEX_FLOW_COLUMN);

    // _title_container
    this->_title_container = lv_obj_create(this->_root);
    lv_obj_set_width(this->_title_container, WIDTH);
    lv_obj_set_height(this->_title_container, APP_TITLE_HEIGHT);

    // _title_disp
    this->_title_disp = lv_label_create(this->_title_container);
    lv_label_set_text(this->_title_disp, this->_app_data_package["app_title"].asString().c_str());
    lv_obj_align(this->_title_disp, LV_ALIGN_TOP_MID, 0, 0);

    // _container
    this->_container = lv_obj_create(this->_root);
    lv_obj_set_width(this->_container, WIDTH);
    lv_obj_set_height(this->_container, HEIGHT - APP_TITLE_HEIGHT);

    this->_statue = READY;

    return this->_root;
}

void AppBase::Loop()
{
    this->_statue = RUNNING;
}

void AppBase::Stop()
{
    lv_obj_del(this->_root);
    this->_statue = READY;
}
