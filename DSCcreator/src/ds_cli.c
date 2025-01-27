const char* CLI_TEMPLATE_C = R"(
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ds_generator.h"
#include "file_utils.h"
#include "string_utils.h"

#define VERSION "1.0.0"

static void print_usage(void) {
    printf("DSCcreator v%s - Data Structure Code Generator\n\n", VERSION);
    printf("Usage:\n");
    printf("  dsc create <type> <name> [options]\n");
    printf("  dsc list\n");
    printf("  dsc info <type>\n");
    printf("  dsc benchmark <type>\n");
    printf("\nTypes:\n");
    printf("  list       - Linked List\n");
    printf("  stack      - Stack\n");
    printf("  queue      - Queue\n");
    printf("  bst        - Binary Search Tree\n");
    printf("  avl        - AVL Tree\n");
    printf("  rbtree     - Red-Black Tree\n");
    printf("  heap       - Binary Heap\n");
    printf("  hashtable  - Hash Table\n");
    printf("  graph      - Graph\n");
    printf("  trie       - Trie\n");
    printf("\nOptions:\n");
    printf("  --thread-safe  Generate thread-safe version\n");
    printf("  --with-tests   Generate test files\n");
    printf("  --with-bench   Generate benchmark files\n");
    printf("  --output=DIR   Output directory (default: current)\n");
}

static void list_templates(void) {
    printf("Available Data Structure Templates:\n\n");
    registry_list_templates();
}

static void show_info(const char* type) {
    DSType ds_type = DS_TYPE_COUNT;
    
    // Convert string to DSType
    for (int i = 0; i < DS_TYPE_COUNT; i++) {
        if (strcmp(type, registry_get_type_name(i)) == 0) {
            ds_type = i;
            break;
        }
    }
    
    if (ds_type == DS_TYPE_COUNT) {
        printf("Error: Unknown data structure type '%s'\n", type);
        return;
    }
    
    const Template* tmpl = registry_get_template(ds_type);
    if (!tmpl) {
        printf("Error: Template not found for type '%s'\n", type);
        return;
    }
    
    printf("Data Structure: %s\n", type);
    printf("Thread-safe version available: %s\n",
           registry_is_thread_safe_supported(ds_type) ? "Yes" : "No");
    printf("\nFiles generated:\n");
    printf("- Header file (.h)\n");
    printf("- Implementation file (.c)\n");
    printf("- Test file (optional)\n");
    printf("- Benchmark file (optional)\n");
}

static void run_benchmark(const char* type) {
    DSType ds_type = DS_TYPE_COUNT;
    
    // Convert string to DSType
    for (int i = 0; i < DS_TYPE_COUNT; i++) {
        if (strcmp(type, registry_get_type_name(i)) == 0) {
            ds_type = i;
            break;
        }
    }
    
    if (ds_type == DS_TYPE_COUNT) {
        printf("Error: Unknown data structure type '%s'\n", type);
        return;
    }
    
    printf("Running benchmarks for %s...\n", type);
    
    Benchmark* bench = benchmark_create(type);
    benchmark_start(bench);
    
    // Run specific benchmarks based on type
    switch (ds_type) {
        case DS_TYPE_LIST:
            // List benchmark implementation
            break;
        case DS_TYPE_STACK:
            // Stack benchmark implementation
            break;
        // ... other cases
    }
    
    benchmark_stop(bench);
    benchmark_report(bench);
    benchmark_destroy(bench);
}

static int create_structure(const char* type, const char* name, 
                          const char* output_dir, bool thread_safe,
                          bool with_tests, bool with_bench) {
    DSType ds_type = DS_TYPE_COUNT;
    
    // Convert string to DSType
    for (int i = 0; i < DS_TYPE_COUNT; i++) {
        if (strcmp(type, registry_get_type_name(i)) == 0) {
            ds_type = i;
            break;
        }
    }
    
    if (ds_type == DS_TYPE_COUNT) {
        printf("Error: Unknown data structure type '%s'\n", type);
        return 1;
    }
    
    // Create output directory if it doesn't exist
    if (output_dir && !create_directory(output_dir)) {
        printf("Error: Failed to create output directory '%s'\n", output_dir);
        return 1;
    }
    
    // Generate files
    const Template* tmpl = registry_get_template(ds_type);
    if (!tmpl) {
        printf("Error: Template not found for type '%s'\n", type);
        return 1;
    }
    
    char path[256];
    
    // Generate header file
    snprintf(path, sizeof(path), "%s/%s.h", 
             output_dir ? output_dir : ".", name);
    if (!write_template_to_file(path, tmpl->header)) {
        printf("Error: Failed to write header file\n");
        return 1;
    }
    
    // Generate source file
    snprintf(path, sizeof(path), "%s/%s.c", 
             output_dir ? output_dir : ".", name);
    if (!write_template_to_file(path, tmpl->source)) {
        printf("Error: Failed to write source file\n");
        return 1;
    }
    
    // Generate thread-safe version if requested
    if (thread_safe && tmpl->thread_safe) {
        snprintf(path, sizeof(path), "%s/%s_ts.h", 
                 output_dir ? output_dir : ".", name);
        if (!write_template_to_file(path, tmpl->thread_safe)) {
            printf("Error: Failed to write thread-safe header file\n");
            return 1;
        }
    }
    
    // Generate test file if requested
    if (with_tests && tmpl->test) {
        snprintf(path, sizeof(path), "%s/test_%s.c", 
                 output_dir ? output_dir : ".", name);
        if (!write_template_to_file(path, tmpl->test)) {
            printf("Error: Failed to write test file\n");
            return 1;
        }
    }
    
    printf("Successfully generated files for %s\n", name);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }
    
    if (strcmp(argv[1], "list") == 0) {
        list_templates();
        return 0;
    }
    
    if (strcmp(argv[1], "info") == 0) {
        if (argc < 3) {
            printf("Error: Missing type argument\n");
            return 1;
        }
        show_info(argv[2]);
        return 0;
    }
    
    if (strcmp(argv[1], "benchmark") == 0) {
        if (argc < 3) {
            printf("Error: Missing type argument\n");
            return 1;
        }
        run_benchmark(argv[2]);
        return 0;
    }
    
    if (strcmp(argv[1], "create") == 0) {
        if (argc < 4) {
            printf("Error: Missing type or name argument\n");
            return 1;
        }
        
        const char* type = argv[2];
        const char* name = argv[3];
        const char* output_dir = NULL;
        bool thread_safe = false;
        bool with_tests = false;
        bool with_bench = false;
        
        // Parse options
        for (int i = 4; i < argc; i++) {
            if (strcmp(argv[i], "--thread-safe") == 0) {
                thread_safe = true;
            } else if (strcmp(argv[i], "--with-tests") == 0) {
                with_tests = true;
            } else if (strcmp(argv[i], "--with-bench") == 0) {
                with_bench = true;
            } else if (strncmp(argv[i], "--output=", 9) == 0) {
                output_dir = argv[i] + 9;
            }
        }
        
        return create_structure(type, name, output_dir, 
                              thread_safe, with_tests, with_bench);
    }
    
    print_usage();
    return 1;
}
)";
