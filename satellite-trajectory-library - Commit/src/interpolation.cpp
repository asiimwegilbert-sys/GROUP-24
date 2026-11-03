// src/interpolation.cpp

#include "sat_trajectory/interpolation.hpp"
#include <stdexcept>   // for std::invalid_argument
using std::vector;

// Helper: checks the input and throws an error if it is bad.
// "static" means only this file can use it.
static void checkInput(const vector<double>& x, const vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("x and y must have the same size");
    }
    if (x.size() < 2) {
        throw std::invalid_argument("at least 2 points are needed");
    }
    // compare every pair of x-values to find duplicates
    for (size_t i = 0; i < x.size(); i++) {
        for (size_t j = i + 1; j < x.size(); j++) {
            if (x[i] == x[j]) {
                throw std::invalid_argument("duplicate x-values are not allowed");
            }
        }
    }
}

// Lagrange: add up y[i] * L_i(xq), where L_i is the "weight" of point i.
// L_i = product over j != i of (xq - x[j]) / (x[i] - 
double lagrangeInterpolate(const vector<double>& x,
                           const vector<double>& y,
                           double xq) {
    checkInput(x, y);

    double total = 0.0;
    for (size_t i = 0; i < x.size(); i++) {
        double weight = 1.0;
        for (size_t j = 0; j < x.size(); j++) {
            if (j != i) {
                weight *= (xq - x[j]) / (x[i] - x[j]);
            }
        }
        total += y[i] * weight;
    }
    return total;
}
// Newton step 1: divided differences.
// Start with the y-values, then repeatedly replace them by differences.
// The first n numbers left over are the Newton coefficients.
vector<double> newtonDividedDifferences(const vector<double>& x,
                                        const vector<double>& y) {
    checkInput(x, y);

    int n = static_cast<int>(x.size());
    vector<double> coeffs = y;               // start as a copy of y

    for (int level = 1; level < n; level++) {
        // go from the end backwards so we don't overwrite values we still need
        for (int i = n - 1; i >= level; i--) {
            coeffs[i] = (coeffs[i] - coeffs[i - 1]) / (x[i] - x[i - level]);
        }
    }
    return coeffs;
}

// Newton step 2: evaluate using nested multiplication (Horner style):
// c0 + (xq-x0)*(c1 + (xq-x1)*(c2 + ...))
double newtonEvaluate(const vector<double>& x,
                      const vector<double>& coeffs,
                      double xq) {
    if (x.size() != coeffs.size() || x.size() < 2) {
        throw std::invalid_argument("x and coeffs must match and have 2+ values");
    }

    int n = static_cast<int>(coeffs.size());
    double result = coeffs[n - 1];           // start from the last coefficient
    for (int i = n - 2; i >= 0; i--) {
        result = result * (xq - x[i]) + coeffs[i];
    }
    return result;
}
// Polynomial fit: turn the Newton form into a0 + a1*x + a2*x^2 + ...
// We build the polynomial one factor at a time:
//   p = c[n-1]
//   then for i = n-2 down to 0:  p = p * (x - x[i]) + c[i]
vector<double> polynomialFit(const vector<double>& x,
                             const vector<double>& y) {
    vector<double> c = newtonDividedDifferences(x, y);   // also checks input

    int n = static_cast<int>(c.size());
    vector<double> p;                         // p[k] is the coefficient of x^k
    p.push_back(c[n - 1]);

    for (int i = n - 2;
