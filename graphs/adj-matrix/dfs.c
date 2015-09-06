#include <string.h>
#include <assert.h>
#include "graph.h"
#include "dfs.h"
#include "stack.h"

Vertex vertex_new(uint32_t id, const char *label)
{
    Vertex v;

    v.id = id;
    v.parent = 0xFF;   /* unused in this version */
    strncpy(v.label, label, MAX_LABEL_LEN-1);
    v.label[MAX_LABEL_LEN-1] = '\0';

    return v;
}

static void do_graph_dfs(Graph g, Vertex v, Visitor visit)
{
	uint8_t vert_state[MAX_VERTS] = {1};
    StackResult res;
    uint8_t u = v.id, w;

    Stack vstk = stack_new(0);
    stack_push(vstk, u, &res);

    while (!stack_empty(vstk)) {
        stack_pop(vstk, &res);
        assert(res.status == STACK_OK);
        
        u = res.data;
        if (!VISITED_VERTEX(vert_state[u])) {
            vert_state[u] = MARK_VISITED_VERTEX(vert_state[u]);
            
            /* call the function that is interested in the visited vertex */
            visit(vertex_new(u, g.labels[u]));
            
            /* push each neighbors of vertex u on the stack */
            for (w = 0; w < g.vc; ++w) {
            	if (w != u && g.adj[u][w] && !VISITED_VERTEX(vert_state[w])) {
            	    stack_push(vstk, w, &res);
            	    assert(res.status == STACK_OK);
                }
            }
        }
    }
}

void graph_dfs(Graph g, Visitor visit)
{
    Vertex root = vertex_new(g.vc - 1, g.labels[g.vc-1]);
    
    do_graph_dfs(g, root, visit);
}
