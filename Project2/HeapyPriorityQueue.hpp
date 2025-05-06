<<<<<<< HEAD
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <stdexcept>
#include <iostream>
#include <unordered_map>
=======
#pragma once

#include <stdexcept>
#include <iostream>
>>>>>>> Oleh
#include "Queue.hpp"

template<typename T>
class HeapyPriorityQueue : public Queue<T> {
private:
    struct Element {
        T value;
        int priority;
<<<<<<< HEAD
        int order;

        bool operator<(const Element& other) const {
            if(priority != other.priority)
                return priority < other.priority;
			return order > other.order;  // FIFO order for same priority
        }
    };

    Element* heap;
    int capacity;
    std::unordered_map<T, int> indexMap;
	int nextOrder = 0;
=======

        bool operator<(const Element& other) const {
            return priority < other.priority;
        }
    };

    Element* heap = nullptr;
    int capacity = 0;
>>>>>>> Oleh

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
<<<<<<< HEAD
    HeapyPriorityQueue();
    ~HeapyPriorityQueue();
=======
    HeapyPriorityQueue() : Queue<T>() {}
    ~HeapyPriorityQueue() { delete[] heap; }
>>>>>>> Oleh

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
<<<<<<< HEAD
HeapyPriorityQueue<T>::HeapyPriorityQueue() : Queue<T>(), heap(nullptr), capacity(0) {}


template<typename T>
HeapyPriorityQueue<T>::~HeapyPriorityQueue() {
    delete[] heap;
}

template<typename T>
void HeapyPriorityQueue<T>::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Element* newHeap = new Element[newCapacity];
    for (int i = 0; i < this->size; ++i) {
        newHeap[i] = heap[i];
    }
=======
void HeapyPriorityQueue<T>::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Element* newHeap = new Element[newCapacity];
    for (int i = 0; i < this->size; ++i)
        newHeap[i] = heap[i];
>>>>>>> Oleh
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

template<typename T>
void HeapyPriorityQueue<T>::heapifyUp(int index) {
    if (index == 0) return;
<<<<<<< HEAD

    int parent = (index - 1) / 2;
    if (heap[parent] < heap[index]) {
        std::swap(heap[parent], heap[index]);
        std::swap(indexMap[heap[parent].value], indexMap[heap[index].value]);
=======
    int parent = (index - 1) / 2;
    if (heap[parent] < heap[index]) {
        std::swap(heap[parent], heap[index]);
>>>>>>> Oleh
        heapifyUp(parent);
    }
}

template<typename T>
void HeapyPriorityQueue<T>::heapifyDown(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

<<<<<<< HEAD
    if (left < this->size && heap[largest] < heap[left]) {
        largest = left;
    }
    if (right < this->size && heap[largest] < heap[right]) {
        largest = right;
    }
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        std::swap(indexMap[heap[index].value], indexMap[heap[largest].value]);
=======
    if (left < this->size && heap[largest] < heap[left]) largest = left;
    if (right < this->size && heap[largest] < heap[right]) largest = right;

    if (largest != index) {
        std::swap(heap[index], heap[largest]);
>>>>>>> Oleh
        heapifyDown(largest);
    }
}

template<typename T>
void HeapyPriorityQueue<T>::insert(const T& e, int p) {
<<<<<<< HEAD
    if (this->size == capacity) {
        resize();
    }
    heap[this->size] = Element{ e, p , nextOrder++};
    indexMap[e] = this->size;
=======
    if (this->size == capacity) resize();
    heap[this->size] = Element{e, p};
>>>>>>> Oleh
    heapifyUp(this->size);
    ++(this->size);
}

template<typename T>
T HeapyPriorityQueue<T>::extractMax() {
<<<<<<< HEAD
    if (empty()) {
        throw std::out_of_range("HeapyPriorityQueue::extractMax() called on empty queue");
    }
    T maxValue = heap[0].value;
    indexMap.erase(maxValue);
    heap[0] = heap[this->size - 1];
    --(this->size);
    if (!empty()) {
        indexMap[heap[0].value] = 0;
        heapifyDown(0);
    }
=======
    if (empty()) throw std::out_of_range("Kolejka jest pusta");
    T maxValue = heap[0].value;
    heap[0] = heap[this->size - 1];
    --(this->size);
    heapifyDown(0);
>>>>>>> Oleh
    return maxValue;
}

template<typename T>
T HeapyPriorityQueue<T>::findMax() const {
<<<<<<< HEAD
    if (empty()) {
        throw std::out_of_range("HeapyPriorityQueue::findMax() called on empty queue");
    }
=======
    if (empty()) throw std::out_of_range("Kolejka jest pusta");
>>>>>>> Oleh
    return heap[0].value;
}

template<typename T>
void HeapyPriorityQueue<T>::modifyKey(const T& e, int p) {
<<<<<<< HEAD
    auto elementPositionInMap = indexMap.find(e);
    if (elementPositionInMap == indexMap.end()) {
=======
<<<<<<< HEAD
    auto it = indexMap.find(e);
    if (it == indexMap.end()) {
>>>>>>> e10cb25641ffd1a59afafcca609a06514182c628
        throw std::invalid_argument("Element not found in HeapyPriorityQueue");
    }
    int heapIndex = elementPositionInMap->second;
    int oldPriority = heap[heapIndex].priority;
    heap[i].priority = p;
    if (p > oldPriority) {
        heapifyUp(heapIndex);
    }
    else if (p < oldPriority) {
        heapifyDown(i);
    }
=======
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
>>>>>>> Oleh
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
<<<<<<< HEAD
    std::cout << "HeapyPriorityQueue (size = " << this->size << ", capacity = " << capacity << "):\n";
    for (int i = 0; i < this->size; ++i) {
        std::cout << "[" << heap[i].value << ", priority: " << heap[i].priority << "]\n";
    }
}

#endif
=======
    std::cout << "Kolejka kopcowa (rozmiar = " << this->size << "):\n";
    for (int i = 0; i < this->size; ++i)
        std::cout << "[" << heap[i].value << ", priorytet: " << heap[i].priority << "]\n";
}
>>>>>>> Oleh
