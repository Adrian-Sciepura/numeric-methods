#ifndef EQUATIONS_SOLVER_H
#define EQUATIONS_SOLVER_H

#include <chrono>
#include "SetOfEquations.h"
#include "Matrix.h"
#include "SolveLog.h"

template<arithmetic T>
class EquationsSolver
{
private:
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;

protected:
	SetOfEquations<T>* setOfEquations;

	void updateStartTime();
	void updateEndTime();

public:
	EquationsSolver(SetOfEquations<T>* setOfEquations);
	
	virtual SolveLog solve() = 0;
	double getExecutionTime();
};


template<arithmetic T>
void EquationsSolver<T>::updateStartTime()
{
	startTime = std::chrono::high_resolution_clock::now();
}

template<arithmetic T>
void EquationsSolver<T>::updateEndTime()
{
	endTime = std::chrono::high_resolution_clock::now();
}

template<arithmetic T>
EquationsSolver<T>::EquationsSolver(SetOfEquations<T>* setOfEquations)
{
	this->setOfEquations = setOfEquations;
}

template<arithmetic T>
double EquationsSolver<T>::getExecutionTime()
{
	std::chrono::duration<double> elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
	return elapsedTime.count();
}

#endif