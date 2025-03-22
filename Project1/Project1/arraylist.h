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
    void push_front(int item);
    void push_index(int item, int index);
    void pop_back();
    void pop_front();
    void pop_index(int index);
    void display() const;
};

