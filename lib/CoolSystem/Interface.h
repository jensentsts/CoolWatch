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
};

/**
 * @brief 桌面
 */
class Desktop : public InterfaceBase
{
private:
    lv_obj_t *_bgimg_disp;
    std::vector<Desktop_AppIcon> _icons;

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

/**
 * @brief 顶部状态栏（时间、电量等）
 */
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
