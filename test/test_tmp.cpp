#include <iostream>

#include "stl_list.h"
#include "stl_vector.h"
#include "stl_deque.h"

using std::cout; using std::endl;

using tt::list;
using tt::vector;
using tt::deque;

int main() {
    int ia[] = {0, 1, 2, 3, 4, 5};
    // vector<int> vec;
    // int *first = ia;
    // int *last = ia + 6;
    
    // for (; first != last; ++first) {
    //     vec.push_back(*first);
    // }

    
    vector<int> vec(ia, ia + 6);
    return 0;
}