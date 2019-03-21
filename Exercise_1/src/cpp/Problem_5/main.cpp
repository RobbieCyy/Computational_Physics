#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "SPB_Matrix.h"

using namespace std;

/*
================================================================================
Program Description
--------------------------------------------------------------------------------
Two classes are defined for later use:
1. class SPB_Matrix:
	Symmetric Positive-definite Band-like matrix.
2. class General_matrix:
	Matrix restoring all elements.
For definition of member functions, see corresponding header files.

This program contains the following functions:
1. Example_matrix_generator(n, A):
	Generate matrix A, restored in A
2. Example_b_generator(n, b):
	Generate vector b, restored in b
3. Show_example(n, A, b):
	Generate a n * n A matrix, and n * 1 b vector, solve the equations, and 
	print the solution into 'log.txt'.
================================================================================
*/

void Example_matrix_generator(int n, SPB_Matrix & A) {
	A.resize(n, 2);
	A.set_data(0, 0, 5);
	A.set_data(n - 1, n - 1, 5);
	for (int i = 1; i < n - 1; i++) {
		A.set_data(i, i, 6);
	}
	for (int i = 1; i < n; i++) {
		A.set_data(i, i - 1, 4);
	}
	for (int i = 2; i < n; i++) {
		A.set_data(i, i - 2, 1);
	}
	return;
}

void Example_b_generator(int n, vector<double> & b) {
	b.clear();
	b.resize(n, 120);
	b[0] = b[n - 1] = 60;
	return;
}

void Show_example(int n, SPB_Matrix & A, vector<double> & b) {
	vector<double> sol;
	Example_matrix_generator(n, A);
	Example_b_generator(n, b);
	clog << "----------------------------------------" << endl;
	cout << "----------------------------------------" << endl;
	clog << "n = " << n << endl;
	cout << "Example case n = " << n << endl;
	//clog << "A:" << endl;
	//clog << A.SPB_2_General();
	//cout << "The matrix A is:" << endl;
	//cout << A.SPB_2_General();
	//cout << "The vector b is:" << endl;
	//clog << "b:" << endl;
	//clog << b << endl;
	//cout << b << endl;
	Solve_SPB(A, b, sol);
	//cout << "Solution:" << endl;
	clog << "Solution vector:" << endl;
	clog << sol << endl;
	//cout << sol << endl;
	clog << "----------------------------------------" << endl;
	cout << "----------------------------------------" << endl;
	return;
}

int main() {
	SPB_Matrix A;
	vector<double> b;
	ofstream log("log.txt");
	clog.rdbuf(log.rdbuf());
	
	Show_example(4, A, b);
	Show_example(10, A, b);
	Show_example(100, A, b);
	Show_example(10000, A, b);

	system("pause");
	return 0;
}