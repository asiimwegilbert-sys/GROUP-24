#include "satellite_trajectory/iterative_solvers.hpp"
#include <stdexcept>
namespace sat::num {
IterationResult jacobi(const Matrix&,const Vector&,const Vector&,const IterationOptions&){throw std::logic_error("TODO: Jacobi");}
IterationResult gauss_seidel(const Matrix&,const Vector&,const Vector&,const IterationOptions&){throw std::logic_error("TODO: Gauss-Seidel");}
IterationResult power_iteration(const Matrix&,const Vector&,const IterationOptions&){throw std::logic_error("TODO: power iteration");}
}
