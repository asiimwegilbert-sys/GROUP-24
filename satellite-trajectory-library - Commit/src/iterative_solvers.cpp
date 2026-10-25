#include "satellite_trajectory/iterative_solvers.hpp"
#include <stdexcept>
#include <cmath>

namespace sat::num {

IterationResult jacobi(const Matrix& A, const Vector& b, const Vector& x_initial, const IterationOptions& options) {
    // Note: Assuming Matrix has a method to get row count, e.g., rows()
    std::size_t n = A.rows();

    if (n == 0 || b.size() != n || x_initial.size() != n) {
        throw std::invalid_argument("Matrix and vector dimensions must match.");
    }

    Vector x_old = x_initial;
    Vector x_new(n, 0.0);
    
    IterationResult result;
    result.converged = false;
    result.iterations = 0;

    double tolerance = options.tolerance;
    std::size_t max_iterations = options.max_iterations;

    for (std::size_t iter = 0; iter < max_iterations; ++iter) {
        for (std::size_t i = 0; i < n; ++i) {
            double sum = 0.0;
            for (std::size_t j = 0; j < n; ++j) {
                if (i != j) {
                    // Using custom matrix operator() instead of [i][j]
                    sum += A(i, j) * x_old[j];
                }
            }

            if (std::abs(A(i, i)) < 1e-12) {
                throw std::runtime_error("Zero or near-zero diagonal element encountered.");
            }

            x_new[i] = (b[i] - sum) / A(i, i);
        }

        double max_diff = 0.0;
        for (std::size_t i = 0; i < n; ++i) {
            double diff = std::abs(x_new[i] - x_old[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }

        result.iterations = iter + 1;

        if (max_diff < tolerance) {
            result.converged = true;
            result.solution = x_new;
            return result;
        }

        x_old = x_new;
    }

    result.solution = x_new;
    return result;
}

IterationResult gauss_seidel(const Matrix&, const Vector&, const Vector&, const IterationOptions&) {
    throw std::logic_error("TODO: Gauss-Seidel");
}

IterationResult power_iteration(const Matrix&, const Vector&, const IterationOptions&) {
    throw std::logic_error("TODO: power iteration");
}

} // namespace sat::num