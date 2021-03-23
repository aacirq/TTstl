#include <iostream>
#include <algorithm>

#include "stl_list.h"

using std::cout;
using std::endl;
using tt::list;

int main() {
    int i;
    list<int> ilist;
    cout << "size = " << ilist.size() << endl;  // size = 0

    ilist.push_back(0);
    ilist.push_back(1);
    ilist.push_back(2);
    ilist.push_back(3);
    ilist.push_back(4);

    cout << "size = " << ilist.size() << endl;  // size = 5
    
    list<int>::iterator ite;
    for (ite = ilist.begin(); ite != ilist.end(); ++ite)
        cout << *ite << ' ';                    // 0 1 2 3 4
    cout << endl;

    ite = ilist.begin();
    ++++++ite;
    if (ite != 0)
        ilist.insert(ite, 99);
    
    cout << "size = " << ilist.size() << endl;  // size = 6
    cout << *ite << endl;

    for (ite = ilist.begin(); ite != ilist.end(); ++ite)
        cout << *ite << ' ';                    // 0 1 2 99 3 4
    cout << endl;

    ite = ilist.begin();
    ++ite;
    if (ite != 0)
        cout << *(ilist.erase(ite)) << endl;    // 2
    
    for (ite = ilist.begin(); ite != ilist.end(); ++ite)
        cout << *ite << ' ';                    // 0 2 99 3 4
    cout << endl;

    return 0;
}