
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

typedef int32_t vertex_t;

void flownet_init(const int32_t nverts, int32_t net[][nverts])
{
	for (int32_t i = 0; i < nverts; ++i) {
		for (int32_t j = 0; j < nverts; ++j) {
			net[i][j] = 0;
		}
	}
}

void flownet_set_capacity(const int32_t nverts, int32_t net[][nverts],
	                      vertex_t src, vertex_t dest, int32_t capacity)
{
    assert(src >= 0 && src < (nverts - 1) && dest > 0 && dest < nverts);
    assert(net[src][dest] == 0);
    assert(net[dest][src] == 0);
    assert(capacity > 0);

    net[src][dest] = capacity;
}

void flownet_show(const int32_t nverts, const int32_t net[][nverts])
{
	for (int32_t i = 0; i < nverts; ++i) {
		for (int32_t j = 0; j < nverts; ++j) {
			printf("%5d", net[i][j]);
		}
		printf("\n");
	}
}

void test_simple_net()
{
	const int32_t nverts = 4;
    int32_t network[nverts][nverts];

    flownet_init(nverts, network);
    flownet_set_capacity(nverts, network, 0, 1, 10);
    flownet_set_capacity(nverts, network, 1, 2, 5);
    flownet_set_capacity(nverts, network, 2, 3, 20);

    flownet_show(nverts, network);
}

int main()
{
    test_simple_net();

    return 0;
}