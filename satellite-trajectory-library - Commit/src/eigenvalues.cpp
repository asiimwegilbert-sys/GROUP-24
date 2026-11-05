#include "satellite_trajectory/eigenvalues.hpp"
#include "satellite_trajectory/decompositions.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace sat::num {

namespace {

void validate_matrix(const Matrix& matrix){
    if(matrix.rows()==0 || matrix.columns()==0)
        throw std::invalid_argument("Eigenvalue matrix must not be empty");

    if(matrix.rows()!=matrix.columns())
        throw std::invalid_argument("Eigenvalue computation requires a square matrix");

    for(std::size_t i=0;i<matrix.rows();++i){
        for(std::size_t j=0;j<matrix.columns();++j){
            if(!std::isfinite(matrix(i,j)))
                throw std::invalid_argument("Matrix entries must be finite");
        }
    }
}


double off_diagonal_norm(const Matrix& matrix){
    double sum=0.0;

    for(std::size_t i=1;i<matrix.rows();++i){
        for(std::size_t j=0;j<i;++j){
            sum+=matrix(i,j)*matrix(i,j);
        }
    }

    return std::sqrt(sum);
}

}


// Eigenvalues using QR iteration
std::vector<double> eigenvalues(const Matrix& matrix){

    validate_matrix(matrix);

    const double tolerance=1e-10;
    const std::size_t max_iterations=1000;

    Matrix current=matrix;

    for(std::size_t iteration=0;
        iteration<max_iterations;
        ++iteration){

        if(off_diagonal_norm(current)<=tolerance)
            break;

        QRResult qr=qr_decompose(current,tolerance);

        current=qr.r*qr.q;
    }


    if(off_diagonal_norm(current)>tolerance)
        throw std::runtime_error(
            "Eigenvalue computation did not converge"
        );


    std::vector<double> values(current.rows());

    for(std::size_t i=0;i<current.rows();++i)
        values[i]=current(i,i);


    std::sort(values.begin(),values.end());

    return values;
}

}
