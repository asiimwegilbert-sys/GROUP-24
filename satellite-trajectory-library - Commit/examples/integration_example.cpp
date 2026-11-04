#include "satellite_trajectory/integration.hpp"
#include <iostream>
#include <iomanip>

// Mock circular orbit tracking derivative function
sat::num::State satellite_circular_ode(double t, const sat::num::State& pos) {
    sat::num::State dpos(2);
    dpos[0] = -std::sin(t); // Mock X-velocity
    dpos[1] = std::cos(t);  // Mock Y-velocity
    return dpos;
}

int main() {
    std::cout << "==================================================" << std::endl;
    // Highlight the exact topics requested by Kakaire Steven
    std::cout << "  SATELLITE TRAJECTORY GENERATION ENGINE DEMO      " << std::endl;
    std::cout << "  Concepts: Multilevel Inheritance, Templates, Poly" << std::endl;
    std::cout << "==================================================" << std::endl;

    sat::num::State state = {1.0, 0.0}; // Initial coordinates
    double t = 0.0;
    double dt = 0.2;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Time(s) \t Coordinate X \t Coordinate Y" << std::endl;
    std::cout << t << " \t\t " << state[0] << " \t\t " << state[1] << std::endl;

    // Run a short 5-step mock trajectory timeline loop using your RK2 class methods
    for (int step = 1; step <= 5; ++step) {
        state = sat::num::rk2_step(satellite_circular_ode, t, state, dt);
        t += dt;
        std::cout << t << " \t\t " << state[0] << " \t\t " << state[1] << std::endl;
    }

    std::cout << "==================================================" << std::endl;
    std::cout << "[SUCCESS] Simulation demonstration finished cleanly!" << std::endl;
    return 0;
}
