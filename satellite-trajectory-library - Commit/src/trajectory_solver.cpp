#include "satellite_trajectory/trajectory_solver.hpp"
#include <stdexcept>
#include <cmath>
namespace sat::orbit {
std::vector<OrbitalState> propagate_rk2(const OrbitalState&,const PropagationOptions&){throw std::logic_error("TODO: satellite RK2");}
std::vector<OrbitalState> propagate_rk4(const OrbitalState&,const PropagationOptions&){throw std::logic_error("TODO: satellite RK4");}
double orbital_period(double semi_major_axis,double gravitational_parameter){
    if(semi_major_axis<=0.0 || gravitational_parameter<=0.0)
        throw std::invalid_argument("Orbital parameters must be positive");

    constexpr double pi=3.14159265358979323846;
    return 2.0*pi*std::sqrt((semi_major_axis*semi_major_axis*semi_major_axis)/gravitational_parameter);
}
}
