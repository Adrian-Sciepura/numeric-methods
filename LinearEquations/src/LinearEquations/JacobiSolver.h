#ifndef JACOBI_SOLVER_H
#define JACOBI_SOLVER_H

#include "EquationsSolver.h"

template<arithmetic T>
class JacobiSolver : public EquationsSolver<T>
{
private:
	
public:
	JacobiSolver(SetOfEquations<T>* setOfEquations);
	~JacobiSolver();

	virtual SolveLog solve();
};


template<arithmetic T>
JacobiSolver<T>::JacobiSolver(SetOfEquations<T>* setOfEquations) : EquationsSolver<T>(setOfEquations)
{
}

template<arithmetic T>
JacobiSolver<T>::~JacobiSolver()
{
}

template<arithmetic T>
SolveLog JacobiSolver<T>::solve()
{
	T acceptableError = static_cast<T>(0.000000001f);
	T currentError = std::numeric_limits<T>::max();
	
	int maxIterations = 100;
	int currentIteration = 0;

	Matrix<T>* current = this->setOfEquations->getX();
	Matrix<T>* next = new Matrix<T>(*current);

	int size = this->setOfEquations->getA()->getRows();

	T** A = this->setOfEquations->getA()->getRawData();
	T** b = this->setOfEquations->getB()->getRawData();

	this->updateStartTime();

	auto result = SolveLog();

	while (acceptableError < currentError && currentIteration < maxIterations)
	{
		T** currentRawData = current->getRawData();
		T** nextRawData = next->getRawData();
		for (int i = 0; i < size; i++)
		{
			T sum1 = 0;
			T sum2 = 0;

			for (int j = 0; j < i; j++)
				sum1 += A[i][j] * currentRawData[j][0];

			for (int j = i + 1; j < size; j++)
				sum2 += A[i][j] * currentRawData[j][0];

			nextRawData[i][0] = (b[i][0] - sum1 - sum2) / A[i][i];
		}

		Matrix<T>* temp = current;
		current = next;
		next = temp;
		this->setOfEquations->swapX(current);
		currentError = this->setOfEquations->norm();
		result.norms->push_back(currentError);
		currentIteration++;
	}

	this->updateEndTime();
	delete next;
	result.time = this->getExecutionTime();
	result.iterations = currentIteration;

	return result;
}

#endif