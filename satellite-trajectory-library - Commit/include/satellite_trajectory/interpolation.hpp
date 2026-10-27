// include/sat_trajectory/interpolation.hpp

#pragma once   // stops this file from being included twice

#include <vector>

// Lagrange method: returns the interpolated y-value at the point xq.
double lagrangeInterpolate(const std::vector<double>& x,
                           const std::vector<double>& y,
                           double xq);

// Newton method, step 1: returns the divided-difference coefficients.
std::vector<double> newtonDividedDifferences(const std::vector<double>& x,
                                             const std::vector<double>& y);

// Newton method, step 2: uses those coefficients to find the y-value at xq.
double newtonEvaluate(const std::vector<double>& x,
                      const std::vector<double>& coeffs,
                      double xq);

// Polynomial fit: returns {a0, a1, a2, ...} for the polynomial
// a0 + a1*x + a2*x^2 + ... that passes through every point.
std::vector<double> polynomialFit(const std::vector<double>& x,
                                  const std::vector<double>& y);
