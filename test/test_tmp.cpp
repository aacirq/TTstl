#include "stl_list.h"
#include "stl_vector.h"

using tt::list;
using tt::vector;

int main() {
    vector<int> vec(500, 0);
    for (int i = 0; i < 1000000; ++i) {
        vec.push_back(i);
    }
    return 0;
}