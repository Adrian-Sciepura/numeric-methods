#include "EquationsSolver.h"

template<arithmetic T>
EquationsSolver<T>::EquationsSolver(SetOfEquations<T>* setOfEquations)
{
	this->setOfEquations = setOfEquations;
}
