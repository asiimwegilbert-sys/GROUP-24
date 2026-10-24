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

// Week 2: Gauss-Seidel Method
IterationResult gauss_seidel(const Matrix& A, const Vector& b, const Vector& x_initial, const IterationOptions& options) {
    std::size_t n = A.rows();

    if (n == 0 || b.size() != n || x_initial.size() != n) {
        throw std::invalid_argument("Matrix and vector dimensions must match.");
    }

    Vector x = x_initial;
    
    IterationResult result;
    result.converged = false;
    result.iterations = 0;

    double tolerance = options.tolerance;
    std::size_t max_iterations = options.max_iterations;

    for (std::size_t iter = 0; iter < max_iterations; ++iter) {
        Vector x_old = x;

        for (std::size_t i = 0; i < n; ++i) {
            double sum = 0.0;
            for (std::size_t j = 0; j < n; ++j) {
                if (i != j) {
                    sum += A(i, j) * x[j];
                }
            }

            if (std::abs(A(i, i)) < 1e-12) {
                throw std::runtime_error("Zero or near-zero diagonal element encountered.");
            }

            x[i] = (b[i] - sum) / A(i, i);
        }

        double max_diff = 0.0;
        for (std::size_t i = 0; i < n; ++i) {
            double diff = std::abs(x[i] - x_old[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }

        result.iterations = iter + 1;

        if (max_diff < tolerance) {
            result.converged = true;
            result.solution = x;
            return result;
        }
    }

    result.solution = x;
    return result;
}

// Week 3: Power Iteration Method
IterationResult power_iteration(const Matrix& A, const Vector& x_initial, const IterationOptions& options) {
    std::size_t n = A.rows();

    if (n == 0 || x_initial.size() != n || x_initial.size() != n) {
        throw std::invalid_argument("Matrix dimensions and vector size must match.");
    }

    Vector x = x_initial;
    
    IterationResult result;
    result.converged = false;
    result.iterations = 0;

    double tolerance = options.tolerance;
    std::size_t max_iterations = options.max_iterations;

    for (std::size_t iter = 0; iter < max_iterations; ++iter) {
        // Step 1: Multiply matrix A by current vector x -> y = A * x
        Vector y(n, 0.0);
        for (std::size_t i = 0; i < n; ++i) {
            double sum = 0.0;
            for (std::size_t j = 0; j < n; ++j) {
                sum += A(i, j) * x[j];
            }
            y[i] = sum;
        }

        // Step 2: Calculate Euclidean norm of y for normalization
        double norm = 0.0;
        for (std::size_t i = 0; i < n; ++i) {
            norm += y[i] * y[i];
        }
        norm = std::sqrt(norm);

        if (norm < 1e-12) {
            throw std::runtime_error("Vector norm is zero, cannot normalize in power iteration.");
        }

        // Step 3: Normalize to get the new eigenvector approximation -> x_new = y / norm
        Vector x_new(n, 0.0);
        for (std::size_t i = 0; i < n; ++i) {
            x_new[i] = y[i] / norm;
        }

        // Step 4: Check convergence by measuring maximum difference
        double max_diff = 0.0;
        for (std::size_t i = 0; i < n; ++i) {
            double diff = std::abs(x_new[i] - x[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }

        result.iterations = iter + 1;
        x = x_new;

        if (max_diff < tolerance) {
            result.converged = true;
            result.solution = x;
            return result;
        }
    }

    result.solution = x;
    return result;
}