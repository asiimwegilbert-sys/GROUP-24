#include "satellite_trajectory/linear_solvers.hpp"
#include <stdexcept>
namespace sat::num {
Vector gaussian_elimination(const Matrix&,const Vector&){throw std::logic_error("TODO: Gaussian elimination");}
Matrix inverse(const Matrix&){throw std::logic_error("TODO: inverse");}
double determinant(const Matrix&){throw std::logic_error("TODO: determinant");}
}
