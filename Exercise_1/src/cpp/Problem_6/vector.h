#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

template <typename T> class vector {
private:
	int _size;
	T * data;
public:
	static int precision;
	vector();
	vector(int);
	vector(int, T);
	vector(vector<T> &);
	vector(vector<T> &&);
	void resize(int);
	void resize(int, T);
	T * begin();
	inline int size() {
		return _size;
	}
	T & operator [] (int);
	void operator =(vector<T> &);
	void operator = (vector<T> &&);
};

template <typename T> vector<T>::vector() {
	_size = 0;
	data = nullptr;
}

template <typename T> vector<T>::vector(int n) {
	_size = n;
	data = new T[n];
	memset(data, 0, sizeof(T) * n);
}

template <typename T> vector<T>::vector(int n, T value) {
	_size = n;
	data = new T[n];
	for (int i = 0; i < n; i++) {
		data[i] = value;
	}
}

template <typename T> vector<T>::vector(vector<T> & a) {
	_size = a._size;
	data = new T[_size];
	for (int i = 0; i < _size; i++) {
		(data)[i] = a[i];
	}
}

template <typename T> void vector<T>::operator =(vector<T> & a) {
	_size = a._size;
	data = new T[_size];
	for (int i = 0; i < _size; i++) {
		data[i] = a[i];
	}
}

template <typename T> vector<T>::vector(vector<T> && a) {
	_size = a._size;
	data = a.data;
	a.data = nullptr;
}

template <typename T> void vector<T>::operator =(vector<T> && a) {
	_size = a._size;
	data = a.data;
	a.data = nullptr;
}

template <typename T> void vector<T>::resize(int n) {
	delete data;
	_size = n;
	data = new T[n];
	memset(data, 0, sizeof(T) * n);
}

template <typename T> void vector<T>::resize(int n, T value) {
	delete data;
	data = new T[n];
	_size = n;
	for (int i = 0; i < n; i++) {
		data[i] = value;
	}
}

template <typename T> T & vector<T>::operator [](int i) {
	return this->data[i];
}

template <typename T> T * begin() {
	return data;
}

