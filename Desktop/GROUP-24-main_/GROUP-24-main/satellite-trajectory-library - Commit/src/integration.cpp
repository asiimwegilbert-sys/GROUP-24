#include "satellite_trajectory/integration.hpp"
#include <cmath>
#include <vector>
#include <iostream>

namespace sat::num {

// 1. Base Class (Parent) - Stores basic simulation configurations
class TrajectorySolver {
protected:
    double time_step; // dt

public:
    // Simple constructor to set our step size
    TrajectorySolver(double dt) {
        time_step = dt;
    }

    // Basic helper check using simple if-statements
    bool validate_inputs(const std::vector<double>& state) {
        if (state.empty()) {
            std::cout << "Warning: No state data!" << std::endl;
            return false;
        }
        if (time_step <= 0.0) {
            std::cout << "Warning: Bad time step!" << std::endl;
            return false;
        }
        return true;
    }
};

class MidpointSolver : public TrajectorySolver {
public:
    // Constructor calling the parent configuration
    MidpointSolver(double dt) : TrajectorySolver(dt) {}

    // Simple implementation of the RK2 logic inside a class method
    State compute_rk2_step(const ODEFunction& f, double t, const State& y) {
        State k1 = f(t, y);
        
        State y_mid(y.size());
        for (size_t i = 0; i < y.size(); ++i) {
            y_mid[i] = y[i] + 0.5 * time_step * k1[i];
        }
        
        State k2 = f(t + 0.5 * time_step, y_mid);
        
        State next_state(y.size());
        for (size_t i = 0; i < y.size(); ++i) {
            next_state[i] = y[i] + time_step * k2[i];
        }
        return next_state;
    }
};

State rk2_step(const ODEFunction& f, double t, const State& y, double dt) {
    MidpointSolver solver(dt);
    if (!solver.validate_inputs(y)) {
        return y;
    }
    return solver.compute_rk2_step(f, t, y);
}

// (The remaining advanced functions are routed here to be converted to classes in Week 4)
State rk4_step(const ODEFunction& f, double t, const State& y, double dt) {
    return y; 
}
double gaussian_quadrature(const ScalarFunction& f, double lower, double upper) {
    return 0.0; 
}
double romberg_integrate(const ScalarFunction& f, double lower, double upper) {
    return 0.0; 
}

} // namespace sat::num
