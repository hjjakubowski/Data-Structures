#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include "arrayList.hpp"
#include "SingleLinkList.hpp"

using namespace std::chrono;

template <typename ListType>
void loadDataset(const std::string& fileName, ListType& list) {
    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Nie mozna otworzyc pliku do odczytu!" << std::endl;
        return;
    }

    std::string line;
    while (getline(inFile, line, ',')) {
        std::stringstream ss(line);
        int number;
        if (ss >> number) {
            if constexpr (std::is_same_v<ListType, Singlelist<int>>) {
                list.addFront(number);
            }
            else if constexpr (std::is_same_v<ListType, Arraylist<int>>) {
                list.addBack(number);
            }
            else {
                list.addBack(number);
            }
        }
    }

    inFile.close();
}


template <typename ListType>
void performTest(ListType& list, const std::string& operation, const std::string& datasetName, int element = 0, int position = 0) {
    auto start = high_resolution_clock::now();

    if (operation == "addFront") {
        list.addFront(element);
    }
    else if (operation == "addBack") {
        list.addBack(element);
    }
    else if (operation == "add") {
        list.add(element, position);
    }
    else if (operation == "removeFront") {
        list.removeFront();
    }
    else if (operation == "removeBack") {
        list.removeBack();
    }
    else if (operation == "remove") {
        list.remove(position);
    }
    else if (operation == "find") {
        list.Find(element);
    }


    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    std::cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << std::endl;
}

template <typename ListType>
void autoPT(const std::string& listName, int element = 43) {
    std::string operation[] = { "addFront", "addBack", "add", "removeFront", "removeBack", "remove", "find" };

    std::string datasets[] = {
        "dataset_5000.txt", "dataset_100000.txt", "dataset_200000.txt", "dataset_300000.txt", "dataset_400000.txt", "dataset_500000.txt",
        "dataset_600000.txt", "dataset_700000.txt", "dataset_800000.txt", "dataset_900000.txt", "dataset_1000000.txt"
    };

    std::cout << "--- " << listName << " ---" << std::endl;
    int position = 0;
    for (int i = 2; i < 7; i++) {
        std::cout << "=== Operation: " << operation[i] << " ===" << std::endl;
        for (int k = 0; k < 10; k++) {
            double totalDuration = 0;
            if (k == 0) { position = 4999; }
            else { position = 99999 + (k - 1) * 100000; }
            std::cout << position << std::endl;

            for (int j = 0; j < 10; j++) {
                ListType list;
                loadDataset(datasets[k], list);

                auto start = high_resolution_clock::now();

                if (operation[i] == "addFront") {
                    list.addFront(element);
                }
                else if (operation[i] == "addBack") {
                    list.addBack(element);
                }
                else if (operation[i] == "add") {
                    list.add(element, position);
                }
                else if (operation[i] == "removeFront") {
                    list.removeFront();
                }
                else if (operation[i] == "removeBack") {
                    list.removeBack();
                }
                else if (operation[i] == "remove") {
                    list.remove(position);
                }
                else if (operation[i] == "find") {
                    list.Find(element);
                }

                auto end = high_resolution_clock::now();
                totalDuration += duration_cast<nanoseconds>(end - start).count();
            }
            
            
            std::cout <<position<< std::endl;
            std::cout << "Dataset: " << datasets[k] << " | Avg time: " << totalDuration / 10 << " ns" << std::endl;
        }
        
    }

    std::cout << "==============================" << std::endl;
}



int main() {
    std::string datasets[] = {
        "dataset_5000.txt", "dataset_100000.txt", "dataset_200000.txt", "dataset_300000.txt", "dataset_400000.txt", "dataset_500000.txt",
        "dataset_600000.txt", "dataset_700000.txt", "dataset_800000.txt","dataset_900000.txt", "dataset_1000000.txt"
    };

    //autoPT<Arraylist<int>>("Arraylist");
    autoPT<Singlelist<int>>("Singlelist");
    //runAutoTest<Doublelist<int>>(dataset, "Doublelist");

    std::cout << "==============================" << std::endl;




    while (true) {
        std::cout << "Wybierz strukture danych do testowania:" << std::endl;
        std::cout << "1. Tablica dynamiczna" << std::endl;
        std::cout << "2. Lista jednokierunkowa" << std::endl;
        std::cout << "3. Lista dwukierunkowa" << std::endl;
        int structureChoice;
        std::cin >> structureChoice;

        std::cout << "Wybierz rodzaj testu:" << std::endl;
        std::cout << "1. Dodanie elementu na poczatek" << std::endl;
        std::cout << "2. Dodanie elementu na koniec" << std::endl;
        std::cout << "3. Dodanie elementu w dowolnym miejscu" << std::endl;
        std::cout << "4. Usuniecie poczatkowego elementu" << std::endl;
        std::cout << "5. Usuniecie koncowego elementu" << std::endl;
        std::cout << "6. Usuniecie elementu z dowolnej pozycji" << std::endl;
        std::cout << "7. Znalezienie podanego przez uzytkownika elementu" << std::endl;
        int testChoice;
        std::cin >> testChoice;

        std::string operation;
        int element = 0;
        int position = 0;
        switch (testChoice) {
        case 1: operation = "addFront"; break;
        case 2: operation = "addBack"; break;
        case 3: operation = "add";
            std::cout << "Podaj element do dodania: ";
            std::cin >> element;
            std::cout << "Podaj pozycje: ";
            std::cin >> position;
            break;
        case 4: operation = "removeFront"; break;
        case 5: operation = "removeBack"; break;
        case 6: operation = "remove";
            std::cout << "Podaj pozycje: ";
            std::cin >> position;
            break;
        case 7: operation = "find";
            std::cout << "Podaj element do znalezienia: ";
            std::cin >> element;
            break;
        default: std::cout << "Nieprawidlowy wybor!" << std::endl; break;
        }

        for (const std::string& datasetName : datasets) {

            if (structureChoice == 1) {
                Arraylist<int> list;
                loadDataset(datasetName, list);
                performTest(list, operation, datasetName, element, position);

            }
            else if (structureChoice == 2) {
                Singlelist<int> list;
                loadDataset(datasetName, list);
                performTest(list, operation, datasetName, element, position);

            }
            else {
                std::cout << "Nieprawidlowy wybor!" << std::endl;
                break;
            }

        }

        std::cout << "Czy chcesz wykonac kolejne testy? (t/n): ";
        char cont;
        std::cin >> cont;
        if (cont == 'n' || cont == 'N') {
            break;
        }
    }

    return 0;
}