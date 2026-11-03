#pragma once
// Public interface and template implementations for the Linear Solvers module.
#include <cmath>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace sat_trajectory {
template<class T> using Vector=std::vector<T>;
template<class T> using Matrix=std::vector<std::vector<T>>;

template<class T> struct SolverOptions {
    T pivot_tolerance=static_cast<T>(1e-12);
    int refinement_iterations=2;
};

template<class T> void checkSystem(const Matrix<T>& A,const Vector<T>& b) {
    const auto n=A.size();
    if(n==0 || b.size()!=n) throw std::invalid_argument("Invalid system dimensions");
    for(const auto& row:A) {
        if(row.size()!=n) throw std::invalid_argument("Matrix must be square");
        for(T v:row) if(!std::isfinite(v)) throw std::invalid_argument("Non-finite matrix value");
    }
    for(T v:b) if(!std::isfinite(v)) throw std::invalid_argument("Non-finite vector value");
}

// Residual convention used here: r = A*x - b.
template<class T> Vector<T> calculateResidual(const Matrix<T>& A,const Vector<T>& x,const Vector<T>& b) {
    checkSystem(A,b);
    if(x.size()!=A.size()) throw std::invalid_argument("Solution vector has wrong size");
    Vector<T> r(A.size(),T{});
    for(std::size_t i=0;i<A.size();++i) {
        for(std::size_t j=0;j<A.size();++j) r[i]+=A[i][j]*x[j];
        r[i]-=b[i];
    }
    return r;
}
template<class T> T vectorNorm(const Vector<T>& v) {
    T sum{};
    for(T value:v) sum+=value*value;
    return std::sqrt(sum);
}
template<class T> T residualNorm(const Matrix<T>& A,const Vector<T>& x,const Vector<T>& b) {
    return vectorNorm(calculateResidual(A,x,b));
}

// Abstract parent class. Derived classes provide their own solve() function.
template<class T> class LinearSolver {
public:
    virtual ~LinearSolver()=default;
    virtual Vector<T> solve(const Matrix<T>& A,const Vector<T>& b) const=0;
    virtual std::string name() const=0;
};

template<class T> class ForwardSubstitutionSolver:public LinearSolver<T> {
public:
    explicit ForwardSubstitutionSolver(SolverOptions<T> options={}):options_(options){}
    Vector<T> solve(const Matrix<T>& L,const Vector<T>& b) const override {
        checkSystem(L,b); Vector<T> x(b.size(),T{});
        for(std::size_t i=0;i<L.size();++i) {
            T sum=b[i];
            for(std::size_t j=0;j<i;++j) sum-=L[i][j]*x[j];
            if(std::abs(L[i][i])<=options_.pivot_tolerance) throw std::runtime_error("Small diagonal pivot");
            x[i]=sum/L[i][i];
        }
        return x;
    }
    std::string name() const override { return "Forward substitution"; }
private:
    SolverOptions<T> options_; // Private settings are protected from direct outside changes.
};

template<class T> class BackSubstitutionSolver:public LinearSolver<T> {
public:
    explicit BackSubstitutionSolver(SolverOptions<T> options={}):options_(options){}
    Vector<T> solve(const Matrix<T>& U,const Vector<T>& b) const override {
        checkSystem(U,b); Vector<T> x(b.size(),T{});
        for(std::size_t i=U.size();i-->0;) {
            T sum=b[i];
            for(std::size_t j=i+1;j<U.size();++j) sum-=U[i][j]*x[j];
            if(std::abs(U[i][i])<=options_.pivot_tolerance) throw std::runtime_error("Small diagonal pivot");
            x[i]=sum/U[i][i];
        }
        return x;
    }
    std::string name() const override { return "Back substitution"; }
private:
    SolverOptions<T> options_;
};

template<class T> class GaussianSolver:public LinearSolver<T> {
public:
    explicit GaussianSolver(SolverOptions<T> options={}):options_(options){}
    Vector<T> solve(const Matrix<T>& A,const Vector<T>& b) const override {
        checkSystem(A,b); Matrix<T> U=A; Vector<T> rhs=b; const auto n=U.size();
        for(std::size_t k=0;k<n;++k) {
            // Partial pivoting selects the largest available pivot in this column.
            std::size_t p=k;
            for(std::size_t i=k+1;i<n;++i) if(std::abs(U[i][k])>std::abs(U[p][k])) p=i;
            if(std::abs(U[p][k])<=options_.pivot_tolerance) throw std::runtime_error("Singular or nearly singular matrix");
            if(p!=k) { std::swap(U[k],U[p]); std::swap(rhs[k],rhs[p]); }
            for(std::size_t i=k+1;i<n;++i) {
                T factor=U[i][k]/U[k][k]; U[i][k]=T{};
                for(std::size_t j=k+1;j<n;++j) U[i][j]-=factor*U[k][j];
                rhs[i]-=factor*rhs[k];
            }
        }
        return BackSubstitutionSolver<T>(options_).solve(U,rhs);
    }
    std::string name() const override { return "Gaussian elimination with partial pivoting"; }
private:
    SolverOptions<T> options_;
};

template<class T> class IterativeRefinementSolver:public LinearSolver<T> {
public:
    explicit IterativeRefinementSolver(SolverOptions<T> options={}):options_(options),gaussian_(options){}
    Vector<T> solve(const Matrix<T>& A,const Vector<T>& b) const override {
        checkSystem(A,b);
        if(options_.refinement_iterations<0) throw std::invalid_argument("Negative refinement iteration count");
        Vector<T> x=gaussian_.solve(A,b);
        for(int k=0;k<options_.refinement_iterations;++k) {
            Vector<T> correctionRhs=calculateResidual(A,x,b);
            for(T& v:correctionRhs) v=-v; // Solve A*correction = -(A*x-b).
            Vector<T> correction=gaussian_.solve(A,correctionRhs);
            for(std::size_t i=0;i<x.size();++i) x[i]+=correction[i];
        }
        return x;
    }
    std::string name() const override { return "Iterative refinement"; }
private:
    SolverOptions<T> options_;
    GaussianSolver<T> gaussian_; // This class also contains a solver object (composition).
};
} // namespace sat_trajectory
