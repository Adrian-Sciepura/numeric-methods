#ifndef GAUSS_SEIDEL_SOLVER_H
#define GAUSS_SEIDEL_SOLVER_H

#include "EquationsSolver.h"

template<arithmetic T>
class GaussSeidelSolver : public EquationsSolver<T>
{
private:

public:
	GaussSeidelSolver(SetOfEquations<T>* setOfEquations);
	~GaussSeidelSolver();

	virtual SolveLog solve();
};


template<arithmetic T>
GaussSeidelSolver<T>::GaussSeidelSolver(SetOfEquations<T>* setOfEquations) : EquationsSolver<T>(setOfEquations)
{
}

template<arithmetic T>
GaussSeidelSolver<T>::~GaussSeidelSolver()
{
}

template<arithmetic T>
SolveLog GaussSeidelSolver<T>::solve()
{
	T acceptableError = static_cast<T>(0.000000001f);
	T currentError = std::numeric_limits<T>::max();

	int maxIterations = 100;
	int currentIteration = 0;

	Matrix<T>* current = this->setOfEquations->getX();

	int size = this->setOfEquations->getA()->getRows();

	T** A = this->setOfEquations->getA()->getRawData();
	T** b = this->setOfEquations->getB()->getRawData();
	T** currentRawData = current->getRawData();

	this->updateStartTime();

	auto result = SolveLog();

	while (acceptableError < currentError && currentIteration < maxIterations)
	{
		for (int i = 0; i < size; i++)
		{
			T sum1 = 0;
			T sum2 = 0;

			for (int j = 0; j < i; j++)
				sum1 += A[i][j] * currentRawData[j][0];

			for (int j = i + 1; j < size; j++)
				sum2 += A[i][j] * currentRawData[j][0];

			currentRawData[i][0] = (b[i][0] - sum1 - sum2) / A[i][i];
		}

		currentError = this->setOfEquations->norm();
		result.norms->push_back(currentError);
		currentIteration++;
	}

	this->updateEndTime();
	result.time = this->getExecutionTime();
	result.iterations = currentIteration;

	return result;
}

#endif