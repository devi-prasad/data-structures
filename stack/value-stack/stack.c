#include <assert.h>
#include "stack.h"

/*
 * Efficiency of implementation is not our concern here.
 * We deal with small-size stack data structure.
 * Stack objects are passed to functions and returned from functions as values.
 * The result of an operation that effects stack's state is communicated using
 *  call by address Result references.
 *
 */
Stack stack_new(uint32_t size)
{
	size = (size > 0 && size < MAX_DEPTH) ? size : MAX_DEPTH;
	Stack s = {size, -1, {0}};

	return s;
}

uint32_t stack_full(Stack stk)
{
    return ((stk.top + 1) == stk.size);
}

uint32_t stack_empty(Stack stk)
{
    return stk.top == -1;
}

Stack stack_push(Stack  stk, int32_t data, StackResult *result)
{
    if (stk.top + 1 < stk.size) {
        stk.data[++stk.top] = data;
        result->data = data;
        result->status = STACK_OK;
    } else {
        result->data = data;
        result->status = STACK_FULL;
    }

    return stk;
}

Stack stack_pop(Stack  stk, StackResult *result)
{
    if (stk.top > -1) {
        result->data = stk.data[stk.top];
        result->status = STACK_OK;
        --stk.top;
    } else {
        result->status = STACK_EMPTY;
    }

    return stk;
}

Stack stack_peek(Stack  stk, StackResult *result)
{
    if (stk.top > -1) {
        result->data = stk.data[stk.top];
        result->status = STACK_OK;
    } else {
        result->status = STACK_EMPTY;
    }

    return stk;
}
