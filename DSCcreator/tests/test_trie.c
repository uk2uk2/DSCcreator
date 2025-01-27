#include <unity.h>
#include "trie.h"
#include <string.h>

static Trie* trie;

void setUp(void) {
    trie = trie_create(free);  // Use free as value destructor
}

void tearDown(void) {
    trie_destroy(trie);
}

void test_trie_create(void) {
    TEST_ASSERT_NOT_NULL(trie);
    TEST_ASSERT_EQUAL(0, trie->size);
}

void test_trie_insert_search(void) {
    char* value1 = strdup("value1");
    char* value2 = strdup("value2");
    
    TEST_ASSERT_EQUAL(DS_OK, trie_insert(trie, "key1", value1));
    TEST_ASSERT_EQUAL(DS_OK, trie_insert(trie, "key2", value2));
    
    TEST_ASSERT_EQUAL_STRING("value1", trie_search(trie, "key1"));
    TEST_ASSERT_EQUAL_STRING("value2", trie_search(trie, "key2"));
    TEST_ASSERT_NULL(trie_search(trie, "nonexistent"));
}

void test_trie_delete(void) {
    char* value = strdup("test_value");
    trie_insert(trie, "test_key", value);
    
    TEST_ASSERT_TRUE(trie_delete(trie, "test_key"));
    TEST_ASSERT_NULL(trie_search(trie, "test_key"));
    TEST_ASSERT_EQUAL(0, trie->size);
}

void test_trie_autocomplete(void) {
    // Insert test data
    trie_insert(trie, "cat", strdup("cat"));
    trie_insert(trie, "car", strdup("car"));
    trie_insert(trie, "cart", strdup("cart"));
    trie_insert(trie, "dog", strdup("dog"));
    
    size_t count;
    char** results = trie_autocomplete(trie, "ca", &count);
    
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL(3, count);
    
    // Sort results for consistent testing
    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            if (strcmp(results[j], results[j + 1]) > 0) {
                char* temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }
    
    TEST_ASSERT_EQUAL_STRING("car", results[0]);
    TEST_ASSERT_EQUAL_STRING("cart", results[1]);
    TEST_ASSERT_EQUAL_STRING("cat", results[2]);
    
    // Cleanup
    for (size_t i = 0; i < count; i++) {
        free(results[i]);
    }
    free(results);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_trie_create);
    RUN_TEST(test_trie_insert_search);
    RUN_TEST(test_trie_delete);
    RUN_TEST(test_trie_autocomplete);
    return UNITY_END();
}
