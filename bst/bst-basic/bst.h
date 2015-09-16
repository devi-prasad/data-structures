#ifndef _INCLUDED_BST_
#define _INCLUDED_BST_

#include <stdint.h>

typedef int32_t Key;
typedef uint32_t Result;

typedef struct _bst_ BST;
typedef struct _tree_node_ TreeNode;

struct _bst_ {
    TreeNode *root;
    uint32_t mass;        /* running count of nodes in the tree */
    uint32_t height;      /* current height of the tree */
};

struct _tree_node_ {
    Key key;
    TreeNode *left;
    TreeNode *right;
};

BST bst_new();
BST* bst_add(BST *tree, Key key, Result *res);
BST* bst_traverse_inorder(BST tree);
BST* bst_traverse_preorder(BST tree);
BST* bst_traverse_postorder(BST tree);
BST* bst_find(BST tree, Key key, Result *result);

uint32_t bst_mass(const BST *tree);
uint32_t bst_height(const BST *tree);

#endif
