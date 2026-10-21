// test_matrix.cpp
// Simple unit tests for Matrix. No test framework needed.
// Each check prints PASS or FAIL. The program returns 0 only if everything passed,
// which is what CTest uses to decide if the test passed.

#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

#include "satellite_trajectory/matrix.hpp"

using sat::num::Matrix;

int failures = 0;

// Prints PASS/FAIL for one check and counts failures.
void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "PASS: " << name << "\n";
    } else {
        std::cout << "FAIL: " << name << "\n";
        ++failures;  }}

// True if both matrices have the same size and every pair of elements
// differs by no more than 'tolerance'.
bool sameValues(const Matrix& a, const Matrix& b, double tolerance = 1e-12) {
    if (a.rows() != b.rows() || a.columns() != b.columns()) {
        return false;
    }
    for (std::size_t i = 0; i < a.rows(); ++i) {
        for (std::size_t j = 0; j < a.columns(); ++j) {
            if (std::fabs(a(i, j) - b(i, j)) > tolerance) {
                return false;
            }   }}
    return true;
}
// True if running 'action' throws std::invalid_argument.
bool throwsInvalidArgument(const std::function<void()>& action) {
    try {
        action();
    } catch (const std::invalid_argument&) {
        return true;
    } catch (...) {
        return false;  // some other exception type
    }
    return false;  // nothing was thrown
}

