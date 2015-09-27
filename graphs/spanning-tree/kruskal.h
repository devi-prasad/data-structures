#ifndef _INCLUDED_KRUSKAL_
#define _INCLUDED_KRUSKAL_

#include <stdint.h>
#include "graph.h"

/*
 * A set of bits. Supports super-fast membership tests.
 * The i-th bit of the set is 1 if i-th element is a member of this set.
 * we assume sets of cardinality less than 16.
 *  
 */
typedef uint16_t set_t;
set_t set_make(uint8_t v);
set_t set_union(set_t u, set_t v);
set_t set_find(set_t sets[], uint8_t nsets, uint8_t v);
int set_subset(set_t a, set_t b);


struct _edge_ {
    uint8_t u;
    uint8_t v;
    uint8_t weight;
    uint8_t selected;
};
typedef struct _edge_ Edge;

void spanning_tree_kruskal(const Graph *graph, Graph *tree);

#endif
