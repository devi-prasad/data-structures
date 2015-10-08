#ifndef _INCLUDED_SINGLE_SOURCE_SHORTEST_PATH_
#define _INCLUDED_SINGLE_SOURCE_SHORTEST_PATH_

#include "vertex.h"

uint32_t find_shortest_path(const Graph g, 
                        uint32_t src, 
                        Vertex verts[], uint32_t len);

#endif