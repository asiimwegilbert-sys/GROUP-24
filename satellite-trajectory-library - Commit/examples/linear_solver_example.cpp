#include "sat_trajectory/linear_solvers.hpp"
#include <iomanip>
#include <iostream>
#include <memory>

// A function template can print vectors containing different numeric types.
template<class T> void printVector(const sat_trajectory::Vector<T>& v){
    std::cout<<"[ ";
    for(T value:v) std::cout<<value<<" ";
    std::cout<<"]\n";
}
int main(){
    using namespace sat_trajectory;
    // Example: 2x + y = 5 and x + 3y = 6.
    Matrix<double> A{{2,1},{1,3}}; Vector<double> b{5,6};
    GaussianSolver<double> gaussian;
    IterativeRefinementSolver<double> refinement;
    auto x=gaussian.solve(A,b);
    auto improved=refinement.solve(A,b);
    std::cout<<std::fixed<<std::setprecision(6);
    std::cout<<gaussian.name()<<": "; printVector(x);
    std::cout<<refinement.name()<<": "; printVector(improved);
    std::cout<<"Residual norm: "<<residualNorm(A,x,b)<<"\n";

    // Runtime polymorphism: call the overridden method through the base type.
    std::unique_ptr<LinearSolver<double>> solver=std::make_unique<GaussianSolver<double>>();
    std::cout<<"Called through base pointer: ";
    printVector(solver->solve(A,b));
}
