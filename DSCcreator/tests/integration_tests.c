const char* INTEGRATION_TESTS_TEMPLATE_C = R"(
#include <unity.h>
#include "ds_generator.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "bst.h"
#include "rbtree.h"
#include "graph.h"
#include "benchmark.h"

// Test data structure
typedef struct {
    int id;
    char* name;
    double value;
} TestData;

static TestData* create_test_data(int id, const char* name, double value) {
    TestData* data = malloc(sizeof(TestData));
    data->id = id;
    data->name = strdup(name);
    data->value = value;
    return data;
}

static void destroy_test_data(void* data) {
    TestData* td = (TestData*)data;
    free(td->name);
    free(td);
}

static int compare_test_data(const void* a, const void* b) {
    return ((TestData*)a)->id - ((TestData*)b)->id;
}

// Integration test scenarios
void test_list_to_bst_conversion(void) {
    List* list = list_create(destroy_test_data);
    
    // Add items to list
    for (int i = 0; i < 10; i++) {
        char name[32];
        sprintf(name, "Item %d", i);
        TestData* data = create_test_data(i, name, i * 1.5);
        list_append(list, data);
    }
    
    // Convert list to BST
    BST* bst = bst_create(compare_test_data, destroy_test_data);
    ListNode* current = list_head(list);
    
    while (current) {
        TestData* data = list_data(current);
        bst_insert(bst, data);
        current = list_next(current);
    }
    
    // Verify conversion
    TEST_ASSERT_EQUAL(list_size(list), bst_size(bst));
    
    // Cleanup
    list_destroy(list);
    bst_destroy(bst);
}

void test_complex_data_structure_operations(void) {
    // Create a graph with RB-Tree vertices
    Graph* graph = graph_create(10, false, destroy_test_data, compare_test_data);
    RBTree** vertex_trees = malloc(5 * sizeof(RBTree*));
    
    // Initialize vertex trees
    for (int i = 0; i < 5; i++) {
        vertex_trees[i] = rbtree_create(compare_test_data, NULL, destroy_test_data);
        
        // Add data to each tree
        for (int j = 0; j < 5; j++) {
            char name[32];
            sprintf(name, "Vertex %d-%d", i, j);
            TestData* data = create_test_data(i * 10 + j, name, i * j * 1.5);
            rbtree_insert(vertex_trees[i], data, data);
        }
        
        // Add tree as vertex to graph
        graph_add_vertex(graph, vertex_trees[i]);
    }
    
    // Add edges between vertices
    for (int i = 0; i < 4; i++) {
        graph_add_edge(graph, i, i + 1, 1.0);
    }
    
    // Verify structure
    TEST_ASSERT_EQUAL(5, graph_vertex_count(graph));
    
    // Cleanup
    free(vertex_trees);
    graph_destroy(graph);
}

void test_concurrent_operations(void) {
    // Create thread-safe data structures
    TSQueue* queue = ts_queue_create(destroy_test_data);
    TSHashTable* table = ts_hashtable_create(100, NULL, destroy_test_data);
    
    #define NUM_THREADS 4
    pthread_t threads[NUM_THREADS];
    
    // Thread function for concurrent operations
    void* thread_func(void* arg) {
        int thread_id = *(int*)arg;
        
        for (int i = 0; i < 100; i++) {
            char name[32];
            sprintf(name, "Thread %d Item %d", thread_id, i);
            TestData* data = create_test_data(thread_id * 1000 + i, name, i * 1.5);
            
            ts_queue_enqueue(queue, data);
            ts_hashtable_insert(table, &data->id, data);
        }
        
        return NULL;
    }
    
    // Start threads
    int thread_ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }
    
    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Verify results
    TEST_ASSERT_EQUAL(NUM_THREADS * 100, ts_queue_size(queue));
    TEST_ASSERT_EQUAL(NUM_THREADS * 100, ts_hashtable_size(table));
    
    // Cleanup
    ts_queue_destroy(queue);
    ts_hashtable_destroy(table);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_to_bst_conversion);
    RUN_TEST(test_complex_data_structure_operations);
    RUN_TEST(test_concurrent_operations);
    return UNITY_END();
}
)";
