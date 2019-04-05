#pragma once
#include "complex.h"
#include <iostream>

long double LaguerreL(int n, int alpha, long double x) {
	long double result = alpha - x + 1, a = 1;
	int t;
	/*
	long double result = 1, temp = 1;
	for (int i = n; i > 0; i--) {
		temp = temp * (alpha + i) / (n + 1 - i);
		result = temp - x * (result / i);
	}
	*/
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return result;
	}
	t = 1;
	while (t < n) {
		double temp;
		temp = result;
		result = ((2 * t + 1 + alpha - x) * result - (t + alpha) * a) / (t + 1);
		a = temp;
		t++;
	}
	return result;
}

complex Y(int l, int m, double theta, double phi) {
	complex result;
	return result;
}
