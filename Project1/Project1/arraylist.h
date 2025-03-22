#pragma once
#include <iostream>
using namespace std;

class Arraylist {
private:
    int* arr;
    int size;
    int capacity;

    void increaseSize();

public:
    Arraylist(int capacity);
    ~Arraylist();

    int getSize() const;
    int getCapacity() const;

    void push_back(int item);
    void pop_back();
    void display() const;
};

