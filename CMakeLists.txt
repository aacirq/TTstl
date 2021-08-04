cmake_minimum_required(VERSION 3.10)

project(TTstl)

add_executable(test1 test/test.cpp)
target_include_directories(test1 PRIVATE ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 11)
