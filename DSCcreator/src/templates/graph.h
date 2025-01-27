const char* GRAPH_TEMPLATE_H = R"(
#ifndef DS_GRAPH_H
#define DS_GRAPH_H

#include "ds_common.h"

typedef struct Edge {
    size_t dest;
    double weight;
    struct Edge* next;
} Edge;

typedef struct Vertex {
    void* data;
    Edge* edges;
    bool visited;  // For traversal
} Vertex;

typedef struct {
    Vertex* vertices;
    size_t vertex_count;
    size_t capacity;
    bool directed;
    void (*destroy)(void*);
    int (*compare)(const void*, const void*);
} Graph;

// Core operations
Graph* graph_create(size_t capacity, bool directed,
                   void (*destroy)(void*),
                   int (*compare)(const void*, const void*));
void graph_destroy(Graph* graph);
int graph_add_vertex(Graph* graph, void* data);
int graph_add_edge(Graph* graph, size_t source, size_t dest, double weight);
int graph_remove_edge(Graph* graph, size_t source, size_t dest);

// Traversal functions
typedef void (*VisitFn)(const void* data, void* user_data);
void graph_dfs(const Graph* graph, size_t start, VisitFn visit, void* user_data);
void graph_bfs(const Graph* graph, size_t start, VisitFn visit, void* user_data);

// Path finding
double* graph_shortest_path(const Graph* graph, size_t source);
double* graph_minimum_spanning_tree(const Graph* graph);

#endif // DS_GRAPH_H
)";
