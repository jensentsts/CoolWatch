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

lv_obj_t *CoolWidget::Show(lv_obj_t *father = nullptr)
{
    if (this->_root == nullptr)
    {
        this->_root = lv_obj_create(father);
    }
    return this->_root;
}

void CoolWidget::Hide()
{
    if (this->_root != nullptr)
    {
        lv_obj_del(this->_root);
    }
}

Card::Card() : CoolWidget()
{
    this->_title_disp = nullptr;
    this->_title_text_disp = nullptr;
    this->_title_icon_disp = nullptr;
    this->_content_disp = nullptr;
    this->title_icon = nullptr;
    this->container_widget = nullptr;

    lv_style_init(&this->_label_shadow);
    lv_style_set_text_opa(&this->_label_shadow, LV_OPA_30);
    lv_style_set_text_color(&this->_label_shadow, lv_color_black());
}

lv_obj_t *Card::Show(lv_obj_t *father = nullptr)
{
    if (this->_root != nullptr)
    {
        return this->_root;
    }
    CoolWidget::Show(father);
    // Root
    lv_obj_set_size(this->_root, CARD_WIDTH, CARD_HEIGHT);
    lv_obj_set_style_radius(this->_root, CARD_RADIUS, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(this->_root, lv_color_hex(CARD_BGCOLOR), LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(this->_root, LV_FLEX_FLOW_COLUMN);

    // Title
    this->_title_disp = lv_obj_create(this->_root);
    lv_obj_set_style_pad_left(this->_title_disp, CARD_TITLE_X_OFFSET, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(this->_title_disp, CARD_TITLE_Y_OFFSET, LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(this->_title_disp, LV_FLEX_FLOW_ROW);
    // Title Icon
    if (this->title_icon != nullptr)
    {
        this->_title_icon_disp = lv_img_create(this->_title_disp);
        lv_img_set_src(this->_title_icon_disp, this->title_icon->graph);
        lv_obj_set_width(this->_title_icon_disp, this->title_icon->width);
        lv_obj_set_height(this->_title_icon_disp, this->title_icon->height);
        lv_img_set_zoom(this->_title_icon_disp, CARD_TITLE_ICON_ZOOM);
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
    this->_content_disp = lv_obj_create(this->_root);
    lv_obj_set_scrollbar_mode(this->_content_disp, LV_SCROLLBAR_MODE_ACTIVE); // 滚动条
    if (this->container_widget != nullptr)
    {
        this->_content_container_disp.push_back(this->container_widget->Show(this->_content_disp));
    }
    else
    {
        lv_obj_t *new_label;
        if (!this->container_text.empty())
        {
            std::vector<std::string>::iterator it = this->container_text.begin();
            // 首行文字需要加粗
            new_label = lv_label_create(this->_content_disp);
            lv_label_set_text(new_label, it->c_str());
            lv_obj_add_style(new_label, &this->_label_shadow, 0);
            this->_content_container_disp.push_back(new_label);
            // 添加其余文字
            it++;
            while (it != this->container_text.end())
            {
                lv_label_set_text(new_label, it->c_str());
                this->_content_container_disp.push_back(new_label);
                it++;
            }
        }
        else
        {
            // 首行文字需要加粗
            new_label = lv_label_create(this->_content_disp);
            lv_label_set_text(new_label, CARD_CONTENT_NOTHING);
            lv_obj_add_style(new_label, &this->_label_shadow, 0);
            this->_content_container_disp.push_back(new_label);
        }
    }

    return this->_root;
}

Desktop_AppIcon::Desktop_AppIcon()
{
    this->_app_icon_disp = nullptr;
    this->_app_name_disp = nullptr;
    this->_app_icon = nullptr;
}

void Desktop_AppIcon::SetIcon(Graph *app_icon)
{
    this->_app_icon = app_icon;
}

void Desktop_AppIcon::SetName(std::string app_name)
{
    this->_app_name = app_name;
}

lv_obj_t *Desktop_AppIcon::Show(lv_obj_t *father)
{
    if (this->_root != nullptr)
    {
        return this->_root;
    }

    CoolWidget::Show(father);
    // root
    lv_obj_set_size(this->_root, APP_ICON_ZOOM, APP_ICON_ZOOM + APP_ITEMS_PADDING + 14);
    lv_obj_set_flex_flow(this->_root, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(this->_root, APP_ICON_PADDING, LV_STATE_DEFAULT);
    // icon
    this->_app_icon_disp = lv_img_create(this->_root);
    lv_img_set_size_mode(this->_app_icon_disp, LV_SIZE_CONTENT);
    lv_img_set_zoom(this->_app_icon_disp, APP_ICON_ZOOM);
    lv_obj_set_style_radius(this->_app_icon_disp, APP_ICON_RADIUS, LV_STATE_DEFAULT);
    if (this->_app_icon != nullptr)
    {
        lv_img_set_src(this->_app_icon_disp, this->_app_icon->graph);
    }
    else
    {
        lv_img_set_src(this->_app_icon_disp, LV_SYMBOL_DUMMY NO_IMG_INFO);
    }
    // name
    this->_app_name_disp = lv_label_create(this->_root);
    lv_label_set_text(this->_app_name_disp, this->_app_name.c_str());
    lv_obj_set_style_pad_top(this->_app_name_disp, APP_ITEMS_PADDING, LV_STATE_DEFAULT);
    lv_obj_align(this->_app_name_disp, LV_ALIGN_BOTTOM_MID, 0, 0); // @todo 居中对齐

    return this->_root;
}
