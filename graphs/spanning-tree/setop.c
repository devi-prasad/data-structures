#include <assert.h>
#include "kruskal.h"

/*
 * makes a set from a vertex number 'v'.
 * Only v-th bit of the returned set will be turned on.
 */
set_t set_make(uint8_t v)
{
	assert(v < MAX_VERTS && MAX_VERTS < 16);

    set_t setv = (1 << v);
    return setv;
}

/*
 * Fast set union. Returns bit-wise 'and' of two sets.
 */
set_t set_union(set_t u, set_t v)
{
	//assert((u & v) == 0);

    return (u | v);
}

/*
 * 'sets' is a collection. 'nsets' is the number of sets in this collection.
 * 'v' represents the element/set whose membership is being tested.
 * returns the index of the set that contains 'v' in 'sets'.
 *
 */
set_t set_find(set_t sets[], uint8_t nsets, uint8_t v)
{
    assert(nsets > 0);

    set_t setv = set_make(v);
    uint16_t i;
    for (i = 0; i < nsets; ++i) {
        if ((setv & sets[i]) == setv) break;
    }

    return i;
}

/*
 * checks if set 'a' is contained in 'b'
 */
int set_subset(set_t a, set_t b)
{
    return ((a & b) == a);
}



