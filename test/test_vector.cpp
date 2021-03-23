#include <iostream>
#include <algorithm>

#include "stl_vector.h"

using tt::vector;
using std::cout;
using std::endl;

int main() {
    vector<int> iv(2, 9);
    cout << "size = " << iv.size() << endl;          // size = 2
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 2
    for (int i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';                        // 9 9
    cout << endl;

    iv.push_back(1);
    cout << "size = " << iv.size() << endl;          // size = 3
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 4

    iv.push_back(2);
    cout << "size = " << iv.size() << endl;          // size = 4
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 4

    iv.push_back(3);
    cout << "size = " << iv.size() << endl;          // size = 5
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 8

    iv.push_back(4);
    cout << "size = " << iv.size() << endl;          // size = 6
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 8
    for (int i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';                        // 9 9 1 2 3 4
    cout << endl;

    iv.push_back(5);
    cout << "size = " << iv.size() << endl;          // size = 7
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 8
    for (int i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';                        // 9 9 1 2 3 4 5
    cout << endl;

    iv.pop_back();
    iv.pop_back();
    cout << "size = " << iv.size() << endl;          // size = 5
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 8

    iv.pop_back();
    cout << "size = " << iv.size() << endl;          // size = 4
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 8

    vector<int>::iterator ivite = iv.begin() + 2;
    iv.erase(ivite);
    cout << "size = " << iv.size() << endl;          // size = 3
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 8
    for (int i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';                        // 9 9 2
    cout << endl;

    vector<int>::iterator ite = iv.begin() + 2;
    iv.insert(ite, 3, 7);
    cout << "size = " << iv.size() << endl;          // size = 6
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 8
    for (int i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';                        // 9 9 7 7 7 2
    cout << endl;

    iv.clear();
    cout << "size = " << iv.size() << endl;          // size = 0
    cout << "capacity = " << iv.capacity() << endl;  // capacity = 8

    return 0;
}