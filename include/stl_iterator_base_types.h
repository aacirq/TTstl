#ifndef STL_ITERATOR_BASE_TYPES_H
#define STL_ITERATOR_BASE_TYPES_H

namespace tt {
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename Category, typename T, typename Distance = ptrdiff_t,
          typename Pointer = T*, typename Reference = T&>
class iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

template <typename Iterator>
class iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

template <typename T>
class iterator_traits<T*> {
  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef T* pointer;
  typedef T& reference;
};

template <typename T>
class iterator_traits<const T*> {
  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef const T* pointer;
  typedef const T& reference;
};

template <typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category
__iterator_category(const Iterator&) {
  return typename iterator_traits<Iterator>::iterator_category();
}
}  // namespace tt

#endif  // STL_ITERATOR_BASE_TYPES_H
