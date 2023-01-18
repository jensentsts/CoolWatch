#include "CoolWidgets.h"
#include "lvgl.h"

CoolWidget::CoolWidget()
{
    this->_root = nullptr;
}

CoolWidget::~CoolWidget()
{
    if (this->_root != nullptr)
    {
        lv_obj_del(this->_root);
    }
}

void CoolWidget::Show(lv_obj_t *father = nullptr)
{
    this->_root = lv_obj_create(father);
}

void CoolWidget::Hide()
{
    if (this->_root != nullptr)
    {
        lv_obj_del(this->_root);
    }
}

void CoolWidget::Update()
{
}

void Card::Show(lv_obj_t* father = nullptr)
{
    CoolWidget::Show(father);
}


