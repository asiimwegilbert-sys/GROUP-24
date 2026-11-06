#include "satellite_trajectory/trajectory_solver.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {

double radius(const sat::orbit::OrbitalState& state)
{
    double x = state.position[0];
    double y = state.position[1];
    double z = state.position[2];

    return std::sqrt(
        x*x +
        y*y +
        z*z
    );
}


double specific_energy(
    const sat::orbit::OrbitalState& state,
    double mu)
{
    double r = radius(state);

    double vx = state.velocity[0];
    double vy = state.velocity[1];
    double vz = state.velocity[2];

    double speed_squared =
        vx*vx +
        vy*vy +
        vz*vz;

    return 0.5*speed_squared -
           mu/r;
}

}


int main()
{
    using sat::orbit::OrbitalState;
    using sat::orbit::PropagationOptions;
    using sat::orbit::orbital_period;
    using sat::orbit::propagate_rk4;

    constexpr double mu = 398600.4418;


    // ---------------------------------
    // Test 1: Orbital period
    // ---------------------------------

    double period =
        orbital_period(
            7000.0,
            mu
        );

    if(std::abs(period - 5828.5166) > 0.1)
    {
        std::cerr
            << "Orbital period test failed\n";

        return 1;
    }


    // ---------------------------------
    // Test 2: Circular orbit propagation
    // ---------------------------------

    double orbital_radius = 7000.0;

    double circular_velocity =
        std::sqrt(
            mu/orbital_radius
        );


    OrbitalState initial{
        sat::num::Vector{
            orbital_radius,
            0.0,
            0.0
        },

        sat::num::Vector{
            0.0,
            circular_velocity,
            0.0
        },

        0.0
    };


    PropagationOptions options;

    options.gravitational_parameter = mu;
    options.time_step = 10.0;
    options.steps = 100;
    options.enable_drag = false;


    auto trajectory =
        propagate_rk4(
            initial,
            options
        );


    // Initial state + 100 propagated states
    if(trajectory.size() != options.steps + 1)
    {
        std::cerr
            << "Trajectory size test failed\n";

        return 1;
    }


    // Final time should equal steps * time step
    double expected_time =
        options.steps *
        options.time_step;


    if(std::abs(
        trajectory.back().time -
        expected_time
    ) > 1e-9)
    {
        std::cerr
            << "Trajectory time test failed\n";

        return 1;
    }


    // Radius of an ideal circular orbit
    // should remain close to the initial radius.
    double final_radius =
        radius(
            trajectory.back()
        );


    if(std::abs(
        final_radius -
        orbital_radius
    ) > 5.0)
    {
        std::cerr
            << "Circular orbit stability test failed\n";

        return 1;
    }


    // ---------------------------------
    // Test 3: Atmospheric drag
    // ---------------------------------

    PropagationOptions drag_options =
        options;

    drag_options.enable_drag = true;

    drag_options.earth_radius = 6378.137;

    drag_options.drag_coefficient = 2.2;

    drag_options.cross_sectional_area = 20.0;

    drag_options.satellite_mass = 500.0;

    // Increased slightly for a clear numerical test.
    drag_options.reference_density = 1.0e-9;

    drag_options.reference_altitude =
        orbital_radius -
        drag_options.earth_radius;

    drag_options.scale_height = 60.0;


    auto drag_trajectory =
        propagate_rk4(
            initial,
            drag_options
        );


    double energy_without_drag =
        specific_energy(
            trajectory.back(),
            mu
        );


    double energy_with_drag =
        specific_energy(
            drag_trajectory.back(),
            mu
        );


    if(!(energy_with_drag <
         energy_without_drag))
    {
        std::cerr
            << "Atmospheric drag test failed\n";

        return 1;
    }


    // ---------------------------------
    // Test 4: Invalid input
    // ---------------------------------

    bool invalid_input_caught = false;


    try
    {
        PropagationOptions bad_options =
            options;

        bad_options.time_step = -1.0;


        propagate_rk4(
            initial,
            bad_options
        );
    }
    catch(const std::invalid_argument&)
    {
        invalid_input_caught = true;
    }


    if(!invalid_input_caught)
    {
        std::cerr
            << "Invalid input test failed\n";

        return 1;
    }


    std::cout
        << "Trajectory tests passed\n";


    return 0;
}