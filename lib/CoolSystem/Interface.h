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

#include "AsResource.h"
#include "lvgl.h"
#include "CoolWidgets.h"

class InterfaceBase : public CoolWidget
{

public:
    InterfaceBase& transfer(lv_dir_t dir);
};

/**
 * @brief 桌面
 */
class Desktop : public InterfaceBase
{
private:
    lv_obj_t* _desktop_bgimg;

public:
    Desktop();
    ~Desktop();
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
    lv_obj_t* _time_disp;
    lv_obj_t* _date_disp;
    lv_obj_t* _lock_bgimg;

public:
    Lock();
    ~Lock();
    void Show();
    
};

class TopBar : public InterfaceBase
{
private:
    lv_obj_t* _time_disp;
    lv_obj_t* _battery_disp;
    lv_obj_t* _battery_num_disp;
    lv_obj_t* _icons_disp;

public:
    TopBar();
    ~TopBar();
    void Show();
    void Hide();
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
    void Start();
    void Stop();
    bool isFinal();
};

/**
 * @brief 关机动画
 */
class StopAnimation : public InterfaceBase
{
private:
public:
    StopAnimation();
    ~StopAnimation();
    void Start();
    void Stop();
    bool isFinal();
};

#endif // __Interface_h
