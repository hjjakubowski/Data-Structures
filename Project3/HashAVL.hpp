#pragma once
#include <iostream>
#include "AVL.hpp"
using namespace std;

template<typename T, int TABLE_SIZE = 10>
class HashTable {
private:
    AVL<T> trees[TABLE_SIZE];

    int hash(int key);

public:
    HashTable();

    void insert(int key, T value);
    void remove(int key);
    void print();
};

template<typename T, int TABLE_SIZE>
HashTable<T, TABLE_SIZE>::HashTable() {}

template<typename T, int TABLE_SIZE>
int HashTable<T, TABLE_SIZE>::hash(int key) {
    return key % TABLE_SIZE;
}

template<typename T, int TABLE_SIZE>
void HashTable<T, TABLE_SIZE>::insert(int key, T value) {
    int idx = hash(key);
    trees[idx].insert(key, value);
}

template<typename T, int TABLE_SIZE>
void HashTable<T, TABLE_SIZE>::remove(int key) {
    int idx = hash(key);
    trees[idx].remove(key);
}

template<typename T, int TABLE_SIZE>
void HashTable<T, TABLE_SIZE>::print() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        cout << "Bucket " << i << ": ";
        trees[i].inOrder();
    }
}
