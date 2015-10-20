#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "heap.h"

/*
 * A min-heap implementation. 
 * Specialized for use within Dijkstra's single-source shortest path algorithm.
 */

static void _heapify_(Vertex verts[], uint32_t len, uint32_t i)
{
    assert(/*len > 0 && */len < MAX_HEAP_SIZE && i > 0);

    if (len == 0) return;
    int32_t l = LEFT(i), r = RIGHT(i);
    uint32_t minimum = i;

    if (l <= len && verts[l].dist < verts[i].dist)
        minimum = l;
    if (r <= len && verts[r].dist < verts[minimum].dist)
        minimum = r;

    if (minimum != i) {
        Vertex temp = verts[i];
        verts[i] = verts[minimum];
        verts[minimum] = temp;

        _heapify_(verts, len, minimum);
    }
}

uint32_t heap_size(Heap *heap)
{
    assert(heap->size >= 0 && heap->size < MAX_HEAP_SIZE);
    assert(heap_check_good(heap));

    return heap->size;
}

static inline void _heap_set_good_(Heap *heap)
{
    heap->data[0].id = HEAP_GOOD_MAGIC_SIG; 
}

static inline void _heap_set_bad_(Heap *heap)
{
    heap->data[0].id = HEAP_BAD_MAGIC_SIG;
}

inline int32_t  heap_check_valid(Heap *heap)
{
    return (heap_check_good(heap) || heap_check_bad(heap));
}

inline int32_t heap_check_good(Heap *heap)
{
    return (heap->data[0].id == HEAP_GOOD_MAGIC_SIG);
}

inline int32_t heap_check_bad(Heap *heap)
{
    return (heap->data[0].id == HEAP_BAD_MAGIC_SIG);
}


Heap heap_new(Vertex data[], uint32_t len)
{
    Heap heap;
    int32_t i;

    assert(len > 0 && len < MAX_HEAP_SIZE);

    //memset(heap.data, 0, MAX_HEAP_SIZE * sizeof(Vertex));
    
    for (i = len/2; i > 0; --i) {
        _heapify_(data, len, i);
    }
    heap.size = len;
    //memcpy(heap.data, data, (len+1) * sizeof(Vertex));
    heap.data = data;
    _heap_set_good_(&heap);

    return heap;
}

Heap* heap_sort(Heap *heap)
{
    assert(heap->size > 0 && heap->size < MAX_HEAP_SIZE);
    assert(heap_check_good(heap));

	int32_t len = heap->size;
	Vertex *data = heap->data;

    while (len > 1) {
        _heapify_(++data, --len, 1);
    }
    
    _heap_set_bad_(heap);
    return heap;
}

Vertex heap_get_min(Heap *heap)
{
    assert(heap->size > 0 && heap->size < MAX_HEAP_SIZE);
    assert(heap_check_valid(heap));

    return heap->data[1];
}

/*
 * precondition: heap_size(heap) must be > 0
 * otherwise, the heap will reach a bad state.
 *
 */
Vertex heap_extract_min(Heap *heap)
{
    assert(heap->size > 0 && heap->size < MAX_HEAP_SIZE);
    assert(heap_check_good(heap));

    Vertex min = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->data[heap->size] = min;
    --heap->size;
    _heapify_(heap->data, heap->size, 1);
    
    assert(heap_check_good(heap));
    return min;
}

Heap* heap_insert(Heap *heap, Vertex vertex)
{
    assert(heap->size > 0 && (heap->size + 1) < MAX_HEAP_SIZE);
    assert(heap_check_good(heap));

    ++heap->size;
    uint32_t i = heap->size;

    /* heap->data[ PARENT(i) ] > key */
    while (i > 1 && heap->data[PARENT(i)].dist > vertex.dist) {
        heap->data[i] = heap->data[PARENT(i)];
        i = PARENT(i);
    }
    heap->data[i] = vertex;
    
    assert(heap_check_good(heap));
    return heap;
}

void heap_delete(Heap *heap)
{
    assert(heap_check_valid(heap));
    memset(heap->data, 0, heap->size * sizeof(Vertex));
    heap->size = 0;
    _heap_set_bad_(heap);
}
