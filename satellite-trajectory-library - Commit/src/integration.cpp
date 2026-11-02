#include "satellite_trajectory/integration.hpp"
#include <cmath>
#include <vector>
#include <iostream>

namespace sat::num {

// 1. Grandparent Base Class - Handles Templated Input Data Validation
template <typename T>
class BaseSolver {
public:
    bool validate_inputs(const std::vector<T>& state, T dt) {
        if (state.empty()) {
            std::cout << "Error: Empty state!" << std::endl;
            return false;
        }
        if (dt <= static_cast<T>(0.0)) {
            std::cout << "Error: Bad dt!" << std::endl;
            return false;
        }
        return true;
    }
};

// 2. Parent Class - Structural Base for Templated Vector ODE Solvers
template <typename T>
class TrajectorySolver : public BaseSolver<T> {
protected:
    T time_step;

public:
    TrajectorySolver(T dt) {
        time_step = dt;
    }

    virtual std::vector<T> compute_step(const ODEFunction& f, T t, const std::vector<T>& y) {
        return y;
    }
};

// 3. Child Class A - Runge-Kutta 2nd Order Midpoint Solver using Templates
template <typename T>
class MidpointSolver : public TrajectorySolver<T> {
public:
    MidpointSolver(T dt) : TrajectorySolver<T>(dt) {}

    std::vector<T> compute_step(const ODEFunction& f, T t, const std::vector<T>& y) override {
        std::vector<T> k1 = f(t, y);
        std::vector<T> y_mid(y.size());
        for (size_t i = 0; i < y.size(); ++i) {
            y_mid[i] = y[i] + static_cast<T>(0.5) * this->time_step * k1[i];
        }
        std::vector<T> k2 = f(t + static_cast<T>(0.5) * this->time_step, y_mid);
        std::vector<T> next_state(y.size());
        for (size_t i = 0; i < y.size(); ++i) {
            next_state[i] = y[i] + this->time_step * k2[i];
        }
        return next_state;
    }
};

// 4. Child Class B - Runge-Kutta 4th Order Classical Step Solver using Templates
template <typename T>
class ClassicalRK4Solver : public TrajectorySolver<T> {
public:
    ClassicalRK4Solver(T dt) : TrajectorySolver<T>(dt) {}

    std::vector<T> compute_step(const ODEFunction& f, T t, const std::vector<T>& y) override {
        size_t n = y.size();
        std::vector<T> k1 = f(t, y);

        std::vector<T> y2(n);
        for (size_t i = 0; i < n; ++i) y2[i] = y[i] + static_cast<T>(0.5) * this->time_step * k1[i];
        std::vector<T> k2 = f(t + static_cast<T>(0.5) * this->time_step, y2);

        std::vector<T> y3(n);
        for (size_t i = 0; i < n; ++i) y3[i] = y[i] + static_cast<T>(0.5) * this->time_step * k2[i];
        std::vector<T> k3 = f(t + static_cast<T>(0.5) * this->time_step, y3);

        std::vector<T> y4(n);
        for (size_t i = 0; i < n; ++i) y4[i] = y[i] + this->time_step * k3[i];
        std::vector<T> k4 = f(t + this->time_step, y4);

        std::vector<T> next_state(n);
        for (size_t i = 0; i < n; ++i) {
            next_state[i] = y[i] + (this->time_step / static_cast<T>(6.0)) * (k1[i] + static_cast<T>(2.0) * k2[i] + static_cast<T>(2.0) * k3[i] + k4[i]);
        }
        return next_state;
    }
};

// 5. Separate Independent Base for Scalar Quadrature Area Calculators (Templated)
template <typename T>
class QuadratureIntegrator {
public:
    virtual T integrate(const ScalarFunction& f, T lower, T upper) {
        return static_cast<T>(0.0);
    }
};

// 6. Concrete Subclass - 2-Point Gaussian Quadrature Solver using Templates
template <typename T>
class GaussLegendreSolver : public QuadratureIntegrator<T> {
public:
    T integrate(const ScalarFunction& f, T lower, T upper) override {
        T c1 = static_cast<T>(0.5) * (upper - lower);
        T c2 = static_cast<T>(0.5) * (upper + lower);
        T x1 = static_cast<T>(-1.0 / std::sqrt(3.0));
        T x2 = static_cast<T>(1.0 / std::sqrt(3.0));
        return c1 * (f(c1 * x1 + c2) + f(c1 * x2 + c2));
    }
};

// 7. Concrete Subclass - Romberg Integration Engine using Templates
template <typename T>
class RombergSolver : public QuadratureIntegrator<T> {
public:
    T integrate(const ScalarFunction& f, T lower, T upper) override {
        int max_steps = 5;
        std::vector<T> R1(max_steps, static_cast<T>(0.0)), R2(max_steps, static_cast<T>(0.0));
        T h = upper - lower;
        R1[0] = static_cast<T>(0.5) * h * (f(lower) + f(upper));

        for (int i = 1; i < max_steps; ++i) {
            h /= static_cast<T>(2.0);
            T sum = static_cast<T>(0.0);
            int points = 1 << (i - 1);
            for (int k = 1; k <= points; ++k) {
                sum += f(lower + (2 * k - 1) * h);
            }
            R2[0] = static_cast<T>(0.5) * R1[0] + h * sum;
            for (int j = 1; j <= i; ++j) {
                T factor = static_cast<T>(std::pow(4.0, j));
                R2[j] = (factor * R2[j - 1] - R1[j - 1]) / (factor - static_cast<T>(1.0));
            }
            R1 = R2;
        }
        return R1[max_steps - 1];
    }
};

// --- Group Compatibility Linker Interfaces (Explicitly Instantiated for double) ---
State rk2_step(const ODEFunction& f, double t, const State& y, double dt) {
    MidpointSolver<double> m_solver(dt);
    TrajectorySolver<double>* ptr = &m_solver;
    if (!ptr->validate_inputs(y, dt)) return y;
    return ptr->compute_step(f, t, y);
}

State rk4_step(const ODEFunction& f, double t, const State& y, double dt) {
    ClassicalRK4Solver<double> rk4_solver(dt);
    TrajectorySolver<double>* ptr = &rk4_solver;
    if (!ptr->validate_inputs(y, dt)) return y;
    return ptr->compute_step(f, t, y);
}

double gaussian_quadrature(const ScalarFunction& f, double lower, double upper) {
    GaussLegendreSolver<double> gauss_solver;
    QuadratureIntegrator<double>* ptr = &gauss_solver;
    return ptr->integrate(f, lower, upper);
}

double romberg_integrate(const ScalarFunction& f, double lower, double upper) {
    RombergSolver<double> romberg_solver;
    QuadratureIntegrator<double>* ptr = &romberg_solver;
    return ptr->integrate(f, lower, upper);
}

} // namespace sat::num
