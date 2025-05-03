#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include "Queue.hpp"

template<typename T>
class HeapyPriorityQueue : public Queue<T> {
private:
    struct Element {
        T value;
        int priority;
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

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    HeapyPriorityQueue();
    ~HeapyPriorityQueue();

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
        std::swap(indexMap[heap[parent].value], indexMap[heap[index].value]);
        heapifyUp(parent);
    }
}

template<typename T>
void HeapyPriorityQueue<T>::heapifyDown(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < this->size && heap[largest] < heap[left]) {
        largest = left;
    }
    if (right < this->size && heap[largest] < heap[right]) {
        largest = right;
    }
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        std::swap(indexMap[heap[index].value], indexMap[heap[largest].value]);
        heapifyDown(largest);
    }
}

template<typename T>
void HeapyPriorityQueue<T>::insert(const T& e, int p) {
    if (this->size == capacity) {
        resize();
    }
    heap[this->size] = Element{ e, p , nextOrder++};
    indexMap[e] = this->size;
    heapifyUp(this->size);
    ++(this->size);
}

template<typename T>
T HeapyPriorityQueue<T>::extractMax() {
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
    return maxValue;
}

template<typename T>
T HeapyPriorityQueue<T>::findMax() const {
    if (empty()) {
        throw std::out_of_range("HeapyPriorityQueue::findMax() called on empty queue");
    }
    return heap[0].value;
}

template<typename T>
void HeapyPriorityQueue<T>::modifyKey(const T& e, int p) {
    auto it = indexMap.find(e);
    if (it == indexMap.end()) {
        throw std::invalid_argument("Element not found in HeapyPriorityQueue");
    }
    int i = it->second;
    int oldPriority = heap[i].priority;
    heap[i].priority = p;
    if (p > oldPriority) {
        heapifyUp(i);
    }
    else if (p < oldPriority) {
        heapifyDown(i);
    }
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
    std::cout << "HeapyPriorityQueue (size = " << this->size << ", capacity = " << capacity << "):\n";
    for (int i = 0; i < this->size; ++i) {
        std::cout << "[" << heap[i].value << ", priority: " << heap[i].priority << "]\n";
    }
}

#endif
