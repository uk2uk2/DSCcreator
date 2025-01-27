#ifndef DS_BENCHMARK_H
#define DS_BENCHMARK_H

#include "ds_common.h"
#include <time.h>

typedef struct {
    const char* name;
    clock_t start_time;
    clock_t end_time;
    size_t operations;
    size_t data_size;
} Benchmark;

Benchmark* benchmark_create(const char* name);
void benchmark_start(Benchmark* b);
void benchmark_stop(Benchmark* b);
void benchmark_set_operations(Benchmark* b, size_t ops);
void benchmark_set_data_size(Benchmark* b, size_t size);
void benchmark_report(const Benchmark* b);

// Benchmark suite
typedef struct {
    Benchmark** benchmarks;
    size_t count;
    size_t capacity;
} BenchmarkSuite;

BenchmarkSuite* suite_create(void);
void suite_add_benchmark(BenchmarkSuite* suite, Benchmark* b);
void suite_run_all(BenchmarkSuite* suite);
void suite_report_all(const BenchmarkSuite* suite);

#endif // DS_BENCHMARK_H
