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
        int order;     // Insertion order to preserve FIFO for same priority

        // Custom comparator: higher priority comes first; ties are broken by insertion order (FIFO)
        bool operator<(const Element& other) const {
            if (priority != other.priority)
                return priority < other.priority;
            return order > other.order;  // FIFO order for same priority
        }
    };

    Element* heap;                          // Dynamic array representing the binary max-heap
    int capacity;                           
    std::unordered_map<T, int> indexMap;    // Maps an element to its index in the heap (used for modifyKey)
    int nextOrder = 0;                      // Counter used to preserve insertion order (FIFO for same priority)

    void heapifyUp(int index);              
    void heapifyDown(int index);            
    void resize();                          

public:
    HeapyPriorityQueue();                  
    ~HeapyPriorityQueue();                 

    void insert(const T& e, int p) override;    
    T extractMax() override;                   // Removes and returns the element with the highest priority
    T findMax() const override;                // Returns the element with the highest priority without removing it
    void modifyKey(const T& e, int p) override; // Changes the priority of a given element
    int getSize() const override;              
    bool empty() const override;               

    int getCapacity() const;                   
    void print() const;                        // Prints the contents of the heap (for debugging)
};

template<typename T>
HeapyPriorityQueue<T>::HeapyPriorityQueue() : Queue<T>(), heap(nullptr), capacity(0) {}


template<typename T>
HeapyPriorityQueue<T>::~HeapyPriorityQueue() {
    delete[] heap;
}

// Doubles the capacity of the heap and copies elements to a new array
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

// Moves the element at index up to restore the max-heap property
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

// Moves the element at index down to restore the max-heap property
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

// Inserts a new element with priority p into the heap
template<typename T>
void HeapyPriorityQueue<T>::insert(const T& e, int p) {
    if (this->size == capacity) {
        resize();
    }
    heap[this->size] = Element{ e, p , nextOrder++ }; // Create new element
    indexMap[e] = this->size;                         // Track its index for modifyKey
    heapifyUp(this->size);                            // Restore heap order
    ++(this->size);
}

// Removes and returns the element with the highest priority (root of the heap)
template<typename T>
T HeapyPriorityQueue<T>::extractMax() {
    if (empty()) {
        throw std::out_of_range("HeapyPriorityQueue::extractMax() called on empty queue");
    }
    T maxValue = heap[0].value;
    indexMap.erase(maxValue);
    heap[0] = heap[this->size - 1];         // Move last element to root
    --(this->size);
    if (!empty()) {
        indexMap[heap[0].value] = 0;
        heapifyDown(0);                     // Restore heap order
    }
    return maxValue;
}

// Returns the value with the highest priority without removing it
template<typename T>
T HeapyPriorityQueue<T>::findMax() const {
    if (empty()) {
        throw std::out_of_range("HeapyPriorityQueue::findMax() called on empty queue");
    }
    return heap[0].value;
}

// Modifies the priority of an existing element and reorders the heap
template<typename T>
void HeapyPriorityQueue<T>::modifyKey(const T& e, int p) {
    auto elementPositionInMap = indexMap.find(e);
    if (elementPositionInMap == indexMap.end()) {
        throw std::invalid_argument("Element not found in HeapyPriorityQueue");
    }

    int heapIndex = elementPositionInMap->second;
    int oldPriority = heap[heapIndex].priority;
    heap[heapIndex].priority = p;

    if (p > oldPriority) {
        heapifyUp(heapIndex);
    }
    else if (p < oldPriority) {
        heapifyDown(heapIndex);
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

// Prints the heap contents (value and priority) 
template<typename T>
void HeapyPriorityQueue<T>::print() const {
    std::cout << "HeapyPriorityQueue (size = " << this->size << ", capacity = " << capacity << "):\n";
    for (int i = 0; i < this->size; ++i) {
        std::cout << "[" << heap[i].value << ", priority: " << heap[i].priority << "]\n";
    }
}

#endif
