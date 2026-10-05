Satellite Trajectory Numerical Computing Library — Linear Solvers

Contributor: Lubangakene Derrick  
Language standard: C++23  
Module: `sat_trajectory.linear_solvers`

 Purpose

This module provides the linear-system routines in the project blueprint. It supports triangular-system substitution, Gaussian elimination with partial pivoting, residual calculation, and iterative refinement.

Types

- `Vector` — `std::vector<double>`
- `Matrix` — `std::vector<std::vector<double>>`
- `SolverOptions` — currently provides `pivot_tolerance`, defaulting to `1e-12`.

Functions

- `forwardSubstitution(L, b)` — solves a lower-triangular system.
- `backSubstitution(U, b)` — solves an upper-triangular system.
- `solveGaussian(A, b)` — solves a square system using Gaussian elimination and partial pivoting.
- `residualNorm(A, x, b)` — computes the Euclidean norm of `Ax-b`.
- `refineSolution(A, b, x, options, iterations)` — improves an existing solution by repeatedly solving the residual correction system.

 Validation and numerical safeguards

The implementation checks:

1. The matrix is non-empty and square.
2. Matrix rows are not ragged.
3. Matrix, right-hand-side, and solution values are finite.
4. Vector dimensions match the matrix dimension.
5. Pivot tolerance is positive and finite.
6. Triangular pivots are not zero or numerically negligible.
7. Gaussian elimination detects singular or nearly singular systems.
8. A negative refinement-iteration count is rejected.

Example use

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

 Testing

The supplied test program checks:

- back substitution;
- forward substitution;
- Gaussian elimination with a pivot swap;
- residual calculation;
- iterative refinement;
- singular-matrix rejection; and
- dimension validation.
