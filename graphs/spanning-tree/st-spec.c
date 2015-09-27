#include <assert.h>
#include "prim.h"
#include "kruskal.h"

#include <stdio.h>
static void _print_adj_matrix_(const Graph *g)
{
    int i, j;
    
    printf("\n\n");
    for (i = 0; i < g->vc; i++) {
        for (j = 0; j < g->vc; j++) {
        	printf(" %d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

/*     
 *        1        2
 *   (0)-----(1)------(2) -
 *    -       | -      |   - 1
 *     -      |  - 4   |     -
 *      -    3|   -    |3     - (5)
 *     2  -   |    -   |     -
 *         -  |     -  |   - 2
 *          -(3)     -(4) -
 */
void test_6verts_graph_prim()
{
    Graph g = {
        6,
        { {0, 1, 0, 2, 0, 0, }, 
          {1, 0, 2, 3, 4, 0, },
          {0, 2, 0, 0, 3, 1, },
          {2, 3, 0, 0, 0, 0, },
          {0, 4, 3, 0, 0, 2, },
          {0, 0, 1, 0, 2, 0, }
        },
        {"a", "b", "c", "d", "e", "f"},
        8
    };

    spanning_tree_prim(&g, 0, &g);
    _print_adj_matrix_(&g);
}

void test_6verts_graph_kruskal()
{
    Graph g = {
        6,
        { {0, 1, 0, 2, 0, 0, }, 
          {1, 0, 2, 3, 4, 0, },
          {0, 2, 0, 0, 3, 1, },
          {2, 3, 0, 0, 0, 0, },
          {0, 4, 3, 0, 0, 2, },
          {0, 0, 1, 0, 2, 0, }
        },
        {"a", "b", "c", "d", "e", "f"},
        8
    };

    spanning_tree_kruskal(&g, &g);
    _print_adj_matrix_(&g);
}

void test_another_6verts_graph_prim()
{
    Graph g = {
        6,
        { {0, 2, 3, 0, 0, 0, }, 
          {2, 0, 6, 5, 3, 0, },
          {3, 6, 0, 0, 2, 0, },
          {0, 5, 0, 0, 1, 2, },
          {0, 3, 2, 1, 0, 4, },
          {0, 0, 0, 2, 4, 0, }
        },
        {"a", "b", "c", "d", "e", "f"},
        9
    };

    spanning_tree_prim(&g, 0, &g);
    _print_adj_matrix_(&g);
}

void test_another_6verts_graph_kruskal()
{
    Graph g = {
        6,
        { {0, 2, 3, 0, 0, 0, }, 
          {2, 0, 6, 5, 3, 0, },
          {3, 6, 0, 0, 2, 0, },
          {0, 5, 0, 0, 1, 2, },
          {0, 3, 2, 1, 0, 4, },
          {0, 0, 0, 2, 4, 0, }
        },
        {"a", "b", "c", "d", "e", "f"},
        9
    };

    spanning_tree_kruskal(&g, &g);
    _print_adj_matrix_(&g);
}

int main()
{
    test_6verts_graph_prim();
    test_6verts_graph_kruskal();
    test_another_6verts_graph_prim();
    test_another_6verts_graph_kruskal();
    
    return 0;
}
