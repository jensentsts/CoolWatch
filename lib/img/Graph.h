#ifndef __Graph_h
#define __Graph_h

#include <Arduino.h>
#include "Resource.h"
/**
 * @brief Create a Graph object
 * 
 * @param width 宽度
 * @param height 高度
 * @param graph 图片指针
 * @return Resource 返回格式：{ "width": width, "height": height, "graph": graph }
 */
Resource CreateGraph(size_t width = 0, size_t height = 0, uint16_t *graph = nullptr);

#endif // __Graph_h
