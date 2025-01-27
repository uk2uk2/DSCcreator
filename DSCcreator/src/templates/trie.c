const char* TRIE_TEMPLATE_C = R"(
#include "trie.h"
#include <string.h>

static TrieNode* trie_node_create(void) {
    TrieNode* node = calloc(1, sizeof(TrieNode));
    if (node) {
        node->is_end = false;
        node->value = NULL;
        // children array is zeroed by calloc
    }
    return node;
}

static void trie_node_destroy(TrieNode* node, void (*destroy_value)(void*)) {
    if (!node) return;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            trie_node_destroy(node->children[i], destroy_value);
        }
    }

    if (destroy_value && node->value) {
        destroy_value(node->value);
    }
    free(node);
}

Trie* trie_create(void (*destroy_value)(void*)) {
    Trie* trie = malloc(sizeof(Trie));
    if (!trie) return NULL;

    trie->root = trie_node_create();
    if (!trie->root) {
        free(trie);
        return NULL;
    }

    trie->size = 0;
    trie->destroy_value = destroy_value;
    return trie;
}

void trie_destroy(Trie* trie) {
    if (!trie) return;
    trie_node_destroy(trie->root, trie->destroy_value);
    free(trie);
}

int trie_insert(Trie* trie, const char* key, void* value) {
    if (!trie || !key) return DS_ERROR;

    TrieNode* current = trie->root;
    while (*key) {
        int index = (unsigned char)*key;
        if (!current->children[index]) {
            current->children[index] = trie_node_create();
            if (!current->children[index]) return DS_ERROR;
        }
        current = current->children[index];
        key++;
    }

    if (!current->is_end) {
        trie->size++;
    } else if (trie->destroy_value) {
        trie->destroy_value(current->value);
    }

    current->is_end = true;
    current->value = value;
    return DS_OK;
}

void* trie_search(const Trie* trie, const char* key) {
    if (!trie || !key) return NULL;

    TrieNode* current = trie->root;
    while (*key) {
        int index = (unsigned char)*key;
        if (!current->children[index]) return NULL;
        current = current->children[index];
        key++;
    }

    return current->is_end ? current->value : NULL;
}

static bool trie_delete_recursive(TrieNode* node, const char* key, 
                                void (*destroy_value)(void*), bool* size_decreased) {
    if (!node) return false;

    if (*key == '\0') {
        if (node->is_end) {
            node->is_end = false;
            if (destroy_value) {
                destroy_value(node->value);
            }
            node->value = NULL;
            *size_decreased = true;
            
            // Check if node can be deleted
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (node->children[i]) return false;
            }
            return true;
        }
        return false;
    }

    int index = (unsigned char)*key;
    if (trie_delete_recursive(node->children[index], key + 1, 
                            destroy_value, size_decreased)) {
        free(node->children[index]);
        node->children[index] = NULL;

        // Check if current node can be deleted
        if (!node->is_end) {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (node->children[i]) return false;
            }
            return true;
        }
    }
    return false;
}

bool trie_delete(Trie* trie, const char* key) {
    if (!trie || !key) return false;
    
    bool size_decreased = false;
    trie_delete_recursive(trie->root, key, trie->destroy_value, &size_decreased);
    
    if (size_decreased) {
        trie->size--;
        return true;
    }
    return false;
}

// Advanced operations
static void trie_collect_keys(TrieNode* node, char* prefix, int depth,
                            char** keys, size_t* count, size_t max_count) {
    if (!node || *count >= max_count) return;

    if (node->is_end) {
        prefix[depth] = '\0';
        keys[*count] = strdup(prefix);
        (*count)++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            prefix[depth] = (char)i;
            trie_collect_keys(node->children[i], prefix, depth + 1, 
                            keys, count, max_count);
        }
    }
}

char** trie_autocomplete(const Trie* trie, const char* prefix, size_t* count) {
    if (!trie || !prefix || !count) return NULL;
    *count = 0;

    // Find prefix node
    TrieNode* current = trie->root;
    while (*prefix) {
        int index = (unsigned char)*prefix;
        if (!current->children[index]) return NULL;
        current = current->children[index];
        prefix++;
    }

    // Allocate space for results
    char** keys = malloc(trie->size * sizeof(char*));
    if (!keys) return NULL;

    // Buffer for building strings
    char* buffer = malloc(1024); // Adjust size as needed
    if (!buffer) {
        free(keys);
        return NULL;
    }

    // Collect all words with the prefix
    strcpy(buffer, prefix);
    trie_collect_keys(current, buffer, strlen(prefix), keys, count, trie->size);

    free(buffer);
    return keys;
}
)";
