#ifndef TTSTL_STL_QUEUE_H
#define TTSTL_STL_QUEUE_H

#include "stl_deque.h"

namespace tt {

    template <class T, class Sequence = deque<T>>
    class queue {
    protected:
        typedef typename Sequence::value_type       value_type;
        typedef typename Sequence::size_type        size_type;
        typedef typename Sequence::iterator         iterator;
        typedef typename Sequence::reference        reference;
        typedef typename Sequence::const_reference  const_reference;

    protected:
        Sequence c;

    public:
        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        void push(const value_type &x) { c.push_back(x); }
        void pop() { c.pop_front(); }
        reference front() { return c.front(); }
        const_reference front() const { return c.front(); }
        reference back() { return c.back(); }
        const_reference back() const { return c.back(); }
    };
    // operator == 不知道这个有没有必要，用在哪呢？
    // operator < 不知道这个有没有必要，用在哪呢？
}

#endif /* TTSTL_STL_QUEUE_H */