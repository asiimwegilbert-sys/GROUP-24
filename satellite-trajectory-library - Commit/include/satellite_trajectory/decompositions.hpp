#pragma once
#include "satellite_trajectory/matrix.hpp"

#include <cstddef>
#include <vector>
namespace sat::num {
//LU factorization with partial pivoting. The factors satify
//P*A = lower * upper, where row i of P*A is row permutation[i] of A.
struct LUResult {
Matrix lower;// unit Lower-traingleular matrix
Matrix upper; //upper-triangular matrix
std::vector<std::size_t> permutation;
int swap_count{0};
};

struct QRResult {
Matrix q;
Matrix r;
};

LUResult lu_decompose(const Matrix& matrix, double tol = 1e-10);
//returns lower and upper factors satisfying A = lower * upper, with upper equal to lower.transpose().

LUResult cholesky_decompose(const Matrix& matrix, double tol = 1e-10);
//householder QR decomposition, returned in thin form
QRResult qr_decompose(const Matrix& matrix, double tol = 1e-10)

//modified Gram-schmidt QR decomposition, returned in thin form
QRResult qr_decompose(const Matrix& matrix, double tol = 1e-10 );

//convenience function returning only the orthogonal Q factor.
Matrix gram_schmidt(const Matrix& matrix, double tol = 1e-10);
}
