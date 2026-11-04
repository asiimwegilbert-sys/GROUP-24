#include "satellite_trajectory/least_squares.hpp"
#include "satellite_trajectory/decompositions.hpp"

#include <cmath>
#include <stdexcept>

namespace sat::num {

namespace {

Vector back_substitute(const Matrix& upper,const Vector& b){

    std::size_t n=upper.rows();

    if(upper.columns()!=n || b.size()!=n)
        throw std::invalid_argument("Invalid back substitution dimensions");

    Vector x(n,0.0);

    for(std::size_t i=n;i-- >0;){

        double sum=b[i];

        for(std::size_t j=i+1;j<n;++j)
            sum-=upper(i,j)*x[j];

        if(std::abs(upper(i,i))<=1e-12)
            throw std::runtime_error("Least squares matrix is rank deficient");

        x[i]=sum/upper(i,i);
    }

    return x;
}

}


// Solve Ax approximately equal to b
Vector least_squares_solution(const Matrix& A,const Vector& b){

    if(A.rows()!=b.size())
        throw std::invalid_argument("Matrix rows must match vector size");

    if(A.rows()<A.columns())
        throw std::invalid_argument("Least squares requires rows >= columns");

    QRResult qr=qr_decompose(A);

    Matrix qt=qr.q.transpose();

    Vector y=qt*b;

    return back_substitute(qr.r,y);
}

}