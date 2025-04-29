#pragma once
#include "queue.hpp"
#include "doublyLinkedList.hpp"
#include <iostream>

template <typename T>
class LinkedQueue : public Queue<T> {
private:
    struct Node { 
        T item;
        int priority;

        Node() : item(T()), priority(0) {}
        Node(T e, int p) : item(e), priority(p) {}
    };


    DLinkedList<Node> list;

public:
    LinkedQueue(int size_) : Queue<T>(size_) {}
    LinkedQueue() {}
    LinkedQueue(const LinkedQueue<T>& other);

    void insert(const T& e, int p) override;
    int operator[](int index);
    T extractMax() override;
    T findMax() const override;
    void modifyKey(const T& e, int p) override;
    void print() const;
    bool empty() const override { return this->size == 0; }
};

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other) : Queue<T>(other.size) {
    for (int i = 0; i < other.size; ++i) {
        this->insert(other.list[i].item, other.list[i].priority);
    }
}


template <typename T>
void LinkedQueue<T>::insert(const T& e, int p) {
    Node newNode(e, p);

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
    if (this->size == 0) return T();
    T item = list[--(this->size)].item;
    list.removeBack();
    return item;
}

template <typename T>
T LinkedQueue<T>::findMax() const {
    if (this->size == 0) return T();
    return list[this->size - 1].item;
}

template <typename T>
void LinkedQueue<T>::modifyKey(const T& e, int p) {
    if (list[this->size - 1].item == e) {
        list[this->size - 1].priority = p;
        return;
    }
    for (int i = this->size - 1; i >= 0; i--) {
        if (e == list[i].item) {
            T temp = list[i].item;
            list.remove(i + 1);
            insert(temp, p);
            this->size--;
            return;
        }
    }
}

template <typename T>
int LinkedQueue<T>::operator[](int index) {
    if (index < 0 || index >= this->size) return -1;
    return list[index].priority;
}

template <typename T>
void LinkedQueue<T>::print() const {
    for (int i = 0; i < this->size; ++i) {
        std::cout << "[" << list[i].item << ", priorytet: " << list[i].priority << "] ";
    }
    std::cout << std::endl;
}