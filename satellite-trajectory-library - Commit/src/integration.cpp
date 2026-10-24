#include "satellite_trajectory/integration.hpp"
#include <cmath>
#include <vector>
#include <iostream>

namespace sat::num {

// 1. Grandparent Class - Handles baseline data verification (Week 2 Logic)
class BaseSolver {
public:
    bool validate_inputs(const std::vector<double>& state, double dt) {
        if (state.empty()) {
            std::cout << "Error: Empty state!" << std::endl;
            return false;
        }
        if (dt <= 0.0) {
            std::cout << "Error: Bad dt!" << std::endl;
            return false;
        }
        return true;
    }
};

// 2. Parent Class - Demonstrates Multilevel Inheritance & Polymorphism Setup
class NumericalIntegrator : public BaseSolver {
protected:
    double time_step;

public:
    NumericalIntegrator(double dt) {
        time_step = dt;
    }

    // Virtual function to enable runtime polymorphism
    virtual State compute_step(const ODEFunction& f, double t, const State& y) {
        return y; 
    }
};

// 3. Child Class - Completes Multilevel Inheritance tree and Overrides the step
class MidpointSolver : public NumericalIntegrator {
public:
    // Simple constructor passing dt up to the parent
    MidpointSolver(double dt) : NumericalIntegrator(dt) {}

    // Polymorphism in action: Overriding the base execution function for RK2
    State compute_step(const ODEFunction& f, double t, const State& y) override {
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

// --- Group Compatibility Wrapper
State rk2_step(const ODEFunction& f, double t, const State& y, double dt) {
    // Demonstrating polymorphism via a base class pointer
    MidpointSolver concrete_solver(dt);
    NumericalIntegrator* solver_ptr = &concrete_solver;

    // Call validation inherited from Grandparent class
    if (!solver_ptr->validate_inputs(y, dt)) {
        return y;
    }

    // Call overridden algorithm dynamically via polymorphism pointer
    return solver_ptr->compute_step(f, t, y);
}

// (Remaining slots temporarily bypassed to be structured into the OOP tree during Week 4)
State rk4_step(const ODEFunction& f, double t, const State& y, double dt) { return y; }
double gaussian_quadrature(const ScalarFunction& f, double lower, double upper) { return 0.0; }
double romberg_integrate(const ScalarFunction& f, double lower, double upper) { return 0.0; }

} // namespace sat::num
