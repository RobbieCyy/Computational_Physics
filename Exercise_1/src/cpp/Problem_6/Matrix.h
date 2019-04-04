#pragma once
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;
class matrix {
private:
	int n, m;
	vector<vector<double>> data;
public:
	static int precision;
	matrix() {
		n = m = 0;
	}
	matrix(int nn = 0, int mm = 0) {
		n = nn;
		m = mm;
		data.resize(n);
		for (int i = 0; i < n; i++) {
			data[i].resize(m, 0);
		}
	}
	matrix(const matrix & A) {
		n = A.n;
		m = A.m;
		data = A.data;
	}
	vector<double> & operator [] (int);
	friend ostream & operator << (ostream &, matrix &);
	friend matrix operator * (matrix &, matrix &);
	friend matrix operator * (double, matrix &);
	friend vector<double> operator * (vector<double> &, matrix &);
	friend vector<double> operator * (matrix &, vector<double> &);
	matrix T();
	friend matrix zeros(int, int);
	friend matrix ones(int, int);
	friend matrix diag(vector<double>);
	vector<double> diag();
};

// Default precision of output
int matrix::precision = 8;

// Operator [] for modify/get the data
vector<double> & matrix::operator [](int index) {
	return this->data[index];
}

// Output matrix
ostream & operator << (ostream & out, matrix & A) {
	for (int i = 0; i < A.n; i++) {
		for (int j = 0; j < A.m; j++) {
			out << setw(matrix::precision + 5) << setprecision(matrix::precision);
		}
		out << endl;
	}
	return out;
}

// Output vector
ostream & operator << (ostream & out, vector<double> & x) {
	for (size_t i = 0; i < x.size(); i++) {
		out << setw(matrix::precision + 5) << setprecision(matrix::precision) << x[i] << endl;
	}
	return out;
}

// Matrix multiplication
matrix operator * (matrix & A, matrix & B) {
	matrix result(A.n, B.m);
	if (A.m == B.n) {
		for (int i = 0; i < A.n; i++) {
			for (int j = 0; j < B.m; j++) {
// Parallelization by openmp
#pragma omp for
				for (int k = 0; k < A.n; k++) {
					result.data[i][j] += A.data[i][k] * B.data[k][j];
				}
			}
		}
	}
	return result;
}

// Number times matrix
matrix operator * (double a, matrix & A) {
	matrix result(A);
	for (int i = 0; i < A.n; i++) {
		for (int j = 0; j < A.m; j++) {
			result.data[i][j] *= a;
		}
	}
	return result;
}

// Row vector times matrix
vector<double> operator * (vector<double> & x, matrix & A) {
	vector<double> result;
	result.resize(A.m);
	if (x.size() != A.n) {
		return x;
	}
	for (int i = 0; i < A.m; i++) {
		for (size_t j = 0; j < x.size(); j++) {
			result[i] += x[j] * A.data[j][i];
		}
	}
	return result;
}

// Matrix times column vector
vector<double> operator * (matrix & A, vector<double> & x) {
	vector<double> result;
	result.resize(A.n);
	if (x.size() != A.m) {
		return x;
	}
	for (int i = 0; i < A.n; i++) {
		for (size_t j = 0; j < x.size(); j++) {
			result[i] += A.data[i][j]*x[j];
		}
	}
	return result;
}

// Transpose of matrix
matrix matrix::T(){
	matrix result(m, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			result.data[j][i] = this->data[i][j];
		}
	}
	return result;
}

// Zeros (matrix)
matrix zeros(int n, int m) {
	matrix result(n, m);
	return result;
}

// Zeros (vector)
vector<double> zeros(int n) {
	vector<double> result(n, 0);
	return result;
}

// Ones (matrix)
matrix ones(int n, int m) {
	matrix result(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result.data[i][j] = 1;
		}
	}
	return result;
}

// Ones (vector)
vector<double> ones(int n) {
	vector<double> result(n, 1.0);
	return result;
}

// Diagonal matrix
matrix diag(vector<double> d) {
	matrix result(d.size(), d.size());
	for (int i = 0; i < result.n; i++) {
		result.data[i][i] = d[i];
	}
	return result;
}

// Diagonal elements
vector<double> matrix::diag(){
	vector<double> result((n < m) ? n : m);
	for (size_t i = 0; i < result.size(); i++) {
		result[i] = data[i][i];
	}
	return result;
}

// Vector add
vector<double> operator + (vector<double> & a, vector<double> & b) {
	vector<double> result(a.size());
	if (a.size() != b.size()) {
		return a;
	}
	for (size_t i = 0; i < result.size(); i++) {
		result[i] = a[i] + b[i];
	}
	return result;
}

// Vector minus
vector<double> operator - (vector<double> & a, vector<double> & b) {
	vector<double> result(a.size());
	if (a.size() != b.size()) {
		return a;
	}
	for (size_t i = 0; i < result.size(); i++) {
		result[i] = a[i] - b[i];
	}
	return result;
}

// Number times vector
vector<double> operator * (double k, vector<double> & a) {
	vector<double> result(a.size());
	for (size_t i = 0; i < a.size(); i++) {
		result[i] = k * (a[i]);
	}
	return result;
}

// Vector inner product
double operator * (vector<double> & a, vector<double> & b) {
	double result = 0;
	if (a.size() != b.size()) {
		return 0;
	}
	for (size_t i = 0; i < a.size(); i++) {
		result += a[i] * b[i];
	}
	return result;
}

// Vector norm
 double norm(vector<double> & a) {
	return sqrt(a * a);
}