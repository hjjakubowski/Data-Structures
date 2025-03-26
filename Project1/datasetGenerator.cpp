#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <cmath>
#include <string>

using namespace std;


void datasetGenerator(int n) {


    string fileName = "dataset_" + to_string(n)  + ".txt";

    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 2147483647);

    for (int i = 0; i < n; ++i) {
        outFile << dis(gen) << ",";
    }

    outFile.close();
    cout << "Dataset wygenerowany i zapisany do pliku dataset" + to_string(n) +  ".txt" << endl;
    

}
/*
int main() {
	datasetGenerator(5000);
	datasetGenerator(10000);
	datasetGenerator(50000);
	datasetGenerator(100000);
	datasetGenerator(200000);
    datasetGenerator(300000);
	datasetGenerator(400000);
	datasetGenerator(500000);
	datasetGenerator(600000);
	datasetGenerator(700000);
	datasetGenerator(800000);
	datasetGenerator(900000);
	datasetGenerator(1000000);
}
*/