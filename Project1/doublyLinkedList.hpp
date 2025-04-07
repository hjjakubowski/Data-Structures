#pragma once
#include <iostream>
#include <stdexcept>

template <typename Elem>
class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();
    
    bool empty() const;
    int getSize();
    void addFront(const Elem& e);
    void addBack(const Elem& e);
    void add(const Elem& e, int pos);
    void removeFront();
    void removeBack();
	void remove(int pos);
    int Find(const Elem& e);

private:
    struct DNode {
        Elem elem;
        DNode* next;
        DNode* prev;
    };

    DNode* header;
    DNode* trailer;
    int size;
};

template <typename Elem>
DLinkedList<Elem>::DLinkedList(): size(0) {
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;
	header->prev = nullptr;
    trailer->prev = header;
	trailer->next = nullptr;
}

template <typename Elem>
DLinkedList<Elem>::~DLinkedList() {
    while(!empty()) removeFront();
    delete header;
    delete trailer;
}

template <typename Elem>
bool DLinkedList<Elem>::empty() const {
    return header->next == trailer;
}

template <typename Elem>
int DLinkedList<Elem>::getSize() {
    DNode* temp = header->next;
    while (temp != trailer) {
        size++;
        temp = temp->next;
    }
    return size;
}

template <typename Elem>
void DLinkedList<Elem>::addFront(const Elem& e) {
    DNode* newNode = new DNode;
    newNode->elem = e;
    newNode->next = header->next;
    newNode->prev = header;
    header->next->prev = newNode;
    header->next = newNode;
}

template <typename Elem>
void DLinkedList<Elem>::addBack(const Elem& e) {
    DNode* newNode = new DNode;
    newNode->elem = e;
    newNode->prev = trailer->prev;
    newNode->next = trailer;
    trailer->prev->next = newNode;
    trailer->prev = newNode;
}

template <typename Elem>
void DLinkedList<Elem>::add(const Elem& e, int pos) {
    if (pos < 0 || pos > getSize()) throw std::out_of_range("Invalid position!");
    if (pos == 0) addFront(e);
    else if (pos == getSize()) addBack(e);
    else {
        DNode* newNode = new DNode;
        newNode->elem = e;
        DNode* current = header->next;
        for (int i = 0; i < pos - 1; i++) current = current->next;

        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
}

template <typename Elem>
void DLinkedList<Elem>::removeFront() {
    if(!empty()){
        DNode* oldNode = header->next;
        header->next = oldNode->next;
        oldNode->next->prev = header;
        delete oldNode;
	}
	else throw std::runtime_error("Empty list!");
}

template <typename Elem>
void DLinkedList<Elem>::removeBack() {
    if(!empty()){
        DNode* oldNode = trailer->prev;
        trailer->prev = oldNode->prev;
        oldNode->prev->next = trailer;
        delete oldNode;
	}
	else throw std::runtime_error("Empty list!");
}

template <typename Elem>
void DLinkedList<Elem>::remove(int pos) {
    if (pos < 0 || pos >= getSize())throw std::out_of_range("Invalid position");
    if (pos == 0) removeFront();  
	else if (pos == getSize()-1) removeBack();
	else {
        DNode* current = header->next;
        for (int i = 0; i < pos-1; ++i) current = current->next;


        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
	}
    
}

template <typename Elem>
int DLinkedList<Elem>::Find(const Elem& e) {
    DNode* current = header->next;
    int index = 0;
    while (current != trailer) {
        if (current->elem == e) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

