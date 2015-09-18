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

    bst_traverse_inorder_recursive(&tree);
    bst_traverse_inorder_iterative(&tree);
}

int main()
{
	test_bst_with_one_key();
    test_bst_with_three_keys();
    
    test_bst_traverse_inorder();

    return 0;
}