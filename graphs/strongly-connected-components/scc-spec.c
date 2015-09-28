#include <stdint.h>
#include <assert.h>
#include "graph.h"
#include "scc.h"

#define STACK_CONTENT_TYPE Vertex
#include "stack.h"

void test_2verts_1cycle_scc()
{
	Graph g = {
        2, /* number of vertices */
        {{0, 1}, {1, 0}},
        {"A", "B"},
	};

    int32_t n = find_stronly_connected_components_tarjan(&g);
    assert(n == 1);
}

void test_3verts_1cycle_scc()
{
	Graph g = {
        3,
        {{0, 1, 0}, {0, 0, 1}, {0, 1, 0}},
        {"A", "B", "C"},
	};

    int32_t n = find_stronly_connected_components_tarjan(&g);
    assert(n == 2);
}

void test_3verts_3scc()
{
	Graph g = {
        3,
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {"A", "B", "C"},
	};

    int32_t n = find_stronly_connected_components_tarjan(&g);
    assert(n == 3);
}

void test_3verts_2scc()
{
	Graph g = {
        3,
        {{0, 1, 0}, {0, 0, 1}, {0, 0, 0}},
        {"A", "B", "C"},
	};

    int32_t n = find_stronly_connected_components_tarjan(&g);
    assert(n == 3);
}


int main()
{
	test_2verts_1cycle_scc();
    test_3verts_1cycle_scc();
    test_3verts_3scc();
    test_3verts_2scc();

    return 0;
}