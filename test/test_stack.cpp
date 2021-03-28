#include <iostream>
#include <algorithm>
#include <list>
#include "stl_stack.h"
#include "stl_list.h"

using std::cout;
using std::endl;
using tt::stack;

int main() {
    // {
    //     // 由于deque的问题，目前无法通过 
    //     stack<int> istack;
    //     istack.push(1);
    //     istack.push(3);
    //     istack.push(5);
    //     istack.push(7);

    //     cout << istack.size() << endl; // 4
    //     cout << istack.top() << endl;  // 7

    //     istack.pop(); cout << istack.top() << endl; // 5
    //     istack.pop(); cout << istack.top() << endl; // 3
    //     istack.pop(); cout << istack.top() << endl; // 1
    //     cout << istack.size() << endl; // 1
    // }
    {
        stack<int, tt::list<int>> istack;
        istack.push(1);
        istack.push(3);
        istack.push(5);
        istack.push(7);

        cout << istack.size() << endl; // 4
        cout << istack.top() << endl;  // 7

        istack.pop(); cout << istack.top() << endl; // 5
        istack.pop(); cout << istack.top() << endl; // 3
        istack.pop(); cout << istack.top() << endl; // 1
        cout << istack.size() << endl; // 1
    }
    {
        stack<int, std::list<int>> istack;
        istack.push(1);
        istack.push(3);
        istack.push(5);
        istack.push(7);

        cout << istack.size() << endl; // 4
        cout << istack.top() << endl;  // 7

        istack.pop(); cout << istack.top() << endl; // 5
        istack.pop(); cout << istack.top() << endl; // 3
        istack.pop(); cout << istack.top() << endl; // 1
        cout << istack.size() << endl; // 1
    }
    return 0;
}