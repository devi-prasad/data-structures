#include <assert.h>
#include <stddef.h>
#include "queue.h"

Queue  queue_new(uint32_t size)
{
	size = (size > 0 && size < MAX_QUEUE_LEN) ? size : MAX_QUEUE_LEN;
	
    Queue q = {size, /*count*/ 0, /*head*/0, /*tail*/0, /*data*/{0} };
    
    return q;
}

Queue* queue_add(Queue *q, int32_t data, QueueResult *result)
{
	assert(q != NULL && q->count <= q->size);

    if (q->count < q->size) {
        q->q[q->tail] = data;
        q->tail = (q->tail + 1) % q->size;
        ++q->count;
        result->status = QUEUE_OK;
    } else {
        result->status = QUEUE_FULL;
    }

    assert(result->status == QUEUE_OK || q->count == q->size);
    return q;
}

Queue* queue_remove(Queue *q, QueueResult *result)
{
	assert(q != NULL && q->count <= q->size);

    if (q->count > 0) {
        result->data = q->q[q->head];
        q->head = (q->head + 1) % q->size;
        --q->count;
        result->status = QUEUE_OK;
    } else {
        result->status = QUEUE_EMPTY;
    }

    assert(q->count < q->size);
    assert(result->status == QUEUE_OK || q->count == 0);

    return q;
}

uint32_t queue_full(Queue *q)
{
	assert(q != NULL && q->count <= q->size);
    return (q->count == q->size);
}

uint32_t queue_empty(Queue *q)
{
    return (q->count == 0);
}
