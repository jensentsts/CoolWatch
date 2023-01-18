#include "CoolWidgets.h"
#include "lvgl.h"
#include <string>
#include "SysConf.h"

CoolWidget::CoolWidget()
{
    this->_root = nullptr;
    this->name = "No-Name";
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
    #if DEBUG == 1
    Serial.printf("CoolWidget %s: Update", this->name.c_str());
    #endif // DEBUG
}

Card::Card() : CoolWidget()
{
    this->_title_disp = nullptr;
    this->_title_text_disp = nullptr;
    this->_title_icon_disp = nullptr;
    this->_container_disp = nullptr;
    this->title_icon = nullptr;
    this->container_widget = nullptr;
}

void Card::Show(lv_obj_t *father = nullptr)
{
    /* @todo */
    CoolWidget::Show(father);
    // Root
    lv_obj_set_size(this->_root, CARD_WIDTH, CARD_HEIGHT);
    lv_obj_set_style_radius(this->_root, CARD_RADIUS, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(this->_root, lv_color_hex(CARD_BGCOLOR), LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(this->_root, LV_FLEX_FLOW_COLUMN);

    // Title
    this->_title_disp = lv_obj_create(this->_root);
    lv_obj_align(this->_title_disp, LV_ALIGN_TOP_LEFT, CARD_TITLE_X_OFFSET, CARD_TITLE_Y_OFFSET);
    lv_obj_set_flex_flow(this->_title_disp, LV_FLEX_FLOW_ROW);
    // Title Icon
    if (this->title_icon != nullptr)
    {
        this->_title_icon_disp = lv_img_create(this->_title_disp);
        lv_img_set_src(this->_title_icon_disp, this->title_icon->graph);
        lv_obj_set_width(this->_title_icon_disp, this->title_icon->width);
        lv_obj_set_height(this->_title_icon_disp, this->title_icon->height);
    }
    else
    {
        this->_title_icon_disp = lv_label_create(this->_title_disp);
        lv_label_set_text(this->_title_icon_disp, NO_IMG_INFO);
        #if DEBUG == 1
        Serial.printf("Widget %s has NO title icon. %s", this->name.c_str(), NO_IMG_INFO);
        #endif // DEBUG
    }
    // Title Text
    this->_title_text_disp = lv_label_create(this->_title_disp);
    if (this->title.empty())
    {
        lv_label_set_text(this->_title_text_disp, "Untitled");
    }
    else
    {
        lv_label_set_text(this->_title_text_disp, this->title.c_str());
    }

    // Container
    if (this->container_widget != nullptr)
    {
        this->container_widget->Show(this->_root);
        this->_container_disp = nullptr;
    }
    else
    {
        this->_container_disp = lv_label_create(this->_root);
        lv_label_set_text(this->_container_disp, this->container_text.c_str());
    }
}
