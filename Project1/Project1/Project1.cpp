#include <iostream>
#include "arraylist.h"

using namespace std;
int main()
{
    Arraylist arr(2);

    for (int i = 0; i < 5000; i++) {
        arr.push_back(i);
    }
    for (size_t i = 0; i < 2500; i++) {
        arr.pop_back();
    }
    arr.display();
}

