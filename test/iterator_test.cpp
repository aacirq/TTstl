/*
 * Test cases of stl_iterator_base_types.h & stl_iterator_base_funcs.h
 * For stl_iterator_base_types.h, include:
 *   iterator_traits<T>
 *   iterator<T>
 * For stl_iterator_base_funcs.h, include:
 *
 */

#include <gtest/gtest.h>

#include <iostream>

#include "stl_iterator_base_types.h"

using tt::bidirectional_iterator_tag;
using tt::forward_iterator_tag;
using tt::input_iterator_tag;
using tt::iterator;
using tt::iterator_traits;
using tt::output_iterator_tag;
using tt::random_access_iterator_tag;

// operator == and != for input_iterator_tag
namespace tt {

template <typename Category>
bool operator==(const input_iterator_tag &lhs, const Category &rhs) {
  return false;
}

template <>
bool operator==(const input_iterator_tag &lhs, const input_iterator_tag &rhs) {
  return true;
}

template <typename Category>
bool operator!=(const input_iterator_tag &lhs, const Category &rhs) {
  return true;
}

template <>
bool operator!=(const input_iterator_tag &lhs, const input_iterator_tag &rhs) {
  return false;
}

// operator == and != for input_iterator_tag
template <typename Category>
bool operator==(const tt::output_iterator_tag &lhs, const Category &rhs) {
  return false;
}

template <>
bool operator==(const tt::output_iterator_tag &lhs,
                const tt::output_iterator_tag &rhs) {
  return true;
}

template <typename Category>
bool operator!=(const tt::output_iterator_tag &lhs, const Category &rhs) {
  return true;
}

template <>
bool operator!=(const tt::output_iterator_tag &lhs,
                const tt::output_iterator_tag &rhs) {
  return false;
}

// operator == and != for input_iterator_tag
template <typename Category>
bool operator==(const tt::forward_iterator_tag &lhs, const Category &rhs) {
  return false;
}

template <>
bool operator==(const tt::forward_iterator_tag &lhs,
                const tt::forward_iterator_tag &rhs) {
  return true;
}

template <typename Category>
bool operator!=(const tt::forward_iterator_tag &lhs, const Category &rhs) {
  return true;
}

template <>
bool operator!=(const tt::forward_iterator_tag &lhs,
                const tt::forward_iterator_tag &rhs) {
  return false;
}

// operator == and != for input_iterator_tag
template <typename Category>
bool operator==(const tt::bidirectional_iterator_tag &lhs,
                const Category &rhs) {
  return false;
}

template <>
bool operator==(const tt::bidirectional_iterator_tag &lhs,
                const tt::bidirectional_iterator_tag &rhs) {
  return true;
}

template <typename Category>
bool operator!=(const tt::bidirectional_iterator_tag &lhs,
                const Category &rhs) {
  return true;
}

template <>
bool operator!=(const tt::bidirectional_iterator_tag &lhs,
                const tt::bidirectional_iterator_tag &rhs) {
  return false;
}

// operator == and != for input_iterator_tag
template <typename Category>
bool operator==(const tt::random_access_iterator_tag &lhs,
                const Category &rhs) {
  return false;
}

template <>
bool operator==(const tt::random_access_iterator_tag &lhs,
                const tt::random_access_iterator_tag &rhs) {
  return true;
}

template <typename Category>
bool operator!=(const tt::random_access_iterator_tag &lhs,
                const Category &rhs) {
  return true;
}

template <>
bool operator!=(const tt::random_access_iterator_tag &lhs,
                const tt::random_access_iterator_tag &rhs) {
  return false;
}

}  // namespace tt

// test cases
TEST(CategoryOperatorEqual, IteratorTest) {
  EXPECT_EQ(input_iterator_tag(), input_iterator_tag());
  EXPECT_NE(input_iterator_tag(), output_iterator_tag());
  EXPECT_NE(input_iterator_tag(), forward_iterator_tag());
  EXPECT_NE(input_iterator_tag(), bidirectional_iterator_tag());
  EXPECT_NE(input_iterator_tag(), random_access_iterator_tag());

  EXPECT_NE(output_iterator_tag(), input_iterator_tag());
  EXPECT_EQ(output_iterator_tag(), output_iterator_tag());
  EXPECT_NE(output_iterator_tag(), forward_iterator_tag());
  EXPECT_NE(output_iterator_tag(), bidirectional_iterator_tag());
  EXPECT_NE(output_iterator_tag(), random_access_iterator_tag());

  EXPECT_NE(forward_iterator_tag(), input_iterator_tag());
  EXPECT_NE(forward_iterator_tag(), output_iterator_tag());
  EXPECT_EQ(forward_iterator_tag(), forward_iterator_tag());
  EXPECT_NE(forward_iterator_tag(), bidirectional_iterator_tag());
  EXPECT_NE(forward_iterator_tag(), random_access_iterator_tag());

  EXPECT_NE(bidirectional_iterator_tag(), input_iterator_tag());
  EXPECT_NE(bidirectional_iterator_tag(), output_iterator_tag());
  EXPECT_NE(bidirectional_iterator_tag(), forward_iterator_tag());
  EXPECT_EQ(bidirectional_iterator_tag(), bidirectional_iterator_tag());
  EXPECT_NE(bidirectional_iterator_tag(), random_access_iterator_tag());

  EXPECT_NE(random_access_iterator_tag(), input_iterator_tag());
  EXPECT_NE(random_access_iterator_tag(), output_iterator_tag());
  EXPECT_NE(random_access_iterator_tag(), forward_iterator_tag());
  EXPECT_NE(random_access_iterator_tag(), bidirectional_iterator_tag());
  EXPECT_EQ(random_access_iterator_tag(), random_access_iterator_tag());
}

TEST(IteratorCategoryTest, IteratorTest) {
  EXPECT_EQ(iterator_traits<int *>::iterator_category(),
            random_access_iterator_tag());
  EXPECT_EQ(iterator_traits<const int *>::iterator_category(),
            random_access_iterator_tag());
  EXPECT_EQ(iterator_traits<char *>::iterator_category(),
            random_access_iterator_tag());
  EXPECT_EQ(iterator_traits<const char *>::iterator_category(),
            random_access_iterator_tag());
  EXPECT_EQ(iterator_traits<long *>::iterator_category(),
            random_access_iterator_tag());
  EXPECT_EQ(iterator_traits<const long *>::iterator_category(),
            random_access_iterator_tag());
  EXPECT_EQ(iterator_traits<long long *>::iterator_category(),
            random_access_iterator_tag());
  EXPECT_EQ(iterator_traits<const long long *>::iterator_category(),
            random_access_iterator_tag());
}

TEST(GetCategoryByIterator, IteratorTest) {
  using Category1 =
      typename iterator<input_iterator_tag, int>::iterator_category;
  using Category2 =
      typename iterator<output_iterator_tag, int>::iterator_category;
  using Category3 =
      typename iterator<forward_iterator_tag, int>::iterator_category;
  using Category4 =
      typename iterator<bidirectional_iterator_tag, int>::iterator_category;
  using Category5 =
      typename iterator<random_access_iterator_tag, int>::iterator_category;

  EXPECT_EQ(Category1(), input_iterator_tag());
  EXPECT_EQ(Category2(), output_iterator_tag());
  EXPECT_EQ(Category3(), forward_iterator_tag());
  EXPECT_EQ(Category4(), bidirectional_iterator_tag());
  EXPECT_EQ(Category5(), random_access_iterator_tag());
}