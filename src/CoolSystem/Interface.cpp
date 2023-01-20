#include "Interface.h"
#include <string>
#include "Mgr.h"
#include "CoolWidgets.h"
#include "lvgl.h"

void AppIcon_OnClick(lv_event_t * arg){
    std::string package_name = *(std::string*)arg;
    task_mgr.StartApp(package_name);
    // @todo animation
}

Desktop::Desktop() : InterfaceBase()
{
    this->_bgimg = nullptr;
    this->_bgimg_disp = nullptr;
}

void Desktop::Show()
{
    if (this->_root != nullptr)
    {
        return;
    }

    InterfaceBase::Show(nullptr);
    Desktop_AppIcon new_icon;
    for (size_t i = 0; i < app_package_mgr.size(); ++i)
    {
        new_icon.SetName(app_package_mgr[i]->GetDataPackage()->app_title);
        new_icon.SetIcon(&app_package_mgr[i]->GetDataPackage()->icon);
        this->_icons.push_back(new_icon);
        lv_obj_add_event_cb(new_icon.Show(this->_root), 
                            AppIcon_OnClick, 
                            LV_EVENT_CLICKED, 
                            (void*)&app_package_mgr[i]->GetDataPackage()->package_name);
        // @todo animation
    }
}

Cards::Cards() : InterfaceBase()
{
}

Cards::~Cards()
{
}

Lock::Lock() : InterfaceBase()
{
}

Lock::~Lock()
{
}

void Lock::Show()
{
}

TopBar::TopBar()
{
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
