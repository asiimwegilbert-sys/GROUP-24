#include "satellite_trajectory/integration.hpp"
#include <cmath>
#include <vector>
#include <iostream>

namespace sat::num {

// Simple input validation check for week 2
bool validate_simulation_inputs(const std::vector<double>& state, double dt) {
    if (state.empty()) {
        std::cout << "Warning: State vector has no data!" << std::endl;
        return false;
    }
    if (dt <= 0.0) {
        std::cout << "Warning: Time step (dt) must be a positive number!" << std::endl;
        return false;
    }
    std::cout << "Inputs checked successfully. Ready for math simulation." << std::endl;
    return true;
}

// 1. Runge-Kutta 2nd Order (RK2 Midpoint Method Step)
State rk2_step(const ODEFunction& f, double t, const State& y, double dt) {
    State k1 = f(t, y);
    
    State y_mid(y.size());
    for (size_t i = 0; i < y.size(); ++i) {
        y_mid[i] = y[i] + 0.5 * dt * k1[i];
    }
    
    State k2 = f(t + 0.5 * dt, y_mid);
    
    State next_state(y.size());
    for (size_t i = 0; i < y.size(); ++i) {
        next_state[i] = y[i] + dt * k2[i];
    }
    return next_state;
}

// 2. Runge-Kutta 4th Order (RK4 Classical Step Engine)
State rk4_step(const ODEFunction& f, double t, const State& y, double dt) {
    size_t n = y.size();
    State k1 = f(t, y);

    State y2(n);
    for (size_t i = 0; i < n; ++i) y2[i] = y[i] + 0.5 * dt * k1[i];
    State k2 = f(t + 0.5 * dt, y2);

    State y3(n);
    for (size_t i = 0; i < n; ++i) y3[i] = y[i] + 0.5 * dt * k2[i];
    State k3 = f(t + 0.5 * dt, y3);

    State y4(n);
    for (size_t i = 0; i < n; ++i) y4[i] = y[i] + dt * k3[i];
    State k4 = f(t + dt, y4);

    State next_state(n);
    for (size_t i = 0; i < n; ++i) {
        next_state[i] = y[i] + (dt / 6.0) * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
    }
    return next_state;
}

// 3. Gaussian Quadrature (2-Point Rule)
double gaussian_quadrature(const ScalarFunction& f, double lower, double upper) {
    double c1 = 0.5 * (upper - lower);
    double c2 = 0.5 * (upper + lower);
    double x1 = -1.0 / std::sqrt(3.0);
    double x2 = 1.0 / std::sqrt(3.0);
    return c1 * (f(c1 * x1 + c2) + f(c1 * x2 + c2));
}

// 4. Romberg Integration (Richardson Extrapolation)
double romberg_integrate(const ScalarFunction& f, double lower, double upper) {
    int max_steps = 5;
    std::vector<double> R1(max_steps, 0.0);
    std::vector<double> R2(max_steps, 0.0);

    double h = upper - lower;
    R1[0] = 0.5 * h * (f(lower) + f(upper));

    for (int i = 1; i < max_steps; ++i) {
        h /= 2.0;
        double sum = 0.0;
        int points = 1 << (i - 1);
        
        for (int k = 1; k <= points; ++k) {
            sum += f(lower + (2 * k - 1) * h);
        }
        
        R2[0] = 0.5 * R1[0] + h * sum;

        for (int j = 1; j <= i; ++j) {
            double factor = std::pow(4.0, j);
            R2[j] = (factor * R2[j - 1] - R1[j - 1]) / (factor - 1.0);
        }
        R1 = R2;
    }
    return R1[max_steps - 1];
}

} // namespace sat::num
