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
	Matrix(const Matrix& other);
	~Matrix();

	void setDiagonal(T newValue, int offset);
	void fill(T newValue);

	void print();
	
	T** getRawData();
	int getRows();
	int getCols();

	//friend Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b);
	
	Matrix<T> operator*(const Matrix<T>& other);
	Matrix<T> operator+(const Matrix<T>& other);
	Matrix<T> operator-(const Matrix<T>& other);
	Matrix<T>& operator-=(const Matrix<T>& other);
	Matrix<T>& operator+=(const Matrix<T>& other);
};


template<arithmetic T>
Matrix<T>::Matrix(int rows, int cols) : rows{ rows }, cols{ cols }
{
	this->matrix = new T * [rows];

	for (int i = 0; i < rows; i++)
		this->matrix[i] = new T[cols];
}

template<arithmetic T>
Matrix<T>::Matrix(int rows, int cols, T startValue) : Matrix(rows, cols)
{
	this->fill(startValue);
}

template<arithmetic T>
Matrix<T>::Matrix(const Matrix& other) : Matrix<T>(other.rows, other.cols)
{
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->matrix[i][j] = other.matrix[i][j];
}

template<arithmetic T>
Matrix<T>::~Matrix()
{
	if (this->matrix != nullptr)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] this->matrix[i];
		}

		delete[] this->matrix;
	}
}


template<arithmetic T>
void Matrix<T>::setDiagonal(T newValue, int offset)
{
	if (this->cols != this->rows)
		return;

	int x = offset > 0 ? offset : 0;
	int y = offset > 0 ? 0 : -offset;
	int iters = this->rows - abs(offset);

	for (int i = 0; i < iters; i++)
	{
		this->matrix[y][x] = newValue;

		x++;
		y++;
	}
}

template<arithmetic T>
void Matrix<T>::fill(T newValue)
{
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->matrix[i][j] = newValue;
}

template<arithmetic T>
void Matrix<T>::print()
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			std::cout << this->matrix[i][j] << ' ';
		}

		std::cout << std::endl;
	}
}

template<arithmetic T>
T** Matrix<T>::getRawData()
{
	return this->matrix;
}

template<arithmetic T>
int Matrix<T>::getRows()
{
	return this->rows;
}

template<arithmetic T>
int Matrix<T>::getCols()
{
	return this->cols;
}

template<arithmetic T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
	if (this->cols != other.rows)
		return Matrix<T>(0, 0, 0);

	Matrix<T> result(this->rows, other.cols, 0);

	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < other.cols; j++)
			for (int k = 0; k < this->cols; k++)
				result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];

	return result;
}

template<arithmetic T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)
{
	Matrix<T> result(this->rows, this->cols, 0);

	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];

	return result;
}

template<arithmetic T>
inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)
{
	Matrix<T> result(this->rows, this->cols, 0);

	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			result.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];

	return result;
}

template<arithmetic T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->matrix[i][j] -= other.matrix[i][j];

	return *this;
}

template<arithmetic T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->matrix[i][j] += other.matrix[i][j];

	return *this;
}

//template<arithmetic T>
//Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b)
//{
//	if (a.cols != b.rows)
//		return Matrix<T>(0, 0);
//
//	Matrix<T> result(a.rows, b.cols);
//
//	for (int i = 0; i < a.rows; i++)
//		for (int j = 0; j < b.cols; j++)
//			for (int k = 0; k < a.cols; k++)
//				result.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
//
//	return result;
//}

#endif