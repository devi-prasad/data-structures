#include <stddef.h>
#include "prim.h"
#include "assert.h"

#define MAX_WEIGHT     0xFF
#define NULL_PARENT    0xFF
#define TRUE           1
#define FALSE          0

/*
 * selects a vertex with minimum weight among the unmarked ones.
 */ 
static uint8_t 
_extract_min_weight_vertex_(const uint8_t weight[], const uint8_t marked[], const uint8_t nverts)
{
    uint8_t i, min, index = nverts; 
    
    for (i = 0, min = MAX_WEIGHT; i < nverts; ++i) {
        if (!marked[i] && weight[i] < min) {
            min = weight[i];
            index = i;
	    }
    }

    assert(index != nverts);
    return index;
}

/*
 * A simple-minded procedure to initialize the adjacency matrix of the new tree.
 *
 */
static void 
_init_tree_(const uint8_t root, const uint8_t parent[], const uint8_t weight[], 
            const uint8_t nverts, Graph *tree)
{
    int u, v;
    
    assert(nverts > 0 && tree != NULL);
    assert(root < nverts);
    assert(tree->vc >= nverts);

    for (u = 0; u < nverts; ++u) {
        for (v = 0; v < nverts; ++v) {
            tree->adj[u][v] = 0;
            tree->adj[v][u] = 0;
        }
    }

    for (v = 0; v < nverts; ++v) {
    	u = parent[v];
        assert(v == root || parent[v] != NULL_PARENT);
        if (v != root) {
            /* printf("parent[%d] -> %d\n", v, u); */
            tree->adj[u][v] = weight[v];
            tree->adj[v][u] = weight[v];
        }
    }
}

/*
 * A greedy technique for computing the minimum weight spanning tree.
 * 'graph' is the input and 'tree' is the result.
 * It is perfectly alright to have 'graph' and 'tree' share identity.
 *
 */
void spanning_tree_prim(const Graph *graph, uint8_t root, Graph *tree)
{
    const uint8_t VERTEX_COUNT = graph->vc;
    uint8_t weight[VERTEX_COUNT], marked[VERTEX_COUNT], parent[VERTEX_COUNT];
    uint8_t u, v;

    for (v = 0; v < VERTEX_COUNT; ++v) {
        weight[v] = MAX_WEIGHT;
        marked[v] = FALSE;
        parent[v] = NULL_PARENT;
    }
    weight[root] = 0;

    uint8_t unmarked_vertices_exist = VERTEX_COUNT;
    while (--unmarked_vertices_exist) {
        u = _extract_min_weight_vertex_(weight, marked, VERTEX_COUNT);
        marked[u] = TRUE;     /* V - {u} */
        for (v = 0; v < VERTEX_COUNT; ++v) {
            if (graph->adj[u][v] && !marked[v] && 
                                    graph->adj[u][v] < weight[v]) {
                parent[v]  = u;
                weight[v] = graph->adj[u][v];
            }
        }
    }

    _init_tree_(root, parent, weight, VERTEX_COUNT, tree);
}
