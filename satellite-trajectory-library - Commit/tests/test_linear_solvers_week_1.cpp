import sat_trajectory.linear_solvers;

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

int main()
{
    using sat_trajectory::Matrix;
    using sat_trajectory::Vector;

    // Test:
    // 2x + y = 5
    //     3y = 6
    //
    // Expected:
    // x = 1.5
    // y = 2.0

    Matrix U{
        {2.0, 1.0},
        {0.0, 3.0}
    };

    Vector b{5.0, 6.0};

    Vector x = sat_trajectory::backSubstitution(U, b);

    assert(std::abs(x[0] - 1.5) < 1e-9);
    assert(std::abs(x[1] - 2.0) < 1e-9);

    std::cout << "Back substitution test passed.\n";

    // Test an invalid matrix.
    Matrix bad{
        {1.0, 2.0},
        {3.0}
    };

    try
    {
        sat_trajectory::backSubstitution(bad, b);
        assert(false);
    }
    catch (const std::invalid_argument&)
    {
        std::cout << "Invalid matrix test passed.\n";
    }

    return 0;
}
