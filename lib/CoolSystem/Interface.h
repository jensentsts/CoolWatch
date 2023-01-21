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
#include "Resource.h"
#include "lvgl.h"
#include "CoolWidgets.h"

class InterfaceBase : public CoolWidget
{
public:
    template<typename IndexType>
    Resource& operator[](IndexType);
    lv_obj_t* Show(lv_obj_t*);
    void Hide();
};

/**
 * @brief 主界面，显示一些必要信息，例如时间、天气、QQ与微信通知数等
 */
class MainInterface : public InterfaceBase
{
public:
};

/**
 * @brief 桌面
 */
class Desktop : public InterfaceBase
{
private:
    lv_obj_t *_bgimg_disp;

public:
    Desktop();
    void Show();
    void Hide();
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
    void Show();
    void Hide();
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
    void Show();
    void Hide();
    bool isFinal();
};

class AppInterface : public InterfaceBase
{
public:
    AppInterface();
    void Show(lv_obj_t **app_root);
    void Hide();
};

#endif // __Interface_h
