#ifndef TTSTL_STL_DEQUE_H
#define TTSTL_STL_DEQUE_H

#include <cstddef>

#include "iterator.h"
#include "stl_alloc.h"
#include "stl_uninitialized.h"

namespace tt {

    inline size_t _deque_bufer_size(size_t n, size_t sz) {
        return n != 0 ? n : (sz < 512 ? size_t(512/sz) : size_t(1));
    }

    template <class T, class Ref, class Ptr, size_t BufSiz>
    struct _deque_iterator {
        typedef _deque_iterator<T, T&, T*, BufSiz>             iterator;
        typedef _deque_iterator<T, const T&, const T*, BufSiz> const_iterator;

        static size_t buffer_size() { return _deque_bufer_size(BufSiz, sizeof(T)); }

        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef Ref                         reference;
        typedef Ptr                         pointer;
        typedef ptrdiff_t                   difference_type;

        typedef value_type*   pointer_type;
        typedef pointer_type* map_pointer;

        typedef _deque_iterator self;

        T *first;
        T *last;
        T *cur;
        map_pointer node;

        void set_node(map_pointer new_node) {
            node = new_node;
            first = *new_node;
            last = *new_node + buffer_size();
        }

        reference operator * () const { return *cur; }
        pointer_type operator -> () const { return &(operator*()); }
        difference_type operator - (const self &x) const {
            return (node - x.node - 1) * buffer_size() + (cur - first) + (x.last - x.cur);
        }
        self & operator ++ () {
            if (cur + 1 == last) {
                set_node(node + 1);
                cur = first;
            } else {
                ++cur;
            }
            return *this;
        }
        self operator ++ (int) {
            self tmp = *this;
            ++(*this);
            return tmp;
        }
        self & operator -- () {
            if (cur == first) {
                set_node(node - 1);
                cur = last - 1;
            } else {
                --cur;
            }
            return *this;
        }
        self operator -- (int) {
            self tmp = *this;
            --(*this);
            return tmp;
        }
        self & operator += (difference_type n) {
            difference_type offset = cur - first + n;
            if (offset > 0 && offset < buffer_size()) {
                cur += n;
            } else {
                difference_type node_offset;
                if (offset >= 0) {
                    node_offset = offset / buffer_size();
                } else {
                    node_offset = (offset + 1) / buffer_size() - 1;
                }
                set_node(node + node_offset);
                cur = first + (offset - node_offset * buffer_size());
            }
            return *this;
        }
        self operator + (difference_type n) const {
            self tmp = *this;
            return tmp += n;
        }
        self & operator -= (difference_type n) {
            return (*this += (-n));
        }
        self operator - (difference_type n) const {
            self tmp = *this;
            return tmp -= n;
        }
        reference operator [] (difference_type n) const {
            return *(*this + n);
        }
        bool operator == (const self &rhs) const {
            return cur == rhs.cur;
        }
        bool operator != (const self &rhs) const {
            return cur != rhs.cur;
        }
        bool operator < (const self &rhs) const {
            return node == rhs.node ? (cur < rhs.cur) : (node < rhs.node);
        }
    };

    template <class T, class Alloc = alloc, size_t BufSiz = 0>
    class deque {
    public:
        typedef T            value_type;
        typedef value_type*  pointer_type;
        typedef size_t       size_type;
    
    public:
        typedef _deque_iterator<T, T&, T*, BufSiz>  iterator;
        typedef typename iterator::difference_type  difference_type;
        typedef typename iterator::reference        reference;
        typedef typename iterator::const_iterator::reference const_reference;
    
    protected:
        typedef pointer_type*  map_pointer;

        typedef simple_alloc<value_type, Alloc> data_allocator;
        typedef simple_alloc<pointer_type, Alloc> node_allocator;
    
    protected:
        iterator start;
        iterator finish;

        map_pointer map;
        size_type   map_size;
    
    public:
        iterator begin() { return start; }
        iterator end() { return finish; }
        reference operator [] (size_type n) { return start[difference_type(n)]; }
        reference front() { return *start; }
        reference back() {
            iterator tmp = finish;
            --tmp;
            return *tmp;
        }
        size_type size() const { return size_type(finish - start); }
        bool empty() const { return start == finish; }

    public:
        // TODO 补充默认构造函数

        deque(int n, const value_type &x) : start(), finish(), map(0), map_size(0) {
            fill_initialization(n, x);
        }
    
    protected:
        static size_type buffer_size() { return iterator::buffer_size(); }
        size_type initial_map_size() { return 8; }

