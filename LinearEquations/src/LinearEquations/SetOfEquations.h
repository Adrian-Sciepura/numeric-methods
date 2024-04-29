#ifndef SET_OF_EQUATIONS_H
#define SET_OF_EQUATIONS_H

#include "Matrix.h"
#include "Matrix.cpp"

template<arithmetic T>
class SetOfEquations
{
private:
	Matrix<T>* A;
	Matrix<T>* b;

public:

	SetOfEquations(Matrix<T>* A, Matrix<T>* b);
	~SetOfEquations();

	Matrix<T>* getA();
	Matrix<T>* getB();
};

#endif