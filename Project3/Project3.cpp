﻿#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include "bucketListHM.hpp"
#include "linearProbingHM.hpp"
#include "hashAVL.hpp"


long long measureTime(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

void generateTestData(int* keys, int* values, int n, int seed = 42) {
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dis(1, n * 10);
    for (int i = 0; i < n; ++i) {
        keys[i] = i;
        values[i] = dis(gen);
    }
}

template <typename HashTableType>
void autoTestHashTable(const std::string& name, int initialCapacity) {
    std::cout << "--- Autotest HashTable: " << name << " ---\n";
    int sizes[] = { 5000, 100000, 200000, 300000, 400000, 500000, 1000000, 2500000,5000000};
    int repeatCount = 10;

    for (int size : sizes) {
        int* keys = new int[size];
        int* values = new int[size];
        generateTestData(keys, values, size);

        long long totalInsertTime = 0;
        long long totalRemoveTime = 0;

        for (int r = 0; r < repeatCount; ++r) {
            HashTableType table(initialCapacity);

            long long insertTime = measureTime([&]() {
                for (int i = 0; i < size; ++i) {
                    table.insert(keys[i], values[i]);
                }
                });
            totalInsertTime += insertTime;

            long long removeTime = measureTime([&]() {
                for (int i = 0; i < size / 2; ++i) {
                    table.remove(keys[i]);
                }
                });
            totalRemoveTime += removeTime;
        }

        std::cout << "Rozmiar: " << size << std::endl;
        std::cout << "Sredni czas wstawiania (na element): "
            << (totalInsertTime / repeatCount / size) << " ns" << std::endl;
        std::cout << "Sredni czas usuwania (na element): "
            << (totalRemoveTime / repeatCount / (size / 2)) << " ns" << std::endl;
        std::cout << "---------------------------" << std::endl;

        delete[] keys;
        delete[] values;
    }
}


template <typename HashTableType>
void hashTableMenu(const std::string& name, int initialCapacity = 100000) {
    HashTableType table(initialCapacity);
    int choice = -1;
    while (choice != 4) {
        std::cout << "\nWybrana implementacja: " << name << "\n";
        std::cout << "1. Dodaj element\n";
        std::cout << "2. Usun element\n";
        std::cout << "3. Wyswietl tablice\n";
        std::cout << "4. Wyjdz\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> choice;

        if (choice == 1) {
            int key, value;
            std::cout << "Podaj klucz i wartosc: ";
            std::cin >> key >> value;
            table.insert(key, value);
        }
        else if (choice == 2) {
            int key;
            std::cout << "Podaj klucz do usuniecia: ";
            std::cin >> key;
            table.remove(key);
        }
        else if (choice == 3) {
            table.print();
        }
        else if (choice == 4) {
            std::cout << "Powrot do menu glownego.\n";
        }
        else {
            std::cout << "Nieprawidlowy wybor!\n";
        }
    }
}



void mainMenu() {
    int choice = -1;
    while (choice != 4) {
        std::cout << "\nWybierz implementacje tablicy mieszajacej:\n";
        std::cout << "1. Separate Chaining HM\n";
        std::cout << "2. Linear Probing HM\n";
        std::cout << "3. Autotest wszystkich implementacji\n";
        std::cout << "4. Wyjdz\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            hashTableMenu<HashMapBucketList<int, int>>("Chain separating HM");
            break;
        case 2:
            hashTableMenu<HashMapLinearProbing<int, int>>("Linear Probing HM");
            break;
        case 3:
            autoTestHashTable<HashMapBucketList<int, int>>("Chain separating HM", 1000000);   
            autoTestHashTable<HashMapLinearProbing<int, int>>("Linear Probing HM", 100); 
			autoTestHashTable<HashTable<int, int>>("Hash AVL", 1000000);
            break;
        case 4:
            std::cout << "Zakonczono program.\n";
            break;
        default:
            std::cout << "Nieprawidlowy wybor!\n";
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
