#include "Matrix.h"

template<arithmetic T>
Matrix<T>::Matrix(int rows, int cols) : rows {rows}, cols {cols}
{
	this->matrix = new T*[rows];

	for (int i = 0; i < rows; i++) 
	{
		this->matrix[i] = new T[cols];
	}
}

template<arithmetic T>
Matrix<T>::Matrix(int rows, int cols, T startValue) : Matrix(rows, cols)
{
	this->fill(startValue);
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

	int offsetSign = (offset > 0) - (offset < 0);

	int x = 0;
	int y = 0;

	for (int i = 0; i < this->rows; i++)
	{
		x = i + offset;
		y = i - offset + offsetSign;

		if (x >= 0 && x < this->cols && y >= 0 && y < this->rows)
			this->matrix[y][x] = newValue;
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
