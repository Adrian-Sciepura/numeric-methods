#ifndef SET_OF_EQUATIONS_H
#define SET_OF_EQUATIONS_H

#include "Matrix.h"

template<arithmetic T>
class SetOfEquations
{
private:
	Matrix<T>* A;
	Matrix<T>* b;
	Matrix<T>* x;

public:

	SetOfEquations(Matrix<T>* A, Matrix<T>* b);
	~SetOfEquations();

	Matrix<T>* getA();
	Matrix<T>* getB();
	Matrix<T>* getX();

	void swapX(Matrix<T>* newX);
	void resetX();

	Matrix<T> residuum();
	T norm();
};


template<arithmetic T>
SetOfEquations<T>::SetOfEquations(Matrix<T>* A, Matrix<T>* b) : A{ A }, b{ b }
{
	this->x = nullptr;
	resetX();
}

template<arithmetic T>
SetOfEquations<T>::~SetOfEquations()
{
	delete this->x;
}

template<arithmetic T>
Matrix<T>* SetOfEquations<T>::SetOfEquations::getA()
{
	return this->A;
}

template<arithmetic T>
Matrix<T>* SetOfEquations<T>::SetOfEquations::getB()
{
	return this->b;
}

template<arithmetic T>
Matrix<T>* SetOfEquations<T>::getX()
{
	return this->x;
}

template<arithmetic T>
void SetOfEquations<T>::swapX(Matrix<T>* newX)
{
	if (newX->getCols() != x->getCols() || newX->getRows() != x->getRows())
		return;

	this->x = newX;
}

template<arithmetic T>
void SetOfEquations<T>::resetX()
{
	if (this->x != nullptr)
		delete this->x;

	this->x = new Matrix<T>(A->getRows(), 1, 0);
}

template<arithmetic T>
Matrix<T> SetOfEquations<T>::residuum()
{
	Matrix<T> Ax = *(this->A) * *(this->x);
	Ax -= *this->b;
	return Ax;
}

template<arithmetic T>
T SetOfEquations<T>::norm()
{
	T sum = 0;
	Matrix<T> r = this->residuum();
	T** rawMatrix = r.getRawData();

	for (int i = 0; i < r.getRows(); i++)
		sum += rawMatrix[i][0] * rawMatrix[i][0];

	return sqrt(sum);
}

#endif