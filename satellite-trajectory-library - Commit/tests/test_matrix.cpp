#include "satellite_trajectory/matrix.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace sat::num;

int main()
{
    // Test 1: Create a matrix
    Matrix a{{1, 2}, {3, 4}};
    assert(a.rows() == 2);
    assert(a.columns() == 2);
    assert(a(0, 0) == 1);
    assert(a(1, 1) == 4);

    // Test 2: Matrix addition
    Matrix b{{5, 6}, {7, 8}};
    Matrix sum = a + b;
    assert(sum(0, 0) == 6);
    assert(sum(1, 1) == 12);

    // Test 3: Matrix subtraction
    Matrix difference = b - a;
    assert(difference(0, 0) == 4);
    assert(difference(1, 1) == 4);

    // Test 4: Matrix multiplication
    Matrix product = a * b;
    assert(product(0, 0) == 19);
    assert(product(0, 1) == 22);
    assert(product(1, 0) == 43);
    assert(product(1, 1) == 50);

    // Test 5: Transpose
    Matrix transposed = a.transpose();
    assert(transposed(0, 1) == 3);
    assert(transposed(1, 0) == 2);

    // Test 6: Identity matrix
    Matrix identity = Matrix::identity(2);
    assert(identity(0, 0) == 1);
    assert(identity(1, 1) == 1);
    assert(identity(0, 1) == 0);
    assert(identity(1, 0) == 0);

    // Test 7: Scalar multiplication
    Matrix scaled = 2.0 * a;
    assert(scaled(0, 0) == 2);
    assert(scaled(1, 1) == 8);

    // Test 8: Matrix-vector multiplication
    Vector v{1, 2};
    Vector result = a * v;
    assert(result[0] == 5);
    assert(result[1] == 11);

    // Test 9: Invalid matrix dimensions
    bool error_caught = false;

    try {
        Matrix wrong{{1, 2, 3}};
        Matrix other{{1, 2}};
        Matrix invalid = wrong + other;
        (void)invalid;
    }
    catch (const std::invalid_argument&) {
        error_caught = true;
    }

    assert(error_caught);

    std::cout << "All Matrix tests passed!" << std::endl;

    return 0;
}