        void fill_initialization(size_type n, const value_type &x);
        void create_map_and_nodes(size_type num_elem);
        void destroy_all();
        void deallocate_all();
    
    protected:
        void reserve_map_at_back(size_type nodes_to_add = 1) {
            if (nodes_to_add + 1 > map_size - (finish.node - map)) {
                reallocate_map(nodes_to_add, false);
            }
        }

        void reserve_map_at_front(size_type nodes_to_add = 1) {
            if (nodes_to_add > start.node - map) {
                reallocate_map(nodes_to_add, true);
            }
        }

        void push_back_aux(const value_type &x);
        void push_front_aux(const value_type &x);
        void reallocate_map(size_type nodes_to_add, bool add_at_front);
        iterator insert_aux(iterator pos, const value_type &x);

    public:
        void push_back(const value_type &x) {
            if (finish.cur + 1 != finish.last) {
                construct(finish.cur, x);
                ++finish.cur;
            } else {
                push_back_aux(x);
            }
        }

        void push_front(const value_type &x) {
            if (start.cur != start.first) {
                --start.cur;
                construct(start.cur, x);
            } else {
                push_front_aux(x);
            }
        }

        void pop_back() {
            if (finish.cur != finish.first) {
                --finish.cur;
                destroy(finish.cur);
            } else {
                data_allocator::deallocate(finish.first);
                finish.set_node(finish.node - 1);
                finish.cur = finish.last - 1;
                destroy(finish.cur);
            }
        }

        void pop_front() {
            if (start.cur + 1 != start.last) {
                destroy(start.cur);
                ++start.cur;
            } else {
                destroy(start.cur);
                data_allocator::deallocate(start.first);
                start.set_node(start.node + 1);
                start.cur = start.first;
            }
        }

