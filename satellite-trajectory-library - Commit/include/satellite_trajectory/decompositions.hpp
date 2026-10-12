#pragma once
#include "satellite_trajectory/matrix.hpp"
namespace sat::num {
struct LUResult { Matrix lower; Matrix upper; };
struct QRResult { Matrix q; Matrix r; };
LUResult lu_decompose(const Matrix&);
LUResult cholesky_decompose(const Matrix&);
QRResult qr_decompose(const Matrix&);
Matrix gram_schmidt(const Matrix&);
}
