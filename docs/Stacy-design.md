Matrix Decompositions
This is a module design note for Lead, Matrix Decompositions being handled my Stacy, branch name; feature/stacy-decompositions. The module provides the matrix factorisations
used by the Satellite Trajectory Numerical Computing Library: LU, Cholesky, QR and Gram-Schmidt.

Files included are;
'include/satellite_trajectory/decompositions.hpp'
'src/decompositions.cpp'
''tests/test_decompositions.cpp'

The items to be used include;
Matrix class being handled by Ibrahim; rows(), columns(), operator()(i,j), transpose() and the (row, columns, value) constructor
The C++ standard library too; <vector>, <cmath>, <cstddef>, <numeric>
Build and test; CMake and CTest

 Methods
Methods, Factorisations, Requirements
LU with partial pivoting, P·A = L·U, square, non-singular
Cholesky, A = L·Lᵀ,| square, symmetric, positive definite
Modified Gram-Schmidt, A = Q·R ,| rows ≥ columns, independent columns 
Householder QR, A = Q·R ,| rows ≥ columns, full column rank 

The APIs
namespace sat::num {
struct LUResult {
    Matrix lower;                          // unit lower-triangular
    Matrix upper;                          // upper-triangular
    std::vector<std::size_t> permutation;  // row i of P*A is row permutation[i] of A
    int swap_count = 0;                    
};

struct QRResult {
    Matrix q;  // m x n, orthonormal columns
    Matrix r;  // n x n, upper-triangular
};

LUResult lu_decompose(const Matrix& A, double tol = 1e-10);
LUResult cholesky_decompose(const Matrix& A, double tol = 1e-10);  // upper = lower^T
QRResult qr_decompose(const Matrix& A, double tol = 1e-10);
QRResult gram_schmidt_qr(const Matrix& A, double tol = 1e-10);
Matrix   gram_schmidt(const Matrix& A, double tol = 1e-10);        // returns Q only

}  // namespace sat::num

Error Handling
`std::invalid_argument`: non-square matrix (LU, Cholesky), non-symmetric matrix (Cholesky), or fewer rows than columns (QR, Gram-Schmidt)
`std::runtime_error`: singular matrix (LU), not positive definite (Cholesky), or rank-deficient (QR, Gram-Schmidt)

Numerical Assumptions to be cosidered;
Default tolerance is `1e-10`. A pivot or diagonal value at or below the tolerance is treated as zero.
QR and Gram-Schmidt use a relative zero test: `tol * max(1, column norm)`.
QR results are in thin form. Householder QR may give negative diagonal entries in R.
