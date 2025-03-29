#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include "doublyLinkedList.hpp"


using namespace std;
using namespace std::chrono;



void loadDatasetToList(const string& fileName, DLinkedList<int>& list) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Nie mozna otworzyc pliku do odczytu!" << endl;
        return;
    }

    string line;
    while (getline(inFile, line, ',')) {
        stringstream ss(line);
        int number;
        if (ss >> number) {
            list.addBack(number);
        }
    }

    inFile.close();
}


void performTest(DLinkedList<int>& list, const string& operation, const string& datasetName, int element = 0, int position = 0) {
    
    if (operation == "addFront") {
        auto start = high_resolution_clock::now();
        list.addFront(element);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << endl;

    }
    else if (operation == "addBack") {
        auto start = high_resolution_clock::now();
        list.addBack(element);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << endl;

    }
    else if (operation == "add") {
        auto start = high_resolution_clock::now();
        list.add(element, position);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << endl;

    }
    else if (operation == "removeFront") {
        auto start = high_resolution_clock::now();
        list.removeFront();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << endl;

    }
    else if (operation == "removeBack") {
        auto start = high_resolution_clock::now();
        list.removeBack();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << endl;

    }
    else if (operation == "remove") {
        auto start = high_resolution_clock::now();
        list.remove(position);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << endl;

    }
    else if (operation == "find") {
        auto start = high_resolution_clock::now();
        list.Find(element);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Czas wykonania operacji " << operation << " na zbiorze " << datasetName << ": " << duration.count() << " ns" << endl;

    }
}

int main() {
    string datasets[] = {
        "dataset_5000.txt", "dataset_100000.txt", "dataset_200000.txt", "dataset_300000.txt", "dataset_400000.txt", "dataset_500000.txt",
        "dataset_600000.txt", "dataset_700000.txt", "dataset_800000.txt","dataset_900000.txt", "dataset_1000000.txt"
    };
    while (true) {
        cout << "Wybierz strukture danych do testowania:" << endl;
        cout << "1. Tablica dynamiczna" << endl;
        cout << "2. Lista jednokierunkowa" << endl;
        cout << "3. Lista dwukierunkowa" << endl;
        int structureChoice;
        cin >> structureChoice;

        cout << "Wybierz rodzaj testu:" << endl;
        cout << "1. Dodanie elementu na poczatek" << endl;
        cout << "2. Dodanie elementu na koniec" << endl;
        cout << "3. Dodanie elementu w dowolnym miejscu" << endl;
        cout << "4. Usuniecie poczatkowego elementu" << endl;
        cout << "5. Usuniecie koncowego elementu" << endl;
        cout << "6. Usuniecie elementu z dowolnej pozycji" << endl;
        cout << "7. Znalezienie podanego przez uzytkownika elementu" << endl;
        int testChoice;
        cin >> testChoice;

        string operation;
        int element = 0;
        int position = 0;
        switch (testChoice) {
        case 1: operation = "addFront"; break;
        case 2: operation = "addBack"; break;
        case 3: operation = "add";
            cout << "Podaj element do dodania: ";
            cin >> element;
            cout << "Podaj pozycje: ";
            cin >> position;
            break;
        case 4: operation = "removeFront"; break;
        case 5: operation = "removeBack"; break;
        case 6: operation = "remove";
            cout << "Podaj pozycje: ";
            cin >> position;
            break;
        case 7: operation = "find";
            cout << "Podaj element do znalezienia: ";
            cin >> element;
            break;
        default: cout << "Nieprawidlowy wybor!" << endl; continue;
        }
        
        for (int i = 0; i < 11; ++i) {
            string datasetName = datasets[i];
            DLinkedList<int> list;
            loadDatasetToList(datasetName, list);
            performTest(list, operation, datasetName, element, position);
            //cout << list.getSize() << endl;
        }
        
        cout << "Czy chcesz wykonac kolejne testy? (t/n): ";
        char cont;
        cin >> cont;
        if (cont == 'n' || cont == 'N') {
            break;
        }
    }

    return 0;
}


	
   

