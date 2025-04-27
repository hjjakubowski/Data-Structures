#pragma once
#include "queue.hpp"
#include "doublyLinkedList.hpp"
#include <iostream>

template <typename T>
class LinkedQueue : public Queue<T> {
private:
    DLinkedList<typename Queue<T>::Node> list;  

public:
    LinkedQueue(int size_) : Queue<T>(size_) {}
    LinkedQueue() {}

    void insert(const T& e, int p) override;
    int operator[](int index);

    T extractMax() override;
    T findMax() const override;
    void modifyKey(const T& e, int p) override;
    void print() const;
};

template <typename T>
void LinkedQueue<T>::insert(const T& e, int p) {
    typename Queue<T>::Node newNode(e, p);

    if (this->size == 0) {
        list.addFront(newNode);
        this->size++;
        return;
    }

    for (int i = 0; i < this->size; ++i) {
        if (list[i].priority >= p) {
            list.add(newNode, i);  
            this->size++;
            return;
        }
    }

    list.addBack(newNode);
    this->size++;
}

template <typename T>
T LinkedQueue<T>::extractMax() {
    if (this->size == 0) {
        return -1;
    }
    
    T item = list[--(this->size)].item;  
    list.removeBack();  
    return item;
}

template <typename T>
T LinkedQueue<T>::findMax() const {

}

template <typename T>
void LinkedQueue<T>::modifyKey(const T& e, int p) {

}

template <typename T>
int LinkedQueue<T>::operator[](int index) {
    if (index < 0 || index >= this->size) {
        return -1;
    }
    return list[index].priority;
}

template <typename T>
void LinkedQueue<T>::print() const {
    for (int i = 0; i < this->size; ++i) {
        std::cout << "[" << list[i].item << ", priority: " << list[i].priority << "] ";
    }
    std::cout << std::endl;
}
