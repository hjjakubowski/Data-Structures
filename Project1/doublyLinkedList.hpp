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
    newNode->next = header->next;   // Set newNode's next to the header next
    newNode->prev = header;         // Set newNode's prev to header
    header->next->prev = newNode;   // Set the previous pointer of the node that was after header to point to newNode.
    header->next = newNode;         // Set header next to newNode
}

template <typename Elem>
void DLinkedList<Elem>::addBack(const Elem& e) {
    DNode* newNode = new DNode;
    newNode->elem = e;
    newNode->prev = trailer->prev;  // Set newNode's prev to where the trailer prev pointed before
    newNode->next = trailer;        // Set newNode's next to trailer
    trailer->prev->next = newNode;  // Set the next pointer of the node that was before trailer to point to newNode.
    trailer->prev = newNode;        // Set trailer prev to newNode
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

        newNode->next = current;        // Set newNode's next to current (the node at pos)
        newNode->prev = current->prev;  // Set newNode's prev to the node before current
        current->prev->next = newNode;  // Set the next pointer of the node before current to newNode
        current->prev = newNode;        // Set current's prev to newNode
    }
}

template <typename Elem>
void DLinkedList<Elem>::removeFront() {
    if(!empty()){
        DNode* oldNode = header->next;  // Get the node after header
        header->next = oldNode->next;   // Set header's next to the node after oldNode
        oldNode->next->prev = header;   // Set the previous pointer of the node after oldNode to header
        delete oldNode;
	}
	else throw std::runtime_error("Empty list!");
}

template <typename Elem>
void DLinkedList<Elem>::removeBack() {
    if(!empty()){
        DNode* oldNode = trailer->prev; // Get the node before trailer
        trailer->prev = oldNode->prev;  // Set trailer's prev to the node before oldNode
        oldNode->prev->next = trailer;  // Set the next pointer of the node before oldNode to trailer
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


        current->prev->next = current->next;    // Set the next pointer of the node before current to the node after current
        current->next->prev = current->prev;    // Set the previous pointer of the node after current to the node before current
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

