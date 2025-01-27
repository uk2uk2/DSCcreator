# Examples CMakeLists.txt
add_executable(data_structure_examples data_structure_examples.c)
target_link_libraries(data_structure_examples PRIVATE dsccreator)

add_executable(thread_safe_examples thread_safe_examples.c)
target_link_libraries(thread_safe_examples PRIVATE dsccreator ${CMAKE_THREAD_LIBS_INIT})

# Install examples
install(TARGETS data_structure_examples thread_safe_examples
    RUNTIME DESTINATION share/dsccreator/examples)
