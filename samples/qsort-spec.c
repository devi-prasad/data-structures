#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef int (Comparator)(const void *, const void *);

struct _edge_ {
    uint8_t u;
    uint8_t v;
    uint8_t weight;
};

typedef struct _edge_ Edge;

int compare_edges(const void *p, const void *q)
{
	const Edge *e1 = p;
	const Edge *e2 = q;

    if (e1->weight < e2->weight) return -1;
    else if (e1->weight > e2->weight) return 1;
    return 0;
}

int main()
{
    Edge edges[] = {
        {0, 1, 8}, {0, 3, 4}, 
        {1, 2, 1}, {2, 3, 10},
        {3, 4, 3}, {2, 4, 5},
    };

    qsort(edges, 6, sizeof(Edge), compare_edges);
    
    int i;
    for (i = 0; i < 5; ++i) {
        printf(" %d ", edges[i].weight);
        assert(edges[i].weight <= edges[i+1].weight);
    }
    printf("\n");

    return 0;
}
