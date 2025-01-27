const char* LIST_TEMPLATE_C = R"(
#include "list.h"
#include <string.h>

List* list_create(void (*destroy)(void*), int (*compare)(const void*, const void*)) {
    List* list = malloc(sizeof(List));
    if (list) {
        list->head = NULL;
        list->size = 0;
        list->destroy = destroy;
        list->compare = compare;
    }
    return list;
}

void list_destroy(List* list) {
    if (!list) return;
    
    ListNode* current = list->head;
    while (current) {
        ListNode* next = current->next;
        if (list->destroy) {
            list->destroy(current->data);
        }
        free(current);
        current = next;
    }
    free(list);
}

int list_insert(List* list, void* data) {
    if (!list) return DS_ERROR;
    
    ListNode* node = malloc(sizeof(ListNode));
    if (!node) return DS_ERROR;
    
    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
    
    return DS_OK;
}

// ... More implementations
)";