#include <iostream>
#include <deque>
#include <list>
#include <algorithm>

#include "stl_algobase.h"
#include "iterator.h"

using std::cout; using std::endl;
using std::deque;
using std::list;
using std::for_each;
using namespace tt;

template <typename T>
struct display {
    void operator()(const T &x) {
        cout << x << ' ';
    }
};

void test_copy();
void test_copy_backward();

int main() {
    test_copy_backward();
    return 0;
}

void test_copy() {
    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        tt::copy(ia+2, ia+7, ia);
        for_each(ia, ia+9, display<int>()); // 2 3 4 5 6 5 6 7 8
        cout << endl;
    }
    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        tt::copy(ia+2, ia+7, ia+4);
        for_each(ia, ia+9, display<int>()); // 0 1 2 3 2 3 4 5 6
        cout << endl;
    }
    // {
    //     // TODO ERROR，std::deque无法和tt::copy联合起来用
    //     int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    //     deque<int> id(ia, ia+9);

    //     auto first = id.begin();
    //     auto last = id.end();
    //     // TODO advance()没法用，iterator.h中的内容无法与STL合起来用
    //     // tt::advance(first, 2);
    //     ++++first;
    //     cout << *first << endl; // 2
    //     // TODO advance()没法用，iterator.h中的内容无法与STL合起来用
    //     // tt::advance(first, -2);
    //     ----last;
    //     cout << *last << endl; // 7

    //     auto result = id.begin();
    //     cout << *result << endl; // 0

    //     tt::copy(first, last, result);
    //     for_each(id.begin(), id.end(), display<int>()); // 2 3 4 5 6 5 6 7 8
    //     cout << endl;
    // }
    // {
    //     // TODO ERROR，std::deque无法和tt::copy联合起来用
    //     int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    //     deque<int> id(ia, ia+9);
    //     auto first = id.begin();
    //     auto last = id.end();
    //     ++++first;
    //     cout << *first << endl; // 2
    //     ----last;
    //     cout << *last << endl; // 7

    //     auto result = id.begin();
    //     // TODO advance()没法用，iterator.h中的内容无法与STL合起来用
    //     // tt::advance(result, 4);
    //     ++++result;
    //     ++++result;
    //     cout << *result << endl; // 4

    //     tt::copy(first, last, result);
    //     // TODO 这个输出有问题，输出结果是0 1 2 3 2 3 4 5 6，是不是用的STL的deque的原因？
    //     for_each(id.begin(), id.end(), display<int>()); // 0 1 2 3 2 3 2 3 2
    //     cout << endl;
    // }
}

void test_copy_backward() {
    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        tt::copy_backward(ia+2, ia+7, ia+9);
        for_each(ia, ia+9, display<int>()); // 0 1 2 3 2 3 4 5 6
        cout << endl;
    }
    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        copy_backward(ia+2, ia+7, ia+5);
        for_each(ia, ia+9, display<int>()); // 2 3 4 5 6 5 6 7 8
        cout << endl;
    }
    // {
    //     // TODO advance()没法用，iterator.h中的内容无法与STL合起来用
    //     int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    //     deque<int> id(ia, ia+9);

    //     auto first = id.begin();
    //     auto last = id.end();
    //     ++++first;
    //     cout << *first << endl;
    //     ----last;
    //     cout << *last << endl;

    //     auto result = id.end();
    //     tt::copy_backward(first, last, result);
    //     for_each(id.begin(), id.end(), display<int>());
    //     cout << endl;
    // }
    // {
    //     // TODO advance()没法用，iterator.h中的内容无法与STL合起来用
    //     int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    //     deque<int> id(ia, ia+9);

    //     auto first = id.begin();
    //     auto last = id.end();
    //     ++++first;
    //     cout << *first << endl;
    //     ----last;
    //     cout << *last << endl;

    //     auto result = id.begin();
    //     tt::advance(result, 5);
    //     cout << *result << endl;

    //     tt::copy_backward(first, last, result);
    //     for_each(id.begin(), id.end(), display<int>());
    //     cout << endl;
    // }
}