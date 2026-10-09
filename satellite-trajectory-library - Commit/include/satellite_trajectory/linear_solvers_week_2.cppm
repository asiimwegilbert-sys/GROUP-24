module;
#include <vector>

export module sat_trajectory.linear_solvers;

export namespace sat_trajectory
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<std::vector<double>>;

    struct SolverOptions
    {
        double pivot_tolerance = 1e-12;
    };

    Vector backSubstitution(
        const Matrix& U,
        const Vector& b,
        SolverOptions options = {});

    Vector solveGaussian(
        const Matrix& A,
        const Vector& b,
        SolverOptions options = {});
}
