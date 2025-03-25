#include <iostream>
#include "arraylist.h"
#include "SingleLinkList.h"
using namespace std;
int main()
{
    Singlelist list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }
    list.push_front(15);
    list.push_index(16, 1);
    list.pop_index(2);
    for (int i = 0; i < list.getSize(); i++) {
        cout << list[i] << endl;
    }

    cout << "Size  " << list.getSize();
}