        void clear();
        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);
        iterator insert(iterator pos, const value_type &x);
    };

    template <class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::fill_initialization(size_type n, const value_type &x) {
        create_map_and_nodes(n);
        value_type x_copy = x;
        try {
            for (map_pointer cur = start.node; cur < finish.node; ++cur) {
                uninitialized_fill(*cur, *cur + buffer_size(), x_copy);
            }
            uninitialized_fill(finish.first, finish.cur, x_copy);
        } catch(...) {
            destroy_all();
            deallocate_all();
            throw;
        }
    }

    template <class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::create_map_and_nodes(size_type num_elem) {
        int num_nodes = num_elem / buffer_size() + 1;
        // map_size = max(initial_map_size(), num_nodes + 2);
        map_size = initial_map_size() > (num_nodes+2) ? initial_map_size() : (num_nodes+2);
        map = node_allocator::allocate(map_size);

        map_pointer node_start = map + (map_size - num_nodes) / 2;
        map_pointer node_finish = node_start + num_nodes - 1;
        try {
            for (map_pointer cur = node_start; cur <= node_finish; ++cur) {
                *cur = data_allocator::allocate(buffer_size());
            }
        } catch (...) {
            for (map_pointer cur = node_start; cur <= node_finish; ++cur) {
                data_allocator::deallocate(*cur, buffer_size());
            }
            node_allocator::deallocate(map, map_size);
            throw;
        }
        start.set_node(node_start);
        finish.set_node(node_finish);
        start.cur = start.first;
        finish.cur = finish.first + num_elem % buffer_size();
    }

    template <class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::destroy_all() {
        if (start.node == finish.node) {
            destroy(start.cur, finish.cur);
        } else {
            for (map_pointer cur = start.node + 1; cur < finish.node; ++cur) {
                destroy(*cur, *cur + buffer_size());
            }
            destroy(start.cur, start.last);
            destroy(finish.first, finish.cur);
        }
    }

    template <class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::deallocate_all() {
        if (start.node == finish.node) {
            data_allocator::deallocate(start.first, buffer_size());
        } else {
            for (map_pointer cur = start.node; cur < finish.node; ++cur) {
                data_allocator::deallocate(*cur, buffer_size());
            }
        }
        node_allocator::deallocate(map, map_size);
    }

    // TODO 需要思考所有try{}catch(){}中catch(){}部分是否合理

    template <class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::push_back_aux(const value_type &x) {
        reserve_map_at_back();
        map_pointer node_last = finish.node + 1;
        value_type x_copy = x;
        *node_last = data_allocator::allocate(buffer_size());
        try {
            construct(finish.cur, x_copy);
            finish.set_node(node_last);
            finish.cur = finish.first;
        } catch (...) {
            data_allocator::deallocate(*node_last, buffer_size());
            throw;
        }
    }

    template <class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::push_front_aux(const value_type &x) {
        reserve_map_at_front();
        map_pointer new_front_node = start.node - 1;
        value_type x_copy = x;
        *new_front_node = data_allocator::allocate(buffer_size());
        try {
            start.set_node(new_front_node);
            start.cur = start.last - 1;
            construct(start.cur, x_copy);
        } catch(...) {
            start.set_node(new_front_node + 1);
            start.cur = start.first;
            data_allocator::deallocate(*new_front_node, buffer_size());
            throw;
        }
    }

    template <class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::reallocate_map(size_type nodes_to_add, bool add_at_front) {
        size_type old_num_nodes = finish.node - start.node + 1;
        size_type new_num_nodes = old_num_nodes + nodes_to_add;
        map_pointer new_start;
        if (map_size > 2 * new_num_nodes) {
            new_start = map + (map_size-new_num_nodes)/2 + (add_at_front ? nodes_to_add : 0);
            if (new_start < start.node) {
                copy(start.node, finish.node, new_start);
            } else {
                copy_backward(start.node, finish.node, new_start + old_num_nodes);
            }
        } else {
            size_type new_map_size = map_size + (map_size > new_num_nodes ? map_size : new_num_nodes) + 2;
            map_pointer new_map = node_allocator::allocate(new_map_size);
            new_start = new_map + (new_map_size-new_num_nodes)/2 + (add_at_front ? nodes_to_add : 0);
            copy(start.node, finish.node + 1, new_start);
            node_allocator::deallocate(map, old_num_nodes);
            map = new_map;
            map_size = new_map_size;
        }
        start.set_node(new_start);
        finish.set_node(new_start + old_num_nodes - 1);
    }

    template <class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::clear() {
        if (start.node == finish.node) {
            destroy(start.cur, finish.cur);
        } else {
            for (map_pointer cur = start.node + 1; cur < finish.node; ++cur) {
                destroy(*cur, *cur + buffer_size());
                data_allocator::deallocate(*cur, buffer_size());
            }
            destroy(finish.first, finish.cur);
            data_allocator::deallocate(*(finish.node), buffer_size());
            destroy(start.cur, start.last);
        }
        finish = start;
    }

    template <class T, class Alloc, size_t BufSiz>
    typename deque<T, Alloc, BufSiz>::iterator
    deque<T, Alloc, BufSiz>::erase(iterator pos) {
        difference_type index = pos - start;
        iterator next = pos + 1;
        if (index < size()/2) {
            copy_backward(start, pos, next);
            pop_front();
        } else {
            copy(next, finish, pos);
            pop_back();
        }
        return start + index;
    }

    template <class T, class Alloc, size_t BufSiz>
    typename deque<T, Alloc, BufSiz>::iterator 
    deque<T, Alloc, BufSiz>::erase(iterator first, iterator last) {
        if (first == start && last == finish) {
            clear();
            return finish;
        } else {
            difference_type len_front = first - start;
            difference_type len_back = finish - last - 1;
            difference_type n = last - first;
            if (len_front < len_back) {
                copy_backward(start, first, last);
                iterator new_start = start + n;
                destroy(start, new_start);
                for (map_pointer cur = start.node; cur < new_start.node; ++cur) {
                    data_allocator::deallocate(*cur, buffer_size());
                }
                start = new_start;
            } else {
                copy(last, finish, first);
                iterator new_finish = finish - n;
                destroy(new_finish, finish);
                for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur) {
                    data_allocator::deallocate(*cur, buffer_size());
                }
                finish = new_finish;
            }
            return start + len_front;
        }
    }

    template <class T, class Alloc, size_t BufSiz>
    typename deque<T, Alloc, BufSiz>::iterator 
    deque<T, Alloc, BufSiz>::insert(iterator pos, const value_type &x) {
        if (pos == begin()) {
            push_front(x);
            return start;
        } else if (pos == end()) {
            push_back(x);
            return finish - 1;
        } else {
            return insert_aux(pos, x);
        }
    }

    template <class T, class Alloc, size_t BufSiz>
    typename deque<T, Alloc, BufSiz>::iterator 
    deque<T, Alloc, BufSiz>::insert_aux(iterator pos, const value_type &x) {
        difference_type len_front = pos - start;
        value_type x_copy = x;
        if (len_front < size()/2) {
            push_front(front());
            copy(start + 2, pos, start + 1);
            --pos;
        } else {
            push_back(back());
            copy_backward(pos, finish - 2, finish - 1);
        }
        *pos = x_copy;
        return pos;
    }

}

#endif /* TTSTL_STL_DEQUE_H */