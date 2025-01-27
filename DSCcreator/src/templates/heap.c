const char* HEAP_TEMPLATE_C = R"(
#include "heap.h"

#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i)   (2 * (i) + 1)
#define RIGHT(i)  (2 * (i) + 2)

static void swap(void** a, void** b) {
    void* temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(Heap* heap, int index) {
    while (index > 0) {
        int parent = PARENT(index);
        if (heap->compare(heap->array[index], heap->array[parent]) < 0) {
            swap(&heap->array[index], &heap->array[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

static void heapify_down(Heap* heap, int index) {
    int smallest = index;
    int left = LEFT(index);
    int right = RIGHT(index);

    if (left < heap->size && 
        heap->compare(heap->array[left], heap->array[smallest]) < 0) {
        smallest = left;
    }

    if (right < heap->size && 
        heap->compare(heap->array[right], heap->array[smallest]) < 0) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        heapify_down(heap, smallest);
    }
}

Heap* heap_create(int (*compare)(const void*, const void*),
                 void (*destroy)(void*),
                 size_t initial_capacity) {
    Heap* heap = malloc(sizeof(Heap));
    if (!heap) return NULL;

    heap->array = malloc(initial_capacity * sizeof(void*));
    if (!heap->array) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = initial_capacity;
    heap->compare = compare;
    heap->destroy = destroy;

    return heap;
}

void heap_destroy(Heap* heap) {
    if (!heap) return;
    
    if (heap->destroy) {
        for (size_t i = 0; i < heap->size; i++) {
            heap->destroy(heap->array[i]);
        }
    }
    
    free(heap->array);
    free(heap);
}

static int heap_resize(Heap* heap) {
    size_t new_capacity = heap->capacity * 2;
    void** new_array = realloc(heap->array, new_capacity * sizeof(void*));
    if (!new_array) return DS_ERROR;

    heap->array = new_array;
    heap->capacity = new_capacity;
    return DS_OK;
}

int heap_insert(Heap* heap, void* data) {
    if (!heap) return DS_ERROR;

    if (heap->size == heap->capacity) {
        if (heap_resize(heap) != DS_OK) {
            return DS_ERROR;
        }
    }

    heap->array[heap->size] = data;
    heapify_up(heap, heap->size);
    heap->size++;

    return DS_OK;
}

void* heap_extract(Heap* heap) {
    if (!heap || heap->size == 0) return NULL;

    void* min = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    if (heap->size > 0) {
        heapify_down(heap, 0);
    }

    return min;
}

void* heap_peek(const Heap* heap) {
    return (heap && heap->size > 0) ? heap->array[0] : NULL;
}

size_t heap_size(const Heap* heap) {
    return heap ? heap->size : 0;
}

bool heap_is_empty(const Heap* heap) {
    return heap ? heap->size == 0 : true;
}
)";
