const char* GRAPH_TEMPLATE_C = R"(
#include "graph.h"
#include <string.h>

Graph* graph_create(size_t capacity, bool directed,
                   void (*destroy)(void*),
                   int (*compare)(const void*, const void*)) {
    Graph* graph = malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->vertices = calloc(capacity, sizeof(Vertex));
    if (!graph->vertices) {
        free(graph);
        return NULL;
    }

    graph->vertex_count = 0;
    graph->capacity = capacity;
    graph->directed = directed;
    graph->destroy = destroy;
    graph->compare = compare;

    return graph;
}

static void edge_destroy(Edge* edge) {
    while (edge) {
        Edge* next = edge->next;
        free(edge);
        edge = next;
    }
}

void graph_destroy(Graph* graph) {
    if (!graph) return;

    for (size_t i = 0; i < graph->vertex_count; i++) {
        if (graph->destroy) {
            graph->destroy(graph->vertices[i].data);
        }
        edge_destroy(graph->vertices[i].edges);
    }

    free(graph->vertices);
    free(graph);
}

int graph_add_vertex(Graph* graph, void* data) {
    if (!graph || graph->vertex_count >= graph->capacity) {
        return DS_ERROR;
    }

    graph->vertices[graph->vertex_count].data = data;
    graph->vertices[graph->vertex_count].edges = NULL;
    graph->vertices[graph->vertex_count].visited = false;
    graph->vertex_count++;

    return DS_OK;
}

static Edge* create_edge(size_t dest, double weight) {
    Edge* edge = malloc(sizeof(Edge));
    if (!edge) return NULL;

    edge->dest = dest;
    edge->weight = weight;
    edge->next = NULL;

    return edge;
}

int graph_add_edge(Graph* graph, size_t source, size_t dest, double weight) {
    if (!graph || source >= graph->vertex_count || dest >= graph->vertex_count) {
        return DS_ERROR;
    }

    // Add edge from source to dest
    Edge* edge = create_edge(dest, weight);
    if (!edge) return DS_ERROR;

    edge->next = graph->vertices[source].edges;
    graph->vertices[source].edges = edge;

    // If undirected, add edge from dest to source
    if (!graph->directed) {
        edge = create_edge(source, weight);
        if (!edge) return DS_ERROR;

        edge->next = graph->vertices[dest].edges;
        graph->vertices[dest].edges = edge;
    }

    return DS_OK;
}

static void reset_visited(Graph* graph) {
    for (size_t i = 0; i < graph->vertex_count; i++) {
        graph->vertices[i].visited = false;
    }
}

static void dfs_recursive(const Graph* graph, size_t vertex, 
                         VisitFn visit, void* user_data) {
    graph->vertices[vertex].visited = true;
    
    if (visit) {
        visit(graph->vertices[vertex].data, user_data);
    }

    for (Edge* edge = graph->vertices[vertex].edges; edge; edge = edge->next) {
        if (!graph->vertices[edge->dest].visited) {
            dfs_recursive(graph, edge->dest, visit, user_data);
        }
    }
}

void graph_dfs(const Graph* graph, size_t start, VisitFn visit, void* user_data) {
    if (!graph || start >= graph->vertex_count) return;

    reset_visited((Graph*)graph);  // Cast away const for resetting visited flags
    dfs_recursive(graph, start, visit, user_data);
}

void graph_bfs(const Graph* graph, size_t start, VisitFn visit, void* user_data) {
    if (!graph || start >= graph->vertex_count) return;

    reset_visited((Graph*)graph);

    // Create a queue for BFS
    size_t* queue = malloc(graph->vertex_count * sizeof(size_t));
    if (!queue) return;

    size_t front = 0, rear = 0;

    // Enqueue start vertex
    queue[rear++] = start;
    graph->vertices[start].visited = true;

    while (front < rear) {
        size_t vertex = queue[front++];
        
        if (visit) {
            visit(graph->vertices[vertex].data, user_data);
        }

        for (Edge* edge = graph->vertices[vertex].edges; edge; edge = edge->next) {
            if (!graph->vertices[edge->dest].visited) {
                queue[rear++] = edge->dest;
                graph->vertices[edge->dest].visited = true;
            }
        }
    }

    free(queue);
}

// Dijkstra's shortest path algorithm
double* graph_shortest_path(const Graph* graph, size_t source) {
    if (!graph || source >= graph->vertex_count) return NULL;

    double* distances = malloc(graph->vertex_count * sizeof(double));
    bool* visited = calloc(graph->vertex_count, sizeof(bool));
    
    if (!distances || !visited) {
        free(distances);
        free(visited);
        return NULL;
    }

    // Initialize distances
    for (size_t i = 0; i < graph->vertex_count; i++) {
        distances[i] = INFINITY;
    }
    distances[source] = 0;

    // Find shortest path for all vertices
    for (size_t count = 0; count < graph->vertex_count - 1; count++) {
        // Find minimum distance vertex
        double min = INFINITY;
        size_t min_vertex = 0;
        
        for (size_t v = 0; v < graph->vertex_count; v++) {
            if (!visited[v] && distances[v] <= min) {
                min = distances[v];
                min_vertex = v;
            }
        }

        visited[min_vertex] = true;

        // Update distances of adjacent vertices
        for (Edge* edge = graph->vertices[min_vertex].edges; edge; edge = edge->next) {
            if (!visited[edge->dest] && 
                distances[min_vertex] != INFINITY &&
                distances[min_vertex] + edge->weight < distances[edge->dest]) {
                distances[edge->dest] = distances[min_vertex] + edge->weight;
            }
        }
    }

    free(visited);
    return distances;
}
)";
