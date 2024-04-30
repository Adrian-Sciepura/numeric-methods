#include <fstream>
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

Matrix<double>* prepareExampleMatrix_A(double a1, double a2, double a3, int size = N)
{
    Matrix<double>* A = new Matrix<double>(size, size, 0);
    A->setDiagonal(a1, 0);
    A->setDiagonal(a2, 1);
    A->setDiagonal(a2, -1);
    A->setDiagonal(a3, 2);
    A->setDiagonal(a3, -2);
	return A;
}

Matrix<double>* prepareExampleMatrix_B(int size = N)
{
    auto b = new Matrix<double>(size, 1, 0);
    auto bRawData = b->getRawData();
    for (int i = 0; i < size; i++)
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
    auto jacobiSolve = solver->solve();
    delete solver;

    std::cout << std::endl;
    equations.resetX();

    std::cout << "Running Gauss-Seidel solver for exercise B" << std::endl;
    solver = new GaussSeidelSolver<double>(&equations);
    auto gaussSolve = solver->solve();
    delete solver;
    
    std::cout << std::endl << std::endl;

    auto file = std::ofstream("exercise_B.csv");
    file << "Iteration;Jacobi;Gauss-Seidel\n";
    int maxIterations = jacobiSolve.iterations > gaussSolve.iterations ? jacobiSolve.iterations : gaussSolve.iterations;

    auto jacobiIterator = jacobiSolve.norms.begin();
    auto gaussIterator = gaussSolve.norms.begin();
    for (int i = 0; i < maxIterations; i++)
    {
        file << i << ';';

        if (jacobiSolve.iterations > i)
        {
            file << *jacobiIterator;
            jacobiIterator++;
        }

        file << ';';

        if (gaussSolve.iterations > i)
        {
            file << *gaussIterator;
			gaussIterator++;
        }

        file << std::endl;
    }

    file.close();

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
    auto jacobiSolve = solver->solve();
    delete solver;

    std::cout << std::endl;
    equations.resetX();

    std::cout << "Running Gauss-Seidel solver for exercise C" << std::endl;
    solver = new GaussSeidelSolver<double>(&equations);
    auto gaussSolve = solver->solve();
    delete solver;

    std::cout << std::endl << std::endl;

    auto file = std::ofstream("exercise_C.csv");
    file << "Iteration;Jacobi;Gauss-Seidel\n";
    int maxIterations = jacobiSolve.iterations > gaussSolve.iterations ? jacobiSolve.iterations : gaussSolve.iterations;

    auto jacobiIterator = jacobiSolve.norms.begin();
    auto gaussIterator = gaussSolve.norms.begin();
    for (int i = 0; i < maxIterations; i++)
    {
        file << i << ';';

        if (jacobiSolve.iterations > i)
        {
            file << *jacobiIterator;
            jacobiIterator++;
        }

        file << ';';

        if (gaussSolve.iterations > i)
        {
            file << *gaussIterator;
            gaussIterator++;
        }

        file << std::endl;
    }

    file.close();

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
    std::cout << solver->solve();
    delete solver;


    std::cout << std::endl << std::endl;

    delete A;
    delete b;
}


void exercise_E()
{
    std::vector<int> sizesToTest = { 100, 500, 1000, 2000, 3000, 4000, 5000, 6000 };
    EquationsSolver<double>* solver;

    auto file = std::ofstream("exercise_E.csv");
    file << "size;Jacobi;Gauss-Seidel;LU factorization\n";

    for (auto size : sizesToTest)
    {
        std::cout << "\n\n------- Current size: " << size << " -------" << std::endl;
        file << size << ";";

        auto A = prepareExampleMatrix_A(5 + e, -1, -1, size);
        auto b = prepareExampleMatrix_B(size);
        auto equations = SetOfEquations<double>(A, b);

        solver = new JacobiSolver<double>(&equations);
        std::cout << "Jacobi: \n";
        auto log = solver->solve();
        std::cout << log << std::endl;
        file << log.time << ";";
        equations.resetX();
        delete solver;
        

        solver = new GaussSeidelSolver<double>(&equations);
        std::cout << "Gauss-Seidel: \n";
        log = solver->solve();
        std::cout << log << std::endl;
        file << log.time << ";";
        equations.resetX();
        delete solver;
        

        solver = new LUfactorizationSolver<double>(&equations);
        std::cout << "LU factorization: \n";
        log = solver->solve();
        std::cout << log << std::endl;
        file << log.time;
        equations.resetX();
        delete solver;
        file << std::endl;
    }


    file.close();
}


int main()
{
    exercise_A();
    exercise_B();
    exercise_C();
    exercise_D();
    exercise_E();
}