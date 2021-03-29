#ifndef TTSTL_STL_ALGOBASE_H
#define TTSTL_STL_ALGOBASE_H

#include <cstring>

#include "iterator.h"
#include "type_traits.h"
#include "stl_construct.h"

// TODO 重新看一遍copy_backward()，保证是逆着复制的，这样能够防止存在overlap的时候的复制。

namespace tt {

    /* ========== fill ========== */
    template <typename ForwardIterator, typename T>
    inline void
    fill(ForwardIterator first, ForwardIterator last, const T &value) {
        for (; first != last; ++first) {
            *first = value;
        }
    }

    /* ========== fill_n ========== */
    template <typename OutputIterator, typename Size, typename T>
    inline OutputIterator
    fill_n(OutputIterator first, Size n, const T &value) {
        for (; n > 0; --n, ++first) {
            *first = value;
        }
        return first;
    }

    /* ========== copy ========== */
    template <typename RandomAccessIterator, typename OutputIterator, typename Distance>
    inline OutputIterator
    _copy_d(RandomAccessIterator first, RandomAccessIterator last,
            OutputIterator result, Distance*) {
        // TODO 这样效率高在哪？
        for (Distance n = last - first; n > 0; --n, ++result, ++first) {
            *result = *first;
        }
        return result;
    }

    template <typename T>
    inline T *
    _copy_tf(const T *first, const T *last, T *result, _true_type) {
        memmove(result, first, (last - first) * sizeof(T));
        return result + (last - first);
    }

    template <typename T>
    inline T *
    _copy_tf(const T *first, const T *last, T *result, _false_type) {
        return _copy_d(first, last, result, (ptrdiff_t *)0);
    }

    template <typename InputIterator, typename OutputIterator>
    inline OutputIterator
    _copy(InputIterator first, InputIterator last, 
          OutputIterator result, input_iterator_tag) {
        for (; first != last; ++first, ++result) {
            *result = *first;
        }
        return result;
    }

    template <typename RandomAccessIterator, typename OutputIterator>
    inline OutputIterator
    _copy(RandomAccessIterator first, RandomAccessIterator last, 
          OutputIterator result, random_access_iterator_tag) {
        return _copy_d(first, last, result, distance_type(first));
    }

    template <typename InputIterator, typename OutputIterator>
    struct _copy_dispatch {
        OutputIterator operator () (InputIterator first, InputIterator last, OutputIterator result) {
            return _copy(first, last, result, iterator_category(first));
        }
    };

    template <typename T>
    struct _copy_dispatch<T*, T*> {
        T * operator () (T *first, T *last, T *result) {
            typedef typename _type_traits<T>::has_trivial_assignment_operator has_trivial;
            return _copy_tf(first, last, result, has_trivial());
        }
    };

    template <typename T>
    struct _copy_dispatch<const T*, T*> {
        T * operator () (const T *first, const T *last, T *result) {
            typedef typename _type_traits<T>::has_trivial_assignment_operator has_trivial;
            return _copy_tf(first, last, result, has_trivial());
        }
    };

    // TODO 考虑区间重叠问题
    template <typename InputIterator, typename OutputIterator>
    inline OutputIterator
    copy(InputIterator first, InputIterator last, OutputIterator result) {
        return _copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
    }

    template <> inline char *
    copy(const char *first, const char *last, char *result) {
        memmove(result, first, last - first);
        return result + (last - first);
    }

    template <> inline wchar_t *
    copy(const wchar_t *first, const wchar_t *last, wchar_t *result) {
        memmove(result, first, (last - first) * sizeof(wchar_t));
        return result + (last - first);
    }


    /* ========== copy_backward ========== */
    template <class RandomAccessIterator, class BidirectionalIterator, class Distance>
    inline BidirectionalIterator
    _copy_backward_d(RandomAccessIterator first, RandomAccessIterator last,
                     BidirectionalIterator result, Distance *) {
        Distance n = last - first;
        for (--last, --result; n > 0; --n, --last, --result) {
            *result = *last;
        }
        return ++result;
    }

    template <class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2
    _copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
                   BidirectionalIterator2 result, bidirectional_iterator_tag) {
        for (--first, --last, --result; last != first; --last, --result) {
            *result = *last;
        }
        return ++result;
    }

    template <class RandomAccessIterator, class BidirectionalIterator>
    inline BidirectionalIterator
    _copy_backward(RandomAccessIterator first, RandomAccessIterator last,
                   BidirectionalIterator result, random_access_iterator_tag) {
        return _copy_backward_d(first, last, result, distance_type(first));
    }

    template <class T>
    inline T *_copy_backward_tf(const T *first, const T *last, T *result, _true_type) {
        T *cur_first = result - (last - first);
        memmove(cur_first, first, (last - first) * sizeof(T));
        return cur_first;
    }

    template <class T>
    inline T *_copy_backward_tf(const T *first, const T *last, T *result, _false_type) {
        return _copy_backward_d(first, last, result, (ptrdiff_t*)0);
    }

    template <class BidirectionalIterator1, class BidirectionalIterator2>
    struct _copy_backward_dispatch {
        inline BidirectionalIterator2
        operator ()(BidirectionalIterator1 first, BidirectionalIterator1 last,
                    BidirectionalIterator2 result) {
            return _copy_backward(first, last, result, iterator_category(first));
        }
    };

    template <class T>
    struct _copy_backward_dispatch<T*, T*> {
        inline T * operator ()(T *first, T *last, T *result) {
            typedef typename _type_traits<T>::has_trivial_assignment_operator t;
            return _copy_backward_tf(first, last, result, t());
        }
    };

    template <class T>
    struct _copy_backward_dispatch<const T*, T*> {
        inline T * operator ()(const T *first, const T *last, T *result) {
            typedef typename _type_traits<T>::has_trivial_assignment_operator t;
            return _copy_backward_tf(first, last, result, t());
        }
    };

    template <class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2
    copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, 
                  BidirectionalIterator2 result) {
        return _copy_backward_dispatch<BidirectionalIterator1, BidirectionalIterator2>()(first, last, result);
    }

    template <> inline char *
    copy_backward(const char *first, const char *last, char *result) {
        char *res_first = result - (last - first);
        memmove(res_first, first, last - first);
        return res_first;
    }

    template <> inline wchar_t *
    copy_backward(const wchar_t *first, const wchar_t *last, wchar_t *result) {
        wchar_t *res_first = result - (last - first);
        memmove(res_first, first, (last - first) * sizeof(wchar_t));
        return res_first;
    }
}


#endif /* TTSTL_STL_ALGOBASE_H */