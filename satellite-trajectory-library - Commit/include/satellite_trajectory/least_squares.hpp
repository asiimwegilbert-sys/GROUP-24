#pragma once
#include <vector>
#include <cstddef>
#include "satellite_trajectory/matrix.hpp"
namespace sat::num {
std::vector<double> least_squares_polynomial_fit(const std::vector<double>&, const std::vector<double>&, std::size_t degree);
Vector least_squares_solution(const Matrix&, const Vector&);
}
