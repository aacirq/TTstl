#include <iostream>

#include <gtest/gtest.h>

#include "stl_list.h"
#include "iterator.h"

using tt::list;
using tt::advance;

TEST(List, Constructor) {
    list<int> l;
    ASSERT_TRUE(l.empty());
    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.begin(), l.end());

    const list<int> cl;
    ASSERT_TRUE(cl.empty());
    ASSERT_EQ(cl.size(), 0);
    ASSERT_EQ(cl.begin(), cl.end());
}

TEST(List, PushBack) {
    list<int> l;
    for (int i = 0; i < 5000; ++i) {
        l.push_back(i);
    }

    ASSERT_FALSE(l.empty());
    ASSERT_EQ(l.size(), 5000);
    auto itr = l.begin();
    for (int i = 0; i < 5000; ++i) {
        ASSERT_NE(itr, l.end());
        EXPECT_EQ(*itr, i);
        ++itr;
    }
}

TEST(List, PushFront) {
    list<int> l;
    for (int i = 0; i < 5000; ++i) {
        l.push_front(i);
    }

    ASSERT_FALSE(l.empty());
    ASSERT_EQ(l.size(), 5000);
    auto itr = l.begin();
    for (int i = 4999; i >= 0; --i) {
        ASSERT_NE(itr, l.end());
        EXPECT_EQ(*itr, i);
        ++itr;
    }
}

TEST(List, Insert) {
    list<int> l;
    for (int i = 0; i < 500; ++i) {
        l.push_back(i);
    }

    auto itr = l.begin();
    for (int i = 0; i < 4; ++i) {
        advance(itr, 100);
        ASSERT_NE(itr, l.end());
        auto in_itr = l.insert(itr, 2222);
        ASSERT_NE(in_itr, l.end());
        EXPECT_EQ(*in_itr, 2222);
    }

    ASSERT_EQ(l.size(), 504);

    itr = l.begin();
    for (int n = 0; n < 4; ++n) {
        for (int i = 0; i < 100; ++i) {
            ASSERT_NE(itr, l.end());
            EXPECT_EQ(*itr++, i + n*100);
        }
        ASSERT_NE(itr, l.end());
        EXPECT_EQ(*itr, 2222);
    }
    for (int i = 0; i < 100; ++i) {
        ASSERT_NE(itr, l.end());
        EXPECT_EQ(*itr++, i+400);
    }
    ASSERT_EQ(itr, l.end());
}

TEST(List, Erase) {
    list<int> l;
    for (int i = 0; i < 500; ++i) {
        l.push_back(i);
    }

    auto itr = l.begin();
    ++itr;
    for (int i = 0; i < 4; ++i) {
        advance(itr, 99);
        ASSERT_NE(itr, l.end());
        itr = l.erase(itr);
        ASSERT_NE(itr, l.end());
    }

    ASSERT_FALSE(l.empty());
    ASSERT_EQ(l.size(), 496);

    itr = l.begin();
    ASSERT_NE(itr, l.end());
    EXPECT_EQ(*itr++, 0);
    for (int n = 0; n < 5; ++n) {
        for (int i = 0; i < 99; ++i) {
            ASSERT_NE(itr, l.end());
            EXPECT_EQ(*itr++, i + n*100 + 1);
        }
    }
    ASSERT_EQ(itr, l.end());
}

TEST(List, Clear) {
    list<int> l;
    for (int i = 0; i < 2500; ++i) {
        l.push_back(i);
    }
    for (int i = 0; i < 2500; ++i) {
        l.push_front(i);
    }
    l.clear();
    ASSERT_TRUE(l.empty());
    ASSERT_EQ(l.size(), 0);
}

TEST(List, remove) {
    list<int> l;
    for (int i = 0; i < 500; ++i) {
        l.push_back(i);
    }
    for (int i = 0; i < 500; i += 100) {
        l.remove(i);
    }

    ASSERT_FALSE(l.empty());
    ASSERT_EQ(l.size(), 495);

    auto itr = l.begin();
    for (int n = 0; n < 5; ++n) {
        for (int i = 1; i < 100; ++i) {
            ASSERT_NE(itr, l.end());
            EXPECT_EQ(*itr++, i + n*100);
        }
    }
    ASSERT_EQ(itr, l.end());
}

TEST(List, Unique) {
    list<int> l;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 10; ++j) {
            l.push_back(i);
        }
    }

    l.unique();
    ASSERT_FALSE(l.empty());
    ASSERT_EQ(l.size(), 100);

    auto itr = l.begin();
    for (int i = 0; i < 100; ++i) {
        ASSERT_NE(itr, l.end());
        EXPECT_EQ(*itr++, i);
    }
    ASSERT_EQ(itr, l.end());
}

