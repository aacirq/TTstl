#ifndef STL_ITERATOR_BASE_FUNCS_H
#define STL_ITERATOR_BASE_FUNCS_H

#include "stl_iterator_base_types.h"

namespace tt {

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type _distance(
    InputIterator first, InputIterator last, input_iterator_tag) {
  typename iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last) {
    n++;
    first++;
  }
  return n;
}

template <typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
_distance(RandomAccessIterator first, RandomAccessIterator last,
          random_access_iterator_tag) {
  return (last - first);
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type distance(
    InputIterator first, InputIterator last) {
  return _distance(
      first, last,
      typename iterator_traits<InputIterator>::iterator_category());
}

template <typename InputIterator>
inline void _advance(InputIterator &itr,
                     typename iterator_traits<InputIterator>::difference_type n,
                     input_iterator_tag) {
  while (n--) {
    itr++;
  }
}

template <typename BidirectionalIterator>
inline void _advance(
    BidirectionalIterator &itr,
    typename iterator_traits<BidirectionalIterator>::difference_type n,
    bidirectional_iterator_tag) {
  if (n > 0) {
    while (n--) {
      itr++;
    }
  } else {
    while (n++) {
      itr--;
    }
  }
}

template <typename RandomAccessIterator>
inline void _advance(
    RandomAccessIterator &itr,
    typename iterator_traits<RandomAccessIterator>::difference_type n,
    random_access_iterator_tag) {
  itr += n;
}

template <typename InputIterator>
inline void advance(
    InputIterator &itr,
    typename iterator_traits<InputIterator>::difference_type n) {
  _advance(itr, n,
           typename iterator_traits<InputIterator>::iterator_category());
}

template <typename InputIterator>
inline InputIterator next(
    InputIterator itr,
    typename iterator_traits<InputIterator>::difference_type n = 1) {
  advance(itr, n);
  return itr;
}

template <typename BidirectionalIterator>
inline BidirectionalIterator prev(
    BidirectionalIterator itr,
    typename iterator_traits<BidirectionalIterator>::difference_type n = 1) {
  advance(itr, -n);
  return itr;
}

}  // namespace tt

#endif  // STL_ITERATOR_BASE_FUNCS_H
