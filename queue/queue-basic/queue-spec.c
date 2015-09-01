#include <assert.h>
#include "queue.h"

void test_one_element_queue()
{
    Queue q = queue_new(1);
    QueueResult res;

    assert(queue_empty(&q));
    assert(!queue_full(&q));

    queue_add(&q, 100, &res);
    assert(res.status == QUEUE_OK);

    assert(!queue_empty(&q));
    assert(queue_full(&q));

    queue_add(&q, 100, &res);
    assert(res.status == QUEUE_FULL);

    queue_remove(&q, &res);
    assert(res.status == QUEUE_OK);

    assert(queue_empty(&q));
    assert(!queue_full(&q));
}

void test_two_element_queue()
{
    Queue q = queue_new(2);
    QueueResult res;

    assert(queue_empty(&q));
    assert(!queue_full(&q));

    queue_add(&q, 100, &res);
    assert(res.status == QUEUE_OK);
    assert(!queue_empty(&q));
    assert(!queue_full(&q));

    queue_add(&q, 200, &res);
    assert(res.status == QUEUE_OK);
    assert(!queue_empty(&q));
    assert(queue_full(&q));

    queue_add(&q, 300, &res);
    assert(res.status == QUEUE_FULL);
    assert(!queue_empty(&q));
    assert(queue_full(&q));

    queue_remove(&q, &res);
    assert(res.data == 100 && res.status == QUEUE_OK);
    assert(!queue_empty(&q));
    assert(!queue_full(&q));

    queue_remove(&q, &res);
    assert(res.data == 200 && res.status == QUEUE_OK);
    assert(queue_empty(&q));
    assert(!queue_full(&q));

    queue_remove(&q, &res);
    assert(res.status == QUEUE_EMPTY);
    assert(queue_empty(&q));
    assert(!queue_full(&q));
}

void test_generic_element_queue()
{
    Queue q = queue_new(0);
    QueueResult res;

    assert(queue_empty(&q));
    assert(!queue_full(&q));

    int32_t i;
    for (i = 0; i < MAX_QUEUE_LEN; ++i) {
        queue_add(&q, i, &res);
        assert(res.status == QUEUE_OK);
    }
    assert(queue_full(&q));

    for (i = 0; i < MAX_QUEUE_LEN; ++i) {
        queue_remove(&q, &res);
        assert(res.data == i && res.status == QUEUE_OK);
    }
    assert(queue_empty(&q));
}

int main()
{
    test_one_element_queue();
    
    test_two_element_queue();
    
    test_generic_element_queue();

    return 0;
}
