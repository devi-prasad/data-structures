#include <assert.h>
#include "graph.h"
#include "shortest_path.h"

#include <stdio.h>

static void _print_the_shortest_path_(Vertex verts[], uint32_t len)
{
    int i;

    for (i = 0; i < len; ++i) {
        printf("    id: %d, pred: %0X, dist: %0X\n", 
                                    verts[i].id, verts[i].pred, verts[i].dist);
    }
    printf("\n");
}

void test_one()
{
    Graph g = {
       3,
       { {0, 4, 11}, {6, 0, 2}, {3, DIST_INFINITE, 0} },
    };
    
    Path p = find_shortest_path(g, 2);
    _print_the_shortest_path_(p.verts, p.len);
}

void test_two()
{
    Graph g = {
       4,
       { {0, DIST_INFINITE, DIST_INFINITE, DIST_INFINITE },
         {7, 0, DIST_INFINITE, 2},
         {8, 2, 0, 5}, 
         {3, DIST_INFINITE, DIST_INFINITE, 0} },
    };

    Path p = find_shortest_path(g, 2);
    _print_the_shortest_path_(p.verts, p.len);
}

void test_three()
{
    Graph g = {
       4,
       { {0, 2, 5, 8},
         {DIST_INFINITE, 0, 2, DIST_INFINITE}, 
         {DIST_INFINITE, DIST_INFINITE, DIST_INFINITE, 2},
         {DIST_INFINITE, DIST_INFINITE, DIST_INFINITE, DIST_INFINITE} },
    };
    
    Path p = find_shortest_path(g, 1);
    _print_the_shortest_path_(p.verts, p.len);
}

int main()
{
    test_one();
    test_two();
    test_three();
    return 0;
}