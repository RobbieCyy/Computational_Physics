#include <iostream>

using namespace std;

// Convert by definition (IEEE 754)
// Subnormal numbers are NOT considered
char * double_2_ieee_method_1(double x) {
	char * result = new char[64];
	int exponent = 1023;

	memset(result, '0', 64);

	// Special case: x=0
	if (x == 0) {
		return result;
	}

	// Determine sign bit
	if (x < 0) {
		result[0] = '1';
		x = -x;
	}

	// Determine exponent
	if (x >= 2) {
		while (x >= 2) {
			x /= 2;
			exponent++;
		}
	}
	else {
		if (x < 1) {
			while (x < 1) {
				x *= 2;
				exponent--;
			}
		}
	}
	for (int i = 11; exponent > 0; i--, exponent >>= 1) {
		result[i] = char('0' + (exponent & 1));
	}

	// Determine significant digits
	// Since subnormal numbers are NOT considered, at this moment, x must lies in [1,2).
	x--;
	for (int i = 12; x > 0; i++, x--) {
		x *= 2;
		result[i] = x >= 1 ? '1' : '0';
	}

	return result;
}

// Convert by definition (IEEE 754)
double ieee_2_double_method_1(char * s) {
	double result = 0;
	return result;
}

char * double_2_ieee_method_2(double x) {
	char * result = new char[64];
	return result;
}

double ieee_2_double_method_2(char * s) {
	return -1;
}

inline void stringout(char * s, int n) {
	for (int i = 0; i < n; i++) {
		cout << s[i];
	}
	cout << endl;
}

int main() {
	char * ans = new char[64];
	for (int i = 0; i < 64; i++) {
		cout << (i + 1) % 10;
	}
	cout << endl;
	ans = double_2_ieee_method_1(0);
	stringout(ans, 64);
	ans = double_2_ieee_method_1(1);
	stringout(ans, 64);
	ans = double_2_ieee_method_1(-1);
	stringout(ans, 64);
	ans = double_2_ieee_method_1(-213142.3215);
	stringout(ans, 64);
	ans = double_2_ieee_method_1(213142.3215);
	stringout(ans, 64);
	ans = double_2_ieee_method_1(0.24256745);
	stringout(ans, 64);
	ans = double_2_ieee_method_1(-0.24256745);
	stringout(ans, 64);
	system("pause");
	return 0;
}