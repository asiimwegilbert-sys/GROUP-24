#include "satellite_trajectory/integration.hpp"
#include <stdexcept>
namespace sat::num {
double rk2_step(const ODEFunction&,double,double,double){throw std::logic_error("TODO: RK2");}
double rk4_step(const ODEFunction&,double,double,double){throw std::logic_error("TODO: RK4");}
double gaussian_quadrature(const ScalarFunction&,double,double,std::size_t){throw std::logic_error("TODO: Gaussian quadrature");}
double romberg_integrate(const ScalarFunction&,double,double,std::size_t){throw std::logic_error("TODO: Romberg integration");}
}
