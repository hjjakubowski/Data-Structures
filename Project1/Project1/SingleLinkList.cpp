//#include "SingleLinklist.h"
//
//template <typename T>
//Singlelist<T>::Singlelist() : size(0), head(nullptr) {}
//
//template <typename T>
//Singlelist<T>::~Singlelist() {
//    while (head) {
//        pop_front();
//    }
//}
//
//template <typename T>
//int Singlelist<T>::getSize() const {
//    return size;
//}
//
//template <typename T>
//void Singlelist<T>::push_back(T item) {
//    Node<T>* newNode = new Node<T>(item);
//    if (!head) {
//        head = newNode;
//    }
//    else {
//        Node<T>* current = head;
//        while (current->next) {
//            current = current->next;
//        }
//        current->next = newNode;
//    }
//    size++;
//}
//
//template <typename T>
//void Singlelist<T>::pop_back() {
//    if (!head) return;
//
//    Node<T>* current = head;
//    if (!current->next) {
//        delete head;
//        head = nullptr;
//    }
//    else {
//        while (current->next && current->next->next) {
//            current = current->next;
//        }
//        delete current->next;
//        current->next = nullptr;
//    }
//    size--;
//}
//
//template <typename T>
//void Singlelist<T>::push_front(T item) {
//    head = new Node<T>(item, head);
//    size++;
//}
//
//template <typename T>
//void Singlelist<T>::pop_front() {
//    if (head) {
//        Node<T>* temp = head;
//        head = head->next;
//        delete temp;
//        size--;
//    }
//}
//
//template <typename T>
//void Singlelist<T>::push_index(T item, int index) {
//    if (index == 0) {
//        push_front(item);
//    }
//    else if (index > 0 && index < size) {
//        Node<T>* previous = head;
//        for (int i = 0; i < index - 1; i++) {
//            previous = previous->next;
//        }
//        Node<T>* newNode = new Node<T>(item, previous->next);
//        previous->next = newNode;
//        size++;
//    }
//    else {
//        std::cout << "Index out of range." << std::endl;
//    }
//}
//
//template <typename T>
//void Singlelist<T>::pop_index(int index) {
//    if (index < 0 || index >= size) {
//        std::cout << "Enter proper index" << std::endl;
//        return;
//    }
//
//    if (index == 0) {
//        pop_front();
//    }
//    else {
//        Node<T>* previous = head;
//        for (int i = 0; i < index - 1; i++) {
//            previous = previous->next;
//        }
//        Node<T>* temp = previous->next;
//        previous->next = temp->next;
//        delete temp;
//        size--;
//    }
//}
//
//template <typename T>
//int Singlelist<T>::find(T item) const {
//    Node<T>* current = head;
//    int index = 0;
//    while (current) {
//        if (current->item == item) {
//            return index;
//        }
//        current = current->next;
//        index++;
//    }
//    return -1;
//}
//
//template <typename T>
//T& Singlelist<T>::operator[](const int index) {
//    if (index < 0 || index >= size) {
//        std::cout << "Index out of bounds" << std::endl;
//        throw std::out_of_range("Index out of bounds");
//    }
//
//    Node<T>* current = head;
//    for (int i = 0; i < index; i++) {
//        current = current->next;
//    }
//    return current->item;
//}