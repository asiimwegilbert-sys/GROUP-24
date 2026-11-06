// examples/interpolation_example.cpp
// Shows how to use the interpolation library in three small examples.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "satellite_trajectory/interpolation.hpp"

using namespace std;

// Prints a list of numbers like {1, 2, 1}
void printList(const vector<double>& v) {
    cout << "{";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << (i + 1 < v.size() ? ", " : "");
    }
    cout << "}";
}

int main() {
    cout << fixed << setprecision(4);

    // Example 1: three points on y = x^2 + x + 1, estimate y at x = 1.5
  
    cout << "Example 1: points on y = x^2 + x + 1\n";
    vector<double> x1 = {0, 1, 2};
    vector<double> y1 = {1, 3, 7};
    double q1 = 1.5;

    vector<double> newton1 = newtonDividedDifferences(x1, y1);
    vector<double> poly1 = polynomialFit(x1, y1);

    cout << "  Lagrange at x = 1.5:  " << lagrangeInterpolate(x1, y1, q1) << "\n";
    cout << "  Newton at x = 1.5:    " << newtonEvaluate(x1, newton1, q1) << "\n";
    cout << "  Newton coefficients:  "; printList(newton1); cout << "\n";
    cout << "  Polynomial a0,a1,a2:  "; printList(poly1);   cout << "\n";
    cout << "  Exact value:          " << q1*q1 + q1 + 1 << "\n\n";

    // Example 2: satellite on a circular orbit (radius 7000 km, period 96 min).
    // x(t) = 7000 * cos(2*pi*t/96). We know x at t = 0, 8, 16, 24 minutes
    // and estimate x at t = 12 minutes.
  
    cout << "Example 2: satellite x-position (km) at sampled times\n";
    const double PI = 3.14159265358979323846;
    vector<double> t = {0, 8, 16, 24};
    vector<double> xpos;
    for (double ti : t) {
        xpos.push_back(7000.0 * cos(2 * PI * ti / 96.0));
        cout << "  t = " << setw(2) << (int)ti << " min,  x = " << setw(9) << xpos.back() << " km\n";
    }
    double tq = 12;
    double estimate = lagrangeInterpolate(t, xpos, tq);
    double exact = 7000.0 * cos(2 * PI * tq / 96.0);
    cout << "  Interpolated x at t = 12 min: " << estimate << " km\n";
    cout << "  Exact x at t = 12 min:        " << exact << " km\n";
    cout << "  Error:                        " << fabs(estimate - exact) << " km\n\n";

    // Example 3: bad input is caught with try / catch
  
    cout << "Example 3: duplicate x-values\n";
    vector<double> badX = {0, 1, 1};
    vector<double> badY = {0, 1, 2};
    try {
        lagrangeInterpolate(badX, badY, 0.5);
    } catch (const invalid_argument& e) {
        cout << "  Caught error: " << e.what() << "\n";
    }

    return 0;
}
