#include "sat_trajectory/linear_solvers.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
using namespace sat_trajectory;
bool near(double a,double b){return std::abs(a-b)<1e-8;}
int main(){
    Matrix<double> A{{2,1},{1,3}}; Vector<double> b{5,6};
    GaussianSolver<double> g; auto x=g.solve(A,b);
    assert(near(x[0],1.8)&&near(x[1],1.4));

    // This matrix needs a row swap at the first pivot.
    auto px=g.solve(Matrix<double>{{0,1},{2,1}},Vector<double>{2,4});
    assert(near(px[0],1)&&near(px[1],2));

    BackSubstitutionSolver<double> back;
    auto bx=back.solve(Matrix<double>{{2,1},{0,3}},Vector<double>{5,6});
    assert(near(bx[0],1.5)&&near(bx[1],2));

    ForwardSubstitutionSolver<double> forward;
    auto fx=forward.solve(Matrix<double>{{2,0},{1,3}},Vector<double>{4,7});
    assert(near(fx[0],2)&&near(fx[1],5.0/3.0));

    // Different derived objects are called through the same base-class pointer.
    std::vector<std::unique_ptr<LinearSolver<double>>> solvers;
    solvers.push_back(std::make_unique<GaussianSolver<double>>());
    solvers.push_back(std::make_unique<IterativeRefinementSolver<double>>());
    for(const auto& solver:solvers) {
        auto answer=solver->solve(A,b);
        assert(near(answer[0],1.8)&&near(answer[1],1.4));
        std::cout<<"Passed: "<<solver->name()<<'\n';
    }
    assert(residualNorm(A,x,b)<1e-8);

    bool singular=false;
    try { g.solve(Matrix<double>{{1,2},{2,4}},Vector<double>{3,6}); }
    catch(const std::runtime_error&){singular=true;}
    assert(singular);

    bool badSize=false;
    try { g.solve(A,Vector<double>{5}); }
    catch(const std::invalid_argument&){badSize=true;}
    assert(badSize);

    // Templates allow the same solver to work with float as well as double.
    GaussianSolver<float> gf;
    auto xf=gf.solve(Matrix<float>{{2,0},{0,4}},Vector<float>{6,8});
    assert(std::abs(xf[0]-3.0f)<1e-5f&&std::abs(xf[1]-2.0f)<1e-5f);
    std::cout<<"All linear solver tests passed.\n";
}
