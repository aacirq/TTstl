#ifndef TTSTL_STL_STACK_H
#define TTSTL_STL_STACK_H

#include "stl_deque.h"

namespace tt {

    template <class T, class Sequence = deque<T>>
    class stack {
        template <class Type, class SeqType>
        friend bool operator == (const stack<Type, SeqType> &s1, const stack<Type, SeqType> &s2);
        template <class Type, class SeqType>
        friend bool operator < (const stack<Type, SeqType> &s1, const stack<Type, SeqType> &s2);
    protected:
        Sequence c;
    public:
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::size_type  size_type;
        typedef typename Sequence::reference  reference;
        typedef typename Sequence::const_reference const_reference;

        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        reference top() { return c.back(); }
        const_reference top() const { return c.back(); }
        void push(const value_type &x) { c.push_back(x); }
        void pop() { c.pop_back(); }
    };

    template <class T, class Sequence>
    bool operator == (const stack<T, Sequence> &s1, const stack<T, Sequence> &s2) {
        return s1.c == s2.c;
    }

    template <class T, class Sequence>
    bool operator < (const stack<T, Sequence> &s1, const stack<T, Sequence> &s2) {
        return s1.c < s2.c;
    }

}


#endif /* TTSTL_STL_STACK_H */