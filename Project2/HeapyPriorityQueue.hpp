#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.hpp"

template<typename T>
class HeapyPriorityQueue : public Queue<T> {
private:
    struct Element {
        T value;
        int priority;

        bool operator<(const Element& other) const {
            return priority < other.priority;
        }
    };

    Element* heap = nullptr;
    int capacity = 0;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    HeapyPriorityQueue() : Queue<T>() {}
    ~HeapyPriorityQueue() { delete[] heap; }

    void insert(const T& e, int p) override;
    T extractMax() override;
    T findMax() const override;
    void modifyKey(const T& e, int p) override;
    int getSize() const override;
    bool empty() const override;

    int getCapacity() const;
    void print() const;
};

template<typename T>
void HeapyPriorityQueue<T>::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Element* newHeap = new Element[newCapacity];
    for (int i = 0; i < this->size; ++i)
        newHeap[i] = heap[i];
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

template<typename T>
void HeapyPriorityQueue<T>::heapifyUp(int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (heap[parent] < heap[index]) {
        std::swap(heap[parent], heap[index]);
        heapifyUp(parent);
    }
}

template<typename T>
void HeapyPriorityQueue<T>::heapifyDown(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < this->size && heap[largest] < heap[left]) largest = left;
    if (right < this->size && heap[largest] < heap[right]) largest = right;

    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

template<typename T>
void HeapyPriorityQueue<T>::insert(const T& e, int p) {
    if (this->size == capacity) resize();
    heap[this->size] = Element{e, p};
    heapifyUp(this->size);
    ++(this->size);
}

template<typename T>
T HeapyPriorityQueue<T>::extractMax() {
    if (empty()) throw std::out_of_range("Kolejka jest pusta");
    T maxValue = heap[0].value;
    heap[0] = heap[this->size - 1];
    --(this->size);
    heapifyDown(0);
    return maxValue;
}

template<typename T>
T HeapyPriorityQueue<T>::findMax() const {
    if (empty()) throw std::out_of_range("Kolejka jest pusta");
    return heap[0].value;
}

template<typename T>
void HeapyPriorityQueue<T>::modifyKey(const T& e, int p) {
    for (int i = 0; i < this->size; ++i) {
        if (heap[i].value == e) {
            int oldPriority = heap[i].priority;
            heap[i].priority = p;
            if (p > oldPriority) heapifyUp(i);
            else heapifyDown(i);
            return;
        }
    }
    throw std::invalid_argument("Nie znaleziono elementu");
}

template<typename T>
int HeapyPriorityQueue<T>::getSize() const {
    return this->size;
}

template<typename T>
bool HeapyPriorityQueue<T>::empty() const {
    return this->size == 0;
}

template<typename T>
int HeapyPriorityQueue<T>::getCapacity() const {
    return capacity;
}

template<typename T>
void HeapyPriorityQueue<T>::print() const {
    std::cout << "Kolejka kopcowa (rozmiar = " << this->size << "):\n";
    for (int i = 0; i < this->size; ++i)
        std::cout << "[" << heap[i].value << ", priorytet: " << heap[i].priority << "]\n";
}
