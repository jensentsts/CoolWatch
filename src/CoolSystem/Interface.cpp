#include "Interface.h"
#include <string>
#include "Mgr.h"
#include "CoolWidgets.h"
#include "lvgl.h"

template <typename IndexType>
Resource &InterfaceBase::operator[](IndexType index)
{
    return this->resource[index];
}

/**
 * @brief 在桌面上点击app图标时，启动app
 *
 * @param arg app_pointer
 */
void Desktop_AppIcon_OnClick(lv_event_t *arg)
{
    AppBase *app_pointer = (AppBase *)arg;
    task_mgr.StartApp(app_pointer);
    // @todo animation
}

Desktop::Desktop() : InterfaceBase()
{
    this->_bgimg_disp = nullptr;
    this->resource["package_name"] = "Desktop";
    this->resource["transfer"][LV_DIR_LEFT] = "Cards";
    this->resource["transfer"][LV_DIR_RIGHT] = "MainInterface";
    this->resource["transfer"][LV_DIR_BOTTOM] = "TopBar";
}

void Desktop::Show()
{
    if (this->_root != nullptr)
    {
        return;
    }

    InterfaceBase::Show(nullptr);
    // @todo background
    Desktop_AppIcon new_icon;
    Resource app_package_array = app_package_mgr.GetAppPackageArray();
    for (size_t i = 0; i < app_package_array.size(); ++i)
    {
        new_icon.SetTitle(app_package_array[i]["app_title"].asString());
        new_icon.SetIcon(app_package_array[i]["icon"]["graph"]);
        lv_obj_add_event_cb(new_icon.Show(this->_root),
                            Desktop_AppIcon_OnClick,
                            LV_EVENT_CLICKED,
                            (void *)app_package_array[i]["app_pointer"].asPointer());
        // @todo animation
    }
}

Cards::Cards() : InterfaceBase()
{
    this->resource["package_name"] = "Cards";
}

Cards::~Cards()
{
}

Lock::Lock() : InterfaceBase()
{
    this->resource["package_name"] = "Lock";
}

Lock::~Lock()
{
}

void Lock::Show()
{
    if (this->_root != nullptr)
    {
        return;
    }
    InterfaceBase::Show(nullptr);

    // background

    // time

    // date
}

TopBar::TopBar()
{
    this->resource["package_name"] = "TopBar";
}

TopBar::~TopBar()
{
}

void TopBar::Show()
{
}

StartAnimation::StartAnimation() : InterfaceBase()
{
    this->_label = nullptr;
    this->resource["package_name"] = "StartAnimation";
}

StartAnimation::~StartAnimation()
{
}

lv_obj_t *StartAnimation::Show()
{
    if (this->_root != nullptr)
    {
        return this->_root;
    }

    InterfaceBase::Show(nullptr);
    // @todo 设计更丰富的动画效果
    this->_label = lv_label_create(this->_root);
    lv_label_set_text(this->_label, "Hello, World");
    lv_obj_set_align(this->_label, LV_ALIGN_CENTER);

    return this->_root;
}

bool StartAnimation::isFinal()
{
    /* @todo */
    return true;
}

StopAnimation::StopAnimation() : InterfaceBase()
{
    this->resource["package_name"] = "StopAnimation";
}

StopAnimation::~StopAnimation()
{
}

lv_obj_t *StopAnimation::Show()
{
    if (this->_root != nullptr)
    {
        return this->_root;
    }

    InterfaceBase::Show(nullptr);
    // @todo 设计更丰富的动画效果
    this->_label = lv_label_create(this->_root);
    lv_label_set_text(this->_label, "Hello, World");
    lv_obj_set_align(this->_label, LV_ALIGN_CENTER);

    return this->_root;
}

bool StopAnimation::isFinal()
{
    /* @todo */
    return true;
}
