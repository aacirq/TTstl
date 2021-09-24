add_executable(hello_gtest gtest_test.cpp)
target_link_libraries(hello_gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(hello_gtest)
