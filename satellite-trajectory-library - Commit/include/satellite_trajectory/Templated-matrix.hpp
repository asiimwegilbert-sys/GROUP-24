// matrix_templated.hpp
// Small helper TEMPLATES for the Matrix class.
//
// A template is code written once that the compiler copies for each type you use it with.
// Example: toMatrix works for int, float and double data without three separate versions.
//
// This file is header-only: all the code is here, there is no matrix_utils.cpp
// and nothing to add to CMake. It only uses the public Matrix interface
// (rows(), columns(), operator()), so it does not change matrix.hpp or matrix.cpp.
//
// Why Matrix itself is not a template: the rest of the library uses Matrix as a
// matrix of doubles, so these helpers add flexibility around it instead.

#pragma once

#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "satellite_trajectory/matrix.hpp"

namespace sat::num {
// toMatrix: build a Matrix from nested vectors of ANY number type.
//
//   std::vector<std::vector<int>> data = {{1, 2, 3}, {4, 5, 6}};
//   Matrix A = toMatrix(data);          // 2 x 3 Matrix of doubles
//
// T is the template parameter: the compiler works it out from 'rows'.
// Note: pass a named variable. toMatrix({{1, 2}, {3, 4}}) will not compile
// because the compiler cannot work out T from a bare { } list.
//
// Throws std::invalid_argument if there are no rows, a row is empty,
// or the rows have different lengths.
template <typename T>
Matrix toMatrix(const std::vector<std::vector<T>>& rows) {
    static_assert(std::is_arithmetic<T>::value,
                  "toMatrix: T must be a number type such as int, float or double");

    if (rows.empty() || rows[0].empty()) {
        throw std::invalid_argument("toMatrix: need at least one row and one column");
    }
    const std::size_t columns = rows[0].size();
    for (const auto& row : rows) {
        if (row.size() != columns) {
            throw std::invalid_argument("toMatrix: all rows must have the same length");
        }
    }

    Matrix result(rows.size(), columns);
    for (std::size_t i = 0; i < rows.size(); ++i) {
        for (std::size_t j = 0; j < columns; ++j) {
            result(i, j) = static_cast<double>(rows[i][j]);
        }
    }
    return result;
}
// toMatrix: the same idea for a built-in 2D array.
//
//   int data[2][3] = {{1, 2, 3}, {4, 5, 6}};
//   Matrix A = toMatrix(data);          // 2 x 3
//
// R and C are template parameters too, but they are NUMBERS (the array sizes).
// The compiler reads them from the array, so you do not pass them yourself.
template <typename T, std::size_t R, std::size_t C>
Matrix toMatrix(const T (&data)[R][C]) {
    static_assert(std::is_arithmetic<T>::value,
                  "toMatrix: T must be a number type such as int, float or double");

    Matrix result(R, C);
    for (std::size_t i = 0; i < R; ++i) {
        for (std::size_t j = 0; j < C; ++j) {
            result(i, j) = static_cast<double>(data[i][j]);
        }
    }
    return result;
}
// mapElements: returns a NEW Matrix where every element x is replaced by f(x).
// The original matrix is not changed.
//
//   Matrix squares = mapElements(A, [](double x) { return x * x; });
//   Matrix scaled  = mapElements(A, [k](double x) { return k * x; });
//
// 'Function' can be a lambda, a normal function, or any object you can call
// with one double and that gives back a number.
//
// Throws std::invalid_argument if the matrix is empty.
template <typename Function>
Matrix mapElements(const Matrix& m, Function f) {
    if (m.rows() == 0 || m.columns() == 0) {
        throw std::invalid_argument("mapElements: the matrix is empty");
    }
    Matrix result(m.rows(), m.columns());
    for (std::size_t i = 0; i < m.rows(); ++i) {
        for (std::size_t j = 0; j < m.columns(); ++j) {
            result(i, j) = f(m(i, j));
        }
    }
    return result;
}
// allElements: true if test(x) is true for EVERY element x, otherwise false.
// Stops at the first element that fails.
//
//   bool ok = allElements(A, [](double x) { return std::isfinite(x); });
//   // useful to check for NaN or infinity before solving a system
//
// An empty matrix has no elements to fail, so the answer is true.
template <typename Predicate>
bool allElements(const Matrix& m, Predicate test) {
    for (std::size_t i = 0; i < m.rows(); ++i) {
        for (std::size_t j = 0; j < m.columns(); ++j) {
            if (!test(m(i, j))) {
                return false;
            }
        }
    }
    return true;
}
}  // namespace sat::num
