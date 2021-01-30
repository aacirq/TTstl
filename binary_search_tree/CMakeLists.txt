add_library(binary_search_tree bst.hpp)
set_target_properties(binary_search_tree PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(binary_search_tree 
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})