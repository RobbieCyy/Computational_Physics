#ifndef SPB_MATRIX
#define SPB_MATRIX

#include <string>
#include <iostream>
#include <iomanip>
#define MAX_N 500
#define MAX_M 500

using namespace std;

class SPB_Matrix {
private:
	int n;
	int m;
	int data[MAX_N][MAX_M + 1];
	inline int get_data(int i, int j) {
		return i < j ? data[j][i - j + m + 1] : data[i][j - i + m + 1];
	}
public:
	SPB_Matrix() {
		n = m = 0;
	}
	inline void SPB_2_General() {
		cout << "The matrix is as following:" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << setw(8) << get_data(i, j);
			}
			cout << endl;
		}
	}

};

#endif // !SPB_MATRIX
