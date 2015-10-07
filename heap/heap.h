#ifndef _INCLUDED_HEAP_
#define _INCLUDED_HEAP_

#include <stdint.h>

#define PARENT(i) (i/2)
#define LEFT(i)   (i << 1)
#define RIGHT(i)  ((i << 1) | 0x1)

/* we will use one word to store heap's state */
#define MAX_HEAP_SIZE (16 + 1)

struct _heap_ {
    uint32_t size;
    int32_t  data[MAX_HEAP_SIZE];
};

typedef struct _heap_ Heap;

#define  HEAP_GOOD_MAGIC_SIG 0xBEADCAFE
#define  HEAP_BAD_MAGIC_SIG  0xDEADBEEF

inline void     heap_set_good(Heap *heap);
inline void     heap_set_bad(Heap *heap);
inline int32_t  heap_check_good(Heap *heap);
inline int32_t  heap_check_bad(Heap *heap);
inline int32_t  heap_check_valid(Heap *heap);

Heap     heap_new(int32_t data[], uint32_t len);
void     heap_delete(Heap *heap);
Heap*    heap_sort(Heap *heap);
Heap*    heap_insert(Heap *heap, int32_t key);
int32_t  heap_get_max(Heap *heap);
int32_t  heap_extract_max(Heap *heap);
uint32_t heap_size(Heap *heap);

#endif
