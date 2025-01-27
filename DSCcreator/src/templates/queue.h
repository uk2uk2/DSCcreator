const char* QUEUE_TEMPLATE_H = R"(
#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include "ds_common.h"

typedef struct QueueNode {
    void* data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    size_t size;
    void (*destroy)(void*);
} Queue;

// Core operations
Queue* queue_create(void (*destroy)(void*));
void queue_destroy(Queue* queue);
int queue_enqueue(Queue* queue, void* data);
void* queue_dequeue(Queue* queue);
void* queue_peek(const Queue* queue);

// Utility functions
size_t queue_size(const Queue* queue);
bool queue_is_empty(const Queue* queue);
void queue_clear(Queue* queue);

#endif // DS_QUEUE_H
)";
