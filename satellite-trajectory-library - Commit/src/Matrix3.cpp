// matrix.cpp
// Code for the Matrix class declared in include/satellite_trajectory/matrix.hpp.
//
// Error rules used in this file:
//   std::invalid_argument -> the input itself is wrong (zero size, rows of
//                            different lengths, sizes that do not fit together)
//   std::out_of_range     -> a (row, column) index is outside the matrix
//
// A default-constructed Matrix is empty (0 x 0). You can create it and read its
// size, but using it in arithmetic throws, because the result would have size 0.

#include "satellite_trajectory/matrix.hpp"
#include <stdexcept>
namespace sat::num {
// Constructor
// rows x columns matrix with every element set to 'value' (0.0 if not given).
Matrix::Matrix(std::size_t rows, std::size_t columns, double value)
    : rows_(rows), columns_(columns), values_(rows * columns, value) {
    if (rows == 0 || columns == 0) {
        throw std::invalid_argument("Matrix: rows and columns must be at least 1");
    }
}
// Matrix A{{1, 2, 3}, {4, 5, 6}};   (2 rows, 3 columns)
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> values)
    : rows_(values.size()), columns_(0) {
    if (rows_ == 0) {
        throw std::invalid_argument("Matrix: no rows given");
    }
    columns_ = values.begin()->size();  // length of the first row
    if (columns_ == 0) {
        throw std::invalid_argument("Matrix: rows must not be empty");
    }
    values_.reserve(rows_ * columns_);
    for (const auto& row : values) {
        if (row.size() != columns_) {
            throw std::invalid_argument("Matrix: all rows must have the same length");
        }
        for (double x : row) {
            values_.push_back(x);  // stored row by row (row-major)
   }  }}
// n x n matrix with 1 on the diagonal and 0 everywhere else.
Matrix Matrix::identity(std::size_t size) {
    Matrix result(size, size);  // all zeros (throws if size is 0)
    for (std::size_t i = 0; i < size; ++i) {
        result(i, i) = 1.0;
    }
    return result;
}
// Size information
std::size_t Matrix::rows() const noexcept { return rows_; }
std::size_t Matrix::columns() const noexcept { return columns_; }
// Element access (zero-based: the first element is (0, 0))
// Element (i, j) is stored at values_[i * columns_ + j].
double& Matrix::operator()(std::size_t row, std::size_t column) {
    if (row >= rows_ || column >= columns_) {
        throw std::out_of_range("Matrix: index outside the matrix");
    }
    return values_[row * columns_ + column];
}
const double& Matrix::operator()(std::size_t row, std::size_t column) const {
    if (row >= rows_ || column >= columns_) {
        throw std::out_of_range("Matrix: index outside the matrix");
    }
    return values_[row * columns_ + column];}
//operations
// Rows become columns and columns become rows.
Matrix Matrix::transpose() const {
    Matrix result(columns_, rows_);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < columns_; ++j) {
            result(j, i) = (*this)(i, j);
        }   } return result;}
Matrix operator+(const Matrix& a, const Matrix& b) {
    if (a.rows() != b.rows() || a.columns() != b.columns()) {
        throw std::invalid_argument("Matrix +: sizes must match");
    }
    Matrix result(a.rows(), a.columns());
    for (std::size_t i = 0; i < a.rows(); ++i) {
        for (std::size_t j = 0; j < a.columns(); ++j) {
            result(i, j) = a(i, j) + b(i, j);
        }  } return result;}
Matrix operator-(const Matrix& a, const Matrix& b) {
    if (a.rows() != b.rows() || a.columns() != b.columns()) {
        throw std::invalid_argument("Matrix -: sizes must match");
    }
    Matrix result(a.rows(), a.columns());
    for (std::size_t i = 0; i < a.rows(); ++i) {
        for (std::size_t j = 0; j < a.columns(); ++j) {
            result(i, j) = a(i, j) - b(i, j);
        }   } return result;}
// (a is r x n) * (b is n x c) gives an r x c matrix.
// Element (i, j) of the result = row i of a times column j of b.
Matrix operator*(const Matrix& a, const Matrix& b) {
    if (a.columns() != b.rows()) {
        throw std::invalid_argument("Matrix *: columns of the left matrix must equal rows of the right");   }
    Matrix result(a.rows(), b.columns());
    for (std::size_t i = 0; i < a.rows(); ++i) {
        for (std::size_t j = 0; j < b.columns(); ++j) {
            double sum = 0.0;
            for (std::size_t k = 0; k < a.columns(); ++k) {
                sum += a(i, k) * b(k, j);   }
            result(i, j) = sum;
        } }    return result;}
// number * matrix: every element is multiplied by the number.
Matrix operator*(double scalar, const Matrix& m) {
    Matrix result(m.rows(), m.columns());
    for (std::size_t i = 0; i < m.rows(); ++i) {
        for (std::size_t j = 0; j < m.columns(); ++j) {
            result(i, j) = scalar * m(i, j); }}
    return result;}
