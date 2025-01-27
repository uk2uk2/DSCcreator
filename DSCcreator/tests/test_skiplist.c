#include <unity.h>
#include "skiplist.h"
#include <string.h>

static SkipList* list;

static int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

static void print_int(const void* data) {
    printf("%d", *(int*)data);
}

void setUp(void) {
    list = skiplist_create(compare_ints, free, free);
}

void tearDown(void) {
    skiplist_destroy(list);
}

void test_skiplist_create(void) {
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(0, skiplist_size(list));
    TEST_ASSERT_TRUE(skiplist_is_empty(list));
}

void test_skiplist_insert_search(void) {
    int* keys[] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
    int* values[] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
    
    *keys[0] = 10; *values[0] = 100;
    *keys[1] = 20; *values[1] = 200;
    *keys[2] = 30; *values[2] = 300;
    
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(DS_OK, skiplist_insert(list, keys[i], values[i]));
    }
    
    TEST_ASSERT_EQUAL(3, skiplist_size(list));
    
    // Test search
    int search_key = 20;
    int* found_value = skiplist_search(list, &search_key);
    TEST_ASSERT_NOT_NULL(found_value);
    TEST_ASSERT_EQUAL(200, *found_value);
    
    // Test non-existent key
    search_key = 40;
    TEST_ASSERT_NULL(skiplist_search(list, &search_key));
}

void test_skiplist_delete(void) {
    int* key = malloc(sizeof(int));
    int* value = malloc(sizeof(int));
    *key = 50;
    *value = 500;
    
    skiplist_insert(list, key, value);
    TEST_ASSERT_EQUAL(1, skiplist_size(list));
    
    int search_key = 50;
    TEST_ASSERT_TRUE(skiplist_delete(list, &search_key));
    TEST_ASSERT_EQUAL(0, skiplist_size(list));
    TEST_ASSERT_NULL(skiplist_search(list, &search_key));
}

void test_skiplist_multiple_levels(void) {
    // Insert many elements to test multiple levels
    for (int i = 0; i < 100; i++) {
        int* key = malloc(sizeof(int));
        int* value = malloc(sizeof(int));
        *key = i;
        *value = i * 10;
        skiplist_insert(list, key, value);
    }
    
    TEST_ASSERT_EQUAL(100, skiplist_size(list));
    TEST_ASSERT_TRUE(list->level > 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_skiplist_create);
    RUN_TEST(test_skiplist_insert_search);
    RUN_TEST(test_skiplist_delete);
    RUN_TEST(test_skiplist_multiple_levels);
    return UNITY_END();
}
