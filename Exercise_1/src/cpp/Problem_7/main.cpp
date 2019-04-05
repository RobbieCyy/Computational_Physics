#include <iostream>
#include <iomanip>
#include "Hydrogen.h"

using namespace std;

void Laguerre_test() {
	double alpha[3] = { 2, 20, 40 }, x[3] = { 1e-3, 1, 100 };
	int n[3] = { 3, 10, 30 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cout << setw(16) << n[i] << setw(16) << setprecision(8) << alpha[j]
					<< setw(16) << setprecision(8) << x[k]
					<< setw(16) << setprecision(8) << LaguerreL(n[i], alpha[j], x[k]) << endl;
			}
		}
	}
}

int main() {
	Laguerre_test();

	getchar();
	return 0;
}