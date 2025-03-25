#pragma once
#include "Node.h"
#include "iostream"
class Singlelist {
private:
    int size;
    Node* head;

public:
    Singlelist();
    ~Singlelist();

    int getSize() const;

    void push_back(int item);
    void push_front(int item);
    void push_index(int item, int index);

    void pop_back();
    void pop_front();
    void pop_index(int index);

    int& operator[](const int index);
};
