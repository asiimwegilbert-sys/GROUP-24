#include "satellite_trajectory/decompositions.hpp"
#include <stdexcept>
namespace sat::num {
LUResult lu_decompose(const Matrix&){throw std::logic_error("TODO: LU");}
LUResult cholesky_decompose(const Matrix&){throw std::logic_error("TODO: Cholesky");}
QRResult qr_decompose(const Matrix&){throw std::logic_error("TODO: QR");}
Matrix gram_schmidt(const Matrix&){throw std::logic_error("TODO: Gram-Schmidt");}
}
