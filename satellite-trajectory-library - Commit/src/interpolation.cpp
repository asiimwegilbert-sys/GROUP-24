#include "satellite_trajectory/interpolation.hpp"
#include <stdexcept>
namespace sat::num {
double lagrange_interpolate(const std::vector<double>&,const std::vector<double>&,double){throw std::logic_error("TODO: Lagrange interpolation");}
double newton_interpolate(const std::vector<double>&,const std::vector<double>&,double){throw std::logic_error("TODO: Newton interpolation");}
std::vector<double> polynomial_interpolation_coefficients(const std::vector<double>&,const std::vector<double>&){throw std::logic_error("TODO: polynomial interpolation");}
double evaluate_polynomial(const std::vector<double>&,double){throw std::logic_error("TODO: polynomial evaluation");}
}
