#pragma once
#include <vector>
#include <functional>

namespace sat::num {

// A State vector represents position and velocity: [x, y, z, vx, vy, vz]
using State = std::vector<double>;

// ODEFunction signature: derivative = f(time, state)
using ODEFunction = std::function<State(double, const State&)>;

// Scalar function signature for single-variable integration
using ScalarFunction = std::function<double(double)>;

// 1. Runge-Kutta 2nd Order single step
State rk2_step(const ODEFunction& f, double t, const State& y, double dt);

// 2. Runge-Kutta 4th Order single step (Primary Propagator Engine)
State rk4_step(const ODEFunction& f, double t, const State& y, double dt);

// 3. Custom integration methods required by numerical coverage
double gaussian_quadrature(const ScalarFunction& f, double lower, double upper);
double romberg_integrate(const ScalarFunction& f, double lower, double upper);

} // namespace sat::num
