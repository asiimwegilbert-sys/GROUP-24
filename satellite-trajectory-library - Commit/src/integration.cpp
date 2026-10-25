#include "satellite_trajectory/integration.hpp"
#include <cmath>
#include <vector>
#include <iostream>

namespace sat::num {

// 1. Grandparent Base Class - Handles Data Validation
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

// 2. Parent Class - Structural Base for Vector ODE Trajectory Simulators
class TrajectorySolver : public BaseSolver {
protected:
    double time_step;

public:
    TrajectorySolver(double dt) {
        time_step = dt;
    }

    virtual State compute_step(const ODEFunction& f, double t, const State& y) {
        return y;
    }
};

// 3. Child Class A - Runge-Kutta 2nd Order Midpoint Solver
class MidpointSolver : public TrajectorySolver {
public:
    MidpointSolver(double dt) : TrajectorySolver(dt) {}

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

// 4. Child Class B - Runge-Kutta 4th Order Classical Step Solver
class ClassicalRK4Solver : public TrajectorySolver {
public:
    ClassicalRK4Solver(double dt) : TrajectorySolver(dt) {}

    State compute_step(const ODEFunction& f, double t, const State& y) override {
        size_t n = y.size();
        State k1 = f(t, y);

        State y2(n);
        for (size_t i = 0; i < n; ++i) y2[i] = y[i] + 0.5 * time_step * k1[i];
        State k2 = f(t + 0.5 * time_step, y2);

        State y3(n);
        for (size_t i = 0; i < n; ++i) y3[i] = y[i] + 0.5 * time_step * k2[i];
        State k3 = f(t + 0.5 * time_step, y3);

        State y4(n);
        for (size_t i = 0; i < n; ++i) y4[i] = y[i] + time_step * k3[i];
        State k4 = f(t + time_step, y4);

        State next_state(n);
        for (size_t i = 0; i < n; ++i) {
            next_state[i] = y[i] + (time_step / 6.0) * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
        }
        return next_state;
    }
};

// 5. Separate Independent Base for Scalar Quadrature Area Calculators
class QuadratureIntegrator {
public:
    virtual double integrate(const ScalarFunction& f, double lower, double upper) {
        return 0.0;
    }
};

// 6. Concrete Subclass - 2-Point Gaussian Quadrature Solver
class GaussLegendreSolver : public QuadratureIntegrator {
public:
    double integrate(const ScalarFunction& f, double lower, double upper) override {
        double c1 = 0.5 * (upper - lower);
        double c2 = 0.5 * (upper + lower);
        double x1 = -1.0 / std::sqrt(3.0);
        double x2 = 1.0 / std::sqrt(3.0);
        return c1 * (f(c1 * x1 + c2) + f(c1 * x2 + c2));
    }
};

// 7. Concrete Subclass - Romberg Integration Engin
class RombergSolver : public QuadratureIntegrator {
public:
    double integrate(const ScalarFunction& f, double lower, double upper) override {
        int max_steps = 5;
        std::vector<double> R1(max_steps, 0.0), R2(max_steps, 0.0);
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
};

// --- Group Compatibility Linker Interfaces --
State rk2_step(const ODEFunction& f, double t, const State& y, double dt) {
    MidpointSolver m_solver(dt);
    TrajectorySolver* ptr = &m_solver;
    if (!ptr->validate_inputs(y, dt)) return y;
    return ptr->compute_step(f, t, y);
}

State rk4_step(const ODEFunction& f, double t, const State& y, double dt) {
    ClassicalRK4Solver rk4_solver(dt);
    TrajectorySolver* ptr = &rk4_solver;
    if (!ptr->validate_inputs(y, dt)) return y;
    return ptr->compute_step(f, t, y);
}

double gaussian_quadrature(const ScalarFunction& f, double lower, double upper) {
    GaussLegendreSolver gauss_solver;
    QuadratureIntegrator* ptr = &gauss_solver;
    return ptr->integrate(f, lower, upper);
}

double romberg_integrate(const ScalarFunction& f, double lower, double upper) {
    RombergSolver romberg_solver;
    QuadratureIntegrator* ptr = &romberg_solver;
    return ptr->integrate(f, lower, upper);
}

} // namespace sat::num
