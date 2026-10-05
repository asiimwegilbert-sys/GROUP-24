# Derrick - Linear Solvers Module

## Project

Satellite Trajectory Numerical Computing Library

## Language

C++23

## Module

`sat_trajectory.linear_solvers`

## What this module does

The Linear Solvers module is used to solve systems of linear equations:

`A x = b`

The first version contains simple functions for:

- Forward substitution
- Back substitution
- Gaussian elimination
- Partial pivoting
- Residual calculation
- Iterative refinement

## Main types

```cpp
using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;
```

## SolverOptions

```cpp
struct SolverOptions {
    double pivot_tolerance = 1e-12;
};
```

The tolerance is used to identify zero or very small pivot values.

## Main functions

```cpp
Vector backSubstitution(const Matrix& U, const Vector& b,
                       SolverOptions options = {});

Vector forwardSubstitution(const Matrix& L, const Vector& b,
                          SolverOptions options = {});

Vector solveGaussian(const Matrix& A, const Vector& b,
                     SolverOptions options = {});

double residualNorm(const Matrix& A, const Vector& x, const Vector& b);

Vector refineSolution(const Matrix& A, const Vector& b, const Vector& x,
                      SolverOptions options = {}, int iterations = 2);
```

## Simple method description

1. Check that the matrix is square.
2. Check that the vector has the correct size.
3. Use partial pivoting during Gaussian elimination.
4. Convert the system into an upper triangular system.
5. Use back substitution to find the answer.
6. Calculate the residual to check the answer.

## C++23 build example with GCC 14

```bash
g++ -std=c++23 -fmodules-ts -c include/linear_solvers.cppm -o build/linear_solvers.o
g++ -std=c++23 -fmodules-ts -c src/linear_solvers.cpp -o build/linear_solvers_impl.o
g++ -std=c++23 -fmodules-ts -c tests/test_linear_solvers.cpp -o build/test_linear_solvers.o
g++ build/linear_solvers.o build/linear_solvers_impl.o build/test_linear_solvers.o -o build/test_linear_solvers
./build/test_linear_solvers
```

## Expected test result

```text
All Linear Solvers tests passed.
```

## Beginner notes

This implementation is intentionally kept simple so that the main algorithms can be
understood by a first-year or second-year undergraduate student. The code uses basic
loops, vectors, functions, exceptions and simple numerical calculations rather than
advanced C++ techniques.
