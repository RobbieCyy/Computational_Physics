#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Convert by definition (IEEE 754)
// ** Subnormal numbers are NOT considered **
char * double_2_ieee_method_1(double x) {
	char * result = new char[64];
	int exponent = 1023;

	memset(result, '0', 64);

	cout << "Convert " << x << " by method 1:" << endl;

	// Special case: x=0
	// Default: x=positive zero
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
	for (int i = 12; x > 0 && i < 64; i++) {
		x *= 2;
		result[i] = x >= 1 ? '1' : '0';
		if (x >= 1) {
			x--;
		}
	}

	return result;
}

// Convert by definition (IEEE 754)
// ** Subnormal numbers are NOT considered **
double ieee_2_double_method_1(char * s) {
	double result = 1;
	double temp = 1;
	int exponent = 0;

	cout << "Convert back by method 1:" << endl;

	// Determine significant digits
	for (int i = 12;i<64;i++) {
		temp /= 2;
		result += temp * (int(s[i]) - int('0'));
	}

	// Determine exponent
	for (int i = 11; i > 0; i--) {
		exponent += (int(s[i]) - int('0')) * (1 << (11 - i));
	}
	if (exponent == 0) {
		return 0;
	}
	exponent -= 1023;
	if (exponent >= 0) {
		result *= (long long(1)) << exponent;
	}
	else {
		// Special treatment:
		// The draft version was
		// >   result /= (long long(1)) << (-exponent);
		// However, this version somehow caused 'result' to be inf (or -inf) for some very small 'result'
		// Example: s="1001100110011010101010010101111010101110101101011001011010101011"
		// The correct result should be -2.45103e-185.
		// The draft version would give -inf as the result.
		// This bug is fixed through not dividing a huge number (1 << (-exponent)), but dividing 'result' step by step.
		for (; exponent < 0; exponent++) {
			result /= 2;
		}
	}

	// Determine sign
	if (s[0] == '1') {
		result = -result;
	}

	return result;
}

// Convert by explicit type conversion
char * double_2_ieee_method_2(double x) {
	char * result = new char[64];
	long long * byte = (long long *)(&x);	// sizeof(long long)=sizeof(double)=8

	memset(result, '0', 64);
	
	cout << "Convert " << x << " by method 2;" << endl;

	// Fill result fromt the back 'bit' by 'bit'
	for (int i = 63; i >= 0; i--) {
		result[i] = (char)(int('0') + ((*byte) & 1));
		*byte >>= 1;
	}

	return result;
}

// Convert by explicit type conversion
double ieee_2_double_method_2(char * s) {
	long long result = 0;

	cout << "Convert back by method 2:" << endl;

	for (int i = 0; i < 64; i++) {
		result <<= 1;
		result += (int)(s[i]) - (int)'0';
	}

	return *((double *)(&result));
}

// Method for output of cstrings
inline void stringout(char * s, int n) {
	for (int i = 0; i < n; i++) {
		cout << s[i];
	}
	cout << endl;
}

// Method for showcasing the examples
inline void showcase(double x) {
	char * s1, *s2;
	stringout(s1 = double_2_ieee_method_1(x), 64);
	stringout(s2 = double_2_ieee_method_2(x), 64);
	cout << ieee_2_double_method_1(s1) << endl;
	cout << ieee_2_double_method_2(s2) << endl;
}

int main() {
	double x = 0;
	char * s = new char[64];
	// Example from Chapter 1 Lecture note Page 50
	showcase(-222.111);

	// Other examples
	cout << "Try another example. Input the double:" << endl;
	cin >> x;
	showcase(x);

	cout << "Try another example. Input the string:" << endl;
	cin >> s;
	cout << ieee_2_double_method_1(s) << endl;
	cout << ieee_2_double_method_2(s) << endl;
	system("pause");
	return 0;
}