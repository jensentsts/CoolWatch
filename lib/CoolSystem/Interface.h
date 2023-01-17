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

class InterfaceBase : public Resource 
{
protected:
    lv_obj_t *_root;
};

/**
 * @brief 桌面
 */
class Desktop : public InterfaceBase
{
private:
    /* data */
public:
    Desktop(/* args */);
    ~Desktop();
};

/**
 * @brief 卡片
 */
class Cards : public InterfaceBase
{
private:
    /* data */
public:
    Cards(/* args */);
    ~Cards();
};

/**
 * @brief 锁屏
 */
class Lock : public InterfaceBase
{
private:
    /* data */
public:
    Lock(/* args */);
    ~Lock();
};

/**
 * @brief 开机动画
 */
class StartAnimation : public InterfaceBase
{
private:
    /* data */
public:
    StartAnimation(/* args */);
    ~StartAnimation();
};

/**
 * @brief 关机动画
 */
class StopAnimation : public InterfaceBase
{
private:
    /* data */
public:
    StopAnimation(/* args */);
    ~StopAnimation();
};

#endif // __Interface_h
