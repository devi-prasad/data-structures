#include <stdio.h>
#include "graph.h"
#include "dfs.h"
#include "assert.h"

void printer(Vertex v)
{
    printf("    visited: (%d, %s)\n", v.id, v.label);
}

void test_three_vertex_graph()
{
    Graph g = {3, {{0, 1, 0}, {1, 0, 1}, {0, 1, 0} }, {"a", "b", "c"} };
    
    graph_dfs(g, printer);
}

/*
 *   0 -- 1 -- 2 -
 *    -   | -  |   -5
 *      - |  - | -
 *       -3   -4
 */
void test_six_vertex_graph()
{
    Graph g = {
        6,
        { {0, 1, 0, 1, 0, 0, }, 
          {1, 0, 1, 1, 1, 0, },
          {0, 1, 0, 0, 1, 1, },
          {1, 1, 0, 0, 0, 0, },
          {0, 1, 1, 0, 0, 1, },
          {0, 0, 1, 0, 1, 0, }
        },
        {"a", "b", "c", "d", "e", "f"},
    };
  
    graph_dfs(g, printer);
}

void test_six_vertex_complete_graph()
{
    Graph g = {
        6,
        { {0, 1, 1, 1, 1, 1, }, 
          {1, 0, 1, 1, 1, 1, },
          {1, 1, 0, 1, 1, 1, },
          {1, 1, 1, 0, 1, 1, },
          {1, 1, 1, 1, 0, 1, },
          {1, 1, 1, 1, 1, 0, }
        },
        {"a", "b", "c", "d", "e", "f"},
    };
  
    graph_dfs(g, printer);
}

void test_generic_graph()
{
    Graph g = {
      8,
      { {0, 1, 0, 0, 1, 1, 0, 0}, 
        {1, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0}
      },
      {"a", "b", "c", "d", "e", "f", "g", "h"},
    };

    graph_dfs(g, printer);   
}

int main()
{
    test_three_vertex_graph();
    printf("\n\n");
    test_six_vertex_graph();
    printf("\n\n");
    test_six_vertex_complete_graph();
    printf("\n\n");
    test_generic_graph();

    return 0;
}
