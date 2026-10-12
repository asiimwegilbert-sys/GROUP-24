#pragma once
#include <vector>
#include "satellite_trajectory/orbital_state.hpp"
namespace sat::orbit {
struct PropagationOptions { double gravitational_parameter{398600.4418}; double time_step{1.0}; std::size_t steps{1}; };
std::vector<OrbitalState> propagate_rk2(const OrbitalState&, const PropagationOptions& = {});
std::vector<OrbitalState> propagate_rk4(const OrbitalState&, const PropagationOptions& = {});
double orbital_period(double semi_major_axis, double gravitational_parameter = 398600.4418);
}
