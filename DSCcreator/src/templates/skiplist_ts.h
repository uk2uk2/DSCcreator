const char* SKIPLIST_TS_TEMPLATE_H = R"(
#ifndef DS_SKIPLIST_TS_H
#define DS_SKIPLIST_TS_H

#include "ds_common.h"
#include <pthread.h>

// Thread-safe structure definitions
typedef struct TSSkipNode {
    void* data;
    struct TSSkipNode** forward;
    int level;
    pthread_mutex_t lock;  // Node-level lock
} TSSkipNode;

typedef struct {
    TSSkipNode* header;
    int level;
    size_t size;
    int (*compare)(const void*, const void*);
    void (*destroy)(void*);
    pthread_mutex_t global_lock;  // List-level lock
    pthread_rwlock_t size_lock;   // Reader-writer lock for size
} TSSkipList;

// Thread-safe function declarations
TSSkipList* ts_skiplist_create(int (*compare)(const void*, const void*),
                              void (*destroy)(void*));
void ts_skiplist_destroy(TSSkipList* list);
int ts_skiplist_insert(TSSkipList* list, void* data);
bool ts_skiplist_remove(TSSkipList* list, const void* data);
void* ts_skiplist_search(const TSSkipList* list, const void* data);
size_t ts_skiplist_size(const TSSkipList* list);
bool ts_skiplist_is_empty(const TSSkipList* list);

#endif // DS_SKIPLIST_TS_H
)";
