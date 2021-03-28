#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include "stl_vector.h"
#include "complex_class.h"

using std::string;

using tt::vector;

TEST(Vector, DefaultConstructor) {
    vector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 0);
    ASSERT_TRUE(vec.empty());
    ASSERT_EQ(vec.begin(), vec.end());

    const vector<double> vec_double;
    ASSERT_EQ(vec_double.size(), 0);
    ASSERT_EQ(vec_double.capacity(), 0);
    ASSERT_TRUE(vec_double.empty());
    ASSERT_EQ(vec_double.begin(), vec_double.end());

    vector<ComplexClass> vec_complex;
    ASSERT_EQ(vec_complex.size(), 0);
    ASSERT_EQ(vec_complex.capacity(), 0);
    ASSERT_TRUE(vec_complex.empty());
    ASSERT_EQ(vec_complex.begin(), vec_complex.end());
}

TEST(Vector, ConstructWithOneArgument) {
    constexpr size_t NUM = 1000;

    vector<int> vec_int(NUM);
    ASSERT_FALSE(vec_int.empty());
    ASSERT_EQ(vec_int.size(), NUM);
    ASSERT_EQ(vec_int.capacity(), NUM);

    vector<ComplexClass> vec_complex(NUM);
    ASSERT_FALSE(vec_complex.empty());
    ASSERT_EQ(vec_complex.size(), NUM);
    ASSERT_EQ(vec_complex.capacity(), NUM);
}

TEST(Vector, ConstructWithTwoArguments) {
    constexpr size_t NUM_SIZE = 1000;
    constexpr int NUM_INT = 2000;
    constexpr long NUM_LONG = 3000;

    vector<int> vec_size(NUM_SIZE, 2);
    ASSERT_FALSE(vec_size.empty());
    ASSERT_EQ(vec_size.size(), NUM_SIZE);
    ASSERT_EQ(vec_size.capacity(), NUM_SIZE);
    for (size_t i = 0; i < vec_size.size(); ++i) {
        EXPECT_EQ(vec_size[i], 2);
    }

    vector<int> vec_int(NUM_INT, 22);
    ASSERT_FALSE(vec_int.empty());
    ASSERT_EQ(vec_int.size(), NUM_INT);
    ASSERT_EQ(vec_int.capacity(), NUM_INT);
    for (size_t i = 0; i < vec_int.size(); ++i) {
        EXPECT_EQ(vec_int[i], 22);
    }

    vector<int> vec_long(NUM_LONG, 222);
    ASSERT_FALSE(vec_long.empty());
    ASSERT_EQ(vec_long.size(), NUM_LONG);
    ASSERT_EQ(vec_long.capacity(), NUM_LONG);
    for (size_t i = 0; i < vec_long.size(); ++i) {
        EXPECT_EQ(vec_long[i], 222);
    }
}

TEST(vector, PushBackAndPopBack) {
    vector<int> iv(2, 9);
    iv.push_back(1);
    EXPECT_EQ(iv.size(), 3);
    EXPECT_EQ(iv.capacity(), 4);

    iv.push_back(2);
    EXPECT_EQ(iv.size(), 4);
    EXPECT_EQ(iv.capacity(), 4);

    iv.push_back(3);
    EXPECT_EQ(iv.size(), 5);
    EXPECT_EQ(iv.capacity(), 8);

    iv.push_back(4);
    EXPECT_EQ(iv.size(), 6);
    EXPECT_EQ(iv.capacity(), 8);

    iv.push_back(5);
    EXPECT_EQ(iv.size(), 7);
    EXPECT_EQ(iv.capacity(), 8);

    int ans[] = {9, 9, 1, 2, 3, 4, 5};
    for (int i = 0; i < iv.size(); ++i) {
        EXPECT_EQ(iv[i], ans[i]);
    }
}

class VectorChangeTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (size_t i = 1; i <= 7; ++i)
            iv.push_back(i);
    }

    vector<int> iv;
};

