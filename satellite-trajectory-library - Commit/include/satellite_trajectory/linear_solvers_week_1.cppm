module;
#include <vector>

export module sat_trajectory.linear_solvers;

export namespace sat_trajectory
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<std::vector<double>>;

    Vector backSubstitution(const Matrix& U, const Vector& b);
}
