#ifndef TTSTL_STL_HEAP_H
#define TTSTL_STL_HEAP_H

#include "iterator.h"

namespace tt {

    template <class RandomAccessIterator, class Distance, class T>
    inline void _push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value) {
        Distance parent = (holeIndex - 1) / 2;
        while (holeIndex > topIndex && *(first + parent) < value) {
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;
    }

    template <class RandomAccessIterator, class Distance, class T>
    inline void _push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*) {
        _push_heap(first, Distance(last - first - 1), Distance(0), static_cast<T>(*(last - 1)));
    }

    template <class RandomAccessIterator>
    inline void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
        _push_heap_aux(first, last, distance_type(first), value_type(first));
    }

    template <class RandomAccessIterator, class Distance, class T>
    void _adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value) {
        Distance secondChild = 2 * holeIndex + 2;
        Distance topIndex = holeIndex;
        while (secondChild < len) {
            if (*(first + secondChild) < *(first + secondChild - 1)) {
                --secondChild;
            }
            *(first + holeIndex) = *(first + secondChild);
            holeIndex = secondChild;
            secondChild = 2 * holeIndex + 2;
        }
        if (secondChild == len) {
            *(first + holeIndex) = *(first + secondChild - 1);
            holeIndex = secondChild - 1;
        }
        _push_heap(first, holeIndex, topIndex, value);
    }

    template <class RandomAccessIterator, class Distance, class T>
    inline void _pop_heap(RandomAccessIterator first, RandomAccessIterator last, 
                          RandomAccessIterator result, T value, Distance*) {
        *result = *first;
        _adjust_heap(first, Distance(0), Distance(last - first), value);
    }

    template <class RandomAccessIterator, class T>
    inline void _pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
        _pop_heap(first, last - 1, last - 1, static_cast<T>(*(last - 1)), distance_type(first));
    }

    template <class RandomAccessIterator>
    inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
        _pop_heap_aux(first, last, value_type(first));
    }

    template <class RandomAccessIterator>
    void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
        while (last - first > 1) {
            pop_heap(first, last--);
        }
    }

    template <class RandomAccessIterator, class Distance, class T>
    inline void _make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*) {
        if (last - first < 2) return;
        Distance len = last - first;
        Distance holeIndex = (last - first) / 2 - 1;
        while (true) {
            _adjust_heap(first, holeIndex, len, static_cast<T>(*(first + holeIndex)));
            if (holeIndex == 0) return;
            --holeIndex;
        }
    }

    template <class RandomAccessIterator>
    inline void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
        _make_heap(first, last, value_type(first), distance_type(first));
    }

}

#endif