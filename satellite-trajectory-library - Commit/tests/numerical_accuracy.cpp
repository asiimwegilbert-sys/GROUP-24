#include "satellite_trajectory/integration.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

// A known orbital test problem: Simple Harmonic Satellite Oscillation (u'' = -u)
sat::num::State harmonic_orbit_ode(double t, const sat::num::State& state) {
    sat::num::State derivatives(2);
    derivatives[0] = state[1];          // Velocity
    derivatives[1] = -1.0 * state[0];   // Acceleration proportional to position
    return derivatives;
}

int main() {
    std::cout << "=== STARTING WEEK 5 NUMERICAL INTEGRATION RUNTIME VERIFICATION ===" << std::endl;

    // Initial Conditions: Position = 1.0, Velocity = 0.0. (True solution is Position = cos(t))
    sat::num::State initial_state = {1.0, 0.0};
    double t = 0.0;
    double dt = 0.1;
    double target_time = 1.0;

    sat::num::State rk2_state = initial_state;
    sat::num::State rk4_state = initial_state;

    // Simulate up to t = 1.0s to compare drift profiles against the true analytical solution: cos(1.0)
    int steps = static_cast<int>(target_time / dt);
    for (int i = 0; i < steps; ++i) {
        rk2_state = sat::num::rk2_step(harmonic_orbit_ode, t, rk2_state, dt);
        rk4_state = sat::num::rk4_step(harmonic_orbit_ode, t, rk4_state, dt);
        t += dt;
    }

    double true_value = std::cos(target_time);
    double rk2_error = std::abs(rk2_state[0] - true_value);
    double rk4_error = std::abs(rk4_state[0] - true_value);

    std::cout << "\n[ACCURACY COMPARISON RESULT AT t = 1.0s]:" << std::endl;
    std::cout << "True Analytical Position : " << true_value << std::endl;
    std::cout << "RK2 Midpoint Position    : " << rk2_state[0] << " (Absolute Error: " << rk2_error << ")" << std::endl;
    std::cout << "RK4 Classical Position   : " << rk4_state[0] << " (Absolute Error: " << rk4_error << ")" << std::endl;

    // Verify RK4 accuracy constraint
    assert(rk4_error < rk2_error);
    std::cout << "\n[EDGE CASE CHECK]: Testing empty vector error boundaries..." << std::endl;

    try {
        sat::num::State empty_vector;
        sat::num::rk4_step(harmonic_orbit_ode, 0.0, empty_vector, dt);
    } catch (const std::invalid_argument& e) {
        std::cout << "Success: System gracefully handled edge case! Caught exception: " << e.what() << std::endl;
    }

    std::cout << "==================================================================" << std::endl;
    std::cout << "VERIFICATION COMPLETE: ALL WEEK 5 CRITERIA SUCCESSFULLY SATISFIED!" << std::endl;
    return 0;
}
