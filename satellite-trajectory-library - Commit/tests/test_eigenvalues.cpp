#include "satellite_trajectory/eigenvalues.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

int main(){

    using sat::num::Matrix;
    using sat::num::eigenvalues;


    // Test 1
    Matrix diagonal{
        {2.0,0.0},
        {0.0,5.0}
    };

    auto values1=eigenvalues(diagonal);

    if(std::abs(values1[0]-2.0)>1e-6 ||
       std::abs(values1[1]-5.0)>1e-6){

        std::cerr<<"Diagonal eigenvalue test failed\n";
        return 1;
    }


    // Test 2
    Matrix symmetric{
        {2.0,1.0},
        {1.0,2.0}
    };

    auto values2=eigenvalues(symmetric);

    if(std::abs(values2[0]-1.0)>1e-6 ||
       std::abs(values2[1]-3.0)>1e-6){

        std::cerr<<"Symmetric eigenvalue test failed\n";
        return 1;
    }


    // Test 3
    bool invalid_matrix=false;

    try{
        Matrix rectangular{
            {1.0,2.0,3.0},
            {4.0,5.0,6.0}
        };

        eigenvalues(rectangular);
    }
    catch(const std::invalid_argument&){
        invalid_matrix=true;
    }


    if(!invalid_matrix){
        std::cerr<<"Non-square matrix test failed\n";
        return 1;
    }


    std::cout<<"Eigenvalue tests passed\n";

    return 0;
}
