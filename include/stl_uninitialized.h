#ifndef TTSTL_STL_UINITIALIZED_H
#define TTSTL_STL_UINITIALIZED_H

#include <cstring>
#include <memory>

#include "iterator.h"
#include "type_traits.h"
#include "stl_construct.h"
#include "stl_algobase.h"

namespace tt {

    /* ========== uninitialized_copy ========== */
    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    _uninitialized_copy_aux(InputIterator first, InputIterator last, 
                        ForwardIterator result, _true_type) {
        // memmove(result, first, last - first);
        return copy(first, last, result);
        // return result;
    }

    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    _uninitialized_copy_aux(InputIterator first, InputIterator last, 
                        ForwardIterator result, _false_type) {
        ForwardIterator mem = result;
        for (; first != last; ++first, ++mem) {
            construct(&*mem, *first);
        }
        return mem;
    }

    template <typename InputIterator, typename ForwardIterator, typename T>
    inline ForwardIterator
    _uninitialized_copy(InputIterator first, InputIterator last,
                        ForwardIterator result, T*) {
        typedef typename _type_traits<T>::is_POD_type is_POD;
        return _uninitialized_copy_aux(first, last, result, is_POD());
    }

    /* 返回在目的地址中的最后一个元素后一个 */
    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator 
    uninitialized_copy(InputIterator first, InputIterator last, 
                    ForwardIterator result) {
        return _uninitialized_copy(first, last, result, value_type(result));
    }


    /* ========== uninitialized_fill ========== */
    template <typename ForwardIterator, typename T>
    inline void
    _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, 
                            const T &value, _true_type) {
        for (; first != last; ++first) {
            *first = value;
        }
    }

    template <typename ForwardIterator, typename T>
    inline void
    _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, 
                            const T &value, _false_type) {
        for (; first != last; ++first) {
            construct(&*first, value);
        }
    }

    template <typename ForwardIterator, typename T, typename T1>
    inline void 
    _uninitialized_fill(ForwardIterator first, ForwardIterator last, 
                        const T &value, T1*) {
        typedef typename _type_traits<T1>::is_POD_type is_POD;
        _uninitialized_fill_aux(first, last, value, is_POD());
    }

    template <typename ForwardIterator, typename T>
    inline void 
    uninitialized_fill(ForwardIterator first, ForwardIterator last, 
                       const T &value) {
        _uninitialized_fill(first, last, value, value_type(first));
    }

    
    /* ========== uninitialized_fill_n ========== */
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &value,
                              _true_type) {
        for (; n > 0; --n, ++first) {
            *first = value;
        }
        return first;
    }
    
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &value,
                              _false_type) {
        for (; n > 0; --n, ++first) {
            construct(&*first, value);
        }
        return first;
    }

    template <typename ForwardIterator, typename Size, typename T, typename T1>
    inline ForwardIterator
    _uninitialized_fill_n(ForwardIterator first, Size n, const T &value, T1*) {
        typedef typename _type_traits<T1>::is_POD_type is_POD;
        return _uninitialized_fill_n_aux(first, n, value, is_POD());
    }

    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    uninitialized_fill_n(ForwardIterator first, Size n, const T &value) {
        return _uninitialized_fill_n(first, n, value, value_type(first));
    }
}

#endif /* TTSTL_STL_UINITIALIZED_H */