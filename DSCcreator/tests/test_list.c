#include "unity.h"
#include "ds_generator.h"
#include "templates/list.h"

void setUp(void) {
    // Set up test environment
}

void tearDown(void) {
    // Clean up after test
}

void test_list_create(void) {
    List* list = list_create(NULL);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_INT(0, list_size(list));
    TEST_ASSERT_TRUE(list_is_empty(list));
    list_destroy(list);
}

void test_list_insert(void) {
    List* list = list_create(free);
    int* value = malloc(sizeof(int));
    *value = 42;
    
    TEST_ASSERT_EQUAL_INT(DS_OK, list_insert(list, 0, value));
    TEST_ASSERT_EQUAL_INT(1, list_size(list));
    TEST_ASSERT_FALSE(list_is_empty(list));
    
    int* retrieved = list_get(list, 0);
    TEST_ASSERT_NOT_NULL(retrieved);
    TEST_ASSERT_EQUAL_INT(42, *retrieved);
    
    list_destroy(list);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_create);
    RUN_TEST(test_list_insert);
    return UNITY_END();
}
