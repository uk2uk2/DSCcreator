const char* STACK_TEMPLATE_H = R"(
#ifndef DS_STACK_H
#define DS_STACK_H

#include "ds_common.h"

typedef struct StackNode {
    void* data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    size_t size;
    void (*destroy)(void*);
} Stack;

// Core operations
Stack* stack_create(void (*destroy)(void*));
void stack_destroy(Stack* stack);
int stack_push(Stack* stack, void* data);
void* stack_pop(Stack* stack);
void* stack_peek(const Stack* stack);

// Utility functions
size_t stack_size(const Stack* stack);
bool stack_is_empty(const Stack* stack);
void stack_clear(Stack* stack);

#endif // DS_STACK_H
)";
