#ifndef _INCLUDED_STACK_H_
#define _INCLUDED_STACK_H_

#include <stdint.h>

#if STACK_MAX_DEPTH < 32
#undef STACK_MAX_DEPTH
#define STACK_MAX_DEPTH 32
#endif

#ifndef STACK_CONTENT_TYPE
#define STACK_CONTENT_TYPE uint32_t
#endif

struct _stack_ {
    uint32_t size; /* requested stack depth */
    int32_t  top;  /* index of the topmost element */
    STACK_CONTENT_TYPE data[STACK_MAX_DEPTH];  /* actual contents */
};
typedef struct _stack_ *Stack;

/* status bits used in the Result structure */
#define RESULT_INVALID    0
#define STACK_OK          1
#define STACK_FULL        2
#define STACK_EMPTY       4

struct _stack_result_ {
    STACK_CONTENT_TYPE data;
    uint32_t status;
};
typedef struct _stack_result_ StackResult;

/* The ADT interface */
/*
 * NOTE: we copy Stack instances across procedure calls.
 * This is inefficient and not-completely-right. But till we learn explicit
 * memory management using 'malloc' and 'free', we continue to pass
 * objects by value than by address.
 */
Stack    stack_new  (uint32_t size);
void     stack_delete(Stack stk);
uint32_t stack_full (const Stack stk);
uint32_t stack_empty(const Stack stk);
Stack    stack_push (Stack stk, STACK_CONTENT_TYPE data, StackResult *result);
Stack    stack_pop  (Stack stk, StackResult *result);
Stack    stack_peek (const Stack stk, StackResult *result);

#endif
