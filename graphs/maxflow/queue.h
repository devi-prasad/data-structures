#ifndef INCLUDED_QUEUE
#define INCLUDED_QUEUE

#include <stdint.h>

#define MAX_QUEUE_LEN 32

struct _queue_ {
    uint32_t size;                /* actual size */
    uint32_t count;               /* occupied */
    uint32_t head;                /* removing end */
    uint32_t tail;                /* add new items here */
    int32_t  q[MAX_QUEUE_LEN];    /* queue data */
};
typedef struct _queue_ Queue;

struct _queue_result_ {
    int32_t data;
    uint32_t status;
};
typedef struct _queue_result_ QueueResult;


#define QUEUE_OK     1
#define QUEUE_FULL   2
#define QUEUE_EMPTY  4

Queue    queue_new(uint32_t size);
Queue*   queue_add(Queue *q, int32_t data, QueueResult *result);
Queue*   queue_remove(Queue *q, QueueResult *result);
uint32_t queue_full(Queue *q);
uint32_t queue_empty(Queue *q);

#endif
