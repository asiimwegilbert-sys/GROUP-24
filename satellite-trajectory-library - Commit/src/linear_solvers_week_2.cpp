module;
#include <algorithm>
#include <cmath>
#include <stdexcept>

module sat_trajectory.linear_solvers;

namespace sat_trajectory
{
    Vector backSubstitution(
        const Matrix& U,
        const Vector& b,
        SolverOptions options)
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

            if (std::abs(U[i][i]) <= options.pivot_tolerance)
            {
                throw std::runtime_error("Zero or very small pivot");
            }

            x[i] = sum / U[i][i];
        }

        return x;
    }

    Vector solveGaussian(
        const Matrix& A,
        const Vector& b,
        SolverOptions options)
    {
        std::size_t n = A.size();

        if (n == 0 || b.size() != n)
        {
            throw std::invalid_argument("Invalid system dimensions");
        }

        for (const auto& row : A)
        {
            if (row.size() != n)
            {
                throw std::invalid_argument("Matrix must be square");
            }
        }

        Matrix U = A;
        Vector rhs = b;

        for (std::size_t k = 0; k < n; ++k)
        {
            std::size_t pivotRow = k;

            // Find the largest value in the current column.
            for (std::size_t i = k + 1; i < n; ++i)
            {
                if (std::abs(U[i][k]) > std::abs(U[pivotRow][k]))
                {
                    pivotRow = i;
                }
            }

            if (std::abs(U[pivotRow][k]) <= options.pivot_tolerance)
            {
                throw std::runtime_error(
                    "Singular or nearly singular matrix");
            }

            // Swap rows when a better pivot is found.
            if (pivotRow != k)
            {
                std::swap(U[k], U[pivotRow]);
                std::swap(rhs[k], rhs[pivotRow]);
            }

            // Eliminate values below the pivot.
            for (std::size_t i = k + 1; i < n; ++i)
            {
                double factor = U[i][k] / U[k][k];

                U[i][k] = 0.0;

                for (std::size_t j = k + 1; j < n; ++j)
                {
                    U[i][j] -= factor * U[k][j];
                }

                rhs[i] -= factor * rhs[k];
            }
        }

        return backSubstitution(U, rhs, options);
    }
}
