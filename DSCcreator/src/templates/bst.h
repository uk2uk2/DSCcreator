const char* BST_TEMPLATE_H = R"(
#ifndef DS_BST_H
#define DS_BST_H

#include "ds_common.h"

typedef struct BSTNode {
    void* data;
    struct BSTNode* left;
    struct BSTNode* right;
    int height;  // For AVL balancing
} BSTNode;

typedef struct {
    BSTNode* root;
    size_t size;
    void (*destroy)(void*);
    int (*compare)(const void*, const void*);
    bool is_avl;  // Enable AVL balancing
} BSTree;

// Core operations
BSTree* bst_create(void (*destroy)(void*), 
                  int (*compare)(const void*, const void*),
                  bool is_avl);
void bst_destroy(BSTree* tree);
int bst_insert(BSTree* tree, void* data);
void* bst_remove(BSTree* tree, const void* key);
void* bst_find(const BSTree* tree, const void* key);

// Traversal types
typedef enum {
    PREORDER,
    INORDER,
    POSTORDER,
    LEVELORDER
} TraversalType;

// Iterator interface
typedef struct {
    BSTNode** stack;
    int top;
    BSTNode* current;
    TraversalType type;
} BSTIterator;

BSTIterator bst_iterator_create(BSTree* tree, TraversalType type);
void* bst_iterator_next(BSTIterator* iterator);
bool bst_iterator_has_next(const BSTIterator* iterator);

// Utility functions
size_t bst_size(const BSTree* tree);
bool bst_is_empty(const BSTree* tree);
int bst_height(const BSTree* tree);
void bst_clear(BSTree* tree);

// Visualization
void bst_print(const BSTree* tree);

#endif // DS_BST_H
)";