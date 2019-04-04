#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

double a, b, tau_a, tau_b, t, delta;

double a_prev;
double b_prev;
ofstream out("result.txt");

// The core of the ODE solver, where magic happens (lol)
void solve_core() {
// Method 1
// Naive iteration
/*
	a -= delta * a_prev / tau_a;
	b += delta * (a_prev / tau_a - b_prev / tau_b);
*/
// Method 2
// Naive iteration for a, a small correction for b 
/*
	a -= delta * a_prev / tau_a;
	b += delta * ((a_prev + a) / (2 * tau_a) - b_prev / tau_b);
*/
// Method 3
// RK4 for a, no correction for b
/*
	double k[4];
	k[0] = - delta * a_prev / tau_a;
	k[1] = - delta * (a_prev + k[0] / 2) / tau_a;
	k[2] = - delta * (a_prev + k[1] / 2) / tau_a;
	k[3] = - delta * (a_prev + k[2]) / tau_a;
	a += (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
	b += delta * ((a_prev + a) / (2 * tau_a) - b_prev / tau_b);
*/
// Method 4
// RK4 for a, after that, RK4 for b

	double k[4];
	k[0] = -delta * a_prev / tau_a;
	k[1] = -delta * (a_prev + k[0] / 2) / tau_a;
	k[2] = -delta * (a_prev + k[1] / 2) / tau_a;
	k[3] = -delta * (a_prev + k[2]) / tau_a;
	a += (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
	
	k[0] = delta * (a_prev / tau_a - b_prev / tau_b);
	k[1] = delta * ((a_prev + a) / (2 * tau_a) - (b_prev + k[0] / 2) / tau_b); // Explicit time dependent in N_A, linear intrapolate
	k[2] = delta * ((a_prev + a) / (2 * tau_a) - (b_prev + k[1] / 2) / tau_b); // Explicit time dependent in N_A, linear intrapolate
	k[3] = delta * (a / tau_a - (b_prev + k[2]) / tau_b);
	b += (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;

}

// The outer wrapper of the ODE solver
void solver() {
	double t_now = 0;
	int n = 0;
	// Get the parameters
	cin >> t;
	cin >> delta;
	// Print parameters into the output file
	out << "a = " << setw(16) << setprecision(4) << a << endl;
	out << "b = " << setw(16) << setprecision(4) << b << endl;
	out << "tau_a = " << setw(16) << setprecision(4) << tau_a << endl;
	out << "tau_b = " << setw(16) << setprecision(4) << tau_b << endl;
	out << "t = " << setw(16) << setprecision(4) << t << endl;
	out << "delta = " << setw(16) << setprecision(4) << delta << endl;
	// In actual implementation, it suffices to restore only the results of this iteration and the previes iteration
	a_prev = a;
	b_prev = b;
	// Iteration
	while (t_now <= t) {
		n++;
		out << setw(16) << setprecision(4) << t_now << setw(16) << setprecision(4) << a << setw(16) << setprecision(4) << b << endl;
		// Different methods vary here.
		solve_core();
		t_now += delta;
		// Update the results
		a_prev = a;
		b_prev = b;
	}
	out << setw(16) << setprecision(6) << t_now << setw(16) << setprecision(4) << a << setw(16) << setprecision(4) << b << endl;
	// Linear intrapolate for the result, if t is not a multiple of Delta t 
	a = ((t - t_now) / delta + 1) * (a - a_prev) + a;
	b = ((t - t_now) / delta + 1) * (b - b_prev) + b;
}

int main() {
	a = b = 1;
	cout << "Input the parameters in the following order: tau_a, tau_b, t, Delta t" << endl;
	cin >> tau_a >> tau_b;
	// Solve the ODE
	solver();
	cout << setw(16) << setprecision(4) << a << setw(16) << setprecision(4) << b << endl;
	getchar();
	getchar();
	return 0;
}