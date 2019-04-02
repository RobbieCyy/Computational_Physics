#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matrix.h"

using namespace std;

vector<double> generate_b_vector(int n) {
	vector<double> b(n, 1.5);
	b[0] = b[n - 1] = 2.5;
	b[(n / 2) - 1] = b[(n / 2)] = 1;
	return b;
}

matrix generate_A_matrix(int n) {
	matrix A(n, n);
	for (int i = 0; i < n; i++) {
		A[i][i] = 3;
		A[i][n - 1 - i] = 0.5;
	}
	for (int i = 0; i < n - 1; i++) {
		A[i + 1][i] = A[i][i + 1] = -1;
	}
	return A;
}

struct solution {
	int k;
	vector<double> x;
	solution(){}
	solution(int kk, vector<double> & xx) {
		k = kk;
		x = xx;
	}
	solution new_solution(int kk, vector<double> & xx) {
		solution result(kk, xx);
		return result;
	}
};

solution solve(matrix A, vector<double> b, double epsilon) {
	vector<double> x = zeros(b.size());
	vector<double> r = b - A * x;
	vector<double> r_0;
	vector<double> p = r;
	solution result;
	double alpha, beta;
	int k = 0;
	//cout << "b:" << endl;
	//cout << b;
	while (norm(r) / norm(b) > epsilon) {
		cout << norm(r) << ' ' << norm(r) / norm(b) << endl;
		alpha = norm(r) / (p * (A * p));
		x = x + alpha * p;
		r_0 = r;
		r = r - (alpha * A) * p;
		beta = norm(r) / norm(r_0);
		p = r + beta * p;
		++k;
	}
	result = result.new_solution(k, x);
	return result;
}

void showcase(int n) {
	cout << "----------------------------------------------------------------" << endl;
	cout << "n = " << n << endl;
	vector<double> b = generate_b_vector(n);
	matrix A = generate_A_matrix(n);
	solution result = solve(A, b, 1e-3);
	cout << "Solution:" << endl;
	cout << result.x;
	cout << "Number of iteration:" << endl;
	cout << result.k << endl;
	vector<double> residue = (A * result.x) - b;
	cout << "Residue norm:" << endl;
	cout << norm(residue) << endl;
	cout << "----------------------------------------------------------------" << endl;
}

int main() {
	ofstream out("log.txt");
	std::cout.rdbuf(out.rdbuf());
	showcase(10);
	//showcase(100);
	//showcase(10000);
	return 0;
}