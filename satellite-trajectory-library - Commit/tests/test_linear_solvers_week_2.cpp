import sat_trajectory.linear_solvers;

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

bool closeEnough(double a, double b)
{
    return std::abs(a - b) < 1e-9;
}

int main()
{
    using sat_trajectory::Matrix;
    using sat_trajectory::Vector;

    // Test 1:
    // 2x + y = 5
    // x + 3y = 6
    //
    // Expected:
    // x = 1.8
    // y = 1.4

    Matrix A1{
        {2.0, 1.0},
        {1.0, 3.0}
    };

    Vector b1{5.0, 6.0};

    Vector x1 = sat_trajectory::solveGaussian(A1, b1);

    assert(closeEnough(x1[0], 1.8));
    assert(closeEnough(x1[1], 1.4));

    std::cout << "Normal system test passed.\n";

    // Test 2:
    // y = 2
    // 2x + y = 4
    //
    // The first pivot is zero, so rows must be swapped.
    //
    // Expected:
    // x = 1
    // y = 2

    Matrix A2{
        {0.0, 1.0},
        {2.0, 1.0}
    };

    Vector b2{2.0, 4.0};

    Vector x2 = sat_trajectory::solveGaussian(A2, b2);

    assert(closeEnough(x2[0], 1.0));
    assert(closeEnough(x2[1], 2.0));

    std::cout << "Partial pivoting test passed.\n";

    // Test 3: singular matrix.
    Matrix A3{
        {1.0, 2.0},
        {2.0, 4.0}
    };

    Vector b3{3.0, 6.0};

    try
    {
        sat_trajectory::solveGaussian(A3, b3);
        assert(false);
    }
    catch (const std::runtime_error&)
    {
        std::cout << "Singular matrix test passed.\n";
    }

    std::cout << "Week 2 tests passed.\n";

    return 0;
}
