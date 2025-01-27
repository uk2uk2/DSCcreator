#include <unity.h>
#include "btree.h"
#include <string.h>

static BTree* tree;

// Comparison function for integers
static int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void setUp(void) {
    tree = btree_create(3, compare_ints, free, free);
}

void tearDown(void) {
    btree_destroy(tree);
}

void test_btree_create(void) {
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_EQUAL(0, btree_size(tree));
    TEST_ASSERT_TRUE(btree_is_empty(tree));
}

void test_btree_insert_search(void) {
    int* keys[] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
    int* values[] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
    
    *keys[0] = 10; *values[0] = 100;
    *keys[1] = 20; *values[1] = 200;
    *keys[2] = 30; *values[2] = 300;
    
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(DS_OK, btree_insert(tree, keys[i], values[i]));
    }
    
    TEST_ASSERT_EQUAL(3, btree_size(tree));
    
    // Test search
    int search_key = 20;
    int* found_value = btree_search(tree, &search_key);
    TEST_ASSERT_NOT_NULL(found_value);
    TEST_ASSERT_EQUAL(200, *found_value);
    
    // Test non-existent key
    search_key = 40;
    TEST_ASSERT_NULL(btree_search(tree, &search_key));
}

void test_btree_delete(void) {
    int* key = malloc(sizeof(int));
    int* value = malloc(sizeof(int));
    *key = 50;
    *value = 500;
    
    btree_insert(tree, key, value);
    TEST_ASSERT_EQUAL(1, btree_size(tree));
    
    int search_key = 50;
    TEST_ASSERT_TRUE(btree_delete(tree, &search_key));
    TEST_ASSERT_EQUAL(0, btree_size(tree));
    TEST_ASSERT_NULL(btree_search(tree, &search_key));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_btree_create);
    RUN_TEST(test_btree_insert_search);
    RUN_TEST(test_btree_delete);
    return UNITY_END();
}
