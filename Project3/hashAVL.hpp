#pragma once
#include <iostream>
#include "AVL.hpp"
using namespace std;

template<typename K, typename V>
class HashTable {
private:
    AVL<K, V>* buckets;
    int initialCapacity;
    int numElements;
    const float maxLoadFactor = 0.75f;

    int hash(const K& key) const;
    bool isPrime(int n);
    int nextPrime(int n);
    void rehashTree(const AVL<K, V>& tree, AVL<K, V>* newBuckets, int newSize);
    void rehash();

public:
    explicit HashTable(int initialCapacity = 100);
    ~HashTable();

    void insert(const K& key, const V& value);
    void remove(const K& key);
    void print();
};

template<typename K, typename V>
int HashTable<K, V>::hash(const K& key) const {
    int h = static_cast<int>(key);
    if (h < 0) h = -h;
    return h % initialCapacity;
}

template<typename K, typename V>
bool HashTable<K, V>::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

template<typename K, typename V>
int HashTable<K, V>::nextPrime(int n) {
    while (!isPrime(n)) ++n;
    return n;
}

template<typename K, typename V>
void HashTable<K, V>::rehashTree(const AVL<K, V>& tree, AVL<K, V>* newBuckets, int newSize) {
    tree.forEach([&](const K& key, const V& value) {
        int idx = static_cast<int>(key);
        if (idx < 0) idx = -idx;
        idx %= newSize;
        newBuckets[idx].insert(key, value);
        });
}

template<typename K, typename V>
void HashTable<K, V>::rehash() {
    int newSize = nextPrime(initialCapacity * 2);
    AVL<K, V>* newBuckets = new AVL<K, V>[newSize];

    for (int i = 0; i < initialCapacity; ++i) {
        rehashTree(buckets[i], newBuckets, newSize);
    }

    delete[] buckets;
    buckets = newBuckets;
    initialCapacity = newSize;
}

template<typename K, typename V>
HashTable<K, V>::HashTable(int size)
    : initialCapacity(nextPrime(size)), numElements(0) {
    buckets = new AVL<K, V>[initialCapacity];
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
    delete[] buckets;
}

template<typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& value) {
    if (float(numElements + 1) / initialCapacity > maxLoadFactor) {
        rehash();
    }
    int idx = hash(key);
    buckets[idx].insert(key, value);
    ++numElements;
}

template<typename K, typename V>
void HashTable<K, V>::remove(const K& key) {
    int idx = hash(key);
    buckets[idx].remove(key);
    if (numElements > 0) --numElements;
}

template<typename K, typename V>
void HashTable<K, V>::print() {
    for (int i = 0; i < initialCapacity; ++i) {
        cout << "Bucket " << i << ": ";
        buckets[i].inOrder();
    }
}
