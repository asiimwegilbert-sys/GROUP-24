#include "satellite_trajectory/trajectory_solver.hpp"
#include <stdexcept>
#include <cmath>

namespace sat::orbit {

namespace {

void validate_propagation_inputs(const OrbitalState& initial,const PropagationOptions& options){
    if(initial.position.size()!=3 || initial.velocity.size()!=3)
        throw std::invalid_argument("Position and velocity must have 3 components");

    if(options.time_step<=0.0)
        throw std::invalid_argument("Time step must be positive");

    if(options.steps==0)
        throw std::invalid_argument("Number of steps must be positive");

    if(options.gravitational_parameter<=0.0)
        throw std::invalid_argument("Gravitational parameter must be positive");
}

}

std::vector<OrbitalState> propagate_rk2(const OrbitalState& initial,const PropagationOptions& options){
    validate_propagation_inputs(initial,options);
    throw std::logic_error("TODO: satellite RK2");
}

std::vector<OrbitalState> propagate_rk4(const OrbitalState& initial,const PropagationOptions& options){
    validate_propagation_inputs(initial,options);
    throw std::logic_error("TODO: satellite RK4");
}

double orbital_period(double semi_major_axis,double gravitational_parameter){
    if(semi_major_axis<=0.0 || gravitational_parameter<=0.0)
        throw std::invalid_argument("Orbital parameters must be positive");

    constexpr double pi=3.14159265358979323846;
    return 2.0*pi*std::sqrt((semi_major_axis*semi_major_axis*semi_major_axis)/gravitational_parameter);
}

}