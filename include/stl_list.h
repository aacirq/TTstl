#ifndef TTSTL_STL_LIST_H
#define TTSTL_STL_LIST_H

#include "iterator.h"
#include "stl_alloc.h"
#include "stl_construct.h"

namespace tt {

    template <class T>
    struct _list_node {
        typedef _list_node * link_type;
        link_type prev;
        link_type next;
        T data;
    };

    template <class T, class Ref, class Ptr> // TODO 为什么设置Ref和Ptr模板呢？
    struct _list_iterator {
        typedef _list_iterator<T, T&, T*>   iterator;
        typedef _list_iterator<T, Ref, Ptr> self;

        typedef bidirectional_iterator_tag iterator_category;
        typedef T              value_type;
        typedef T &            reference;
        typedef T *            pointer;
        typedef ptrdiff_t      difference_type;
        typedef size_t         size_type;
        typedef _list_node<T>* link_type;

        link_type node;

        _list_iterator() {}
        _list_iterator(link_type x) : node(x) {}
        _list_iterator(const iterator &x) : node(x.node) {}

        bool operator == (const self &rhs) const { return node == rhs.node; }
        bool operator != (const self &rhs) const { return node != rhs.node; }

        reference operator * () { return node->data; }
        pointer operator -> () { return &(operator*()); } // TODO 再理解一下这里
        self & operator ++ () {
            node = node->next;
            return *this;
        }
        self operator ++ (int) {
            self tmp = *this;
            ++(*this);
            return tmp;
        }
        self & operator -- () {
            node = node->prev;
            return *this;
        }
        self operator -- (int) {
            self tmp = *this;
            --(*this);
            return tmp;
        }
    };

    template <class T, class Alloc = alloc>
    class list {
    protected:
        typedef _list_node<T> list_node;
        typedef simple_alloc<list_node, Alloc> list_node_allocator;

    public:
        typedef list_node*                 link_type;
        typedef _list_iterator<T, T&, T*>  iterator;
        typedef size_t                     size_type;
        typedef T&                         reference;

    protected:
        link_type node;

    protected:
        link_type get_node() { return (link_type)(list_node_allocator::allocate()); }
        void put_node(link_type p) { list_node_allocator::deallocate(p); }
        link_type create_node(const T &x) {
            link_type p = get_node();
            construct(&(p->data), x);
            return p;
        }
        void destroy_node(link_type p) {
            destroy(&(p->data));
            put_node(p);
        }

    public:
        iterator begin() { return iterator(node->next); }
        iterator end() { return iterator(node); }
        bool empty() const { return node->next == node; }
        size_type size() const { return distance(iterator(node->next), iterator(node)); } // 解决const问题，begin()和end()无法在const对象中使用
        // 取最前面的元素data
        reference front() { return *begin(); }
        // 取最后面的元素data
        reference back() { return *end(); }

    public:
        list() { empty_initialize(); }

        iterator insert(iterator position, const T &x) {
            link_type new_node = create_node(x);
            new_node->next = position.node;
            new_node->prev = position.node->prev;
            position.node->prev->next = new_node;
            position.node->prev = new_node;
            return iterator(new_node);
        }

        void push_front(const T &x) { insert(begin(), x); }
        void push_back(const T &x) { insert(end(), x); }

        iterator erase(iterator position) {
            link_type prev_node = position.node->prev;
            link_type next_node = position.node->next;
            prev_node->next = next_node;
            next_node->prev = prev_node;
            destroy_node(position.node);
            return iterator(next_node);
        }

        void pop_front() { erase(begin()); }
        void pop_back() {
            link_type tmp = end();
            erase(--tmp);
        }

        // 清除所有结点
        void clear();
        // 将数值value的所有元素移除
        void remove(const T &value);
        // 如果存在连续的相同的元素，只保留一个
        void unique();
        // 将[first, last)区间内的所有元素移动到position前面
        void transfer(iterator position, iterator first, iterator last);
        // 将x合并到*this上，x和*this都是递增序列
        void merge(list<T, Alloc> &x);
        // 反方向
        void reverse();
        // 升序排序，quick sort
        void sort();

        // 将列表x接到position之前
        void splice(iterator position, list &x) {
            if (!x.empty()) {
                transfer(position, x.begin(), x.end());
            }
        }
        void splice(iterator position, list &, iterator i) {
            iterator j = i;
            ++j;
            if (position == i || position == j) return;
            transfer(position, i, j);
        }
        void splice(iterator position, list &, iterator first, iterator last) {
            if (last != position) {
                transfer(position, first, last);
            }
        }

        void swap(list<T, Alloc> &rhs) {
            link_type tmp = node;
            node = rhs.node;
            rhs.node = tmp;
        }


    protected:
        void empty_initialize() {
            node = get_node();
            node->next = node;
            node->prev = node;
        }
    };

    template <class T, class Alloc>
    void list<T, Alloc>::clear() {
        link_type cur = node->next;
        while (cur != node) {
            link_type tmp = cur;
            cur = cur->next;
            destroy_node(tmp);
        }
        node->next = node;
        node->prev = node;
    }
    
    template <class T, class Alloc>
    void list<T, Alloc>::remove(const T &value) {
        iterator cur = begin();
        iterator last = end();
        while (cur != last) {
            iterator tmp = cur;
            ++tmp;
            if (*tmp == value)
                erase(tmp);
            cur = tmp;
        }
    }
    
    template <class T, class Alloc>
    void list<T, Alloc>::unique() {
        iterator cur = begin();
        iterator last = end();
        if (cur == last) return;
        iterator next = cur;
        while (++next != last) {
            if (*cur == *next) {
                erase(next);
                next = cur;
            } else {
                cur = next;
            }
        }
    }

    template <class T, class Alloc>
    void list<T, Alloc>::transfer(iterator position, iterator first, iterator last) {
        if (position != last) {
            link_type tmp = last.node->prev;
            first.node->prev->next = last.node;
            last.node->prev = first.node->prev;
            position.node->prev->next = first.node;
            first.node->prev = position.node->prev;
            position.node->prev = tmp;
            tmp->next = position.node;
        }
    }

    template <class T, class Alloc>
    void list<T, Alloc>::merge(list<T, Alloc> &x) {
        iterator cur = x.begin();
        iterator this_cur = this->begin();
        while (cur != x.end() && this_cur != this->end()) {
            if (*cur < *this_cur) {
                iterator now = cur;
                transfer(this_cur, now, ++cur);
            } else {
                ++this_cur;
            }
        }
        if (cur != x.end()) {
            transfer(this->end(), cur, x.end());
        }
    }
    
    template <class T, class Alloc>
    void list<T, Alloc>::reverse() {
        // TODO 思考有没有更高效的实现
        if (node->next == node || node->next->next == node)
            return;
        iterator first = this->begin();
        ++first;
        while (first != this->end()) {
            iterator old = first;
            ++first;
            transfer(begin(), old, first);
        }
    }

    template <class T, class Alloc>
    void list<T, Alloc>::sort() {
        list<T, Alloc> carry;
        list<T, Alloc> capacity[64];
        int fill = 0;
        while (!this->empty()) {
            carry.splice(carry.begin(), *this, this->begin());
            int i = 0;
            while (!capacity[i].empty()) {
                carry.merge(capacity[i++]);
            }
            carry.swap(capacity[i]);
            if (i >= fill) fill = i;
        }
        for (int i = 1; i <= fill; ++i) {
            capacity[i].merge(capacity[i-1]);
        }
        this->swap(capacity[fill]);
    }

}

#endif