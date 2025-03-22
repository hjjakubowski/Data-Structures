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

void Arraylist::push_front(int item) {
    increaseSize();
    for (int i = size; i > 0; i--) {
        arr[i] = arr[i-1];
    }
    arr[0] = item;
    size++;
}

void Arraylist::push_index(int item, int index) {
    increaseSize();
    for (int i = size; i >= size-index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = item;
    size++;
}

void Arraylist::pop_back() {
    if (size > 0) {
        size--;
    }
}

void Arraylist::pop_front() {
    if (size > 0) {
        for (int i = 1; i < size; i++) {
            arr[i-1] = arr[i];
        }
        size--;
    }
}

void Arraylist::pop_index(int index) {
    if (size > 0) {
        for (int i = index; i < size; i++) {
            arr[i] = arr[i+1];
        }
        size--;
    }
}

int Arraylist::find(int item) {
    int index;
    for (int i = 0; i < size; i++) {
        if (arr[i] == item) {
            index = i;
            return index;
        }
    }
    return -1;
}

void Arraylist::display() const {
    std::cout << "ArrayList: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
