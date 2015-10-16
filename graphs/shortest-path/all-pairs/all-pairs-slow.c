#include <stdint.h>
#include <assert.h>
#include "all-pairs-slow.h"

int32_t MIN(dist_t x, dist_t y)
{
    if (x == INFINITE) return y;
    if (y == INFINITE) return x;

    return (x <= y ? x : y);
}

int32_t ADD(dist_t d, dist_t w)
{
    if (d == INFINITE || w == INFINITE) return INFINITE;

    return d + w;
}

static Graph _extend_shortest_paths_(const Graph D, const Graph W)
{
    const int32_t NUM_VERTS = W.vc;
    int32_t i, j, k;
    Graph D_DASH  = D;

    for (i = 0; i < NUM_VERTS; ++i) {
        for (j = 0; j < NUM_VERTS; ++j) {
            D_DASH.adj[i][j] = INFINITE;
            for (k = 0; k < NUM_VERTS; ++k) {
                D_DASH.adj[i][j] = MIN(D_DASH.adj[i][j], ADD (D.adj[i][k],  W.adj[k][j]) );
            }
        }
    }

    return D_DASH;
}

static Graph _compute_all_pairs_shortest_paths_(Graph D, const Graph W)
{
    const int32_t NUM_VERTS = W.vc;
    int32_t m;

    for (m = 1; m < NUM_VERTS - 1; ++m) {
        D = _extend_shortest_paths_(D, W);

        /*printf("\n");
        int i, j;
        for (i = 0; i < NUM_VERTS; ++i) {
            for (j = 0; j < NUM_VERTS; ++j) {
                printf(" %d ", D.adj[i][j]);
            }
            printf("\n");
        }
        printf("\n");*/
    }

    return D;
}

Graph all_pairs_shortest_paths_slow(const Graph w)
{
    Graph d = _compute_all_pairs_shortest_paths_(w, w);

    return d;
}