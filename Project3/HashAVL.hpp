#pragma once
#include <iostream>
#include "AVL.hpp"
using namespace std;

template<typename K, typename V>
class HashTable {
private:
    AVL<K, V>* buckets;
    int tableSize;
    int numElements;
    const float maxLoadFactor = 0.75f;

    int hash(const K& key) const {
        int h = static_cast<int>(key);
        if (h < 0) h = -h;
        return h % tableSize;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; ++i)
            if (n % i == 0) return false;
        return true;
    }

    int nextPrime(int n) {
        while (!isPrime(n)) ++n;
        return n;
    }

    void rehashTree(const AVL<K, V>& tree, AVL<K, V>* newBuckets, int newSize) {
        tree.forEach([&](const K& key, const V& value) {
            int idx = static_cast<int>(key);
            if (idx < 0) idx = -idx;
            idx %= newSize;
            newBuckets[idx].insert(key, value);
        });
    }

    void rehash() {
        int newSize = nextPrime(tableSize * 2);
        AVL<K, V>* newBuckets = new AVL<K, V>[newSize];

        for (int i = 0; i < tableSize; ++i) {
            rehashTree(buckets[i], newBuckets, newSize);
        }

        delete[] buckets;
        buckets = newBuckets;
        tableSize = newSize;
    }

public:
    explicit HashTable(int size = 100) : tableSize(nextPrime(size)), numElements(0) {
        buckets = new AVL<K, V>[tableSize];
    }

    ~HashTable() {
        delete[] buckets;
    }

    void insert(const K& key, const V& value) {
        if (float(numElements + 1) / tableSize > maxLoadFactor) {
            rehash();
        }
        int idx = hash(key);
        buckets[idx].insert(key, value);
        ++numElements;
    }

    void remove(const K& key) {
        int idx = hash(key);
        buckets[idx].remove(key);
        if (numElements > 0) --numElements;
    }

    void print() {
        for (int i = 0; i < tableSize; ++i) {
            cout << "Bucket " << i << ": ";
            buckets[i].inOrder();
        }
    }
};
