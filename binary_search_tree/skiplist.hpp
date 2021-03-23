//
// Created by aacirq.
//

#include <iostream>

#ifndef TTSTL_SKIPLIST_HPP
#define TTSTL_SKIPLIST_HPP

namespace tt {
    template <typename TK, typename TV>
    class SkipList {
    private:
        class _skip_list_node {
            TK _key;
            TV _value;
            int _level;
            _skip_list_node **_forward;
            _skip_list_node(const TK &k, const TV &v, int l = 1);
            ~_skip_list_node();
        };

        int _maxLevel;
        int _level;
        _skip_list_node *_head;

        int randomLevel();

    public:
        explicit SkipList(int ml = 32);
        const TV &search(const TK &key) const;
        bool empty() const;
        void insert(const TK &key, const TV &value);
        void erase(const TK &key);
    };

    template <typename TK, typename TV>
    SkipList<TK, TV>::_skip_list_node::_skip_list_node(const TK &k, const TV &v, int l)
            : _key(k), _value(v), _level(l) {
        _forward = new _skip_list_node[l][1];
        for (int i = 0; i < l; ++i) {
            _forward[i] = nullptr;
        }
    }

    template <typename TK, typename  TV>
    SkipList<TK, TV>::_skip_list_node::~_skip_list_node() {
        delete [] _forward;
    }

    template <typename TK, typename  TV>
    SkipList<TK, TV>::SkipList(int ml)
            : _maxLevel(ml), _level(1), _head(new _skip_list_node(TK(), TV(), _maxLevel)) {}

    template <typename TK, typename  TV>
    int SkipList<TK, TV>::randomLevel() {
        int l = 1;
        while (rand() % 100 < 50 && l < _maxLevel - 1) {
            ++l;
        }
        return l;
    }

    template <typename TK, typename  TV>
    const TV &SkipList<TK, TV>::search(const TK &key) const {
        // TODO 当搜索空表的时候怎么办
        _skip_list_node *node = _head;
        for (int i = _level - 1; i >= 0; --i) {
            while (node->_forward[i] && node->_forward[i]->_key < key) {
                node = node->_forward[i];
            }
        }
        if (node->_forward[0] && node->_forward[0]->_key == key)
            return node->_forward[0]->_value;
//        return failure; TODO
    }

    template <typename TK, typename TV>
    bool SkipList<TK, TV>::empty() const {
        return _level == 0;
    }

    template <typename TK, typename TV>
    void SkipList<TK, TV>::insert(const TK &key, const TV &value) {
        _skip_list_node *node = _head;
        _skip_list_node *update[_maxLevel];
        for (int i = _level - 1; i >= 0; --i) {
            while (node->_forward[i] && node->_forward[i]->_key < key) {
                node = node->_forward[i];
            }
            update[i] = node;
        }
        if (node->_forward[0] && node->_forward[0]->_key == key) {
            node->_forward[0]->_value = value;
        } else {
            int lev = randomLevel();
            _skip_list_node *newNode = new _skip_list_node(key, value, lev);
            if (newNode == nullptr) return;
            for (int i = 0; i < _level; ++i) {
                newNode->_forward[i] = update[i]->_forward[i];
                update[i]->_forward[i] = newNode;
            }
        }
    }

    template <typename TK, typename TV>
    void SkipList<TK, TV>::erase(const TK &key) {
        _skip_list_node *node = _head;
        _skip_list_node *update[_maxLevel];
        for (int i = _level; i >= 0; ++i) {
            while (node->_forward[i] && node->_forward[i]->_key < key) {
                node = node->_forward[i];
            }
            update[i] = node;
        }
        if (node->_forward[0] && node->_forward[0]->_key == key) {
            _skip_list_node *eraseNode = node->_forward[0];
            for (int i = 0; i <= _level; ++i) {
                if (update[i]->_forward[i] == eraseNode) {
                    update[i]->_forward[i] = eraseNode->_forward[i];
                }
            }
            delete eraseNode;
            while (_level > 0) {
                if (_head->_forward[_level] == nullptr) --_level;
            }
        }
    }
}

#endif //TTSET_SKIPLIST_HPP

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
