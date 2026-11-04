#include "satellite_trajectory/decompositions.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace sat::num {

namespace {

void validate_tolerance(double tol){
    if(!std::isfinite(tol) || tol<=0.0)
        throw std::invalid_argument("Decomposition tolerance must be finite and positive");
}

void validate_finite_matrix(const Matrix& matrix){
    for(std::size_t i=0;i<matrix.rows();++i){
        for(std::size_t j=0;j<matrix.columns();++j){
            if(!std::isfinite(matrix(i,j)))
                throw std::invalid_argument("Matrix entries must all be finite");
        }
    }
}

void validate_nonempty_matrix(const Matrix& matrix){
    if(matrix.rows()==0 || matrix.columns()==0)
        throw std::invalid_argument("Decomposition requires a non-empty matrix");
}

double column_norm(const Matrix& matrix,std::size_t column,std::size_t first_row=0){
    double sum=0.0;

    for(std::size_t i=first_row;i<matrix.rows();++i)
        sum=std::hypot(sum,matrix(i,column));

    return sum;
}

}


// LU decomposition with partial pivoting
LUResult lu_decompose(const Matrix& matrix,double tol){
    validate_tolerance(tol);
    validate_finite_matrix(matrix);
    validate_nonempty_matrix(matrix);

    if(matrix.rows()!=matrix.columns())
        throw std::invalid_argument("LU decomposition requires a square matrix");

    std::size_t n=matrix.rows();

    Matrix upper=matrix;
    Matrix lower=Matrix::identity(n);

    std::vector<std::size_t> permutation(n);

    for(std::size_t i=0;i<n;++i)
        permutation[i]=i;

    int swap_count=0;

    for(std::size_t k=0;k<n;++k){

        std::size_t pivot_row=k;
        double pivot_size=std::abs(upper(k,k));

        for(std::size_t i=k+1;i<n;++i){

            double candidate=std::abs(upper(i,k));

            if(candidate>pivot_size){
                pivot_size=candidate;
                pivot_row=i;
            }
        }

        if(pivot_size<=tol)
            throw std::runtime_error("LU decomposition failed: matrix is singular");

        if(pivot_row!=k){

            for(std::size_t j=0;j<n;++j)
                std::swap(upper(k,j),upper(pivot_row,j));

            for(std::size_t j=0;j<k;++j)
                std::swap(lower(k,j),lower(pivot_row,j));

            std::swap(permutation[k],permutation[pivot_row]);
            ++swap_count;
        }

        for(std::size_t i=k+1;i<n;++i){

            double multiplier=upper(i,k)/upper(k,k);

            lower(i,k)=multiplier;
            upper(i,k)=0.0;

            for(std::size_t j=k+1;j<n;++j)
                upper(i,j)-=multiplier*upper(k,j);
        }
    }

    return {lower,upper,permutation,swap_count};
}


// Cholesky decomposition
LUResult cholesky_decompose(const Matrix& matrix,double tol){
    validate_tolerance(tol);
    validate_finite_matrix(matrix);
    validate_nonempty_matrix(matrix);

    if(matrix.rows()!=matrix.columns())
        throw std::invalid_argument("Cholesky decomposition requires a square matrix");

    std::size_t n=matrix.rows();
    double matrix_scale=0.0;

    for(std::size_t i=0;i<n;++i){
        for(std::size_t j=0;j<n;++j)
            matrix_scale=std::max(matrix_scale,std::abs(matrix(i,j)));
    }

    double symmetry_tol=tol*std::max(1.0,matrix_scale);

    for(std::size_t i=0;i<n;++i){
        for(std::size_t j=i+1;j<n;++j){

            if(std::abs(matrix(i,j)-matrix(j,i))>symmetry_tol)
                throw std::invalid_argument("Cholesky decomposition requires a symmetric matrix");
        }
    }

    Matrix lower(n,n);

    for(std::size_t i=0;i<n;++i){

        for(std::size_t j=0;j<=i;++j){

            double sum=matrix(i,j);

            for(std::size_t k=0;k<j;++k)
                sum-=lower(i,k)*lower(j,k);

            if(i==j){

                if(!std::isfinite(sum) || sum<=tol)
                    throw std::runtime_error("Cholesky decomposition failed: matrix is not positive definite");

                lower(i,j)=std::sqrt(sum);
            }

            else{

                if(std::abs(lower(j,j))<=tol)
                    throw std::runtime_error("Cholesky decomposition failed: zero diagonal");

                lower(i,j)=sum/lower(j,j);
            }
        }
    }

    return {lower,lower.transpose(),{},0};
}


