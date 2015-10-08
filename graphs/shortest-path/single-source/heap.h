#ifndef _INCLUDED_HEAP_
#define _INCLUDED_HEAP_

#include <stdint.h>
#include "vertex.h"

#define PARENT(i) (i/2)
#define LEFT(i)   (i << 1)
#define RIGHT(i)  ((i << 1) | 0x1)

/* we will use one word to store heap's state */
#define MAX_HEAP_SIZE (16 + 1)


struct _heap_ {
    uint32_t size;
    Vertex data[MAX_HEAP_SIZE];
};

typedef struct _heap_ Heap;

#define  HEAP_GOOD_MAGIC_SIG 0xBEADCAFE
#define  HEAP_BAD_MAGIC_SIG  0xDEADBEEF

inline int32_t  heap_check_good(Heap *heap);
inline int32_t  heap_check_bad(Heap *heap);
inline int32_t  heap_check_valid(Heap *heap);

Heap     heap_new(Vertex verts[], uint32_t len);
void     heap_delete(Heap *heap);
Heap*    heap_sort(Heap *heap);
Heap*    heap_insert(Heap *heap, Vertex key);
Vertex   heap_get_min(Heap *heap);
Vertex   heap_extract_min(Heap *heap);
uint32_t heap_size(Heap *heap);

#endif
