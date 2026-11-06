#include "satellite_trajectory/decompositions.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

int failures = 0;

void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "PASS: " << name << '\n';
    } else {
        std::cerr << "FAIL: " << name << '\n';
        ++failures;
    }
}

bool near(double lhs, double rhs, double tolerance = 1e-9) {
    return std::abs(lhs - rhs) <= tolerance;
}

bool matrices_near(const sat::num::Matrix& lhs,
                   const sat::num::Matrix& rhs,
                   double tolerance = 1e-9) {
    if (lhs.rows() != rhs.rows() || lhs.columns() != rhs.columns()) {
        return false;
    }
    for (std::size_t i = 0; i < lhs.rows(); ++i) {
        for (std::size_t j = 0; j < lhs.columns(); ++j) {
            if (!near(lhs(i, j), rhs(i, j), tolerance)) {
                return false;
            }
        }
    }
    return true;
}

bool throws(const std::function<void()>& action, bool invalid_argument) {
    try {
        action();
    } catch (const std::invalid_argument&) {
        return invalid_argument;
    } catch (const std::runtime_error&) {
        return !invalid_argument;
    } catch (...) {
        return false;
    }
    return false;
}

sat::num::Matrix apply_permutation(const sat::num::Matrix& matrix,
                                   const std::vector<std::size_t>& permutation) {
    sat::num::Matrix result(matrix.rows(), matrix.columns());
    for (std::size_t i = 0; i < matrix.rows(); ++i) {
        for (std::size_t j = 0; j < matrix.columns(); ++j) {
            result(i, j) = matrix(permutation.at(i), j);
        }
    }
    return result;
}

} // namespace

int main() {
    using namespace sat::num;

    const Matrix pivoted{{0.0, 2.0, 1.0},
                         {1.0, 1.0, 0.0},
                         {2.0, 0.0, 1.0}};
    const auto lu = lu_decompose(pivoted);
    check(matrices_near(apply_permutation(pivoted, lu.permutation),
                        lu.lower * lu.upper),
          "LU satisfies P*A = L*U with pivoting");
    check(lu.swap_count > 0, "LU records row swaps");

    const Matrix positive_definite{{4.0, 2.0}, {2.0, 3.0}};
    const auto cholesky = cholesky_decompose(positive_definite);
    check(matrices_near(cholesky.lower * cholesky.upper, positive_definite),
          "Cholesky factors reconstruct the input");

    const Matrix rectangular{{1.0, 1.0},
                             {1.0, 0.0},
                             {0.0, 1.0}};
    const Matrix identity = Matrix::identity(rectangular.columns());
    const auto householder = qr_decompose(rectangular);
    check(matrices_near(householder.q * householder.r, rectangular),
          "Householder QR reconstructs the input");
    check(matrices_near(householder.q.transpose() * householder.q, identity),
          "Householder Q has orthonormal columns");

    const auto modified_gs = qr_gram_schmidt(rectangular);
    check(matrices_near(modified_gs.q * modified_gs.r, rectangular),
          "Modified Gram-Schmidt QR reconstructs the input");
    check(matrices_near(modified_gs.q.transpose() * modified_gs.q, identity),
          "Modified Gram-Schmidt Q has orthonormal columns");
    check(matrices_near(gram_schmidt(rectangular).transpose() * gram_schmidt(rectangular),
                        identity),
          "Gram-Schmidt convenience function returns orthonormal columns");

    check(throws([] { (void)lu_decompose(Matrix{{1.0, 2.0}, {2.0, 4.0}}); }, false),
          "LU rejects singular matrices");
    check(throws([] { (void)cholesky_decompose(Matrix{{1.0, 2.0}, {0.0, 1.0}}); }, true),
          "Cholesky rejects non-symmetric matrices");
    check(throws([] { (void)cholesky_decompose(Matrix{{1.0, 2.0}, {2.0, 1.0}}); }, false),
          "Cholesky rejects matrices that are not positive definite");
    check(throws([] { (void)qr_decompose(Matrix{{1.0, 2.0}, {2.0, 4.0}}); }, false),
          "Householder QR rejects dependent columns");
    check(throws([] { (void)qr_gram_schmidt(Matrix{{1.0, 2.0}, {2.0, 4.0}}); }, false),
          "Modified Gram-Schmidt rejects dependent columns");
    check(throws([] { (void)qr_decompose(Matrix{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}}); }, true),
          "QR rejects matrices with more columns than rows");
    check(throws([] { (void)lu_decompose(Matrix{{1.0}}, 0.0); }, true),
          "Decompositions reject non-positive tolerances");

    if (failures == 0) {
        std::cout << "\nAll decomposition tests passed.\n";
        return 0;
    }
    std::cerr << failures << " decomposition test(s) failed.\n";
    return 1;
}
