#include "satellite_trajectory/least_squares.hpp"
#include <cmath>
#include <iostream>

int main(){
    using namespace sat::num;

    Matrix A{{1.0,1.0},
             {1.0,2.0},
             {1.0,3.0}};

    Vector b{1.0,2.0,2.0};

    Vector solution=least_squares_solution(A,b);

    if(solution.size()!=2 ||
       std::abs(solution[0]-0.6666667)>0.001 ||
       std::abs(solution[1]-0.5)>0.001){
        std::cerr<<"Least-squares solution test failed\n";
        return 1;
    }

    std::vector<double> x{0.0,1.0,2.0};
    std::vector<double> y{1.0,3.0,5.0};

    std::vector<double> coefficients=
        least_squares_polynomial_fit(x,y,1);

    if(coefficients.size()!=2 ||
       std::abs(coefficients[0]-1.0)>0.001 ||
       std::abs(coefficients[1]-2.0)>0.001){
        std::cerr<<"Least-squares polynomial fit test failed\n";
        return 1;
    }

    std::cout<<"Least-squares tests passed\n";
    return 0;
}
