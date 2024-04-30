#ifndef LU_FACTORIZATION_SOLVER_H
#define LU_FACTORIZATION_SOLVER_H

#include "EquationsSolver.h"


template<arithmetic T>
class LUfactorizationSolver : public EquationsSolver<T>
{
protected:
	Matrix<T>* L;
	Matrix<T>* U;
	Matrix<T>* Y;

	void forwardSubstitution();
	void backwardSubstitution();

public:
	LUfactorizationSolver(SetOfEquations<T>* setOfEquations);
	~LUfactorizationSolver();

	virtual void solve();
};


template<arithmetic T>
void LUfactorizationSolver<T>::forwardSubstitution()
{
	T sum = 0;
	int N = L->getRows();
	auto rawL = L->getRawData();
	auto rawY = Y->getRawData();
	auto rawB = this->setOfEquations->getB()->getRawData();
	
	for (int i = 0; i < N; i++)
	{
		sum = 0;
		for (int j = 0; j < i; j++)
			sum += rawL[i][j] * rawY[j][0];

		rawY[i][0] = (rawB[i][0] - sum) / rawL[i][i];
	}
}

template<arithmetic T>
void LUfactorizationSolver<T>::backwardSubstitution()
{
	T sum = 0;
	int N = U->getRows();
	auto rawU = U->getRawData();
	auto rawY = Y->getRawData();
	auto rawX = this->setOfEquations->getX()->getRawData();


	for (int i = N - 1; i >= 0 ; i--)
	{
		sum = 0;
		for (int j = i + 1; j < N; j++)
			sum += rawU[i][j] * rawX[j][0];

		rawX[i][0] = (rawY[i][0] - sum) / rawU[i][i];
	}
}

template<arithmetic T>
LUfactorizationSolver<T>::LUfactorizationSolver(SetOfEquations<T>* setOfEquations) : EquationsSolver<T>(setOfEquations), U{ nullptr }, L{ nullptr }, Y{ nullptr }
{
}

template<arithmetic T>
LUfactorizationSolver<T>::~LUfactorizationSolver()
{
}

template<arithmetic T>
void LUfactorizationSolver<T>::solve()
{
	int N = this->setOfEquations->getA()->getRows();
	
	this->U = new Matrix<T>(*(this->setOfEquations->getA()));
	this->L = new Matrix<T>(N, N, 0);
	this->Y = new Matrix<T>(N, 1, 0);

	L->setDiagonal(1, 0);

	auto rawU = U->getRawData();
	auto rawL = L->getRawData();


	for (int i = 2; i < N + 1; i++)
	{
		for (int j = 1; j < i; j++)
		{
			rawL[i-1][j-1] = rawU[i-1][j-1] / rawU[j-1][j-1];
			for (int k = 0; k < N; k++)
			{
				rawU[i-1][k] -= rawL[i-1][j-1] * rawU[j-1][k];
			}
		}
	}


	forwardSubstitution();
	backwardSubstitution();

	T norm = this->setOfEquations->norm();
	std::cout << "Error: " << norm << std::endl;


	delete U;
	delete L;
	delete Y;
	this->U = nullptr;
	this->L = nullptr;
	this->Y = nullptr;
}

#endif