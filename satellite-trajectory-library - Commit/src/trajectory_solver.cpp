#include "satellite_trajectory/trajectory_solver.hpp"
#include "satellite_trajectory/integration.hpp"

#include <cmath>
#include <stdexcept>

namespace sat::orbit {

namespace {

using sat::num::State;
using sat::num::ODEFunction;


// Validate trajectory inputs
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
}


// Convert OrbitalState to RK state
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


// Convert RK state back to OrbitalState
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


// Two-body satellite dynamics
ODEFunction two_body_dynamics(double mu)
{
    return [mu](double, const State& state)
    {
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

        if(r<=0.0)
            throw std::invalid_argument(
                "Satellite position magnitude must be positive"
            );

        double factor=
            -mu/(r*r*r);

        double ax=factor*x;
        double ay=factor*y;
        double az=factor*z;

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


// RK2 satellite propagation
std::vector<OrbitalState> propagate_rk2(
    const OrbitalState& initial,
    const PropagationOptions& options)
{
    validate_propagation_inputs(
        initial,
        options
    );

    std::vector<OrbitalState> trajectory;

    State state=to_state(initial);
    double time=initial.time;

    ODEFunction dynamics=
        two_body_dynamics(
            options.gravitational_parameter
        );

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


// RK4 satellite propagation
std::vector<OrbitalState> propagate_rk4(
    const OrbitalState& initial,
    const PropagationOptions& options)
{
    validate_propagation_inputs(
        initial,
        options
    );

    std::vector<OrbitalState> trajectory;

    State state=to_state(initial);
    double time=initial.time;

    ODEFunction dynamics=
        two_body_dynamics(
            options.gravitational_parameter
        );

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

    return 2.0*pi*std::sqrt(
        (semi_major_axis*
         semi_major_axis*
         semi_major_axis)
        /gravitational_parameter
    );
}

}