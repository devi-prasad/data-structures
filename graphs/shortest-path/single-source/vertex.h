#ifndef _INCLUDED_VERTEX_
#define _INCLUDED_VERTEX_

#include <stdint.h>

typedef struct {
	uint32_t id;
    int32_t dist;
    uint32_t pred;
} Vertex;

#define DIST_INFINITE (0x7FFFFFFF) /* largest positive 32-bit number */
#define NO_PREDECESSOR (0x7FFFFFFF)

#define MAX_PATH_VERTS 16

typedef struct {
    uint32_t len;
    Vertex verts[MAX_PATH_VERTS];
} Path;

#endif