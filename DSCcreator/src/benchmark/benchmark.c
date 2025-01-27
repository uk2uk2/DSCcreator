const char* BENCHMARK_TEMPLATE_C = R"(
#include "benchmark.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    const char* name;
    double duration;
    size_t operations;
    size_t memory_used;
    double ops_per_second;
} BenchmarkResult;

static BenchmarkResult* results = NULL;
static size_t result_count = 0;
static size_t result_capacity = 0;

static void add_result(BenchmarkResult result) {
    if (result_count >= result_capacity) {
        size_t new_capacity = result_capacity == 0 ? 16 : result_capacity * 2;
        BenchmarkResult* new_results = realloc(results, 
                                             new_capacity * sizeof(BenchmarkResult));
        if (!new_results) return;
        
        results = new_results;
        result_capacity = new_capacity;
    }
    
    results[result_count++] = result;
}

Benchmark* benchmark_create(const char* name) {
    Benchmark* b = malloc(sizeof(Benchmark));
    if (!b) return NULL;
    
    b->name = strdup(name);
    b->start_time = 0;
    b->end_time = 0;
    b->operations = 0;
    b->memory_used = 0;
    
    return b;
}

void benchmark_destroy(Benchmark* b) {
    if (!b) return;
    free((void*)b->name);
    free(b);
}

void benchmark_start(Benchmark* b) {
    if (!b) return;
    b->start_time = clock();
}

void benchmark_stop(Benchmark* b) {
    if (!b) return;
    b->end_time = clock();
    
    double duration = ((double)(b->end_time - b->start_time)) / CLOCKS_PER_SEC;
    double ops_per_second = b->operations / duration;
    
    BenchmarkResult result = {
        .name = b->name,
        .duration = duration,
        .operations = b->operations,
        .memory_used = b->memory_used,
        .ops_per_second = ops_per_second
    };
    
    add_result(result);
}

void benchmark_report(const Benchmark* b) {
    if (!b) return;
    
    double duration = ((double)(b->end_time - b->start_time)) / CLOCKS_PER_SEC;
    double ops_per_second = b->operations / duration;
    
    printf("\nBenchmark: %s\n", b->name);
    printf("Duration: %.4f seconds\n", duration);
    printf("Operations: %zu\n", b->operations);
    printf("Memory used: %zu bytes\n", b->memory_used);
    printf("Operations per second: %.2f\n", ops_per_second);
}

void benchmark_summary(void) {
    if (!results || result_count == 0) return;
    
    printf("\nBenchmark Summary\n");
    printf("================\n\n");
    
    for (size_t i = 0; i < result_count; i++) {
        printf("%-20s: %.4f sec, %zu ops, %.2f ops/sec, %zu bytes\n",
               results[i].name,
               results[i].duration,
               results[i].operations,
               results[i].ops_per_second,
               results[i].memory_used);
    }
}

void benchmark_cleanup(void) {
    free(results);
    results = NULL;
    result_count = 0;
    result_capacity = 0;
}
)";
