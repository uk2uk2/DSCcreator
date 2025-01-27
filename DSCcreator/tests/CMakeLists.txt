# Tests CMakeLists.txt
# Unity Test Framework
include(FetchContent)
FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(unity)

# Tests CMakeLists.txt
enable_testing()

# Add Unity test framework
add_subdirectory(unity)

# Add test executables
add_executable(test_list test_list.c)
target_link_libraries(test_list PRIVATE dsccreator unity)
add_test(NAME test_list COMMAND test_list)

add_executable(test_bst test_bst.c)
target_link_libraries(test_bst PRIVATE dsccreator unity)
add_test(NAME test_bst COMMAND test_bst)

add_executable(test_hashtable test_hashtable.c)
target_link_libraries(test_hashtable PRIVATE dsccreator unity)
add_test(NAME test_hashtable COMMAND test_hashtable)

# Thread-safe tests
add_executable(test_thread_safe test_thread_safe.c)
target_link_libraries(test_thread_safe PRIVATE dsccreator unity ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME test_thread_safe COMMAND test_thread_safe)

# Install test executables
install(TARGETS test_list test_bst test_hashtable test_thread_safe
    RUNTIME DESTINATION share/dsccreator/tests)
