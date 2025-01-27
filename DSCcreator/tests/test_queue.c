#include <unity.h>
#include "queue.h"

static Queue* queue;
static int test_data[] = {1, 2, 3, 4, 5};

void setUp(void) {
    queue = queue_create(NULL);  // No destructor for int data
}

void tearDown(void) {
    queue_destroy(queue);
}

void test_queue_create(void) {
    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_TRUE(queue_is_empty(queue));
    TEST_ASSERT_EQUAL(0, queue_size(queue));
}

void test_queue_enqueue(void) {
    TEST_ASSERT_EQUAL(DS_OK, queue_enqueue(queue, &test_data[0]));
    TEST_ASSERT_EQUAL(1, queue_size(queue));
    TEST_ASSERT_EQUAL_PTR(&test_data[0], queue_peek(queue));
}

void test_queue_dequeue(void) {
    queue_enqueue(queue, &test_data[0]);
    queue_enqueue(queue, &test_data[1]);
    
    void* data = queue_dequeue(queue);
    TEST_ASSERT_EQUAL_PTR(&test_data[0], data);
    TEST_ASSERT_EQUAL(1, queue_size(queue));
    
    data = queue_dequeue(queue);
    TEST_ASSERT_EQUAL_PTR(&test_data[1], data);
    TEST_ASSERT_TRUE(queue_is_empty(queue));
}

void test_queue_fifo_order(void) {
    for (int i = 0; i < 5; i++) {
        queue_enqueue(queue, &test_data[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        void* data = queue_dequeue(queue);
        TEST_ASSERT_EQUAL_PTR(&test_data[i], data);
    }
}

void test_queue_empty_operations(void) {
    TEST_ASSERT_NULL(queue_dequeue(queue));
    TEST_ASSERT_NULL(queue_peek(queue));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_queue_create);
    RUN_TEST(test_queue_enqueue);
    RUN_TEST(test_queue_dequeue);
    RUN_TEST(test_queue_fifo_order);
    RUN_TEST(test_queue_empty_operations);
    return UNITY_END();
}
