/**
 * @file CoolWidgets.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 复用组件，使用LVGL
 * @version 1.0.0
 * @date 2023-01-18
 *
 * @copyright CC4.0 BY-NC-SA
 *
 */

#ifndef __CoolWidgets_h
#define __CoolWidgets_h

#include "lvgl.h"
#include <string>
#include <vector>
#include "Resource.h"
#include "Graph.h"
#include "AppBase.h"

/**
 * @brief 组件基础
 */
class CoolWidget
{
protected:
    lv_obj_t *_root;

public:
    Resource resource;

    CoolWidget();
    ~CoolWidget();
    lv_obj_t *Show(lv_obj_t *father); // Create obj and show; @todo animation
    void Hide();                      // Delete obj and hide; @todo animation
};

class Card : public CoolWidget
{
protected:
    lv_obj_t *_title_disp;
    lv_obj_t *_title_text_disp;
    lv_obj_t *_title_icon_disp;
    lv_obj_t *_content_disp;
    std::vector<lv_obj_t *> _content_container_disp;

    static lv_style_t _label_shadow;    // 用于实现类似于加粗的效果

public:
    Card();
    lv_obj_t *Show(lv_obj_t *father);

    //std::string title;
    //Graph *title_icon;
    //std::vector<std::string> container_text;
    //CoolWidget *container_widget;
};

class Desktop_AppIcon : public CoolWidget
{
protected:
    lv_obj_t *_app_icon_disp;
    lv_obj_t *_app_name_disp;

public:
    Desktop_AppIcon();
    void SetIcon(Resource& icon);
    void SetTitle(std::string app_title);
    void SetAppPointer(AppBase* app_pointer);
    lv_obj_t *Show(lv_obj_t *father);
};

#endif // __CoolWidgets_h
