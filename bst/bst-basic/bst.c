#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "stack.h"
#include "bst.h"

BST bst_new()
{
    BST tree = { NULL, 0, 0 };
    return tree;
}

static TreeNode* _make_tree_node_(Key key)
{
    TreeNode *tn = (TreeNode *) malloc(sizeof(TreeNode));
    assert(tn != NULL);

    tn->key = key;
    tn->left = tn->right = NULL;
    return tn;
}

/*
 * attempts to add 'key' to the 'tree',
 * returns a positive number if 'key' is not in 'tree' and a new node is added.
 * returns 0 if 'key' already exists in the 'tree'.
 */
BST* bst_add(BST *tree, Key key, Result *res)
{
    assert(res != NULL);
    TreeNode *root, *parent;

    /* find the right place for the new key.*/
    /* in the end, the new node should be inserted under 'parent' */
    parent = root = tree->root;
    while (root != NULL && root->key != key) {
    	parent = root;
        if (key < root->key) {
        	root = root->left;
        } else if (key > root->key) {
            root = root->right;
        }
    }
    /* add a new node if 'key' is not in 'tree' */
    if (root == NULL) {
        TreeNode *tnode = _make_tree_node_(key);
        if (parent == NULL) { assert(tree->mass == 0); tree->root = tnode; }
        else if (key < parent->key) parent->left = tnode;
        else parent->right = tnode;
        ++tree->mass;
    }
    
    *res = !root;
    assert(tree->root != NULL);

    return tree;
}

uint32_t bst_mass(const BST *tree)
{
    return tree->mass;
}

static void _do_bst_traverse_inorder_recursive_(TreeNode *root, Visitor visitor)
{
    if (root != NULL) {
        _do_bst_traverse_inorder_recursive_(root->left, visitor);
        visitor(VISIT_ELEMENT, root->key);
        _do_bst_traverse_inorder_recursive_(root->right, visitor);
    }
}

BST* bst_traverse_inorder_recursive(BST *tree, Visitor visitor)
{
    assert(tree != NULL);
    visitor(VISIT_START, 0); /* ignore the second argument. Its a dummy. */
    _do_bst_traverse_inorder_recursive_(tree->root, visitor);
    visitor(VISIT_END, 0);   /* ignore the second argument. Its a dummy. */

    return tree;
}

static void _do_bst_traverse_inorder_iterative_(TreeNode *root, Visitor visitor)
{
    Stack stk;
    StackResult res;

    stk = stack_new(0);
    while (root != NULL || !stack_empty(stk)) {
        if (root != NULL) { /* walk down the left subtree. */
            stack_push(stk, root, &res);
            root = root->left;
        } else {
            /* no subtree to process; visit the parent node. */
            stack_pop(stk, &res);
            root = res.data;
            /* Now is the time to process this node data! */
            visitor(VISIT_ELEMENT, root->key);
            root = root->right; /* inspect the right subtree. */
        }
    };
    stack_delete(stk);
}

BST* bst_traverse_inorder_iterative(BST *tree, Visitor visitor)
{
    assert(tree != NULL);
    visitor(VISIT_START, 0); /* ignore the second argument. Its a dummy. */
    _do_bst_traverse_inorder_iterative_(tree->root, visitor);
    visitor(VISIT_END, 0);   /* ignore the second argument. Its a dummy. */

    return tree;
}
