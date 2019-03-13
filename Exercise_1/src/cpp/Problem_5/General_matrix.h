#ifndef GENERAL_MATRIX
#define GENERAL_MATRIX

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class General_matrix {
private:
	vector<vector<double>> data;
	int n;
	friend class SPB_Matrix;
public:
	General_matrix(int nn = 0) {
		n = nn;
		data.resize(nn);
		for (int i = 0; i < nn; i++) {
			data[i].resize(nn);
		}
	}
	friend ostream & operator << (ostream &, const General_matrix &);
};

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
