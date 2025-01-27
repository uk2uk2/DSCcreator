const char* TRIE_TEMPLATE_H = R"(
#ifndef DS_TRIE_H
#define DS_TRIE_H

#include "ds_common.h"

#define ALPHABET_SIZE 256

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool is_end;
    void* value;  // Associated value for key-value storage
} TrieNode;

typedef struct {
    TrieNode* root;
    size_t size;
    void (*destroy_value)(void*);
} Trie;

// Core operations
Trie* trie_create(void (*destroy_value)(void*));
void trie_destroy(Trie* trie);
int trie_insert(Trie* trie, const char* key, void* value);
void* trie_search(const Trie* trie, const char* key);
bool trie_delete(Trie* trie, const char* key);

// Advanced operations
char** trie_autocomplete(const Trie* trie, const char* prefix, size_t* count);
void trie_foreach(const Trie* trie, void (*callback)(const char*, void*, void*), void* user_data);
size_t trie_size(const Trie* trie);

#endif // DS_TRIE_H
)";
