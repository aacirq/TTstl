#ifndef TTSTL_STL_VECTOR_H
#define TTSTL_STL_VECTOR_H

#include <cstddef>
#include "stl_alloc.h"
#include "stl_construct.h"
#include "stl_uninitialized.h"
#include "stl_algobase.h"

namespace tt {

    template <class T, class Alloc = alloc>
    class vector {
    public:
        typedef T          value_type;
        typedef T*         pointer;
        typedef T*         iterator;
        typedef T&         reference;
        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;

    protected:
        typedef simple_alloc<T, Alloc> data_allocator;
        iterator start;
        iterator finish;
        iterator end_of_storge;

        void insert_aux(iterator position, const T &x);
        void deallocate() {
            if (start)
                data_allocator::deallocate(start, end_of_storge - start);
        }
        void fill_initialize(size_type n, const T &value) {
            start = allocate_and_fill(n, value);
            finish = start + n;
            end_of_storge = finish;
        }

    public:
        iterator begin() { return start; }
        iterator end() { return finish; }
        size_type size() const { return size_type(finish - start); }
        size_type capacity() const { return size_type(end_of_storge - start); }
        bool empty() const { return start == finish; }
        reference operator[] (size_type n) { return *(begin() + n); }

        vector() : start(0), finish(0), end_of_storge(0) {}
        vector(size_type n, const T &value) { fill_initialize(n, value); }
        vector(int n, const T &value) { fill_initialize(static_cast<size_type>(n), value); }
        vector(long n, const T &value) { fill_initialize(static_cast<size_type>(n), value); }
        explicit vector(size_type n) { fill_initialize(static_cast<size_type>(n), T()); }

        ~vector() {
            destroy(start, finish);
            deallocate();
        }

        reference front() { return *begin(); }
        reference back() { return *(end() - 1); }

        void push_back(const T &x) {
            if (finish != end_of_storge) {
                construct(finish, x);
                ++finish;
            } else {
                insert_aux(finish, x);
            }
        }

        void pop_back() {
            --finish;
            destroy(finish);
        }

        iterator erase(iterator position) {
            if (position + 1 != finish)
                iterator i = copy(position + 1, finish, position);
            --finish;
            destroy(finish);
            return position;
        }

        iterator erase(iterator first, iterator last) {
            iterator i = copy(last, finish, first);
            destroy(i, finish);
            finish -= last - first;
            return first;
        }

        void insert(iterator position, const T &x) {

        }

        void insert(iterator position, size_type n, const T &x);

        void resize(size_type new_size, const T &x) {
            if (new_size <= size()) {
                erase(begin() + new_size, end());
            } else {
                insert(end(), new_size - size(), x);
            }
        }

        void resize(size_type new_size) { resize(new_size, T()); }
        void clear() { erase(start, finish); }

    protected:
        iterator allocate_and_fill(size_type n, const T &x) {
            iterator result = data_allocator::allocate(n);
            uninitialized_fill_n(result, n, x);
            return result;
        }
    };


    template <class T, class Alloc>
    void vector<T, Alloc>::insert_aux(iterator position, const T &x) {
        if (finish != end_of_storge) {
            construct(finish, *(finish - 1));
            copy_backward(position, finish - 1, finish);
            ++finish;
            T x_copy = x;
            *position = x_copy;
        } else {
            const size_type old_size = size();
            const size_type len = ((old_size == 0) ? 1 : (2 * old_size));
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;
            try {
                new_finish = uninitialized_copy(start, position, new_start);
                construct(new_finish, x);
                ++new_finish;
                new_finish = uninitialized_copy(position, finish, new_finish);
            } catch(...) {
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, len);
                throw;
            }
            destroy(start, finish);
            deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storge = start + len;
        }
    }

    template <class T, class Alloc>
    void
    vector<T, Alloc>::insert(iterator position, size_type n, const T &x) {
        if (n == 0) return;
        if (size_type(end_of_storge - finish) >= n) {
            const size_type elem_after = finish - position;
            T x_copy = x;
            if (elem_after > n) {
                uninitialized_copy(finish - n, finish, finish);
                copy_backward(position, finish - n, finish);
                finish += n;
                fill_n(position, n, x_copy);
            } else {
                uninitialized_fill_n(finish, n - elem_after, x_copy);
                uninitialized_copy(position, finish, position + n);
                fill(position, finish, x_copy);
                finish += n;
            }
        } else {
            const size_type old_size = size();
            const size_type new_size = old_size + (old_size > n ? old_size : n);
            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            try {
                new_finish = uninitialized_copy(start, position, new_start);
                new_finish = uninitialized_fill_n(new_finish, n, x);
                new_finish = uninitialized_copy(position, finish, new_finish);
            } catch(...) {
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_size);
                throw;
            }
            destroy(start, finish);
            deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storge = start + new_size;
        }
    }


}

#endif /* TTSTL_STL_VECTOR_H */