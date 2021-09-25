cmake_minimum_required(VERSION 3.10)

project(TTstl)

set(CMAKE_CXX_STANDARD 11)


##############################################
## Add GoogleTest Support ##
##############################################
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


##############################################
## Link GoogleTest to directory test_cases ##
##############################################
enable_testing()

add_subdirectory(test)


##############################################
##
##############################################
include_directories({PROJECT_SOURCE_DIR}/include)
