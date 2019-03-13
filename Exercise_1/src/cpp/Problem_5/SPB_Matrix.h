#ifndef SPB_MATRIX
#define SPB_MATRIX

#include <string>
#include <iostream>
#include <iomanip>
#include "General_matrix.h"

using namespace std;

// SPB_Matrix: Symmetric Positive-definite Band-like Matrix

class SPB_Matrix {
private:
	int n;
	int m;
	vector<vector<double>> data;
public:
	SPB_Matrix(int nn = 0, int mm = 0) {
		n = nn;
		m = mm;
		data.resize(n);
		for (int i = 0; i < n; i++) {
			data[i].resize(m + 1);
		}
	}
	inline int get_m() {
		return m;
	}
	inline int get_n() {
		return n;
	}
	inline double get_data(int i, int j) {
		return i > j ? (j - i + m >= 0 ? data[i][j - i + m] : 0) : (i - j + m >= 0 ? data[j][i - j + m] : 0);
	}
	void set_data(int i, int j, double x) {
		(i < j ? (i - j + m >= 0 ? data[j][i - j + m] : x) : (j - i + m >= 0 ? data[i][j - i + m] : x)) = x;
	}
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
	void resize(int nn = 0, int mm = 0) {
		n = nn;
		m = mm;
		data.resize(n);
		for (int i = 0; i < n; i++) {
			data[i].resize(m + 1);
		}
	}
	friend void Solve_SPB(SPB_Matrix &, vector<double> &, vector<double> &);
};

ostream & operator << (ostream & out, const vector<double> vec) {
	for (int i = 0; i < int(vec.size()); i++) {
		out << setw(16) << setprecision(4) << ((abs(vec[i]) < 0.00001) ? 0 : vec[i]);
	}
	return out;
}

void Solve_SPB(SPB_Matrix & A, vector<double> & b, vector<double> & sol) {
	SPB_Matrix L(A.n, A.m);
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

	for (int i = 0; i < A.n; i++) {
		for (int j = ((i - A.m > 0) ? (i - A.m) : 0); j < i; j++) {
			b[i] -= L.get_data(i, j) * b[j] / L.get_data(j, j);
		}
	}

	//clog << "b_tilde:" << endl;
	//clog << b << endl;

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
