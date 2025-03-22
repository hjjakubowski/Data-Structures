#include <iostream>
#include "arraylist.h"

using namespace std;
int main()
{
    Arraylist arr(2);

    for (int i = 0; i < 4; i++) {
        arr.push_back(i);
    }
    arr.push_front(6);
    /*for (size_t i = 0; i < 2500; i++) {
        arr.pop_back();
    }*/
    int item_index = arr.find(9);
    if (item_index != -1) {
        cout << "Index of your item : " << item_index << endl;
    }
    else {
        cout << "There is no such item included in the given list" << endl;
    }
    arr.display();
}

