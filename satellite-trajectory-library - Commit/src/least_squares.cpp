#include "satellite_trajectory/least_squares.hpp"
#include "satellite_trajectory/decompositions.hpp"

#include <stdexcept>

namespace sat::num {

// Minimises ||A x - b|| using QR: A = Q R, so R x = Q^T b (back substitution).
Vector least_squares_solution(const Matrix& A, const Vector& b)
{
  if (A.rows() == 0 || A.columns() == 0) {
    throw std::invalid_argument("Least squares: matrix must not be empty");
  }
  if (b.size() != A.rows()) {
    throw std::invalid_argument("Least squares: b must have one entry per row of A");
  }
  if (A.rows() < A.columns()) {
    throw std::invalid_argument("Least squares: need at least as many rows as columns");
  }

  const QRResult qr = qr_decompose(A);   // throws std::runtime_error for dependent columns
  const std::size_t n = A.columns();

  Vector qtb(n, 0.0);
  for (std::size_t j = 0; j < n; ++j) {
    for (std::size_t i = 0; i < A.rows(); ++i) {
      qtb[j] += qr.q(i, j) * b[i];
    }
  }

  Vector x(n, 0.0);
  for (std::size_t i = n; i-- > 0;) {
    double sum = qtb[i];
    for (std::size_t j = i + 1; j < n; ++j) {
      sum -= qr.r(i, j) * x[j];
    }
    x[i] = sum / qr.r(i, i);
  }
  return x;
}

// Fits a0 + a1 x + ... + a_degree x^degree to the data by least squares.
std::vector<double> least_squares_polynomial_fit(const std::vector<double>& x,
                                                 const std::vector<double>& y,
                                                 std::size_t degree)
{
  if (x.size() != y.size() || x.empty()) {
    throw std::invalid_argument("Polynomial fit: x and y must be non-empty and the same size");
  }
  if (x.size() < degree + 1) {
    throw std::invalid_argument("Polynomial fit: need at least degree + 1 points");
  }

  Matrix design(x.size(), degree + 1);   // Vandermonde matrix: column j holds x^j
  Vector rhs(y.size(), 0.0);
  for (std::size_t i = 0; i < x.size(); ++i) {
    double power = 1.0;
    for (std::size_t j = 0; j <= degree; ++j) {
      design(i, j) = power;
      power *= x[i];
    }
    rhs[i] = y[i];
  }

  const Vector coefficients = least_squares_solution(design, rhs);
  std::vector<double> result(degree + 1);
  for (std::size_t j = 0; j <= degree; ++j) result[j] = coefficients[j];
  return result;
}

}  // namespace sat::num
