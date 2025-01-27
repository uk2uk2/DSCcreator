const char* GRAPH_THREAD_SAFE_C = R"(
#include "graph_ts.h"
#include <pthread.h>

TSGraph* ts_graph_create(size_t capacity, bool directed,
                        void (*destroy)(void*),
                        int (*compare)(const void*, const void*)) {
    TSGraph* graph = malloc(sizeof(TSGraph));
    if (!graph) return NULL;

    graph->vertices = calloc(capacity, sizeof(TSVertex));
    if (!graph->vertices) {
        free(graph);
        return NULL;
    }

    // Initialize mutexes and locks
    if (pthread_mutex_init(&graph->global_lock, NULL) != 0) {
        free(graph->vertices);
        free(graph);
        return NULL;
    }

    if (pthread_rwlock_init(&graph->traversal_lock, NULL) != 0) {
        pthread_mutex_destroy(&graph->global_lock);
        free(graph->vertices);
        free(graph);
        return NULL;
    }

    // Initialize vertex locks
    for (size_t i = 0; i < capacity; i++) {
        if (pthread_mutex_init(&graph->vertices[i].lock, NULL) != 0) {
            // Cleanup previously initialized mutexes
            while (i > 0) {
                pthread_mutex_destroy(&graph->vertices[--i].lock);
            }
            pthread_rwlock_destroy(&graph->traversal_lock);
            pthread_mutex_destroy(&graph->global_lock);
            free(graph->vertices);
            free(graph);
            return NULL;
        }
    }

    graph->vertex_count = 0;
    graph->capacity = capacity;
    graph->directed = directed;
    graph->destroy = destroy;
    graph->compare = compare;

    return graph;
}

void ts_graph_destroy(TSGraph* graph) {
    if (!graph) return;

    pthread_mutex_lock(&graph->global_lock);

    for (size_t i = 0; i < graph->vertex_count; i++) {
        pthread_mutex_lock(&graph->vertices[i].lock);
        
        if (graph->destroy) {
            graph->destroy(graph->vertices[i].data);
        }
        
        TSEdge* edge = graph->vertices[i].edges;
        while (edge) {
            TSEdge* next = edge->next;
            pthread_mutex_destroy(&edge->lock);
            free(edge);
            edge = next;
        }
        
        pthread_mutex_unlock(&graph->vertices[i].lock);
        pthread_mutex_destroy(&graph->vertices[i].lock);
    }

    pthread_rwlock_destroy(&graph->traversal_lock);
    pthread_mutex_destroy(&graph->global_lock);
    free(graph->vertices);
    free(graph);
}

int ts_graph_add_vertex(TSGraph* graph, void* data) {
    if (!graph) return DS_ERROR;

    pthread_mutex_lock(&graph->global_lock);

    if (graph->vertex_count >= graph->capacity) {
        pthread_mutex_unlock(&graph->global_lock);
        return DS_ERROR;
    }

    size_t index = graph->vertex_count++;
    graph->vertices[index].data = data;
    graph->vertices[index].edges = NULL;
    graph->vertices[index].visited = false;

    pthread_mutex_unlock(&graph->global_lock);
    return DS_OK;
}

static TSEdge* ts_create_edge(size_t dest, double weight) {
    TSEdge* edge = malloc(sizeof(TSEdge));
    if (!edge) return NULL;

    if (pthread_mutex_init(&edge->lock, NULL) != 0) {
        free(edge);
        return NULL;
    }

    edge->dest = dest;
    edge->weight = weight;
    edge->next = NULL;

    return edge;
}

int ts_graph_add_edge(TSGraph* graph, size_t source, size_t dest, double weight) {
    if (!graph) return DS_ERROR;

    pthread_mutex_lock(&graph->global_lock);
    
    if (source >= graph->vertex_count || dest >= graph->vertex_count) {
        pthread_mutex_unlock(&graph->global_lock);
        return DS_ERROR;
    }

    // Lock vertices in order to prevent deadlock
    if (source < dest) {
        pthread_mutex_lock(&graph->vertices[source].lock);
        pthread_mutex_lock(&graph->vertices[dest].lock);
    } else {
        pthread_mutex_lock(&graph->vertices[dest].lock);
        pthread_mutex_lock(&graph->vertices[source].lock);
    }

    // Add edge from source to dest
    TSEdge* edge = ts_create_edge(dest, weight);
    if (!edge) {
        pthread_mutex_unlock(&graph->vertices[source].lock);
        pthread_mutex_unlock(&graph->vertices[dest].lock);
        pthread_mutex_unlock(&graph->global_lock);
        return DS_ERROR;
    }

    edge->next = graph->vertices[source].edges;
    graph->vertices[source].edges = edge;

    // If undirected, add edge from dest to source
    if (!graph->directed) {
        edge = ts_create_edge(source, weight);
        if (!edge) {
            pthread_mutex_unlock(&graph->vertices[source].lock);
            pthread_mutex_unlock(&graph->vertices[dest].lock);
            pthread_mutex_unlock(&graph->global_lock);
            return DS_ERROR;
        }

        edge->next = graph->vertices[dest].edges;
        graph->vertices[dest].edges = edge;
    }

    pthread_mutex_unlock(&graph->vertices[source].lock);
    pthread_mutex_unlock(&graph->vertices[dest].lock);
    pthread_mutex_unlock(&graph->global_lock);

    return DS_OK;
}

// ... more thread-safe implementations
)";
