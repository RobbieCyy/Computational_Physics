#include <iostream>
#include <fstream>
#include <iomanip>
#include "SPB_Matrix.h"
#define N_INTRAPOLATE 100

using namespace std;

vector<double> x, y, h;
vector<double> M;
int n;
ifstream input("input.txt");

// Solve the equations, return a vector {M[1], M[2], ... , M[n-1]}
void solve_spline_core(vector<double> & result) {
	vector<double> lambda(n - 1), mu(n - 1), d(n - 1);
	SPB_Matrix A(n - 1, 1);
	result.clear();
	result.resize(n - 1);
	h.clear();
	h.resize(n);

	for (int i = 0; i < n; i++) {
		h[i] = x[i + 1] - x[i];
	}
	for (int i = 1; i < n; i++) {
		lambda[i - 1] = h[i] / (h[i - 1] + h[i]);
		mu[i - 1] = h[i - 1] / (h[i - 1] + h[i]);
		d[i - 1] = (-(y[i] - y[i - 1]) / h[i - 1] + (y[i + 1] - y[i]) / h[i]) * 6 / (h[i - 1] + h[i]);
	}
	// Set up the matrix
	for (int i = 0; i < n - 1; i++) {
		A.set_data(i, i, 2);
		if (i != n - 2) {
			A.set_data(i, i + 1, lambda[i]);
		}
		if (i != 0) {
			A.set_data(i - 1, i, mu[i]);
		}
	}
	// Solve the equations
	Solve_SPB(A, d, result);
	return;
}

// Return vector M
void solve_spline(vector<double> & M) {
	M.clear();
	M.resize(n + 1);
	M[0] = M[n] = 0;
	vector<double> temp;

	// Compute M[1] through M[n-1]
	solve_spline_core(temp);
	for (int i = 1; i < n; i++) {
		M[i] = temp[i - 1];
	}
	return;
}

// Compute the intrapolated y value
double spline(double x_query) {
	int i;
	double result = 0;
	// Find in which segment the queried x is
	for (i = n - 1; i >= 0; i--) {
		if (x_query >= x[i]) {
			break;
		}
	}
	// Brute force.
	result = pow((x[i + 1] - x_query), 3) / (6 * h[i]) * M[i] +
		pow((x_query - x[i]), 3) / (6 * h[i]) * M[i + 1]
		+ ((y[i + 1] - y[i]) / h[i] - h[i] * (M[i + 1] - M[i]) / 6) * x_query
		+ (y[i] * x[i + 1] - y[i + 1] * x[i]) / h[i] - h[i] * (x[i + 1] * M[i] - x[i] * M[i + 1]) / 6;
	return result;
}

int main() {
	double t;
	input >> n;
	x.resize(n);
	y.resize(n);
	// Assume x[i] in ascending order
	for (int i = 0; i < n; i++) {
		input >> x[i] >> y[i];
	}
	n--;
	cout << "Initializing ..." << endl;
	// Compute the M vector
	solve_spline(M);
	cout << "Initialization finished." << endl;
	ofstream out("output.txt");
	out << setw(16) << "x";
	out << setw(16) << "f(x)" << endl;
	// Intrapolate for plotting
	for (int i = 0; i <= N_INTRAPOLATE; i++) {
		t = x[0] + (x[n] - x[0]) / N_INTRAPOLATE * i;
		out << setw(16) << setprecision(8) << t;
		out << setw(16) << setprecision(8) << spline(t); // Intrapolate here
		out << endl;
	}
	getchar();
	return 0;
}