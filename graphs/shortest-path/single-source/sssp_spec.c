#include <assert.h>
#include "graph.h"
#include "shortest_path.h"

#include <stdio.h>

static void _print_the_shortest_path_(Vertex verts[], uint32_t len)
{
    int i;

    for (i = 1; i < len; ++i) {
        printf("    id: %d, pred: %0X, dist: %d\n", 
                                    verts[i].id, verts[i].pred, verts[i].dist);
    }
    printf("\n");
}

void test_one()
{
    Graph g = {
       3,
       { {0, 4, 11}, {6, 0, 2}, {3, 0, 0} },
       {"1", "2", "3"},
       5,
    };
    
    Vertex verts[g.vc + 1];

    find_shortest_path(g, 0, verts, (g.vc + 1));
    _print_the_shortest_path_(verts, (g.vc + 1));
}

void test_two()
{
    Graph g = {
       4,
       { {0, 4, 2, 2}, {0, 0, 0, 0, }, {0, 1, 0, 2}, {0, 0, 0, 0} },
       {"1", "2", "3", "4"},
       5,
    };
    Vertex verts[g.vc + 1];

    find_shortest_path(g, 0, verts, (g.vc + 1));
    _print_the_shortest_path_(verts, (g.vc + 1));
}

int main()
{
    test_one();
    test_two();

    return 0;
}