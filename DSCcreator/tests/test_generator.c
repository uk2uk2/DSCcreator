#include <unity.h>
#include "ds_generator.h"
#include "templates.h"

void setUp(void) {
    // Setup code before each test
}

void tearDown(void) {
    // Cleanup code after each test
}

void test_project_creation(void) {
    DSProject project = {
        .name = "test_ds",
        .type = DS_LIST,
        .thread_safe = false,
        .include_tests = true,
        .include_benchmark = false
    };
    
    TEST_ASSERT_EQUAL(DS_OK, create_project_structure(&project));
    // Verify directory structure
    TEST_ASSERT_TRUE(access("test_ds", F_OK) == 0);
    TEST_ASSERT_TRUE(access("test_ds/src", F_OK) == 0);
    TEST_ASSERT_TRUE(access("test_ds/include", F_OK) == 0);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_project_creation);
    return UNITY_END();
}
