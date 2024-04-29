#include "Matrix.h"
#include "SetOfEquations.h"
#include "JacobiSolver.h"
#include "GaussSeidelSolver.h"

constexpr int f = 3;
constexpr int e = 3;
constexpr int c = 5;
constexpr int d = 0;
constexpr int N = 900 + c *10 + d;

Matrix<double>* getExerciseAMatrix()
{
    Matrix<double>* A = new Matrix<double>(N, N, 0);
    A->setDiagonal(5 + e, 0);
    A->setDiagonal(-1, 1);
    A->setDiagonal(-1, 2);
    A->setDiagonal(-1, -1);
    A->setDiagonal(-1, -2);
	return A;
}


void exercise_A() 
{
    auto A = getExerciseAMatrix();

    auto b = new Matrix<double>(N, 1, 0);
    double** bRawData = b->getRawData();
    for (int i = 0; i < N; i++)
        bRawData[i][0] = sin(i * (f + 1));

    delete A;
    delete b;
}


void exercise_B()
{
    auto A = getExerciseAMatrix();

    auto b = new Matrix<double>(N, 1, 0);
    double** bRawData = b->getRawData();
    for (int i = 0; i < N; i++)
        bRawData[i][0] = sin(i * (f + 1));

    auto equations = SetOfEquations<double>(A, b);

    EquationsSolver<double>* solver;

    solver = new JacobiSolver<double>(&equations);
    solver->solve();
    delete solver;

    std::cout << std::endl;
    equations.resetX();

    solver = new GaussSeidelSolver<double>(&equations);
    solver->solve();
    delete solver;

    delete A;
    delete b;
}


int main()
{
    //exercise_A();
    exercise_B();

}