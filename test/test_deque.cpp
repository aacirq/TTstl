#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

#include "stl_deque.h"
#include "stl_alloc.h"
#include "iterator.h"

using tt::deque;
using tt::alloc;

TEST(Deque, DefaultConstructor) {
    deque<int> deq;
    ASSERT_TRUE(deq.empty());
    ASSERT_EQ(deq.size(), 0);
    ASSERT_EQ(deq.begin(), deq.end());
}

TEST(Deque, ConstructWithOneParameter) {
    deque<int> deq(20);
    ASSERT_FALSE(deq.empty());
    ASSERT_EQ(deq.size(), 20);
    ASSERT_NE(deq.begin(), deq.end());
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(deq[i], 0);
    }
}

TEST(Deque, ConstructWithTwoParameters) {
    deque<int> ideq1(20, 9);
    ASSERT_FALSE(ideq1.empty());
    ASSERT_EQ(ideq1.size(), 20);
    ASSERT_NE(ideq1.begin(), ideq1.end());
    for (int i = 0; i < ideq1.size(); ++i) {
        EXPECT_EQ(ideq1[i], 9);
    }

    deque<int, alloc, 32> ideq(20, 9);
    ASSERT_FALSE(ideq.empty());
    ASSERT_EQ(ideq.size(), 20);
    ASSERT_NE(ideq.begin(), ideq.end());
    for (int i = 0; i < ideq.size(); ++i) {
        EXPECT_EQ(ideq[i], 9);
    }
}

TEST(Deque, SubscriptOperator) {
    deque<int> deq(20);
    for (int i = 0; i < deq.size(); ++i) {
        deq[i] = i;
    }
    ASSERT_EQ(deq.size(), 20);
    for (int i = 0; i < deq.size(); ++i) {
        EXPECT_EQ(deq[i], i);
    }
}

TEST(Deque, PushBack) {
    deque<int> deq;
    for (int i = 0; i < 10000; ++i) {
        deq.push_back(i);
    }
    ASSERT_EQ(deq.size(), 10000);
    for (int i = 0; i < deq.size(); ++i) {
        EXPECT_EQ(deq[i], i);
    }
}

TEST(Deque, PushFront) {
    deque<int> deq;
    for (int i = 0; i < 10000; ++i) {
        deq.push_front(i);
    }
    ASSERT_EQ(deq.size(), 10000);
    for (int i = 0; i < deq.size(); ++i) {
        EXPECT_EQ(deq[i], 9999-i);
    }
}

TEST(Deque, PopBack) {
    deque<int> deq;
    for (int i = 0; i < 10000; ++i) {
        deq.push_back(i);
    }
    for (int i = 0; i < 5000; ++i) {
        deq.pop_back();
    }
    ASSERT_EQ(deq.size(), 5000);
    for (int i = 0; i < deq.size(); ++i) {
        EXPECT_EQ(deq[i], i);
    }
}

TEST(Deque, PopFront) {
    deque<int> deq;
    for (int i = 0; i < 10000; ++i) {
        deq.push_front(i);
    }
    for (int i = 0; i < 2222; ++i) {
        deq.pop_front();
    }
    ASSERT_EQ(deq.size(), 10000-2222);
    for (int i = 0; i < deq.size(); ++i) {
        EXPECT_EQ(deq[i], 10000-2222-1-i);
    }
}

TEST(Deque, Clear) {
    deque<int> deq;
    for (int i = 0; i < 10000; ++i) {
        deq.push_back(i);
    }
    for (int i = 0; i < 10000; ++i) {
        deq.push_front(i);
    }
    deq.clear();
    ASSERT_TRUE(deq.empty());
    ASSERT_EQ(deq.size(), 0);
    ASSERT_EQ(deq.begin(), deq.end());
}

TEST(Deque, Erase1) {
    deque<int> deq;
    for (int i = 0; i < 100; ++i) {
        deq.push_back(i);
    }
    auto itr = deq.begin();
    advance(itr, 5);
    itr += 5;
    for (int i = 11; i < 100; ++i) {
        itr = deq.erase(itr);
        ASSERT_NE(itr, deq.end());
        EXPECT_EQ(*itr, i);
    }
    itr = deq.erase(itr);
    ASSERT_EQ(itr, deq.end());
    ASSERT_FALSE(deq.empty());
    ASSERT_EQ(deq.size(), 10);
}

TEST(Deque, Erase2) {
    deque<int> deq;
    for (int i = 0; i < 100; ++i) {
        deq.push_back(i);
    }
    auto first = deq.begin() + 10;
    auto last = deq.end();
    auto itr = deq.erase(first, last);
    ASSERT_EQ(itr, deq.end());
    ASSERT_FALSE(deq.empty());
    ASSERT_EQ(deq.size(), 10);
}

TEST(Deque, Insert) {
    deque<int> deq(100, 2);
    auto itr = deq.begin() + 10;
    for (int n = 0; n < 10; ++n) {
        for (int i = 9; i >= 0; --i) {
            itr = deq.insert(itr, i);
        }
        itr += 20;
    }
    ASSERT_EQ(deq.size(), 200);
    itr = deq.begin();
    for (int n = 0; n < 10; ++n) {
        for (int i = 0; i < 10; ++i) {
            ASSERT_NE(itr, deq.end());
            EXPECT_EQ(*itr++, 2);
        }
        for (int i = 0; i < 10; ++i) {
            ASSERT_NE(itr, deq.end());
            EXPECT_EQ(*itr++, i);
        }
    }
}