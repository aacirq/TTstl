#include <iostream>

#include <gtest/gtest.h>

#include "complex_class.h"

TEST(ComplexClassTest, DefaultConstructor) {
    ComplexClass c;
    EXPECT_EQ(c.n_i, 1);
    EXPECT_EQ(c.n_d, 1.0);
    EXPECT_EQ(c.str, "");
    EXPECT_EQ(c.c, nullptr);
}

TEST(ComplexClassTest, ConstructWithMultipleArguments) {
    char ch[] = "12345";
    ComplexClass c(2, 2.22, "abcde", ch);
    EXPECT_EQ(c.n_i, 2);
    EXPECT_EQ(c.n_d, 2.22);
    EXPECT_EQ(c.str, "abcde");
    ASSERT_NE(c.c, nullptr);
    EXPECT_NE(c.c, ch);
    EXPECT_STREQ(c.c, ch);
}

TEST(ComplexClassTest, CopyConstructor) {
    char ch[] = "12345";
    ComplexClass c(2, 2.22, "abcde", ch);
    ComplexClass res(c);
    EXPECT_EQ(res.n_i, c.n_i);
    EXPECT_EQ(res.n_d, c.n_d);
    EXPECT_EQ(res.str, c.str);
    ASSERT_NE(res.c, nullptr);
    EXPECT_NE(res.c, c.c);
    EXPECT_STREQ(res.c, c.c);
}

TEST(ComplexClassTest, CopyAssignment) {
    char ch[] = "12345";
    ComplexClass c(2, 2.22, "abcde", ch);
    ComplexClass res = c;
    EXPECT_EQ(res.n_i, c.n_i);
    EXPECT_EQ(res.n_d, c.n_d);
    EXPECT_EQ(res.str, c.str);
    ASSERT_NE(res.c, nullptr);
    EXPECT_NE(res.c, c.c);
    EXPECT_STREQ(res.c, c.c);
}

TEST(ComplexClassTest, EqualOperator) {
    char ch1[] = "12345";
    char ch2[] = "123";
    ComplexClass c1(2, 2.22, "abcde", ch1);
    ComplexClass c2(2, 2.22, "abcde", ch2);
    ComplexClass c3(2, 2.22, "abcde", ch1);
    ComplexClass c4(2, 2.22, "abcde", nullptr);
    ComplexClass c5(2, 2.22, "abcde", nullptr);
    EXPECT_NE(c1, c2);
    EXPECT_EQ(c1, c3);
    EXPECT_NE(c1.c, c3.c);
    EXPECT_NE(c3, c4);
    EXPECT_EQ(c4, c5);

    const ComplexClass cc1(2, 2.22, "abcde", ch1);
    const ComplexClass cc2(2, 2.22, "abcde", ch2);
    const ComplexClass cc3(2, 2.22, "abcde", ch1);
    EXPECT_NE(cc1, cc2);
    EXPECT_EQ(cc1, cc3);
    EXPECT_NE(cc1.c, cc3.c);
}