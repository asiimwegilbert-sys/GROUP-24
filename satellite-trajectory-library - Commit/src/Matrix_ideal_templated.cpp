// test_matrix_templated.cpp
// Simple unit tests for the template helpers in matrix_utils.hpp.
// No test framework needed. Each check prints PASS or FAIL.
// The program returns 0 only if everything passed, which is what CTest uses.

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#include "satellite_trajectory/matrix.hpp"
#include "satellite_trajectory/matrix_templated.hpp"

using sat::num::allElements;
using sat::num::mapElements;
using sat::num::Matrix;
using sat::num::toMatrix;

int failures = 0;

// Prints PASS/FAIL for one check and counts failures.
void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "PASS: " << name << "\n";
    } else {
        std::cout << "FAIL: " << name << "\n";
        ++failures;
    }
}

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
            }
        }
    }
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

// A normal function, used to show mapElements also accepts these (not only lambdas).
double twice(double x) { return 2.0 * x; }

int main() {
    // toMatrix: nested vectors 

    // int data
    std::vector<std::vector<int>> ints = {{1, 2, 3}, {4, 5, 6}};
    Matrix fromInts = toMatrix(ints);
    check(fromInts.rows() == 2 && fromInts.columns() == 3, "toMatrix(int data) has size 2x3");
    check(sameValues(fromInts, Matrix{{1, 2, 3}, {4, 5, 6}}), "toMatrix(int data) values");

    // float data (0.5 and 1.5 are exact in float, so comparing is safe)
    std::vector<std::vector<float>> floats = {{0.5f, 1.5f}};
    check(sameValues(toMatrix(floats), Matrix{{0.5, 1.5}}), "toMatrix(float data)");

    // double data
    std::vector<std::vector<double>> doubles = {{0.1, 0.2}, {0.3, 0.4}};
    check(sameValues(toMatrix(doubles), Matrix{{0.1, 0.2}, {0.3, 0.4}}), "toMatrix(double data)");

    // 1x1 edge case
    std::vector<std::vector<int>> single = {{7}};
    Matrix one = toMatrix(single);
    check(one.rows() == 1 && one.columns() == 1 && one(0, 0) == 7, "toMatrix 1x1");

    // The input is not changed
    check(ints[1][2] == 6 && ints.size() == 2, "toMatrix does not change its input");

    // toMatrix: built-in 2D arrays 

    int array[2][3] = {{1, 2, 3}, {4, 5, 6}};
    check(sameValues(toMatrix(array), Matrix{{1, 2, 3}, {4, 5, 6}}), "toMatrix(int array[2][3])");

    double wide[1][2] = {{0.25, 0.5}};
    Matrix fromWide = toMatrix(wide);
    check(fromWide.rows() == 1 && fromWide.columns() == 2 && fromWide(0, 1) == 0.5,
          "toMatrix(double array[1][2])");

    //  toMatrix: invalid inputs 

    std::vector<std::vector<int>> noRows;
    check(throwsInvalidArgument([&] { Matrix r = toMatrix(noRows); }), "toMatrix with no rows is rejected");

    std::vector<std::vector<int>> emptyRow = {{}};
    check(throwsInvalidArgument([&] { Matrix r = toMatrix(emptyRow); }), "toMatrix with an empty row is rejected");

    std::vector<std::vector<int>> ragged = {{1, 2}, {3}};
    check(throwsInvalidArgument([&] { Matrix r = toMatrix(ragged); }),
          "toMatrix with rows of different length is rejected");

    // mapElements 

    Matrix A{{1, -2}, {3, -4}};

    // Lambda with no captured values
    Matrix squares = mapElements(A, [](double x) { return x * x; });
    check(sameValues(squares, Matrix{{1, 4}, {9, 16}}), "mapElements with a lambda (squares)");

    // Standard library function inside a lambda
    Matrix absolute = mapElements(A, [](double x) { return std::fabs(x); });
    check(sameValues(absolute, Matrix{{1, 2}, {3, 4}}), "mapElements absolute value");

    // Lambda that uses an outside value
    double factor = 10.0;
    Matrix scaled = mapElements(A, [factor](double x) { return factor * x; });
    check(sameValues(scaled, Matrix{{10, -20}, {30, -40}}), "mapElements with a captured value");

    // Normal function instead of a lambda
    check(sameValues(mapElements(A, twice), Matrix{{2, -4}, {6, -8}}), "mapElements with a normal function");

    // The original matrix is not changed
    check(sameValues(A, Matrix{{1, -2}, {3, -4}}), "mapElements does not change the original");

    // Rectangular and 1x1 matrices
    Matrix wideMatrix{{1, 2, 3}};
    Matrix mapped = mapElements(wideMatrix, [](double x) { return x + 1; });
    check(mapped.rows() == 1 && mapped.columns() == 3 && mapped(0, 2) == 4, "mapElements keeps the size (1x3)");
    check(mapElements(Matrix{{5.0}}, [](double x) { return -x; })(0, 0) == -5.0, "mapElements on 1x1");

    // Invalid input
    Matrix empty;
    check(throwsInvalidArgument([&] { Matrix r = mapElements(empty, twice); }),
          "mapElements on an empty matrix is rejected");

    //  allElements 

    Matrix positive{{1, 2}, {3, 4}};
    check(allElements(positive, [](double x) { return x > 0; }), "allElements true when every element passes");
    check(!allElements(A, [](double x) { return x > 0; }), "allElements false when some element fails");

    // Last element is the only one that fails (makes sure the whole matrix is checked)
    Matrix lastBad{{1, 2}, {3, -1}};
    check(!allElements(lastBad, [](double x) { return x > 0; }), "allElements checks the last element");

    // Checking for NaN and infinity
    Matrix hasNaN{{1.0, std::numeric_limits<double>::quiet_NaN()}};
    Matrix hasInf{{std::numeric_limits<double>::infinity(), 1.0}};
    auto isFinite = [](double x) { return std::isfinite(x); };
    check(allElements(positive, isFinite), "allElements finite: normal matrix passes");
    check(!allElements(hasNaN, isFinite), "allElements finite: NaN is caught");
    check(!allElements(hasInf, isFinite), "allElements finite: infinity is caught");

    // 1x1 and empty matrices
    check(allElements(Matrix{{3.0}}, [](double x) { return x == 3.0; }), "allElements on 1x1");
    check(allElements(empty, [](double) { return false; }), "allElements on an empty matrix is true (no elements)");

    //  Summary 
    if (failures == 0) {
        std::cout << "\nAll tests passed.\n";
        return 0;
    }
    std::cout << "\n" << failures << " test(s) FAILED.\n";
    return 1;
}
