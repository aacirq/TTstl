cmake_minimum_required(VERSION 3.15)

project(tt_stl)

add_executable(test_algobase test/test_algobase.cpp)
target_include_directories(test_algobase
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include)


add_executable(test_vector test/test_vector.cpp)
target_include_directories(test_vector
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include)


add_executable(test_list test/test_list.cpp)
target_include_directories(test_list
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)