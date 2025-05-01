#pragma once

#include <iostream>
#include "queue.hpp"

template <typename T>
class LinkedQueue : public Queue<T> {
public:
    LinkedQueue();
    ~LinkedQueue();

    bool empty() const override;
    int getSize() const override;

    void insert(const T& e, int p) override;
    T extractMax() override;
    T findMax() const override;
    void modifyKey(const T& e, int p) override;
    void print() const;

private:
    struct DNode {
        T elem;
        int priority;
        DNode* next;
        DNode* prev;
        DNode(const T& e = T(), int p = 0) : elem(e), priority(p), next(nullptr), prev(nullptr) {}
    };

    DNode* header;
    DNode* trailer;

    void addBack(const T& e, int priority);
    void removeNode(DNode* node);
};

template <typename T>
LinkedQueue<T>::LinkedQueue() {
    header = new DNode();
    trailer = new DNode();
    header->next = trailer;
    trailer->prev = header;
    header->prev = nullptr;
    trailer->next = nullptr;
    this->size = 0;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    DNode* current = header;
    while (current != nullptr) {
        DNode* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
bool LinkedQueue<T>::empty() const {
    return header->next == trailer;
}

template <typename T>
int LinkedQueue<T>::getSize() const {
    return this->size;
}

template <typename T>
void LinkedQueue<T>::addBack(const T& e, int priority) {
    DNode* newNode = new DNode(e, priority);
    DNode* prevNode = trailer->prev;

    prevNode->next = newNode;
    newNode->prev = prevNode;
    newNode->next = trailer;
    trailer->prev = newNode;

    this->size++;
}

template <typename T>
void LinkedQueue<T>::removeNode(DNode* node) {
    if (node == header || node == trailer) return;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    this->size--;
}

template <typename T>
void LinkedQueue<T>::insert(const T& e, int p) {
    addBack(e, p);
}

template <typename T>
T LinkedQueue<T>::extractMax() {
    if (empty()) {
        std::cout << "Queue is empty\n";
        return T();
    }

    DNode* maxNode = header->next;
    DNode* current = header->next;

    while (current != trailer) {
        if (current->priority > maxNode->priority) {
            maxNode = current;
        }
        current = current->next;
    }

    T result = maxNode->elem;
    removeNode(maxNode);
    return result;
}

template <typename T>
T LinkedQueue<T>::findMax() const {
    if (empty()) {
        std::cout << "Queue is empty\n";
        return T();
    }

    DNode* maxNode = header->next;
    DNode* current = header->next;

    while (current != trailer) {
        if (current->priority > maxNode->priority) {
            maxNode = current;
        }
        current = current->next;
    }

    return maxNode->elem;
}

template <typename T>
void LinkedQueue<T>::modifyKey(const T& e, int p) {
    DNode* current = header->next;
    while (current != trailer) {
        if (current->elem == e) {
            current->priority = p;
            return;
        }
        current = current->next;
    }
    std::cout << "Element not found\n";
}

template <typename T>
void LinkedQueue<T>::print() const {
    DNode* current = header->next;
    while (current != trailer) {
        std::cout << "(" << current->elem << ", " << current->priority << ") ";
        current = current->next;
    }
    std::cout << "\n";
}
