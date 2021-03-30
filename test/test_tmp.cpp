#include <iostream>

#include "stl_list.h"
#include "stl_vector.h"
#include "stl_deque.h"

using std::cout; using std::endl;

using tt::list;
using tt::vector;
using tt::deque;

int main() {
    deque<int> deq;
    for (int i = 0; i < 130; ++i) {
        deq.push_back(i);
    }
    return 0;
}