#include "Matrix.h"
#include "SetOfEquations.h"
#include "JacobiSolver.h"
#include "GaussSeidelSolver.h"
#include "LUfactorizationSolver.h"

constexpr int f = 3;
constexpr int e = 3;
constexpr int c = 5;
constexpr int d = 0;
constexpr int N = 900 + c *10 + d;

Matrix<double>* prepareExampleMatrix_A(double a1, double a2, double a3)
{
    Matrix<double>* A = new Matrix<double>(N, N, 0);
    A->setDiagonal(a1, 0);
    A->setDiagonal(a2, 1);
    A->setDiagonal(a2, -1);
    A->setDiagonal(a3, 2);
    A->setDiagonal(a3, -2);
	return A;
}

Matrix<double>* prepareExampleMatrix_B()
{
    auto b = new Matrix<double>(N, 1, 0);
    auto bRawData = b->getRawData();
    for (int i = 0; i < N; i++)
        bRawData[i][0] = sin(i * (f + 1));

    return b;
}


void exercise_A() 
{
    auto A = prepareExampleMatrix_A(5 + e, -1, -1);
    auto b = prepareExampleMatrix_B();
    
    delete A;
    delete b;
}


void exercise_B()
{
    auto A = prepareExampleMatrix_A(5 + e, -1, -1);
    auto b = prepareExampleMatrix_B();

    auto equations = SetOfEquations<double>(A, b);

    EquationsSolver<double>* solver;

    std::cout << "Running Jacobi solver for exercise B" << std::endl;
    solver = new JacobiSolver<double>(&equations);
    solver->solve();
    delete solver;

    std::cout << std::endl;
    equations.resetX();

    std::cout << "Running Gauss-Seidel solver for exercise B" << std::endl;
    solver = new GaussSeidelSolver<double>(&equations);
    solver->solve();
    delete solver;
    
    std::cout << std::endl << std::endl;

    delete A;
    delete b;
}


void exercise_C()
{
    auto A = prepareExampleMatrix_A(3, -1, -1);
    auto b = prepareExampleMatrix_B();

    auto equations = SetOfEquations<double>(A, b);

    EquationsSolver<double>* solver;

    std::cout << "Running Jacobi solver for exercise C" << std::endl;
    solver = new JacobiSolver<double>(&equations);
    solver->solve();
    delete solver;

    std::cout << std::endl;
    equations.resetX();

    std::cout << "Running Gauss-Seidel solver for exercise C" << std::endl;
    solver = new GaussSeidelSolver<double>(&equations);
    solver->solve();
    delete solver;

    std::cout << std::endl << std::endl;

    delete A;
    delete b;
}


void exercise_D()
{
    auto A = prepareExampleMatrix_A(3, -1, -1);
    auto b = prepareExampleMatrix_B();

    auto equations = SetOfEquations<double>(A, b);

    EquationsSolver<double>* solver;

    std::cout << "Running LU factorization solver for exercise D" << std::endl;
    solver = new LUfactorizationSolver<double>(&equations);
    solver->solve();
    delete solver;

    std::cout << std::endl << std::endl;

    delete A;
    delete b;
}


void exercise_E()
{

}


int main()
{
    //exercise_A();
    //exercise_B();
    //exercise_C();
    exercise_D();
    //exercise_E();
}