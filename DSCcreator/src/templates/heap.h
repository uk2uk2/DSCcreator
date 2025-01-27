const char* HEAP_TEMPLATE_H = R"(
#ifndef DS_HEAP_H
#define DS_HEAP_H

#include "ds_common.h"

typedef struct {
    void** array;
    size_t size;
    size_t capacity;
    int (*compare)(const void*, const void*);
    void (*destroy)(void*);
} Heap;

// Core operations
Heap* heap_create(int (*compare)(const void*, const void*),
                 void (*destroy)(void*),
                 size_t initial_capacity);
void heap_destroy(Heap* heap);
int heap_insert(Heap* heap, void* data);
void* heap_extract(Heap* heap);
void* heap_peek(const Heap* heap);

// Utility functions
size_t heap_size(const Heap* heap);
bool heap_is_empty(const Heap* heap);
void heap_clear(Heap* heap);

#endif // DS_HEAP_H
)";const char* HEAP_TEMPLATE_H = R"(
#ifndef DS_HEAP_H
#define DS_HEAP_H

#include "ds_common.h"

typedef struct {
    void** array;
    size_t size;
    size_t capacity;
    int (*compare)(const void*, const void*);
    void (*destroy)(void*);
} Heap;

// Core operations
Heap* heap_create(int (*compare)(const void*, const void*),
                 void (*destroy)(void*),
                 size_t initial_capacity);
void heap_destroy(Heap* heap);
int heap_insert(Heap* heap, void* data);
void* heap_extract(Heap* heap);
void* heap_peek(const Heap* heap);

// Utility functions
size_t heap_size(const Heap* heap);
bool heap_is_empty(const Heap* heap);
void heap_clear(Heap* heap);

#endif // DS_HEAP_H
)";
