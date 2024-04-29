#ifndef EQUATIONS_SOLVER_H
#define EQUATIONS_SOLVER_H

#include "SetOfEquations.h"
#include "Matrix.h"

template<arithmetic T>
class EquationsSolver
{
protected:
	SetOfEquations<T>* setOfEquations;

public:
	EquationsSolver(SetOfEquations<T>* setOfEquations);
	
	virtual void solve() = 0;
};


template<arithmetic T>
EquationsSolver<T>::EquationsSolver(SetOfEquations<T>* setOfEquations)
{
	this->setOfEquations = setOfEquations;
}

#endif