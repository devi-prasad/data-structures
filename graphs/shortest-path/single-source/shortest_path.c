#include <assert.h>
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
        verts[i].pred = NO_PREDECSSOR;
    }
    verts[src].dist = 0;
}

uint32_t find_shortest_path(const Graph g, 
                            uint32_t src_id,
                            Vertex verts[],
                            uint32_t len)
{
	const uint32_t NUM_VERTS = graph_vertex_count(g);
	assert(len >= NUM_VERTS + 1);

    if (len < NUM_VERTS + 1) return 0;

    _init_single_source_(verts + 1, NUM_VERTS, src_id);

    Heap verts_heap = heap_new(verts, NUM_VERTS);

    while (heap_size(&verts_heap) > 0) {
        Vertex vertex = heap_extract_min(&verts_heap);
        uint32_t u, v;
        for (u = vertex.id, v = 0; v < NUM_VERTS; ++v) {
            uint32_t w = g.adj[u][v];
            if (w > 0) {
                if (verts[v+1].dist > verts[u+1].dist + w) {
                    verts[v+1].dist = verts[u+1].dist + w;
                    verts[v+1].pred = u;
                }
            }
        }
    }
    
    heap_delete(&verts_heap);

    return NUM_VERTS;
}
