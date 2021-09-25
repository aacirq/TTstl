include_directories({PROJECT_SOURCE_DIR}/include)

add_executable(hello_gtest gtest_test.cpp)
target_link_libraries(hello_gtest gtest_main)

add_executable(iterator_test iterator_test.cpp)
target_link_libraries(iterator_test gtest_main)
target_include_directories(iterator_test PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(hello_gtest)
gtest_discover_tests(iterator_test)
