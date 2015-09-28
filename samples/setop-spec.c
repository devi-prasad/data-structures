#include <stdint.h>
#include <assert.h>
#include "graph.h"

typedef uint16_t set_t;

uint16_t set_make(uint8_t v);
uint16_t set_union(uint16_t u, uint16_t v);
int set_member(set_t a, set_t b);
uint16_t set_find(set_t sets[], uint8_t nsets, uint8_t v);

void test_make_set()
{
	assert(set_make(0) & 0X01);
	assert(set_make(1) & 0X02);
    assert(set_make(3) & 0X08);
    assert(set_make(11) & 0X0800);
}

void test_set_find()
{
    set_t sets[MAX_VERTS] = {0};

    sets[0] = set_make(0);
    sets[1] = set_make(1);
    sets[2] = set_make(2);
    sets[3] = set_make(3);
    sets[8] = set_make(8);
    sets[10] = set_make(10);
    sets[11] = set_make(11);

    assert(set_find(sets, MAX_VERTS, 8) == 8);
    assert(set_find(sets, MAX_VERTS, 3) == 3);
    assert(set_find(sets, MAX_VERTS, 2) == 2);
    assert(set_find(sets, MAX_VERTS, 1) == 1);
    assert(set_find(sets, MAX_VERTS, 0) == 0);
    
    sets[3] =  set_union(sets[3], set_union(sets[2], sets[10]));
    assert(set_find(sets, MAX_VERTS, 10) == 3);
    assert(set_member(sets[2], sets[3]));
    assert(set_find(sets, MAX_VERTS, 3) == 3);

    sets[2] =  set_union(sets[2], sets[10]);
    assert(set_find(sets, MAX_VERTS, 10) == 2);
    assert(set_find(sets, MAX_VERTS, 2) == 2);
}

int main()
{
    test_make_set();
    test_set_find();
    return 0;
}