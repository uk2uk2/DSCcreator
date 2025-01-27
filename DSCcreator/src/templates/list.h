// Linked List Template
const char* LIST_TEMPLATE_H = R"(
#ifndef DS_LIST_H
#define DS_LIST_H

#include "ds_common.h"

typedef struct ListNode {
    void* data;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
    size_t size;
    void (*destroy)(void*);  // Custom destructor
    int (*compare)(const void*, const void*);  // Comparison function
} List;

// Core operations
List* list_create(void (*destroy)(void*), int (*compare)(const void*, const void*));
void list_destroy(List* list);
int list_insert(List* list, void* data);
void* list_remove(List* list, const void* key);
void* list_find(const List* list, const void* key);

// Iterator interface
typedef struct {
    ListNode* current;
    ListNode* next;
} ListIterator;

ListIterator list_iterator_create(List* list);
void* list_iterator_next(ListIterator* iterator);
bool list_iterator_has_next(const ListIterator* iterator);

// Utility functions
size_t list_size(const List* list);
bool list_is_empty(const List* list);
void list_clear(List* list);

// Advanced operations
void list_sort(List* list);
List* list_merge(const List* list1, const List* list2);
void list_reverse(List* list);

#endif // DS_LIST_H
)";