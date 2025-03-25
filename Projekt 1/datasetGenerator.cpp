#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <cmath>
#include <string>

using namespace std;

/*
void datasetGenerator() {

    string fileName = "dataset_" + to_string(n) + ".txt";



    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 4294967295);

    for (int i = 0; i < n; ++i) {
        outFile << dis(gen) << ",";
    }

    outFile.close();
    cout << "Dataset wygenerowany i zapisany do pliku dataset.txt" << endl;

}

int main() {
	datasetGenerator(1000);
	datasetGenerator(5000);
	datasetGenerator(10000);
	datasetGenerator(50000);
	datasetGenerator(100000);
    datasetGenerator(250000);
	datasetGenerator(500000);
	datasetGenerator(750000);
	datasetGenerator(1000000);
	datasetGenerator(2500000);
	datasetGenerator(5000000);
	datasetGenerator(7500000);
	datasetGenerator(10000000);
}
*/