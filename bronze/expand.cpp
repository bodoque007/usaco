#include <iostream>
#include <fstream>

using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ifstream inputFile("cowsignal.in");
    ofstream outputFile("cowsignal.out");

    int n, m, k;

    inputFile >> n >> m >> k;
    inputFile.ignore();


    int count = 0;
    while (count < n) {
        string row;
        getline(inputFile, row);
        for (int i = 0; i < k; i++) {
            for (char c : row) {
                for (int j = 0; j < k; j++) {
                    outputFile << c;
                }
            }
            outputFile << endl;
        }
        count++;
}
    inputFile.close();
    outputFile.close();
    return 0;
}