// Householder QR decomposition
QRResult qr_decompose(const Matrix& matrix,double tol){
    validate_tolerance(tol);
    validate_finite_matrix(matrix);
    validate_nonempty_matrix(matrix);

    std::size_t m=matrix.rows();
    std::size_t n=matrix.columns();

    if(m<n)
        throw std::invalid_argument("QR decomposition requires rows >= columns");

    Matrix r_work=matrix;
    Matrix q_full=Matrix::identity(m);

    for(std::size_t k=0;k<n;++k){

        double column_scale=std::max(1.0,column_norm(matrix,k));
        double x_norm=column_norm(r_work,k,k);

        if(!std::isfinite(x_norm) || x_norm<=tol*column_scale)
            throw std::runtime_error("QR decomposition failed: linearly dependent columns");

        double alpha=-std::copysign(x_norm,r_work(k,k));

        std::vector<double> v(m-k,0.0);

        for(std::size_t i=k;i<m;++i)
            v[i-k]=r_work(i,k);

        v[0]-=alpha;

        double v_norm=0.0;

        for(double value:v)
            v_norm+=value*value;

        if(!std::isfinite(v_norm) || v_norm<=0.0)
            throw std::runtime_error("QR decomposition failed");

        double beta=2.0/v_norm;

        for(std::size_t j=k;j<n;++j){

            double projection=0.0;

            for(std::size_t i=k;i<m;++i)
                projection+=v[i-k]*r_work(i,j);

            for(std::size_t i=k;i<m;++i)
                r_work(i,j)-=beta*v[i-k]*projection;
        }

        for(std::size_t i=0;i<m;++i){

            double projection=0.0;

            for(std::size_t j=k;j<m;++j)
                projection+=q_full(i,j)*v[j-k];

            for(std::size_t j=k;j<m;++j)
                q_full(i,j)-=beta*projection*v[j-k];
        }
    }

    Matrix q(m,n);
    Matrix r(n,n);

    for(std::size_t i=0;i<m;++i){
        for(std::size_t j=0;j<n;++j)
            q(i,j)=q_full(i,j);
    }

    for(std::size_t i=0;i<n;++i){
        for(std::size_t j=i;j<n;++j)
            r(i,j)=r_work(i,j);
    }

    return {q,r};
}


// Modified Gram-Schmidt QR
QRResult qr_gram_schmidt(const Matrix& matrix,double tol){
    validate_tolerance(tol);
    validate_finite_matrix(matrix);
    validate_nonempty_matrix(matrix);

    std::size_t m=matrix.rows();
    std::size_t n=matrix.columns();

    if(m<n)
        throw std::invalid_argument("Gram-Schmidt requires rows >= columns");

    Matrix q(m,n);
    Matrix r(n,n);

    for(std::size_t j=0;j<n;++j){

        std::vector<double> v(m);

        for(std::size_t i=0;i<m;++i)
            v[i]=matrix(i,j);

        for(std::size_t k=0;k<j;++k){

            double projection=0.0;

            for(std::size_t i=0;i<m;++i)
                projection+=q(i,k)*v[i];

            r(k,j)=projection;

            for(std::size_t i=0;i<m;++i)
                v[i]-=projection*q(i,k);
        }

        double norm=0.0;

        for(double value:v)
            norm=std::hypot(norm,value);

        double scale=std::max(1.0,column_norm(matrix,j));

        if(!std::isfinite(norm) || norm<=tol*scale)
            throw std::runtime_error("Gram-Schmidt failed: linearly dependent columns");

        r(j,j)=norm;

        for(std::size_t i=0;i<m;++i)
            q(i,j)=v[i]/norm;
    }

    return {q,r};
}

// Return only orthogonal Q matrix
Matrix gram_schmidt(const Matrix& matrix,double tol){
    return qr_gram_schmidt(matrix,tol).q;
}

}//namespace sat::num
