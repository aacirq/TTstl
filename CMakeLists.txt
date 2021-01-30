cmake_minimum_required(VERSION 3.10)
project(TTAlgorithm)

set(CMAKE_CXX_STANDARD 11)

# aux_source_directory(. DIR_SRC)

# add new folder
# include_directories(./ ./binary_search_tree)

# add subdir
add_subdirectory(binary_search_tree)

# append libs
list(APPEND EXTRA_LIBS binary_search_tree)

# add_executable(TTAlgorithm main.cpp)

# link libs
# target_link_libraries(TTAlgorithm PUBLIC ${EXTRA_LIBS})


# ==============================================================================
# cmake_minimum_required(VERSION 2.8.9)
# project(utest)
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)

# The gtest/gmock targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we
# have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include"
    )
endif()

# add_executable(utest utest.cpp)
add_executable(TTAlgorithm main.cpp)
# target_link_libraries(TTAlgorithm PUBLIC ${EXTRA_LIBS})
target_link_libraries(TTAlgorithm gtest gtest_main)
enable_testing()