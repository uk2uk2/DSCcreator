const char* STACK_TEMPLATE_C = R"(
#include "stack.h"

Stack* stack_create(void (*destroy)(void*)) {
    Stack* stack = malloc(sizeof(Stack));
    if (stack) {
        stack->top = NULL;
        stack->size = 0;
        stack->destroy = destroy;
    }
    return stack;
}

void stack_destroy(Stack* stack) {
    if (!stack) return;
    
    StackNode* current = stack->top;
    while (current) {
        StackNode* next = current->next;
        if (stack->destroy) {
            stack->destroy(current->data);
        }
        free(current);
        current = next;
    }
    free(stack);
}

int stack_push(Stack* stack, void* data) {
    if (!stack) return DS_ERROR;
    
    StackNode* node = malloc(sizeof(StackNode));
    if (!node) return DS_ERROR;
    
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    
    return DS_OK;
}

void* stack_pop(Stack* stack) {
    if (!stack || !stack->top) return NULL;
    
    StackNode* top = stack->top;
    void* data = top->data;
    stack->top = top->next;
    stack->size--;
    
    free(top);
    return data;
}

void* stack_peek(const Stack* stack) {
    return stack && stack->top ? stack->top->data : NULL;
}

size_t stack_size(const Stack* stack) {
    return stack ? stack->size : 0;
}

bool stack_is_empty(const Stack* stack) {
    return stack ? stack->size == 0 : true;
}

void stack_clear(Stack* stack) {
    if (!stack) return;
    
    while (!stack_is_empty(stack)) {
        void* data = stack_pop(stack);
        if (stack->destroy) {
            stack->destroy(data);
        }
    }
}
)";
