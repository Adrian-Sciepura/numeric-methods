#ifndef EQUATIONS_SOLVER_H
#define EQUATIONS_SOLVER_H

#include "SetOfEquations.h"
#include "Matrix.h"

template<arithmetic T>
class EquationsSolver
{
private:
	SetOfEquations<T>* setOfEquations;

public:
	EquationsSolver(SetOfEquations<T>* setOfEquations);
	
	virtual Matrix<T>* solve() = 0;
};

#endif