cmake_minimum_required(VERSION 3.10)
project(DSCcreator VERSION 1.0.0 LANGUAGES C)

# Options
option(BUILD_TESTS "Build test suite" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# Find required packages
find_package(Threads REQUIRED)

# Set compilation flags
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main library
add_library(dsccreator
    src/ds_generator.c
    src/utils/file_utils.c
    src/benchmark/benchmark.c
    src/templates/list.c
    src/templates/stack.c
    src/templates/queue.c
    src/templates/bst.c
    src/templates/avl.c
    src/templates/heap.c
    src/templates/hashtable.c
    src/templates/graph.c
    src/templates/trie.c
    src/templates/rbtree.c
    # Add all template source files
)
# CLI Executable
add_executable(dsc src/ds_cli.c)
target_link_libraries(dsc PRIVATE dsccreator ${CMAKE_THREAD_LIBS_INIT})

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation
install(TARGETS dsc dsccreator
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include/dsccreator)

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif():
