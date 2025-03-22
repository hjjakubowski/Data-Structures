#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <cmath>
#include <string>

using namespace std;

int main() {
    cout << "Podaj iloœæ liczb do wygenerowania: (min 10 000 x " << pow(10, n) << " dla n>=0)" << endl;
	cin >> n;
    
	string fileName = "dataset_" + to_string(n) + ".txt";

	if (n < 10000) {
		cout << "Podana liczba jest za ma³a!" << endl;
		return 1;
	}

    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Nie mo¿na otworzyæ pliku do zapisu!" << endl;
        return 1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, n);

    for (int i = 0; i < n; ++i) {
        outFile << dis(gen) << endl;
    }

    outFile.close();
    cout << "Dataset wygenerowany i zapisany do pliku dataset.txt" << endl;

    return 0;
}