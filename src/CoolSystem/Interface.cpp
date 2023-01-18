#include "Interface.h"
#include "Mgr.h"

InterfaceBase &InterfaceBase::transfer(lv_dir_t dir)
{
    return *this;
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

void Lock::Show()
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
    this->Show(nullptr);
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
    this->Show(nullptr);
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
