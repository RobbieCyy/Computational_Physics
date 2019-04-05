#pragma once
#include <cmath>
#include <iostream>
#include <iomanip>
#define real_plus_i_imag true
#define norm_times_phase false
#define pi 3.1415926535897932
class complex {
private:
	long double _real;
	long double _imag;
	long double _norm;
	long double _arg;
	// Private member functions for converting x+iy to r*exp(arg)
	inline long double get_real();
	inline long double get_imag();
	inline long double get_norm();
	inline long double get_arg();
public:
	// Constants: 0, i
	const static complex zero;
	const static complex i_unit;
	static bool display_style;
	static int precision;

	// Constructors and assignment operators (No need for destructors)
	complex();
	complex(long double);
	complex(long double, long double, bool = real_plus_i_imag);
	complex(const complex &);
	complex(complex &&);
	complex & operator = (const complex &);
	complex & operator = (complex &&);

	// Other operators
	complex operator + (const complex &) const;
	complex operator + (long double) const;
	complex operator - (const complex &) const;
	complex operator - (long double) const;
	complex operator - () const;
	complex operator * (const complex &) const;
	complex operator * (long double) const;
	complex operator / (const complex &) const;
	complex operator / (long double) const;
	complex operator ^ (const complex &) const;
	complex operator ^ (long double) const;
	complex & operator += (const complex &);
	complex & operator += (long double);
	complex & operator -= (const complex &);
	complex & operator -= (long double);
	complex & operator *= (const complex &);
	complex & operator *= (long double);
	complex & operator /= (const complex &);
	complex & operator /= (long double);
	complex & operator ^= (const complex &);
	complex & operator ^= (long double);
	complex pow(long double, const complex &) const;
	complex conj() const;
	complex exp(const complex &) const;
	friend std::ostream & operator << (std::ostream &, const complex &);

	// Get data
	inline long double norm();
	inline long double arg();
	inline long double real();
	inline long double imag();
};

long double complex::get_real() {
	return this->_norm * cos(this->_arg);
}

long double complex::get_imag() {
	return this->_norm * sin(this->_arg);
}

long double complex::get_norm() {
	return sqrt(this->_real * this->_real + this->_imag * this->_imag);
}

long double complex::get_arg() {
	return acos(this->_real / this->_norm);
}

// Constants
const complex complex::zero(0, 0);

const complex complex::i_unit(0, 1);

bool complex::display_style = real_plus_i_imag;

int complex::precision = 8;

// Constructors and assignment operators (No need for destructors)
complex::complex() {
	_real = _imag = _norm = _arg = 0;
}

complex::complex(long double r) {
	this->_norm = this->_real = r;
	this->_arg = this->_imag = 0;
}

complex::complex(long double a, long double b, bool format) {
	if (format == real_plus_i_imag) {
		_real = a;
		_imag = b;
		_norm = get_norm();
		_arg = get_arg();
	}
	else {
		_norm = a;
		_arg = b;
		_real = get_real();
		_imag = get_imag();
	}
}

complex::complex(const complex & c) {
	this->_norm = c._norm;
	this->_arg = c._arg;
	this->_real = c._real;
	this->_imag = c._imag;
}

complex::complex(complex && c) {
	this->_norm = c._norm;
	this->_arg = c._arg;
	this->_real = c._real;
	this->_imag = c._imag;
}

complex & complex::operator = (const complex & c) {
	this->_norm = c._norm;
	this->_arg = c._arg;
	this->_real = c._real;
	this->_imag = c._imag;
	return (*this);
}

complex & complex::operator = (complex && c) {
	this->_norm = c._norm;
	this->_arg = c._arg;
	this->_real = c._real;
	this->_imag = c._imag;
	return (*this);
}

// Operators
complex complex::operator + (const complex & c) const {
	complex result(this->_real + c._real, this->_imag + c._imag);
	return result;
}

complex complex::operator + (long double r) const {
	complex result(this->_real + r, this->_imag);
	return result;
}

complex complex::operator - (const complex & c) const {
	complex result(this->_real - c._real, this->_imag - c._imag);
	return result;
}

complex complex::operator - (long double r) const {
	complex result(this->_real - r, this->_imag);
	return result;
}

complex complex::operator - () const {
	complex result(-this->_real, -this->_imag);
	return result;
}

complex complex::operator * (const complex & c) const {
	complex result(this->_real * c._real - this->_imag * c._imag, this->_real * c._imag + this->_imag * c._real);
	return result;
}

complex complex::operator * (long double r) const {
	complex result(this->_real * r, this->_imag * r);
	return result;
}

complex complex::operator / (const complex & c) const {
	complex result((this->_real * c._real + this->_imag * c._imag) / (c._norm * c._norm), (this->_imag * c._real - this->_real * c._imag) / (c._norm * c._norm));
	return result;
}

complex complex::operator / (long double r) const {
	complex result(this->_real / r, this->_imag / r);
	return result;
}

