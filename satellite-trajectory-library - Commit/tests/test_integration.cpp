#include "satellite_trajectory/integration.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

// A basic mock differential equation representing simple linear acceleration
sat::num::State mock_orbit_ode(double t, const sat::num::State& state) {
    sat::num::State derivatives(state.size());
    derivatives[0] = state[1];  // Velocity change
    derivatives[1] = -9.81;     // Constant mock gravity pull acceleration
    return derivatives;
}

int main() {
    std::cout << "[TESTING RUNTIME] Starting Numerical Module Validation..." << std::endl;

    // Initial conditions layout: Position = 1000m, Velocity = 0m/s
    sat::num::State initial_state = {1000.0, 0.0};
    double current_time = 0.0;
    double step_size = 0.1;

    // Run a single simulation step via your ClassicalRK4 child class pointer pipeline
    sat::num::State next_state = sat::num::rk4_step(mock_orbit_ode, current_time, initial_state, step_size);

    // Simple assertion: Verify that the satellite has dropped in altitude due to gravity pull
    assert(next_state[0] < initial_state[0]);
    assert(!next_state.empty());

    std::cout << "[SUCCESS LOG] Test passed! Position changed safely from " 
              << initial_state[0] << " to " << next_state[0] << "m." << std::endl;
    return 0;
}
