#pragma once
#include <iostream>
#include "AVL.hpp"
using namespace std;

// Szablonowa klasa HashTable oparta o tablicę AVL drzew
template<typename K, typename V>
class HashTable {
private:
    AVL<K, V>* buckets;       // Tablica drzew AVL (każde "wiadro" to jedno drzewo)
    int tableSize;            // Aktualna liczba wiader (rozmiar tablicy)
    int numElements;          // Liczba wstawionych elementów
    const float maxLoadFactor = 0.75f; // Maksymalny współczynnik zapełnienia

    // Funkcja mieszająca — zakłada, że typ K można rzutować na int
    int hash(const K& key) const {
        int h = static_cast<int>(key); // Zamiana klucza na liczbę całkowitą
        if (h < 0) h = -h;              // Upewniamy się, że jest nieujemna
        return h % tableSize;          // Indeks w tablicy (modulo rozmiar)
    }

    // Sprawdza, czy liczba jest pierwsza
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; ++i)
            if (n % i == 0) return false;
        return true;
    }

    // Zwraca najbliższą większą liczbę pierwszą
    int nextPrime(int n) {
        while (!isPrime(n)) ++n;
        return n;
    }

    // Pomocnicza funkcja do przenoszenia jednego drzewa AVL do nowej tablicy
    void rehashTree(const AVL<K, V>& tree, AVL<K, V>* newBuckets, int newSize) {
        tree.forEach([&](const K& key, const V& value) {
            int idx = static_cast<int>(key);
            if (idx < 0) idx = -idx;
            idx %= newSize;
            newBuckets[idx].insert(key, value);
        });
    }

    // Rehashowanie: tworzy nową tablicę większego rozmiaru i przenosi dane
    void rehash() {
        int newSize = nextPrime(tableSize * 2); // Znajdź nowy większy rozmiar (liczba pierwsza)
        AVL<K, V>* newBuckets = new AVL<K, V>[newSize];

        for (int i = 0; i < tableSize; ++i) {
            rehashTree(buckets[i], newBuckets, newSize);
        }

        delete[] buckets; // Usunięcie starej tablicy
        buckets = newBuckets;
        tableSize = newSize;
    }

public:
    // Konstruktor: inicjalizuje tablicę AVL z rozmiarem będącym liczbą pierwszą
    explicit HashTable(int size = 100) : tableSize(nextPrime(size)), numElements(0) {
        buckets = new AVL<K, V>[tableSize];
    }

    // Destruktor: usuwa dynamicznie alokowaną tablicę
    ~HashTable() {
        delete[] buckets;
    }

    // Wstawianie elementu — rehashowanie jeśli zbyt wysoki współczynnik zapełnienia
    void insert(const K& key, const V& value) {
        if (float(numElements + 1) / tableSize > maxLoadFactor) {
            rehash(); // Rozszerz tablicę i przenieś dane
        }
        int idx = hash(key);               // Wyznacz indeks
        buckets[idx].insert(key, value);   // Wstaw do odpowiedniego drzewa AVL
        ++numElements;
    }

    // Usuwanie elementu o podanym kluczu
    void remove(const K& key) {
        int idx = hash(key);         // Znajdź odpowiednie wiadro
        buckets[idx].remove(key);    // Usuń z drzewa AVL
        if (numElements > 0) --numElements;
    }

    // Wydrukuj zawartość całej tablicy
    void print() {
        for (int i = 0; i < tableSize; ++i) {
            cout << "Bucket " << i << ": ";
            buckets[i].inOrder();    // Wypisuje elementy w kolejności rosnącej kluczy
        }
    }
};
