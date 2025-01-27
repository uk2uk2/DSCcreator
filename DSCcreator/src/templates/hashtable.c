const char* HASHTABLE_TEMPLATE_C = R"(
#include "hashtable.h"

HashTable* hashtable_create(size_t initial_capacity,
                          size_t (*hash)(const void*),
                          int (*compare)(const void*, const void*),
                          void (*destroy_key)(void*),
                          void (*destroy_value)(void*)) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) return NULL;
    
    table->buckets = calloc(initial_capacity, sizeof(HashNode*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    
    table->capacity = initial_capacity;
    table->size = 0;
    table->hash = hash;
    table->compare = compare;
    table->destroy_key = destroy_key;
    table->destroy_value = destroy_value;
    
    return table;
}

static void bucket_destroy(HashTable* table, HashNode* node) {
    while (node) {
        HashNode* next = node->next;
        if (table->destroy_key) table->destroy_key(node->key);
        if (table->destroy_value) table->destroy_value(node->value);
        free(node);
        node = next;
    }
}

void hashtable_destroy(HashTable* table) {
    if (!table) return;
    
    for (size_t i = 0; i < table->capacity; i++) {
        bucket_destroy(table, table->buckets[i]);
    }
    
    free(table->buckets);
    free(table);
}

static void hashtable_resize(HashTable* table) {
    size_t old_capacity = table->capacity;
    HashNode** old_buckets = table->buckets;
    
    table->capacity *= 2;
    table->buckets = calloc(table->capacity, sizeof(HashNode*));
    if (!table->buckets) {
        table->buckets = old_buckets;
        table->capacity = old_capacity;
        return;
    }
    
    table->size = 0;
    for (size_t i = 0; i < old_capacity; i++) {
        HashNode* node = old_buckets[i];
        while (node) {
            HashNode* next = node->next;
            size_t index = table->hash(node->key) % table->capacity;
            node->next = table->buckets[index];
            table->buckets[index] = node;
            table->size++;
            node = next;
        }
    }
    
    free(old_buckets);
}

int hashtable_put(HashTable* table, void* key, void* value) {
    if (!table) return DS_ERROR;
    
    if (table->size >= table->capacity * 0.75) {
        hashtable_resize(table);
    }
    
    size_t index = table->hash(key) % table->capacity;
    HashNode* node = table->buckets[index];
    
    while (node) {
        if (table->compare(key, node->key) == 0) {
            // Update existing key
            if (table->destroy_value) table->destroy_value(node->value);
            node->value = value;
            return DS_OK;
        }
        node = node->next;
    }
    
    // Insert new node
    node = malloc(sizeof(HashNode));
    if (!node) return DS_ERROR;
    
    node->key = key;
    node->value = value;
    node->next = table->buckets[index];
    table->buckets[index] = node;
    table->size++;
    
    return DS_OK;
}

// ... more implementation
)";
