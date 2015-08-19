#include "graph.h"
#include "assert.h"

void test_two_vertex_graph()
{
    Graph g = {3, {{0, 1, 0}, {1, 0, 1}, {0, 1, 0} }, {"a", "b", "c"} };
    //       len, type, visits 
    Walk fw = {2, 0, {1, 0, 2} };
    Walk w  = {2, 0, {0, 1, 2} };
    Walk w2 = {4, 0, {0, 1, 0, 1, 0} };

    assert(!isa_walk(g, fw));
    assert(isa_walk(g, w));
    assert(isa_walk(g, w2));
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
    //       len, type, visits  
    Walk w =  {8, 0, {0, 3, 1, 4, 2, 1, 4, 2, 5} };
    Walk t =  {7, 0, {5, 2, 1, 0, 3, 1, 4, 2} };
    Walk wt = {8, 0, {5, 2, 1, 0, 3, 1, 4, 2, 5} };
    
    Walk p = {5, 0, {5, 2, 4, 1, 3, 0 } };

    assert(isa_walk(g, w));
    
    assert(!isa_trail(g, w));
    assert(isa_trail(g, t));
    assert(isa_trail(g, t));
    assert(!isa_trail(g, wt));

    assert(!isa_path(g, w));
    assert(!isa_path(g, t));
    assert(!isa_path(g, wt));
    assert(isa_path(g, p));
}

int main()
{
    test_two_vertex_graph();
    test_six_vertex_graph();

    return 0;
}













