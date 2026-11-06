// Explicit instantiations for the commonly used double type.
// Template definitions remain in the public header for other numeric types.
#include "satellite_trajectory/linear_solvers.hpp"
namespace sat_trajectory {
template class ForwardSubstitutionSolver<double>;
template class BackSubstitutionSolver<double>;
template class GaussianSolver<double>;
template class IterativeRefinementSolver<double>;
}
