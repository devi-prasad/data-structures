#include "assert.h"
#include "bst.h"

void test_bst_with_one_key()
{
	BST tree = bst_new();
    Result res = 0;

    bst_add(&tree, 10, &res);
    assert(res == 1);

    bst_add(&tree, 10, &res);
    assert(res == 0);
}

void test_bst_with_three_keys()
{
	BST tree = bst_new();
    Result res = 0;

    bst_add(&tree, 100, &res);
    assert(res == 1);
    assert(bst_mass(&tree) == 1);
    bst_add(&tree, 300, &res);
    assert(res == 1);
    assert(bst_mass(&tree) == 2);
    bst_add(&tree, 50, &res);
    assert(res == 1);
    assert(bst_mass(&tree) == 3);

    bst_add(&tree, 100, &res);
    assert(res == 0);
    assert(bst_mass(&tree) == 3);
    bst_add(&tree, 300, &res);
    assert(res == 0);
    assert(bst_mass(&tree) == 3);
    bst_add(&tree, 50, &res);
    assert(res == 0);
    assert(bst_mass(&tree) == 3);
}

/*
 * A simple-minded visitor. All it does is to react to BST traversal
 * events so it pretty-prints values in the inorder fashion.
 *
 */
#include <stdio.h>
void printer(uint32_t visit_event, Key data)
{
    switch (visit_event) {
        case VISIT_START  : printf("\nA new traversal:\n "); break;
        case VISIT_ELEMENT: printf(" %d ", data); break;
        case VISIT_END    : printf("\nThe traversal is completed.\n\n"); break;
    }
}

/*
 * NOTE: take a closer look at the way 'static' storage is used inside 
 *       the function to record the visited values and the running count.
 *       On VISIT_START we reset the counter to zero.
 *       On successive VISIT_ELEMENT we store the value in 'arr' and update
 *       the 'count' of elements we have with us.
 *       On VISIT_END we check if 'arr' is actually sorted!
 */
void inorder_validator(uint32_t visit_event, Key data)
{
    static Key arr[STACK_MAX_DEPTH] = {0};
    static int32_t count = 0;

    switch (visit_event) {
        case VISIT_START  : count = 0; break;
        case VISIT_ELEMENT: arr[count] = data; ++count; break;
        case VISIT_END    : {
            int32_t i;
            for (i = 0, --count; i < count; ++i) {
                assert(arr[i] < arr[i+1]);
            }
            count = 0;
            /*printf("\n  inorder traversal checked!\n\n");*/
        }
        break;
    }
}

void test_bst_traverse_inorder()
{
    BST tree = bst_new();
    Result res = 0;
   
    bst_add(&tree, 100, &res);
    bst_add(&tree, 500, &res);
    bst_add(&tree, 300, &res);
    bst_add(&tree, 50, &res);
    bst_add(&tree, 25, &res);
    bst_add(&tree, 250, &res);
    bst_add(&tree, 70, &res);
    bst_add(&tree, 80, &res);
    bst_add(&tree, 400, &res);
    bst_add(&tree, 85, &res);
    bst_add(&tree, 480, &res);
    bst_add(&tree, 75, &res);
    bst_add(&tree, 60, &res);
    bst_add(&tree, 1024, &res);

    /* NOTE: 'printer' and 'inorder_validator' are both Visitor types. */
    bst_traverse_inorder_recursive(&tree, printer);
    bst_traverse_inorder_recursive(&tree, inorder_validator);

    bst_traverse_inorder_iterative(&tree, printer);
    bst_traverse_inorder_iterative(&tree, inorder_validator);
}

int main()
{
	test_bst_with_one_key();
    test_bst_with_three_keys();
    
    test_bst_traverse_inorder();

    return 0;
}