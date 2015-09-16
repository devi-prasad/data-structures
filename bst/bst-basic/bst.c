#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
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