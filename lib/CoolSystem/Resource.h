/**
 * @file Resource.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 拓充Jsoncpp的Value类型，使之满足项目对指针的需求。
 * @note 规定：ResourceNode的所有子类中，public下可以访问到的变量应一律通过[]进行访问。
 * @version 1.0.0
 * @date 2023-01-20
 *
 * @copyright CC4.0 BY-NC-SA
 *
 */
#ifndef __Resource_h
#define __Resource_h

#include <json/json.h>

typedef Json::Value Resource;

#endif // __Resource_h
