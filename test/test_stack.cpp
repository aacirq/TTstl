#include <iostream>
#include <list>

#include <gtest/gtest.h>

#include "stl_stack.h"
#include "stl_list.h"

using std::cout;
using std::endl;
using tt::stack;

TEST(Stack, General) {
    stack<int> istack;
    for (int i = 0; i < 5; ++i) {
        istack.push(i);
    }
    ASSERT_FALSE(istack.empty());
    ASSERT_EQ(istack.size(), 5);
    ASSERT_EQ(istack.top(), 4);

    for (int i = 3; i >= 0; --i) {
        istack.pop();
        EXPECT_EQ(istack.top(), i);
    }

    ASSERT_EQ(istack.size(), 1);

    istack.pop();
    ASSERT_TRUE(istack.empty());
}

TEST(Stack, ByTTList) {
    stack<int, tt::list<int>> istack;
    for (int i = 0; i < 5; ++i) {
        istack.push(i);
    }
    ASSERT_FALSE(istack.empty());
    ASSERT_EQ(istack.size(), 5);
    ASSERT_EQ(istack.top(), 4);

    for (int i = 3; i >= 0; --i) {
        istack.pop();
        EXPECT_EQ(istack.top(), i);
    }

    ASSERT_EQ(istack.size(), 1);

    istack.pop();
    ASSERT_TRUE(istack.empty());
}

TEST(Stack, ByStdList) {
    stack<int, std::list<int>> istack;
    for (int i = 0; i < 5; ++i) {
        istack.push(i);
    }
    ASSERT_FALSE(istack.empty());
    ASSERT_EQ(istack.size(), 5);
    ASSERT_EQ(istack.top(), 4);

    for (int i = 3; i >= 0; --i) {
        istack.pop();
        EXPECT_EQ(istack.top(), i);
    }

    ASSERT_EQ(istack.size(), 1);

    istack.pop();
    ASSERT_TRUE(istack.empty());
}