// True if running 'action' throws std::out_of_range.
bool throwsOutOfRange(const std::function<void()>& action) {
    try {
        action();
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

int main() {
    //  Normal cases 

    // Default constructor gives an empty matrix
    Matrix empty;
    check(empty.rows() == 0 && empty.columns() == 0, "default matrix is 0x0");

    // Sized constructor: zeros by default, or a chosen fill value
    Matrix zeros(2, 3);
    check(zeros.rows() == 2 && zeros.columns() == 3, "size of 2x3 matrix");
    check(zeros(1, 2) == 0.0 && zeros(0, 0) == 0.0, "new matrix is filled with zeros");
    Matrix filled(2, 2, 2.5);
    check(filled(0, 0) == 2.5 && filled(1, 1) == 2.5, "fill value is used");

    // Nested list constructor and zero-based access
    Matrix A{{1, 2, 3}, {4, 5, 6}};
    check(A.rows() == 2 && A.columns() == 3, "nested list gives 2x3");
    check(A(0, 0) == 1 && A(0, 2) == 3 && A(1, 0) == 4 && A(1, 2) == 6,
          "values are stored row by row, zero-based");

    // Writing an element
    Matrix B(2, 2);
    B(0, 1) = 7.5;
    B(1, 0) = -2.0;
    check(B(0, 1) == 7.5 && B(1, 0) == -2.0 && B(0, 0) == 0.0, "elements can be changed");

    // Identity
    Matrix I = Matrix::identity(3);
    check(I.rows() == 3 && I.columns() == 3 && I(0, 0) == 1 && I(1, 1) == 1 && I(2, 2) == 1 &&
              I(0, 1) == 0 && I(2, 0) == 0,
          "identity matrix");

    // Transpose of a rectangular matrix
    Matrix At = A.transpose();
    check(At.rows() == 3 && At.columns() == 2, "transpose swaps the size");
    check(sameValues(At, Matrix{{1, 4}, {2, 5}, {3, 6}}), "transpose values");
    check(sameValues(At.transpose(), A), "transposing twice gives the original");

    // Addition and subtraction
    Matrix P{{1, 2}, {3, 4}};
    Matrix Q{{10, 20}, {30, 40}};
    check(sameValues(P + Q, Matrix{{11, 22}, {33, 44}}), "addition");
    check(sameValues(Q - P, Matrix{{9, 18}, {27, 36}}), "subtraction");

    // Matrix multiplication (2x3 times 3x2 gives 2x2)
    Matrix X{{1, 2, 3}, {4, 5, 6}};
    Matrix Y{{7, 8}, {9, 10}, {11, 12}};
    Matrix XY = X * Y;
    check(XY.rows() == 2 && XY.columns() == 2, "product size is (2x3)*(3x2) = 2x2");
    check(sameValues(XY, Matrix{{58, 64}, {139, 154}}), "product values");

    // Multiplying by identity changes nothing
    check(sameValues(P * Matrix::identity(2), P), "A * I = A");
    check(sameValues(Matrix::identity(2) * P, P), "I * A = A");

    // Multiplication is not commutative
    Matrix M1{{1, 2}, {3, 4}};
    Matrix M2{{0, 1}, {1, 0}};
    check(!sameValues(M1 * M2, M2 * M1), "A*B is not always B*A");

    // Scalar multiplication (number on the left)
    check(sameValues(2.0 * P, Matrix{{2, 4}, {6, 8}}), "number * matrix");
    check(sameValues(0.5 * Q, Matrix{{5, 10}, {15, 20}}), "0.5 * matrix");

    // Operations do not change the original matrices
    check(sameValues(P, Matrix{{1, 2}, {3, 4}}), "original unchanged after operations");

    // Edge cases

    // 1x1 matrix
    Matrix one{{5.0}};
    check(one.rows() == 1 && one.columns() == 1, "1x1 from nested list");
    check((one * one)(0, 0) == 25, "1x1 multiplication");
    check(one.transpose()(0, 0) == 5, "1x1 transpose");

    // Row times column (1x3 * 3x1 = 1x1, the dot product)
    Matrix row{{1, 2, 3}};
    Matrix col{{4}, {5}, {6}};
    check((row * col)(0, 0) == 32, "row * column = dot product (32)");

    // Column times row gives a 3x3 matrix
    Matrix outer = col * row;
    check(outer.rows() == 3 && outer.columns() == 3 && outer(2, 1) == 12,
          "column * row gives 3x3");

    // Last valid index works
    check(A(A.rows() - 1, A.columns() - 1) == 6, "last valid index");

    // Zero matrix behaviour
    Matrix Z(2, 2);
    check(sameValues(P + Z, P) && sameValues(P * Z, Z), "adding or multiplying by zeros");
    check(sameValues(0.0 * P, Z), "scalar 0 gives zero matrix");

    // Element access on a const matrix
    const Matrix constant{{1, 2}, {3, 4}};
    check(constant(1, 0) == 3, "const matrix can be read");

    // Invalid inputs

    // Bad construction
    check(throwsInvalidArgument([] { Matrix m(0, 3); }), "0 rows is rejected");
    check(throwsInvalidArgument([] { Matrix m(3, 0); }), "0 columns is rejected");
    check(throwsInvalidArgument([] { Matrix m = Matrix::identity(0); }), "identity(0) is rejected");
    check(throwsInvalidArgument([] { Matrix m{{1, 2}, {3}}; }), "rows of different length are rejected");
    check(throwsInvalidArgument([] { Matrix m{{}}; }), "empty row is rejected");

    // Bad indices (non-const and const versions)
    check(throwsOutOfRange([&] { A(2, 0); }), "row index too large is rejected");
    check(throwsOutOfRange([&] { A(0, 3); }), "column index too large is rejected");
    check(throwsOutOfRange([&] { constant(5, 5); }), "const access also checks indices");

    // Mismatched sizes
    check(throwsInvalidArgument([&] { Matrix r = A + P; }), "adding different sizes is rejected");
    check(throwsInvalidArgument([&] { Matrix r = A - P; }), "subtracting different sizes is rejected");
    check(throwsInvalidArgument([&] { Matrix r = A * A; }), "(2x3)*(2x3) is rejected");

    // summary
    if (failures == 0) {
        std::cout << "\nAll tests passed.\n";
        return 0;
    }
    std::cout << "\n" << failures << " test(s) FAILED.\n";
    return 1;
}
