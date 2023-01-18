#ifndef __Graph_h
#define __Graph_h

#include <Arduino.h>

struct Graph
{
    size_t width, height;
    uint16_t *graph;
};

#endif // __Graph_h
