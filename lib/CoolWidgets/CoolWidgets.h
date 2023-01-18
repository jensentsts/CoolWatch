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
#include "AsResource.h"
#include "Graph.h"

/**
 * @brief 组件基础
 */
class CoolWidget : public Resource
{
protected:
    lv_obj_t *_root;

public:
    std::string name;

    CoolWidget();
    ~CoolWidget();
    lv_obj_t *Show(lv_obj_t *father); // Create obj and show; no animation
    void Hide();                      // Delete obj and hide; no animation
};

class Card : public CoolWidget
{
protected:
    lv_obj_t *_title_disp;
    lv_obj_t *_title_text_disp;
    lv_obj_t *_title_icon_disp;
    lv_obj_t *_content_disp;
    std::vector<lv_obj_t *> _content_container_disp;

    static lv_style_t _label_shadow;

public:
    Card();
    lv_obj_t *Show(lv_obj_t *father);

    std::string title;
    Graph *title_icon;
    std::vector<std::string> container_text;
    CoolWidget *container_widget;
};

class Desktop_AppIcon : public CoolWidget
{
protected:
    lv_obj_t *_app_icon_disp;
    lv_obj_t *_app_name_disp;
    std::string _app_name;
    Graph* _app_icon;

public:
    Desktop_AppIcon();
    void SetIcon(Graph *app_icon);
    void SetName(std::string app_name);
    lv_obj_t *Show(lv_obj_t *father);
};

#endif // __CoolWidgets_h
