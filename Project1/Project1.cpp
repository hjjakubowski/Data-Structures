#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include "arrayList.hpp"
#include "SingleLinkList.h"
#include "DoublyLinkedList.hpp"



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
            list.addBack(number);
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
        list.add(element,position);
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
/*

template <typename ListType>
void performTest(ListType& list, const std::string& operation, const std::string& datasetName, int element = 0, int position = 0) {

    if (operation == "addFront") {
        auto start = high_resolution_clock::now();
        list.addFront(element);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        std::cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << std::endl;

    }
    else if (operation == "addBack") {
        auto start = high_resolution_clock::now();
        list.addBack(element);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        std::cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << std::endl;

    }
    else if (operation == "add") {
        auto start = high_resolution_clock::now();
        list.add(element, position);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        std::cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << std::endl;

    }
    else if (operation == "removeFront") {
        auto start = high_resolution_clock::now();
        list.removeFront();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        std::cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << std::endl;

    }
    else if (operation == "removeBack") {
        auto start = high_resolution_clock::now();
        list.removeBack();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        std::cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << std::endl;

    }
    else if (operation == "remove") {
        auto start = high_resolution_clock::now();
        list.remove(position);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        std::cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << std::endl;

    }
    else if (operation == "find") {
        auto start = high_resolution_clock::now();
        list.Find(element);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        std::cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << std::endl;

    }
}

*/


int main() {
    std::string datasets[] = {
        "dataset_5000.txt", "dataset_100000.txt", "dataset_200000.txt", "dataset_300000.txt", "dataset_400000.txt", "dataset_500000.txt",
        "dataset_600000.txt", "dataset_700000.txt", "dataset_800000.txt","dataset_900000.txt", "dataset_1000000.txt"
    };
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
           
            if (structureChoice == 1){
                Arraylist<int> list;
				loadDataset(datasetName, list);
				performTest(list, operation, datasetName, element, position);
                
			}
			else if (structureChoice == 2) {
                Singlelist<int> list;
				loadDataset(datasetName, list);
				performTest(list, operation, datasetName, element, position);
               
            }
			else if (structureChoice == 3) {
				DLinkedList<int> list;
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


	
   