complex complex::operator ^ (const complex & b) const {
	complex result;
	result._norm = std::pow(this->_norm, b._real) * std::exp(-b._imag * this->_arg);
	result._arg = this->_arg * b._real + log(this->_norm) * b._imag;
	result._arg -= floor(result._arg / (2 * pi)) * 2 * pi;
	result._real = result.get_real();
	result._imag = result.get_imag();
	return result;
}

complex complex::operator ^ (long double r) const {
	complex result;
	result._norm = std::pow(this->_norm, r);
	result._arg = this->_arg * r;
	result._arg -= floor(result._arg / (2 * pi)) * 2 * pi;
	result._real = result.get_real();
	result._imag = result.get_imag();
	return result;
}

complex & complex::operator += (const complex & c) {
	this->_real += c._real;
	this->_imag += c._imag;
	this->_norm = get_norm();
	this->_arg = get_arg();
	return (*this);
}

complex & complex::operator += (long double r) {
	this->_real += r;
	this->_norm = get_norm();
	this->_arg = get_arg();
	return (*this);
}

complex & complex::operator -= (const complex & c) {
	this->_real -= c._real;
	this->_imag -= c._imag;
	this->_norm = get_norm();
	this->_arg = get_arg();
	return (*this);
}

complex & complex::operator -= (long double r) {
	this->_real -= r;
	this->_norm = get_norm();
	this->_arg = get_arg();
	return (*this);
}

complex & complex::operator *= (const complex & c) {
	this->_real = this->_real * c._real - this->_imag * c._imag;
	this->_imag = this->_real * c._imag + this->_imag * c._real;
	this->_norm *= c._norm;
	this->_arg += c._arg;
	if (this->_arg > 2 * pi) {
		this->_arg -= 2 * pi;
	}
	if (this->_arg < 0) {
		this->_arg += 2 * pi;
	}
	return (*this);
}

complex & complex::operator *= (long double r) {
	this->_real *= r;
	this->_imag *= r;
	this->_norm *= r;
	return (*this);
}

complex & complex::operator /= (const complex & c) {
	this->_real -= (this->_real * c._real + this->_imag * c._imag) / (c._norm * c._norm);
	this->_imag -= (this->_imag * c._real - this->_real * c._imag) / (c._norm * c._norm);
	this->_norm /= c._norm;
	this->_arg -= c._arg;
	if (this->_arg > 2 * pi) {
		this->_arg -= 2 * pi;
	}
	if (this->_arg < 0) {
		this->_arg += 2 * pi;
	}
	return (*this);
}

complex & complex::operator /= (long double r) {
	this->_real /= r;
	this->_imag /= r;
	this->_norm /= r;
	return (*this);
}

complex & complex::operator ^= (const complex & c) {
	long double old_norm = this->_norm, old_arg = this->_arg;
	this->_norm = std::pow(old_norm, c._real) * std::exp(-c._imag * old_arg);
	this->_arg = old_arg * c._real + log(old_norm) * c._imag;
	this->_arg -= floor(this->_arg / (2 * pi)) * 2 * pi;
	this->_real = this->get_real();
	this->_imag = this->get_imag();
	return (*this);
}

complex & complex::operator ^= (long double r) {
	this->_norm = std::pow(this->_norm, r);
	this->_arg = this->_arg * r;
	this->_arg -= floor(this->_arg / (2 * pi)) * 2 * pi;
	this->_real = this->get_real();
	this->_imag = this->get_imag();
	return (*this);
}

complex complex::pow(long double r, const complex & a) const {
	complex result;
	result._norm = std::pow(r, a._real);
	result._arg = a._imag * log(r);
	result._arg -= floor(result._arg / (2 * pi)) * 2 * pi;
	result._real = result.get_real();
	result._imag = result.get_imag();
	return result;
}

complex complex::conj() const {
	complex result = *this;
	result._imag *= -1;
	if (result._arg > 1e-5) {
		result._arg = 2 * pi - result._arg;
	}
	else {
		if (result._imag < 0) {
			result._arg = 2 * pi - result._arg;
		}
	}
	return result;
}

complex complex::exp(const complex & a) const{
	complex result(std::exp(a._real), this->_imag, norm_times_phase);
	return result;
}

std::ostream & operator << (std::ostream & out, const complex & a) {
	if (complex::display_style == real_plus_i_imag) {
		out << std::setw(complex::precision + 5) << std::setprecision(complex::precision) << a._real;
		out << " + ";
		out << std::setw(complex::precision + 5) << std::setprecision(complex::precision) << a._imag;
		out << " i";
	}
	else {
		out << std::setw(complex::precision + 5) << std::setprecision(complex::precision) << a._norm;
		out << " * exp(";
		out << std::setw(complex::precision + 5) << std::setprecision(complex::precision) << a._arg;
		out << ")";
	}
	return out;
}

long double complex::real() {
	return this->_real;
}

long double complex::imag() {
	return this->_imag;
}

long double complex::norm() {
	return this->_norm;
}

long double complex::arg() {
	return this->_arg;
}