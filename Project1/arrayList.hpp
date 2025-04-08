#pragma once
#include <iostream>

template <typename T>
class Arraylist {
private:
    T* arr;           // Wskaźnik na dynamicznie alokowaną tablicę
    int size;         
    int capacity;     

    void increaseSize(); // Funkcja zwiększająca rozmiar tablicy

public:
    Arraylist(int capacity = 2);  // początkowy rozmiar tablicy - 2
    ~Arraylist();                 

    int getSize() const;         
    int getCapacity() const;    

    void addBack(T item);       
    void addFront(T item);       
    void add(T item, int index); 
    void removeBack();          
    void removeFront();         
    void remove(int index);     

    int Find(T item) const;     

    T& operator[](const int index); 
};

// Implementacja konstruktora
template <typename T>
Arraylist<T>::Arraylist(int capacity) : size(0), capacity(capacity) {
    arr = new T[capacity]; // Alokacja pamięci na tablicę o początkowej pojemności
}

// Destruktor - zwalnia pamięć zajmowaną przez tablicę
template <typename T>
Arraylist<T>::~Arraylist() {
    delete[] arr; // Zwalnia pamięć dynamiczną
}

// Zwiększa pojemność tablicy dwukrotnie, jeśli brakuje miejsca
template <typename T>
void Arraylist<T>::increaseSize() {
    if (size == capacity) { // Jeśli tablica jest pełna
        capacity *= 2; // Podwajamy pojemność
        T* temp = new T[capacity]; // Tworzymy nową tablicę o większej pojemności

        for (int i = 0; i < size; i++) {
            temp[i] = arr[i]; // Kopiujemy elementy do nowej tablicy
        }

        delete[] arr; // Zwalniamy starą tablicę
        arr = temp;    // Aktualizujemy wskaźnik do nowej tablicy
    }
}

// Zwraca aktualny rozmiar tablicy
template <typename T>
int Arraylist<T>::getSize() const {
    return size;
}

// Zwraca aktualną pojemność tablicy
template <typename T>
int Arraylist<T>::getCapacity() const {
    return capacity;
}

// Dodaje element na koniec tablicy
template <typename T>
void Arraylist<T>::addBack(T item) {
    increaseSize(); // Sprawdzamy, czy trzeba zwiększyć pojemność
    arr[size] = item; // Dodajemy element na koniec
    size++; 
}

// Dodaje element na początek tablicy
template <typename T>
void Arraylist<T>::addFront(T item) {
    increaseSize(); // Sprawdzamy, czy trzeba zwiększyć pojemność
    for (int i = size; i > 0; i--) {
        arr[i] = arr[i - 1]; // Przesuwamy elementy o jedno miejsce w prawo
    }
    arr[0] = item; // Wstawiamy element na początek
    size++; 
}

// Dodaje element w określonym indeksie
template <typename T>
void Arraylist<T>::add(T item, int index) {
    if (index < 0 || index > size) return; // Sprawdzamy, czy indeks jest prawidłowy
    increaseSize(); // Sprawdzamy, czy trzeba zwiększyć pojemność
    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1]; // Przesuwamy elementy w prawo
    }
    arr[index] = item; // Wstawiamy element w podanym indeksie
    size++; 
}

// Usuwa ostatni element z tablicy
template <typename T>
void Arraylist<T>::removeBack() {
    if (size > 0) {
        delete arr[size - 1];  // Zwolnienie pamięci, na którą wskazuje ostatni element
        size--; 
    }
}


// Usuwa pierwszy element z tablicy
template <typename T>
void Arraylist<T>::removeFront() {
    if (size > 0) {
        for (int i = 1; i < size; i++) {
            arr[i - 1] = arr[i]; // Przesuwamy elementy w lewo
        }
        size--; 
    }
}

// Usuwa element o podanym indeksie
template <typename T>
void Arraylist<T>::remove(int index) {
    if (index < 0 || index >= size) return; // Sprawdzamy, czy indeks jest prawidłowy
    if (size > 0) {
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1]; // Przesuwamy elementy w lewo
        }
        size--; 
    }
}

// Zwraca indeks pierwszego wystąpienia danego elementu, lub -1 jeśli nie znaleziono
template <typename T>
int Arraylist<T>::Find(T item) const {
    for (int i = 0; i < size; i++) {
        if (arr[i] == item) {
            return i; // Zwracamy indeks pierwszego wystąpienia
        }
    }
    return -1; // Zwracamy -1, jeśli element nie został znaleziony
}

// Operator dostępu do elementu - jak dla zwykłej tablicy
template <typename T>
T& Arraylist<T>::operator[](const int index) {
    if (index < 0 || index >= size) {
        std::cout << "Index out of bounds" << std::endl; // Jeśli indeks jest poza zakresem
    }
    return arr[index]; // Zwracamy element w podanym indeksie
}
