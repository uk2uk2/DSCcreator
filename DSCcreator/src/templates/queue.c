const char* QUEUE_TEMPLATE_C = R"(
#include "queue.h"

Queue* queue_create(void (*destroy)(void*)) {
    Queue* queue = malloc(sizeof(Queue));
    if (!queue) return NULL;
    
    queue->front = queue->rear = NULL;
    queue->size = 0;
    queue->destroy = destroy;
    
    return queue;
}

void queue_destroy(Queue* queue) {
    if (!queue) return;
    
    while (!queue_is_empty(queue)) {
        void* data = queue_dequeue(queue);
        if (queue->destroy) {
            queue->destroy(data);
        }
    }
    
    free(queue);
}

int queue_enqueue(Queue* queue, void* data) {
    if (!queue) return DS_ERROR;
    
    QueueNode* node = malloc(sizeof(QueueNode));
    if (!node) return DS_ERROR;
    
    node->data = data;
    node->next = NULL;
    
    if (queue_is_empty(queue)) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    
    queue->size++;
    return DS_OK;
}

void* queue_dequeue(Queue* queue) {
    if (!queue || queue_is_empty(queue)) return NULL;
    
    QueueNode* temp = queue->front;
    void* data = temp->data;
    
    queue->front = queue->front->next;
    if (!queue->front) {
        queue->rear = NULL;
    }
    
    free(temp);
    queue->size--;
    
    return data;
}

void* queue_peek(const Queue* queue) {
    return (queue && queue->front) ? queue->front->data : NULL;
}

size_t queue_size(const Queue* queue) {
    return queue ? queue->size : 0;
}

bool queue_is_empty(const Queue* queue) {
    return queue ? queue->size == 0 : true;
}
)";
