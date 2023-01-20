#include "CoolWidgets.h"
#include <string>
#include "lvgl.h"
#include "SysConf.h"
#include "Resource.h"
#include "AppBase.h"

CoolWidget::CoolWidget()
{
    this->_root = nullptr;
    this->resource["package_name"] = "Unnamed_Widget";
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

    this->resource["package_name"] = "Unnamed_Card";
    this->resource["title"] = "Untitled";
    this->resource["title_icon"] = CreateGraph();
    this->resource["container"] = Json::Value::null;

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
    lv_obj_set_style_radius(this->_root, CARD_RADIUS, LV_STATE_ANY);
    lv_obj_set_style_bg_color(this->_root, lv_color_hex(CARD_BGCOLOR), LV_STATE_ANY);
    lv_obj_set_flex_flow(this->_root, LV_FLEX_FLOW_COLUMN);

    // Title
    this->_title_disp = lv_obj_create(this->_root);
    lv_obj_set_style_pad_left(this->_title_disp, CARD_TITLE_X_OFFSET, LV_STATE_ANY);
    lv_obj_set_style_pad_top(this->_title_disp, CARD_TITLE_Y_OFFSET, LV_STATE_ANY);
    lv_obj_set_flex_flow(this->_title_disp, LV_FLEX_FLOW_ROW);
    // Title Icon
    if (this->resource["title_icon"].isObject())
    {
        this->_title_icon_disp = lv_img_create(this->_title_disp);
        lv_img_set_src(this->_title_icon_disp, this->resource["title_icon"]["graph"].asPointer());
        lv_obj_set_width(this->_title_icon_disp, this->resource["title_icon"]["width"].asUInt());
        lv_obj_set_height(this->_title_icon_disp, this->resource["title_icon"]["height"].asUInt());
        lv_img_set_zoom(this->_title_icon_disp, CARD_TITLE_ICON_ZOOM);
    }
    else
    {
        this->_title_icon_disp = lv_label_create(this->_title_disp);
        lv_label_set_text(this->_title_icon_disp, NO_IMG_INFO);
    }
    // Title Text
    this->_title_text_disp = lv_label_create(this->_title_disp);
    if (this->resource["title"].isString())
    {
        lv_label_set_text(this->_title_text_disp, this->resource["title"].asString().c_str());
    }
    else
    {
        lv_label_set_text(this->_title_text_disp, "Untitled");
    }

    // Container
    this->_content_disp = lv_obj_create(this->_root);
    lv_obj_set_scrollbar_mode(this->_content_disp, LV_SCROLLBAR_MODE_ACTIVE); // 滚动条
    lv_obj_t *new_obj = nullptr;
    if (this->resource["container"].isString())
    {
        // @todo 多行文字
        // 作为仅有的首行文字也需要加粗
        new_obj = lv_label_create(this->_content_disp);
        lv_label_set_text(new_obj, this->resource["container"].asString().c_str());
        lv_obj_add_style(new_obj, &this->_label_shadow, 0);
        this->_content_container_disp.push_back(new_obj);
    }
    else if (this->resource["container"].isPointer())
    {
        this->_content_container_disp.push_back(((CoolWidget *)this->resource["container"].asPointer())->Show(this->_content_disp));
    }
    // @todo 多行文字
    /*
    else if (this->resource["container"].isArray()) { }
    */

    return this->_root;
}

Desktop_AppIcon::Desktop_AppIcon()
{
    this->_app_icon_disp = nullptr;
    this->_app_name_disp = nullptr;
    this->resource["package_name"] = "Unnamed_Desktop_AppIcon";
    this->resource["app_package"] = CreateAppPackageData();
}

void Desktop_AppIcon::SetIcon(Resource& icon)
{
    this->resource["app_package"]["icon"] = icon;
}

void Desktop_AppIcon::SetTitle(std::string app_title)
{
    this->resource["app_package"]["app_title"] = app_title;
}

void Desktop_AppIcon::SetAppPointer(AppBase* app_pointer)
{
    this->resource["app_package"]["app_pointer"] = app_pointer;
}

lv_obj_t *Desktop_AppIcon::Show(lv_obj_t *father)
{
    if (this->_root != nullptr)
    {
        return this->_root;
    }

    CoolWidget::Show(father);
    // root
    lv_obj_set_size(this->_root, APP_ICON_ZOOM, APP_ICON_ZOOM + APP_ICON_ITEMS_PADDING + 14);
    lv_obj_set_flex_flow(this->_root, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(this->_root, APP_ICON_PADDING, LV_STATE_ANY);
    // icon
    this->_app_icon_disp = lv_img_create(this->_root);
    lv_img_set_size_mode(this->_app_icon_disp, LV_SIZE_CONTENT);
    lv_img_set_zoom(this->_app_icon_disp, APP_ICON_ZOOM);
    lv_obj_set_style_radius(this->_app_icon_disp, APP_ICON_RADIUS, LV_STATE_ANY);
    if (this->resource["app_package"]["icon"].isObject())
    {
        lv_img_set_src(this->_app_icon_disp, this->resource["app_package"]["graph"].asPointer());
    }
    else
    {
        lv_img_set_src(this->_app_icon_disp, LV_SYMBOL_DUMMY NO_IMG_INFO);
    }
    // name
    this->_app_name_disp = lv_label_create(this->_root);
    lv_label_set_text(this->_app_name_disp, this->resource["app_package"]["app_title"].asString().c_str());
    lv_obj_set_style_pad_top(this->_app_name_disp, APP_ICON_ITEMS_PADDING, LV_STATE_ANY);
    lv_obj_align(this->_app_name_disp, LV_ALIGN_BOTTOM_MID, 0, 0); // @todo 居中对齐

    return this->_root;
}
