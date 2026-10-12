#include "satellite_trajectory/matrix.hpp"
#include <stdexcept>
namespace sat::num {
Matrix::Matrix(std::size_t r,std::size_t c,double v):rows_(r),columns_(c),values_(r*c,v){}
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> a){rows_=a.size();columns_=rows_?a.begin()->size():0;for(const auto& row:a){if(row.size()!=columns_)throw std::invalid_argument("row size mismatch");values_.insert(values_.end(),row.begin(),row.end());}}
std::size_t Matrix::rows()const noexcept{return rows_;}
std::size_t Matrix::columns()const noexcept{return columns_;}
double& Matrix::operator()(std::size_t r,std::size_t c){return values_.at(r*columns_+c);}
const double& Matrix::operator()(std::size_t r,std::size_t c)const{return values_.at(r*columns_+c);}
Matrix Matrix::transpose()const{throw std::logic_error("TODO: transpose");}
Matrix Matrix::identity(std::size_t){throw std::logic_error("TODO: identity");}
Matrix operator+(const Matrix&,const Matrix&){throw std::logic_error("TODO: matrix addition");}
Matrix operator-(const Matrix&,const Matrix&){throw std::logic_error("TODO: matrix subtraction");}
Matrix operator*(const Matrix&,const Matrix&){throw std::logic_error("TODO: matrix multiplication");}
Vector operator*(const Matrix&,const Vector&){throw std::logic_error("TODO: matrix-vector multiplication");}
Matrix operator*(double,const Matrix&){throw std::logic_error("TODO: matrix scaling");}
}