TEST(List, Reverse) {
    list<int> l;
    for (int i = 0; i < 1000; ++i) {
        l.push_back(i);
    }

    l.reverse();

    ASSERT_FALSE(l.empty());
    ASSERT_EQ(l.size(), 1000);

    auto itr = l.begin();
    for (int i = 999; i >= 0; --i) {
        ASSERT_NE(itr, l.end());
        EXPECT_EQ(*itr++, i);
    }
    ASSERT_EQ(itr, l.end());
}

TEST(List, Merge) {
    list<int> l1;
    for (int i = 0; i < 100; i += 2) {
        l1.push_back(i);
    }
    list<int> l2;
    for (int i = 1; i < 100; i += 2) {
        l2.push_back(i);
    }
    for (int i = 100; i < 200; ++i) {
        l2.push_back(i);
    }
    l1.merge(l2);

    ASSERT_TRUE(l2.empty());
    ASSERT_FALSE(l1.empty());
    ASSERT_EQ(l1.size(), 200);

    auto itr = l1.begin();
    for (int i = 0; i < 200; ++i) {
        ASSERT_NE(itr, l1.end());
        EXPECT_EQ(*itr, i);
    }
    ASSERT_EQ(itr, l1.end());
}

TEST(List, Sort) {
    srand((unsigned)time(NULL));
    list<int> l;
    int arr[200];
    for (int i = 0; i < 200; ++i) {
        arr[i] = i;
    }
    for (int i = 0; i < 200; ++i) {
        using std::swap;
        int ind = i + rand() % (200-i);
        swap(arr[i], arr[ind]);
        l.push_back(arr[i]);
    }
    l.sort();
    ASSERT_FALSE(l.empty());
    ASSERT_EQ(l.size(), 200);
    auto itr = l.begin();
    for (int i = 0; i < 200; ++i) {
        ASSERT_NE(itr, l.end());
        EXPECT_EQ(*itr++, i);
    }
    ASSERT_EQ(itr, l.end());
}

TEST(List, Transfer) {
    list<int> l1;
    for (int i = 0; i < 100; ++i) {
        l1.push_back(i);
    }
    list<int> l2;
    for (int i = 100; i < 200; ++i) {
        l2.push_back(i);
    }
    auto itr2 = l2.begin();
    advance(itr2, 49);
    auto itr1 = l1.begin();
    advance(itr1, 50);
    l1.transfer(itr1, l2.begin(), itr2);

    ASSERT_NE(l1.size(), 150);
    ASSERT_NE(l2.size(), 50);
    itr1 = l1.begin();
    for (int i = 0; i < 50; ++i) {
        ASSERT_NE(itr1, l1.end());
        EXPECT_EQ(*itr1++, i);
    }
    for (int i = 100; i < 150; ++i) {
        ASSERT_NE(itr1, l1.end());
        EXPECT_EQ(*itr1++, i);
    }
    for (int i = 50; i < 100; ++i) {
        ASSERT_NE(itr1, l1.end());
        EXPECT_EQ(*itr1++, i);
    }
    ASSERT_EQ(itr1, l1.end());
    itr2 = l2.begin();
    for (int i = 150; i < 200; ++i) {
        ASSERT_NE(itr2, l2.end());
        EXPECT_EQ(*itr2++, i);
    }
    ASSERT_EQ(itr2, l2.end());
}

TEST(List, Splice1) {
    list<int> l1;
    for (int i = 0; i < 100; ++i) {
        l1.push_back(i);
    }
    list<int> l2;
    for (int i = 100; i < 200; ++i) {
        l2.push_back(i);
    }
    auto itr1 = l1.begin();
    advance(itr1, 50);
    l1.splice(itr1, l2);

    ASSERT_FALSE(l1.empty());
    ASSERT_EQ(l1.size(), 200);
    ASSERT_TRUE(l2.empty());

    itr1 = l1.begin();
    for (int i = 0; i < 50; ++i) {
        ASSERT_NE(itr1, l1.end());
        EXPECT_EQ(*itr1++, i);
    }
    for (int i = 100; i < 200; ++i) {
        ASSERT_NE(itr1, l1.end());
        EXPECT_EQ(*itr1++, i);
    }
    for (int i = 50; i < 100; ++i) {
        ASSERT_NE(itr1, l1.end());
        EXPECT_EQ(*itr1++, i);
    }
    ASSERT_EQ(itr1, l1.end());
}

TEST(List, Splice2) {
    
}

TEST(List, Splice3) {
    
}