#pragma once
#include <cstddef>
#include <initializer_list>
#include <vector>
#include "satellite_trajectory/vector.hpp"
namespace sat::num {
class Matrix {
public:
  Matrix() = default;
  Matrix(std::size_t rows, std::size_t columns, double value = 0.0);
  Matrix(std::initializer_list<std::initializer_list<double>> values);
  std::size_t rows() const noexcept;
  std::size_t columns() const noexcept;
  double& operator()(std::size_t row, std::size_t column);
  const double& operator()(std::size_t row, std::size_t column) const;
  Matrix transpose() const;
  static Matrix identity(std::size_t size);
private:
  std::size_t rows_{0}, columns_{0};
  std::vector<double> values_;
};
Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Vector operator*(const Matrix&, const Vector&);
Matrix operator*(double, const Matrix&);
}
