#ifndef __Graph_h
#define __Graph_h

#include <Arduino.h>

struct Graph_t
{
    size_t width, height;
    uint16_t *graph;
    Graph_t();
    Graph_t(size_t w, size_t h, uint16_t *graph);
};

#endif // __Graph_h
