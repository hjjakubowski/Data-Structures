#pragma once
#include <iostream>

// Struktura reprezentująca pojedynczy węzeł listy
template <typename T>
struct Node {
    T item;        // Element przechowywany w węźle
    Node* next;    // Wskaźnik na następny węzeł

    Node(T item, Node* next = nullptr) : item(item), next(next) {} // Konstruktor węzła
};

template <typename T>
class Singlelist {
private:
    int size;       // Liczba elementów w liście
    Node<T>* head;  // Wskaźnik na pierwszy element listy

public:
    Singlelist();   // Konstruktor listy
    ~Singlelist();  // Destruktor listy

    int getSize() const;  // Zwraca aktualny rozmiar listy

    void addBack(T item);  // Dodaje element na koniec listy
    void addFront(T item); // Dodaje element na początek listy
    void add(T item, int index);  // Dodaje element w określonym indeksie

    void removeBack();  // Usuwa ostatni element z listy
    void removeFront(); // Usuwa pierwszy element z listy
    void remove(int index);  // Usuwa element na podanym indeksie

    int Find(T item) const; // Zwraca indeks pierwszego wystąpienia elementu, lub -1 jeśli nie znaleziono
    T& operator[](const int index);  // Operator [] do dostępu do elementów listy
};

// Konstruktor listy - inicjalizuje pustą listę
template <typename T>
Singlelist<T>::Singlelist() : size(0), head(nullptr) {}

// Destruktor listy - zwalnia pamięć zajmowaną przez listę
template <typename T>
Singlelist<T>::~Singlelist() {
    while (head) {
        removeFront();  // Usuwamy wszystkie elementy z listy
    }
}

// Zwraca rozmiar listy
template <typename T>
int Singlelist<T>::getSize() const {
    return size;
}

// Dodaje element na koniec listy
template <typename T>
void Singlelist<T>::addBack(T item) {
    Node<T>* newNode = new Node<T>(item); // Tworzymy nowy węzeł
    if (!head) { // Jeśli lista jest pusta, ustawiamy nowy węzeł jako pierwszy
        head = newNode;
    }
    else {
        Node<T>* current = head;
        while (current->next) { // Przechodzimy do ostatniego elementu listy
            current = current->next;
        }
        current->next = newNode;  // Dodajemy nowy węzeł na końcu listy
    }
    size++; 
}

// Usuwa ostatni element listy
template <typename T>
void Singlelist<T>::removeBack() {
    if (!head) return; // Jeśli lista jest pusta, nic nie robimy

    Node<T>* current = head;
    if (!current->next) {  // Jeśli lista ma tylko jeden element
        delete head;
        head = nullptr;  // Usuwamy jedyny element i ustawiamy wskaźnik na null
    }
    else {
        while (current->next && current->next->next) { // Przechodzimy do przedostatniego elementu
            current = current->next;
        }
        delete current->next; // Usuwamy ostatni element
        current->next = nullptr;  // Ustawiamy wskaźnik na null, by zakończyć listę
    }
    size--;  
}

// Dodaje element na początek listy
template <typename T>
void Singlelist<T>::addFront(T item) {
    head = new Node<T>(item, head); // Tworzymy nowy węzeł, który wskazuje na obecny pierwszy element
    size++; 
}

// Usuwa pierwszy element listy
template <typename T>
void Singlelist<T>::removeFront() {
    if (head) {
        Node<T>* temp = head;
        head = head->next;  // Ustawiamy wskaźnik na drugi element
        delete temp;  // Usuwamy pierwszy element
        size--;  
    }
}

// Dodaje element w określonym indeksie
template <typename T>
void Singlelist<T>::add(T item, int index) {
    if (index < 0 || index > size) { // Sprawdzamy, czy indeks jest w odpowiednim zakresie
        std::cout << "Index out of range." << std::endl;
        return;
    }

    if (index == 0) {  // Jeśli indeks to 0, dodajemy element na początek
        addFront(item);
    }
    else {
        Node<T>* previous = head;
        for (int i = 0; i < index - 1; i++) { // Przechodzimy do elementu przed wskazywanym indeksem
            previous = previous->next;
        }
        Node<T>* newNode = new Node<T>(item, previous->next); // Tworzymy nowy węzeł
        previous->next = newNode;  // Łączymy go z poprzednim elementem
        size++; 
    }
}

// Usuwa element o podanym indeksie
template <typename T>
void Singlelist<T>::remove(int index) {
    if (index < 0 || index >= size) { // Sprawdzamy, czy indeks jest w odpowiednim zakresie
        std::cout << "Enter proper index" << std::endl;
        return;
    }

    if (index == 0) {  // Jeśli indeks to 0, usuwamy pierwszy element
        removeFront();
    }
    else {
        Node<T>* previous = head;
        for (int i = 0; i < index - 1; i++) { // Przechodzimy do elementu przed wskazywanym indeksem
            previous = previous->next;
        }
        Node<T>* temp = previous->next;  // Wskaźnik na element do usunięcia
        previous->next = temp->next;  // Łączymy poprzedni element z następnym
        delete temp;  // Usuwamy element
        size--;  
    }
}

// Zwraca indeks pierwszego wystąpienia danego elementu w liście, lub -1 jeśli nie znaleziono
template <typename T>
int Singlelist<T>::Find(T item) const {
    Node<T>* current = head;
    int index = 0;
    while (current) {
        if (current->item == item) {  // Jeśli element jest równy szukanemu, zwracamy indeks
            return index;
        }
        current = current->next;  // Przechodzimy do następnego elementu
        index++;
    }
    return -1;  // Zwracamy -1, jeśli element nie został znaleziony
}

// Operator [] do dostępu do elementów listy
template <typename T>
T& Singlelist<T>::operator[](const int index) {
    if (index < 0 || index >= size) { // Sprawdzamy, czy indeks jest w odpowiednim zakresie
        std::cout << "Index out of bounds" << std::endl;
        throw std::out_of_range("Index out of bounds"); // Rzucamy wyjątek, jeśli indeks jest niepoprawny
    }

    Node<T>* current = head;
    for (int i = 0; i < index; i++) {  // Przechodzimy do wskazywanego elementu
        current = current->next;
    }
    return current->item;  // Zwracamy element w wskazanym indeksie
}
