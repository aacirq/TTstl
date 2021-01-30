//
// Created by renxin on 2021/1/3.
//

#ifndef TTALGORITHM_BST_H
#define TTALGORITHM_BST_H

#include <iostream>

namespace tt {
    template <typename T>
    class BstNode {
    public:
        explicit BstNode(T k = T(), BstNode<T> *tp = nullptr, 
                         BstNode<T> *tl = nullptr, BstNode<T> *tr = nullptr) 
        : key(k), p(tp), left(tl), right(tr) { }
        // inline T           get_key()    const { return key; }
        // inline BstNode<T> *get_parent() const { return p; }
        // inline BstNode<T> *get_left()   const { return left; }
        // inline BstNode<T> *get_right()  const { return right; }

    public:
        T key;
        BstNode<T> *p;
        BstNode<T> *left;
        BstNode<T> *right;
    };

    template <typename T> void print_a_node(T &v);

    // TODO 需要考虑接口是否合理，private和public设置、类之间的关系是否合适
    template <typename T>
    class BST {
    public:
        explicit BST(BstNode<T> *r = nullptr) : root(r) { }
        ~BST();
        BstNode<T> *get_root() const { return root; }
        // TODO 1. 看看函数版本和lambda版本能不能合并
        // TODO 2. 查一下怎么样把lambda版本定义在外部，不是直接在类里面定义
        void inorder_walk(BstNode<T> *node, void (*fun)(T &v) = print_a_node);
        void inorder_walk(void (*fun)(T &v) = print_a_node);
        template <typename F> void inorder_walk(BstNode<T> *node, F const &f) {
            if (node != nullptr) {
                inorder_walk(node->left, f);
                f(node->key);
                inorder_walk(node->right, f);
            }
        }
        template <typename F> void inorder_walk(F const &f) {
            inorder_walk(this->root, f);
        }
        BstNode<T> *search(const T &k);
        BstNode<T> *minimum(BstNode<T> *node);
        BstNode<T> *minimum();
        BstNode<T> *maximum(BstNode<T> *node);
        BstNode<T> *maximum();
        BstNode<T> *predecessor(BstNode<T> *node);
        BstNode<T> *successor(BstNode<T> *node);
        void insert(const T &k);
        void remove(const T &k);
        void remove(BstNode<T> *node);

    private:
        void insert(BstNode<T> *node);
        void transplant(BstNode<T> *u, BstNode<T> *v);
        void remove_all(BstNode<T> *node);

        BstNode<T> *root;
    };

    template <typename T>
    void print_a_node(T &v) { std::cout << v << " "; }

    // deconstructor function
    // =========================================================================
    template <typename T>
    void BST<T>::remove_all(BstNode<T> *node) {
        if (node == nullptr) return;
        remove_all(node->left);
        remove_all(node->right);
        delete node;
    }

    template <typename T>
    BST<T>::~BST() {
        remove_all(root);
        root = nullptr;
    }

    // inorder walk
    // =========================================================================
    template <typename T>
    inline void BST<T>::inorder_walk(BstNode<T> *node, void (*fun)(T &v)) {
        if (node != nullptr) {
            inorder_walk(node->left, fun);
            fun(node->key);
            inorder_walk(node->right, fun);
        }
    }

    template <typename T>
    inline void BST<T>::inorder_walk(void (*fun)(T &v)) {
        inorder_walk(this->root, fun);
    }

    
    // template <typename T, typename F>
    // void BST<T>::inorder_walk(BstNode<T> *node, F const &f) {
    //     if (node != nullptr) {
    //         inorder_walk(node->left, f);
    //         f(node->key);
    //         inorder_walk(node->right, f);
    //     }
    // }

    // template <typename T, typename F>
    // void BST<T>::inorder_walk(F const &f) {
    //     inorder_walk(this->root, f);
    // }

    // tree search
    // =========================================================================
    template <typename T>
    inline BstNode<T> *BST<T>::search(const T &k) {
        BstNode<T> *node = root;
        while (node != nullptr && node->key != k) {
            if (k < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return node;
    }

    // tree minimum
    // =========================================================================
    template <typename T>
    inline BstNode<T> *BST<T>::minimum(BstNode<T> *node) {
        if (node == nullptr) return node;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    template <typename T>
    inline BstNode<T> *BST<T>::minimum() {
        return minimum(root);
    }

    // tree maximum
    // =========================================================================
    template <typename T>
    inline BstNode<T> *BST<T>::maximum(BstNode<T> *node) {
        if (node == nullptr) return node;
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    template <typename T>
    inline BstNode<T> *BST<T>::maximum() {
        return maximum(root);
    }

    // tree predecessor
    // =========================================================================
    template <typename T>
    BstNode<T> *BST<T>::predecessor(BstNode<T> *node) {
        if (node == nullptr) return nullptr;
        if (node->left != nullptr) return maximum(node->left);
        BstNode<T> *t_node = node->p;
        while (t_node != nullptr && t_node->left == node) {
            node = t_node;
            t_node = t_node->p;
        }
        return t_node;
    }

    // tree successor
    // =========================================================================
    template <typename T>
    BstNode<T> *BST<T>::successor(BstNode<T> *node) {
        if (node == nullptr) return nullptr;
        if (node->right != nullptr) return minimum(node->right);
        BstNode<T> *t_node = node->p;
        while (t_node != nullptr && t_node->right == node) {
            node = t_node;
            t_node = t_node->p;
        }
        return t_node;
    }

    // tree insert
    // =========================================================================
    template <typename T>
    void BST<T>::insert(BstNode<T> *node) {
        BstNode<T> *x = root;
        BstNode<T> *y = nullptr;
        while (x != nullptr) {
            y = x;
            if (node->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        node->p = y;
        if (y == nullptr) // root is nullptr
            root = node;
        else if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }

    template <typename T>
    void BST<T>::insert(const T &k) {
        insert(new BstNode<T>(k));
    }

    // tree delete
    // =========================================================================
    template <typename T>
    inline void BST<T>::transplant(BstNode<T> *u, BstNode<T> *v) {
        // 以v为root的树替代以u为root的树，不仅仅替代节点
        if (u->p == nullptr)
            root = v;
        else if (u->p->left == u)
            u->p->left = v;
        else
            u->p->right = v;
        if (v != nullptr)
            v->p = u->p;
    }

    template <typename T>
    void BST<T>::remove(BstNode<T> *node) {
        if (node->left == nullptr) {
            transplant(node, node->right);
        } else if (node->right == nullptr) {
            transplant(node, node->left);
        } else {
            BstNode<T> *t_node = minimum(node);
            if (t_node->p != node) {
                transplant(t_node, t_node->right);
                t_node->right = node->right;
                t_node->right->p = t_node;
            }
            transplant(node, t_node);
            t_node->left = node->left;
            t_node->left->p = t_node;
        }
        delete node;
    }

    template <typename T>
    void BST<T>::remove(const T &k) {
        BstNode<T> *node = search(k);
        remove(node);
    }
}

#endif // TTALGORITHM_BST_H
