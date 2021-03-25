#include <iostream>
#include <algorithm>

#include "stl_deque.h"
#include "stl_alloc.h"

using std::cout;
using std::endl;
using tt::deque;
using tt::alloc;

int main() {
    deque<int, alloc, 32> ideq(20, 9);
    cout << "size = " << ideq.size() << endl; // size = 20

    for (int i = 0; i < ideq.size(); ++i)
        ideq[i] = i;
    
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';               // 0 1 2 3 4 5 6 ... 19
    cout << endl;

    for (int i = 0; i < 3; i++)
        ideq.push_back(i);

    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';               // 0 1 2 3 ... 19 0 1 2
    cout << endl;
    cout << "size = " << ideq.size() << endl; // size = 23

    ideq.push_back(3);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';               // 0 1 2 3 ... 19 0 1 2 3
    cout << endl;
    cout << "size = " << ideq.size() << endl; // size = 24

    ideq.push_front(99);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';               // 99 0 1 2 3 ... 19 0 1 2 3
    cout << endl;
    cout << "size = " << ideq.size() << endl; // size = 25

    ideq.push_front(98);
    ideq.push_front(97);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';               // 97 98 99 0 1 2 3 ... 19 0 1 2 3
    cout << endl;
    cout << "size = " << ideq.size() << endl; // size = 27

    deque<int, alloc, 32>::iterator itr;
    itr = ideq.begin() + 2;
    cout << *itr << endl;                     // 99
    cout << *(itr.cur) << endl;               // 99

    return 0;
}