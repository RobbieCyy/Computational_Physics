#ifndef GENERAL_MATRIX
#define GENERAL_MATRIX

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/*
================================================================================
Program Description
--------------------------------------------------------------------------------
This file defines class General_matrix.
--------------------------------------------------------------------------------
*/


class General_matrix {
private:
	vector<vector<double>> data;		// Elements of the matrix
	int n;								// Size of the matrix
	friend class SPB_Matrix;			// Friend with class SPB_Matrix
public:
	// Constructor, initialize the matrix to a nn * nn matrix.
	General_matrix(int nn = 0) {
		n = nn;
		data.resize(nn);
		for (int i = 0; i < nn; i++) {
			data[i].resize(nn);
		}
	}
	// Operator for the printing of the matrix
	friend ostream & operator << (ostream &, const General_matrix &);
};

// Operator for the printing of the matrix
ostream & operator << (ostream & out, const General_matrix & G_m) {
	for (int i = 0; i < G_m.n; i++) {
		for (int j = 0; j < G_m.n; j++) {
			out << setw(8) << setprecision(4) << G_m.data[i][j];
		}
		out << endl;
	}
	return out;
}

#endif // !GENERAL_MATRIX
