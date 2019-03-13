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

================================================================================
*/

void Example_matrix_generator(int n, SPB_Matrix & result) {
	result.resize(n, 2);
	result.set_data(0, 0, 5);
	result.set_data(n - 1, n - 1, 5);
	for (int i = 1; i < n - 1; i++) {
		result.set_data(i, i, 6);
	}
	for (int i = 1; i < n; i++) {
		result.set_data(i, i - 1, 4);
	}
	for (int i = 2; i < n; i++) {
		result.set_data(i, i - 2, 1);
	}
	return;
}

void Example_b_generator(int n, vector<double> & result) {
	result.resize(n, 120);
	result[0] = result[n - 1] = 60;
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
	
	//Show_example(4, A, b);
	//Show_example(100, A, b);
	Show_example(10000, A, b);

	system("pause");
	return 0;
}