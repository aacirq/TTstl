#include <gtest/gtest.h>

#include "stl_heap.h"
#include "stl_vector.h"

using tt::vector;

TEST(Heap, TestCase1) {
    constexpr int LEN = 9;
    int ia[] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    vector<int> ivec;
    for (int i = 0; i < sizeof(ia)/sizeof(int); ++i) {
        ivec.push_back(ia[i]);
    }
    ASSERT_EQ(ivec.size(), LEN);

    tt::make_heap(ivec.begin(), ivec.end());
    ASSERT_EQ(ivec.size(), LEN);
    int res1[] = {9, 5, 8, 3, 4, 0, 2, 3, 1};
    for (int i = 0; i < sizeof(res1)/sizeof(int); ++i) {
        EXPECT_EQ(ivec[i], res1[i]);
    }

    ivec.push_back(7);
    tt::push_heap(ivec.begin(), ivec.end());
    ASSERT_EQ(ivec.size(), LEN+1);
    int res2[] = {9, 7, 8, 3, 5, 0, 2, 3, 1, 4};
    for (int i = 0; i < sizeof(res2)/sizeof(int); ++i) {
        EXPECT_EQ(ivec[i], res2[i]);
    }

    tt::pop_heap(ivec.begin(), ivec.end());
    EXPECT_EQ(ivec.back(), 9);
    ivec.pop_back();
    ASSERT_EQ(ivec.size(), LEN);
    int res3[] = {8, 7, 4, 3, 5, 0, 2, 3, 1};
    for (int i = 0; i < sizeof(res3)/sizeof(int); ++i) {
        EXPECT_EQ(ivec[i], res3[i]);
    }

    tt::sort_heap(ivec.begin(), ivec.end());
    int res4[] = {0, 1, 2, 3, 3, 4, 5, 7, 8};
    for (int i = 0; i < sizeof(res4)/sizeof(int); ++i) {
        EXPECT_EQ(ivec[i], res4[i]);
    }
}

TEST(Heap, TestCase2) {
    int ia[] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    tt::make_heap(ia, ia+9);

    tt::sort_heap(ia, ia+9);
    int res[] = {0, 1, 2, 3, 3, 4, 5, 8, 9};
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(ia[i], res[i]);
    }

    tt::make_heap(ia, ia+9);
    tt::pop_heap(ia, ia+9);
    EXPECT_EQ(ia[8], 9);
}

TEST(Heap, TestCase3) {
    int ia[] = {4, 1, 7, 6, 2, 5};
    tt::make_heap(ia, ia+6);
    int res[] = {7, 6, 5, 1, 2, 4};
    for (int i = 0; i < 6; ++i) {
        EXPECT_EQ(ia[i], res[i]);
    }
}