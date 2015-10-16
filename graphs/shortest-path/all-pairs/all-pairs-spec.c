#include <assert.h>
#include "all-pairs-slow.h"

static void _display_graph_(Graph d)
{
	int32_t i, j;

    printf("\n");
	for (i = 0; i < d.vc; ++i) {
	    for (j = 0; j < d.vc; ++j) {
	        printf(" %d ", d.adj[i][j]);
	    }
	    printf("\n");
	}
}

void test_a_five_vertex_graph()
{
    Graph g = {
       5,
       { {0, 3, 8, INFINITE, -4},
         {INFINITE, 0, INFINITE, 1, 7},
         {INFINITE, 4, 0, INFINITE, INFINITE},
         {2, INFINITE, -5, 0, INFINITE},
         {INFINITE, INFINITE, INFINITE, 6, 0} },
    };

    Graph d = all_pairs_shortest_paths_slow(g);
    assert(d.vc == g.vc);

    _display_graph_(d);
}

void test_a_sample()
{
    Graph g = {
       3,
       {{0, 4, 11}, {6, 0, 2}, {3, INFINITE, 0} },
    };

    Graph d = all_pairs_shortest_paths_slow(g);
    assert(d.vc == g.vc);
    _display_graph_(d);
}

int main()
{
    test_a_sample();
    test_a_five_vertex_graph();

    return 0;
}