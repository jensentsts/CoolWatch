#include "Graph.h"
#include "Resource.h"

Resource CreateGraph(size_t width/* = 0*/, size_t height/* = 0*/, uint16_t *graph/* = nullptr*/)
{
    Resource res;
    res["width"] = width;
    res["height"] = height;
    res["graph"] = graph;
    return res;
}
