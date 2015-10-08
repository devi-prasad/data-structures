#ifndef _INCLUDED_VERTEX_
#define _INCLUDED_VERTEX_

#include <stdint.h>

typedef struct {
	uint32_t id;
    uint32_t dist;
    uint32_t pred;
} Vertex;

#define DIST_INFINITE (0x7FFFFFFF)
#define NO_PREDECSSOR (0x7FFFFFFF)

#endif