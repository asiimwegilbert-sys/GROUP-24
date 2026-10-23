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

//LUResult cholesky_decompose(const Matrix&){throw std::logic_error("TODO: Cholesky");} these 3 lines were written by Gilbert. Make use!! 
//QRResult qr_decompose(const Matrix&){throw std::logic_error("TODO: QR");}
//Matrix gram_schmidt(const Matrix&){throw std::logic_error("TODO: Gram-Schmidt");}
}

