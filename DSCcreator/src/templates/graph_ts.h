const char* GRAPH_THREAD_SAFE_H = R"(
#ifndef DS_GRAPH_THREAD_SAFE_H
#define DS_GRAPH_THREAD_SAFE_H

#include "ds_common.h"
#include <pthread.h>

typedef struct TSEdge {
    size_t dest;
    double weight;
    struct TSEdge* next;
    pthread_mutex_t lock;
} TSEdge;

typedef struct TSVertex {
    void* data;
    TSEdge* edges;
    bool visited;
    pthread_mutex_t lock;
} TSVertex;

typedef struct {
    TSVertex* vertices;
    size_t vertex_count;
    size_t capacity;
    bool directed;
    void (*destroy)(void*);
    int (*compare)(const void*, const void*);
    pthread_mutex_t global_lock;
    pthread_rwlock_t traversal_lock;
} TSGraph;

// Thread-safe operations
TSGraph* ts_graph_create(size_t capacity, bool directed,
                        void (*destroy)(void*),
                        int (*compare)(const void*, const void*));
void ts_graph_destroy(TSGraph* graph);
int ts_graph_add_vertex(TSGraph* graph, void* data);
int ts_graph_add_edge(TSGraph* graph, size_t source, size_t dest, double weight);

// Concurrent traversal
void ts_graph_parallel_bfs(TSGraph* graph, size_t start, 
                          void (*visit)(const void*, void*),
                          void* user_data);

#endif // DS_GRAPH_THREAD_SAFE_H
)";const char* GRAPH_THREAD_SAFE_H = R"(
#ifndef DS_GRAPH_THREAD_SAFE_H
#define DS_GRAPH_THREAD_SAFE_H

#include "ds_common.h"
#include <pthread.h>

typedef struct TSEdge {
    size_t dest;
    double weight;
    struct TSEdge* next;
    pthread_mutex_t lock;
} TSEdge;

typedef struct TSVertex {
    void* data;
    TSEdge* edges;
    bool visited;
    pthread_mutex_t lock;
} TSVertex;

typedef struct {
    TSVertex* vertices;
    size_t vertex_count;
    size_t capacity;
    bool directed;
    void (*destroy)(void*);
    int (*compare)(const void*, const void*);
    pthread_mutex_t global_lock;
    pthread_rwlock_t traversal_lock;
} TSGraph;

// Thread-safe operations
TSGraph* ts_graph_create(size_t capacity, bool directed,
                        void (*destroy)(void*),
                        int (*compare)(const void*, const void*));
void ts_graph_destroy(TSGraph* graph);
int ts_graph_add_vertex(TSGraph* graph, void* data);
int ts_graph_add_edge(TSGraph* graph, size_t source, size_t dest, double weight);

// Concurrent traversal
void ts_graph_parallel_bfs(TSGraph* graph, size_t start, 
                          void (*visit)(const void*, void*),
                          void* user_data);

#endif // DS_GRAPH_THREAD_SAFE_H
)";const char* GRAPH_THREAD_SAFE_H = R"(
#ifndef DS_GRAPH_THREAD_SAFE_H
#define DS_GRAPH_THREAD_SAFE_H

#include "ds_common.h"
#include <pthread.h>

typedef struct TSEdge {
    size_t dest;
    double weight;
    struct TSEdge* next;
    pthread_mutex_t lock;
} TSEdge;

typedef struct TSVertex {
    void* data;
    TSEdge* edges;
    bool visited;
    pthread_mutex_t lock;
} TSVertex;

typedef struct {
    TSVertex* vertices;
    size_t vertex_count;
    size_t capacity;
    bool directed;
    void (*destroy)(void*);
    int (*compare)(const void*, const void*);
    pthread_mutex_t global_lock;
    pthread_rwlock_t traversal_lock;
} TSGraph;

// Thread-safe operations
TSGraph* ts_graph_create(size_t capacity, bool directed,
                        void (*destroy)(void*),
                        int (*compare)(const void*, const void*));
void ts_graph_destroy(TSGraph* graph);
int ts_graph_add_vertex(TSGraph* graph, void* data);
int ts_graph_add_edge(TSGraph* graph, size_t source, size_t dest, double weight);

// Concurrent traversal
void ts_graph_parallel_bfs(TSGraph* graph, size_t start, 
                          void (*visit)(const void*, void*),
                          void* user_data);

#endif // DS_GRAPH_THREAD_SAFE_H
)";
