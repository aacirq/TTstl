#ifndef STL_UINITIALIZED_H
#define STL_UINITIALIZED_H

#include <string.h>

#include "stl_algobase.h"
#include "stl_iterator_base_types.h"
#include "type_traits.h"

namespace tt {

template <typename InputIterator, typename ForwardIterator, typename IsPOD>
ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last,
                                     ForwardIterator result, IsPOD) {
  ForwardIterator cur = result;
  for (; first != last; first++, cur++) {
    tt::construct(&*cur, *first);
  }
  return cur;
}

template <typename InputIterator, typename ForwardIterator>
ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last,
                                     ForwardIterator result, tt::__true_type) {
  return tt::copy(first, last, result);
}

template <typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
                                   ForwardIterator result) {
  typedef typename tt::iterator_traits<first>::value_type Type;
  typedef typename tt::__type_traits<Type>::is_POD_type IsPOD;
  return tt::__uninitialized_copy(first, last, result, IsPOD());
}

template <typename ForwardIterator, typename T, typename IsPOD>
void __uninitialized_fill(ForwardIterator first, ForwardIterator last,
                          const T &x, IsPOD) {
  for (; first != last; first++) {
    tt::construct(&*first, x);
  }
}

template <typename ForwardIterator, typename T>
void __uninitialized_fill(ForwardIterator first, ForwardIterator last,
                          const T &x, tt::__true_type) {
  tt::fill(first, last, x);
}

template <typename ForwardIterator, typename T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last,
                        const T &x) {
  typedef typename tt::iterator_traits<first>::value_type Type;
  typedef typename tt::__type_traits<Type>::is_POD_type IsPOD;
  tt::__uninitialized_fill(first, last, const T &x, IsPOD());
}

template <typename InputIterator, typename ForwardIterator, typename Size,
          typename IsPOD>
ForwardIterator __uninitialized_copy_n(InputIterator first, Size count,
                                       ForwardIterator result, IsPOD) {
  ForwardIterator cur = result;
  while (count-- != 0) {
    tt::construct(&*cur, *first);
    cur++;
    first++;
  }
  return cur;
}

template <typename InputIterator, typename ForwardIterator, typename Size>
ForwardIterator __uninitialized_copy_n(InputIterator first, Size count,
                                       ForwardIterator result,
                                       tt::__true_type) {
  return tt::copy_n(first, count, result);
}

template <typename InputIterator, typename ForwardIterator, typename Size>
ForwardIterator uninitialized_copy_n(InputIterator first, Size count,
                                     ForwardIterator result) {
  typedef typename tt::iterator_traits<first>::value_type Type;
  typedef typename tt::__type_traits<Type>::is_POD_type IsPOD;
  return tt::__uninitialized_copy_n(first, count, result, IsPOD());
}

template <typename ForwardIterator, typename Size, typename T, typename IsPOD>
ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size count,
                                       const T &x, IsPOD) {
  while (count-- != 0) {
    tt::construct(&*first, x);
    first++;
  }
  return first;
}

template <typename ForwardIterator, typename Size, typename T>
ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size count,
                                       const T &x, tt::__true_type) {
  return tt::fill_n(first, count, x);
}

template <typename ForwardIterator, typename Size, typename T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size count,
                                     const T &x) {
  typedef typename tt::iterator_traits<first>::value_type Type;
  typedef typename tt::__type_traits<Type>::is_POD_type IsPOD;
  return tt::__uninitialized_fill_n(first, count, x, IsPOD());
}
}  // namespace tt

#endif  // STL_UINITIALIZED_H