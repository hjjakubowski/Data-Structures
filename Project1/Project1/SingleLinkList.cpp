#include "SingleLinklist.h"

Singlelist::Singlelist() : size(0), head(nullptr) {}

Singlelist::~Singlelist() {
    while (head) {
        pop_front();
    }
}

int Singlelist::getSize() const {
    return size;
}

void Singlelist::push_back(int item) {
    Node* newNode = new Node(item);
    if (!head) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;

    }
    size++;
}

void Singlelist::pop_back() {
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current = nullptr;
    size--;
}

void Singlelist::push_front(int item) {
    head = new Node(item, head);
    size++;
}

void Singlelist::pop_front() {
    Node* current = head;
    head = current->next;
    delete current;
    size--;
}

void Singlelist::push_index(int item, int index) {
    if (index == 0) {
        push_front(item);
    }
    else{
        Node* previous = head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->next;
        }
        Node* newNode = new Node(item, previous->next);
        previous->next = newNode;
    }
    
    size++;
}

void Singlelist::pop_index(int index) {
    if (index < size) {
        Node* previous = head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->next;
        }
        Node* temp = previous->next;
        previous->next = temp->next;
        delete temp;
    }
    else {
        std::cout << "Enter proper index" << std::endl;
    }

    size--;
}

int Singlelist::find(int item) {
    Node* current = head;
    int index = 0;
    while (current) {
        if (current->item == item) {
            return index;
            break;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int& Singlelist::operator[](const int index) {
    int counter = 0;
    Node* current = head;
    while (current) {
        if (counter == index) {
            return current->item;
        }
        current = current->next;
        counter++;
    }
}