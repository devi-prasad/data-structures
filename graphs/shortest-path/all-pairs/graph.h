#ifndef _INCLUDED_GRAPH_
#define _INCLUDED_GRAPH_

#include <stdint.h>

#define MAX_VERTS 12                   /* we deal with tiny graphs! */
#define GRAPH_MAX_VERTS 12             /* we deal with tiny graphs! */ 
#define MAX_WALK_LEN (MAX_VERTS * 3)   /* 3 edges per vertex is reasonable */
#define MAX_LABEL_LEN 16               /* length of a vertex label */

#define INFINITE 127                   /* largest positive 8-bit value */

typedef int8_t dist_t;

struct _graph_ {
    uint8_t  vc;                           /* actual # vertices in the graph */
    dist_t   adj[MAX_VERTS][MAX_VERTS];    /* edges */
    char     *labels[MAX_VERTS];           /* for a labeled graph */
};
typedef struct _graph_ Graph;

#endif
