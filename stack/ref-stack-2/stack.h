#ifndef _INCLUDED_STACK_H_
#define _INCLUDED_STACK_H_

#include <stdint.h>

#define MAX_DEPTH 32

struct _stack_ {
    uint32_t size;               /* requested stack depth */
    int32_t  top;                /* index of the topmost element */
    float    data[MAX_DEPTH];    /* actual contents */
};
typedef struct _stack_ *Stack;

/* status bits used in the Result structure */
#define RESULT_INVALID    0
#define STACK_OK          1
#define STACK_FULL        2
#define STACK_EMPTY       4

struct _stack_result_ {
    float data;
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
Stack   stack_push (Stack stk, float data, StackResult *result);
Stack   stack_pop  (Stack stk, StackResult *result);
Stack   stack_peek (const Stack stk, StackResult *result);

#endif
