#include <string.h>
#include <assert.h>
#include "graph.h"
#include "bfs.h"
#include "queue.h"

Vertex vertex_new(uint8_t id, const char *label, uint8_t parent)
{
    Vertex v;

    v.id = id;
    v.parent = 0xFF;   /* unused in this version */
    strncpy(v.label, label, MAX_LABEL_LEN-1);
    v.label[MAX_LABEL_LEN-1] = '\0';

    return v;
}

static void do_graph_bfs(Graph g, Vertex v, Visitor visit)
{
	uint8_t vert_state[MAX_VERTS] = {1};
    QueueResult res;
    uint8_t u = v.id, w;

    Queue queue = queue_new(0);
    Queue *q = &queue;

    queue_add(q, u, &res);

    while (!queue_empty(q)) {
        queue_remove(q, &res);
        assert(res.status == QUEUE_OK);
        
        u = res.data;
        if (!VISITED_VERTEX(vert_state[u])) {
            vert_state[u] = MARK_VISITED_VERTEX(vert_state[u]);
            
            /* call the function that is interested in the visited vertex */
            visit(vertex_new(u, g.labels[u], 0));
            
            /* push each neighbors of vertex u on the stack */
            for (w = 0; w < g.vc; ++w) {
            	if (w != u && g.adj[u][w]) {
            	    queue_add(q, w, &res);
            	    assert(res.status == QUEUE_OK);
                }
            }
        }
    }
}

void graph_bfs(Graph g, Visitor visit)
{
    Vertex root = vertex_new(0, g.labels[g.vc-1], 0);
    
    do_graph_bfs(g, root, visit);
}
