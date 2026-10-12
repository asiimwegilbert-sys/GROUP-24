#include "satellite_trajectory/vector.hpp"
#include <cmath>
#include <stdexcept>
namespace sat::num {
Vector::Vector(std::size_t n,double v):values_(n,v){}
Vector::Vector(std::initializer_list<double> v):values_(v){}
std::size_t Vector::size() const noexcept{return values_.size();}
double& Vector::operator[](std::size_t i){return values_.at(i);}
const double& Vector::operator[](std::size_t i) const{return values_.at(i);}
double Vector::norm() const{double s=0;for(double v:values_)s+=v*v;return std::sqrt(s);}
Vector operator+(const Vector&,const Vector&){throw std::logic_error("TODO: vector addition");}
Vector operator-(const Vector&,const Vector&){throw std::logic_error("TODO: vector subtraction");}
Vector operator*(double,const Vector&){throw std::logic_error("TODO: vector scaling");}
double dot(const Vector&,const Vector&){throw std::logic_error("TODO: dot product");}
}
