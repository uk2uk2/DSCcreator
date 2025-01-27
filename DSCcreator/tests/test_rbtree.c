#include <unity.h>
#include "rbtree.h"

static RBTree* tree;

static int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void setUp(void) {
    tree = rbtree_create(compare_ints, free, free);
}

void tearDown(void) {
    rbtree_destroy(tree);
}

void test_rbtree_create(void) {
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_EQUAL(0, rbtree_size(tree));
    TEST_ASSERT_TRUE(rbtree_is_empty(tree));
}

void test_rbtree_insert_search(void) {
    int* keys[] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
    int* values[] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
    
    *keys[0] = 10; *values[0] = 100;
    *keys[1] = 20; *values[1] = 200;
    *keys[2] = 30; *values[2] = 300;
    
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(DS_OK, rbtree_insert(tree, keys[i], values[i]));
    }
    
    TEST_ASSERT_EQUAL(3, rbtree_size(tree));
    
    // Test search
    int search_key = 20;
    int* found_value = rbtree_search(tree, &search_key);
    TEST_ASSERT_NOT_NULL(found_value);
    TEST_ASSERT_EQUAL(200, *found_value);
    
    // Test non-existent key
    search_key = 40;
    TEST_ASSERT_NULL(rbtree_search(tree, &search_key));
}

void test_rbtree_properties(void) {
    // Insert values that would cause rotations
    for (int i = 1; i <= 10; i++) {
        int* key = malloc(sizeof(int));
        int* value = malloc(sizeof(int));
        *key = i;
        *value = i * 10;
        rbtree_insert(tree, key, value);
    }
    
    TEST_ASSERT_TRUE(rbtree_verify(tree));
}

void test_rbtree_delete(void) {
    // Insert and then delete nodes
    int* key = malloc(sizeof(int));
    int* value = malloc(sizeof(int));
    *key = 50;
    *value = 500;
    
    rbtree_insert(tree, key, value);
    TEST_ASSERT_EQUAL(1, rbtree_size(tree));
    
    int search_key = 50;
    TEST_ASSERT_TRUE(rbtree_delete(tree, &search_key));
    TEST_ASSERT_EQUAL(0, rbtree_size(tree));
    TEST_ASSERT_NULL(rbtree_search(tree, &search_key));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_rbtree_create);
    RUN_TEST(test_rbtree_insert_search);
    RUN_TEST(test_rbtree_properties);
    RUN_TEST(test_rbtree_delete);
    return UNITY_END();
}
