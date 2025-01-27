#ifndef TEMPLATE_REGISTRY_H
#define TEMPLATE_REGISTRY_H

#include "ds_common.h"

typedef enum {
    DS_TYPE_LIST,
    DS_TYPE_STACK,
    DS_TYPE_QUEUE,
    DS_TYPE_BST,
    DS_TYPE_HEAP,
    DS_TYPE_HASHTABLE,
    DS_TYPE_GRAPH,
    DS_TYPE_TRIE,
    DS_TYPE_RBTREE,
    DS_TYPE_BTREE,
    DS_TYPE_COUNT
} DSType;

typedef struct {
    const char* header;
    const char* source;
    const char* test;
    const char* example;
    const char* thread_safe;  // Optional thread-safe version
} Template;

typedef struct {
    DSType type;
    const char* name;
    Template template;
    bool has_thread_safe;
} TemplateEntry;

// Core registry operations
void registry_init(void);
const Template* registry_get_template(DSType type);
const char* registry_get_type_name(DSType type);
bool registry_is_thread_safe_supported(DSType type);

// Utility functions
void registry_list_templates(void);
const char* registry_get_template_path(DSType type, const char* suffix);

#endif // TEMPLATE_REGISTRY_H
