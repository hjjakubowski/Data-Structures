#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include "linkedQueue.hpp"
#include "HeapyPriorityQueue.hpp"


template<typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

template <typename QueueType>
void autoPT(const std::string& queueName) {
    std::string operations[] = { "insert", "extractMax", "findMax", "modifyKey", "getSize" };
    int dataSizes[] = { 5000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 };

    std::cout << "--- " << queueName << " ---" << std::endl;

    for (const std::string& opName : operations) {
        std::cout << "=== Operacja: " << opName << " ===" << std::endl;

        for (int dataSize : dataSizes) {
            double totalDuration = 0;

            for (int seed = 1; seed <= 10; ++seed) {
                QueueType queue;
                std::mt19937 generator(seed);
                std::uniform_int_distribution<> dis(1, 2*dataSize);



                for (int i = 0; i < dataSize; ++i) {
                    queue.insert(i , dis(generator));
                }

                int testElement = dataSize - 1;
                int testPriority = queue.findMax() - 1;

                if (opName == "insert") {
                    totalDuration += measureTime([&]() { queue.insert(testElement, testPriority); });
                }
                else if (opName == "extractMax") {
                    totalDuration += measureTime([&]() { queue.extractMax(); });
                }
                else if (opName == "findMax") {
                    totalDuration += measureTime([&]() { queue.findMax(); });
                }
                else if (opName == "modifyKey") {
                    totalDuration += measureTime([&]() { queue.modifyKey(testElement, testPriority + 1); });
                }
                else if (opName == "getSize") {
                    totalDuration += measureTime([&]() { queue.getSize(); });
                }
            }

            std::cout << "Rozmiar: " << dataSize << " | Sredni czas operacji " << opName
                << " = " << totalDuration / 10 << " ns" << std::endl;
        }
    }

    std::cout << "==============================" << std::endl;
}

template<typename QueueType>
void queueMenu(QueueType& queue) {
    int choice = -1;
    while (choice != 6) {
        std::cout << "\nMenu Kolejki:\n";
        std::cout << "1. Dodaj element\n";
        std::cout << "2. Zmien priorytet elementu\n";
        std::cout << "3. Wyciagnij max\n";
        std::cout << "4. Wydrukuj kolejke\n";
        std::cout << "5. Znajdz max\n";
        std::cout << "6. Wyjdz do glownego menu\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> choice;

        int element, priority;

        switch (choice) {
        case 1:
            std::cout << "Podaj element i jego priorytet: ";
            std::cin >> element >> priority;
            queue.insert(element, priority);
            break;
        case 2:
            std::cout << "Podaj element do zmiany priorytetu: ";
            std::cin >> element;
            std::cout << "Podaj nowy priorytet: ";
            std::cin >> priority;
            queue.modifyKey(element, priority);
            break;
        case 3:
            std::cout << "Max element: " << queue.extractMax() << " wyciagniety" << std::endl;
            break;
        case 4:
            queue.print();
            break;
        case 5:
            std::cout << "Max element: " << queue.findMax() << std::endl;
            break;
        case 6:
            break;
        default:
            std::cout << "Nieprawidlowy wybor!\n";
            break;
        }
    }
    std::cout << std::endl << std::endl;
}

void menu() {
    std::cout << "Wybierz strukture kolejki:\n";
    std::cout << "1. LinkedQueue\n";
    std::cout << "2. HeapyPriorityQueue\n";
    std::cout << "3. AutoPT (Pomiar czasu)\n";
    std::cout << "0. Zakoncz\n";
}

int main() {
    int mainChoice = -1;
    LinkedQueue<int> linkedQueue;
    HeapyPriorityQueue<int> heapyQueue;

    while (mainChoice != 0) {
        menu();
        std::cout << "Wybierz opcje: ";
        std::cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            queueMenu(linkedQueue);
            break;
        case 2:
            queueMenu(heapyQueue);
            break;
        case 3:
            autoPT<HeapyPriorityQueue<int>>("Heap-based Priority Queue");
            autoPT<LinkedQueue<int>>("Linked Queue");
            break;
        case 0:
            std::cout << "Zakonczono program.\n";
            break;
        default:
            std::cout << "Nieprawidlowy wybor!\n";
            break;
        }
    }

    return 0;
}

