#pragma once
#include <iostream>

template <typename T>
struct Node {
    T item;
    Node* next;

    Node(T item, Node* next = nullptr) : item(item), next(next) {}
};

template <typename T>
class Singlelist {
private:
    int size;
    Node<T>* head;

public:
    Singlelist();
    ~Singlelist();

    int getSize() const;

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
Singlelist<T>::Singlelist() : size(0), head(nullptr) {}

template <typename T>
Singlelist<T>::~Singlelist() {
    while (head) {
        removeFront();
    }
}

template <typename T>
int Singlelist<T>::getSize() const {
    return size;
}

template <typename T>
void Singlelist<T>::addBack(T item) {
    Node<T>* newNode = new Node<T>(item);
    if (!head) {
        head = newNode;
    }
    else {
        Node<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

template <typename T>
void Singlelist<T>::removeBack() {
    if (!head) return;

    Node<T>* current = head;
    if (!current->next) {
        delete head;
        head = nullptr;
    }
    else {
        while (current->next && current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    size--;
}

template <typename T>
void Singlelist<T>::addFront(T item) {
    head = new Node<T>(item, head);
    size++;
}

template <typename T>
void Singlelist<T>::removeFront() {
    if (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
}

template <typename T>
void Singlelist<T>::add(T item, int index) {
    if (index < 0 || index > size) {
        std::cout << "Index out of range." << std::endl;
        return;
    }

    if (index == 0) {
        addFront(item);
    }
    else {
        Node<T>* previous = head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->next;
        }
        Node<T>* newNode = new Node<T>(item, previous->next);
        previous->next = newNode;
        size++;
    }
}

template <typename T>
void Singlelist<T>::remove(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Enter proper index" << std::endl;
        return;
    }

    if (index == 0) {
        removeFront();
    }
    else {
        Node<T>* previous = head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->next;
        }
        Node<T>* temp = previous->next;
        previous->next = temp->next;
        delete temp;
        size--;
    }
}

template <typename T>
int Singlelist<T>::Find(T item) const {
    Node<T>* current = head;
    int index = 0;
    while (current) {
        if (current->item == item) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

template <typename T>
T& Singlelist<T>::operator[](const int index) {
    if (index < 0 || index >= size) {
        std::cout << "Index out of bounds" << std::endl;
        throw std::out_of_range("Index out of bounds");
    }

    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->item;
}
