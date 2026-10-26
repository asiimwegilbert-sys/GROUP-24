#include "satellite_trajectory/trajectory_solver.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

int main(){
    using namespace sat::orbit;
    using sat::num::Vector;

    // Orbital period test
    double period=orbital_period(7000.0);

    if(std::abs(period-5828.5166)>0.01){
        std::cerr<<"Orbital period calculation test failed\n";
        return 1;
    }

    // Invalid semi-major axis
    bool invalid_axis=false;

    try{
        orbital_period(-7000.0);
    }
    catch(const std::invalid_argument&){
        invalid_axis=true;
    }

    if(!invalid_axis){
        std::cerr<<"Negative semi-major axis test failed\n";
        return 1;
    }

    // Invalid gravitational parameter
    bool invalid_mu=false;

    try{
        orbital_period(7000.0,0.0);
    }
    catch(const std::invalid_argument&){
        invalid_mu=true;
    }

    if(!invalid_mu){
        std::cerr<<"Invalid gravitational parameter test failed\n";
        return 1;
    }


    // Valid satellite state used to test propagation inputs
    OrbitalState state{
        Vector{7000.0,0.0,0.0},
        Vector{0.0,7.546,0.0},
        0.0
    };


    // Invalid position dimension
    bool invalid_position=false;

    try{
        OrbitalState bad_state{
            Vector{7000.0,0.0},
            Vector{0.0,7.546,0.0},
            0.0
        };

        propagate_rk2(bad_state,PropagationOptions{});
    }
    catch(const std::invalid_argument&){
        invalid_position=true;
    }

    if(!invalid_position){
        std::cerr<<"Invalid position dimension test failed\n";
        return 1;
    }


    // Invalid velocity dimension
    bool invalid_velocity=false;

    try{
        OrbitalState bad_state{
            Vector{7000.0,0.0,0.0},
            Vector{0.0,7.546},
            0.0
        };

        propagate_rk2(bad_state,PropagationOptions{});
    }
    catch(const std::invalid_argument&){
        invalid_velocity=true;
    }

    if(!invalid_velocity){
        std::cerr<<"Invalid velocity dimension test failed\n";
        return 1;
    }


    // Invalid time step
    bool invalid_step=false;

    try{
        PropagationOptions options;
        options.time_step=0.0;

        propagate_rk2(state,options);
    }
    catch(const std::invalid_argument&){
        invalid_step=true;
    }

    if(!invalid_step){
        std::cerr<<"Invalid time step test failed\n";
        return 1;
    }


    // Invalid number of steps
    bool invalid_steps=false;

    try{
        PropagationOptions options;
        options.steps=0;

        propagate_rk4(state,options);
    }
    catch(const std::invalid_argument&){
        invalid_steps=true;
    }

    if(!invalid_steps){
        std::cerr<<"Invalid propagation steps test failed\n";
        return 1;
    }


    // Invalid propagation gravitational parameter
    bool invalid_propagation_mu=false;

    try{
        PropagationOptions options;
        options.gravitational_parameter=0.0;

        propagate_rk4(state,options);
    }
    catch(const std::invalid_argument&){
        invalid_propagation_mu=true;
    }

    if(!invalid_propagation_mu){
        std::cerr<<"Invalid propagation gravitational parameter test failed\n";
        return 1;
    }


    std::cout<<"Trajectory validation tests passed\n";
    return 0;
}