#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "heap.h"

static void _heapify_(int32_t data[], uint32_t len, uint32_t i)
{
    assert(len > 0 && len < MAX_HEAP_SIZE && i > 0);

    int32_t l = LEFT(i), r = RIGHT(i);
    uint32_t largest = i;

    if (l <= len && data[l] > data[i])
        largest = l;
    if (r <= len && data[r] > data[largest])
        largest = r;

    if (largest != i) {
        int32_t temp = data[i];
        data[i] = data[largest];
        data[largest] = temp;

        _heapify_(data, len, largest);
    }
}

uint32_t heap_size(Heap *heap)
{
    assert(heap->size > 0 && heap->size < MAX_HEAP_SIZE);

    return heap->size;
}

Heap heap_new(int32_t data[], uint32_t len)
{
    Heap heap;
    int32_t i;

    assert(len > 0 && len < MAX_HEAP_SIZE);
    for (i = len/2; i > 0; --i) {
        _heapify_(data, len, i);
    }
    heap.size = len;
    memcpy(heap.data, data, (len+1) * sizeof(int32_t));

    return heap;
}

Heap* heap_sort(Heap *heap)
{
    assert(heap->size > 0 && heap->size < MAX_HEAP_SIZE);
	int32_t len = heap->size;
	int32_t *data = heap->data;

    while (len > 1) {
    	int32_t temp = data[len]; data[len] = data[1]; data[1] = temp;
        _heapify_(data, --len, 1);
    }

    return heap;
}

int32_t heap_get_max(Heap *heap)
{
    assert(heap->size > 0 && heap->size < MAX_HEAP_SIZE);
    return heap->data[1];
}

int32_t heap_extract_max(Heap *heap)
{
    assert(heap->size > 0 && heap->size < MAX_HEAP_SIZE);
    
    int32_t max = heap->data[1];
    heap->data[1] = heap->data[heap->size - 1];
    --heap->size;
    _heapify_(heap->data, heap->size, 1);

    return max;
}

Heap* heap_insert(Heap *heap, int32_t key)
{
    assert(heap->size > 0 && (heap->size + 1) < MAX_HEAP_SIZE);

    ++heap->size;
    uint32_t i = heap->size;

    while (i > 1 && heap->data[ PARENT(i) ] < key) {
        heap->data[i] = heap->data[PARENT(i)];
        i = PARENT(i);
    }
    heap->data[i] = key;

    return heap;
}

void heap_delete(Heap *heap)
{
    heap->size = 0;
    memset(heap->data, 0, MAX_HEAP_SIZE * sizeof(int32_t));
}
