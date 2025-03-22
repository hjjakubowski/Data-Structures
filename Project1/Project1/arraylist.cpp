#include "arraylist.h"

Arraylist::Arraylist(int capacity) : size(0), capacity(capacity) { 
    arr = new int[capacity]; 
}


Arraylist::~Arraylist() {
    delete[] arr;
}

void Arraylist::increaseSize() {
    if (size == capacity) {
        capacity *= 2;
        int* temp = new int[capacity];

        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        
    }
}

int Arraylist::getSize() const {
    return size;
}

int Arraylist::getCapacity() const {
    return capacity;
}

void Arraylist::push_back(int item) {
    increaseSize();
    arr[size] = item;
    size++;
}

void Arraylist::pop_back() {
    if (size > 0) {
        size--;
    }
}

void Arraylist::display() const {
    std::cout << "ArrayList: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
