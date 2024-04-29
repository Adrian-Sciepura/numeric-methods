#include "SetOfEquations.h"

template<arithmetic T>
SetOfEquations<T>::SetOfEquations(Matrix<T>* A, Matrix<T>* b) : A {A}, b{b}
{
}

template<arithmetic T>
SetOfEquations<T>::~SetOfEquations()
{
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