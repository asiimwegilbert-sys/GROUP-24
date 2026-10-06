#include "satellite_trajectory/trajectory_solver.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

int main(){
    using sat::orbit::orbital_period;

    double period=orbital_period(7000.0);
    if(std::abs(period-5828.5166)>0.01){
        std::cerr<<"Orbital period calculation test failed\n";
        return 1;
    }

    bool invalid_axis=false;
    try{orbital_period(-7000.0);}
    catch(const std::invalid_argument&){invalid_axis=true;}

    if(!invalid_axis){
        std::cerr<<"Negative semi-major axis test failed\n";
        return 1;
    }

    bool invalid_mu=false;
    try{orbital_period(7000.0,0.0);}
    catch(const std::invalid_argument&){invalid_mu=true;}

    if(!invalid_mu){
        std::cerr<<"Invalid gravitational parameter test failed\n";
        return 1;
    }

    std::cout<<"Trajectory tests passed\n";
    return 0;
}
