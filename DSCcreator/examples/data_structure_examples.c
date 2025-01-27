const char* EXAMPLES_TEMPLATE_C = R"(
#include <stdio.h>
#include "ds_generator.h"

// Example 1: Student Management System
void student_management_example(void) {
    printf("\nStudent Management System Example\n");
    printf("================================\n");
    
    // Create data structures
    HashTable* student_table = hashtable_create(100, NULL, free);
    List* student_list = list_create(NULL);
    
    // Add students
    struct Student {
        int id;
        char name[50];
        float gpa;
    };
    
    struct Student* s1 = malloc(sizeof(struct Student));
    s1->id = 1; strcpy(s1->name, "John Doe"); s1->gpa = 3.8;
    hashtable_insert(student_table, &s1->id, s1);
    list_append(student_list, s1);
    
    struct Student* s2 = malloc(sizeof(struct Student));
    s2->id = 2; strcpy(s2->name, "Jane Smith"); s2->gpa = 3.9;
    hashtable_insert(student_table, &s2->id, s2);
    list_append(student_list, s2);
    
    // Lookup and print student
    int lookup_id = 1;
    struct Student* found = hashtable_search(student_table, &lookup_id);
    if (found) {
        printf("Found student: %s (ID: %d, GPA: %.2f)\n", 
               found->name, found->id, found->gpa);
    }
    
    // Cleanup
    hashtable_destroy(student_table);
    list_destroy(student_list);
}

// Example 2: Graph-based Social Network
void social_network_example(void) {
    printf("\nSocial Network Example\n");
    printf("=====================\n");
    
    // Create graph
    Graph* network = graph_create(10, false, free, NULL);
    
    // Add users as vertices
    struct User {
        int id;
        char name[50];
    };
    
    struct User* users[5];
    for (int i = 0; i < 5; i++) {
        users[i] = malloc(sizeof(struct User));
        users[i]->id = i;
        sprintf(users[i]->name, "User %d", i);
        graph_add_vertex(network, users[i]);
    }
    
    // Add friendships as edges
    graph_add_edge(network, 0, 1, 1.0); // User 0 and 1 are friends
    graph_add_edge(network, 1, 2, 1.0);
    graph_add_edge(network, 2, 3, 1.0);
    graph_add_edge(network, 3, 4, 1.0);
    
    // Print user's friends
    void print_friend(void* data, void* user_data) {
        struct User* user = (struct User*)data;
        printf("Friend: %s\n", user->name);
    }
    
    printf("User 0's friends:\n");
    graph_bfs(network, 0, print_friend, NULL);
    
    // Cleanup
    graph_destroy(network);
}

// Example 3: Task Scheduler
void task_scheduler_example(void) {
    printf("\nTask Scheduler Example\n");
    printf("=====================\n");
    
    // Create priority queue (using heap)
    Heap* task_queue = heap_create(NULL, free);
    
    struct Task {
        int priority;
        char description[100];
    };
    
    // Add tasks
    struct Task* tasks[3];
    tasks[0] = malloc(sizeof(struct Task));
    tasks[0]->priority = 1;
    strcpy(tasks[0]->description, "High priority task");
    
    tasks[1] = malloc(sizeof(struct Task));
    tasks[1]->priority = 3;
    strcpy(tasks[1]->description, "Low priority task");
    
    tasks[2] = malloc(sizeof(struct Task));
    tasks[2]->priority = 2;
    strcpy(tasks[2]->description, "Medium priority task");
    
    for (int i = 0; i < 3; i++) {
        heap_insert(task_queue, tasks[i]);
    }
    
    // Process tasks in priority order
    printf("Processing tasks:\n");
    while (!heap_is_empty(task_queue)) {
        struct Task* task = heap_extract(task_queue);
        printf("Priority %d: %s\n", task->priority, task->description);
        free(task);
    }
    
    // Cleanup
    heap_destroy(task_queue);
}

int main(void) {
    student_management_example();
    social_network_example();
    task_scheduler_example();
    return 0;
}
)";
