const char* RBTREE_TEMPLATE_H = R"(
#ifndef DS_RBTREE_H
#define DS_RBTREE_H

#include "ds_common.h"

typedef enum { BLACK, RED } NodeColor;

typedef struct RBNode {
    void* key;
    void* value;
    NodeColor color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

typedef struct {
    RBNode* root;
    size_t size;
    int (*compare)(const void*, const void*);
    void (*destroy_key)(void*);
    void (*destroy_value)(void*);
} RBTree;

// Core operations
RBTree* rbtree_create(int (*compare)(const void*, const void*),
                     void (*destroy_key)(void*),
                     void (*destroy_value)(void*));
void rbtree_destroy(RBTree* tree);
int rbtree_insert(RBTree* tree, void* key, void* value);
void* rbtree_search(const RBTree* tree, const void* key);
bool rbtree_delete(RBTree* tree, const void* key);

// Utility functions
size_t rbtree_size(const RBTree* tree);
bool rbtree_is_empty(const RBTree* tree);
void rbtree_clear(RBTree* tree);

// Validation
bool rbtree_verify(const RBTree* tree);

#endif // DS_RBTREE_H
)";
