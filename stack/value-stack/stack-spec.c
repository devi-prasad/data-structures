#include <assert.h>
#include "stack.h"

void test_capacity_one_stack()
{
    Stack stk = stack_new(1);
    StackResult result;

    assert(stack_empty(stk));
    assert(!stack_full(stk));

    stack_peek(stk, &result);
    assert(result.status == STACK_EMPTY);
    stack_pop(stk, &result);
    assert(result.status == STACK_EMPTY);

    stk = stack_push(stk, 99, &result);
    assert(result.status == STACK_OK);
    assert(stack_full(stk));

    stk = stack_push(stk, 222, &result);
    assert(result.status == STACK_FULL);
    stack_peek(stk, &result);
    assert(result.data == 99 && result.status == STACK_OK);

    stk = stack_pop(stk, &result);
    assert(result.data == 99 && result.status == STACK_OK);
    assert(stack_empty(stk));
}

void test_arbitrary_stack()
{
    Stack stk = stack_new(0);
    StackResult result = { 0, RESULT_INVALID };
    int i;

    for (i = 0; i < MAX_DEPTH; i++) {
        stk = stack_push(stk, i, &result);
        assert(result.status == STACK_OK);
        result.status = RESULT_INVALID;
    }
    
    stack_push(stk, i, &result);
    assert(result.status == STACK_FULL);

    for (i = 0; i < MAX_DEPTH; i++) {
    	result.status = 0;
        stack_peek(stk, &result);
        assert(result.status == STACK_OK);
        assert(result.data == MAX_DEPTH - i - 1);

        result.status = RESULT_INVALID;
        stk = stack_pop(stk, &result);
        assert(result.status == STACK_OK);
    }
    assert(stack_empty(stk));
}

int main()
{
    test_capacity_one_stack();

    test_arbitrary_stack();

    return 0;
}
