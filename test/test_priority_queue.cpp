#include <gtest/gtest.h>
#include <iostream>

#include "stl_priority_queue.h"

using std::cerr; using std::endl;
using tt::priority_queue;

TEST(PriorityQueue, Case1) {
    int ia[] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    priority_queue<int> ipq(ia, ia+9);
    ASSERT_EQ(ipq.size(), 9);

    for (int i = 0; i < ipq.size(); ++i) {
        EXPECT_EQ(ipq.top(), 9);
    }

    int res[] = {9, 8, 5, 4, 3, 3, 2, 1};
    for (int i = 0; i < sizeof(res)/sizeof(int); ++i) {
        EXPECT_EQ(ipq.top(), res[i]);
        ipq.pop();
    }
}