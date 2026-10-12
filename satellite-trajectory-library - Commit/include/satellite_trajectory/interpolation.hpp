#pragma once
#include <vector>
namespace sat::num {
double lagrange_interpolate(const std::vector<double>& x, const std::vector<double>& y, double query);
double newton_interpolate(const std::vector<double>& x, const std::vector<double>& y, double query);
std::vector<double> polynomial_interpolation_coefficients(const std::vector<double>& x, const std::vector<double>& y);
double evaluate_polynomial(const std::vector<double>& coefficients, double x);
}
