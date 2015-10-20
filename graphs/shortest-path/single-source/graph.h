#ifndef _INCLUDED_GRAPH_
#define _INCLUDED_GRAPH_

#include <stdint.h>

#define MAX_VERTS 12                       /* we deal with tiny graphs! */ 

struct _graph_ {
    uint8_t  vc;                           /* actual # vertices in the graph */
    int32_t  adj[MAX_VERTS][MAX_VERTS];    /* edges */
    char     *labels[MAX_VERTS];           /* for a labeled graph */
    uint8_t  ec;                           /* number of distinct edges */
};
typedef struct _graph_ Graph;

#endif
