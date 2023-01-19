#include "Graph.h"

Graph_t::Graph_t()
{
    this->width = 0;
    this->height = 0;
    this->graph = nullptr;
}

Graph_t::Graph_t(size_t w, size_t h, uint16_t *graph)
{
    this->width = w;
    this->height = h;
    this->graph = graph;
}
