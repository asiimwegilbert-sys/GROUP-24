Individual Member Report: Matrix Decompositions
Week 01 report by Stacy on Lead, Matrix decompositions (LU, Cholesky, QR, Gram-Schmidt)

Summary
This week I defined the design of the matrix decompositions module for the Satellite Trajectory Numerical Computing Library and documented it. The note covers the purpose, methods, API, error handling, numerical assumptions, dependencies and test plan.
The module is written in C++17 in the sat::num namespace, with no external math libraries, and builds on Ibrahim's Matrix class.

The module's Overview
Method, Factorisation, Requirements
LU with partial pivoting |P·A = L·U |square, non-singular
Cholesky, A = L·Lᵀ| square, symmetric, positive definite
Modified Gram-Schmidt |A = Q·R |rows ≥ columns, independent columns
Householder QR |A = Q·R | rows ≥ columns, full column rank

Files
include/satellite_trajectory/decompositions.hpp
src/decompositions.cpp
tests/test_decompositions.cpp
docs/Stacy_decompositions.md

API
LUResult holds lower, upper, permutation and swap_count
QRResult holds q and r in thin form (Q is m×n, R is n×n)
lu_decompose(A, tol)
cholesky_decompose(A, tol), which returns lower and upper = lower
qr_decompose(A, tol)
gram_schmidt_qr(A, tol), which returns both factors
gram_schmidt(A, tol), which returns Q only

Approach (how the module is to be attempted)
Interface first: agreeing the API and the error convention with Ibrahim, Derrick and Erick before implementing.
LU with partial pivoting: selecting the largest pivot in each column, swapping rows, storing the multipliers below the diagonal, then separating L and U. Recording the permutation and swap counting so Derrick can compute determinants.
Cholesky: checking that the matrix is square and symmetric, building L column by column, and rejecting any non-positive diagonal value.
Modified Gram-Schmidt: orthogonalising each column against the previous ones and report dependent columns.
Householder QR: applying successive reflections to produce R and accumulate Q, then returning the thin form.
Tests with each method: writing tests in the same branch as the implementation (normal, edge and invalid cases).
Integration: adding files to CMake in the same pull request, building from a clean directory, running ctest, then opening a pull request for review.

Items Used
Matrix class (Ibrahim): rows(), columns(), operator()(i, j), transpose(), and the (rows, columns, value) constructor
C++ standard library: <vector>, <cmath>, <cstddef>, <numeric>, <stdexcept>, <utility>, <algorithm>
Build and test: CMake and CTest

Error Handling
std::invalid_argument: non-square matrix (LU, Cholesky), non-symmetric matrix (Cholesky), or fewer rows than columns (QR, Gram-Schmidt)
std::runtime_error: singular matrix (LU), not positive definite (Cholesky), or rank-deficient (QR, Gram-Schmidt)

Numerical Assumptions
Default tolerance is 1e-10. A pivot or diagonal value at or below it is treated as zero.
QR and Gram-Schmidt use a relative zero test: tol * max(1, column norm).
Householder QR may produce negative diagonal entries in R.

Completed;
Module design note written and added to docs/
API and result types defined
Testing Completed;
[ ] Normal cases tested
[ ] Edge cases tested
[ ] Invalid inputs tested
[ ] Relevant tests pass
[ ] Clean build tested

Test commands: cmake -S. -B build, cmake --build build, ctest --test-dir build --output-on-failure

Next Week's plan
Implementing and testing Cholesky decomposition
Implementing and testing modified Gram-Schmidt
Implementing and testing Householder QR
