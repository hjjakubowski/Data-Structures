#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include "HashAVL.hpp"

using namespace std;

long long measureTime(auto func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

void autoTestHashTable() {
    cout << "--- Autotest HashTable ---\n";

    int sizes[] = { 5000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 };

    for (int size : sizes) {
        mt19937 gen(42);

        int* keys = new int[size];
        int* values = new int[size];

        for (int i = 0; i < size; ++i) {
            keys[i] = i;
        }

        shuffle(keys, keys + size, gen);

        uniform_int_distribution<int> dis(1, size * 10);
        for (int i = 0; i < size; ++i) {
            values[i] = dis(gen);
        }

        HashTable<int, int> table(1000);

        long long insertTime = measureTime([&]() {
            for (int i = 0; i < size; ++i) {
                table.insert(keys[i], values[i]);
            }
        });

        long long removeTime = measureTime([&]() {
            for (int i = 0; i < size / 2; ++i) {
                table.remove(keys[i]);
            }
        });

        cout << "Rozmiar: " << size << "\n";
        cout << "Sredni czas wstawiania (na element): " << (insertTime / size) << " ns\n";
        cout << "Sredni czas usuwania (na element): " << (removeTime / (size / 2)) << " ns\n";
        cout << "---------------------------\n";

        delete[] keys;
        delete[] values;
    }
}

void menu() {
    cout << "\nMenu HashTable:\n";
    cout << "1. Dodaj element\n";
    cout << "2. Usun element\n";
    cout << "3. Wyswietl tablice\n";
    cout << "4. Autotest (pomiar czasu)\n";
    cout << "5. Wyjdz\n";
    cout << "Wybierz opcje: ";
}

void hashTableMenu() {
    HashTable<int, int> table;

    int choice = -1;
    while (choice != 5) {
        menu();
        cin >> choice;

        if (choice == 1) {
            int key, value;
            cout << "Podaj klucz i wartosc: ";
            cin >> key >> value;
            table.insert(key, value);
        } else if (choice == 2) {
            int key;
            cout << "Podaj klucz do usuniecia: ";
            cin >> key;
            table.remove(key);
        } else if (choice == 3) {
            table.print();
        } else if (choice == 4) {
            autoTestHashTable();
        } else if (choice == 5) {
            cout << "Zakonczono program.\n";
        } else {
            cout << "Nieprawidlowy wybor!\n";
        }
    }
}

int main() {
    hashTableMenu();
    return 0;
}
