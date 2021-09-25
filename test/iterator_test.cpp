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

#include "complex_class.h"
#include "stl_iterator_base_types.h"

using tt::bidirectional_iterator_tag;
using tt::forward_iterator_tag;
using tt::input_iterator_tag;
using tt::iterator;
using tt::iterator_traits;
using tt::output_iterator_tag;
using tt::random_access_iterator_tag;

TEST(IteratorCategory, IteratorTraitsTest) {
  EXPECT_EQ(typeid(iterator_traits<int *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<const int *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<char *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<const char *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<long *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<const long *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<long long *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<const long long *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<ComplexClass *>::iterator_category),
            typeid(random_access_iterator_tag));
  EXPECT_EQ(typeid(iterator_traits<const ComplexClass *>::iterator_category),
            typeid(random_access_iterator_tag));
}

TEST(ValueType, IteratorTraitsTest) {
  EXPECT_EQ(typeid(iterator_traits<int *>::value_type), typeid(int));
  EXPECT_EQ(typeid(iterator_traits<const int *>::value_type), typeid(int));
  EXPECT_EQ(typeid(iterator_traits<char *>::value_type), typeid(char));
  EXPECT_EQ(typeid(iterator_traits<const char *>::value_type), typeid(char));
  EXPECT_EQ(typeid(iterator_traits<long *>::value_type), typeid(long));
  EXPECT_EQ(typeid(iterator_traits<const long *>::value_type), typeid(long));
  EXPECT_EQ(typeid(iterator_traits<long long *>::value_type),
            typeid(long long));
  EXPECT_EQ(typeid(iterator_traits<const long long *>::value_type),
            typeid(long long));
  EXPECT_EQ(typeid(iterator_traits<ComplexClass *>::value_type),
            typeid(ComplexClass));
  EXPECT_EQ(typeid(iterator_traits<const ComplexClass *>::value_type),
            typeid(ComplexClass));
}

TEST(DifferenceType, IteratorTraitsTest) {
  EXPECT_EQ(typeid(iterator_traits<int *>::difference_type), typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<const int *>::difference_type),
            typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<char *>::difference_type),
            typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<const char *>::difference_type),
            typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<long *>::difference_type),
            typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<const long *>::difference_type),
            typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<long long *>::difference_type),
            typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<const long long *>::difference_type),
            typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<ComplexClass *>::difference_type),
            typeid(ptrdiff_t));
  EXPECT_EQ(typeid(iterator_traits<const ComplexClass *>::difference_type),
            typeid(ptrdiff_t));
}

TEST(Pointer, IteratorTraitsTest) {
  EXPECT_EQ(typeid(iterator_traits<int *>::pointer), typeid(int *));
  EXPECT_EQ(typeid(iterator_traits<const int *>::pointer), typeid(const int *));
  EXPECT_EQ(typeid(iterator_traits<char *>::pointer), typeid(char *));
  EXPECT_EQ(typeid(iterator_traits<const char *>::pointer),
            typeid(const char *));
  EXPECT_EQ(typeid(iterator_traits<long *>::pointer), typeid(long *));
  EXPECT_EQ(typeid(iterator_traits<const long *>::pointer),
            typeid(const long *));
  EXPECT_EQ(typeid(iterator_traits<long long *>::pointer), typeid(long long *));
  EXPECT_EQ(typeid(iterator_traits<const long long *>::pointer),
            typeid(const long long *));
  EXPECT_EQ(typeid(iterator_traits<ComplexClass *>::pointer),
            typeid(ComplexClass *));
  EXPECT_EQ(typeid(iterator_traits<const ComplexClass *>::pointer),
            typeid(const ComplexClass *));
}

TEST(Reference, IteratorTraitsTest) {
  EXPECT_EQ(typeid(iterator_traits<int *>::reference), typeid(int &));
  EXPECT_EQ(typeid(iterator_traits<const int *>::reference),
            typeid(const int &));
  EXPECT_EQ(typeid(iterator_traits<char *>::reference), typeid(char &));
  EXPECT_EQ(typeid(iterator_traits<const char *>::reference),
            typeid(const char &));
  EXPECT_EQ(typeid(iterator_traits<long *>::reference), typeid(long &));
  EXPECT_EQ(typeid(iterator_traits<const long *>::reference),
            typeid(const long &));
  EXPECT_EQ(typeid(iterator_traits<long long *>::reference),
            typeid(long long &));
  EXPECT_EQ(typeid(iterator_traits<const long long *>::reference),
            typeid(const long long &));
  EXPECT_EQ(typeid(iterator_traits<ComplexClass *>::reference),
            typeid(ComplexClass &));
  EXPECT_EQ(typeid(iterator_traits<const ComplexClass *>::reference),
            typeid(const ComplexClass &));
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

  EXPECT_EQ(typeid(Category1), typeid(input_iterator_tag));
  EXPECT_EQ(typeid(Category2), typeid(output_iterator_tag));
  EXPECT_EQ(typeid(Category3), typeid(forward_iterator_tag));
  EXPECT_EQ(typeid(Category4), typeid(bidirectional_iterator_tag));
  EXPECT_EQ(typeid(Category5), typeid(random_access_iterator_tag));
}

