#pragma once

#include <iostream>
#include "queue.hpp"

// Klasa kolejki priorytetowej oparta na dwukierunkowej liście powiązanej
template <typename T>
class LinkedQueue : public Queue<T> {
public:
    LinkedQueue();                      // Konstruktor
    ~LinkedQueue();                     // Destruktor

    bool empty() const override;       // Czy kolejka jest pusta
    int getSize() const override;      // Zwraca rozmiar kolejki

    void insert(const T& e, int p) override;    // Wstawia element z priorytetem
    T extractMax() override;                   // Usuwa i zwraca element o najwyższym priorytecie
    T findMax() const override;                // Zwraca element o najwyższym priorytecie (bez usuwania)
    void modifyKey(const T& e, int p) override; // Modyfikuje priorytet danego elementu
    void print() const;                        // Wypisuje zawartość kolejki

private:
    // Struktura węzła listy
    struct DNode {
        T elem;
        int priority;
        DNode* next;
        DNode* prev;
        DNode(const T& e = T(), int p = 0) : elem(e), priority(p), next(nullptr), prev(nullptr) {}
    };

    DNode* header;   // Wskaźnik na węzeł początkowy (strażnik)
    DNode* trailer;  // Wskaźnik na węzeł końcowy (strażnik)

    void addBack(const T& e, int priority); // Dodaje element na koniec listy
    void removeNode(DNode* node);          // Usuwa dany węzeł z listy
};

template <typename T>
LinkedQueue<T>::LinkedQueue() {
    header = new DNode();   // Tworzy węzeł początkowy
    trailer = new DNode();  // Tworzy węzeł końcowy
    header->next = trailer;
    trailer->prev = header;
    header->prev = nullptr;
    trailer->next = nullptr;
    this->size = 0;         // Początkowy rozmiar to 0
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    DNode* current = header;
    // Usuwanie wszystkich węzłów listy
    while (current != nullptr) {
        DNode* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
bool LinkedQueue<T>::empty() const {
    return header->next == trailer; // Kolejka pusta jeśli między strażnikami nic nie ma
}

template <typename T>
int LinkedQueue<T>::getSize() const {
    return this->size;
}

template <typename T>
void LinkedQueue<T>::addBack(const T& e, int priority) {
    DNode* newNode = new DNode(e, priority);   // Tworzy nowy węzeł
    DNode* prevNode = trailer->prev;

    // Wstawia nowy węzeł przed trailer
    prevNode->next = newNode;
    newNode->prev = prevNode;
    newNode->next = trailer;
    trailer->prev = newNode;

    this->size++;
}

template <typename T>
void LinkedQueue<T>::removeNode(DNode* node) {
    if (node == header || node == trailer) return; // Nie usuwa strażników
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    this->size--;
}

template <typename T>
void LinkedQueue<T>::insert(const T& e, int p) {
    addBack(e, p); // Dodaje element na koniec listy z priorytetem
}

template <typename T>
T LinkedQueue<T>::extractMax() {
    if (empty()) {
        std::cout << "Queue is empty\n";
        return T(); // Zwraca domyślną wartość typu T
    }

    DNode* maxNode = header->next;
    DNode* current = header->next;

    // Szuka elementu o najwyższym priorytecie
    while (current != trailer) {
        if (current->priority > maxNode->priority) {
            maxNode = current;
        }
        current = current->next;
    }

    T result = maxNode->elem;
    removeNode(maxNode); // Usuwa znaleziony element
    return result;
}

template <typename T>
T LinkedQueue<T>::findMax() const {
    if (empty()) {
        std::cout << "Queue is empty\n";
        return T(); // Zwraca domyślną wartość typu T
    }

    DNode* maxNode = header->next;
    DNode* current = header->next;

    // Szuka elementu o najwyższym priorytecie (bez usuwania)
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
    // Szuka elementu do zmiany
    while (current != trailer) {
        if (current->elem == e) {
            current->priority = p; // Ustawia nowy priorytet
            return;
        }
        current = current->next;
    }
    std::cout << "Element not found\n";
}

template <typename T>
void LinkedQueue<T>::print() const {
    DNode* current = header->next;
    // Wypisuje wszystkie elementy z ich priorytetami
    while (current != trailer) {
        std::cout << "(" << current->elem << ", " << current->priority << ") ";
        current = current->next;
    }
    std::cout << "\n";
}
