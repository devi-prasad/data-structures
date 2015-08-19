#include "graph.h"
#include <assert.h>

/* 
 * A "Walk" is a sequence of vertices visited in arbitrary manner.
 * returns 0 if an attempt is made to walk across a non-existing edge.
 * returna 1 otherwise
 */

int isa_walk(const Graph g, const Walk w)
{
    assert(w.len > 0);
    assert(w.len <=  MAX_WALK_LEN);
    assert(g.vc <= MAX_VERTS);

    uint8_t u, v;
    int i;
    
    for (i = 0; i < w.len; ++i) {
    	u = w.visits[i];
    	v = w.visits[i+1];
    	assert(u < g.vc);
    	assert(v < g.vc);
        /* assert(IS_AN_EDGE(g.adj[u][v])); */

        if (NOT_AN_EDGE(g.adj[u][v])) return 0;
    }

    return 1;
}

/*
 * A Trail is a Walk with distinct edges.
 * returns 1 if a sequence of vertices represent a Trail.
 * returns 0 otherwise. 
 */
int isa_trail(Graph g, const Walk w)
{
    int res = 0;

    if (isa_walk(g, w)) {
        uint8_t u, v;
        int i;

        for (i = 0; i < w.len; ++i) {
            u = w.visits[i];
            v = w.visits[i+1];
            if (VISITED_EDGE(g.adj[u][v])) break;
            g.adj[u][v] = MARK_VISITED_EDGE(g.adj[u][v]);
            g.adj[v][u] = MARK_VISITED_EDGE(g.adj[v][u]);
        }
        res = (i == w.len);
    }

    return res;
}

/*
 * A Path is a Trail with distinct vertices.
 * returns 1 if a sequence of vertices represent a Path.
 * returns 0 otherwise.
 */
int isa_path(const Graph g, const Walk w)
{
    int res = 0;
    if (isa_trail(g, w)) {
        uint8_t u;
        int i;
        uint8_t vert_state[MAX_VERTS] = {1};

        u = w.visits[0];
        vert_state[u] = MARK_VISITED_VERTEX(vert_state[u]);
        for (i = 1; i < w.len; ++i) {
            u = w.visits[i];
            if (VISITED_VERTEX(vert_state[u])) break;
            vert_state[u] = MARK_VISITED_VERTEX(vert_state[u]);
        }
        res = (i == w.len);
    }

    return res;
}

