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
    CoolWidget(/* args */);
    ~CoolWidget();
    void Show(lv_obj_t* father);        // Create obj and show; no animation
    void Hide();                        // Delete obj and hide; no animation
    void Update();                      // Update.
};

class Card : public CoolWidget
{
protected:
    lv_obj_t* _app_icon_disp;
    lv_obj_t* _app_name_disp;
    lv_obj_t* _container;

public:
    Card();
    ~Card();
    void Show(lv_obj_t* father);
    void SetName(std::string name);
    void SetIcon(Graph* graph);
    void SetContainer(lv_obj_t* container);
};

class InformationCard : public Card
{

};

#endif // __CoolWidgets_h
