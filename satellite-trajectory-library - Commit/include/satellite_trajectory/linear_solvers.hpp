#pragma once
#include "satellite_trajectory/matrix.hpp"
namespace sat::num {
Vector gaussian_elimination(const Matrix&, const Vector&);
Matrix inverse(const Matrix&);
double determinant(const Matrix&);
}
