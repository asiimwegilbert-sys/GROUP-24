#include "satellite_trajectory/matrix.hpp"

#include <stdexcept>

namespace sat::num {

Matrix::Matrix(std::size_t rows, std::size_t columns, double value)
    : rows_(rows), columns_(columns), values_(rows * columns, value)
{
}

Matrix::Matrix(
    std::initializer_list<std::initializer_list<double>> values)
    : rows_(values.size()),
      columns_(values.size() == 0 ? 0 : values.begin()->size()),
      values_{}
{
    values_.reserve(rows_ * columns_);

    for (const auto& row : values) {
        if (row.size() != columns_) {
            throw std::invalid_argument(
                "All matrix rows must have the same length");
        }

        for (double value : row) {
            values_.push_back(value);
        }
    }
}

std::size_t Matrix::rows() const noexcept
{
    return rows_;
}

std::size_t Matrix::columns() const noexcept
{
    return columns_;
}

double& Matrix::operator()(std::size_t row, std::size_t column)
{
    if (row >= rows_ || column >= columns_) {
        throw std::out_of_range("Matrix index out of range");
    }

    return values_.at(row * columns_ + column);
}

const double& Matrix::operator()(
    std::size_t row, std::size_t column) const
{
    if (row >= rows_ || column >= columns_) {
        throw std::out_of_range("Matrix index out of range");
    }

    return values_.at(row * columns_ + column);
}

Matrix Matrix::transpose() const
{
    Matrix result(columns_, rows_);

    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < columns_; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }

    return result;
}

Matrix Matrix::identity(std::size_t size)
{
    Matrix result(size, size);

    for (std::size_t i = 0; i < size; ++i) {
        result(i, i) = 1.0;
    }

    return result;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
    if (a.rows() != b.rows() || a.columns() != b.columns()) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    Matrix result(a.rows(), a.columns());

    for (std::size_t i = 0; i < a.rows(); ++i) {
        for (std::size_t j = 0; j < a.columns(); ++j) {
            result(i, j) = a(i, j) + b(i, j);
        }
    }

    return result;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
    if (a.rows() != b.rows() || a.columns() != b.columns()) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    Matrix result(a.rows(), a.columns());

    for (std::size_t i = 0; i < a.rows(); ++i) {
        for (std::size_t j = 0; j < a.columns(); ++j) {
            result(i, j) = a(i, j) - b(i, j);
        }
    }

    return result;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
    if (a.columns() != b.rows()) {
        throw std::invalid_argument(
            "Matrix dimensions are incompatible for multiplication");
    }

    Matrix result(a.rows(), b.columns());

    for (std::size_t i = 0; i < a.rows(); ++i) {
        for (std::size_t j = 0; j < b.columns(); ++j) {
            for (std::size_t k = 0; k < a.columns(); ++k) {
                result(i, j) += a(i, k) * b(k, j);
            }
        }
    }

    return result;
}

Vector operator*(const Matrix& matrix, const Vector& vector)
{
    if (matrix.columns() != vector.size()) {
        throw std::invalid_argument(
            "Matrix columns must match vector size");
    }

    Vector result(matrix.rows(), 0.0);

    for (std::size_t i = 0; i < matrix.rows(); ++i) {
        for (std::size_t j = 0; j < matrix.columns(); ++j) {
            result[i] += matrix(i, j) * vector[j];
        }
    }

    return result;
}

Matrix operator*(double scalar, const Matrix& matrix)
{
    Matrix result(matrix.rows(), matrix.columns());

    for (std::size_t i = 0; i < matrix.rows(); ++i) {
        for (std::size_t j = 0; j < matrix.columns(); ++j) {
            result(i, j) = scalar * matrix(i, j);
        }
    }

    return result;
}

} // namespace sat::num

