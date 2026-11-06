#include "satellite_trajectory/trajectory_solver.hpp"
#include "satellite_trajectory/integration.hpp"

#include <cmath>
#include <stdexcept>

namespace sat::orbit {

namespace {

using sat::num::State;
using sat::num::ODEFunction;


// Validate propagation inputs
void validate_propagation_inputs(
    const OrbitalState& initial,
    const PropagationOptions& options)
{
    if(initial.position.size()!=3 || initial.velocity.size()!=3)
        throw std::invalid_argument(
            "Position and velocity must have 3 components"
        );

    if(options.time_step<=0.0)
        throw std::invalid_argument(
            "Time step must be positive"
        );

    if(options.steps==0)
        throw std::invalid_argument(
            "Number of steps must be positive"
        );

    if(options.gravitational_parameter<=0.0)
        throw std::invalid_argument(
            "Gravitational parameter must be positive"
        );


    if(options.enable_drag){

        if(options.earth_radius<=0.0)
            throw std::invalid_argument(
                "Earth radius must be positive"
            );

        if(options.drag_coefficient<=0.0)
            throw std::invalid_argument(
                "Drag coefficient must be positive"
            );

        if(options.cross_sectional_area<=0.0)
            throw std::invalid_argument(
                "Cross-sectional area must be positive"
            );

        if(options.satellite_mass<=0.0)
            throw std::invalid_argument(
                "Satellite mass must be positive"
            );

        if(options.reference_density<0.0)
            throw std::invalid_argument(
                "Reference atmospheric density cannot be negative"
            );

        if(options.scale_height<=0.0)
            throw std::invalid_argument(
                "Atmospheric scale height must be positive"
            );
    }
}


// Convert OrbitalState to numerical RK state
State to_state(const OrbitalState& orbital)
{
    return {
        orbital.position[0],
        orbital.position[1],
        orbital.position[2],

        orbital.velocity[0],
        orbital.velocity[1],
        orbital.velocity[2]
    };
}


// Convert numerical state back to OrbitalState
OrbitalState to_orbital_state(
    const State& state,
    double time)
{
    if(state.size()!=6)
        throw std::invalid_argument(
            "Satellite state must contain 6 components"
        );

    return {
        sat::num::Vector{
            state[0],
            state[1],
            state[2]
        },

        sat::num::Vector{
            state[3],
            state[4],
            state[5]
        },

        time
    };
}


// Simple exponential atmospheric-density model
double atmospheric_density(
    double altitude,
    const PropagationOptions& options)
{
    return options.reference_density*
           std::exp(
               -(altitude-options.reference_altitude)
               /options.scale_height
           );
}


// Two-body gravity with optional atmospheric drag
ODEFunction orbital_dynamics(
    const PropagationOptions& options)
{
    return [options](double,const State& state){

        if(state.size()!=6)
            throw std::invalid_argument(
                "Satellite state must contain 6 components"
            );


        double x=state[0];
        double y=state[1];
        double z=state[2];

        double vx=state[3];
        double vy=state[4];
        double vz=state[5];


        double r=std::sqrt(
            x*x+y*y+z*z
        );


        if(!std::isfinite(r) || r<=0.0)
            throw std::invalid_argument(
                "Satellite position magnitude must be positive"
            );


        // ---------------------------------
        // Gravitational acceleration
        // ---------------------------------

        double gravity_factor=
            -options.gravitational_parameter/
            (r*r*r);


        double ax=gravity_factor*x;
        double ay=gravity_factor*y;
        double az=gravity_factor*z;


        // ---------------------------------
        // Atmospheric drag
        // ---------------------------------

        if(options.enable_drag){

            double altitude=
                r-options.earth_radius;


            double density=
                atmospheric_density(
                    altitude,
                    options
                );


            // Convert velocity from km/s to m/s
            double vx_m=vx*1000.0;
            double vy_m=vy*1000.0;
            double vz_m=vz*1000.0;


            double speed_m=
                std::sqrt(
                    vx_m*vx_m+
                    vy_m*vy_m+
                    vz_m*vz_m
                );


            if(speed_m>0.0){

                double drag_factor=
                    -0.5*
                    density*
                    options.drag_coefficient*
                    options.cross_sectional_area/
                    options.satellite_mass*
                    speed_m;


                // Drag acceleration in m/s^2
                double drag_ax_m=
                    drag_factor*vx_m;

                double drag_ay_m=
                    drag_factor*vy_m;

                double drag_az_m=
                    drag_factor*vz_m;


                // Convert m/s^2 to km/s^2
                ax+=drag_ax_m/1000.0;
                ay+=drag_ay_m/1000.0;
                az+=drag_az_m/1000.0;
            }
        }


        return State{
            vx,
            vy,
            vz,
            ax,
            ay,
            az
        };
    };
}

}


// RK2 propagation
std::vector<OrbitalState> propagate_rk2(
    const OrbitalState& initial,
    const PropagationOptions& options)
{
    validate_propagation_inputs(
        initial,
        options
    );


    std::vector<OrbitalState> trajectory;


    State state=
        to_state(initial);

    double time=
        initial.time;


    ODEFunction dynamics=
        orbital_dynamics(options);


    trajectory.push_back(initial);


    for(std::size_t i=0;i<options.steps;++i){

        state=sat::num::rk2_step(
            dynamics,
            time,
            state,
            options.time_step
        );


        time+=options.time_step;


        trajectory.push_back(
            to_orbital_state(
                state,
                time
            )
        );
    }


    return trajectory;
}


// RK4 propagation
std::vector<OrbitalState> propagate_rk4(
    const OrbitalState& initial,
    const PropagationOptions& options)
{
    validate_propagation_inputs(
        initial,
        options
    );


    std::vector<OrbitalState> trajectory;


    State state=
        to_state(initial);

    double time=
        initial.time;


    ODEFunction dynamics=
        orbital_dynamics(options);


    trajectory.push_back(initial);


    for(std::size_t i=0;i<options.steps;++i){

        state=sat::num::rk4_step(
            dynamics,
            time,
            state,
            options.time_step
        );


        time+=options.time_step;


        trajectory.push_back(
            to_orbital_state(
                state,
                time
            )
        );
    }


    return trajectory;
}


// Orbital period
double orbital_period(
    double semi_major_axis,
    double gravitational_parameter)
{
    if(semi_major_axis<=0.0 ||
       gravitational_parameter<=0.0)

        throw std::invalid_argument(
            "Orbital parameters must be positive"
        );


    constexpr double pi=
        3.14159265358979323846;


    return 2.0*pi*
           std::sqrt(
               (semi_major_axis*
                semi_major_axis*
                semi_major_axis)
               /gravitational_parameter
           );
}

}