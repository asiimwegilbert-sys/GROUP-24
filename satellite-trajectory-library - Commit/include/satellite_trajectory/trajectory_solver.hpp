#pragma once

#include <cstddef>
#include <vector>

#include "satellite_trajectory/orbital_state.hpp"

namespace sat::orbit {

struct PropagationOptions {
    double gravitational_parameter{398600.4418};
    double time_step{1.0};
    std::size_t steps{1};

    // Atmospheric drag options
    bool enable_drag{false};

    double earth_radius{6378.137};          // km
    double drag_coefficient{2.2};
    double cross_sectional_area{4.0};       // m^2
    double satellite_mass{500.0};           // kg

    // Simple local exponential atmosphere model
    double reference_altitude{400.0};       // km
    double reference_density{4.0e-12};      // kg/m^3
    double scale_height{60.0};               // km
};

std::vector<OrbitalState> propagate_rk2(
    const OrbitalState& initial,
    const PropagationOptions& options = {}
);

std::vector<OrbitalState> propagate_rk4(
    const OrbitalState& initial,
    const PropagationOptions& options = {}
);

double orbital_period(
    double semi_major_axis,
    double gravitational_parameter = 398600.4418
);

}