module;
#include <cmath>
#include <stdexcept>

module sat_trajectory.linear_solvers;

namespace sat_trajectory
{
    Vector backSubstitution(const Matrix& U, const Vector& b)
    {
        std::size_t n = U.size();

        if (n == 0 || b.size() != n)
        {
            throw std::invalid_argument("Invalid system size");
        }

        for (const auto& row : U)
        {
            if (row.size() != n)
            {
                throw std::invalid_argument("Matrix must be square");
            }
        }

        Vector x(n, 0.0);

        for (std::size_t i = n; i-- > 0;)
        {
            double sum = b[i];

            for (std::size_t j = i + 1; j < n; ++j)
            {
                sum -= U[i][j] * x[j];
            }

            if (std::abs(U[i][i]) < 1e-12)
            {
                throw std::runtime_error("Zero or very small diagonal value");
            }

            x[i] = sum / U[i][i];
        }

        return x;
    }
}
