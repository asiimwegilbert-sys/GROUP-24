// Interpolate satellite positions between RK4 sample times.
// Week 5 demo: use interpolation to estimate a satellite's position
// BETWEEN the time steps computed by the RK4 propagator.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include "satellite_trajectory/interpolation.hpp"
#include "satellite_trajectory/trajectory_solver.hpp"

using namespace std;
using sat::num::Vector;
using sat::orbit::OrbitalState;
using sat::orbit::PropagationOptions;

int main() {
    cout << fixed << setprecision(3);
    const double mu = 398600.4418;            // Earth's gravitational parameter (km^3/s^2)

    // ---------------------------------------------------------------
    // Step 1: a circular orbit, radius 7000 km, starting on the x-axis.
    // For a circular orbit the speed is v = sqrt(mu / r).
    // ---------------------------------------------------------------
    double r = 7000.0;
    double v = sqrt(mu / r);
    OrbitalState start{Vector{r, 0.0, 0.0}, Vector{0.0, v, 0.0}, 0.0};

    // ---------------------------------------------------------------
    // Step 2: run RK4 with a big step (300 s) for 8 steps = 2400 s.
    // This gives 9 samples: t = 0, 300, 600, ... 2400.
    // ---------------------------------------------------------------
    PropagationOptions options;
    options.time_step = 300.0;
    options.steps = 8;
    vector<OrbitalState> samples = sat::orbit::propagate_rk4(start, options);

    // Copy the times and the x, y positions into plain lists for interpolation
    vector<double> t, x, y;
    for (const OrbitalState& s : samples) {
        t.push_back(s.time);
        x.push_back(s.position[0]);
        y.push_back(s.position[1]);
    }

    cout << "RK4 samples (every 300 s):\n";
    for (size_t i = 0; i < t.size(); i++) {
        cout << "  t = " << setw(4) << (int)t[i] << " s   x = " << setw(10) << x[i]
             << " km   y = " << setw(10) << y[i] << " km\n";
    }

    // ---------------------------------------------------------------
    // Step 3: estimate the position at times that are NOT samples,
    // and compare with the exact circular-orbit position:
    //   x = r cos(w t),  y = r sin(w t),  where w = sqrt(mu / r^3)
    // ---------------------------------------------------------------
    double w = sqrt(mu / (r * r * r));
    double queries[] = {150.0, 1050.0, 2250.0};

    cout << "\nInterpolated position between samples:\n";
    for (double tq : queries) {
        double xi = lagrangeInterpolate(t, x, tq);
        double yi = lagrangeInterpolate(t, y, tq);
        double xe = r * cos(w * tq);
        double ye = r * sin(w * tq);
        double error = hypot(xi - xe, yi - ye);
        double radius = hypot(xi, yi);
        cout << "  t = " << setw(4) << (int)tq << " s\n";
        cout << "    interpolated: x = " << setw(10) << xi << ", y = " << setw(10) << yi << " km\n";
        cout << "    exact:        x = " << setw(10) << xe << ", y = " << setw(10) << ye << " km\n";
        cout << "    position error: " << scientific << setprecision(3) << error << " km"
             << fixed << setprecision(3) << ",  radius = " << radius << " km\n";
    }

    // ---------------------------------------------------------------
    // Step 4: the Newton method gives the same answer as Lagrange.
    // ---------------------------------------------------------------
    vector<double> coeffs = newtonDividedDifferences(t, x);
    double newtonX = newtonEvaluate(t, coeffs, 150.0);
    cout << "\nNewton x at t = 150 s: " << newtonX
         << " km (Lagrange: " << lagrangeInterpolate(t, x, 150.0) << " km)\n";
    return 0;
}
