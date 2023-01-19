/**
 * @file Interface.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief
 * @version 1.0.0
 * @date 2023-01-17
 *
 * @copyright CC4.0 BY-NC-SA
 *
 */

#ifndef __Interface_h
#define __Interface_h

#include <map>
#include "AsResource.h"
#include "lvgl.h"
#include "CoolWidgets.h"

struct TransferObj
{
    lv_dir_t dir;
    lv_dir_t area;
};

class InterfaceBase : public CoolWidget
{
public:
    std::map<TransferObj, InterfaceBase *> transfer;
    lv_obj_t *GetActiveLvObj(); // 获取活动对象，例如被点击的卡片
    template <typename t>
    void SetActiveObj(t obj);
};

/**
 * @brief 桌面
 */
class Desktop : public InterfaceBase
{
private:
    Graph_t *_bgimg;
    lv_obj_t *_bgimg_disp;
    lv_obj_t *_apps_disp;

public:
    Desktop();
    void Show();
    void SetActiveObj(size_t index);
};

/**
 * @brief 卡片
 */
class Cards : public InterfaceBase
{
private:
public:
    Cards();
    ~Cards();
};

/**
 * @brief 锁屏
 */
class Lock : public InterfaceBase
{
private:
    lv_obj_t *_time_disp;
    lv_obj_t *_date_disp;
    lv_obj_t *_lock_bgimg;

public:
    Lock();
    ~Lock();
    void Show();
    void SetActiveObj(size_t index);
};

class TopBar : public InterfaceBase
{
private:
    lv_obj_t *_time_disp;
    lv_obj_t *_battery_disp;
    lv_obj_t *_battery_num_disp;
    lv_obj_t *_icons_disp;

public:
    TopBar();
    ~TopBar();
    void Show();
};

/**
 * @brief 开机动画
 */
class StartAnimation : public InterfaceBase
{
private:
    lv_obj_t *_label;

public:
    StartAnimation();
    ~StartAnimation();
    lv_obj_t *Show();
    bool isFinal();
};

/**
 * @brief 关机动画
 */
class StopAnimation : public InterfaceBase
{
private:
    lv_obj_t *_label;

public:
    StopAnimation();
    ~StopAnimation();
    lv_obj_t *Show();
    bool isFinal();
};

class AppInterface : public InterfaceBase
{

public:
    AppInterface();
    lv_obj_t *Show();

};

#endif // __Interface_h
