const char* SKIPLIST_TEMPLATE_H = R"(
#ifndef DS_SKIPLIST_H
#define DS_SKIPLIST_H

#include "ds_common.h"

#define SKIPLIST_MAX_LEVEL 16
#define SKIPLIST_P 0.5

typedef struct SkipNode {
    void* key;
    void* value;
    struct SkipNode** forward;
    int level;
} SkipNode;

typedef struct {
    SkipNode* header;
    int level;
    size_t size;
    int (*compare)(const void*, const void*);
    void (*destroy_key)(void*);
    void (*destroy_value)(void*);
} SkipList;

// Core operations
SkipList* skiplist_create(int (*compare)(const void*, const void*),
                         void (*destroy_key)(void*),
                         void (*destroy_value)(void*));
void skiplist_destroy(SkipList* list);
int skiplist_insert(SkipList* list, void* key, void* value);
void* skiplist_search(const SkipList* list, const void* key);
bool skiplist_delete(SkipList* list, const void* key);

// Utility functions
size_t skiplist_size(const SkipList* list);
bool skiplist_is_empty(const SkipList* list);
void skiplist_clear(SkipList* list);

// Debug/visualization
void skiplist_print(const SkipList* list, void (*print_key)(const void*));

#endif // DS_SKIPLIST_H
)";
