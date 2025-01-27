#include <unity.h>
#include "heap.h"

static Heap* heap;

// Comparison function for integers
static int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void setUp(void) {
    heap = heap_create(compare_ints, NULL, 10);
}

void tearDown(void) {
    heap_destroy(heap);
}

void test_heap_create(void) {
    TEST_ASSERT_NOT_NULL(heap);
    TEST_ASSERT_TRUE(heap_is_empty(heap));
    TEST_ASSERT_EQUAL(0, heap_size(heap));
}

void test_heap_insert(void) {
    int values[] = {5, 3, 7, 1, 4, 6, 2};
    for (int i = 0; i < 7; i++) {
        TEST_ASSERT_EQUAL(DS_OK, heap_insert(heap, &values[i]));
    }
    TEST_ASSERT_EQUAL(7, heap_size(heap));
    
    // Verify min heap property
    int* min = heap_peek(heap);
    TEST_ASSERT_EQUAL(1, *min);
}

void test_heap_extract(void) {
    int values[] = {5, 3, 7, 1, 4, 6, 2};
    for (int i = 0; i < 7; i++) {
        heap_insert(heap, &values[i]);
    }

    // Extract values and verify they come out in sorted order
    int prev = *(int*)heap_extract(heap);
    while (!heap_is_empty(heap)) {
        int current = *(int*)heap_extract(heap);
        TEST_ASSERT_TRUE(prev <= current);
        prev = current;
    }
}

void test_heap_peek(void) {
    int value = 42;
    heap_insert(heap, &value);
    int* peek = heap_peek(heap);
    TEST_ASSERT_EQUAL(42, *peek);
    TEST_ASSERT_EQUAL(1, heap_size(heap));  // Peek shouldn't remove the element
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_heap_create);
    RUN_TEST(test_heap_insert);
    RUN_TEST(test_heap_extract);
    RUN_TEST(test_heap_peek);
    return UNITY_END();
}
