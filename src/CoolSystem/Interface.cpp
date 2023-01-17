#include "Interface.h"
#include "Mgr.h"

InterfaceBase::InterfaceBase()
{
    this->_root = lv_obj_create(nullptr);
    lv_obj_add_flag(this->_root, LV_OBJ_FLAG_HIDDEN);
}

InterfaceBase::~InterfaceBase()
{
}

void InterfaceBase::Show()
{
    lv_obj_clear_flag(this->_root, LV_OBJ_FLAG_HIDDEN);
}

void InterfaceBase::Hide()
{
    lv_obj_add_flag(this->_root, LV_OBJ_FLAG_HIDDEN);
}

Desktop::Desktop()
{

}

Desktop::~Desktop()
{
}

Cards::Cards()
{
}

Cards::~Cards()
{
}

Lock::Lock()
{
}

Lock::~Lock()
{
}

StartAnimation::StartAnimation()
{
    this->_label = lv_label_create(this->_root);
    lv_label_set_text(this->_label, "Hello, World");
    lv_obj_set_align(this->_label, LV_ALIGN_CENTER);
}

StartAnimation::~StartAnimation()
{
}

void StartAnimation::Start()
{
    this->Show();
    /* @todo */
}

void StartAnimation::Stop()
{
    this->Hide();
    /* @todo */
}

bool StartAnimation::isFinal()
{
    /* @todo */
    return true;
}

StopAnimation::StopAnimation()
{
}

StopAnimation::~StopAnimation()
{
}

void StopAnimation::Start()
{
    this->Show();
    /* @todo */
}

void StopAnimation::Stop()
{
    this->Hide();
    /* @todo */
}

bool StopAnimation::isFinal()
{
    /* @todo */
    return true;
}