TEST(GetValueTypeByIterator, IteratorTest) {
  using Type1 = typename iterator<input_iterator_tag, int>::value_type;
  using Type2 = typename iterator<input_iterator_tag, char>::value_type;
  using Type3 = typename iterator<input_iterator_tag, long>::value_type;
  using Type4 = typename iterator<input_iterator_tag, long long>::value_type;
  using Type5 = typename iterator<input_iterator_tag, ComplexClass>::value_type;

  EXPECT_EQ(typeid(Type1), typeid(int));
  EXPECT_EQ(typeid(Type2), typeid(char));
  EXPECT_EQ(typeid(Type3), typeid(long));
  EXPECT_EQ(typeid(Type4), typeid(long long));
  EXPECT_EQ(typeid(Type5), typeid(ComplexClass));
}

TEST(GetDifferenceTypeByIterator, IteratorTest) {
  using DiffType1 = typename iterator<input_iterator_tag, int>::difference_type;
  using DiffType2 =
      typename iterator<input_iterator_tag, char>::difference_type;
  using DiffType3 =
      typename iterator<input_iterator_tag, long>::difference_type;
  using DiffType4 =
      typename iterator<input_iterator_tag, long long>::difference_type;
  using DiffType5 =
      typename iterator<input_iterator_tag, ComplexClass>::difference_type;
  using DiffType6 = typename iterator<input_iterator_tag, int, long, char *,
                                      ComplexClass &>::difference_type;

  EXPECT_EQ(typeid(DiffType1), typeid(ptrdiff_t));
  EXPECT_EQ(typeid(DiffType2), typeid(ptrdiff_t));
  EXPECT_EQ(typeid(DiffType3), typeid(ptrdiff_t));
  EXPECT_EQ(typeid(DiffType4), typeid(ptrdiff_t));
  EXPECT_EQ(typeid(DiffType5), typeid(ptrdiff_t));
  EXPECT_EQ(typeid(DiffType6), typeid(long));
}

TEST(GetPointerByIterator, IteratorTest) {
  using PointerType1 = typename iterator<input_iterator_tag, int>::pointer;
  using PointerType2 = typename iterator<input_iterator_tag, char>::pointer;
  using PointerType3 = typename iterator<input_iterator_tag, long>::pointer;
  using PointerType4 =
      typename iterator<input_iterator_tag, long long>::pointer;
  using PointerType5 =
      typename iterator<input_iterator_tag, ComplexClass>::pointer;
  using PointerType6 = typename iterator<input_iterator_tag, int, long, char *,
                                         ComplexClass &>::pointer;

  EXPECT_EQ(typeid(PointerType1), typeid(int *));
  EXPECT_EQ(typeid(PointerType2), typeid(char *));
  EXPECT_EQ(typeid(PointerType3), typeid(long *));
  EXPECT_EQ(typeid(PointerType4), typeid(long long *));
  EXPECT_EQ(typeid(PointerType5), typeid(ComplexClass *));
  EXPECT_EQ(typeid(PointerType6), typeid(char *));
}

TEST(GetReferenceByIterator, IteratorTest) {
  using RefType1 = typename iterator<input_iterator_tag, int>::reference;
  using RefType2 = typename iterator<input_iterator_tag, char>::reference;
  using RefType3 = typename iterator<input_iterator_tag, long>::reference;
  using RefType4 = typename iterator<input_iterator_tag, long long>::reference;
  using RefType5 =
      typename iterator<input_iterator_tag, ComplexClass>::reference;
  using RefType6 = typename iterator<input_iterator_tag, int, long, char *,
                                     ComplexClass &>::reference;

  EXPECT_EQ(typeid(RefType1), typeid(int &));
  EXPECT_EQ(typeid(RefType2), typeid(char &));
  EXPECT_EQ(typeid(RefType3), typeid(long &));
  EXPECT_EQ(typeid(RefType4), typeid(long long &));
  EXPECT_EQ(typeid(RefType5), typeid(ComplexClass &));
  EXPECT_EQ(typeid(RefType6), typeid(ComplexClass &));
}