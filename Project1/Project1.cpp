#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <random>
#include "arrayList.hpp"
#include "SingleLinkList.hpp"
#include "DoublyLinkedList.hpp"

using namespace std::chrono;


template <typename Func>
long long measureTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

template <typename ListType>
void generateDataset(ListType& list, int size, int seed) {
    std::mt19937 generator(seed); 
    std::uniform_int_distribution<> dis(1, 2147483647);

    for (int i = 0; i < size; ++i) {
        if constexpr (std::is_same_v<ListType, Singlelist<int>>) {
            list.addFront(dis(generator));
        }
        else {
            list.addBack(dis(generator));
        }
    }
}

template <typename ListType>
void autoPT(const std::string& listName, int element = 43) {
    std::string operations[] = { "addFront", "addBack", "add", "removeFront", "removeBack", "remove", "find" };
    int dataSizes[] = { 5000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 };

    std::cout << "--- " << listName << " ---" << std::endl;

    for (const std::string& opName : operations) {
        std::cout << "=== Operation: " << opName << " ===" << std::endl;

        for (int dataSize : dataSizes) {
            double totalDuration = 0;
            int position = dataSize / 2;

            for (int seed = 1; seed <= 10; ++seed) {
                ListType list;
                generateDataset(list, dataSize, seed);

                if (opName == "addFront") {
                    totalDuration += measureTime([&]() { list.addFront(element); });
                }
                else if (opName == "addBack") {
                    totalDuration += measureTime([&]() { list.addBack(element); });
                }
                else if (opName == "add") {
                    totalDuration += measureTime([&]() { list.add(element, position); });
                }
                else if (opName == "removeFront") {
                    totalDuration += measureTime([&]() { list.removeFront(); });
                }
                else if (opName == "removeBack") {
                    totalDuration += measureTime([&]() { list.removeBack(); });
                }
                else if (opName == "remove") {
                    totalDuration += measureTime([&]() { list.remove(position); });
                }
                else if (opName == "find") {
                    totalDuration += measureTime([&]() { list.Find(element); });
                }
            }

            std::cout << "Rozmiar: " << dataSize << " | Sredni czas operacji " << opName
                << " = " << totalDuration / 10 << " ns" << std::endl;
        }
    }

    std::cout << "==============================" << std::endl;
}

int main() {
    autoPT<Arraylist<int>>("Tablica Dynamiczna");
    autoPT<Singlelist<int>>("Lista jednokierunkowa");
    autoPT<DLinkedList<int>>("Lista dwukierunkowa");
    return 0;
}
