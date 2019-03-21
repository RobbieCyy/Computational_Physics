#ifndef SPB_MATRIX
#define SPB_MATRIX

#include <string>
#include <iostream>
#include <iomanip>
#include "General_matrix.h"

using namespace std;

// SPB_Matrix: Symmetric Positive-definite Band-like Matrix
/*
================================================================================
Program Description
--------------------------------------------------------------------------------
This file defines class SPB_Matrix and the function for solving SPB equations.

void Solve_SPB(SPB_Matrix & A, vector<double> & b, vector<double> & sol):
Solve the equations AX=b, restore the solution in sol.
--------------------------------------------------------------------------------
*/

class SPB_Matrix {
private:
	int n;								// Size of the matrix
	int m;								// Half band width (HBW)
	vector<vector<double>> data;		// Data, only restore the non-trivial elements in the lower half triangle.
public:
	// Constructor, initialize the matrix to a nn * nn matrix with HBW = mm
	SPB_Matrix(int nn = 0, int mm = 0) {
		n = nn;
		m = mm;
		data.resize(n);
		for (int i = 0; i < n; i++) {
			data[i].resize(m + 1);
		}
	}
	// Get HBW of the matrix
	inline int get_m() {
		return m;
	}
	// Get size of the matrix
	inline int get_n() {
		return n;
	}
	// Get A(i, j)
	inline double get_data(int i, int j) {
		return i > j ? (j - i + m >= 0 ? data[i][j - i + m] : 0) : (i - j + m >= 0 ? data[j][i - j + m] : 0);
	}
	// Set A(i, j)
	void set_data(int i, int j, double x) {
		(i < j ? (i - j + m >= 0 ? data[j][i - j + m] : x) : (j - i + m >= 0 ? data[i][j - i + m] : x)) = x;
	}
	// Convert SPB_Matrix to a General_matrix
	General_matrix SPB_2_General() {
		General_matrix result(n);
		//clog << "SPB_2_General:" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				//clog << setw(16) << setprecision(6) << get_data(i, j);
				result.data[i][j] = get_data(i, j);
			}
			//clog << endl;
		}
		return result;
	}
	// Resize the SPB_Matrix, works in the same way as the constructor
	// !! NOT TO BE CONFUSED WITH THE resize FUNCTION OF VECTORS !!
	void resize(int nn = 0, int mm = 0) {
		n = nn;
		m = mm;
		data.resize(n);
		for (int i = 0; i < n; i++) {
			data[i].resize(m + 1);
		}
	}
	// Friend with Solve_SPB, the function to solve SPB equations
	friend void Solve_SPB(SPB_Matrix &, vector<double> &, vector<double> &);
};

// Operator for printing vectors
ostream & operator << (ostream & out, const vector<double> vec) {
	for (int i = 0; i < int(vec.size()); i++) {
		out << setw(16) << setprecision(8) << ((abs(vec[i]) < 0.00001) ? 0 : vec[i]) << endl;
	}
	return out;
}

// The function to solve SPB equations AX=b, solution is restored in sol.
void Solve_SPB(SPB_Matrix & A, vector<double> & b, vector<double> & sol) {
	SPB_Matrix L(A.n, A.m);
	// Compute L matrix
	for (int j = 0; j < A.n; j++) {
		for (int i = j; i < A.n && i <= j + A.m; i++) {
			double temp;
			temp = A.get_data(i, j);
			for (int k = (i - A.m > 1) ? i - A.m - 1 : 0; k < j; k++) {
				temp -= L.get_data(i, k) * L.get_data(j, k) / L.get_data(k, k);
			}
			L.set_data(i, j, temp);
		}
	}

	//clog << "L_gm:" << endl;
	//clog << L.SPB_2_General();

	// Compute \tilde{b}
	for (int i = 0; i < A.n; i++) {
		for (int j = ((i - A.m > 0) ? (i - A.m) : 0); j < i; j++) {
			b[i] -= L.get_data(i, j) * b[j] / L.get_data(j, j);
		}
	}

	//clog << "b_tilde:" << endl;
	//clog << b << endl;

	// Compute solution vector
	sol.resize(A.n);
	for (int i = A.n - 1; i >= 0; i--) {
		sol[i] = b[i];
		for (int j = i + 1; j <= ((i + A.m) >= A.n ? A.n - 1: i + A.m); j++) {
			sol[i] -= L.get_data(j, i) * sol[j];
		}
		sol[i] /= L.get_data(i, i);
	}
	return;
}

#endif // !SPB_MATRIX
