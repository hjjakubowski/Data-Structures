#include "doubleLinkedList.hpp"

template <typename Elem>
DLinkedList<Elem>::DLinkedList() {
    header = new DNode<Elem>;
    trailer = new DNode<Elem>;
    header->next = trailer;
    trailer->prev = header;
}

template <typename Elem>
DLinkedList<Elem>::~DLinkedList() {
    while (!empty()) removeFront();
    delete header;
    delete trailer;
}

template <typename Elem>
bool DLinkedList<Elem>::empty() const {
    return (header->next == trailer);
}

template <typename Elem>
const Elem& DLinkedList<Elem>::front() const {
    return header->next->elem;
}

template <typename Elem>
const Elem& DLinkedList<Elem>::back() const {
    return trailer->prev->elem;
}

template <typename Elem>
void DLinkedList<Elem>::add(DNode<Elem>* v, const Elem& e) {
    DNode<Elem>* u = new DNode<Elem>;
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
}

template <typename Elem>
void DLinkedList<Elem>::addFront(const Elem& e) {
    add(header->next, e);
}

template <typename Elem>
void DLinkedList<Elem>::addBack(const Elem& e) {
    add(trailer, e);
}

template <typename Elem>
void DLinkedList<Elem>::remove(DNode<Elem>* v) {
    DNode<Elem>* u = v->prev;
    DNode<Elem>* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}

template <typename Elem>
void DLinkedList<Elem>::removeFront() {
    remove(header->next);
}

template <typename Elem>
void DLinkedList<Elem>::removeBack() {
    remove(trailer->prev);
}

template <typename Elem>
int DLinkedList<Elem>::getSize() {
    int size = 0;
    DNode<Elem>* temp = header->next;
    while (temp != trailer) {
        size++;
        temp = temp->next;
    }
    return size;
}

template <typename Elem>
int DLinkedList<Elem>::Find(const Elem& e) {
    int index = 0;
    DNode<Elem>* temp = header->next;
    while (temp != trailer) {
        if (temp->elem == e) {
            return index;
        }
        index++;
        temp = temp->next;
    }
    return -1;
}