#include "doublyLinkedList.hpp"

template <typename Elem>
DLinkedList<Elem>::DLinkedList() {
    header = new DNode;
    trailer = new DNode;
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
    
	DNode* newNode = new DNode;
	newNode->elem = e;
    
    if (pos == 0) addFront(e);
	else if (pos == getSize()) addBack(e);
	else {
		DNode* current = header->next;
		for (int i = 0; i < pos - 1; i++) current = current->next;
		
        newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;
	}

}

template <typename Elem>
void DLinkedList<Elem>::add(const Elem& e, int pos) {
    if (pos < 0 || pos > getSize()) throw std::out_of_range("Invalid position!");
    
	DNode* newNode = new DNode;
	newNode->elem = e;
    
    if (pos == 0) addFront(e);
	else if (pos == getSize()) addBack(e);
	else {
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
	if (empty()) throw std::runtime_error("Empty list!");
    if (!empty()) {
        DNode* oldNode = header->next;
        header->next = oldNode->next;
        oldNode->next->prev = header;
        delete oldNode;
    }
}

template <typename Elem>
void DLinkedList<Elem>::removeBack() {
    if (empty()) throw std::runtime_error("Empty list!");
    if (!empty()) {
        DNode* oldNode = trailer->prev;
        trailer->prev = oldNode->prev;
        oldNode->prev->next = trailer;
        delete oldNode;
    }
}

template <typename Elem>
void DLinkedList<Elem>::remove(int pos) {
    if (pos < 0 || pos >= getSize())throw std::out_of_range("Invalid position");
    
    DNode* current = header->next;
    for (int i = 0; i < pos; ++i) current = current->next;
    

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
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