#pragma once

#include <cstddef>
#include <functional>
#include <vector>

namespace sat::num {


using State = std::vector<double>;
using ScalarFunction = std::function<double(double)>;
using ODEFunction = std::function<State(double, const State&)>;


State rk2_step(
    const ODEFunction& f,
    double time,
    const State& state,
    double step
);

State rk4_step(
    const ODEFunction& f,
    double time,
    const State& state,
    double step
);

double gaussian_quadrature(
    const ScalarFunction& f,
    double lower,
    double upper
);

double romberg_integrate(
    const ScalarFunction& f,
    double lower,
    double upper
);

} // namespace sat::num