TEST_F(VectorChangeTest, PopBack) {
    iv.pop_back();
    iv.pop_back();
    EXPECT_EQ(iv.size(), 5);
    EXPECT_EQ(iv.capacity(), 8);
    
    iv.pop_back();
    EXPECT_EQ(iv.size(), 4);
    EXPECT_EQ(iv.capacity(), 8);
}

TEST_F(VectorChangeTest, Iterator) {
    int d = 1;
    for (auto itr = iv.begin(); itr != iv.end(); ++itr) {
        EXPECT_EQ(*itr, d++);
    } 
}

TEST_F(VectorChangeTest, Erase) {
    vector<int>::iterator ivite = iv.begin() + 2;
    auto ret = iv.erase(ivite);
    EXPECT_EQ(iv.size(), 6);
    EXPECT_NE(ret, iv.end());
    EXPECT_EQ(*ret, 4);

    ivite = ret;
    ret = iv.erase(ivite, ivite + 4);
    EXPECT_EQ(iv.size(), 2);
    EXPECT_EQ(ret, iv.end());

    for (int i = 0; i < iv.size(); ++i) {
        EXPECT_EQ(iv[i], i+1);
    }
}

TEST_F(VectorChangeTest, Insert) {
    auto ite = iv.begin() + 2;
    iv.insert(ite, 9);
    EXPECT_EQ(iv[0], 1);
    EXPECT_EQ(iv[1], 2);
    EXPECT_EQ(iv[2], 9);
    for (int i = 3; i < iv.size(); ++i) {
        EXPECT_EQ(iv[i], i);
    }

    ite = iv.begin() + 2;
    iv.insert(ite, 3, 2);
    EXPECT_EQ(iv[0], 1);
    for (int i = 1; i <= 4; ++i) {
        EXPECT_EQ(iv[i], 2);
    }
    EXPECT_EQ(iv[5], 9);
    for (int i = 6; i < iv.size(); ++i) {
        EXPECT_EQ(iv[i], i-3);
    }
}

TEST_F(VectorChangeTest, ResizeToLargeWithDefault) {
    iv.resize(100);
    EXPECT_EQ(iv.size(), 100);
    for (int i = 0; i < 7; ++i) {
        EXPECT_EQ(iv[i], i+1);
    }
    for (int i = 7; i < iv.size(); ++i) {
        EXPECT_EQ(iv[i], 0);
    }

    char ch[] = "12345";
    ComplexClass comp = ComplexClass(2, 2.22, "abc", ch);
    vector<ComplexClass> vec(10, comp);
    vec.resize(222);
    EXPECT_EQ(vec.size(), 222);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(vec[i], comp);
    }
    for (int i = 10; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], ComplexClass());
    }
}

TEST_F(VectorChangeTest, ResizeToLargeWithCopy) {
    iv.resize(100, 22);
    EXPECT_EQ(iv.size(), 100);
    for (int i = 0; i < 7; ++i) {
        EXPECT_EQ(iv[i], i+1);
    }
    for (int i = 7; i < iv.size(); ++i) {
        EXPECT_EQ(iv[i], 22);
    }

    char ch[] = "12345";
    ComplexClass comp = ComplexClass(2, 2.22, "abc", ch);
    char copy_ch[] = "22222";
    ComplexClass copyComp = ComplexClass(2, 2.22, "aaa", copy_ch);
    vector<ComplexClass> vec(10, comp);
    vec.resize(222, copyComp);
    EXPECT_EQ(vec.size(), 222);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(vec[i], comp);
    }
    for (int i = 10; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], copyComp);
    }
}

TEST_F(VectorChangeTest, ResizeToSmall) {
    iv.resize(5);
    EXPECT_EQ(iv.size(), 5);
    for (int i = 0; i < iv.size(); ++i) {
        EXPECT_EQ(iv[i], i+1);
    }
}

TEST_F(VectorChangeTest, Clear) {
    iv.clear();
    EXPECT_EQ(iv.size(), 0);
}
