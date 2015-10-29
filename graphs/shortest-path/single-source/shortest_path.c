#include <assert.h>
#include <string.h>
#include "graph.h"
#include "vertex.h"
#include "heap.h"
#include "shortest_path.h"

/*
 * Implements Dijkstra's single-source shortest path algorithm.
 *
 */

static void _init_single_source_(Vertex verts[], uint32_t len, uint32_t src)
{
    uint32_t i;
    assert(len > 0 && src >= 0 && src < len);

    for (i = 0; i < len; ++i) {
    	verts[i].id = i;
        verts[i].dist = DIST_INFINITE;
        verts[i].pred = NO_PREDECESSOR;
    }

    verts[src].dist = 0;
}

#include <stdio.h>

static uint32_t _get_index_(Vertex verts[], uint32_t len, uint32_t index)
{
    uint32_t i;

    for (i = 0; i <= len; ++i) {
       if (verts[i].id == index) return i;
    }

    fprintf(stderr, "Internal error! No vertex with id %d in the heap!\n", index);
    assert(0);
    return -1;
}

Path find_shortest_path(const Graph g, uint32_t src_id)
{
	const uint32_t NUM_VERTS = g.vc;
    Vertex verts[NUM_VERTS + 1];

    Path path = { 0, {{0, 0, 0}, } };
    
    _init_single_source_(verts + 1, NUM_VERTS, src_id);

    Heap verts_heap = heap_new(verts, NUM_VERTS);
    while (heap_size(&verts_heap) > 0) {
        Vertex vertex = heap_get_min(&verts_heap);
        if (vertex.dist != DIST_INFINITE) {
            uint32_t u, v, j;
            for (u = vertex.id, j = 0; j < NUM_VERTS; ++j) {
                int32_t w = g.adj[u][j];
                if (w != 0 && w != DIST_INFINITE) {
                    v = _get_index_(verts, NUM_VERTS, j); 
                    if (verts[v].dist > vertex.dist + w) {
                        verts[v].dist = vertex.dist + w;
                        verts[v].pred = u;
                    }
                }
            }
            path.verts[path.len] = vertex;
            ++path.len;
        }

        heap_extract_min(&verts_heap);
    }
    heap_delete(&verts_heap);

    return path;
}
