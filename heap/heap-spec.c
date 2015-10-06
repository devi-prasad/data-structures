#include <assert.h>
#include "heap.h"

static void _assert_sorted_(int32_t data[], uint32_t len)
{
	uint32_t i;
    for (i = 1; i < len; i++) {
        assert(data[i] <= data[i+1]);
    }
}

void test_heap_insert()
{
	int32_t data[] = {0, 5, 13, 2, 25, 7, 17, 20, 8, 4};

	Heap heap = heap_new(data, 9);

	assert(heap_size(&heap) == 9);
	assert(heap_get_max(&heap) == 25);

	heap_insert(&heap, 31);
	assert(heap_size(&heap) == 10);
	assert(heap_get_max(&heap) == 31);

    heap_insert(&heap, 31);
    assert(heap_size(&heap) == 11);
    assert(heap_get_max(&heap) == 31);

    assert(heap_extract_max(&heap) == heap_extract_max(&heap));
    assert(heap_size(&heap) == 9);
    assert(heap_get_max(&heap) == 25);
    
    heap_extract_max(&heap);
    assert(heap_extract_max(&heap) == 20);

	heap_delete(&heap);
}

void test_grow_heap()
{
	int32_t data[] = {0, 5}; //, 13, 2, 25, 7, 17, 20, 8, 4};

	Heap heap = heap_new(data, 1);
	assert(heap_size(&heap) == 1);
	assert(heap_get_max(&heap) == 5);

	heap_insert(&heap, 13);
	heap_insert(&heap, 2);
	heap_insert(&heap, 25);
	heap_insert(&heap, 7);

	assert(heap_size(&heap) == 5);
	assert(heap_get_max(&heap) == 25);
}

void test_heap_extract_max()
{
	int32_t data[] = {0, 5, 13, 2, 25, 7, 17, 20, 8, 4};

	Heap heap = heap_new(data, 9);

	assert(heap_size(&heap) == 9);
	assert(heap_get_max(&heap) == 25);
    assert(heap_extract_max(&heap) == 25);

    assert(heap_get_max(&heap) == heap_extract_max(&heap));
    assert(heap_size(&heap) == 7);
    
    assert(heap_extract_max(&heap) == 17);
    assert(heap_size(&heap) == 6);

    heap_delete(&heap);
}

/* CLR - exercise 7.4-1 */
void test_heap_sort()
{
    int32_t data[] = {0, 5, 13, 2, 25, 7, 17, 20, 8, 4};

    Heap heap = heap_new(data, 9);
    assert(heap_get_max(&heap) == 25);

    heap_sort(&heap);
    _assert_sorted_(heap.data, heap.size);

    /* after heap-sort 'heap' is no longer an actual heap! */
    assert(heap_get_max(&heap) == 2);

    heap_delete(&heap);
}

void test_heap_size_three()
{
  {
    int32_t data[] = {0, 2, 10, 7};

    Heap heap = heap_new(data, 3);

    assert(heap_size(&heap) == 3);
    assert(heap.data[0] == 0);
    assert(heap.data[1] == 10);
    assert(heap.data[2] == 2);
    assert(heap.data[3] == 7);
    
    assert(heap_get_max(&heap) == 10);

    heap_sort(&heap);
    _assert_sorted_(heap.data, heap.size);

    heap_delete(&heap);
  }

  {
    int32_t data[] = {0, 2, 7, 10};

    Heap heap = heap_new(data, 3);
    
    assert(heap_size(&heap) == 3);
    assert(heap.data[0] == 0);
    assert(heap.data[1] == 10);
    assert(heap.data[2] == 7);
    assert(heap.data[3] == 2);
    
    heap_sort(&heap);
    _assert_sorted_(heap.data, heap.size);
    heap_delete(&heap);
  }  
}

int main()
{
    test_heap_size_three();
    test_heap_sort();
    test_heap_extract_max();
    test_heap_insert();
    test_grow_heap();
    
    return 0;
}