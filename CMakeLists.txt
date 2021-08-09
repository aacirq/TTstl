cmake_minimum_required(VERSION 3.10)

project(TTstl)

include_directories({PROJECT_SOURCE_DIR}/include)

add_executable(test1 test/test.cpp)

set(CMAKE_CXX_STANDARD 11)
