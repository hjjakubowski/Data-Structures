#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <vector>
#include <sstream>
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
    std::string operations[] = { "insert", "extractMax", "findMax", "modifyKey", "empty" };
    std::vector<int> dataSizes = { 5000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 };
    int repeatCount = 1;

	std::cout << "Tworzenie kolejek..." << std::endl;
    std::vector<std::unique_ptr<QueueType>> preparedQueues;

    for (int dataSize : dataSizes) {
        std::mt19937 generator(1);
        std::uniform_int_distribution<> priorityDistribution(1, dataSize * 2);

        std::vector<std::pair<int, int>> data;
        for (int i = 0; i < dataSize; ++i) {
            data.emplace_back(i, priorityDistribution(generator));
        }

        auto queue = std::make_unique<QueueType>();
        for (const auto& [element, priority] : data) {
            queue->insert(element, priority);
        }
        preparedQueues.push_back(std::move(queue));
    }
	std::cout << "Kolejki utworzone." << std::endl;

    std::cout << "--- " << queueName << " ---" << std::endl;

    for (const std::string& opName : operations) {
        std::cout << "=== Operacja: " << opName << " ===" << std::endl;

        for (size_t idx = 0; idx < dataSizes.size(); ++idx) {
            int dataSize = dataSizes[idx];
            const auto& preparedQueue = preparedQueues[idx];
            double totalDuration = 0;

            for (int r = 0; r < repeatCount; ++r) {
                auto queue = std::make_unique<QueueType>(*preparedQueue);

                int testElement = dataSize - 1;

                if (opName == "insert") {
                    totalDuration += measureTime([&]() {
                        queue->insert(testElement, 5);
                        });
                }
                else if (opName == "extractMax") {
                    totalDuration += measureTime([&]() {
                        queue->extractMax();
                        });
                }
                else if (opName == "findMax") {
                    totalDuration += measureTime([&]() {
                        queue->findMax();
                        });
                }
                else if (opName == "modifyKey") {
                    totalDuration += measureTime([&]() {
                        queue->modifyKey(testElement, 6);
                        });
                }
                else if (opName == "empty") {
                    totalDuration += measureTime([&]() {
                        queue->empty();
                        });
                }
            }

            std::cout << "Rozmiar: " << dataSize << " | Sredni czas operacji " << opName
                << " = " << totalDuration / repeatCount << " ns" << std::endl;
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
        std::cout << "5. Sprawdz czy kolejka jest pusta\n";
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
            std::cout << "Max element: " << queue.extractMax() << std::endl;
            break;
        case 4:
            queue.print();
            break;
        case 5:
            std::cout << (queue.empty() ? "Kolejka jest pusta" : "Kolejka nie jest pusta") << std::endl;
            break;
        case 6:
            break;
        default:
            std::cout << "Nieprawidlowy wybor!\n";
            break;
        }
    }
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
            autoPT<LinkedQueue<int>>("Linked Queue");
            autoPT<HeapyPriorityQueue<int>>("Heap-based Priority Queue");
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
