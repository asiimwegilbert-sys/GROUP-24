#include "satellite_trajectory/decompositions.hpp"

#include <iomanip>
#include <iostream>

using sat::num::Matrix;

void print_matrix(const char* label, const Matrix& matrix)
{
    std::cout << label << '\n' << std::fixed << std::setprecision(4);
    for (std::size_t i = 0; i < matrix.rows(); ++i) {
        for (std::size_t j = 0; j < matrix.columns(); ++j) {
            std::cout << std::setw(10) << matrix(i, j);
        }
        std::cout << '\n';
    }
}

int main()
{
    // A deliberately pivot-requiring matrix demonstrates P*A = L*U.
    const Matrix a{{0.0, 2.0, 1.0},
                   {1.0, 1.0, 0.0},
                   {2.0, 0.0, 1.0}};

    const auto lu = sat::num::lu_decompose(a);
    Matrix pa(a.rows(), a.columns());
    for (std::size_t i = 0; i < a.rows(); ++i) {
        for (std::size_t j = 0; j < a.columns(); ++j) {
            pa(i, j) = a(lu.permutation[i], j);
        }
    }
    print_matrix("P*A (LU pivoted input):", pa);
    print_matrix("L:", lu.lower);
    print_matrix("U:", lu.upper);
    std::cout << "LU row swaps: " << lu.swap_count << "\n\n";

    const Matrix spd{{4.0, 2.0}, {2.0, 3.0}};
    const auto ch = sat::num::cholesky_decompose(spd);
    print_matrix("Cholesky L:", ch.lower);
    print_matrix("Cholesky L^T:", ch.upper);

    const Matrix rectangular{{1.0, 1.0},
                             {1.0, 0.0},
                             {0.0, 1.0}};
    const auto qr = sat::num::qr_decompose(rectangular);
    print_matrix("Householder Q:", qr.q);
    print_matrix("Householder R:", qr.r);

    const auto gs = sat::num::qr_gram_schmidt(rectangular);
    print_matrix("Modified Gram-Schmidt Q:", gs.q);
    print_matrix("Modified Gram-Schmidt R:", gs.r);
    return 0;
}
