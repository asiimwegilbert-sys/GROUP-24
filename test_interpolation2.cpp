// tests/test_interpolation.cpp - Week 2 (ARINDA DEOGRATIUS KEVIN)
// Assumes these functions will exist in interpolation.hpp:
//   lagrangeInterpolate, newtonDividedDifferences, newtonEvaluate, polynomialFit
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "sat_trajectory/interpolation.hpp"

using std::vector;

// True if a and b are almost equal
bool close(double a, double b) { return std::fabs(a - b) < 1e-9; }

// Test 1: all three methods must match the cubic y = 2x^3 - 3x^2 + x - 5
bool testKnownCubic() {
    vector<double> x = {-1, 0, 1, 2};
    vector<double> y;
    for (double xi : x) y.push_back(2*xi*xi*xi - 3*xi*xi + xi - 5);
    vector<double> newton = newtonDividedDifferences(x, y);
    vector<double> p = polynomialFit(x, y);   // p = {a0, a1, a2, a3}
    double q = 1.5;
    double expected = 2*q*q*q - 3*q*q + q - 5;
    bool ok = close(lagrangeInterpolate(x, y, q), expected);
    ok = ok && close(newtonEvaluate(x, newton, q), expected);
    ok = ok && close(p[0] + p[1]*q + p[2]*q*q + p[3]*q*q*q, expected);
    return ok;
}

// Returns true if bad input makes the function throw invalid_argument
bool throwsError(const vector<double>& x, const vector<double>& y) {
    try { lagrangeInterpolate(x, y, 0.5); }
    catch (const std::invalid_argument&) { return true; }
    return false;
}

// Test 2: duplicate nodes and mismatched sizes must both throw
bool testBadInput() {
    return throwsError({0, 1, 1}, {0, 1, 2}) && throwsError({0, 1}, {0, 1, 2});
}

int main() {
    bool t1 = testKnownCubic();
    bool t2 = testBadInput();
    std::cout << (t1 ? "PASS" : "FAIL") << ": known cubic\n";
    std::cout << (t2 ? "PASS" : "FAIL") << ": bad input throws\n";
    return (t1 && t2) ? 0 : 1;
}
