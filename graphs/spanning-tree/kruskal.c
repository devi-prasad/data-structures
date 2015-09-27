#include <stdlib.h>
#include <assert.h>
#include "kruskal.h"

typedef int (Comparator)(const void *, const void *);

static int _compare_edges_(const void *p, const void *q)
{
	const Edge *e1 = p;
	const Edge *e2 = q;

    if (e1->weight < e2->weight) return -1;
    else if (e1->weight > e2->weight) return 1;
    return 0;
}

static void _make_sorted_edge_array_(const Graph *graph, Edge edges[], uint8_t nedges)
{
    const uint8_t VERTEX_COUNT = graph->vc;
    uint8_t u, v;
    uint8_t i;

    for (i = 0, u = 0; u < VERTEX_COUNT; ++u) {
        for (v = u+1; v < VERTEX_COUNT; ++v) {
            if (graph->adj[u][v]) {
            	assert(i < nedges);
            	edges[i].u = u;
            	edges[i].v = v;
    	        edges[i].weight = graph->adj[u][v];
    	        ++i;
    	    }
    	}
    }
    assert(i == nedges);
    qsort(edges, nedges, sizeof(Edge), _compare_edges_);
    for (i = 0; i < nedges - 1; ++i) {
    	assert(edges[i].weight <= edges[i+1].weight);
    }
}

void spanning_tree_kruskal(const Graph *graph, Graph *tree)
{
    const uint8_t VERTEX_COUNT = graph->vc;
    const uint8_t EDGE_COUNT = graph->ec;
    set_t vertex_set[VERTEX_COUNT];
    Edge edges[EDGE_COUNT];

    uint8_t i, u, v;

    for (i = 0; i < VERTEX_COUNT; ++i) {
        vertex_set[i] = set_make(i);
    }
    _make_sorted_edge_array_(graph, edges, EDGE_COUNT);

    for (i = 0; i < VERTEX_COUNT; ++i) {
    	edges[i].selected = 0;
        u = edges[i].u;
        v = edges[i].v;
        if (set_find(vertex_set, VERTEX_COUNT, u) != 
                                     set_find(vertex_set, VERTEX_COUNT, v)) {
            edges[i].selected = 1;
            vertex_set[u] = vertex_set[v] = set_union(vertex_set[u], vertex_set[v]);
    	}
    }
    
    for (i = 0; i < EDGE_COUNT; ++i) {
        u = edges[i].u;
        v = edges[i].v;
        if (edges[i].selected == 1) {
            tree->adj[u][v] = edges[i].weight;
            tree->adj[v][u] = edges[i].weight;
        } else {
            tree->adj[u][v] = tree->adj[v][u] = 0;
        }
    }
}

