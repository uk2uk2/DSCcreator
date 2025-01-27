#ifndef DS_GENERATOR_H
#define DS_GENERATOR_H

#include "ds_common.h"

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
} DSType;

// Project configuration
typedef struct {
    char name[256];
    DSType type;
    bool thread_safe;
    bool include_tests;
    bool include_benchmark;
} DSProject;

// Function declarations
void create_project_structure(const DSProject* project);
void generate_common_headers(const char* project_path);
void generate_cmake(const DSProject* project);

#endif // DS_GENERATOR_H
