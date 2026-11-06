#include "satellite_trajectory/iterative_solvers.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
int failures = 0;
void check(bool condition, const std::string& message) {
    if (condition) std::cout << "PASS: " << message << '\n';
    else { std::cerr << "FAIL: " << message << '\n'; ++failures; }
}
bool near(double a, double b, double tol = 1e-7) { return std::abs(a-b) <= tol; }
bool vector_near(const sat::num::Vector& a, const sat::num::Vector& b) {
    if (a.size() != b.size()) return false;
    for (std::size_t i=0; i<a.size(); ++i) if (!near(a[i], b[i])) return false;
    return true;
}
}

int main() {
    using namespace sat::num;
    const Matrix A{{4.0, 1.0}, {2.0, 3.0}};
    const Vector b{1.0, 2.0};
    const Vector initial{0.0, 0.0};
    const Vector expected{0.1, 0.6};
    IterationOptions options;
    options.tolerance = 1e-10;
    options.max_iterations = 1000;

    const auto j = jacobi(A, b, initial, options);
    check(j.converged && vector_near(j.solution, expected), "Jacobi converges to the known solution");
    check(j.iterations > 0 && j.iterations <= options.max_iterations, "Jacobi reports its iteration count");

    const auto gs = gauss_seidel(A, b, initial, options);
    check(gs.converged && vector_near(gs.solution, expected), "Gauss-Seidel converges to the known solution");
    check(gs.iterations > 0 && gs.iterations <= options.max_iterations, "Gauss-Seidel reports its iteration count");

    const Matrix diagonal{{5.0, 0.0}, {0.0, 2.0}};
    const auto power = power_iteration(diagonal, Vector{1.0, 1.0}, options);
    check(power.converged, "Power iteration reports convergence for a diagonal matrix");
    check(near(std::abs(power.solution[0]), 1.0, 1e-6), "Power iteration approaches the dominant eigenvector");

    bool bad_dimensions = false;
    try { (void)jacobi(A, Vector{1.0}, initial, options); }
    catch (const std::invalid_argument&) { bad_dimensions = true; }
    check(bad_dimensions, "Jacobi rejects mismatched vector dimensions");

    bool zero_diagonal = false;
    try { (void)gauss_seidel(Matrix{{0.0, 1.0}, {1.0, 2.0}}, b, initial, options); }
    catch (const std::runtime_error&) { zero_diagonal = true; }
    check(zero_diagonal, "Gauss-Seidel rejects a zero diagonal pivot");

    IterationOptions no_iterations = options;
    no_iterations.max_iterations = 0;
    const auto limited = jacobi(A, b, initial, no_iterations);
    check(!limited.converged, "Jacobi reports non-convergence when iteration limit is zero");

    if (failures == 0) { std::cout << "\nAll iterative solver tests passed.\n"; return 0; }
    std::cerr << failures << " iterative solver test(s) failed.\n";
    return 1;
}
