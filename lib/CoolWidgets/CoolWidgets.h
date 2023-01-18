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

    CoolWidget(/* args */);
    ~CoolWidget();
    void Show(lv_obj_t* father);        // Create obj and show; no animation
    void Hide();                        // Delete obj and hide; no animation
    void Update();                      // Update.
};

class Card : public CoolWidget
{
protected:
    lv_obj_t* _title_text_disp;
    lv_obj_t* _title_icon_disp;
    lv_obj_t* _container_disp;
    lv_obj_t* _title_disp;

public:
    Card();
    ~Card();
    void Show(lv_obj_t* father);

    std::string title;
    Graph* title_icon;
    std::string container_text;
    CoolWidget* container_widget;
};


#endif // __CoolWidgets_h
