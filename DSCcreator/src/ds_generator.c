#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>

// Version and metadata
#define DS_GEN_VERSION "1.0.0"
#define AUTHOR "Generated by DS-Generator"
#define LICENSE "MIT License"

// Structure types
typedef enum {
    DS_LIST,
    DS_STACK,
    DS_QUEUE,
    DS_BST,
    DS_AVL,
    DS_HEAP,
    DS_HASHTABLE,
    DS_GRAPH,
    DS_TRIE,
    DS_RBTREE,
    DS_COUNT,
    DS_SKIPLIST
} DSType;

// Template components
typedef struct {
    const char* header;     // Header file template
    const char* source;     // Source file template
    const char* test;       // Unit test template
    const char* example;    // Example usage template
    const char* thread;     // Thread-safe version template
    const char* benchmark;  // Benchmark template
} DSTemplate;

// Project structure
typedef struct {
    char name[256];
    DSType type;
    bool thread_safe;
    bool include_tests;
    bool include_benchmark;
} DSProject;

// Utility functions
void create_project_structure(const DSProject* project) {
    char cmd[512];
    
    // Create main project directory
    snprintf(cmd, sizeof(cmd), "mkdir -p %s/{src,include,tests,examples,bench}", 
             project->name);
    system(cmd);
    
    // Create build directory
    snprintf(cmd, sizeof(cmd), "mkdir -p %s/build", project->name);
    system(cmd);
}

// Generate common headers
void generate_common_headers(const char* project_path) {
    char filepath[512];
    FILE* file;

    // ds_common.h
    snprintf(filepath, sizeof(filepath), "%s/include/ds_common.h", project_path);
    file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "%s", COMMON_HEADER_TEMPLATE);
        fclose(file);
    }

    // ds_thread.h
    snprintf(filepath, sizeof(filepath), "%s/include/ds_thread.h", project_path);
    file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "%s", THREAD_HEADER_TEMPLATE);
        fclose(file);
    }
}

// CMake generation
void generate_cmake(const DSProject* project) {
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/CMakeLists.txt", project->name);
    
    FILE* file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "cmake_minimum_required(VERSION 3.10)\n");
        fprintf(file, "project(%s VERSION 1.0)\n\n", project->name);
        fprintf(file, "set(CMAKE_C_STANDARD 11)\n");
        fprintf(file, "set(CMAKE_C_STANDARD_REQUIRED ON)\n\n");
        
        // Add compilation flags
        fprintf(file, "add_compile_options(-Wall -Wextra -Wpedantic)\n\n");
        
        // Add threading if needed
        if (project->thread_safe) {
            fprintf(file, "find_package(Threads REQUIRED)\n\n");
        }
        
        // Add library
        fprintf(file, "add_library(${PROJECT_NAME} STATIC\n");
        fprintf(file, "    src/%s.c\n", project->name);
        fprintf(file, ")\n\n");
        
        // Add tests if needed
        if (project->include_tests) {
            fprintf(file, "enable_testing()\n");
            fprintf(file, "add_subdirectory(tests)\n");
        }
        
        fclose(file);
    }
}
