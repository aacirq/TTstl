#ifndef STL_ITERATOR_BASE_TYPES_H
#define STL_ITERATOR_BASE_TYPES_H

#include <stddef.h>

namespace tt {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename Category, typename T, typename Distance = ptrdiff_t,
          typename Pointer = T *, typename Reference = T &>
struct iterator {
  using iterator_category = Category;
  using value_type = T;
  using difference_type = ptrdiff_t;
  using pointer = Pointer;
  using reference = Reference;
};

template <typename Iterator>
struct iterator_traits {
  using iterator_category = typename Iterator::iterator_category;
  using value_type = typename Iterator::value_type;
  using difference_type = typename Iterator::difference_type;
  using pointer = typename Iterator::pointer;
  using reference = typename Iterator::reference;
};

template <typename T>
struct iterator_traits<T *> {
  using iterator_category = random_access_iterator_tag;
  using value_type = T;
  using difference_type = ptrdiff_t;
  using pointer = T *;
  using reference = T &;
};

template <typename T>
struct iterator_traits<const T *> {
  using iterator_category = random_access_iterator_tag;
  using value_type = T;
  using difference_type = ptrdiff_t;
  using pointer = const T *;
  using reference = const T &;
};

template <typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category
__iterator_category(const Iterator &) {
  return typename iterator_traits<Iterator>::iterator_category();
}

}  // namespace tt

#endif  // STL_ITERATOR_BASE_TYPES_H
