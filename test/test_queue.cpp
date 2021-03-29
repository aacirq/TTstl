#include <list>

#include <gtest/gtest.h>

#include "stl_queue.h"
#include "stl_list.h"

using tt::queue;

TEST(Queue, General) {
    queue<int> iqueue;
    for (int i = 0; i < 5; ++i) {
        iqueue.push(i);
    }

    ASSERT_FALSE(iqueue.empty());
    EXPECT_EQ(iqueue.front(), 0);

    for (int i = 1; i < 5; ++i) {
        iqueue.pop();
        ASSERT_FALSE(iqueue.empty());
        EXPECT_EQ(iqueue.front(), i);
    }

    iqueue.pop();
    ASSERT_TRUE(iqueue.empty());
}

TEST(Queue, ByTTList) {
    queue<int, tt::list<int>> iqueue;
    for (int i = 0; i < 5; ++i) {
        iqueue.push(i);
    }

    ASSERT_FALSE(iqueue.empty());
    EXPECT_EQ(iqueue.front(), 0);

    for (int i = 1; i < 5; ++i) {
        iqueue.pop();
        ASSERT_FALSE(iqueue.empty());
        EXPECT_EQ(iqueue.front(), i);
    }

    iqueue.pop();
    ASSERT_TRUE(iqueue.empty());
}

TEST(Queue, ByStdList) {
    queue<int, std::list<int>> iqueue;
    for (int i = 0; i < 5; ++i) {
        iqueue.push(i);
    }

    ASSERT_FALSE(iqueue.empty());
    EXPECT_EQ(iqueue.front(), 0);

    for (int i = 1; i < 5; ++i) {
        iqueue.pop();
        ASSERT_FALSE(iqueue.empty());
        EXPECT_EQ(iqueue.front(), i);
    }

    iqueue.pop();
    ASSERT_TRUE(iqueue.empty());
}