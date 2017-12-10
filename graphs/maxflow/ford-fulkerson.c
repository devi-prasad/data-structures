
/**
 * Compile this code in Linux using the following command
 *     cc -Wall -std=c99 ford-fulkerson.c queue.c
 * or simply run 'make' ij in the current directory.
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "queue.h"

typedef int32_t vertex_t;
struct flow_and_capacity {
    int32_t capacity;
    int32_t residual_capacity;
    int32_t flow;
};

void graph_bfs(const int32_t nverts,
               struct flow_and_capacity net[][nverts],
               vertex_t parents[])
{
    Queue queue = queue_new(0);
    Queue *q = &queue;
    QueueResult res;

    uint32_t visited[nverts];
    memset(visited, 0, sizeof(visited));

    queue_add(q, 0, &res);

    while (!queue_empty(q)) {
        queue_remove(q, &res);
        assert(res.status == QUEUE_OK);

        vertex_t u = res.data;
        if (visited[u] == 0) {
            visited[u] = 1;

            printf("Path Augmentation - parent[%d]=%d\n", u, parents[u]);
            if (u == nverts -1) break;

            /* push each neighbors of vertex u on the stack */
            for (int32_t w = 0; w < nverts; ++w) {
                if (w != u && net[u][w].residual_capacity > 0) {
                    queue_add(q, w, &res);
                    parents[w] = u;
                    assert(res.status == QUEUE_OK);
                }
            }
        }
    }
}


void flownet_init(const int32_t nverts, struct flow_and_capacity net[][nverts])
{
    for (vertex_t i = 0; i < nverts; ++i) {
        for (vertex_t j = 0; j < nverts; ++j) {
            net[i][j].capacity = -1;
            net[i][j].residual_capacity = 0;
            net[i][j].flow = 0;
        }
    }
}

int32_t max_capacity_in_net = 0;
void flownet_set_capacity(const int32_t nverts,
                          struct flow_and_capacity net[][nverts],
                          vertex_t src, vertex_t dest, int32_t capacity)
{
    assert(src >= 0 && src < (nverts - 1) && dest > 0 && dest < nverts);
    assert(net[src][dest].capacity == -1);
    assert(net[dest][src].capacity == -1);
    assert(capacity > 0);

    net[src][dest].capacity = capacity;
    if (max_capacity_in_net < capacity) {
        max_capacity_in_net = capacity;
    }
}

void flownet_show(const char *title,
                  const int32_t nverts,
                  const struct flow_and_capacity net[][nverts])
{
    printf("\n\n");
    printf("%s\n", title);
    for (vertex_t i = 0; i < nverts; ++i) {
        for (vertex_t j = 0; j < nverts; ++j) {
            if (net[i][j].capacity == -1) printf("(%2d, %2d, %2d)   ", 0, 0, 0);
            else printf("(%2d, %2d, %2d)   ", net[i][j].capacity,
                                            net[i][j].flow,
                                            net[i][j].residual_capacity);
        }
        printf("\n");
    }
    printf("\n\n");
}


void compute_maxflow_ford_fulkerson(const int32_t nverts,
                                    struct flow_and_capacity net[][nverts])
{
    struct flow_and_capacity residual_net[nverts][nverts];

    while (1) {
        memset(residual_net, 0, sizeof(residual_net));
        for (vertex_t i = 0; i < nverts; ++i) {
            for (vertex_t j = 0; j < nverts; ++j) {
                residual_net[i][j].capacity = net[i][j].capacity;
                residual_net[i][j].flow = net[i][j].flow;
                if (net[i][j].capacity > 0) {
                    int32_t cf = net[i][j].capacity - net[i][j].flow;
                    residual_net[i][j].residual_capacity = cf;
                } else if (net[j][i].capacity > 0) {
                    residual_net[i][j].residual_capacity = net[j][i].flow;
                } else {
                    residual_net[i][j].capacity = -1;
                }
            }
        }

        flownet_show("Residual Net - Before Running the Next Iteration",
                     nverts, residual_net);

        vertex_t path[nverts];
        memset(path, -1, sizeof(path));

        graph_bfs(nverts, residual_net, path);

        if (path[nverts - 1] == -1) {
            printf("**No Augmenting Path! Returning**");
            break;
        }

        int32_t min_possible_flow = max_capacity_in_net + 1;
        for (vertex_t v = nverts - 1, u = 0; v != 0; v = u) {
            u = path[v];
            printf("edge (u, v) = (%d, %d)\n", u, v);
            if (residual_net[u][v].residual_capacity < min_possible_flow) {
                min_possible_flow = residual_net[u][v].residual_capacity;
            }
        }
        printf("min flow for augmentation = %d\n", min_possible_flow);
        
        if (min_possible_flow < max_capacity_in_net + 1) {
            for (vertex_t v = nverts - 1, u = 0; v != 0; v = u) {
                u = path[v];
                residual_net[u][v].flow += min_possible_flow;
                net[u][v].flow += min_possible_flow;
            }
        }

        flownet_show("Updated Residual Net", nverts, residual_net);
    }
}

void test_simple_flownet()
{
    const int32_t nverts = 5;
    struct flow_and_capacity network[nverts][nverts];

    flownet_init(nverts, network);
    flownet_set_capacity(nverts, network, 0, 1, 10);
    flownet_set_capacity(nverts, network, 1, 2, 10);
    flownet_set_capacity(nverts, network, 2, 3, 8);
    flownet_set_capacity(nverts, network, 3, 4, 20);

    flownet_show("The Initial/Input Flow Network", nverts, network);
    compute_maxflow_ford_fulkerson(nverts, network);
    flownet_show("The Resulting Max Flow in the Network", nverts, network);
}

void test_second_flownet()
{
    const int32_t nverts = 6;
    struct flow_and_capacity network[nverts][nverts];

    flownet_init(nverts, network);
    flownet_set_capacity(nverts, network, 0, 1, 10);
    flownet_set_capacity(nverts, network, 1, 2, 10);
    flownet_set_capacity(nverts, network, 2, 5, 8);
    flownet_set_capacity(nverts, network, 0, 3, 20);
    flownet_set_capacity(nverts, network, 3, 4, 6);
    flownet_set_capacity(nverts, network, 4, 5, 20);

    flownet_show("The Initial/Input Flow Network", nverts, network);
    compute_maxflow_ford_fulkerson(nverts, network);
    flownet_show("The Resulting Max Flow in the Network", nverts, network);
}

int main()
{
    test_simple_flownet();
    test_second_flownet();

    return 0;
}
