#pragma once
#include "vector.h"
#include <iostream>
#include <iomanip>

using namespace std;

class matrix {
private:
	int n, m;
	double * data;
public:
	static int precision;
	matrix() {
		//clog << "Default construct" << endl;
		n = m = 0;
	}
	matrix(int nn, int mm) {
		//clog << "Size specified construct" << endl;
		n = nn;
		m = mm;
		data = new double[n * m];
		for (int i = 0; i < n * m; i++) {
			data[i] = 0;
		}
	}
	matrix(const matrix & A) {
		//clog << "Copy construct" << endl;
		n = A.n;
		m = A.m;
		data = new double[n * m];
		memcpy(data, A.data, n * m * sizeof(double));
	}
	matrix(matrix && A) {
		//clog << "Move construct" << endl;
		n = A.n;
		m = A.m;
		data = A.data;
		A.data = nullptr;
	}
	~matrix() {
		//clog << "Destruct" << endl;
		delete[] data;
	}
	double * operator [] (int);
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
double * matrix::operator [](int index) {
	return this->data + index * n;
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

// Matrix multiplication
matrix operator * (matrix & A, matrix & B) {
	matrix result(A.n, B.m);
	if (A.m == B.n) {
		for (int i = 0; i < A.n; i++) {
			for (int j = 0; j < B.m; j++) {
				for (int k = 0; k < A.n; k++) {
					result[i][j] += A[i][k] * B[k][j];
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
			result[i][j] *= a;
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
		for (int j = 0; j < A.n; j++) {
			result[i] += x[j] * A[j][i];
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
		for (int j = 0; j < A.m; j++) {
			result[i] += A[i][j] * x[j];
		}
	}
	return result;
}

// Transpose of matrix
matrix matrix::T(){
	matrix result(m, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			result[j][i] = (*this)[i][j];
		}
	}
	return result;
}

// Zeros (matrix)
matrix zeros(int n, int m) {
	matrix result(n, m);
	return result;
}

// Ones (matrix)
matrix ones(int n, int m) {
	matrix result(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result[i][j] = 1;
		}
	}
	return result;
}

// Diagonal matrix
matrix diag(vector<double> d) {
	matrix result(d.size(), d.size());
	for (int i = 0; i < result.n; i++) {
		result[i][i] = d[i];
	}
	return result;
}

// Diagonal elements
vector<double> matrix::diag(){
	vector<double> result((n < m) ? n : m);
	for (int i = 0; i < result.size(); i++) {
		result[i] = (*this)[i][i];
	}
	return result;
}

// Output vector
ostream & operator << (ostream & out, vector<double> & x) {
	for (size_t i = 0; i < x.size(); i++) {
		out << setw(matrix::precision + 5) << setprecision(matrix::precision) << x[i] << endl;
	}
	return out;
}

// Zeros (vector)
vector<double> zeros(int n) {
	vector<double> result(n, 0);
	return result;
}

// Ones (vector)
vector<double> ones(int n) {
	vector<double> result(n, 1.0);
	return result;
}

// Vector add
vector<double> operator + (vector<double> & a, vector<double> & b) {
	vector<double> result(a.size());
	if (a.size() != b.size()) {
		return a;
	}
	for (int i = 0; i < result.size(); i++) {
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
	for (int i = 0; i < result.size(); i++) {
		result[i] = a[i] - b[i];
	}
	return result;
}

// Number times vector
vector<double> operator * (double k, vector<double> & a) {
	vector<double> result(a.size());
	for (int i = 0; i < a.size(); i++) {
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
	for (int i = 0; i < a.size(); i++) {
		result += a[i] * b[i];
	}
	return result;
}

// Vector norm
inline double norm(vector<double> & a) {
	return sqrt(a * a);
}