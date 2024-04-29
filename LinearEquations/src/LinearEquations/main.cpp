#include "Matrix.h"
#include "SetOfEquations.h"
#include "JacobiSolver.h"

constexpr int c = 5;
constexpr int d = 0;
constexpr int N = 900 + c *10 + d;

constexpr int e = 3;
constexpr int f = 3;

void exercise_A() 
{
    Matrix<float>* A = new Matrix<float>(N, N, 0);
    A->setDiagonal(5 + e, 0);
    A->setDiagonal(-1, 1);
    A->setDiagonal(-1, -1);

    Matrix<float>* b = new Matrix<float>(N, 1, 0);
    float** bRawData = b->getRawData();
    for (int i = 0; i < N; i++)
        bRawData[i][0] = sin(i * (f + 1));

    SetOfEquations<float> equations = SetOfEquations<float>(A, b);

    JacobiSolver<float> solver = JacobiSolver<float>(&equations);
    solver.solve();
    equations.getX()->print();

    delete A;
    delete b;
}


int main()
{
    exercise_A();

}