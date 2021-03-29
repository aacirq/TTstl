# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Now simply link against gtest or gtest_main as needed. Eg

cmake_minimum_required(VERSION 3.15)
project(tt_stl)

# Test of test/complex_class.h
add_executable(test_complex_class test/test_complex_class.cpp)
target_link_libraries(test_complex_class gtest_main)

# Test of include/stl_algobase.h
add_executable(test_algobase test/test_algobase.cpp)
target_include_directories(test_algobase
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(test_algobase gtest_main)

# Test of include/stl_vector.h
add_executable(test_vector test/test_vector.cpp)
target_include_directories(test_vector
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(test_vector gtest_main)

# Test of include/stl_list.h
add_executable(test_list test/test_list.cpp)
target_include_directories(test_list
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(test_list gtest_main)

# Test of include/stl_deque.h
add_executable(test_deque test/test_deque.cpp)
target_include_directories(test_deque
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(test_deque gtest_main)

# Test of include/stl_stack.h
add_executable(test_stack test/test_stack.cpp)
target_include_directories(test_stack
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(test_stack gtest_main)

# Test of include/stl_squeue.h
add_executable(test_queue test/test_queue.cpp)
target_include_directories(test_queue
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(test_queue gtest_main)

# Tmp test
add_executable(test_tmp test/test_tmp.cpp)
target_include_directories(test_tmp
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(test_tmp gtest_main)

add_test(
    NAME TEST_STL 
    COMMAND test_complex_class test_algobase test_vector test_list test_deque test_stack
)