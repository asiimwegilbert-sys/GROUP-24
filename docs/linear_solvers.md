# Satellite Trajectory Numerical Computing Library — Linear Solvers

**Contributor:** Derrick  
**Language standard:** C++23  
**Module:** `sat_trajectory.linear_solvers`

## Purpose

This module provides the linear-system routines assigned to Derrick in the project blueprint. It supports triangular-system substitution, Gaussian elimination with partial pivoting, residual calculation, and iterative refinement.

## Public interface

The public C++23 module interface is `include/linear_solvers.cppm`.

### Types

- `Vector` — `std::vector<double>`
- `Matrix` — `std::vector<std::vector<double>>`
- `SolverOptions` — currently provides `pivot_tolerance`, defaulting to `1e-12`.

### Functions

- `forwardSubstitution(L, b)` — solves a lower-triangular system.
- `backSubstitution(U, b)` — solves an upper-triangular system.
- `solveGaussian(A, b)` — solves a square system using Gaussian elimination and partial pivoting.
- `residualNorm(A, x, b)` — computes the Euclidean norm of `Ax-b`.
- `refineSolution(A, b, x, options, iterations)` — improves an existing solution by repeatedly solving the residual correction system.

## Validation and numerical safeguards

The implementation checks:

1. The matrix is non-empty and square.
2. Matrix rows are not ragged.
3. Matrix, right-hand-side, and solution values are finite.
4. Vector dimensions match the matrix dimension.
5. Pivot tolerance is positive and finite.
6. Triangular pivots are not zero or numerically negligible.
7. Gaussian elimination detects singular or nearly singular systems.
8. A negative refinement-iteration count is rejected.

## C++23 module layout

```text
feature/derrick-linear-solvers/
├── include/
│   └── linear_solvers.cppm
├── src/
│   └── linear_solvers.cpp
├── tests/
│   └── test_linear_solvers.cpp
└── docs/
    └── linear_solvers.md
```

## Example use

```cpp
import sat_trajectory.linear_solvers;

using namespace sat_trajectory;

Matrix A{
    {0.0, 2.0, 1.0},
    {1.0, 1.0, 1.0},
    {2.0, 1.0, 0.0}
};
Vector b{4.0, 6.0, 5.0};

Vector x = solveGaussian(A, b);
double error = residualNorm(A, x, b);
```

## Building with C++23

C++23 named-module compilation is compiler-dependent. The project should use a compiler with named C++ module support enabled.

For GCC 14, a simple module build can be performed as follows:

```bash
g++ -std=c++23 -fmodules-ts -c include/linear_solvers.cppm -o linear_solvers.o
# If the compiler does not recognize .cppm automatically, compile the module interface as C++ source:
# g++ -std=c++23 -fmodules-ts -x c++ -c include/linear_solvers.cppm -o linear_solvers.o

g++ -std=c++23 -fmodules-ts -c src/linear_solvers.cpp -o linear_solvers_impl.o

g++ -std=c++23 -fmodules-ts -c tests/test_linear_solvers.cpp -o test_linear_solvers.o
g++ linear_solvers.o linear_solvers_impl.o test_linear_solvers.o -o test_linear_solvers
./test_linear_solvers
```

The exact module build command may vary with the compiler and its C++23 module implementation. The important project requirement is that all compilation uses the C++23 language standard and the module interface is compiled before units that import it.

## Testing

The supplied test program checks:

- back substitution;
- forward substitution;
- Gaussian elimination with a pivot swap;
- residual calculation;
- iterative refinement;
- singular-matrix rejection; and
- dimension validation.

Expected result:

```text
All Linear Solvers C++23 tests passed.
```
