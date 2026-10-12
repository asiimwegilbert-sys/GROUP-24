#pragma once
#include <cstddef>
#include <functional>
namespace sat::num {
using ScalarFunction = std::function<double(double)>;
using ODEFunction = std::function<double(double, double)>;
double rk2_step(const ODEFunction&, double time, double state, double step);
double rk4_step(const ODEFunction&, double time, double state, double step);
double gaussian_quadrature(const ScalarFunction&, double lower, double upper, std::size_t points = 2);
double romberg_integrate(const ScalarFunction&, double lower, double upper, std::size_t levels = 5);
}
