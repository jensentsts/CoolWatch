#ifndef __AsResource_h
#define __AsResource_h

/**
 * @brief 用于为 MgrBase 派生类赋予访问内部信息的权限
 */
class Resource
{
private:
    friend class MgrBase;
};

#endif // __AsResource_h
