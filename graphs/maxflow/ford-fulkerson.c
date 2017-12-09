
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef int32_t vertex_t;
struct flow_and_capacity {
    int32_t capacity;
    int32_t residual_capacity;
    int32_t flow;
};

void flownet_init(const int32_t nverts, struct flow_and_capacity net[][nverts])
{
    for (int32_t i = 0; i < nverts; ++i) {
        for (int32_t j = 0; j < nverts; ++j) {
            net[i][j].capacity = -1;
            net[i][j].residual_capacity = 0;
            net[i][j].flow = 0;
        }
    }
}

void flownet_set_capacity(const int32_t nverts,
                          struct flow_and_capacity net[][nverts],
                          vertex_t src, vertex_t dest, int32_t capacity)
{
    assert(src >= 0 && src < (nverts - 1) && dest > 0 && dest < nverts);
    assert(net[src][dest].capacity == -1);
    assert(net[dest][src].capacity == -1);
    assert(capacity > 0);

    net[src][dest].capacity = capacity;
}

void flownet_show(const int32_t nverts,
                  const struct flow_and_capacity net[][nverts])
{
    printf("\n\n");
    for (int32_t i = 0; i < nverts; ++i) {
        for (int32_t j = 0; j < nverts; ++j) {
            if (net[i][j].capacity == -1) printf("(%d, %2d, %2d)    ", 0, 0, 0);
            else printf("(%d, %2d, %2d)    ", net[i][j].capacity,
                                            net[i][j].flow,
                                            net[i][j].residual_capacity);
        }
        printf("\n");
    }
}

void compute_maxflow_ford_fulkerson(const int32_t nverts,
                                    struct flow_and_capacity net[][nverts])
{
    struct flow_and_capacity residual_net[nverts][nverts];

    memset(residual_net, 0, sizeof(residual_net));

    for (int32_t i = 0; i < nverts; ++i) {
        for (int32_t j = 0; j < nverts; ++j) {
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

    flownet_show(nverts, residual_net);
}

void test_simple_net()
{
    const int32_t nverts = 4;
    struct flow_and_capacity network[nverts][nverts];

    flownet_init(nverts, network);
    flownet_set_capacity(nverts, network, 0, 1, 10);
    flownet_set_capacity(nverts, network, 1, 2, 5);
    flownet_set_capacity(nverts, network, 2, 3, 20);

    flownet_show(nverts, network);

    compute_maxflow_ford_fulkerson(nverts, network);
}

int main()
{
    test_simple_net();

    return 0;
}
