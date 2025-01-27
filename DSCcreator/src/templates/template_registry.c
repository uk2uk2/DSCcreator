#include "template_registry.h"
#include <string.h>

// Include all template headers
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "bst.h"
#include "heap.h"
#include "hashtable.h"
#include "graph.h"
#include "trie.h"
#include "rbtree.h"
#include "btree.h"

static TemplateEntry registry[DS_TYPE_COUNT] = {
    {
        .type = DS_TYPE_LIST,
        .name = "list",
        .template = {
            .header = LIST_TEMPLATE_H,
            .source = LIST_TEMPLATE_C,
            .test = LIST_TEST_TEMPLATE,
            .example = LIST_EXAMPLE_TEMPLATE,
            .thread_safe = NULL
        },
        .has_thread_safe = false
    },
    {
        .type = DS_TYPE_STACK,
        .name = "stack",
        .template = {
            .header = STACK_TEMPLATE_H,
            .source = STACK_TEMPLATE_C,
            .test = STACK_TEST_TEMPLATE,
            .example = STACK_EXAMPLE_TEMPLATE,
            .thread_safe = NULL
        },
        .has_thread_safe = false
    },
    // ... similar entries for other data structures
    {
        .type = DS_TYPE_GRAPH,
        .name = "graph",
        .template = {
            .header = GRAPH_TEMPLATE_H,
            .source = GRAPH_TEMPLATE_C,
            .test = GRAPH_TEST_TEMPLATE,
            .example = GRAPH_EXAMPLE_TEMPLATE,
            .thread_safe = GRAPH_THREAD_SAFE_TEMPLATE
        },
        .has_thread_safe = true
    }
};

void registry_init(void) {
    // Any initialization needed
}

const Template* registry_get_template(DSType type) {
    if (type >= DS_TYPE_COUNT) return NULL;
    return &registry[type].template;
}

const char* registry_get_type_name(DSType type) {
    if (type >= DS_TYPE_COUNT) return NULL;
    return registry[type].name;
}

bool registry_is_thread_safe_supported(DSType type) {
    if (type >= DS_TYPE_COUNT) return false;
    return registry[type].has_thread_safe;
}

void registry_list_templates(void) {
    printf("Available Data Structures:\n");
    for (int i = 0; i < DS_TYPE_COUNT; i++) {
        printf("- %s%s\n", 
               registry[i].name,
               registry[i].has_thread_safe ? " (thread-safe available)" : "");
    }
}
