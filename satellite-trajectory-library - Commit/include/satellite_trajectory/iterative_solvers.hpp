#pragma once
#include "satellite_trajectory/matrix.hpp"
namespace sat::num {
struct IterationOptions { double tolerance{1e-10}; std::size_t max_iterations{1000}; };
struct IterationResult { Vector solution; std::size_t iterations{0}; bool converged{false}; };
IterationResult jacobi(const Matrix&, const Vector&, const Vector&, const IterationOptions& = {});
IterationResult gauss_seidel(const Matrix&, const Vector&, const Vector&, const IterationOptions& = {});
IterationResult power_iteration(const Matrix&, const Vector&, const IterationOptions& = {});
}
