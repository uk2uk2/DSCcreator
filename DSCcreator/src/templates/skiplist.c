const char* SKIPLIST_TEMPLATE_C = R"(
#include "skiplist.h"
#include <time.h>

static int random_level(void) {
    int level = 1;
    while ((rand() / (double)RAND_MAX) < SKIPLIST_P && 
           level < SKIPLIST_MAX_LEVEL) {
        level++;
    }
    return level;
}

static SkipNode* create_node(int level, void* key, void* value) {
    SkipNode* node = malloc(sizeof(SkipNode));
    if (!node) return NULL;
    
    node->forward = calloc(level + 1, sizeof(SkipNode*));
    if (!node->forward) {
        free(node);
        return NULL;
    }
    
    node->key = key;
    node->value = value;
    node->level = level;
    
    return node;
}

SkipList* skiplist_create(int (*compare)(const void*, const void*),
                         void (*destroy_key)(void*),
                         void (*destroy_value)(void*)) {
    SkipList* list = malloc(sizeof(SkipList));
    if (!list) return NULL;
    
    list->header = create_node(SKIPLIST_MAX_LEVEL, NULL, NULL);
    if (!list->header) {
        free(list);
        return NULL;
    }
    
    list->level = 1;
    list->size = 0;
    list->compare = compare;
    list->destroy_key = destroy_key;
    list->destroy_value = destroy_value;
    
    srand(time(NULL));  // Initialize random seed
    
    return list;
}

void skiplist_destroy(SkipList* list) {
    if (!list) return;
    
    SkipNode* current = list->header->forward[0];
    while (current) {
        SkipNode* next = current->forward[0];
        if (list->destroy_key) list->destroy_key(current->key);
        if (list->destroy_value) list->destroy_value(current->value);
        free(current->forward);
        free(current);
        current = next;
    }
    
    free(list->header->forward);
    free(list->header);
    free(list);
}

int skiplist_insert(SkipList* list, void* key, void* value) {
    if (!list) return DS_ERROR;
    
    SkipNode* update[SKIPLIST_MAX_LEVEL + 1];
    SkipNode* current = list->header;
    
    // Find insert position
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] && 
               list->compare(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
    
    // Update existing key
    if (current && list->compare(current->key, key) == 0) {
        if (list->destroy_value) list->destroy_value(current->value);
        current->value = value;
        return DS_OK;
    }
    
    // Insert new node
    int new_level = random_level();
    if (new_level > list->level) {
        for (int i = list->level; i < new_level; i++) {
            update[i] = list->header;
        }
        list->level = new_level;
    }
    
    SkipNode* new_node = create_node(new_level, key, value);
    if (!new_node) return DS_ERROR;
    
    for (int i = 0; i < new_level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
    
    list->size++;
    return DS_OK;
}

void* skiplist_search(const SkipList* list, const void* key) {
    if (!list) return NULL;
    
    SkipNode* current = list->header;
    
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] && 
               list->compare(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
    }
    
    current = current->forward[0];
    
    if (current && list->compare(current->key, key) == 0) {
        return current->value;
    }
    
    return NULL;
}

bool skiplist_delete(SkipList* list, const void* key) {
    if (!list) return false;
    
    SkipNode* update[SKIPLIST_MAX_LEVEL + 1];
    SkipNode* current = list->header;
    
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] && 
               list->compare(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (!current || list->compare(current->key, key) != 0) {
        return false;
    }
    
    for (int i = 0; i < list->level; i++) {
        if (update[i]->forward[i] != current) {
            break;
        }
        update[i]->forward[i] = current->forward[i];
    }
    
    while (list->level > 1 && 
           list->header->forward[list->level - 1] == NULL) {
        list->level--;
    }
    
    if (list->destroy_key) list->destroy_key(current->key);
    if (list->destroy_value) list->destroy_value(current->value);
    free(current->forward);
    free(current);
    
    list->size--;
    return true;
}

size_t skiplist_size(const SkipList* list) {
    return list ? list->size : 0;
}

bool skiplist_is_empty(const SkipList* list) {
    return list ? list->size == 0 : true;
}

void skiplist_print(const SkipList* list, void (*print_key)(const void*)) {
    if (!list || !print_key) return;
    
    printf("\nSkip List Structure:\n");
    for (int i = list->level - 1; i >= 0; i--) {
        printf("Level %d: ", i);
        SkipNode* node = list->header->forward[i];
        while (node) {
            print_key(node->key);
            printf(" -> ");
            node = node->forward[i];
        }
        printf("NULL\n");
    }
}
)";
