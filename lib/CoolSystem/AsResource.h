/**
 * @file AsResource.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 
 * @version 1.0.0
 * @date 2023-01-15
 * 
 * @copyright CC4.0 BY-NC-SA
 * 
 */

#ifndef __AsResource_h
#define __AsResource_h

#include "Mgr.h"

/**
 * @brief 用于为 MgrBase 派生类赋予访问内部信息的权限
 */
class Resource
{
private:
    friend class MgrBase;
};

#endif // __AsResource_h
