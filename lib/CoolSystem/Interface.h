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
    
public:
    Lock();
    ~Lock();
};

/**
 * @brief 开机动画
 */
class StartAnimation : public InterfaceBase
{
private:
    
public:
    StartAnimation();
    ~StartAnimation();
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
};

#endif // __Interface_h
