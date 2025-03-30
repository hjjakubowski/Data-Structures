#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Arraylist {
private:
    T* arr;
    int size;
    int capacity;

    void increaseSize();

public:
    Arraylist(int capacity = 2);
    ~Arraylist();

    int getSize() const;
    int getCapacity() const;

    void addBack(T item);
    void addFront(T item);
    void add(T item, int index);
    void removeBack();
    void removeFront();
    void remove(int index);

    int Find(T item) const;

    T& operator[](const int index);
};






template <typename T>
Arraylist<T>::Arraylist(int capacity) : size(0), capacity(capacity) {
    arr = new T[capacity];
}

template <typename T>
Arraylist<T>::~Arraylist() {
    delete[] arr;
}

template <typename T>
void Arraylist<T>::increaseSize() {
    if (size == capacity) {
        capacity *= 2;
        T* temp = new T[capacity];

        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
    }
}

template <typename T>
int Arraylist<T>::getSize() const {
    return size;
}

template <typename T>
int Arraylist<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void Arraylist<T>::addBack(T item) {
    increaseSize();
    arr[size] = item;
    size++;
}

template <typename T>
void Arraylist<T>::addFront(T item) {
    increaseSize();
    for (int i = size; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = item;
    size++;
}

template <typename T>
void Arraylist<T>::add(T item, int index) {
    if (index < 0 || index > size) return; // Check for invalid index
    increaseSize();
    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = item;
    size++;
}

template <typename T>
void Arraylist<T>::removeBack() {
    if (size > 0) {
        size--;
    }
}

template <typename T>
void Arraylist<T>::removeFront() {
    if (size > 0) {
        for (int i = 1; i < size; i++) {
            arr[i - 1] = arr[i];
        }
        size--;
    }
}

template <typename T>
void Arraylist<T>::remove(int index) {
    if (index < 0 || index >= size) return; // Check for invalid index
    if (size > 0) {
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }
}

template <typename T>
int Arraylist<T>::Find(T item) const {
    for (int i = 0; i < size; i++) {
        if (arr[i] == item) {
            return i;
        }
    }
    return -1;
}

template <typename T>
T& Arraylist<T>::operator[](const int index) {
    if (index < 0 || index >= size) {
        std::cout << "Index out of bounds" << std::endl;
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

