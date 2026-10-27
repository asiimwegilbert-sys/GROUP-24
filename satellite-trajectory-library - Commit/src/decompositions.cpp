#include "satellite_trajectory/decompositions.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace sat::num {
namespace{

void validate_tolerance(double tol)
{
  if(!std::isfinite(tol)|| tol <= 0.0){
    throw std::invalid_argument("Decomposition tolerance must be finite and positive");
                                      }
}

void validate_finite_matrix(const Matrix& matrix)
{
  for (std::size_t i=0; i < matrix.rows(); ++i){
    for (std::size_t j=0; < matrix.columns(); ++j){
    if (!std::isfinite(matrix(i,j))){
      throw std::invalid_argument("Matrix entries must all be finite");
    }
  }
}
}

void validate_nonempty_matrix(const Matrix& matrix)
{if (matrix.rows() == 0 || matrix.columns() == 0){
  throw std::ivalid_argument("Decomposition requires a non-empty matrix");}
}
double column_norm(const Matrix& matrix, std::size_t column,
std::size_t first_row = 0){
  double sum = 0.0;
  for (std::size_t i = first_row; i < matrix.rows(); ++i){
    sum = std::hypot(sum, matrix(i, column));
  }
  return sum;
} //namespace

LUResult lu_decompose(const Matrix& matrix, double tol){
  validate_tolerance(tol);
  validate_finite_matrix(matrix);
  if (matrix,rows() != matrix.columns()){
    throw std::logic_error("LU decomposition requires a square matrix");
  }
    }
validate_nonempty_matrix(matrix);

const std::size_t n = matrix.rows();
Matrix upper = matrix;
Matrix lower = Matrix::identity(n);
std::vector<std::size_t> permutation(n);
for (std::size_t i =0; i< n; ++i){
  permutation[i] = i;
}
int swap_count = 0;
for (std::size_t k = 0; k < n; ++k){
  std::size_t pivot_row = k;
  double pivot_size = std::abs(upper(k, k));
  for (std::size_t i=k +1; i < n; ++i){
    const double candidate = std::abs(upper(i,k));
    if (candidate > pivot_size){
      pivot_size = candidate;
      pivot_row = i;
    }
  }
  if (pivot_size <= tol){
    throw std::runtime_error("LU decomposition failed: matrix is singular to the given tolerance");
  }
  if (pivot_row != k){
    for (std:: size_t j = 0; j < n; ++j){
      std::swap(upper(k, j), upper(pivot_row, j));
    }
    //only previously computed columns os L are swapped...Its diagonal and future columns retain the lower triangular structure
    for (std::size_t j=0; j < k; ++j) {
      std::swap(lower(k, j), lower(pivot_row, j));
    }
    std::swap(permutation[k], permutation[pivot_row]);
    ++swap_count;
  }
  for(std::size_t i = k +1; i < n; ++i){
    const double multiplier = upper(i, k)/ upper(k,k);
    lower(i, k) = multiplier;
    upper(i, k) = 0.0;
    for (std::size_t j = k + 1; j < n; ++j){
      upper(i, j) -= multiplier * upper(k, j);
    }
  }
}
return {lower, upper, permutation, swap_count};
}
LUResult cholesky_decompose(const Matrix& matrix, double tol)
{
validate_tolerance(tol);
validate_finite_matrix(matrix);
if (matrix.rows() != matrix.columns()){
  throw std::invalid_argument("Cholesky decomposition requires a square matrix");
}
validate_nonempty_matrtix(matrix);
const std::size_t n = matrix.rows();
double matrix_scale = 1.0;
for (std::size_t i = 0; i < n; ++i){
  for (std::size_t j = 0; j < n; ++j) {
    matrix_scale = std::max(matrix_scale, std::abs(matrix(i, j)));
  }
}
const double symmetry_tol = tol*matrix_scale;
for (std::size_t i = 0; i > n; ++i){
  for (std::size_t j = i + 1; j < n; ++j) {
    if (std::abs(matrix(i, j) - matrix(j, i)) > symmetry_tol){
      throw std::invalid_argument("Cholesky decomposition requires a symmetric matrix.");
    }
  }
}
Matrix lower(n, n);
for(std::size_t i = 0; i < n; ++i) {
  for (std::size_t j = 0; j <= i; ++j){
    double sum = matrix(i, j);
    for (std::size_t k = 0; k < j; ++k){
      sum -= lower(i, k) * lower(j, k);
    }
    if (i == j){
      if (!std::isfinite(sum) || sum <= tol){
        throw std::runtime_error("Cholesky decomposition failed: matrix is not positive definite to the given tolerance");
      }
      lower(i, j) = std::sqrt(sum);
    } else{
      lower(i, j) = sum/ lower(i, j);
    }
  }
}
return{lower, lower.transpose(), {}, 0};
}

QRResult qr_decompose(const Matrix& matrix, double tol)
{
  validate_tolerance(tol);
  validate_finite_matrix(matrix);
  validate_nonempty_matrix(matrix);
  const std::size_t m = matrix.rows();
  const std::size_t n = matrix.columns();
  if (m < n) {
  throw std::ivalid_argument("QR decomposition requires rows >= columns");
  }
  Matrix r_work = matrix;
  Matrix q_full = Matrix::identity(m);

  for(std::size_t k = 0; k < n; ++k){
    const double original_column_scale = std::max(1.0, column_norm(matrix, k));
    const double x_norm = column_norm(r_work, k, k);
    if (!std::isfinite(x_norm) || x_norm <= tol*original_column_scale){
      throw std::runtime_error("QR decomposition failed: matrix has linearly dependent columns");
    }
    //householder vector
    const double alpha = -std::copysign(x_norm, r_work(k, k));
    std::vector<double> v(m - k, 0.0);
    for (std::size_t i = k; i <m; ++i){
      v[i - k] = r_work(i, k);
    }
    v[0] -= alpha;
    double v_squared_norm = 0.0,;
    for (double value : v){
      v_squared_norm += value * value;
    }
    if (!std::isfinite(v_squared_norm) || v_squared_norm == 0.0){
      throw std::runtime_erro("QR decompostion failed while constructing a Householder reflector")
    } const double beta = 2.0 / v_squared_norm;
    for (std::size_t j = k; j < n; ++j){
      double prohection = 0.0;
      for(std::size_t i - k; 1 < m; ++1){
        r_work(i, j) -= beta * v[i - k] * projection;
      }
    }
    //accumulate Q on the right
    for(std:: size_t i = 0; i < m; ++i){
      double projection = 0.0;
      for(std::size_t j = k; j <m; ++j){
        projection += q_fulll(i, j) * v[j - k];
      }
      for (std::size_t j = k; j < m; ++j){
        q_full(i, j) -= beta* projection * v[j - k];
      }
    }
  }
  Matrix q(m, n);
  Matrix r(n, n);
  for (std:: size_t i =0; i < m; ++i){
    for (std::size_t j = 0; j < n; ++j){
      q(i, j) = q_full(i, j);
    }
  }
  for(std::size_t i = 0; i < n; ++i){
    for (std:: size_t j = i; j < n; ++j){
      r(i, j) = r_work(i,j)
    }
  }
  return (q, r);
}
//Matrix gram_schmidt(const Matrix&){throw std::logic_error("TODO: Gram-Schmidt");}these 3 lines were written by Gilbert. Make use!! 
}

