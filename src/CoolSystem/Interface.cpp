#include "Interface.h"
#include "Mgr.h"

lv_obj_t *InterfaceBase::GetActiveLvObj()
{
    return nullptr;
}
template <typename t>
void InterfaceBase::SetActiveObj(t obj)
{
}

Desktop::Desktop() : InterfaceBase()
{
    this->_bgimg = nullptr;
    this->_bgimg_disp = nullptr;
    this->_apps_disp = nullptr;
}

void Desktop::Show()
{
    if (this->_root != nullptr)
    {
        return;
    }

    InterfaceBase::Show(nullptr);
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
