
#include "Graph.h"
#include "SysConf.h"
#include "AppBase.h"
#include "lvgl.h"

AppPackageData_t::AppPackageData_t()
{
    this->package_name = "Untitled";
    this->app_title = "Untitled";
    this->icon = Graph_t();
}

AppPackageData_t::AppPackageData_t(std::string package_name, std::string app_name, Graph_t icon)
{
    this->package_name = package_name;
    this->app_title = app_name;
    this->icon = icon;
}

AppBase::AppBase()
{
    this->_root = nullptr;
    this->_app_data_package = AppPackageData_t();
    this->_statue = READY;
}

AppBase::AppBase(AppPackageData_t pkg)
{
    this->_root = nullptr;
    this->_app_data_package = pkg;
    this->_statue = READY;
}

AppBase::~AppBase()
{
}

AppPackageData_t *AppBase::GetDataPackage()
{
    return &this->_app_data_package;
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
    lv_label_set_text(this->_title_disp, this->_app_data_package.app_title.c_str());
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
