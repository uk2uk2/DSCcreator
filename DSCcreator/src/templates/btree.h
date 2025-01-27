const char* BTREE_TEMPLATE_H = R"(
#ifndef DS_BTREE_H
#define DS_BTREE_H

#include "ds_common.h"

#define BTREE_MIN_DEGREE 3  // Minimum degree (minimum children per node)

typedef struct BTreeNode {
    void** keys;            // Array of keys
    void** values;          // Array of values
    struct BTreeNode** children;  // Array of child pointers
    int n;                  // Current number of keys
    bool leaf;              // Is true when node is leaf
} BTreeNode;

typedef struct {
    BTreeNode* root;
    size_t size;
    int t;                  // Minimum degree
    int (*compare)(const void*, const void*);
    void (*destroy_key)(void*);
    void (*destroy_value)(void*);
} BTree;

// Core operations
BTree* btree_create(int t,
                   int (*compare)(const void*, const void*),
                   void (*destroy_key)(void*),
                   void (*destroy_value)(void*));
void btree_destroy(BTree* tree);
int btree_insert(BTree* tree, void* key, void* value);
void* btree_search(const BTree* tree, const void* key);
bool btree_delete(BTree* tree, const void* key);

// Utility functions
size_t btree_size(const BTree* tree);
bool btree_is_empty(const BTree* tree);
void btree_clear(BTree* tree);

// Visualization
void btree_print(const BTree* tree);

#endif // DS_BTREE_H
)";
