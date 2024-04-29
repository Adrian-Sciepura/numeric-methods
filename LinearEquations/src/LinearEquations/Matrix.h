#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template <typename T>
concept arithmetic = std::is_arithmetic<T>::value;

template <arithmetic T>
class Matrix
{
private:
	int rows;
	int cols;
	T** matrix;

public:

	Matrix(int rows, int cols);
	Matrix(int rows, int cols, T startValue);
	~Matrix();

	void setDiagonal(T newValue, int offset);
	void fill(T newValue);

	void print();
	
	T** getRawData();
	int getRows();
	int getCols();
};

#endif